include common.mk

BIN = bin/repl
DEST = /usr/local/bin/alex/repl
CFLAGS = -I. 
CXXFLAGS = -I. -DREPL_MAIN
LFLAGS = $(COMMON_LIBS)
#SRC = src/helpers.cpp src/index_adaptor.cpp src/lazytables.cpp src/repl.cpp
MY_OBJS=$(COMMON_OBJS)
MY_PATH=.

all:$(BIN)
  
o.cpp:
	

o.c:
	

clean:
	rm -fr bin
	rm -fr build
	rm -f  src/*.o
	rm -f  src/parser.c
  
$(BIN): $(OBJ) src/parser.o src/repl_main.o
	mkdir -p bin
	$(COMMON_LINK_RECIPE)
	