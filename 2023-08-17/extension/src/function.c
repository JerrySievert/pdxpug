#include "postgres.h"

#include "fmgr.h"
#include "utils/palloc.h"

#include "soundex.h"

/* This sets up the Postgres module. */
PG_MODULE_MAGIC;

/* Our function declaration. */
Datum soundex_function(PG_FUNCTION_ARGS);

/* Register our function. */
PG_FUNCTION_INFO_V1(soundex_function);

Datum soundex_function(PG_FUNCTION_ARGS) {
  /* Get a copy of the first argument as a text type. */
  text *input = PG_GETARG_TEXT_PP(0);

  /* And get the length of the string. */
  int32 length = VARSIZE_ANY_EXHDR(input);

  /*
   * Allocate enough memory for the output, we know a Soundex is 4 characters
   * plus a string termination character, so we use the VARSIZE macro to give
   * us the correct amount of memory to allocate.
   */
  text *output = (text *)palloc(5 + VARHDRSZ);

  /*
   * We are using the text type, but only want the actual data locations
   * for our Soundex, so we use the VARDATA macro which exposes the actual
   * character pointers.
   */
  soundex(VARDATA(input), length, VARDATA(output));

  /* Set the size of the output, it should be 4, right? */
  SET_VARSIZE(output, 4 + VARHDRSZ);

  /* Free up any results we should be responsible for. */
  PG_FREE_IF_COPY(input, 0);

  /* Return a pointer to the output.  Postgres will pfree our memory. */
  PG_RETURN_TEXT_P(output);
}
