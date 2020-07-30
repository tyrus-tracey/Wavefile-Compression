/*
    General helper functions not tied to a specific class.
*/

#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include "Node.h"

class symbolDistribution
{
public:
    symbolDistribution(std::vector<std::string> input);
    ~symbolDistribution();
    void insert(std::string symbol);
    int getSum();
    std::vector<Node>::iterator find(std::string symbol);
    std::vector<Node> getData();
    

private:
    std::vector<Node> data;
};

std::vector<Node*>::iterator findMin(std::vector<Node*>& distribution);


