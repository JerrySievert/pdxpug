#include <time.h>

#include "c.h"
#include "postgres.h"

#include "fmgr.h"

/*
 * Fnord
 *
 * This defines the data that we store.  There are some special pieces as
 * part of this, vl_len_[4] is used to store the length of the data, we can
 * set that later.  This is pretty postgres standard.  We also track the time
 * that the insert occurs, and a value that gets expanded when we initially
 * allocate the structure.
 */
typedef struct Fnord {
  char vl_len_[ 4 ];
  time_t insert_time;
  char value[];
} Fnord;

PG_MODULE_MAGIC;

/* Define the functions. */
PG_FUNCTION_INFO_V1(fnord_in);
PG_FUNCTION_INFO_V1(fnord_out);

/*
 * fnord_in
 *
 * Input from a CSTRING that we convert to our Fnord structure, which gets
 * set a a Datum and returned.
 */
Datum fnord_in(PG_FUNCTION_ARGS) {
  /* The first argument as a CSTRING. */
  char *input = PG_GETARG_CSTRING(0);
  Fnord *fnord;

  /* Figure out the length of the input CSTRING. */
  int32 length = strlen(input);

  /*
   * Allocate the Fnord structure, which is the size of the structure plus
   * the length of the input and a terminator.
   */
  fnord = (Fnord *)palloc(sizeof(Fnord) + length + 1);

  /* Copy the input into the value, which should set the terminator as well. */
  strcpy(fnord->value, input);

  /* Note the time the insert occurred. */
  fnord->insert_time = time(0);

  /* And set the final variable size.  This is used for storage. */
  SET_VARSIZE(fnord, sizeof(Fnord) + length + 1);

  /* Free anything that might have been allocated. */
  PG_FREE_IF_COPY(input, 0);

  /* Return a pointer to the new filled Fnord structure. */
  PG_RETURN_POINTER(fnord);
}

/*
 * fnord_out
 *
 * Input from a Fnord object, and output to a CSTRING.  Except, if it has
 * not been 10 seconds yet, then you are not enlightened and cannot actually
 * see the Fnord.
 */
Datum fnord_out(PG_FUNCTION_ARGS) {
  /* Get a copy of the pointer from postgres. */
  Fnord *fnord = (Fnord *)PG_GETARG_POINTER(0);

  /* Check our current time. */
  time_t current = time(0);
  char *value;

  /* Are we enlightened? We will be 10 seconds past insert. */
  if (current - fnord->insert_time < 10) {
    /* No? Return that fact. */
    char *value = (char *)palloc(24);
    strcpy(value, "You are not enlightened");
  } else {
    /* Yes? Return the real value. */
    char *value = palloc(strlen(fnord->value) + 1);
    strcpy(value, fnord->value);
  }

  /* Free anything that might have been allocated. */
  PG_FREE_IF_COPY(fnord, 0);

  /* Return the value that was chosen. */
  PG_RETURN_CSTRING(value);
}
