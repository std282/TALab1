#pragma once

template <typename IntT>
inline bool is_power_of_2(IntT n)
{
    return (n & (n - 1)) == 0;
}

template <typename IntT>
int count_bits(IntT n)
{
    int count = 0;
    IntT mask = 1;
    for (int i = 0; i < sizeof(IntT)*8; i++) {
        if (mask & n) {
            count++;
        }

        mask <<= 1;
    }

    return count;
}