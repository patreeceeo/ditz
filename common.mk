CC  = gcc
CXX = g++
LEG = leg

COMMON_OBJS=src/helpers.o src/index_adaptor.o src/lazytables.o src/parser.o src/repl.o

COMMON_LIBS=-lreadline

COMMON_INCLUDE_PATH=.
COMMON_SOURCE_PATH=src
.PHONY: all clean objects
COMMON_LINK_RECIPE=$(CXX) $^ $(LFLAGS) -o $@ 

common_top_rule: all

$(MY_PATH)/src/parser.c: $(MY_PATH)/src/parser.leg
	$(LEG) $(MY_PATH)/src/parser.leg > $(MY_PATH)/src/parser.c