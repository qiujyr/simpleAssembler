#include <iostream>
#include "Parser.h"
#include "CodeWriter.h"
#include <string>

int main(int argc, char* argv[]) {
  std::string filename = argv[1];
  Parser parser(filename);
  std::string outputFile(filename.substr(0,filename.find(".vm")));
  outputFile += ".asm";
  CodeWriter codeWriter(outputFile);
  while (parser.hasMoreCommands()) {
    parser.advance();
    if (parser.commandType() == C_ARITHMETIC) {
      codeWriter.writeArithmetic(parser.getCmd());
    }
    else if (parser.commandType() == C_PUSH) {
      codeWriter.writePushPop(C_PUSH, parser.arg1(), parser.arg2());
    }
    else if (parser.commandType() == C_POP) {
      codeWriter.writePushPop(C_POP, parser.arg1(), parser.arg2());
    }
  }
  codeWriter.close();
}
