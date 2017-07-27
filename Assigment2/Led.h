#include<list>  //for buffer
#include<string>  //for string
#include "Command.h" //command

#ifndef LED_H
#define LED_H

class Led
{

public:
  Led(std::string); //constructor
  void run();       //run method
  void execute(Command&);  //execute mwthod used within run

private:
  std::string fileName;  //name of the input file
  std::list<std::string> buffer;  //list "buffer"
  void appendLine(Command&);
  void insertLine(Command&);
  void removeLine(Command&);
  void printLine(Command&);         //methods for each command
  void numPrint(Command&);
  void changeLine(Command&);
  void upLine(Command&);
  void downLine(Command&);
  void writeLine();
  void lineNum(Command&);
  void replaceString(std::string&, const std::string&, const std::string&);
  //method for substrs within a string

};

#endif
