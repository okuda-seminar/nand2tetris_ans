#include "vm_translator.hpp"

#include <fstream>
#include <iostream>
#include <string>

#include "code_writer.hpp"
#include "parser.hpp"

namespace vm {

VMTranslator::VMTranslator(const std::string input_file,
                           const std::string output_file)
    : parser_{input_file} ,code_writer_{output_file} {
  output_stream_.open(output_file);
  if (!output_stream_) {
    std::cerr << "failed to open the output file " << output_file << std::endl;
    exit(-1);
  }
  
  // This process is for retrieving 'YYY.vm' from 'XXX/YYY.vm' format input.
  // The VM translator doesn't accept '/'.
  std::string input_file_name;
  auto input_file_slash_pos = input_file.rfind('/');
  if (input_file_slash_pos == std::string::npos) {
    input_file_name = input_file;
  } else {
    input_file_name = input_file.substr(input_file_slash_pos + 1);
  }
  code_writer_.SetVMFileName(input_file_name);
}

VMTranslator::~VMTranslator() {
  output_stream_.close();
}

void VMTranslator::Translate() {
  parser_.Advance();
  while (parser_.HasMoreCommands()) {
    VMCommandType vm_command_type = parser_.GetVMCommandType();

    switch (vm_command_type) {
      case VMCommandType::kC_ARITHMETIC:
        code_writer_.WriteArithmetic(parser_.GetArg1());
        break;

      case VMCommandType::kC_POP:
        code_writer_.WritePushPop(vm_command_type, parser_.GetArg1(),
                                  parser_.GetArg2());
        break;

      case VMCommandType::kC_PUSH:
        code_writer_.WritePushPop(vm_command_type, parser_.GetArg1(),
                                  parser_.GetArg2());
        break;

      default:
        std::cerr << "not implemented command." << std::endl;
    }

    parser_.Advance();
  }
}

} // namespace vm
