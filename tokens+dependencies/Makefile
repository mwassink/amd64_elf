CC=gcc
CFLAGSDEBUG=-Wall -Werror -g -Wno-unused-but-set-variable
SRCDIR=src
BINDIR=bin
OBJDIR=src
TESTDIR=Tests
vpath %.c src
vpath %.h include
vpath %.o objects

%.o: %.c
	@echo "Creating Object..."
	$(CC) $(CFLAGSDEBUG) $< -c -o $@

testgetinstructions: testgetinstructions.o get_instructions.o
	$(CC) $(CFLAGSDEBUG)  $(TESTDIR)/$^ -o $(BINDIR)/$@
	$(RM) $(TESTDIR)/$^

testcharinstructions: testcharinstructions.o get_instructions.o
	$(CC) $(CFLAGSDEBUG)  $(TESTDIR)/$^ -o $(BINDIR)/$@
	$(RM) $(TESTDIR)/$^

write_instructions: write_instructions.o get_instructions.o  utilities.o
	$(CC) $(CFLAGSDEBUG) $^ -o $(BINDIR)/$@
	$(RM) $^

convert_instructions: convert_instruction.o  get_instructions.o utilities.o
	@echo "Linking Objects..."
	$(CC) $(CFLAGSDEBUG) $^ -o $(BINDIR)/$@
	$(RM) $^
function_tests: function_tests.o convert_instruction.o  get_instructions.o
	$(CC) $(CFLAGSDEBUG)  $(TESTDIR)/$^ -o $(BINDIR)/$@
	$(RM) $(TESTDIR)/$^

test_convert_instructions: test_convert_instructions.o convert_instruction.o  get_instructions.o
	@echo "Linking Objects"
	$(CC) $(CFLAGSDEBUG)  $(TESTDIR)/$^ -o $(BINDIR)/$@
	$(RM) $(TESTDIR)/$^
