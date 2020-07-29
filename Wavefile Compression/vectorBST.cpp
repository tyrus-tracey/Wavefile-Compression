#include "vectorbst.h"

vectorbst::vectorbst()
{
}

vectorbst::~vectorbst()
{
}

void vectorbst::insert(std::string s)
{
	if (isEmpty()) {
		data.push_back(bstNode()); //dummy node
		data.push_back(bstNode(s, 1));
		return;
	}

	int index = find(s); //get appropriate parent node

	if (data[index].getSymbol() == s) { //if exists, add to frequency
		data[index].increment();
	} else { //reached non-matching external node, create a new child
		createChild(index, s);
	}
	return;
}

// Start a binary search from root (index 1)
int vectorbst::find(std::string s)
{
	return findAtIndex(s, 1, 1);
}

// returns index of either matched node, or last searched external node 
int vectorbst::findAtIndex(std::string s, int parent, int index)
{
	if (index >= data.size() || data[index].getSymbol() == "") { //empty node or out of bound
		return parent;
	}
	else if (index * 2 >= data.size() || s == data[index].getSymbol()) { // match or external node
		return index;
	}
	else {  // internal, non-matching node. continue search.
		return findAtIndex(s, index, (index * 2) + (s < data[index].getSymbol() ? 0 : 1));
	}
}

bool vectorbst::isEmpty()
{
	return (data.size() == 0 ? true : false);
}

// create childnode from data[parent]
void vectorbst::createChild(int parent, std::string s)
{
	int left = parent * 2;
	int right = left + 1;
	//create space if necessary
	if (right > data.size()) { // resize if necessary
		data.resize(right + 1); 
	}

	if (data[parent].getSymbol() > s) {
		data[left] = bstNode(s, 1);
	}
	else {
		data[right] = bstNode(s, 1);
	}
	return;
}
