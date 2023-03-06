#include "parser.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

namespace assembler {

Parser::Parser(const std::string input_file) {
  input_stream_.open(input_file);
  if (!input_stream_) {
    std::cerr << "failed to open the input file " << input_file << std::endl;
    exit(-1);
  }
  current_line_ = "";
};

Parser::~Parser() {
  input_stream_.close();
}

void Parser::SetStreamPosToBeginning() {
  input_stream_.clear();
  input_stream_.seekg(0);
}

bool Parser::HasMoreCommands() {
  return !input_stream_.eof();
}

void Parser::Advance() {
  if (!HasMoreCommands()) {
    current_line_ = "";
    return;
  }
  getline(input_stream_, current_line_);

  // deals with the case when the current_line_ contains comment.
  auto slash_pos = current_line_.find('/');
  if (slash_pos == 0) {
    Advance();
  } else if (slash_pos != std::string::npos) {
    current_line_ = current_line_.substr(0, slash_pos);
  }

  // removes all spaces from current_line_.
  current_line_.erase(
    std::remove_if(current_line_.begin(), current_line_.end(), ::isspace),
    current_line_.end()
  );
  if (current_line_ == "") {
    Advance();
  }
}

CommandType Parser::GetCommandType() {
  if (current_line_[0] == '@') {
    current_command_type_ = CommandType::kA;
  } else if (current_line_[0] == '(') {
    current_command_type_ = CommandType::kL;
  } else {
    current_command_type_ = CommandType::kC;
  }
  return current_command_type_;
}

std::string Parser::GetSymbol() {
  if (current_command_type_ == CommandType::kA) {
    return current_line_.substr(1);
  } else if (current_command_type_ == CommandType::kL) {
    return current_line_.substr(1, current_line_.length() - 2);
  } else {
    std::cerr << "GetSymbol has to be called only when "
      << "the current command is A-Command or L-Command" << std::endl;
    exit(-1);
  }
}

std::string Parser::GetDest() {
  if (current_command_type_ != CommandType::kC) {
    std::cerr << "GetDest has to be called only when "
      << "the current command is C-Command" << std::endl;
    exit(-1);
  }

  auto equal_pos = current_line_.find('=');
  if (equal_pos == std::string::npos) {
    return "";
  }
  return current_line_.substr(0, equal_pos);
}

std::string Parser::GetComp() {
  if (current_command_type_ != CommandType::kC) {
    std::cerr << "GetComp has to be called only when "
      << "the current command is C-Command" << std::endl;
    exit(-1);
  }

  auto equal_pos = current_line_.find('=');
  auto semicolon_pos = current_line_.find(';');

  if (equal_pos == std::string::npos) {
    return current_line_.substr(0, semicolon_pos);
  } else if (semicolon_pos == std::string::npos) {
    return current_line_.substr(equal_pos + 1);
  } else {
    return current_line_.substr(equal_pos + 1, semicolon_pos);
  }
}

std::string Parser::GetJump() {
  if (current_command_type_ != CommandType::kC) {
    std::cerr << "GetJump has to be called only when "
      << "the current command is C-Command" << std::endl;
    exit(-1);
  }

  auto semicolon_pos = current_line_.find(';');
  if (semicolon_pos == std::string::npos) {
    return "";
  }
  return current_line_.substr(semicolon_pos + 1);
}

} // namespace assembler
