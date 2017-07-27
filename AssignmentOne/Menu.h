#include "Text.h"
#ifndef MENU_H
#define MENU_H

class Menu
{

private:
  Text *option_list;
  Text arrow;
  int count;
  int max_size_list;
  Text top_prompt;
  Text bottom_prompt;
  Text top_text;
  Text bottom_text;
  void double_capacity();
  void copyTextArray(Text*, Text*);//copy one text into another
  void appendOptions(Text&) const; //function for appending option list to Text
  void copyPrompts(const Menu&);   //copy messages and prompts from another menu

public:
  Menu();
  virtual ~Menu();
  Menu(Menu&);
  Menu& operator=(const Menu&); //overloaded = operator
  void insert(int, Text&);
  void insert(int, const char*);
  void push_back(const char*);
  void push_back(const Text&);
  Text remove(int);
  int size() const;
  int capacity() const;
  void pop_back();
  Text get(int);          //returns option text
  Text toString() const;  //return text menu reprensentation
  int read_option_number();
  void set_top_prompt(const Text&);
  void set_bottom_prompt(const Text&);
  void set_top_message(const Text&);
  void set_bottom_message(const Text&);
  void clear_top_prompt();
  void clear_bottom_prompt();
  void clear_top_message();
  void clear_bottom_message();
  bool isEmpty() const;
  friend std::ostream& operator<<(std::ostream&, const Menu&); //overloaded << op

};

#endif /* end of include guard: MENU_H */
