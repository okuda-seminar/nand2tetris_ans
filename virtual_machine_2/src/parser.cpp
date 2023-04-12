#include "parser.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

namespace vm {

Parser::Parser(const std::string input_file) {
  input_stream_.open(input_file);
  if (!input_stream_) {
    std::cerr << "failed to open the input file " << input_file << std::endl;
    exit(-1);
  }
  current_line_ = "";
}

Parser::~Parser() {
  input_stream_.close();
}

bool Parser::HasMoreCommands() {
  return !input_stream_.eof() || current_line_ != "";
}

void Parser::Advance() {
  if (input_stream_.eof()) {
    current_line_ = "";
    return;
  }
  getline(input_stream_, current_line_);

  // deals with the case when the current_line_ contains comment.
  int slash_pos = current_line_.find('/');
  if (slash_pos == 0) {
    Advance();
  } else if (slash_pos != std::string::npos) {
    current_line_ = current_line_.substr(0, slash_pos);
  }

  // removes spaces from the left side of current_line_.
  current_line_.erase(
    current_line_.begin(),
    std::find_if(
      current_line_.begin(),
      current_line_.end(),
      [](unsigned char c) { return !isspace(c); }
    )
  );

  // removes spaces from the right side of current_line_.
  current_line_.erase(
    std::find_if(
      current_line_.rbegin(),
      current_line_.rend(),
      [](unsigned char c) { return !isspace(c); }
    ).base(),
    current_line_.end()
  );

  if (current_line_ == "") {
    Advance();
  }
}

VMCommandType Parser::GetVMCommandType() {
  if (current_line_.substr(0, 4) == "push")
  {
    current_vm_command_type_ = VMCommandType::kC_PUSH;
  } else if (current_line_.substr(0, 3) == "pop")
  {
    current_vm_command_type_ = VMCommandType::kC_POP;
  } else if (current_line_.substr(0, 5) == "label")
  {
    current_vm_command_type_ = VMCommandType::kC_LABEL;
  } else if (current_line_.substr(0, 4) == "goto") 
  {
    current_vm_command_type_ = VMCommandType::kC_GOTO;
  } else if (current_line_.substr(0, 7) == "if-goto")
  {
    current_vm_command_type_ = VMCommandType::kC_IF;
  } else if (current_line_.substr(0, 8) == "function")
  {
    current_vm_command_type_ = VMCommandType::kC_FUNCTION;
  } else if (current_line_.substr(0, 4) == "call")
  {
    current_vm_command_type_ = VMCommandType::kC_CALL;
  } else if (current_line_.substr(0, 6) == "return")
  {
    current_vm_command_type_ = VMCommandType::kC_RETURN;
  } else {
    current_vm_command_type_ = VMCommandType::kC_ARITHMETIC;
  }

  return current_vm_command_type_;
}

std::string Parser::GetArg1() {
  if (current_vm_command_type_ == VMCommandType::kC_RETURN) {
    std::cerr << "GetArg1 should not be called if "
      << "the current command is kC_RETURN." << std::endl;
    exit(-1);
  }

  if (current_vm_command_type_ == VMCommandType::kC_ARITHMETIC) {
    return current_line_;
  }

  auto arg_1_start_pos = current_line_.find(' ');
  if (arg_1_start_pos == std::string::npos) {
    std::cerr << "invalid command is found: " << current_line_ << std::endl;
    exit(-1);
  }
  std::string arg_1 = current_line_.substr(arg_1_start_pos + 1);

  auto arg_1_end_pos = arg_1.find(' ');
  if (arg_1_end_pos == std::string::npos) {
    return arg_1;
  } else {
    arg_1 = arg_1.substr(0, arg_1_end_pos);
  }

  return arg_1;
}

int Parser::GetArg2() {
  if (
    current_vm_command_type_ != VMCommandType::kC_PUSH &&
    current_vm_command_type_ != VMCommandType::kC_POP &&
    current_vm_command_type_ != VMCommandType::kC_FUNCTION &&
    current_vm_command_type_ != VMCommandType::kC_CALL
  ) {
    std::cerr << "GetArg2 should be called only if the curent command is "
      << "kC_PUSH, kC_POP, kC_FUNCTION, ot kC_CALL." << std::endl;
    exit(-1);
  }

  auto arg_2_start_pos = current_line_.rfind(' ');
  if (arg_2_start_pos == std::string::npos) {
    std::cerr << "invalid command is found: " << current_line_ << std::endl;
    exit(-1);
  }
  return std::stoi(current_line_.substr(arg_2_start_pos));
}

} // namespace vm
