#include "Parser.h"
#include "CodeWriter.h"

int main(int argc, char* argv[]) {
	std::string filename = argv[1];
	Parser parser(filename);
	CodeWriter codeWriter(filename);
	std::string finalCode;
	while (parser->hasMoreCommands()) {
		parser.advance();
		switch (parser.commandType()) {
		case C_ARITHMETIC:
			finalCode += codeWriter.writeArithmetic(parser.getCmd());
		case C_PUSH:
			finalCode += codeWriter.writePushPop(C_PUSH, parser.arg1(), parser.arg2());
		case C_POP:
			finalCode += codeWriter.writePushPop(C_POP, parser.arg1(), parser.arg2());
		}
	}
}