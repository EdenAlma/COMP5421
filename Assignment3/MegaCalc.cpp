#include "MegaCalc.h"
#include <string>
#include <iostream>
#include<algorithm>

using std::cout;
using std::cin;
using std::string;
using std::remove;

MegaCalc::MegaCalc()
{
}

void MegaCalc::run()
{
	string userIn;
	cout << "Welcome to MegaCalculator\n"; //welcome message
	cout << "=========================\n";

	while (userIn != "q")
	{
		cout << "\nAccumulator: " << accumulator;
		cout << "\nEnter input: ";
		getline(cin, userIn);
		userIn.erase(remove(userIn.begin(), userIn.end(), ' '), userIn.end()); //remove white space
		parseCommand(userIn);
	}

	cout << "\nThank you for using MegaCalculator\n"; //welcome message
}

void MegaCalc::parseCommand(std::string input)
{
	char cmd;
	MegaInt temp;

	if (input.length() == 0)  //empty string input
	{
		cout << "Invalid input...try again";
		return;
	}
	else if (input.length() == 1) //one character input
	{
		if (!isCommand(input[0]))
		{
			cout << "Invalid input...try again";
			return;
		}
		else
		{
			cmd = (input[0]);
			executeCommand(cmd, temp);
			return;
		}
	}
	else if (input.length() > 1)  //multiple character input
	{
		if (!isSymbol(input[0]))  //doesn't start with symbol
		{
			cout << "Invalid input...try again";
			return;
		}
		else
		{
			if (isSymbol(input[1]))  //starts with two symbols?
			{
				if (!isSign(input[1]))  //if second symbol is not a sign
				{
					cout << "Invalid input...try again";
					return;
				}
				else  //second symbol is a sign
				{
					if (input.length() == 2)  //only command not int basically something like *+
					{
						cout << "Invalid input...try again";
						return;
					}
					else
					{
						if (!isIntString(input.substr(2)))   //string contains non-int characters
						{
							cout << "Invalid input...try again";
							return;
						}
						else   //valid input
						{
							MegaInt local(input.substr(1));
							cmd = input[0];
							executeCommand(cmd, local);
							return;
						}
					}

				}
			}
			else  //starts with single symbol
			{
				if (!isIntString(input.substr(1)))   //string contains non-int characters
				{
					cout << "Invalid input...try again";
					return;
				}
				else   //valid input
				{
					MegaInt local(input.substr(1));
					cmd = input[0];
					executeCommand(cmd, local);
					return;
				}
			}
		}
	}

	return;
}

void MegaCalc::executeCommand(char cmd, MegaInt input)
{
	if (cmd == '+')
	{
		accumulator += input;
		return;
	}
	else if (cmd == '-')
	{
		accumulator -= input;
		return;
	}
	else if (cmd == '*')
	{
		accumulator *= input;
		return;
	}
	else if (cmd == '/')
	{
		accumulator /= input;
		return;
	}
	else if(cmd == '%')
	{
		accumulator %= input;
		return;
	}
	else if (cmd == '=')
	{
		accumulator = input;
		return;
	}
	else if (cmd == 'c')
	{
		MegaInt zero;
		accumulator = zero;
	}
	else if (cmd == 'n')
	{
		MegaInt neg("-1");
		accumulator *= neg;
	}
	else if (cmd == 'f')
	{
		factorial();
	}
	else if (cmd == 'h')
	{
		hailstone();
	}
	else if (cmd == 'q')
	{
		return;
	}
}


void MegaCalc::factorial()
{
	MegaInt temp;
	MegaInt zero;
	MegaInt one("1");
	temp = (one-zero);

	if (accumulator <= zero)
	{
		cout << "Invalid factorial parameters!\n";
		return;
	}

	for (one; one <= accumulator; ++one)
	{
		temp = (temp*one);
	}

	cout << accumulator << "! = " << temp << "\n";
}

void MegaCalc::hailstone()
{
	MegaInt count;
	MegaInt one("1");
	MegaInt two("2");
	MegaInt three("3");
	MegaInt zero;
	MegaInt current;
	current = accumulator;

	if (accumulator <= zero)
	{
		cout << "Invalid factorial parameters!\n";
		return;
	}

	while(current != one)
	{
		cout << "> " << current << "\n";
		
		if ((current%two) == zero)
		{
			current = current/two;
		}
		else
		{
			current = (current*three);
			++current;
		}
		++count;
	}

	++count;
	cout << "> " << current << "\n";

	cout << "\nlength of hailstone(" << accumulator << ") sequence: " << count << "\n";

}

bool MegaCalc::isSymbol(char c)
{
	switch (c)
	{
	case'+':
	case'-':
	case'*':
	case'/':
	case'%':
	case'=':
		return true;
		break;
	default:
		return false;
		break;
	}
}

bool MegaCalc::isSign(char c)
{
	return (c == '+' || c == '-');
}

bool MegaCalc::isInt(char c)
{
	return (c <= '9' && c >= '0');
}


bool MegaCalc::isIntString(string s)
{
	for (int i = 0; i < s.length(); ++i)
	{
		if (!isInt(s[i]))
		{
			return false;
		}
	}

	return true;
}

bool MegaCalc::isCommand(char c)
{
	switch (c)
	{
	case'c':
	case'n':
	case'f':
	case'h':
	case'q':
		return true;
		break;
	default:
		return false;
		break;
	}
}





