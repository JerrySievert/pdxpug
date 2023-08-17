OBJS = src/type.o
MODULE_big = fnord

EXTENSION = fnord
DATA = fnord--1.0.0.sql
PGFILEDESC = "fnords - can you see them?"

REGRESS = soundex_function soundex_operator
PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
