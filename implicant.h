#pragma once

#include <cstdint>
#include <stdexcept>

namespace ta {

enum class patchability {
    none,
    left,
    right
};

class implicant {
public:
    implicant() = default;
    implicant(unsigned num);

    static implicant patch(implicant& more, implicant& less);
    friend patchability is_patchable(const implicant& a, const implicant& b);

    unsigned value() const;
    unsigned patch_value() const;
    bool is_patched() const;

    bool operator==(const implicant& imp) const;
    inline bool operator!=(const implicant& imp) const
    {
        return !(*this == imp);
    }

    bool operator<(const implicant& imp) const;


private:
    unsigned number;
    int      index;
    unsigned patch_bits;
    bool     was_patched;
};

class not_patchable : public std::runtime_error {
    not_patchable();
};

patchability is_patchable(const implicant& a, const implicant& b);

}