cmake_minimum_required(VERSION 3.13)
project(assembler)
add_library(assembler STATIC
  ./assembler.cpp
  ./parser.cpp
  ./symbol_table.cpp
)