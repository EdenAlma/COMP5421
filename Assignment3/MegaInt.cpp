#include "MegaInt.h"
#include <string>
#include <iostream>

using std::string;
using std::deque;

/*default constructor puts +0 as the megaInt*/
MegaInt::MegaInt():sign(true)
{
	megaInt.push_back('0');
} 

/*
constructor which takes in string and loads characters into deque 
default sign is +
*/
MegaInt::MegaInt(string input)
{
	int i;

	if (input.at(0) == '+')
	{
		sign = true;
		i = 1;
	}
	else if (input.at(0) == '-')
	{
		sign = false;
		i = 1;
	}
	else
	{
		sign = true;
		i = 0;
	}


	for (i; i < input.size(); ++i)
	{
		megaInt.push_back(input[i]);
	}

}

/*
constructor which takes in character and loads into deque
default sign is +
*/
MegaInt::MegaInt(char c)
{
	megaInt.push_back(c);
	sign = true;
}

/*friend method overload of << for output*/
std::ostream & operator<<(std::ostream & os, MegaInt & input)
{
	string out = ""; // string to be output

	if (input.sign == true){out += '+';}  //add sign to output
	else{out += '-';}

	for (int i = 0; i < input.megaInt.size(); ++i)
	{
		out += input.megaInt[i];  //load characters onto the string
	}

	os << out;  //output the string to screen
	return os;	//return ostream object
}

/*overload of equality operator*/
bool MegaInt::operator==(MegaInt compare)
{
	if (this->sign != compare.sign) { return false; }  //signs don't match --> not equal

	if (this->megaInt.size() != compare.megaInt.size())  //size don't match --> not equal
	{
		return false;
	}
	else
	{
		for (int i = 0; i < this->megaInt.size(); ++i)
		{
			if (this->megaInt[i] != compare.megaInt[i]) { return false; }  //mismatch --> not equal
		}
	}

	return true;  //equality test was passed
}

/*overload of > operator*/
bool MegaInt::operator>(MegaInt compare)
{
	if (*this == compare) { return false; } // if equal

	if (this->sign != compare.sign)  // if signs dont match
	{
		if (compare.sign == true) //if "this" isnt positive --> false
		{
			return false;
		}
		else
		{
			return true;   // "this" is positive --> true
		}
	}
	

	if (this->sign == true)  //if sign is positive 
	{
		if (this->megaInt.size() == compare.megaInt.size())
		{
			for (int i = 0; i < megaInt.size(); ++i)   //if any char starting from left is bigger --> true
			{
				if (this->megaInt[i] > compare.megaInt[i])
				{
					return true;
				}
				else if (this->megaInt[i] < compare.megaInt[i])
				{
					return false;
				}
			}
		}
		else if (this->megaInt.size() > compare.megaInt.size()) //bigger positive number      
		{
			return true;
		}

		return false;
	}
	else   //comparing megaints with negative sign
	{
		if (this->megaInt.size() == compare.megaInt.size())
		{
			for (int i = 0; i < megaInt.size(); ++i)
			{
				if (this->megaInt[i] > compare.megaInt[i])  //bigger with minus --> false
				{
					return false;
				}
				else if (this->megaInt[i] < compare.megaInt[i])
				{
					return true;
				}
			}
		}
		else if (this->megaInt.size() > compare.megaInt.size()) //bigger with minus --> false
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	return false;
}

bool MegaInt::operator!=(MegaInt compare) //!=overload
{
	return !(*this == compare);
}

bool MegaInt::operator<(MegaInt compare) //<overload
{
	return (!(*this > compare) && (*this != compare));
}

bool MegaInt::operator>=(MegaInt compare) //>=overload
{
	return ((*this == compare) || (*this > compare));
}

bool MegaInt::operator<=(MegaInt compare) //<=overload
{
	return ((*this == compare) || (*this < compare));
}

bool MegaInt::isZero() //checking if MegaInt is zero
{
	return (megaInt.size() == 1 && megaInt[0] == '0');
}

char MegaInt::operator[](int index)  //[]overload
{
	return megaInt[index];
}

/*checks if the number portion is equivalent to another*/
bool MegaInt::absEqual(MegaInt compare) 
{
	if (this->megaInt.size() != compare.megaInt.size())  //not the same size --> not equal
	{
		return false;
	}
	else
	{
		for (int i = 0; i < this->megaInt.size(); ++i)
		{
			if (this->megaInt[i] != compare.megaInt[i]) { return false; }  //of chars don't match --> not equal
		}
	}

	return true;
}

/*checks if the number portion is bigger than another megaint*/
bool MegaInt::absGreater(MegaInt compare) 
{
	if (this->megaInt.size() == compare.megaInt.size()) //if sizes are the same
	{
		for (int i = 0; i < megaInt.size(); ++i)
		{
			if (this->megaInt[i] > compare.megaInt[i]) //if greater at leftmost --> true
			{
				return true;
			}
			else if (this->megaInt[i] < compare.megaInt[i]) //if smaller --> false
			{
				return false;
			}		
		}
		return false;   //--> equilvalent numbers
	}
	else if (this->megaInt.size() > compare.megaInt.size()) //more numbers --> bigger/true
	{
		return true; 
	}
	else  //less numbers --> smaller/false;
	{
		return false;
	}
}

/*method which subtracts one deque to another*/
deque<char>  MegaInt::minus(deque<char> lhs, deque<char> rhs)
{
	deque<char> output; //output

	while (rhs.size() < lhs.size()) //pad the rhs with zeros
	{
		rhs.push_front('0');
	}

	int sub = 0;  //temp int car for addition
	int borrow = 0;   //borrow

	for (int i = lhs.size() - 1; i >= 0; --i)  //iterate from right to left
	{
		if ((charToInt(lhs[i]) - charToInt(rhs[i]) - borrow) >= 0)
		{
			sub = charToInt(lhs[i]) - charToInt(rhs[i]) - borrow;   //compute
			borrow = 0; //reset borrow
			output.push_front(intToChar(sub));  //add char to deque
		}
		else
		{
			if (i != 0)  //if at left most and zero --> done
			{
				sub = (charToInt(lhs[i]) + 10) - charToInt(rhs[i]) - borrow; 
				borrow = 1;
				output.push_front(intToChar(sub));
			}
		}
		
	}

	while (output[0] == '0' && output.size() != 1)
	{
		output.pop_front();  //remove padding //but not zero!
	}

	return output;  //return deque
}

/*method which adds one deque to another*/
deque<char> MegaInt::plus(deque<char> lhs, deque<char> rhs)
{
	deque<char> output;

	if (lhs.size() > rhs.size())
	{
		while (rhs.size() <= lhs.size())
		{
			rhs.push_front('0');
		}
		lhs.push_front('0');
	}
	else if (rhs.size() > lhs.size())
	{
		while (lhs.size() <= rhs.size())
		{
			lhs.push_front('0');
		}
		rhs.push_front('0');
	}
	else
	{
		rhs.push_front('0');
		lhs.push_front('0');
	}


	int sum = 0;
	int carry = 0;
	int add = 0;

	for (int i = lhs.size() - 1; i >= 0; --i)
	{
		sum = carry + charToInt(lhs[i]) + charToInt(rhs[i]);
		add = sum % 10;
		carry = sum / 10;
		output.push_front(intToChar(add));
	}

	output.push_front(intToChar(carry));

	while (output[0] == '0' && output.size() != 1)
	{
		output.pop_front();
	}

	return output;

}

/*method converting char to int*/
int MegaInt::charToInt(char c)
{
	return int(c) - 48;
}

/*method converting int to char*/
char MegaInt::intToChar(int i)
{
	return char(i) + 48;
}

/*Method adding two megInts*/
MegaInt MegaInt::add(MegaInt A, MegaInt B)
{
	MegaInt output;
	if (A.sign == B.sign)  //if they have the same sign --> just add and give same sign
	{
		output.sign = A.sign;
		output.megaInt = plus(A.megaInt, B.megaInt);  //assign deque to output
		return output;
	}
	else   //if signs aren't the same
	{
		if (A.absGreater(B))  //if A is bigger than B
		{
			output.sign = A.sign;  //result will have sign of A
			output.megaInt = minus(A.megaInt, B.megaInt);  //subtract and assign to output
			return output;
		}
		else if (B.absGreater(A))  //if B is greater than A
		{
			output.sign = !(A.sign);
			output.megaInt = minus(B.megaInt, A.megaInt);
			return output;
		}
		else if (B.absEqual(A))  //if B == A
		{
			output.sign = true;
			output.megaInt.push_front('0');
			return output;
		}
	}
}

/*Method for subtracting two MegaInts*/
MegaInt MegaInt::subtract(MegaInt A, MegaInt B)
{
	MegaInt output;

	if (A.sign != B.sign) //if signs aren't the same --> add them up 
	{
		output.sign = A.sign;  //give sign of RHS
		output.megaInt = plus(A.megaInt, B.megaInt);
		return output;
	}
	else  //if signs are the same
	{
		if (A.absGreater(B))  //if A is bigger than B (absolute value)
		{
			output.sign = A.sign;
			output.megaInt = minus(A.megaInt, B.megaInt);  //A - B 
			return output;
		}
		else if (B.absGreater(A)) //B is greater than A
		{
			if (!(A.isZero()))  //if A is non-zero
			{
				output.sign = !(A.sign);
			}
			else
			{
				output.sign = false;
			}

			output.megaInt = minus(B.megaInt, A.megaInt);  //subtract
			
			return output;
		}
		else if (B.absEqual(A))  //if they are equal
		{
			output.sign = true;
			return output;   //return output = +0
		}
	}
}

/*overloaded +*/
MegaInt MegaInt::operator+(MegaInt rhs)
{
	return add(*this, rhs);
}

/*overloaded-*/
MegaInt MegaInt::operator-(MegaInt rhs)
{
	return subtract(*this, rhs);
}

/*overloaded +=*/
MegaInt MegaInt::operator+=(MegaInt rhs)
{
	MegaInt temp;
	temp.megaInt = (*this + rhs).megaInt;
	temp.sign = (*this + rhs).sign;
	this->megaInt = temp.megaInt;
	this->sign = temp.sign;

	return *this;
}

/*overloaded -=*/
MegaInt MegaInt::operator-=(MegaInt rhs)
{
	MegaInt temp;
	temp.megaInt = (*this - rhs).megaInt;
	temp.sign = (*this - rhs).sign;
	this->megaInt = temp.megaInt;
	this->sign = temp.sign;

	return *this;
}

/*overloaded **/
MegaInt MegaInt::operator*(MegaInt rhs)
{
	MegaInt output;
	output = this->m2Mult(rhs);
	return output;
}

/*overloaded *=*/
MegaInt MegaInt::operator*=(MegaInt rhs)
{
	MegaInt temp = (*this * rhs);
	this->megaInt = temp.megaInt;
	this->sign = temp.sign;
	return *this;
}

/*overloaded /*/
MegaInt MegaInt::operator/(MegaInt rhs)
{
	return this->d2Div(rhs);
}

/*overloaded /=*/
MegaInt MegaInt::operator/=(MegaInt rhs)
{
	MegaInt temp = (*this/rhs);
	this->megaInt = temp.megaInt;
	this->sign = temp.sign;
	return *this;
}

/*overloaded %*/
MegaInt MegaInt::operator%(MegaInt rhs)
{
	return this->d2Mod(rhs);
}

/*overloaded %=*/
MegaInt MegaInt::operator%=(MegaInt rhs)
{
	MegaInt temp = (*this % rhs);
	this->megaInt = temp.megaInt;
	this->sign = temp.sign;
	return *this;
}

/*overloaded ++ prefix*/
MegaInt MegaInt::operator++()
{
	MegaInt temp("1");
	*this += temp;
	return *this;
}

/*overloaded -- prefix*/
MegaInt MegaInt::operator--()
{
	MegaInt temp("1");
	*this -= temp;
	return *this;
}

/*M1 multiplication algorithm using iterative addition*/
MegaInt MegaInt::m1Mult(MegaInt rhs)
{
	MegaInt index; //megaInt = 0
	MegaInt temp2; //output
	MegaInt temp3; //copy of LHS
	temp3.megaInt = this->megaInt;
	temp3.sign = this->sign;


	for (index; index < rhs; ++index) //add LHS to itself RHS times
	{
		temp2 += temp3;
	}

	return temp2;  //return result
}

/*M2 multiplication algorithm*/
MegaInt MegaInt::m2Mult(MegaInt rhs)
{
	MegaInt output; //output
	MegaInt holder; //holds temporary value
	MegaInt N; //multiplier
	MegaInt M; //multiplcand
	MegaInt zero; //zero

	if (this->absGreater(rhs))  //if LHS > RHS
	{
		M.megaInt = rhs.megaInt;  //assign value to MegInt vars
		M.sign = rhs.sign;
		N.megaInt = this->megaInt;
		N.sign = this->sign;
	}
	else 
	{
		N.megaInt = rhs.megaInt;  //assign value to MegInt vars
		N.sign = rhs.sign;
		M.megaInt = this->megaInt;
		M.sign = this->sign;
	}

	int i = M.megaInt.size() - 1; //size of M 
	int x = 0; //index to know how many zero to add

	for (i; i >= 0; --i)
	{
		MegaInt index(M[i]);  //get leftmost char of multiplier

		holder = N.m1Mult(index);  //multiply by N and store in holder

		for (int y = 0; y < x; ++y)
		{
			holder.megaInt.push_back('0'); //add zeros to RHS of result accordingly
		}
	
		output += holder;  //add value to output var

		++x;  //add more zeros next time around the loop

	}

	if (rhs.sign == this->sign){ output.sign = true; }  //set sign
	else { output.sign = false; }
	return output; //return output

}

/*D1 division algorithm using iterative subtraction*/
MegaInt MegaInt::d1Div(MegaInt rhs)
{
	MegaInt output;
	MegaInt N;
	MegaInt zero;
	MegaInt remainder;
	N.megaInt = this->megaInt;
	N.sign = this->sign;

	if (rhs < zero || *this < zero && !(rhs < zero && *this < zero)) //if one of the vars is negative
	{
		if (rhs < zero) { return zero - (this->d1Div(zero - rhs));} //return negative answer
		else { return zero - (zero - (*this)).d1Div(rhs);}

	}
	else if(rhs < zero && *this < zero)  //if both are negative
	{
		return (zero - (*this)).d1Div(zero - rhs); //return postive answer
	}

	remainder = (N - rhs);//get first remiander
	N -= rhs; //remove from N

	if (remainder < zero) //if RHS > LHS --> return zero
	{
		return zero;
	}

	while (remainder >= zero)  //iterativley subtract rhs from lhs until reach becomes negative
	{
		remainder = (N -= rhs);
		++output;  //count the iterations
	}

	return output;  //return count
}

//uses method above to determine modulo
MegaInt MegaInt::d1Mod(MegaInt rhs)
{
	MegaInt temp;
	MegaInt zero;

	temp = this->d1Div(rhs);
	return ((*this) - (temp*rhs));
	
}

/*D2 division alogorithm using "long division"*/
MegaInt MegaInt::d2Div(MegaInt rhs)
{
	MegaInt output;  //output var
	MegaInt div;  //intermediary result
	MegaInt temp; //holds remainder
	MegaInt rhsCopy; //copy of divisor
	rhsCopy.megaInt = rhs.megaInt;
	rhsCopy.sign = rhs.sign;

	temp.megaInt = this->megaInt;

	int iter = (temp.megaInt.size() - rhsCopy.megaInt.size() + 1); //number of times we will shift divisor left

	while (rhsCopy.megaInt.size() < this->megaInt.size())
	{
		rhsCopy.megaInt.push_back('0'); //pad RHS with 0s so that 34523/72 ==> 34523/72000
	}

	if (iter > 0) //if LHS > RHS
	{
		output.megaInt.pop_back(); //remove zero from output --> empty deque
	}

	for (int i = 0; i < iter; ++i)
	{
		div = temp.d1Div(rhsCopy);
		temp = temp.d1Mod(rhsCopy);

		if(i != 0 || div[0] != '0') //if result of division is not 0
		output.megaInt.push_back(div[0]);  //push into output deque

		rhsCopy.megaInt.pop_back();  //remove padding 
	}

	if (rhs.sign == this->sign) { output.sign = true; }  //fix signs
	else { output.sign = false; }
	return output;

}

/*uses method above to determine modulo*/
MegaInt  MegaInt::d2Mod(MegaInt rhs)
{
	MegaInt temp;
	temp = this->d2Div(rhs);
	return ((*this) - (temp*rhs));
}


