#include "lzwdict.h"
#include <iostream>

//Creates an array-based lookup method of a fixed size (expands if limit reached)
lzwdict::lzwdict(std::stringstream& input)
	: currentCode(0)
{
	//initialize dictionary for values 0...9 and -
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

//insert string into dictionary, using index as the codeword
void lzwdict::insert(std::string symbol)
{
	codes[symbol] = ++currentCode;
}

//linear search of array, returns matching codeword
int lzwdict::getCode(std::string symbol)
{
	return codes.find(symbol)->second;
}

//linear search of array, returns true if match found
bool lzwdict::hasSymbol(std::string symbol)
{
	if (codes.find(symbol) != codes.end()) {
		return true;
	}
	return false;
}

int lzwdict::outputSize()
{
	return output.size();
}
