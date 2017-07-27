// Driver program for assignment 1
// COMP 5421/1 BB, Summer 2017

#include<cstddef>  // for EXIT_SUCCESS
#include<iostream>

using namespace std; // ok in driver code

#include "Text.h"
#include "Menu.h"

int main()
{


    Menu menu; // an empty menu
    cout << menu << endl;

    int choice = menu.read_option_number();
    cout << "you entered: " << choice << endl;

    cout << "demo operator<< on empty menu" << endl;
    cout << "--------------------------------" << endl;
    cout << menu << endl;
    cout << "--------------------" << endl;

    cout << "demo push_back" << endl;
    cout << "---------------------------------" << endl;
    menu.push_back("Pepsi");
    cout << menu << endl;

    cout << "demo more push_backs" << endl;
    cout << "---------------------------------" << endl;
    menu.push_back("Apple juice");
    menu.push_back("Root beer");
    choice = menu.read_option_number();
    cout << "you entered: " << choice << endl;
    cout << "--------------------" << endl;

    cout << "demo top/bot prompts" << endl;
    cout << "---------------------------------" << endl;
    menu.set_top_prompt("Choose your thirst crusher: ");
    menu.set_bottom_prompt("Enter a drink number: ");
    cout << menu << endl;
    cout << "--------------------" << endl;

    cout << "demo pop_back and insert on a menu" << endl;
    cout << "-------------------------------------" << endl;
    menu.pop_back();    // remove the last option
    menu.insert(1, "Iced tea with lemon");  //  this will be option 2
    choice = menu.read_option_number();
    cout << "you entered: " << choice << endl;
    cout << "--------------------" << endl;

    cout << "demo pop_back and remove on a menu" << endl;
    cout << "-------------------------------------" << endl;
    menu.pop_back(); // // remove the last option
    menu.remove(0);  //  // remove the first option (index k indexes element k+1)
    cout << menu << endl;
    cout << "--------------------" << endl;

    cout << "demo top/bot messages" << endl;
    cout << "---------------------------------" << endl;
    menu.set_top_message("Quench your thirst with our fine drinks");
    menu.set_bottom_message("Time to obey your thirst!");
    cout << menu << endl;
    cout << "--------------------" << endl;

    cout << "demo removing the only element" << endl;
    cout << "---------------------------------" << endl;
    menu.pop_back();
    cout << menu << endl;
    cout << "--------------------" << endl;

    cout << "demo resetting top/bot items + more push_backs" << endl;
    cout << "---------------------------------" << endl;
    menu.set_top_message("Who Says You Can't Buy Happiness?");
    menu.clear_bottom_message();
    menu.set_top_prompt("Just Consider Our Seriously Delicious Ice Cream Flavors for Summer ");
    menu.set_bottom_prompt("Enter the number of your Happiness Flavor: ");
    menu.push_back("Bacon ice cream!");
    menu.push_back("Strawberry ice cream");
    menu.push_back("Vanilla ice cream");
    menu.push_back("Chocolate chip cookie dough ice cream");
    choice = menu.read_option_number();
    cout << "you entered: " << choice << endl;
    cout << "--------------------" << endl;

    return EXIT_SUCCESS; // from <cstddef>
}














