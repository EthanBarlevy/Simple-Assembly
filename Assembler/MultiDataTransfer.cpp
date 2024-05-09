#include "MultiDataTransfer.h"

MultiDataTransfer::MultiDataTransfer(std::string code, std::string registry, std::string iBit, std::string uBit, std::string pBit, std::string wBit, std::string lBit, std::string registers) : Command(code, registry)
{
    indexingBit = iBit;
    upBit = uBit;
    PSRBit = pBit;
    writeBackBit = wBit;
    loadStoreBit = lBit;
    registerList = registers;
}

std::vector<std::bitset<8>>* MultiDataTransfer::GetBits()
{
    std::vector<std::bitset<8>>* bits = new std::vector<std::bitset<8>>();
    std::string bitstring = ConditionCode + "100" + indexingBit + upBit + PSRBit + writeBackBit + loadStoreBit + Register + registerList;
    bits->push_back(std::bitset<8>(bitstring.substr(24, 8)));
    bits->push_back(std::bitset<8>(bitstring.substr(16, 8)));
    bits->push_back(std::bitset<8>(bitstring.substr(8, 8)));
    bits->push_back(std::bitset<8>(bitstring.substr(0, 8)));
    return bits;
}
