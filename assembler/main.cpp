#include <iostream>
#include <string>

#include "src/assembler.hpp"
#include "src/parser.hpp"
#include "src/symbol_table.hpp"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "the arguments are invalid." << std::endl;
    exit(-1);
  }

  std::string input_file = argv[1];
  Assembler assembler(input_file);
  assembler.BuildSymbolTable();
  assembler.GenerateCode();

  return 0;
}