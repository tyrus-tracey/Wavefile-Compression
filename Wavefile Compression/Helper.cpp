/*
    General helper functions not tied to a specific class.
*/

#pragma once
#include <string>
#include <vector>
#include "Node.h"
#include "Helper.h"

// Compare for lower-frequency node
struct CompareNodes {
    bool operator()(const Node node1, const Node node2)
    {
        return node1.getFrequency() > node2.getFrequency();
    }
};

/*
itor = vec.begin();								// represents a symbol
    while(itor != vec.end() )
        scan = iter++;
        freq = 1;
        while(*scan == *itor) {						// until the next symbol is found increment frequency
            freq++;
            scan++;
        }
        distribution.push_back( Node(*itor, freq) );// create node
        itor = scan;								// repeat with next symbol
    }
 */
symbolDistribution::symbolDistribution(std::vector<std::string>& input)
{
    int freq;
    std::vector<std::string>::iterator iter = input.begin();
    std::string symbol;
    while (iter != input.end()) {
        symbol = *iter;
        freq = 0;
        if (symbol == "9999") {
            int test = 0;
        }
        while (iter != input.end() && symbol == *iter) {
            freq++;
            iter++;
        }
        data.push_back(Node(symbol, freq));
    }
    
}

symbolDistribution::~symbolDistribution()
{

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