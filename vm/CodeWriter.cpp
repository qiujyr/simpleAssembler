#include "CodeWriter.h"
#include <iostream>
CodeWriter::CodeWriter(std::string filename) {
  fout.open(filename.c_str());
  labelCount = 0;
}

void CodeWriter::setFileName(std::string fname){
  filename = fname;
}  

void CodeWriter::writeArithmetic(std::string command) {
  if (command == "add"){
    fout << code1 << "M=D+M\n";// << "@SP\n" << "M=M+1\n";
  }
  else if (command == "sub"){
    fout << code1 << "M=M-D\n";// << "@SP\n" << "M=M+1\n";
  }
  else if (command == "neg"){
    fout << "@SP\n" << "M=M-1\n" << "A=M\n" << "M=-M\n";
  }
  else if (command == "eq"){
    fout << code1 << compare(true, "JEQ");
  }
  else if (command == "gt"){
    fout << code1 << compare(true, "JGT");
  }
  else if (command == "lt"){
    fout << code1 << compare(true, "JLT");
  }
  else if (command == "and"){
    fout << code1 << "M=M&D\n";
  }
  else if (command == "or"){
    fout << code1 << "M=M|D\n";
  }
  else if (command == "not"){
    fout << "@SP\n" << "M=M-1\n" << "A=M\n" << "M=!M\n";
  }
  fout << "@SP\n" << "M=M+1\n";
}

void CodeWriter::writePushPop(cmdType type, std::string segment, int index) {
  if (type == C_POP) {
  }
  else {//type is C_PUSH
    if (segment == "constant") {
      fout << "@" << index << "\n" << "D=A\n" << "@SP\n"
	   << "A=M\n" << "M=D\n" << "@SP\n" << "M=M+1\n";
    }
    
    //increment sp by 1
    //fout << "@SP\n" << "M=M+1\n";
  }
}

void CodeWriter::close() {
  fout << "(END)\n" << "@END\n" << "0;JMP\n";
  fout.close();
 }

std::string CodeWriter::compare(bool isArithmetic, std::string condition){
  std::string begin;
  if(isArithmetic){
    begin = "D=M-D\n";
  }
  else{
    begin = "D=D+M\n";
  }
  labelCount++;
  return begin + "@TRUE" + std::to_string(labelCount) + "\n" + "D;"
    + condition + "\n" + "@0\n" + "D=A\n" + "@SP\n" + "A=M\n" + "M=D\n"
    + "@OUT" + std::to_string(labelCount) + "\n" + "0;JMP\n" + "(TRUE"
    + std::to_string(labelCount) + ")\n" + "D=-1\n" + "@SP\n"
    + "A=M\n" + "M=D\n" + "(OUT" + std::to_string(labelCount) + ")\n"; 
}
