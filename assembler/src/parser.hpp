#pragma once

#include <fstream>
#include <string>

enum class CommandType {
  kA,
  kC,
  kL,
};

class Parser {
  public:
    Parser(const std::string input_file);
    ~Parser();
    void SetStreamPosToBeginning();
    bool HasMoreCommands();
    void Advance();
    std::string GetSymbol();
    std::string GetDest();
    std::string GetComp();
    std::string GetJump();

    // getter function
    CommandType GetCommandType();
    std::string GetCurrentLine() {return current_line_;}

  private:
    std::ifstream input_stream_;
    CommandType current_command_type_;
    std::string current_line_;
};