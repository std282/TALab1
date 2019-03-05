#include "imparr.h"

#include <algorithm>

#include "minimize.h"
#include "pow2.h"

namespace ta {

imp_array::imp_array(const std::string & in_str)
{
    init(in_str);
}

void imp_array::init(const std::string & in_str)
{
    auto strsize = in_str.size();
    implicants.reserve(strsize);

    if (!is_power_of_2(strsize)) {
        throw std::runtime_error("incorrect input data");
    }

    // Узнает степень двойки
    func_order = func_order_original = count_bits(strsize - 1);

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

    while (func_order > 0) {
        iterate();
    }

    refugees_vec.resize(refugees.size());
    std::transform(
        refugees.begin(),
        refugees.end(),
        refugees_vec.begin(),
        [](const implicant& imp) -> implicant {
        return imp;
    });

    exclude();
    return refugees_vec;
}

int imp_array::order() const
{
    return func_order_original;
}

void imp_array::iterate()
{
    if (implicants.empty()) {
        func_order--;
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

    func_order--;
}

void imp_array::exclude()
{
    mintable original(initial_implicants, refugees_vec);
    minimize_ftor minimize(original);
    mintable minimized = minimize();
    refugees_vec = minimized.get_deads();
}

}