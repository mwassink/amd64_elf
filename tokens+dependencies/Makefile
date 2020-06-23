CC=gcc
CFLAGSDEBUG=-Wall -Werror -g
SRCDIR=src
BINDIR=bin
OBJDIR=objects
vpath %.c src
vpath %.h include
vpath %.o objects

OBJFILES=testcharinstructions.o testgetinstructions.o get_tokens.o \
get_instructions.o
SOURCEFILES=testcharinstructions.c testgetinstructions.c get_tokens.c \
get_instructions.c


%.o : %.c
	$(CC) $(CFLAGSDEBUG) $^ -c -o $(OBJDIR)/$@

testgetinstructions: testgetinstructions.o get_instructions.o
	$(CC) $(CFLAGSDEBUG) $^ -o $(BINDIR)/$@

testcharinstructions: testcharinstructions.o get_instructions.o
	$(CC) $(CFLAGSDEBUG) $^ -o $(BINDIR)/$@
