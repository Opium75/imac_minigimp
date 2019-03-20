export CC=gcc
export CFLAGS=-Wall -ansi
export LDFLAGS=-lm

SRC_REP = ./src/
BIN_REP = ./bin/

export PROG = .$(BIN_REP)minigimp

all : $(PROG)

$(PROG) :
	@(cd $(SRC_REP) && $(MAKE) $@)


clean:
	@(cd $(SRC_REP) && $(MAKE) $@)