#include <iomanip>
#include <iostream>

#include "imparr.h"
#include "logic.h"

int main(int argc, char **argv)
{
    if (argc < 2) {
        std::cout << "No function specified. Stop." << std::endl;
        return 0;
    }

    ta::imp_array arr(argv[1]);
    auto min = arr.minimize();
    for (const auto& imp : min) {
        std::cout 
            << std::right << std::hex << std::uppercase
            << std::setw(3) << imp.value() 
            << " | "
            << std::left << std::hex << std::uppercase
            << std::setw(3) << imp.patch_value()
            << std::endl;
    }
}

/*
    2 : 5 = 0010 : 0101 = 0011001100000000
    0 : 6 = 0000 : 0110 = 1010101000000000
    0 : B = 0000 : 1011 = 1111000011110000
    2 : C = 0010 : 1100 = 0010001000100010
    --------------------|-----------------
                        | 1111101111110010 - OK!
*/

