#include "SymbolTable.h"

void SymbolTable::addEntry(std::string symbol, int address){
  table[symbol] = address;
}

bool SymbolTable::contains(std::string symbol){
  return table.find(symbol) != table.end();
}

//returns the address associated with the symbol
int SymbolTable::getAddress(std::string symbol){
  return table.find(symbol)->second;
}

