#pragma once

#include <fstream>
#include <string>

namespace vm {

// The kinds of the VM command type.
// C_ARITHMETIC:
//    Performs arithmetic and logical operations on the stack.
// C_PUSH:
//    Pushs the value of the specified segment onto the stack.
// C_POP:
//    Pops the top stack value ans store it in the specified segment.
// C_LABEL:
//    Label declaration.
// C_GOTO:
//    Unconditional branching.
// C_IF:
//    Conditional branching.
// C_FUNCTION:
//    Declares function, specifying the number of the function's arguments.
// C_RETURN:
//    Transfers control back to the calling function.
// C_CALL:
//    Invokes function, specifying the number of the function's arguments.
enum class VMCommandType {
  kC_ARITHMETIC,
  kC_PUSH,
  kC_POP,
  kC_LABEL,
  kC_GOTO,
  kC_IF,
  kC_FUNCTION,
  kC_RETURN,
  kC_CALL,
};

// Gets a line from the input file and parse it.
// Example:
//    vm::Parser parser("input_file.vm");
//    parser.Advance();
//    std:string arg_1 = parser.GetArg1();
class Parser {
  public:
    Parser(const std::string input_file);
    ~Parser();
    bool HasMoreCommands();

    // Advances to the next line in 'input_stream_', and
    // assignes it to 'current_line_'. If the line contains a comment,
    // removes it. This process is repeated until non-empty line or
    // EOF of 'input_stream_' is reached.
    void Advance();

    // Parses 'current_line_', assignes the corresponding VM command type to
    // 'current_vm_command_type_', and returns it.
    VMCommandType GetVMCommandType();

    // Returns the first argument of the current command.
    // In the case of kC_ARITHMETIC, the command itself (add, sub, etc.)
    // is returned.
    // Should not be called if the current command is kC_RETURN.
    std::string GetArg1();

    // Returns the second argument of the current command.
    // Should be called only if the current command is
    // kC_PUSH, kC_POP, kC_FUNCTION, ot kC_CALL.
    int GetArg2();

    std::string GetCurrentLine() { return current_line_; }
  
  private:
    std::ifstream input_stream_;
    VMCommandType current_vm_command_type_;
    std::string current_line_;
};

} // namespace vm
