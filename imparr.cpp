#include "imparr.h"

#include <algorithm>

#include "pow2.h"

namespace ta {

imp_array::imp_array(const std::string & in_str)
{
    auto strsize = in_str.size();
    implicants.reserve(strsize);

    if (!is_power_of_2(strsize)) {
        throw std::runtime_error("input data is incorrect");
    }

    // Узнает степень двойки
    order = count_bits(strsize - 1);

    unsigned count = 0;
    for (char c : in_str) {
        switch (c) {
        case '0':
            break;

        case '-':
        case '1':
            implicants.emplace_back(count);
        }

        count++;
    }
}

std::vector<implicant> imp_array::minimize()
{
    initial_implicants = implicants;

    while (order > 0) {
        iterate();
    }

    exclude();
    
    std::vector<implicant> refugees_vec(refugees.size());
    std::transform(
        refugees.begin(),
        refugees.end(),
        refugees_vec.begin(),
        [] (const implicant& imp) -> implicant {
            return imp;
        });

    return refugees_vec;
}

void imp_array::iterate()
{
    if (implicants.empty()) {
        order--;
        return;
    }

    std::set<implicant> next_order;
    
    for (auto it1 = implicants.begin(); it1 != implicants.end(); ++it1)
    for (auto it2 = std::next(it1); it2 != implicants.end(); ++it2) {
        switch (is_patchable(*it1, *it2)) {
        case patchability::none:
            continue;

        case patchability::left:
            next_order.insert(implicant::patch(*it1, *it2));
            break;

        case patchability::right:
            next_order.insert(implicant::patch(*it2, *it1));
            break;
        }
    }

    for (const auto& imp : implicants) {
        if (!imp.is_patched()) {
            refugees.insert(imp);
        }
    }

    implicants.resize(next_order.size());
    std::transform(
        next_order.begin(),
        next_order.end(),
        implicants.begin(),
        [] (const implicant& imp) -> implicant {
            return imp;
        });

    order--;
}

void imp_array::exclude()
{
    std::vector<std::vector<bool>> containment_table;
    containment_table.resize(implicants.size());
    for (auto& imp : containment_table) {
        imp.resize(initial_implicants.size());
    }

    
}

}