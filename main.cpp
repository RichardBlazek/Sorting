#include <iostream>
#include <random>
#include <time.h>
#include "sorts.hpp"

std::mt19937_64 gen64;

template<typename Int>
void fill_random(Int* array, uptr length)
{
    for (uptr i = 0; i < length; ++i)
    {
        i64 value = gen64();
        array[i] = *reinterpret_cast<Int*>(&value);
    }
}

template<typename T, uptr S>
constexpr inline uptr array_size(T (&) [S])
{
    return S;
}

int main()
{
    gen64.seed(time(0));

    i64 values[64] = {0};
    fill_random(values, array_size(values));

    std::cout << "Values:\n";
    for (auto value: values)
    {
        std::cout << +value << "\n";
    }

    radix_sort(values, array_size(values));

    std::cout << "\nSorted:\n";
    for (auto value: values)
    {
        std::cout << +value << "\n";
    }
    std::cout << "\n";

    return 0;
}