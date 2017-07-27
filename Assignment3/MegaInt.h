#ifndef MEGAINT_H
#define MEGAINT_H

#include<deque>
#include<string>
#include<iostream>

class MegaInt
{

public:

	MegaInt();
	MegaInt(std::string);
	MegaInt(char);
	friend std::ostream & operator<<(std::ostream &, MegaInt &);
	bool operator==(MegaInt);
	bool operator>(MegaInt);
	bool operator!=(MegaInt);
	bool operator<(MegaInt);
	bool operator>=(MegaInt);
	bool operator<=(MegaInt);
	bool isZero();
	MegaInt operator+(MegaInt);
	MegaInt operator-(MegaInt);
	MegaInt operator+=(MegaInt);
	MegaInt operator-=(MegaInt);
	MegaInt operator*(MegaInt);
	MegaInt operator*=(MegaInt);
	MegaInt operator/(MegaInt);
	MegaInt operator/=(MegaInt);
	MegaInt operator%(MegaInt);
	MegaInt operator%=(MegaInt);
	MegaInt operator++();
	MegaInt operator--();
	
private:
	std::deque<char> megaInt;
	bool sign;
	int charToInt(char c);
	char intToChar(int i);
	std::deque<char> minus(std::deque<char>, std::deque<char>);
	std::deque<char> plus(std::deque<char>, std::deque<char>);
	bool absEqual(MegaInt);
	bool absGreater(MegaInt);
	MegaInt add(MegaInt, MegaInt);
	MegaInt subtract(MegaInt, MegaInt);
	MegaInt m1Mult(MegaInt);
	MegaInt m2Mult(MegaInt);
	MegaInt d1Div(MegaInt);
	MegaInt d1Mod(MegaInt);
	MegaInt d2Div(MegaInt);
	MegaInt d2Mod(MegaInt);
	char operator[](int);
};
#endif