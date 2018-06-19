#include "Parser.h"
#include<iostream>
#include<fstream>
#include<algorithm>
#include<string>
#include<iterator>

Parser::Parser(std::string filename){
  fin.open(filename.c_str());
  if(!fin.is_open()){
    std::cout << "Could not open the file, \n";
  }
}

Parser::~Parser(){
  fin.close();
}

bool Parser::hasMoreCommands(){
  return !fin.eof();
}

void Parser::advance(){
  std::string command;
  getline(fin, command);
  currentCommand = clearCommand(command);
}

cmdType Parser::commandType(){
  std::string cmd(currentCommand);
  cmdType type;
  if(cmd.size() != 0){
    if(cmd == "add" | cmd == "sub" | cmd == "neg" | cmd == "eq" | cmd == "gt"
       | cmd == "lt" | cmd == "and" | cmd == "or" | cmd == "not"){
      type = C_ARITHMETIC;
    }
    else if(cmd.find("push") != std::string::npos){
      type = C_PUSH;
    }
    else if(cmd.find("pop") != std::string::npos){
      type = C_POP;
    }
    else if(cmd.find("label") != std::string::npos){
      type = C_LABEL;
    }
    else if(cmd.find("if") != std::string::npos){
      type = C_IF;
    }
    else if(cmd.find("goto") != std::string::npos){
      type = C_GOTO;
    }
    else if(cmd.find("function") != std::string::npos){
      type = C_FUNCTION;
    }
    else if(cmd.find("return") != std::string::npos){
      type = C_RETURN;
    }
    else if(cmd.find("call") != std::string::npos){
      type = C_CALL;
    }
  }
  return type;
}

std::string Parser::arg1(){
  std::string arg("");
  if(currentCommand.size() != 0){
    if(currentCommand.find("argument") != std::string::npos){
      arg = "argument";
    }
    else if(currentCommand.find("local") != std::string::npos){
      arg = "local";
    }
    else if(currentCommand.find("static") != std::string::npos){
      arg = "static";
    }
    else if(currentCommand.find("constant") != std::string::npos){
      arg = "constant";
    }
    else if(currentCommand.find("this") != std::string::npos){
      arg = "this";
    }
    else if(currentCommand.find("that") != std::string::npos){
      arg = "that";
    }
    else if(currentCommand.find("pointer") != std::string::npos){
      arg = "pointer";
    }
    else if(currentCommand.find("temp") != std::string::npos){
      arg = "temp";
    }
  }
  return arg;
}

int Parser::arg2(){
  std::string arg(currentCommand.substr(currentCommand.find(arg1()) + arg1().length()));
  return atoi(arg.c_str());
}

std::string Parser::clearCommand(std::string command){
  //remove the space
  command.erase(std::remove(command.begin(), command.end(), ' '),
  		command.end());
  //should get rid of \r if file comes from a windows machine
    command.erase(std::remove(command.begin(), command.end(), '\r'),
		  command.end());
  //reomve the comment
  if(command.find("//") != std::string::npos){
    command = command.substr(0, command.find("//"));
  }
  return command;
}

std::string Parser::getCmd() {
	return currentCommand;
}
