cmake_minimum_required(VERSION 3.5)

project(TestGetInstructions LANGUAGES C)

include_directories(${PROJECT_SOURCE_DIR})
add_executable(TestGetInstructions TestGetInstructions.c get_instructions.c)
add_executable(TestCharInstructions TestCharInstructions.c)
