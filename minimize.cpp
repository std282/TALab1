#include "minimize.h"

#include <algorithm>

namespace ta {

presentation_table::presentation_table()
{
    // default constructor
}

presentation_table::presentation_table(size_t size) :
    is_present(size, false)
{
}

void presentation_table::resize(size_t size)
{
    this->is_present.resize(size, false);
}

void presentation_table::set_present(int i)
{
    this->is_present[i] = true;
}

void presentation_table::disjunct_with(const presentation_table& table)
{
    std::transform(
        this->is_present.begin(), // вход 1
        this->is_present.end(),   // вход 1 (конец)
        table.is_present.begin(), // вход 2
        this->is_present.begin(), // выход
        [] (bool x, bool y) { return x || y; }
    );
}

bool presentation_table::is_equal_to(const presentation_table& table)
{
    return std::equal(
        this->is_present.begin(),
        this->is_present.end(),
        table.is_present.begin()
    );
}

} // ta
