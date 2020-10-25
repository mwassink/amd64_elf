- Simple implementation of an assembler for x86-64, with up to SSE2 instructions, to help me learn x86 assembly better. Lacking functionality in regards to labels and relocation, as well as a proper scanner.

- The assembler creates opcodes and a table to create an object file from at&t syntax assembly, and it includes some tools to help. I plan on making a front-end specifically for ELF .o object files, but for now it will return opcodes like what a disassembler would return, but with assembly given.

In order to build, use the makefile included, which builds with basic args.

- cd tokens+dependencies
- mkdir bin 
- mkdir objects
- make preprocessor
- make amd64_elf

- Example runs are included in opcodes/examples with the at&t assembly and the output if something goes wrong.
- Output may differ from an objdump of the same  instructions assembled with 'as' because mapping is not one to one for certain instructions
