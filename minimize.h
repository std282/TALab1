#pragma once

#include <vector>

namespace ta {

class presentation_table {
public:
    presentation_table();
    presentation_table(size_t size);

    void resize(size_t size);
    void set_present(int i);
    void disjunct_with(const presentation_table& table);
    bool is_equal_to(const presentation_table& table);

private:
    std::vector<bool> is_present;
};

}