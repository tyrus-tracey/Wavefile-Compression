/*
    General helper functions not tied to a specific class.
*/

#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Node.h"
#include "Helper.h"
#include <math.h>

void removeZeroes(std::vector<Node>& distribution)
{
    std::vector<Node>::iterator iter = distribution.begin();
    while (iter != distribution.end()) {
        if (iter->getFrequency() == 0) {
            iter = distribution.erase(iter);
        }
        else {
            iter++;
        }
    }
    return;
}

// Parse string into chars and record frequencies
//vector vst for distribution here
std::vector<Node> readInputDistributionSingle(std::vector<std::string> input) {
    char temp;
    std::vector<Node> distribution;
    std::vector<std::string>::iterator iter = input.begin();

    while (iter != input.end()) {
        Node temp(*iter, 0);
        //if not in distribution
        distribution.push_back(temp);
        //if exists in distribution
      
    }

    removeZeroes(distribution);
    return distribution;
}

std::vector<Node*>::iterator findMin(std::vector<Node*>& distribution) {
    std::vector<Node*>::iterator min = distribution.begin();
    std::vector<Node*>::iterator iter = distribution.begin();
    while (iter != distribution.end()) {
        if ((*iter)->getFrequency() < (*min)->getFrequency()) {
            min = iter;
        }
        iter++;
    }
    return min;
}

int getSum(std::vector<Node> distribution)
{
    std::vector<Node>::iterator iter = distribution.begin();
    int sum = 0;
    while (iter != distribution.end()) {
        sum += (*iter).getFrequency();
        iter++;
    }
    return sum;
}
