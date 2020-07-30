#include "bstNode.h"

bstNode::bstNode()
	: symbol(""), frequency(0)
{

}
bstNode::bstNode(std::string s)
	: symbol(s), frequency(0)
{
}

bstNode::bstNode(std::string s, int freq)
	: symbol(s), frequency(freq)
{

}

bstNode::~bstNode()
{
}

std::string bstNode::getSymbol()
{
	return symbol;
}

void bstNode::increment()
{
	frequency++;
}
