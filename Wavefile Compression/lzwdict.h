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
	uint16_t getCode(std::string symbol);
	bool hasSymbol(std::string symbol);
	int outputSize();

private:
	std::unordered_map <std::string, uint16_t> codes;
	uint16_t currentCode;		
	std::vector<uint16_t> output;
};

