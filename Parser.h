#ifndef PARSER
#define PARSER
#include<fstream>
#include<string>

using namespace std;

enum commandType{
  A_Command, //@Xxx where Xxx is either a symbol or a decimal number
  C_Command, //dest=comp;jump
  L_Command, //(Xxx) where Xxx is a symbol
  Not_A_Command
};

class Parser{
 public:
  /** Constructor: open the input file/stream and gets ready to parse it 
   *
   *  @param input file/stream */
  Parser(std::string fileName);
  
  /** Destructor */
  ~Parser();
 
  /** Wether more commands in the input
   *
   *  @return whether more commands in the input  */ 
  bool hasMoreCommands();

  /** Reads the nexxt command from the input and makes it the current command. 
   *  should be called only if hasMoreCommands() is true  */
  void advance();

  /** Determine the type of the command
   *
   *  @return The type of command */
  commandType commandType();

  /** Symbol or decimal Xxx of the current command @Xxx
   *  should be called only when commandType() is A_Command or L_Command
   *
   *  @return the symbol or decimal Xxx of the current command @Xxx or (Xxx) */
  std::string symbol();

  /** Dest mnemonic, should be called only when commandType() is C-Command
   *
   *  @return the dest mnemonic in the current C-command(8 possibilities) */
  std::string dest();

  /** Comp mnemonic, should be called only when commmandType() is C-Command
   * 
   *  @return the comp mnemonic in the current C-command(28 possibilities) */
  std::string comp();

  /** Jump mnemonic, should be called only when commandType() is C_Command
   *
   *  @return the jump mnemonic in the current C-command(8 possibilities) */
  std::string jump();

  std::string getCurrentCommand();
 private:
  string clearCommand(string command);
  std::string myFileName;
  std::ifstream fin;
  std::string currentCommand;
  
};

#endif
