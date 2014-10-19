#include <cstdint>
#include "fix_point.h"

static const int Q = 16; // number of bits of the fractional part
static const int R = 1 << Q; // number of bits of the fractional part

fix_point to_fix_point(float value) {
    return { std::int32_t(value * (1 << Q)) };
};

float to_float(fix_point value) {
    return float(value.data) / (1 << Q);
};

// TODO -> only integer operations allowed
float floor(fix_point value) {
//    float sign = 1;
//    if (value.data & 0x80000000) {
//        sign = -1;
//    }

//    return (float(value.data & 0x7fff0000) / (1 << Q));
    return (float(value.data >> Q));
};

// TODO -> not working correctly
// TODO -> only integer operations allowed
float frac(fix_point value) {
    return (double(value.data & 0xffff) / (1 << Q));
};

bool equals(fix_point lhs, fix_point rhs) {
    return lhs.data == rhs.data;
};

bool less_than(fix_point lhs, fix_point rhs) {
    return lhs.data < rhs.data;
};

//---- prevent over-/underflow
//std::int32_t to_int32_t_with_saturation(std::int64_t n) {
//    if (n > std::int64_t(0x7fffffff)) {
//        n = 0x7fffffff;
//    } else if (n < std::int64_t(-0x7fffffff)) {
//        n = -0x7fffffff;
//    }
//    return std::int32_t(n);
//}

fix_point add(fix_point lhs, fix_point rhs) {
    std::int64_t temp = lhs.data + rhs.data;
    return { std::int32_t(temp) };
//    return { to_int32_t_with_saturation(temp) };
};

fix_point sub(fix_point lhs, fix_point rhs) {
    std::int64_t temp = lhs.data - rhs.data;
    return { std::int32_t(temp) };
//    return { to_int32_t_with_saturation(temp) };
};

fix_point mul(fix_point lhs, fix_point rhs) {
    std::int64_t temp = std::int64_t(lhs.data) * std::int64_t(rhs.data);
//    temp += (1 << (Q-1)); // mid values are rounded up
    return { std::int32_t(temp >> 16) };
};

fix_point div(fix_point lhs, fix_point rhs) {
    std::int64_t temp = std::int64_t(lhs.data) << Q;
//    temp += rhs.data / 2; // mid values are rounded up
    std::int64_t result = temp / std::int64_t(rhs.data);
    return { std::int32_t(result) };
};
