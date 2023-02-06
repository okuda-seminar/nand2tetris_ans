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

// Converts an assembly representation into binary code that can run
// directly on the Hack hardware platform.
// It consists of two steps.
// First step (building the symbol table):
//    Goes through the entire assembly program, line by line, and
//    builds the symbol table without generating any code.
// Second step (generating the binary code):
//    Goes again through the entire program, parse each line,
//    and generates the equivalent binary code.
class Assembler {
  public:
    Assembler(const std::string input_file);
    ~Assembler();

    // First step
    void BuildSymbolTable();

    // Second step
    void GenerateCode();

  private:
    std::ofstream output_stream_;
    Parser parser_;
    SymbolTable symbol_table_;
};