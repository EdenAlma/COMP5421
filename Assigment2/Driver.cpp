#include<iostream>  //for cout
#include"Led.h"   //led

int main(int argc, const char *argv[])
{

std::string inp("");  //input string

if(argc > 2)          //more than one arguemnt
{
  std::cout << "\ntoo many arguments - all discarded";
  return 1;           //error
}
else if(argc == 2)    //file input from command line
{
  inp = argv[1];      //set file name
}

Led led(inp);        //led constructor
led.run();           //run Led
std::cout << "*****Thanks you for using LED*****\n";   //goodbye message

return 0;  //exit
}
