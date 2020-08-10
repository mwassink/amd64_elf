call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
ECHO Compiling and Linking: convert_instructions
cl convert_instruction.c get_text_tokens.c get_instructions.c /W4 /Z7 /EHsc /link /out:convert_instructions.exe
DEL convert_instruction.obj
MOVE convert_instructions.ilk ../bin/
MOVE convert_instructions.pdb ../bin/
DEL get_text_tokens.obj
DEL get_instructions.obj
MOVE .\convert_instructions.exe ../bin/
