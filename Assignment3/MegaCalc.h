#ifndef MEGACALC_H
#define MEGACALC_H
#include "MegaInt.h";

class MegaCalc 
{

public:
	MegaCalc();
	void run();
	MegaInt accumulator;

private:
	void parseCommand(std::string);
	void executeCommand(char, MegaInt);
	void factorial();
	void hailstone();
	bool isSymbol(char);
	bool isSign(char);
	bool isInt(char);
	bool isIntString(std::string);
	bool isCommand(char );

};


#endif