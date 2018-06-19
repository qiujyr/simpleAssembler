#include "CodeWriter.h"
#include <iostream>
CodeWriter::CodeWriter(std::string filename) {
  fout.open(filename.c_str());
}

void CodeWriter::setFileName(std::string fname){
  filename = fname;
}  

void CodeWriter::writeArithmetic(std::string command) {
  if(command == "add"){
      fout << "@SP\n" << "M=M-1\n" << "A=M\n" << "D=M\n"
	   << "@SP\n" << "M=M-1\n" << "A=M\n" << "M=D+M\n"
	   << "@SP\n" << "M=M+1\n";
  }
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
   fout.close();
 }
