#pragma once

#include <string>
#include <unordered_map>

namespace assembler {

class SymbolTable {
  public:
    SymbolTable() : from_symbol_to_address_{
      {"SP", 0},
      {"LCL", 1},
      {"ARG", 2},
      {"THIS", 3},
      {"THAT", 4},
      {"R0", 0},
      {"R1", 1},
      {"R2", 2},
      {"R3", 3},
      {"R4", 4},
      {"R5", 5},
      {"R6", 6},
      {"R7", 7},
      {"R8", 8},
      {"R9", 9},
      {"R10", 10},
      {"R11", 11},
      {"R12", 12},
      {"R13", 13},
      {"R14", 14},
      {"R15", 15},
      {"SCREEN", 16384},
      {"KBD", 24576},
    } {};
    ~SymbolTable() = default;
    void AddEntry(const std::string symbol, const int address);
    bool IsContain(const std::string symbol);
    int GetAddress(const std::string symbol);
  
  private:
    std::unordered_map<std::string, int> from_symbol_to_address_;
};

} // namespace assembler
