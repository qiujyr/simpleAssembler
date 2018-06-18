#include "CodeWriter.h"

CodeWriter::CodeWriter(std::string filename) {
	fout.open(filename.c_str());
}

void CodeWriter::setFileName(std::string fname) :filename(fname) {}

void CodeWriter::writeArithmetic(std::string command) {
	switch (command) {
	case "add":
		fout << "@SP\n" << "A=M\n" << "D=M\n"
			<< "@SP\n" << "M=M-1\n" << "A=M" << "D=D+M";
	}
}

void CodeWriter::writePushPop(cmdType type, std::string segment, int index) {
	if (type == C_POP) {
	}
	else { //type is C_PUSH
		if (segment == constant) {
			fout << "@" << index << "\n" << "D=A\n" << "@SP\n"
				<< "A=M\n" << "M=D\n";
		}

		//increment sp by 1
		fout << "@SP\n" << "M=M+1\n";
	}
}

void CodeWriter::close() {
	fout.close();
}