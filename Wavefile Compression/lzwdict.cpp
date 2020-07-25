#include "lzwdict.h"
#include <iostream>

//Creates an array-based lookup method of a fixed size (expands if limit reached)
lzwdict::lzwdict(std::vector<std::string> data)
	: codes(new std::string[500]), position(256)
{
	//initialize dictionary for values 0...255
	int i;
	std::vector<std::string>::iterator iter = data.begin();
	std::string s;
	std::string c;
	for (i = 0; i < capacity; i++) {
		codes[i] = i;
	}

	c = *iter;
	s = c;
	while (++iter != data.end()) {
		c = *iter;
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
	delete[] codes;
}

//insert string into dictionary, using index as the codeword
void lzwdict::insert(std::string symbol)
{
	if (position >= capacity) {
		expand();
	}
	codes[position] = symbol;
	position++;
}

//linear search of array, returns matching index (== codeword)
int lzwdict::getCode(std::string symbol)
{
	int code = -1;
	for (int i = 0; i < position; i++) {
		if (codes[i] == symbol) {
			code = i;
		}
	}
	return code;
}

//linear search of array, returns true if match found
bool lzwdict::hasSymbol(std::string symbol)
{
	for (int i = 0; i < position; i++) {
		if (codes[i] == symbol) {
			return true;
		}
	}
	return false;
}

int lzwdict::outputSize()
{
	return output.size();
}


// Allocates larger array and performs deepcopy if limit reached
void lzwdict::expand()
{
	std::string* newCodes = new std::string[position * 2];
	for (int i = 0; i < position; i++) {
		newCodes[i] = codes[i];
	}
	delete[] codes;
	codes = newCodes;
	capacity *= 2;
}
