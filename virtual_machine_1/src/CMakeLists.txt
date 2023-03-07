cmake_minimum_required(VERSION 3.13)
project(vm_translator)
add_library(vm_translator STATIC
  ./code_writer.cpp
  ./parser.cpp
  ./vm_translator.cpp
)
