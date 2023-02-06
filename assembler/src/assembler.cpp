#include "assembler.hpp"

#include <bitset>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

#include "code.hpp"
#include "parser.hpp"
#include "symbol_table.hpp"

namespace {
  bool IsNumber(const std::string str) {
    for (const char &c : str) {
      if (std::isdigit(c) == 0) return false;
    }
    return true;
  }
} // namespace

Assembler::Assembler(const std::string input_file)
  : parser_{input_file}, symbol_table_{} {
  int extension_pos = input_file.rfind('.');
  if (input_file.substr(extension_pos) != ".asm") {
    std::cerr << "the filename extension should be '.asm'." << std::endl;
    exit(-1);
  }
  
  std::string output_file = input_file.substr(0, extension_pos) + ".hack";
  output_stream_.open(output_file);
  if (!output_stream_) {
    std::cerr << "failed to open the output file." << std::endl;
    exit(-1);
  }
}

Assembler::~Assembler() {
  output_stream_.close();
}

void Assembler::BuildSymbolTable() {
  parser_.Advance();
  int address = 0;
  while (parser_.HasMoreCommands()) {
    CommandType command_type = parser_.GetCommandType();
    if (command_type == CommandType::kA or command_type == CommandType::kC) {
      ++address;
    } else if (command_type == CommandType::kL) {
      symbol_table_.AddEntry(parser_.GetSymbol(), address);
    }
    parser_.Advance();
  }

  parser_.SetStreamPosToBeginning();
}

void Assembler::GenerateCode() {
  parser_.Advance();

  int var_count = 0;
  while (parser_.HasMoreCommands()) {
    CommandType command_type = parser_.GetCommandType();

    if (command_type == CommandType::kA) {
      // A-Command
      std::string symbol = parser_.GetSymbol();
      if (IsNumber(symbol)) {
        std::bitset<16> binary(std::stoi(symbol));
        output_stream_ << binary << std::endl;
      } else {
        if (symbol_table_.IsContain(symbol)) {
          std::bitset<16> binary(symbol_table_.GetAddress(symbol));
          output_stream_ << binary << std::endl;
        } else {
          symbol_table_.AddEntry(symbol, var_count + 16);
          std::bitset<16> binary(var_count + 16);
          output_stream_ << binary << std::endl;
          ++var_count;
        }
      }
    } else if (command_type == CommandType::kC) {
      // C-Command
      std::string comp = comp_map.at(parser_.GetComp());
      std::string dest = dest_map.at(parser_.GetDest());
      std::string jump = jump_map.at(parser_.GetJump());

      output_stream_ << "111" + comp + dest + jump << std::endl;
    }
    parser_.Advance();
  }
}
