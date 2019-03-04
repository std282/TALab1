#include "logic.h"

#include <algorithm>
#include <fstream>
#include <stdexcept>

#include "imparr.h"
#include "pow2.h"

ta::imp_array read_input(const std::string& filename)
{
    std::ifstream input(filename);
    if (!input.is_open()) {
        throw std::runtime_error("file doesn't exist");
    }

    std::string raw;
    std::getline(input, raw);

    return ta::imp_array(raw);
}
