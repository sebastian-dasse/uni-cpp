#include <cstdint>
#include "fix_point.h"

static const int Q = 16;

fix_point to_fix_point(float value) {
    return { std::int32_t(value * (1 << Q)) };
};

float to_float(fix_point value) {
    return float(value.data) / (1 << Q);
};

// TODO -> only integer operations allowed
float floor(fix_point value) {
    float sign = 1;
    if (value.data & 0x80000000) {
        sign = -1;
    }

    return (float(value.data & 0x7fff0000) / (1 << Q));
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

fix_point add(fix_point lhs, fix_point rhs) {
    std::int64_t temp = lhs.data + rhs.data;
    if (temp > std::int64_t(0x7fffffff)) {
        temp = 0x7fffffff;
    } else if (temp < std::int64_t(-0x7fffffff)) {
        temp = -0x7fffffff;
    }
    return { std::int32_t(temp) };
};

// TODO -> prevent over-/underflow
fix_point sub(fix_point lhs, fix_point rhs) {
    std::int64_t temp = lhs.data - rhs.data;
    return { std::int32_t(temp) };
};

// TODO -> prevent over-/underflow
fix_point mul(fix_point lhs, fix_point rhs) {
    std::int64_t temp = lhs.data * rhs.data;
    return { std::int32_t(temp) };
};

// TODO -> prevent over-/underflow and division by zero
fix_point div(fix_point lhs, fix_point rhs) {
    std::int64_t temp = lhs.data / rhs.data;
    return { std::int32_t(temp) };
};
