#include <vector>
#include <string>
#include <iostream>
#include "bstNode.h"

class vectorbst
{

public:
	vectorbst();
	~vectorbst();
	void insert(std::string s);
	int find(std::string s);
	bool isEmpty();
	void createChild(int parent, std::string s);

private:
	int findAtIndex(std::string s, int parent, int index);
	std::vector<bstNode> data;
};
