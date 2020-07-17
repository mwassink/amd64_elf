CC=gcc
CFLAGSDEBUG=-Wall -Werror -g
SRCDIR=src
BINDIR=bin
OBJDIR=objects
vpath %.c src
vpath %.h include
vpath %.o objects

OBJFILES==bridgemachineinstruction.o get_instructions.o testcharinstructions.o testgetinstructions.o get_text_tokens.o \
modrm.o sib.o tests.o write_instructions.o validate_instructions.o
SOURCEFILES=bridgemachineinstruction.c get_instructions.c testcharinstructions.c testgetinstructions.c get_text_tokens.c \
modrm.c sib.c tests.c write_instructions.c validate_instructions.c


%.o : %.c
	$(CC) $(CFLAGSDEBUG) $^ -c -o $(OBJDIR)/$@

testgetinstructions: testgetinstructions.o get_instructions.o
	$(CC) $(CFLAGSDEBUG) $^ -o $(BINDIR)/$@

testcharinstructions: testcharinstructions.o get_instructions.o
	$(CC) $(CFLAGSDEBUG) $^ -o $(BINDIR)/$@

write_instructions: write_instructions.o get_instructions.o get_text_tokens.o
	$(CC) $(CFLAGSDEBUG) $^ -o $(BINDIR)/$@
