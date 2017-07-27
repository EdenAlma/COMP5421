#include "Menu.h"
#include "Text.h"
#include<iostream>

using std::cout;
using std::cin;

Menu::Menu()  //default constructor
{
  arrow.set("?->");
  option_list = new Text[1];   //intialize Text array
  count = 0;                  //count
  max_size_list = 1;
}

Menu::~Menu(){delete [] option_list;}   //destructor

void Menu::double_capacity()
{
  max_size_list *= 2;  //multiply list size
  Text* temp = new Text[max_size_list];   //re-initalize
  copyTextArray(option_list, temp);       //recopy array into bigger array
  delete [] option_list;                  //deallocate old array
  option_list = temp;                     //swap pointer
}


Menu::Menu(Menu& m)   //copy constructor
{
  option_list = new Text[1];
  arrow.set("?->");
  count = 0;
  max_size_list = 1;
  copyPrompts(m);         //match prompts
  while(max_size_list != m.max_size_list){double_capacity();} //match sizes
  count = m.count;              //match counts
  copyTextArray(m.option_list, option_list);      //copy arrays
}

Menu& Menu::operator=(const Menu& m)   //overloaded = operator
{
  if(&m == this){return *this;}
  copyPrompts(m);
  while(max_size_list < m.max_size_list){double_capacity();} //give enough size
  count = m.count;
  copyTextArray(m.option_list, option_list);      //copy arrays
  return *this;
}

std::ostream& operator<<(std::ostream& o, const Menu& m) //overloaded << operator
{
  cout << m.toString();  //display menu
  return o;              //return iostream
}

void Menu::insert(int i, Text& t)  //insertion function
{
if(i > count || i < 0)
{cout<<"Invalid selection in void Menu::insert(int i, Text& t)"; return;}
//attempt to insert in invalid index
while(count+1 > max_size_list){double_capacity();} //make sure space is available
int k = count;
for(k; k>=i; k--){option_list[k+1] = option_list[k];}  //shift options
option_list[i].set(t);    //set option at index
count++;       //increment count variable
}


void Menu::insert(int i, const char* t)
{
if(i > count || i < 0)
{cout<<"Invalid selection in void Menu::insert(int i, const char* t)"; return;}
Text temp(t);     //create text object
insert(i,temp);  //using other insert method
}


void Menu::push_back(const char* t)    //add options to menu
{
  while(count+1 > max_size_list){double_capacity();} //make enough room
  option_list[count].set(t);  //set text object
  count++;
}

void Menu::push_back(const Text& t)   //add options to menu (same as above)
{
  while(count+1 > max_size_list){double_capacity();}
  option_list[count].set(t);
  count++;
}

Text Menu::remove(int i)
{
  Text dummy;   //dummy object to be returned incase of invalid selection
  if(i >= count || i < 0){cout<<"Invalid selection in Menu::remove(int i)"; return dummy;}
  //attempt to remove non-existant option
  Text temp(option_list[i]);  //temporary copy to be returned
  for(i; i<count; i++){option_list[i] = option_list[i+1];}  //shift list up
  count--;
  option_list[count].set(""); //set end of list to empty string
  return temp;      //return removed text
}

int Menu::size() const{return count;}  //number of options in the menu

int Menu::capacity() const {return max_size_list;}

void Menu::pop_back()       //remove bottom option on list
{
  if(isEmpty())return;  //if there is nothing to return
  count--;   //deceremnt count
  option_list[count].set("");  //blank last element in the list
}

Text Menu::get(int i)
{
  Text dummy;  //item to return incase of invalid selection
  if(i >= count || i < 0){cout<<"Invalid selection in Menu::get(int i)"; return dummy;}
  //attempt to get non-existant option
  return option_list[i];
}


Text Menu::toString() const  //return Text reprensentation of menu
{
  Text out;  //Text which will contain menu
  if(!isEmpty())out.append("\n");
  if(!top_text.isEmpty()){out.append(top_text); out.append("\n");}
  if(!top_prompt.isEmpty()){out.append(top_prompt); out.append("\n\n");}
  if(!isEmpty())
  appendOptions(out);   //append menu options
  if (!bottom_text.isEmpty()){out.append(bottom_text); out.append("\n");}
  out.append(arrow);  //append "?->"
  if (!bottom_prompt.isEmpty()){out.append(bottom_prompt);}
  return out;   //return text object
}

int Menu::read_option_number()
{
  int choice; //int to be returned
  while(true)  //menu loop incase of invalid input
  {
    cout << toString();
    cin >> choice;
    if(isEmpty()){return choice;}  //if menu is empty --> return anything
    if(choice > count || choice <= 0)   //validation of selection
    {
      cout << "Invalid choice " << choice << ". " <<
      "I must be in the range " << 1 << "-" << count << "\n";
      continue;
    }
    else{return choice;}  //return user selection
  }
}

//setters
void Menu::set_top_prompt(const Text& t){top_prompt = t;}

void Menu::set_bottom_prompt(const Text& t){bottom_prompt = t;}

void Menu::set_top_message(const Text& t){top_text = t;}

void Menu::set_bottom_message(const Text& t){bottom_text = t;}

void Menu::clear_top_prompt(){if(!top_prompt.isEmpty()) top_prompt.set("");}

void Menu::clear_bottom_prompt(){if(!bottom_prompt.isEmpty()) bottom_prompt.set("");}

void Menu::clear_top_message(){if(!top_text.isEmpty()) top_text.set("");}

void Menu::clear_bottom_message(){if(!bottom_text.isEmpty()) bottom_text.set("");}

bool Menu::isEmpty() const{return (count == 0);}

//copy Text array into another
void Menu::copyTextArray(Text* in, Text* out)
{
  for(int i = 0; i < count; i++)
  {
    out[i] = in[i];
  }
}


//append list of options onto text object with numbers
void Menu::appendOptions(Text& t) const
{
  for(int i = 0; i < count; i++)
  {
    t.append("    ");  //space
    t.append("("); //print brackets
    const char* str;
    str = std::to_string(i+1).c_str(); //convert int to char*
    Text temp(str);
    t.append(temp);
    t.append(")");
    t.append(" ");
    t.append(option_list[i]);  //append list item
    t.append("\n");
  }
    t.append("\n");
}

//copy prompts from Menu object into caller
void Menu::copyPrompts(const Menu& m)
{
  top_prompt = m.top_prompt;
  bottom_prompt = m.bottom_prompt;    //set prompts according to "m"
  top_text = m.top_text;
  bottom_text = m .bottom_text;
}
