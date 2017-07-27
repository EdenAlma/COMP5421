#include<fstream>
#include <iostream>   //include statements for i/o, etc...
#include<iterator>
#include "Led.h"

using std::ifstream;
using std::ofstream;
using std::cout;
using std::cin;
using std::string;   //using
using std::list;
using std::getline;


/*
constructor which takes in filename string
and creates the appropraite Led object
*/
Led::Led(string fileName)
{

  string input;
  this->fileName = fileName;  //set filename in this object --> used later
  ifstream fin(fileName.c_str());  //attempt to open file

  if(fileName.length() == 0)  //if no file specified
  {
    cout << "No file name specified.\n";
    fin.close();
  }
  else if(fin.fail())   //if file not found
  {
    cout << "File was not found ("<< fileName << ")\n";
    fin.close();
  }
  else
  {
    cout << fileName << " ";    //if file was found

    while(!fin.eof()) //input while file contains lines
    {
      getline (fin, input);   //extract lines from file
      buffer.push_back(input);
    }
    fin.close();    //close file stream
  }
}

/*
function which is run until the user has finished editing file
*/
void Led::run()
{

  Command cmd;    //command object which will be used continously
  cmd.setDollar(buffer.size()); //set line number for last line
  cmd.setDot(buffer.size());    //set dot as last line
  string input = "";

  //if file contains lines --> print number of lines
  if(this->fileName.length() > 0 && buffer.size() != 0)
  {cout << "contains " << buffer.size() << " lines" << '\n';}
  else cout << "Empty file ==> please enter a, i or q\n";
  cout << "entering command mode.\n:";

  while(true)   //loops until user quits
  {
    getline (cin, input);  //command input

  try{
    cmd.parseCommand(input); //parse and set command
  }catch(...){       //catch all errors which can happen
      cout << "(try-catch) invalid Command, please try again... \n:";
      continue;    //prompt user for command once again
  }


    if(input == "q")break;  //user quits

    if(!cmd.isValid())    //if command is invalid --> prompt user
    {
      cout << "(not valid) invalid Command, please try again... \n:";
      continue;
    }

    execute(cmd); //execute command
    cmd.resetCommand();
    cout<<":";    //command mode symbol
  }

}

/*
method which executes commands according to command letter
which are executed using methods for each command
*/
void Led::execute(Command& cmd)
{
  char test = cmd.getCommand();

  switch(test)
  {
    case 'a':
    appendLine(cmd);
    break;
    case 'i':
    insertLine(cmd);
    break;
    case 'r':
    removeLine(cmd);
    break;
    case 'p':
    printLine(cmd);
    break;
    case 'n':
    numPrint(cmd);    //basic switch statement
    break;
    case 'c':
    changeLine(cmd);
    break;
    case 'u':
    upLine(cmd);
    break;
    case 'd':
    downLine(cmd);
    break;
    case 'w':
    writeLine();
    break;
    case '=':
    lineNum(cmd);
    break;
  }

}

/*
method which is used to append line to text
*/
void Led::appendLine(Command& cmd)
{
  string input;  //string for input
  //iterator to begining of list
  list<string>::iterator index = buffer.begin();
  int startIndex = cmd.getFrst();
  advance(index, cmd.getFrst());  //move iterator forward
  while(true)
  {
    getline (cin, input);
    if(input == ".")break;     //exit condition
    buffer.insert(index, input);  //input lines at specified location
    ++startIndex;   //increment iterator
  }

  
  if(buffer.size() != 0)
  cmd.setDot(startIndex);
  cmd.setDollar(buffer.size());  //setting dollar and doe symbols
  cout << "entering command mode.\n"; //exiting append mode
}

/*
same as method above with a slight modificatio to
where the line gets inserted with respect to the line number
*/
void Led::insertLine(Command& cmd)
{
  string input;
  list<string>::iterator index = buffer.begin();
  int startIndex = cmd.getFrst()-1;

  while(true)
  {
    getline (cin, input);
    if(input == ".")break;
    buffer.insert(index, input);
    ++startIndex;
  }

  if(buffer.size() != 0)
  cmd.setDot(startIndex);
  cmd.setDollar(buffer.size());
  cout << "entering command mode.\n";
}


/*
method used to remove lines from the buffer
*/
void Led::removeLine(Command& cmd)
{
  //if only one line is to be removed
  if(cmd.getFrst() == cmd.getScnd())  //1,1 2,2....
  {
    list<string>::iterator index = buffer.begin(); //iterator for beginning
    advance(index, (cmd.getFrst()-1));    //move iterator forward
    buffer.erase(index);                //erase line
    index = buffer.begin();
    advance(index, (cmd.getFrst()-1));
    cmd.setDollar((cmd.getDollar())-1);
    if(buffer.end() != index)  //checking where to set "dot" to
    cmd.setDot(cmd.getFrst());  //infront
    else
    cmd.setDot(cmd.getFrst()-1);    //behinf
  }
  else  //when a range of number is being deleted
  {
    list<string>::iterator index = buffer.begin();  //similar to above
    advance(index, (cmd.getFrst()-1));

    for(int first = cmd.getFrst(); first <= cmd.getScnd(); ++first)
    {
      buffer.erase(index);
      index = buffer.begin();  //for loop removing lines
      advance(index, (cmd.getFrst()-1));
    }

    cmd.setDollar((cmd.getDollar())-((cmd.getScnd()-cmd.getFrst())+1));
    index = buffer.begin();             //resetting $ and .
    advance(index, (cmd.getFrst()-1));

    if(buffer.end() != index)
    cmd.setDot(cmd.getFrst());
    else
    cmd.setDot(cmd.getFrst()-1);
  }
}

/*
method which prints line using a for loop
and an iterator...
*/
void Led::printLine(Command& cmd)
{
  if(cmd.getDot() == 0 || cmd.getDollar() == 0)return;
  list<string>::iterator index = buffer.begin();
  int first = cmd.getFrst();
  int second = cmd.getScnd();

  if(first == second)   //print single line
  {
    advance(index, first-1);
    cout << *index << '\n';  //print lines + endl
    cmd.setDot(first);
  }
  else   //print multiple lines
  {
    advance(index, first-1);

    for(first; first <= second; ++first)
    {
      cout << *index << '\n';
      ++index;
    }
    cmd.setDot(second);   //resetting "dot"
  }

}

/*
same as above but with numbering on the printed lines
*/
void Led::numPrint(Command& cmd)
{
  if(cmd.getDot() == 0 || cmd.getDollar() == 0)return;
  list<string>::iterator index = buffer.begin();
  int first = cmd.getFrst();
  int second = cmd.getScnd();

  if(first == second)   //printing single line
  {
    advance(index, first-1);
    cout << first << "\t" << *index << '\n';
    cmd.setDot(first);
  }
  else      //print multiple lines
  {
    advance(index, first-1);

    for(first; first <= second; ++first)
    {
      cout << first << "\t" << *index << '\n';
      ++index;
    }
    cmd.setDot(second);
  }
}


/*
changing lines in the buffer using replace method
*/
void Led::changeLine(Command& cmd)
{

  string in;  //what the user wants to replace with
  string out; //what user wants to replace
  cout << "\nChange what? -->";
  getline (cin, in);            //prompt user for change details
  cout << "To what? -->";
  getline (cin, out);  //parse
  cout << "\n";

  list<string>::iterator index = buffer.begin();
  int first = cmd.getFrst();
  int second = cmd.getScnd();

  if(first == second)  //if only one line is being updated
  {
    advance(index, first-1);
    replaceString(*index, in, out);
    cmd.setDot(first);
  }
  else   //if multiple lines are being updated
  {
    advance(index, first-1);

    for(first; first <= second; ++first)
    {
      replaceString(*index, in, out);  //method defined below
      ++index;
    }
    cmd.setDot(second);
  }
}

//moving up a line
void Led::upLine(Command& cmd)
{
  cmd.setDot(cmd.getDot()-(cmd.getFrst()));
}

//moving down a line
void Led::downLine(Command& cmd)
{
  cmd.setDot(cmd.getDot()+(cmd.getFrst()));
}

/*
write buffer content into specified file
*/
void Led::writeLine()
{
  string temp;
  ofstream fout;

  if(fileName.length() == 0)  //fiel name not choser
  {
    cout<< "\nEnter new file name:";
    getline(cin, temp);   //prompt user and take input
    fout.open(temp.c_str());
  }
  else
  {
    fout.open(fileName.c_str());  //open using pre-defined filename
  }

  list<string>::iterator start = buffer.begin();
  list<string>::iterator end = buffer.end();  //iterators for file output

  for(start; start != end; ++start)
  {
    fout << *start;          //for loop...
    if(start != buffer.end())
    fout << '\n';
  }

  fout.close();   //close output file
}

// "=" command
void Led::lineNum(Command& cmd)
{
  cout << cmd.getDot();  //return current line number
}


//method used to reaplce any substring with any string specified by user
void Led::replaceString(string& subject, const string& search, const string& replace)
{
    int pos = 0;
    while ((pos = subject.find(search, pos)) != string::npos)
    {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
}
