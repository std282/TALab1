#pragma once

#include <vector>

#include "implicant.h"

namespace ta {

class mintable {
public:
    mintable()                           = default;
    mintable(const mintable&)            = default;
    mintable& operator=(const mintable&) = default;

    inline mintable(const std::vector<implicant>& imps,
                    const std::vector<implicant>& deads)
    {
        init(imps, deads);
    }

    void init(const std::vector<implicant>& imps,
              const std::vector<implicant>& deads);

    std::vector<bool> compute_disjunction() const;
    int rows() const;
    void remove_row(int pos);

	std::vector<implicant> get_deads() const;

private:
    template <typename T>
    using matrix_2d = std::vector<std::vector<T>>;

    std::vector<implicant> implicants;
    std::vector<implicant> dead_ends;
    matrix_2d<bool>        presence_table;
};

class minimize_ftor {
public:
    inline minimize_ftor(const mintable& table)
    {
        minimized_table = original_table = table;
    }

    mintable operator()();

private:
    void actual_minimizer(const mintable& table);

    mintable original_table;
    mintable minimized_table;
    std::vector<bool> original_disjunction;
};

}