#ifndef _CODE_WRITER_
#define _CODE_WRITER_

#include "Parser.h"
#include <fstream>
#include <string>
class CodeWriter{
 public:
  /** 
   *  constructor, opens the output file/stream
   *  and gets ready to write into it
   *
   *  @param filename, the file to be written 
   */
  CodeWriter(std::string filename);

  /** 
   *  informs the code writer that the translation of
   *  a new VM file is started
   *
   *  @praram filename, the vm file to be translated
   */
  void setFileName(std::string fname);

  /** 
   *  writes the assembly code that is the translation of 
   *  the given arithmetic command
   *
   *  @param command, the command to be translated */
  void writeArithmetic(std::string command);

  /** 
   *  writes the assembly code that is the translation
   *  of the given command, where command is either C_PUSH, or C_POP
   *
   *  @param stype, C_PUSH or C_POP
   *
   *  @param segment, segment of the command
   *
   *  @param index, index of the command 
   */
  void writePushPop(cmdType type, std::string segment, int index);

  /**
   * closes the output file
   */
  void close();

 private:
  std::ofstream fout;
  std::string filename;
};

#endif
