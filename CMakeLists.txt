cmake_minimum_required(VERSION 3.10)

project(TuringMachine VERSION 1.0
					  DESCRIPTION "Implementation of a Turing Machine in C"
					  LANGUAGES C
)

add_executable(turing_machine src/main.c)

# Instructs the compiler to print as many warnings as possible
# Refer https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html for GCC warning options
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(turing_machine PRIVATE -Wall -Wextra -Wpedantic)
elseif(CMAKE_C_COMPILER_ID STREQUAL "MSVC")
	target_compile_options(turing_machine PRIVATE /W4) 
endif()
