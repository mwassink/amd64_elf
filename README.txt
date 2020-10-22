Simple implementation of an assembler for x86-64, with up to SSE2 instructions, to help me learn x86 assembly better. Misses functionality in regards to labels and relocation.

The assembler creates opcodes and a table to create an object file from at&t syntax assembly, and it includes some tools to help. I plan on making a front-end specifically for ELF .o object files, but for now it will return opcodes like what a disassembler would return, but with assembly given.

In order to build, use the makefile included, which builds with basic args and no optimization.

cd tokens+dependencies
mkdir bin 
mkdir objects
make preprocessor
make amd64_elf

Example runs are included in tokens+dependencies/Examples
