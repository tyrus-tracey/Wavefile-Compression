#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

class lzwdict
{
public:
	lzwdict(std::stringstream& input);
	~lzwdict();
	void insert(std::string symbol);
	int getCode(std::string symbol);
	bool hasSymbol(std::string symbol);
	int outputSize();

private:
	std::unordered_map <std::string, int> codes;
	int currentCode;		
	std::vector<int> output;
};

