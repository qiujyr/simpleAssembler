#include "SymbolTable.h"

void SymbolTable::addEntry(string symbol, int address){
  table[symbol] = address;
}

bool SymbolTable::contains(string symbol){
  return table.find(symbol) != table.end();
}

//returns the address associated with the symbol
int SymbolTable::getAddress(string symbol){
  return table.find(symbol)->second;
}

