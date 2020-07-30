#pragma once
#include <string>

class bstNode
{
public:
	bstNode();
	bstNode(std::string s);
	bstNode(std::string s, int freq);
	~bstNode();
	std::string getSymbol();
	void increment();

private:
	std::string symbol;
	int frequency;
};

