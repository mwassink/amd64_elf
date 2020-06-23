
IDIR =include
CC=gcc
CFLAGS=-Werror -Wall -g
DEPS=elf.h
OUTDIR=objects
vpath %.c src
vpath %.o objects
vpath %.h include
INCLUDES=include
SOURCES = elf.c testelfheader.c
SRCDIR=src
OBJECTS=objects
_OBJECTS= elf.o testelfheader.o
BIN= bin


%.o : %.c
	$(CC) -c -o $(OBJECTS)/$@ $^ $(CFLAGS)

testelfobjects: $(_OBJECTS)
	$(CC)  $^ $(CFLAGS) -c -o $(OBJECTS)/$@

testelf: $(SOURCES)
	$(CC)  $^ $(CFLAGS) -o $(BIN)/$@

.PHONY: clean

clean:
	rm -f $(OBJS) testelfheader
