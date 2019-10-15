
#include "SyntaxChecker.h"
#include <iostream>
#include <fstream>
using namespace std;
SyntaxChecker::SyntaxChecker(){

}
SyntaxChecker::~SyntaxChecker(){

}
void SyntaxChecker::createStack(){
  //Calls the template GenStack class with type char
  typedef GenStack<char> CharStack;
  string line;
  int width=0;
  cout<<"Enter file name: "<<endl;
  string filename;
  cin>>filename;
  char character;
  char poppedChar;
  int location=0;
  int BraceCounter=0;
  int closeBraceCounter=0;
  int openParenthesis=0;
  int closeParenthesis=0;
  int openBracket=0;
  int closeBracket=0;
  //Creates a stack with size of 1 which can later be made bigger
  CharStack stack(1);
  int i=0;
  int size=1;
  int k=0;
  bool isComment=false;
  //Reads through the file of choice adding delimiters to a stack
  ifstream readfile2 (filename);
  if(readfile2.is_open()){

    while(getline(readfile2, line)){

      width=line.length();
      //Checks to see if it should ignore a line if it is a comment
      if(line[0]=='/'&&line[1]=='*'){
        isComment=true;
      }
      if(line[width-1]=='/'&&line[width-2]=='*'){
        isComment=false;
      }

      if(line[0]!='/'||line[1]!='/'){

        if(!isComment){

        for(int i=0; i<width; i++){

        character=line[i];

        if(character=='{'||character=='}'||character=='('||character==')'||character=='['||character==']'){

          if(stack.isFull()==true){
            //Calls the makeBigger function from GenStack which doubles the size of the stack
            stack.makeBigger();
          }
          //Pushes to the stack
          stack.push(character);
              }
            }
          }
        }
        }

        while (!stack.isEmpty()){
          //Creates a counter of each delimiter to compare later by popping chars off the stack
          poppedChar=(char)stack.pop();
          if(poppedChar=='{'){
            BraceCounter++;
          }

          else if(poppedChar=='}'){
            closeBraceCounter++;
          }

          else if(poppedChar==')'){
            closeParenthesis++;
          }

          else if(poppedChar=='('){
            openParenthesis++;
          }

          else if(poppedChar=='['){
            openBracket++;
          }

          else if(poppedChar==']'){
            closeBracket++;
          }
        }
        //Checks if user used wrong delimiters and meant for them to be the same
        if (openParenthesis>closeParenthesis && BraceCounter<closeBraceCounter){
          cout<<"Found an extra '(' and '}': Did you mean for them to be the same delimiter? "<<endl;
        }
        else if (openParenthesis>closeParenthesis && openBracket<closeBracket){
          cout<<"Found an extra '(' and ']': Did you mean for them to be the same delimiter? "<<endl;
        }
        else if (openParenthesis<closeParenthesis && openBracket>closeBracket){
          cout<<"Found an extra '[' and '}': Did you mean for them to be the same delimiter? "<<endl;
        }
        else if (openParenthesis<closeParenthesis && BraceCounter>closeBraceCounter){
          cout<<"Found an extra '{' and ')': Did you mean for them to be the same delimiter? "<<endl;
        }
        else if (openBracket<closeBracket && BraceCounter>closeBraceCounter){
          cout<<"Found an extra '{' and ']': Did you mean for them to be the same delimiter? "<<endl;
        }
        else if (openBracket>closeBracket && BraceCounter<closeBraceCounter){
          cout<<"Found an extra '[' and '}': Did you mean for them to be the same delimiter? "<<endl;
        }

        //Checks if the user is missing a closing delimiter

        else if(openParenthesis>closeParenthesis){
          cout<<"Reached end of the file: missing ')' "<<endl;
        }

        else if(BraceCounter>closeBraceCounter){
          cout<<"Reached end of the file: missing '}' "<<endl;
        }

        else if(openBracket>closeBracket){
          cout<<"Reached end of the file: missing ']' "<<endl;
        }

        //Finds Location where there should be a opening delimiter before a closing delimiter for the rest of the program
        else if(openParenthesis<closeParenthesis){
          int j=0;
          ifstream readfile3 (filename);
          if(readfile3.is_open()){
           while(getline(readfile3, line)){
          j++;
           width=line.length();
           for(int i=0; i<width; i++){
           character=line[i];
              if(location==0){
                if(character==')'){
                  location=j;
                }
              }
            }
          }
          readfile3.close();
        }
        cout<<"Line: "<<location<<" Expected '(' before ')'"<<endl;
      }
        else if(BraceCounter<closeBraceCounter){
          int j=0;
          ifstream readfile3 (filename);
          if(readfile3.is_open()){
           while(getline(readfile3, line)){
           j++;
           width=line.length();
           for(int i=0; i<width; i++){
           character=line[i];
            if(location==0){
                if(character=='}'){
                  location=j;
                }
              }
            }
          }
          readfile3.close();
        }
        cout<<"Line: "<<location<<" Expected '{' before '}'"<<endl;
      }
      else if(openBracket<closeBracket){
        int j=0;
        ifstream readfile3 (filename);
        if(readfile3.is_open()){
         while(getline(readfile3, line)){
         j++;
         width=line.length();
         for(int i=0; i<width; i++){
         character=line[i];
          if(location==0){
              if(character==']'){
                location=j;
              }
            }
          }
        }
        readfile3.close();
      }
      cout<<"Line: "<<location<<" Expected '[' before ']'"<<endl;
    }
        else{
          cout<<"No Problems Found"<<endl;

        }
      }
      readfile2.close();
    }
