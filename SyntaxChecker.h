#include <iostream>
#include "GenStack.h"
using namespace std;
class SyntaxChecker{
public:
  SyntaxChecker();
  ~SyntaxChecker();//desructor
  /*Calls createStack Function which is in the SyntaxChecker class. It
  In the createStack Function the GenStack class is called and then it reads
  through the file pushing all delimiters to the stack. Then each delimiter is
  popped from the stack and counted to see if the amount of delimiers is equal.
  It checks the location of the error if neccessary(when missing opener)
  */
  void createStack();
};
