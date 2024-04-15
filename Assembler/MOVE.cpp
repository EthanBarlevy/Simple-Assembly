#include "MOVE.h"

MOVE::MOVE()
{
    c = "0011";
    q = "0000";
    imm12[0] = "";
    imm12[1] = "";
    imm12[2] = "";
    imm4 = "";
}

MOVE::MOVE(MOVE::Half side) : MOVE()
{
    if (side == MOVE::Half::FRONT || side == MOVE::Half::W)
    {
        q = "0000";
    }
    else
    {
        q = "0100";
    }
}

std::bitset<8>* MOVE::GetBits()
{
    static std::bitset<8> bits[4];
    bits[3] = std::bitset<8>( ConditionCode + c);
    bits[2] = std::bitset<8>(q + imm4);
    bits[1] = std::bitset<8>(Register + imm12[0]);
    bits[0] = std::bitset<8>(imm12[1] + imm12[2]);
    return bits;
}

void MOVE::setImmediate(std::string& immediate)
{
    imm4 = immediate.substr(0, 4);
    imm12[0] = immediate.substr(4, 4);
    imm12[1] = immediate.substr(8, 4);
    imm12[2] = immediate.substr(12, 4);
}
