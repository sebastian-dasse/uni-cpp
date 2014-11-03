//#include <cstdint>
#include "fix_point.h"

static const int Q = 16; // number of bits of the fractional part
static const int Q_ONE = 1 << Q; // 1 expressed as 2**Q

fix_point to_fix_point(float value) {
    return { std::int32_t(value * Q_ONE) };
}

float to_float(fix_point value) {
    return float(value.data) / Q_ONE;
}

float floor(fix_point value) {
    return float(value.data / Q_ONE);
}

float frac(fix_point value) {
    return float( (value.data < 0 ? - value.data : value.data) & 0xffff ) / Q_ONE;
}

bool equals(fix_point lhs, fix_point rhs) {
    return lhs.data == rhs.data;
}

bool less_than(fix_point lhs, fix_point rhs) {
    return lhs.data < rhs.data;
}

fix_point add(fix_point lhs, fix_point rhs) {
    return { std::int32_t(lhs.data + rhs.data) };
}

fix_point sub(fix_point lhs, fix_point rhs) {
    return { std::int32_t(lhs.data - rhs.data) };
}

fix_point mul(fix_point lhs, fix_point rhs) {
    return { std::int32_t( (std::int64_t(lhs.data) * std::int64_t(rhs.data)) >> Q ) };
}

fix_point div(fix_point lhs, fix_point rhs) {
    return { std::int32_t( (std::int64_t(lhs.data) << Q) / std::int64_t(rhs.data) ) };
}
