#include "implicant.h"
#include "pow2.h"

namespace ta {

implicant::implicant(unsigned num) :
    number(num),
    index(count_bits(num)),
    patch_bits(0),
    was_patched(false)
{
}

implicant implicant::patch(implicant& more, implicant& less)
{
    auto patch_new_bits = more.number ^ less.number;
    implicant patched(less);
    patched.patch_bits = less.patch_bits | patch_new_bits;
    patched.was_patched = false;

    more.was_patched = true;
    less.was_patched = true;

    return patched;
}

unsigned implicant::value() const
{
    return number;
}

unsigned implicant::patch_value() const
{
    return patch_bits;
}

bool implicant::operator==(const implicant & imp) const
{
    return imp.number == number
        && imp.patch_bits == patch_bits;
}

bool implicant::operator<(const implicant& imp) const
{
    if (patch_bits < imp.patch_bits) {
        return true;
    }
    else if (patch_bits > imp.patch_bits) {
        return false;
    }
    else {
        return number < imp.number;
    }
}

bool implicant::is_patched() const
{
    return was_patched;
}

patchability is_patchable(const implicant& a, const implicant& b)
{
    bool is_left =
           a.patch_bits == b.patch_bits
        && a.number > b.number
        && (a.index - b.index) == 1
        && is_power_of_2(a.number - b.number);

    bool is_right =
        a.patch_bits == b.patch_bits
        && a.number < b.number
        && (b.index - a.index) == 1
        && is_power_of_2(b.number - a.number);

    if (is_left && !is_right) {
        return patchability::left;
    }
    else if (!is_left && is_right) {
        return patchability::right;
    }
    else {
        return patchability::none;
    }
}

}