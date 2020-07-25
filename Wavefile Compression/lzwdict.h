#pragma once
#include <map>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

class lzwdict
{
public:
	lzwdict(std::vector<std::string> data);
	~lzwdict();
	void insert(std::string symbol);
	int getCode(std::string symbol);
	bool hasSymbol(std::string symbol);
	int outputSize();

private:
	void expand();
	std::string* codes;	//array-based dictionary
	int position;		//next available space in dictionary
	int capacity = 500;		//default limit of 256
	std::vector<int> output;
};

