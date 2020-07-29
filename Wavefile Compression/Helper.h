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

void removeZeroes(std::vector<Node>& distribution);

std::vector<Node> readInputDistributionSingle(std::string input);

std::vector<Node*>::iterator findMin(std::vector<Node*>& distribution);

int getSum(std::vector<Node> distribution);
