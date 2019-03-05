#pragma once

#include <vector>

namespace ta {

class mintable {
public:
    mintable()                           = default;
    mintable(const mintable&)            = default;
    mintable& operator=(const mintable&) = default;

    inline mintable(const std::vector<uint32_t>& imps,
                    const std::vector<uint32_t>& deads)
    {
        init(imps, deads);
    }

    void init(const std::vector<uint32_t>& imps,
              const std::vector<uint32_t>& deads);

    std::vector<bool> compute_disjunction() const;
    int rows() const;
    void remove_row(int pos);

private:
    template <typename T>
    using matrix_2d = std::vector<std::vector<T>>;

    std::vector<uint32_t> implicants;
    std::vector<uint32_t> dead_ends;
    matrix_2d<bool>       presence_table;
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