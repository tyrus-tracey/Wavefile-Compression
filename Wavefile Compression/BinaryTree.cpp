#include "BinaryTree.h"
#include "Helper.h"
#include <queue>
#include <iostream>

BinaryTree::BinaryTree(std::vector<Node> distribution)
	:treeSize(distribution.size()), rootNode(nullptr), position(rootNode)
{
	//Create min-heap of allocated node pointers
	std::vector<Node>::iterator iter = distribution.begin();
	std::priority_queue<Node*, std::vector<Node*>, CompareNodes> nodeQueue;
	std::vector<Node*> junkList;
	while (iter != distribution.end()) {
		Node* node = new Node(iter->element(), iter->getFrequency());
		nodeQueue.push(node);
		iter++;
	}

	// 1. Remove least-common nodes
	// 2. join to a parent
	// 3. Append parent back to queue
	Node* left;
	Node* right;
	Node* parent;

	while (nodeQueue.size() > 1) {
		left = new Node(nodeQueue.top());
		junkList.push_back(nodeQueue.top());
		nodeQueue.pop();
		right = new Node(nodeQueue.top());
		junkList.push_back(nodeQueue.top());
		nodeQueue.pop();
		parent = new Node(left, right);
		nodeQueue.push(parent);
	}
	
	// Delete allocated nodes 
	std::vector<Node*>::iterator pNodeIterator = junkList.begin();
	while (pNodeIterator != junkList.end()) {
		delete *pNodeIterator;
		pNodeIterator++;
	}

	// Allocate one node representing root of Huffman tree
	if (!nodeQueue.empty()) {
		rootNode = new Node(nodeQueue.top()); 
	}
}

BinaryTree::~BinaryTree()
{
	deleteTree(rootNode);
	return;
}

int BinaryTree::size() const
{
	return treeSize;	
}

bool BinaryTree::empty() const
{
	return treeSize <= 0;
}

void BinaryTree::printTree()
{
	printNode(rootNode);
	return;
}

void BinaryTree::printNode(Node* node) {
	if (node == nullptr) {
		return;
	}
	printNode(node->left());
	printNode(node->right());
	std::cout << node->element() << ": " << node->getFrequency() << " " << node->getCode() << std::endl;
	return;
}

void BinaryTree::deleteTree(Node* node) {
	if (node == nullptr) {
		return;
	}
	if (!node->isExternal()) {
		deleteTree(node->left());
		deleteTree(node->right());
	}
	delete node;
	return;
}

void BinaryTree::generateCodes()
{
	if (!empty()) {
		if (rootNode->isExternal()) {
			rootNode->appendCode("1");
		}
		generateCode(rootNode);
	}
}

// Returns size of compressed file in bytes
int BinaryTree::totalSize()
{
	return symbolSize(rootNode) / 8;
}


double BinaryTree::averageCodeLength()
{
	if (!empty()) {
		return getCodeLength(rootNode);
	}
	else {
		return 0;
	}
}

// Get codeword size (Frequency * code length) of external nodes
int BinaryTree::symbolSize(Node* node)
{
	if (node->isExternal()) {
		return (node->getFrequency() * node->getCode().length());
	}

	int sum = symbolSize(node->left()) + symbolSize(node->right());
	return sum;
}

void BinaryTree::generateCode(Node* node)
{
	if (node == nullptr) {
		return;
	}
	if (node->isExternal()) {
		return;
	}
	if (node->left() != nullptr) {
		node->left()->appendCode(node->getCode() + '1');
		generateCode(node->left());
	}
	if (node->right() != nullptr) {
		node->right()->appendCode(node->getCode() + '0');
		generateCode(node->right());
	}
	return;
}

double BinaryTree::getCodeLength(Node* node)
{
	if (node->isExternal()) {
		double prob = double(node->getFrequency()) / rootNode->getFrequency();
		return (prob * node->getCode().length());
	}

	double sum = getCodeLength(node->left()) + getCodeLength(node->right());
	return sum;
}

Node* BinaryTree::root() 
{
	return rootNode;
}
