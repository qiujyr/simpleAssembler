#include<iostream>
#include "Parser.h"
#include<algorithm>
using namespace std;

Parser::Parser(std::string filename)
  : myFileName(filename){
  fin.open(myFileName.c_str());
  if(!fin.is_open()){
    std::cout<< "Could not open the source file. \n";
  }
}

Parser::~Parser(){
  fin.close();
}

bool Parser::hasMoreCommands(){
  return !fin.eof();
}

void Parser::advance(){
  string command;
  getline(fin, command);
  currentCommand = clearCommand(command);
}

int Parser::commandType(){
  if(currentCommand[0] == '@'){
    //A-command
    return 0;
  } 
  else if(currentCommand[0] ==  '('){
    //L-command
    return 2;
  } 
  else if(currentCommand.find("=") != string::npos || currentCommand.find(";") != string::npos){
      //C-command
    return 1;
  }
  return 100;
}

std::string Parser::symbol(){
  if(commandType() == 0) return currentCommand.substr(1,currentCommand.size()-2);
  else return currentCommand.substr(1, currentCommand.length() - 2);
}

std::string Parser::dest(){ 
  if(currentCommand.find("=") == string::npos) return "null";
  else return currentCommand.substr(0,currentCommand.find("="));
}

std::string Parser::comp(){
  int start = 0;
  int end = currentCommand.length();
  if(currentCommand.find("=") != string::npos) start = currentCommand.find("=") + 1;
  if(currentCommand.find(";") != string::npos) end = currentCommand.find(";");
  return currentCommand.substr(start, end - start - 1);
}

std::string Parser::jump(){
  if(currentCommand.find(";") == string::npos) return "null";
  else return currentCommand.substr(currentCommand.find(";") + 1);
}

string Parser::clearCommand(string command){
  command.erase(remove(command.begin(),command.end(),' '),command.end());
  if(command.find("//") != string::npos){
    return command.substr(0,command.find("//"));
  } else{
    return command;
  }
}


