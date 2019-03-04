#pragma once

#include <set>
#include <vector>

#include "implicant.h"

namespace ta {

class imp_array {
public:
    imp_array() = default;
    imp_array(const std::string& in_str);

    std::vector<implicant> minimize();
    
private:
    void iterate();
    void exclude();

    std::vector<implicant> initial_implicants;
    std::vector<implicant> implicants;
    std::set<implicant>    refugees;
    int order;
};

}

