#include "symbol_table.hpp"

#include <string>
#include <unordered_map>

namespace assembler {

void SymbolTable::AddEntry(const std::string symbol, const int address) {
  from_symbol_to_address_[symbol] = address;
};

bool SymbolTable::IsContain(const std::string symbol) {
  return from_symbol_to_address_.find(symbol) != from_symbol_to_address_.end();
};

int SymbolTable::GetAddress(const std::string symbol) {
  return from_symbol_to_address_[symbol];
};

} // namespace assembler
