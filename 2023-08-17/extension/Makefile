OBJS = src/soundex.o src/function.o src/operator.o
MODULE_big = soundex

EXTENSION = soundex
DATA = soundex--1.0.0.sql
PGFILEDESC = "soundex - tools for comparing strings"

REGRESS = soundex_function soundex_operator
PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
