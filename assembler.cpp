#include<iostream>
#include<fstream>
#include<string>
#include<bitset>
#include<stdlib.h>
#include "Parser.h"
#include "Code.h"
#include "SymbolTable.h"

using namespace std;
int main(int argc, char* argv[]){
  std::string filename = argv[1];
  Parser* parser1 = new Parser(filename); //first parse
  Parser* parser2 = new Parser(filename); //second parse
  Code* code = new Code();

  //first traverse
  int lineCount = 0;
  SymbolTable* table = new SymbolTable();
  while(parser1 -> hasMoreCommands()){
    parser1 -> advance();
    if(parser1 -> commandType() == L_Command){
      table -> addEntry(parser1 -> symbol(), lineCount);
    }
    else{
      lineCount++;
    }
  }
  
  std::string finalCode;
  int addr = 16;
  while(parser2 -> hasMoreCommands()){
    parser2 -> advance();
    if(parser2 -> commandType() == A_Command){
      bitset<15> binarySymbol;
      std::string symb(parser2 -> symbol());
      if(table -> contains(symb)){
	binarySymbol = table -> getAddress(symb);
      }
      else{
	if(isdigit(symb[0])){
	    int intSymbol = atoi((parser2 -> symbol()).c_str());
	    binarySymbol = intSymbol;
	}
	else{
	  binarySymbol = addr;
	  addr++;
	}
      }
      finalCode += "0" + binarySymbol.to_string() + "\n";
    }
    else if(parser2 -> commandType() == C_Command){
      finalCode += "111"
	+ code -> comp(parser2 -> comp())
	+ code -> dest(parser2 -> dest())
	+ code -> jump(parser2 -> jump())
	+ "\n";
    }
  } 

  string outputFile = filename.substr(0, filename.length() - 4);
  outputFile += ".hack";
  ofstream hackFile(outputFile.c_str());
  hackFile << finalCode;
  hackFile.close();
  return 0;
}

       
