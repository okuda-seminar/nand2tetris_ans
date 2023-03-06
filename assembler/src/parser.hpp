#pragma once

#include <fstream>
#include <string>

namespace assembler {

// The kinds of the command type.
// A-Command:
//    Used to set the A register to a 15-bit value.
// C-Command:
//    A specification that answers three questions: what to compute,
//    where to store the computed value, and what to do next.
// L-Command:
//    Defines a symbol which refers to the instruction memory location
//    holding the next command in the program.
enum class CommandType {
  kA,
  kC,
  kL,
};

// Gets a line from the input file and parses it.
// Example:
//    Parser parser("input_file.asm");
//    parser.Advance();
//    std::string symbol = parser.GetSymbol();
class Parser {
  public:
    Parser(const std::string input_file);
    ~Parser();

    // Resets the position of 'input_stream_' buffer to the start.
    void SetStreamPosToBeginning();

    // Advances to the next line in 'input_stream_', and
    // assignes it to 'current_line_'. If the line contains a comment,
    // removes it. This process is repeated until non-empty line or
    // EOF of 'input_stream_' is reached.
    void Advance();

    // Parses 'current_line_', assignes the corresponding command type to
    // 'current_command_type_', and returns it.
    CommandType GetCommandType();

    bool HasMoreCommands();
    std::string GetSymbol();
    std::string GetDest();
    std::string GetComp();
    std::string GetJump();
    std::string GetCurrentLine() { return current_line_; }

  private:
    std::ifstream input_stream_;
    CommandType current_command_type_;
    std::string current_line_;
};

} // namsespace assembler
