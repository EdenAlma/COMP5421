#include "Text.h"
#include<iostream>

Text::Text():text((char *)""){} //default constructor

Text::~Text(){if(strLen(text)!=0) delete [] text;} //destructor

int Text::strLen(const char* input) const //return length
{
  int x = 0;
  while(true)
  {
    if(input[x] == '\0')break; //find null character
    x++;  //increment char count
  }
  return x;
}

/*size of strings validated prior to use*/
void Text::strCopy(const char* in, char* out) //copies one string into another
{
  int x = 0; //index for copying
  while(true)
  {
    if(in[x] == '\0')break;  //find ending of input string
    out[x] = in[x];
    x++;
  }
  out[x] = '\0';  //set terminating character
}

Text::Text(const Text& t)  //copy constructor
{
  text = new char[strLen(t.text)+1];
  strCopy(t.text , text);
}

Text::Text(const char * t)   //constructor intialized with "string"
{
 text = new char[strLen(t)+1];  //intialize text
 strCopy(t , text);  //copy string into text
}

void Text::set(const char * t)
{
  if(strLen(text)!=0) delete [] text; //if string is non empty --> delete
  text = new char[strLen(t)+1];  //new array
  strCopy(t , text);
}

void Text::set(const Text& t)  //setting text with another texts
{
  if(strLen(text)!=0) delete [] text;
  text = new char[strLen(t.text)+1];
  strCopy(t.text , text);
}

Text& Text::operator=(const Text& t) //overloading = operator
{
  if(&t == this)return *this;
  if(strLen(text)!=0) delete [] text;
  text = new char[strLen(t.text)+1];
  strCopy(t.text , text);
  return *this;
}

void Text::append(const char * t)  //appending "string" onto text
{
  int newLength = strLen(t) + strLen(text) + 1;
  char* temp = new char[newLength];
  int i = 0;

  for(i = 0; i < strLen(text); i++)
  {
    temp[i] = text[i];      //copy contents from string 1
  }

  int x = 0;
  for(i = strLen(text); i < newLength; i++)
  {
    temp[i] = t[x];       //copy contents from string 2
    x++;
  }

  if(strLen(text)!=0) delete [] text;   //delete previous text
  text = temp;      //swap pointers
}

void Text::append(const Text& t)   //same as above just with Text param
{
  int newLength = strLen(t.text) + strLen(text) + 1;
  char* temp = new char[newLength];
  int i = 0;

  for(i = 0; i < strLen(text); i++)
  {
    temp[i] = text[i];
  }

  int x = 0;
  for(i = strLen(text); i < newLength; i++)
  {
    temp[i] = t.text[x];
    x++;
  }

  if(strLen(text)!=0) delete [] text;
  text = temp;
}

int Text::length() const{ return strLen(text);}

bool Text::isEmpty() const{return (strLen(text)==0);}

std::ostream& operator<<(std::ostream& o, const Text& t)   //overloading << operator
{
  std::cout << t.text;
  return o;
}
