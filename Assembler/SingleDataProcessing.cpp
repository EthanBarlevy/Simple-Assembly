#include "SingleDataProcessing.h"
#include <iostream>

SingleDataProcessing::SingleDataProcessing(std::string code, std::string registry, std::string biShift, std::string immediate, std::string oppCode, std::string sBit, std::string Rn, std::string secondOpp) : Command(code, registry)
{
    bitShift = biShift;
    usingImmediate = immediate;
    operationCode = oppCode;
    usingSBit = sBit;
    firstOpperandRegister = Rn;
    secondOpperand = secondOpp;
}

std::vector<std::bitset<8>>* SingleDataProcessing::GetBits()
{
    std::vector<std::bitset<8>>* bits = new std::vector<std::bitset<8>>();
    std::string bitstring = ConditionCode + bitShift + usingImmediate + operationCode + usingSBit + Register + firstOpperandRegister + secondOpperand;
    bits->push_back(std::bitset<8>(bitstring.substr(24, 8)));
    bits->push_back(std::bitset<8>(bitstring.substr(16, 8)));
    bits->push_back(std::bitset<8>(bitstring.substr(8, 8)));
    bits->push_back(std::bitset<8>(bitstring.substr(0,8)));
    return bits;
}
