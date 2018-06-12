#ifndef _SYMBOL_TABLE_H_
#define _SYMBOL_TABLE_H_

#include<string>
#include<map>
class SymbolTable{
 public:
  //constructor
  SymbolTable() = default;

  void addEntry(std::string symbol, int address);
  bool contains(std::string symbol);
  getAddress(std::string symbol);

 private:
  map<std::string, int> table;
};

#endif
