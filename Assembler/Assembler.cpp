#include <iostream>
#include <fstream>
#include "MOVE.h"

void append_to_image_file(const std::string& filename, const std::bitset<8>& data) {
    std::ofstream imageFile(filename, std::ios::binary | std::ios::app); // Open file in append mode
    if (!imageFile.is_open()) {
        // File does not exist, attempt to create it
        imageFile.open(filename, std::ios::binary);
        if (!imageFile.is_open()) {
            std::cerr << "Unable to create or open file: " << filename << std::endl;
            return;
        }
    }

    char byte = static_cast<char>(data.to_ulong());
    imageFile.write(&byte, 1);
    imageFile.close();
    std::cout << "Data appended to " << filename << " successfully." << std::endl;
}

int main()
{
    std::string filename = "blinking.txt";
    MOVE movt;
    movt.ConditionCode = "1110";
    movt.imm4 = "0011";
    movt.Register = "0100";
    movt.imm12[0] = "1111";
    movt.imm12[1] = "0010";
    movt.imm12[2] = "0000";
    append_to_image_file("kernel7.img", movt.GetBits()[0]);
    append_to_image_file("kernel7.img", movt.GetBits()[1]);
    append_to_image_file("kernel7.img", movt.GetBits()[2]);
    append_to_image_file("kernel7.img", movt.GetBits()[3]);
}

