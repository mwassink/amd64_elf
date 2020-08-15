CC=gcc
CFLAGSDEBUG=-Wall -Werror -g -Wno-unused-but-set-variable
SRCDIR=src
BINDIR=bin
OBJDIR=objects
vpath %.c src
vpath %.h include
vpath %.o src

OBJFILES==bridgemachineinstruction.o get_instructions.o testcharinstructions.o testgetinstructions.o get_text_tokens.o \
modrm.o sib.o tests.o write_instructions.o validate_instructions.o convert_instructions.o
SOURCEFILES=bridgemachineinstruction.c get_instructions.c testcharinstructions.c testgetinstructions.c get_text_tokens.c \
modrm.c sib.c tests.c write_instructions.c validate_instructions.c


%.o: %.c
	@echo "Creating Object..."
	$(CC) $(CFLAGSDEBUG) $< -c -o $@

testgetinstructions: testgetinstructions.o get_instructions.o
	$(CC) $(CFLAGSDEBUG) $^ -o $(BINDIR)/$@
	$(RM) $^

testcharinstructions: testcharinstructions.o get_instructions.o
	$(CC) $(CFLAGSDEBUG) $^ -o $(BINDIR)/$@
	$(RM) $^

write_instructions: write_instructions.o get_instructions.o get_text_tokens.o
	$(CC) $(CFLAGSDEBUG) $^ -o $(BINDIR)/$@
	$(RM) $^

convert_instructions: convert_instruction.o get_text_tokens.o get_instructions.o
	@echo "Linking Objects..."
	$(CC) $(CFLAGSDEBUG) $^ -o $(BINDIR)/$@
	$(RM) $^
function_tests: function_tests.o convert_instruction.o get_text_tokens.o get_instructions.o
	$(CC) $(CFLAGSDEBUG) $^ -o $(BINDIR)/$@
	$(RM) $^
