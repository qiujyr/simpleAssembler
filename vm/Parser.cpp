#include "Parser.h"
#include<iostream>
#include<fstream>
#include<string>
#include "algorithm"

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
  if(cmd.find(' ') != std::npos){
    cmd = cmd.substr(0, cmd.find(' '));
  }
  switch(cmd){
  case "add":
  case "sub":
  case "neg":
  case "eq":
  case "gt":
  case "lt":
  case "and":
  case "or":
  case "not":
    return C_ARITHMETIC;
  case "push":
    return C_PUSH;
  case "pop":
    return C_POP;
  case "label":
    return C_LABEL;
  case "goto":
    return C_GOTO;
  case "if-goto":
    return C_IF;
  case "function":
    return C_FUNCTION;
  case "return":
    return C_RETURN;
  case "call":
    return C_CALL;
  }
}

std::string Parser::arg1(){
  std::string arg(currentCommand);
  if(currentCommand.commandType() == C_ARITHMETIC){
    arg = arg.substr(0, arg.find(' '));
  }
  else{
    //remove the cmd
    arg = arg.substr(arg.find(' ') + 1);
    if(arg.find(' ') != std::npos){ //check if it has a second arg
      arg = arg.substr(0, arg.find(' '));
    }
  }
  return arg;
}

int Parser::arg1(){
  std::string arg(currentCommand);
  //remove cmd
  arg = arg.substr(arg.find(' ') + 1);
  //remove the first arg
  arg = arg.substr(arg.find(' ') + 1);
  return atoi(arg.c_str());
}

std::string Parser::clearCommand(std::string command){
  //remove the space
  command.erase(std::remove(command.begin(), command.end(), ' '),
		comamnd.end());
  //should get rid of \r if file comes from a windows machine
    command.erase(std::remove(command.begin(), command.end(), '\r'),
		  command.end());
  //reomve the comment
  if(command.find("//") != std::npos){
    command = command.substr(0, command.find(' '));
  }
  return command;
}

std::string Parser::getCmd() {
	return currentCommand;
}