#pragma once

#include <fstream>
#include <string>

#include "code_writer.hpp"
#include "parser.hpp"

namespace vm {

class VMTranslator {
  public:
    VMTranslator(const std::string input_file, const std::string output_file);
    ~VMTranslator();
    void Translate();

    // Wrapper of CodeWriter::WriteInit()
    void WriteInit() { code_writer_.WriteInit(); }

  private:
    Parser parser_;
    std::ofstream output_stream_;
    CodeWriter code_writer_;
};

} // namespace vm
