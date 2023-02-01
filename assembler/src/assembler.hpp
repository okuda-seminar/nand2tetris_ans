#pragma once

#include <fstream>
#include <string>
#include <unordered_map>

#include "code.hpp"
#include "parser.hpp"
#include "symbol_table.hpp"

extern const std::unordered_map<std::string, std::string> dest_map;
extern const std::unordered_map<std::string, std::string> comp_map;
extern const std::unordered_map<std::string, std::string> jump_map;

class Assembler {
  public:
    Assembler(const std::string input_file);
    ~Assembler();
    void BuildSymbolTable();
    void GenerateCode();
    SymbolTable GetSymbolTable(){return symbol_table_;}

  private:
    std::ofstream output_stream_;
    Parser parser_;
    SymbolTable symbol_table_;
};