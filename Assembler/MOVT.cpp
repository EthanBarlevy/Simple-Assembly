#include "MOVT.h"

MOVT::MOVT()
{
    c->SetBinary("0011");
    q->SetBinary("0100");
    imm12[0] = new Binary();
    imm12[1] = new Binary();
    imm12[2] = new Binary();
    imm4 = new Binary();
}

std::string MOVT::ConvertToHex()
{
    std::string hex;
    hex += Hex::GetHex(imm12[1]->GetBinary());
    hex += Hex::GetHex(imm12[2]->GetBinary());
    hex += Hex::GetHex(Register->GetBinary());
    hex += Hex::GetHex(imm12[0]->GetBinary());
    hex += Hex::GetHex(q->GetBinary());
    hex += Hex::GetHex(imm4->GetBinary());
    hex += Hex::GetHex(ConditionCode->GetBinary());
    hex += Hex::GetHex(c->GetBinary());
    return hex;
}

void MOVT::setImmediate(std::string& immediate)
{
    imm4->SetBinary(immediate.substr(0, 4));
    imm12[0]->SetBinary(immediate.substr(4, 4));
    imm12[1]->SetBinary(immediate.substr(8, 4));
    imm12[2]->SetBinary(immediate.substr(12, 4));
}
