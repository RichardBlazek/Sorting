#include <cstdint>
#include <limits>
#include <type_traits>

using iptr = std::intptr_t;
using uptr = std::uintptr_t;
using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using i8 = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;

template<typename Return, typename... Args>
using fn = Return(&)(Args...);

template<typename Int>
constexpr void counting_sort(Int* array, uptr length)
{
    using UInt = std::make_unsigned_t<Int>;
    constexpr iptr max = std::numeric_limits<Int>::max(), min = std::numeric_limits<Int>::min();

    uptr counts[max - min] = {0};
    for (uptr i = 0; i < length; ++i)
    {
        ++counts[UInt(array[i] - min)];
    }
    uptr i = 0;
    for (UInt value = 0; i < length; ++value)
    {
        for (uptr count = counts[value]; count > 0; --count, ++i)
        {
            array[i] = Int(value + min);
        }
    }
}

// Generic radix sort
// Time complexity O(n+r)
// Space complexity O(n+r)
template<typename TinyInt, typename Value, fn<TinyInt, Value> Proj>
void radix_sort(Value* array, uptr length, Value* tmp)
{
    constexpr iptr max = std::numeric_limits<TinyInt>::max(), min = std::numeric_limits<TinyInt>::min();
    constexpr uptr range = max - min, last_index = max - min - 1;

    uptr counts[range] = {0};
    uptr starts[range] = {0};

    for (uptr i = 0; i < length; ++i)
    {
        ++counts[Proj(array[i])];
        tmp[i] = (Value&&)array[i];
    }
    for (uptr value = 0; value < last_index; ++value)
    {
        starts[value + 1] = starts[value] + counts[value];
    }
    
    for (uptr i = 0; i < length; ++i)
    {
        TinyInt key = Proj(tmp[i]);
        array[starts[key]] = (Value&&)tmp[i];
        ++starts[key];
    }
}

template<typename TinyInt, typename Int, u8 shift>
constexpr inline TinyInt slice_int(Int num)
{
    using UInt = std::make_unsigned_t<Int>;
    constexpr UInt min = std::numeric_limits<Int>::min();

    return TinyInt((UInt(num) + min) >> shift);
}

void radix_sort(u16* array, uptr length)
{
    u16* tmp = new u16[length];
    radix_sort<u8, u16, slice_int<u8, u16, 0>>(array, length, tmp);
    radix_sort<u8, u16, slice_int<u8, u16, 8>>(array, length, tmp);
    delete[] tmp;
}

void radix_sort(i16* array, uptr length)
{
    i16* tmp = new i16[length];
    radix_sort<u8, i16, slice_int<u8, i16, 0>>(array, length, tmp);
    radix_sort<u8, i16, slice_int<u8, i16, 8>>(array, length, tmp);
    delete[] tmp;
}

void radix_sort(u32* array, uptr length)
{
    u32* tmp = new u32[length];
    radix_sort<u8, u32, slice_int<u8, u32, 0>>(array, length, tmp);
    radix_sort<u8, u32, slice_int<u8, u32, 8>>(array, length, tmp);
    radix_sort<u8, u32, slice_int<u8, u32, 16>>(array, length, tmp);
    radix_sort<u8, u32, slice_int<u8, u32, 24>>(array, length, tmp);
    delete[] tmp;
}

void radix_sort(i32* array, uptr length)
{
    i32* tmp = new i32[length];
    radix_sort<u8, i32, slice_int<u8, i32, 0>>(array, length, tmp);
    radix_sort<u8, i32, slice_int<u8, i32, 8>>(array, length, tmp);
    radix_sort<u8, i32, slice_int<u8, i32, 16>>(array, length, tmp);
    radix_sort<u8, i32, slice_int<u8, i32, 24>>(array, length, tmp);
    delete[] tmp;
}

void radix_sort(u64* array, uptr length)
{
    u64* tmp = new u64[length];
    radix_sort<u16, u64, slice_int<u16, u64, 0>>(array, length, tmp);
    radix_sort<u16, u64, slice_int<u16, u64, 16>>(array, length, tmp);
    radix_sort<u16, u64, slice_int<u16, u64, 32>>(array, length, tmp);
    radix_sort<u16, u64, slice_int<u16, u64, 48>>(array, length, tmp);
    delete[] tmp;
}

void radix_sort(i64* array, uptr length)
{
    i64* tmp = new i64[length];
    radix_sort<u16, i64, slice_int<u16, i64, 0>>(array, length, tmp);
    radix_sort<u16, i64, slice_int<u16, i64, 16>>(array, length, tmp);
    radix_sort<u16, i64, slice_int<u16, i64, 32>>(array, length, tmp);
    radix_sort<u16, i64, slice_int<u16, i64, 48>>(array, length, tmp);
    delete[] tmp;
}
