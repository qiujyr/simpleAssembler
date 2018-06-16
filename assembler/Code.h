#ifndef CODE
#define CODE
#include<string>
#include<map>

using namespace std;

class Code{
 public:
  /** Default constructor */
  Code();

  /** Default destructor */
  ~Code();

  /** Dest code
   *
   *  @param dest mnemonic string
   *
   *  @return the binary code of the dest mnemonic */
  std::string dest(std::string mnemonic);

  /** Comp code
   *
   *  @param comp mnemonic string
   *
   *  @return the binary code of the comp mnemonic */
  std::string comp(std::string mnemonic);

  /** Jump code
   *
   *  @param jump mnemonic string
   *  
   *  @return the binary code of the jump mnemonic */
  std::string jump(std::string mnemonic);

 private:
  map<std::string,std::string> comps;
  map<std::string,std::string> jumps;
  map<std::string,std::string> dests;
};


#endif
