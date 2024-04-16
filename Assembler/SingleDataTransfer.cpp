#include "SingleDataTransfer.h"
#include <iostream>

SingleDataTransfer::SingleDataTransfer(std::string code, std::string registry, std::string biShift, std::string immediate, std::string iBit, std::string uBit, std::string bBit, std::string wBit, std::string lBit, std::string Rn, std::string secondOpp) : Command(code, registry)
{
    bitShift = biShift;
    usingImmediate = immediate;
    indexingBit = iBit;
    upBit = uBit;
    wordBit = bBit;
    writeBackBit = wBit;
    loadStoreBit = lBit;
    firstOpperandRegister = Rn;
    secondOpperand = secondOpp;
}

std::vector<std::bitset<8>>* SingleDataTransfer::GetBits()
{
    std::vector<std::bitset<8>>* bits = new std::vector<std::bitset<8>>();
    std::string bitstring = ConditionCode + bitShift + usingImmediate + indexingBit + upBit + wordBit + writeBackBit + loadStoreBit + Register + firstOpperandRegister + secondOpperand;
    bits->push_back(std::bitset<8>(bitstring.substr(24, 8)));
    bits->push_back(std::bitset<8>(bitstring.substr(16, 8)));
    bits->push_back(std::bitset<8>(bitstring.substr(8, 8)));
    bits->push_back(std::bitset<8>(bitstring.substr(0, 8)));
    return bits;
}
