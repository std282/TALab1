#include "minimize.h"

#include <algorithm>

namespace ta {

void mintable::init(
    const std::vector<uint32_t>& imps,
    const std::vector<uint32_t>& deads)
{
    implicants = imps;
    dead_ends  = deads;

    presence_table.resize(deads.size());
    for (auto& row : presence_table) {
        row.resize(imps.size(), false);
    }

    for (size_t i = 0; i < deads.size(); i++)
    for (size_t j = 0; j < imps.size();  j++) {
        if (deads[i] & imps[j] == deads[i]) {
            presence_table[i][j] = true;
        }
    }
}

std::vector<bool> mintable::compute_disjunction() const
{
    std::vector<bool> disj(implicants.size(), false);
    
    for (const auto& row : presence_table) {
        std::transform(
            row.begin(),  // вход 1
            row.end(),    // вход 1 (конец)
            disj.begin(), // вход 2 
            disj.begin(), // выход
            [] (bool a, bool b) { return a || b; });
    }

    return disj;
}

int mintable::rows() const
{
    return dead_ends.size();
}

void mintable::remove_row(int pos)
{
    if (pos >= dead_ends.size()) {
        throw std::out_of_range("table row position is out of range");
    }

    dead_ends.erase(dead_ends.begin() + pos);
    presence_table.erase(presence_table.begin() + pos);
}

mintable minimize_ftor::operator()()
{
    original_disjunction = original_table.compute_disjunction();
    actual_minimizer(original_table);
    
    return minimized_table;
}

void minimize_ftor::actual_minimizer(const mintable& table)
{
    for (int i = 0; i < table.rows(); i++) {
        auto new_table = table;
        new_table.remove_row(i);
        auto new_disj = new_table.compute_disjunction();

        if (new_disj == original_disjunction) {
            if (new_table.rows() < minimized_table.rows()) {
                minimized_table = new_table;
            }

            actual_minimizer(new_table);
        }
    }
}

}