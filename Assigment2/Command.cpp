#include "Command.h"
#include <algorithm>
#include <iostream>

using std::string;
using std::remove;
using std::stoi;
using std::cout;


Command::Command()  //default constructor
{
  command = '?';
  frst = 0;
  scnd = 0;       //all numerical values intialized to zero
  dollar = 0;
  dot = 0;
  valid = false;  //intiallized as false --> invalid command
}

/*
method which pareses commmand from user and set line numbers
and commmands for all the scenarios
*/
void Command::parseCommand(string& cmdText)
{
  string in = cmdText;  //renaming command text
  in.erase(remove(in.begin(), in.end(), ' '), in.end()); //remove white space

  if(in.length() == 0)    //blank command entered  -- "ENTER"
  {
    command = 'd';
    frst = 1;       //command set to 1d
    setCommand();
    return;
  }

  if(in.length() == 1)    //single character command
  {
    if(containsCommand(in))  //single command
    {
      command = in[0];
      setCommand();       //command set to command character
      return;
    }
    else              //single number or symbol
    {
      command = 'p';
      if(in[0] == '$'){frst = scnd = dollar;}
      else if(in[0] == '.'){frst = scnd = dot;}    //print command num,. or $
      else {frst = scnd = stoi(in, nullptr, 10);}   //parse int
      setCommand();
      return;
    }
  }

  if(in.length() > 1)     //command greater than one character
  {

    if(containsCommand(in))     //contains command?
    {

      command = in[in.length()-1];    //set command
      in = in.substr(0, in.length()-1);   //truncate input string 1,2r --> 1,2

      if(containsComma(in))
      {
        frst = leftOfComma(in);    //exctract line numbers
        scnd = rightOfComma(in);
        setCommand();
        return;
      }
      else
      {
        if(in[0] == '$'){frst = dollar;}
        else if(in[0] == '.'){frst = dot;}    //print command num,. or $
        else frst = scnd = stoi(in, nullptr, 10);
        setCommand();
        return;
      }
    }
    else   //no command was specified
    {
      command = 'p';

      if(containsComma(in))
      {
        frst = leftOfComma(in);   //split numbers L and R
        scnd = rightOfComma(in);
        setCommand();
        return;
      }
      else
      {     //only a single number was enetered as command
        frst = scnd = stoi(in, nullptr, 10);
        setCommand();
        return;
      }
    }
  }
}

char Command::getCommand(){return command;}

void Command::setDollar(int x){dollar = x;}

void Command::setDot(int x){dot = x;}

int Command::getDollar(){return dollar;}    //GETTERS

int Command::getDot(){return dot;}          //AND

int Command::getFrst(){return frst;}        //SETTERS

int Command::getScnd(){return scnd;}

bool Command::isValid(){return valid;}

/*
method which validates and re-sets command logic
incase of scenarios where certain numbers are left
out of the commnad
*/
void Command::setCommand()
{

  char cmd = command;  //command character p,r,n etc...

  switch (cmd) {

    case 'a':  //switch cases for a and i
    case 'i':
    if(frst != 0)  //if a line number is 0 --> no number entered
    {
      valid = true;
      if(frst > dollar || frst < 1)  //validation
      {valid = false;}
    }
    else if(scnd != 0)
    {
      frst = scnd;
      valid = true;
      if(frst > dollar || frst < 1)  //validation
      {valid = false;}
    }
    else
    {
      frst = dot = scnd;     //if line numbers were not entered
      valid = true;
    }
    break;

    case 'r':
    case 'p':
    case 'n':   //r, p, n or c
    case 'c':

    if(frst != 0 && scnd != 0)  //both line numbers entered
    {
      valid = true;
      //validation of line numbers
      if(frst < 0 || scnd < 0 || frst > dollar || scnd > dollar || scnd < frst)
      {
        valid = false;
      }
    }
    else if(frst == 0 && scnd != 0)   //only right side entered
    {
      valid = true;
      frst = dot;
      //validation of line numbers
      if(frst < 0 || scnd < 0 || frst > dollar || scnd > dollar || scnd < frst)
      {
        valid = false;
      }
    }
    else if(frst != 0 && scnd == 0)   //only left side entered
    {
      valid = true;
      scnd = frst;
      //validation of line numbers
      if(frst < 0 || scnd < 0 || frst > dollar || scnd > dollar || scnd < frst)
      {
        valid = false;
      }
    }
    else    //both line numberes are not entered
    {
      valid = true;
      frst = scnd = dot;
      //validation of line numbers
      if(frst < 0 || scnd < 0 || frst > dollar || scnd > dollar || scnd < frst)
      {
        valid = false;
      }
    }

    break;

    case 'u':
    case 'd':   //case for u and d

    if(frst != 0)
    {
      valid = true;
      if(frst > dollar || frst < 1)  //valid?
      {valid = false;}
    }
    else if(scnd != 0)
    {
      frst = scnd;
      valid = true;
      if(frst > dollar || frst < 1) //valid?
      {valid = false;}
    }
    else
    {
      frst = scnd = 1;
      valid = true;
    }

    if(getCommand() == 'd')   //validation for moving out of range
    {
      if(getFrst() + getDot() > getDollar()){valid = false;}
    }
    else if(getCommand() == 'u') //validation for moving out of range
    {
      if(getDot() - getFrst() < 1){valid = false;}
    }

    break;

    case 'w':
    case '=':    //w and = commands --> no validation
    valid = true;
    break;

    default:      //if a invalid command was entered
    valid = false;
    break;
  }
}

/*
extract int from left of comma
*/
int Command::leftOfComma(string& input)
{
  int comma = input.find_first_of(",");  //get postion of comma
  string left = input.substr(0, comma); //look to left of comma

  if(left == "$")return dollar;  //if dollar
  else if(left == ".") return dot; //if dot
  else if(left.length() == 0)return 0;  //if blank
  else
  {
    return stoi(left, nullptr, 10);  //return int value (throws)
  }
}

/*
extract int from right of comma
*/
int Command::rightOfComma(string& input)
{
  int comma = input.find_first_of(",");
  string right = input.substr(comma+1);

  if(right == "$")return dollar;
  else if(right == ".") return dot;
  else if(right.length() == 0)return 0;
  else
  {
    return stoi(right, nullptr, 10);
  }
}

//boolean to check if string contains comma
bool Command::containsComma(string& input)
{
  return (input.find(',') != string::npos);
}

//boolean to see if command contains lower case char
bool Command::containsCommand(string& input)
{
  char last = input[input.length()-1];
  return ((last >= 'a' && last <= 'z')||(last == '='));
}

void Command::resetCommand()
{
  frst = scnd = 0;
  valid = false;
}
