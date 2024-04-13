#include <iostream>
#include <fstream>
#include "Binary.h"
#include "Hex.h"
#include "MOVT.h"

char bitset_to_byte(const std::bitset<8>& bits) {
    return static_cast<char>(bits.to_ulong());
}

void write_to_image_file(const std::string& filename, const std::bitset<8>& data) {
    std::ofstream imageFile(filename, std::ios::binary);
    if (imageFile.is_open()) {
        char byte = bitset_to_byte(data);
        imageFile.write(&byte, 1);
        imageFile.close();
        std::cout << "Data written to " << filename << " successfully." << std::endl;
    }
    else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

int main()
{
    std::string filename = "blinking.txt";
    MOVT movt;
    movt.ConditionCode->SetBinary("1110");
    movt.imm4->SetBinary("0011");
    movt.Register->SetBinary("0100");
    movt.imm12[0]->SetBinary("1111");
    movt.imm12[1]->SetBinary("0010");
    movt.imm12[2]->SetBinary("0000");
    std::cout << movt.ConvertToHex();
}

