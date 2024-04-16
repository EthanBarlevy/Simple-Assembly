#include "MOVE.h"
#include <iostream>

MOVE::MOVE(std::string code, std::string registry) : Command(code, registry)
{
    c = "0011";
    q = "0000";
    imm12 = "";
    imm4 = "";
}

MOVE::MOVE(std::string code, std::string registry, MOVE::Half side) : MOVE(code, registry)
{
    if (side == MOVE::Half::FRONT)
    {
        q = "0000";
    }
    else
    {
        q = "0100";
    }
}

MOVE::MOVE(std::string code, Half side, std::string im4, std::string registry, std::string im12) : MOVE(code, registry, side)
{
    imm4 = im4;
    imm12 = im12;
}

std::vector<std::bitset<8>>* MOVE::GetBits()
{
    std::vector<std::bitset<8>>* bits = new std::vector<std::bitset<8>> ();
    std::string bitstring = ConditionCode + c + q + imm4 + Register + imm12;
    bits->push_back(std::bitset<8>(imm12.substr(4, 8)));
    bits->push_back(std::bitset<8>(Register + imm12.substr(0, 4)));
    bits->push_back(std::bitset<8>(q + imm4));
    bits->push_back(std::bitset<8>( ConditionCode + c));
    return bits;
}