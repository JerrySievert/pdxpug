CREATE FUNCTION fnord_in(cstring)
  RETURNS fnord
  AS 'MODULE_PATHNAME', 'fnord_in'
  LANGUAGE C PARALLEL SAFE;

CREATE FUNCTION fnord_out(fnord)
  RETURNS cstring
  AS 'MODULE_PATHNAME', 'fnord_out'
  LANGUAGE C PARALLEL SAFE;

CREATE TYPE fnord (
  INTERNALLENGTH = VARIABLE,
  INPUT = fnord_in,
  OUTPUT = fnord_out
);
