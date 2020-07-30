/*
    General helper functions not tied to a specific class.
*/

#pragma once
#include <string>
#include <vector>
#include "Node.h"
#include "Helper.h"


symbolDistribution::symbolDistribution(std::vector<std::string> input)
{
    std::vector<std::string>::iterator iter = input.begin();
    while (iter != input.end()) {
        insert(*iter);
        iter++;
    }
}

symbolDistribution::~symbolDistribution()
{

}

void symbolDistribution::insert(std::string symbol)
{
    std::vector<Node>::iterator iter = find(symbol);
    if (iter != data.end()) {
        (*iter)++;
    }
    else {
        data.push_back(Node(symbol, 1));
    }
}

std::vector<Node>::iterator symbolDistribution::find(std::string symbol)
{
    std::vector<Node>::iterator iter = data.begin();
    while (iter != data.end()) {
        if (iter->element() == symbol) {
            return iter;
        }
        iter++;
    }
    return iter;
}

std::vector<Node> symbolDistribution::getData()
{
    return data;
}

int symbolDistribution::getSum()
{
    std::vector<Node>::iterator iter = data.begin();
    int sum = 0;
    while (iter != data.end()) {
        sum += iter->getFrequency();
        iter++;
    }
    return sum;
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


