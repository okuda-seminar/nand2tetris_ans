#include "symbol_table.hpp"

#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

void SymbolTable::AddEntry(const string symbol, const int address) {
  from_symbol_to_address_[symbol] = address;
};

bool SymbolTable::IsContain(const string symbol) {
  return from_symbol_to_address_.find(symbol) != from_symbol_to_address_.end();
};

int SymbolTable::GetAddress(const string symbol) {
  return from_symbol_to_address_[symbol];
};