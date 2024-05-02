#include "Branch.h"
#include <iostream>

Branch::Branch(std::string code, std::string registry) : Command(code, registry)
{
    exchange = true;
}

Branch::Branch(std::string code, std::string registry, std::string usingLBit, std::string offsets) : Command(code, registry)
{
    lBit = usingLBit;
    offset = offsets;
    exchange = false;
}

std::vector<std::bitset<8>>* Branch::GetBits()
{
    if (!exchange)
    {
        std::vector<std::bitset<8>>* bits = new std::vector<std::bitset<8>>();;
        std::string bitstring = ConditionCode + "101" + lBit + offset;
        bits->push_back(std::bitset<8>(bitstring.substr(24, 8)));
        bits->push_back(std::bitset<8>(bitstring.substr(16, 8)));
        bits->push_back(std::bitset<8>(bitstring.substr(8, 8)));
        bits->push_back(std::bitset<8>(bitstring.substr(0, 8)));
        return bits;
    }
    else
    {
        std::vector<std::bitset<8>>* bits = new std::vector<std::bitset<8>>();;
        std::string bitstring = ConditionCode + "000100101111111111110001" + Register;
        bits->push_back(std::bitset<8>(bitstring.substr(24, 8)));
        bits->push_back(std::bitset<8>(bitstring.substr(16, 8)));
        bits->push_back(std::bitset<8>(bitstring.substr(8, 8)));
        bits->push_back(std::bitset<8>(bitstring.substr(0, 8)));
        return bits;
    }
}
