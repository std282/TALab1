#include <fstream>
#include <iomanip>
#include <iostream>

#include "imparr.h"
#include "logic.h"

const char *input_file  = "Scale.txt";
const char *output_file = "mdnf.txt";

const char variable_names[] = {
    'x', 'y', 'z', 'u', 'v', 'w', 'p', 'q', 's', 't'
};

int main(int argc, char **argv)
{
    ta::imp_array arr;

    try {
        switch (argc) {
        case 1: {
            std::string func;
            std::ifstream file(input_file);
            std::getline(file, func);
            arr.init(func);
            break;
        }

        default:
            arr.init(argv[1]);
        }
    }
    catch (const std::exception& ex) {
        std::cout << "error: " << ex.what() << std::endl;
        return 0;
    }
    
    auto min = arr.minimize();

    std::ofstream out(output_file);
    
    auto order = arr.order();
    if (static_cast<size_t>(order) >= std::size(variable_names)) {
        std::cout << "error: order is too big" << std::endl;
    }

    for (int i = 0; i < order; i++) {
        out << variable_names[i];
    }

    out << std::endl;


    for (const auto& imp : min) {
        auto value = imp.value();
        auto patch = imp.patch_value();

        decltype(value) mask = 1 << (order - 1);
        for (int i = 0; i < order; i++) {
            if (patch & mask) {
                out << '-';
            }
            else {
                out << (value & mask ? '1' : '0');
            }

            mask >>= 1;
        }

        out << std::endl;
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

