#include<string>
#ifndef COMMAND_H
#define COMMAND_H


class Command
{

public:
  Command();  //deafualt constructor
  void parseCommand(std::string&); //sets command char and line numbers frst + scnd
  char getCommand(); //get command character
  void setDollar(int); //set new value from Led
  void setDot(int); //set new value from Led
  int getDollar(); //get last line
  int getDot(); //get current line
  int getFrst();  //get first line number
  int getScnd(); //get second line number
  bool isValid(); //boolean to check validity
  void resetCommand();

private:
  char command; //command character
  int dollar; //last line
  int dot;  //current line
  int frst; //first line number
  int scnd; //second line number
  bool valid; //boolean flag
  void setCommand();  //check and set validity
  int leftOfComma(std::string&);  //get int from left
  int rightOfComma(std::string&); //get int from right
  bool containsComma(std::string&); //checks if comma exists
  bool containsCommand(std::string&); //check if commad exists

};

#endif
