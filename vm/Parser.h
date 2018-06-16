#ifndef _PARSER_H_
#define _PARSER_H_
#include<fstream>
#include<string>

enum cmdType{
  C_ARITHMETIC,
  C_PUSH,
  C_POP,
  C_LABEL,
  C_GOTO,
  C_IF,
  C_FUNCTION,
  C_RETURN,
  C_CALL
};

class Parser{
 public:
  /** constructor, open the file and ready to parse the file
   *
   * @param filename, file to be parsed */
  Parser(std::string filename);

  /** destructor, close the file after parsing */
  ~Parser(); //destroctor
  bool hasMoreCommands();

  /** reads the next cmd and make it the current cmd after 
   *  clear the space and comment */
  void advance();

  /** return the type of the cmd */
  cmdType commandType();

  /** return the first arg, return the cmd in case of C_ARITHMETIC
   *
   * @pre should not be called if the current cmd is C_RETURN */
  std::string arg1(); 

  /** return the second arg
   *
   * @pre should be called only if the current cmd is C_PUSH, C_POP,
   *      C_FUNCTION, C_CALL */
  int arg2();

 private:
  std::string clearCommand(std::string command);
  std::string currentCommand;
  std::ifstream fin;
};

#endif
