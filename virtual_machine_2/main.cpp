#include <iostream>
#include <string>

#include "./src/vm_translator.hpp"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "the arguments are invalid." << std::endl;
    exit(-1);
  }

  std::string input = argv[1];
  auto extension_pos = input.rfind('.');
  if (input.substr(extension_pos) != ".vm") {
    std::cerr << "the filename extension should be '.vm'." << std::endl;
    exit(-1);
  }
  std::string output = input.substr(0, extension_pos) + ".asm";

  vm::VMTranslator vm_translator(input, output);
  vm_translator.WriteInit();

  for (int i = 1; i < argc; i++) {
    vm::VMTranslator vm_translator(argv[i], output);
    vm_translator.Translate();
  }
  
  return 0;
}
