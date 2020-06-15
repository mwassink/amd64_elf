cmake_minimum_required(VERSION 3.5)

project(intel64 LANGUAGES C)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR})
include_directories(tokens+dependencies)
include_directories(write_output)
add_executable(TestCharInstructions tokens+dependencies/get_instructions.c tokens+dependencies//TestCharInstructions.c)
add_executable(TestGetInstructions  tokens+dependencies/get_instructions.c tokens+dependencies/TestGetInstructions.c)
