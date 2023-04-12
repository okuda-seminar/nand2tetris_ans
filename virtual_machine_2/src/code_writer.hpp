#pragma once

#include <fstream>
#include <string>

#include "parser.hpp"

namespace vm {

class CodeWriter {
  public:
    CodeWriter(const std::string output_file);
    ~CodeWriter();

    // Informs the code writer that the translation of a new VM file is started.
    void SetVMFileName(const std::string file_name);

    // Writes the assembly code that is the translation of
    // the given arithmetic command.
    void WriteArithmetic(const std::string command);

    // Writes the assembly code that is the translation of the given command,
    // where command is either kC_PUSH or kC_POP.
    void WritePushPop(const VMCommandType command_type,
                      const std::string segment,
                      const int index);
    
    // Writes the assembly code that calls 'Sys.init'.
    // When a VM program starts running (or is reset), the convention is that
    // it always executes an argument-less VM function, Sys.init.
    void WriteInit();

    void WriteLabel(const std::string label);
    void WriteGoto(const std::string label);
    void WriteIf(const std::string label);
    void WriteCall(const std::string function_name, const int num_args);
    void WriteFunction(const std::string function_name, const int num_locals);
    void WriteReturn();
  
  private:
    std::ofstream output_stream_;
    std::string vm_file_name_{""};
    int label_count_{0};
    int return_count_{0};

    void WriteAdd();
    void WriteSub();
    void WriteNeg();
    void WriteEq();
    void WriteGt();
    void WriteLt();
    void WriteAnd();
    void WriteOr();
    void WriteNot();
    void WritePush(const std::string segment, const int index);
    void WritePop(const std::string segment, const int index);
    void SaveState(std::string register_name);
};

} // namespace vm