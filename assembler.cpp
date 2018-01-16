#include<iostream>
#include<fstream>
#include<string>
#include<bitset>
#include<stdlib.h>
#include "Parser.h"
#include "Code.h"
using namespace std;
int main(int argc, char* argv[]){
  std::string filename = argv[1];
  Parser* parser = new Parser(filename);
  Code* code = new Code();
  std::string finalCode;
  while(parser -> hasMoreCommands()){
    parser -> advance();
    if(parser -> commandType() == A_Command){
      int intSymbol = atoi((parser -> symbol()).c_str());
      bitset<15> binarySymbol(intSymbol);
      finalCode += "0" + binarySymbol.to_string() + "\n";
    }
    else if(parser -> commandType() == C_Command){
      finalCode += "111" 
	+ code -> comp(parser -> comp())
	+ code -> dest(parser -> dest())
	+ code -> jump(parser -> jump())
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

       
