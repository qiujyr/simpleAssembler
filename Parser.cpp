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
  std::string command;
  getline(fin, command);
  currentCommand = clearCommand(command);
}

cmdType Parser::commandType(){
  if(currentCommand[0] == '@'){
    //A-command
    return A_Command;
  } 
  else if(currentCommand[0] ==  '('){
    //L-command
    return L_Command;
  } 
  else if(currentCommand.find("=") != string::npos || currentCommand.find(";") != string::npos){
      //C-command
    return C_Command;
  }
  return Not_A_Command;
}

std::string Parser::symbol(){
  if(commandType() == A_Command){
    return currentCommand.substr(1);
  }
  else if(commandType() == L_Command){
    return currentCommand.substr(1, currentCommand.length() - 2);
  }
}

std::string Parser::dest(){ 
  if(currentCommand.find("=") == string::npos) return "null";
  else return currentCommand.substr(0,currentCommand.find("="));
}

std::string Parser::comp(){
  int start = 0;
  int end = currentCommand.length();
  if(currentCommand.find("=") != string::npos){
    start = currentCommand.find("=") + 1;
  }
  if(currentCommand.find(";") != string::npos){
    end = currentCommand.find(";");
  }
  return currentCommand.substr(start, end - start);
}

std::string Parser::jump(){
  if(currentCommand.find(";") == string::npos) return "null";
  else return currentCommand.substr(currentCommand.find(";") + 1, 3);
}

string Parser::clearCommand(string command){
  command.erase(remove(command.begin(),command.end(),' '),command.end());
  command.erase(remove(command.begin(),command.end(),'\n'),command.end());
  if(command.find("//") != string::npos){
    return command.substr(0,command.find("//"));
  } else{
    return command.substr(0,command.length() - 1);
  }
}


