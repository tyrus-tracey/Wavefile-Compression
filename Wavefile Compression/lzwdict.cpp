#include "lzwdict.h"
#include <iostream>

//Creates a hash-table dictionary and outputs codes to a vector
lzwdict::lzwdict(std::stringstream& input)
	: currentCode(0)
{
	//initialize dictionary for values 0...9 and '-'
	int i;
	std::string s;
	char c;
	for (i = 0; i < 10; i++) {
		codes[std::to_string(i)] = ++currentCode;
	}
	codes["-"] = ++currentCode;
	input >> c;
	s = c;
	while (input >> c) {
		if (hasSymbol(s + c)) {
			s = s + c;
		}
		else {
			output.push_back(getCode(s));
			insert(s + c);
			s = c;
		}
	}
	output.push_back(getCode(s));
}

lzwdict::~lzwdict()
{
}

//insert string into dictionary with code
void lzwdict::insert(std::string symbol)
{
	codes[symbol] = ++currentCode;
}

//returns matching codeword of symbol
uint16_t lzwdict::getCode(std::string symbol)
{
	return codes.find(symbol)->second;
}

//returns true if found in dictionary
bool lzwdict::hasSymbol(std::string symbol)
{
	if (codes.find(symbol) != codes.end()) {
		return true;
	}
	return false;
}

//number of codes * bytes per code
int lzwdict::outputSize()
{
	int codeSize = sizeof(uint16_t);
	return output.size() * codeSize;
}
