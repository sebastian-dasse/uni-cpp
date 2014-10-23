#include <cstdint>
#include "fix_point.h"

static const int Q = 16; // number of bits of the fractional part
static const int R = 1 << Q; // number of bits of the fractional part

fix_point::fix_point(float data)
    : m_data(std::int32_t(data * (1 << Q))) {}

fix_point::fix_point(std::int32_t data)
    : m_data(data) {}

bool fix_point::operator==(fix_point other) {
    return m_data == other.m_data;
}

bool fix_point::operator<(fix_point other) {
    return m_data < other.m_data;
}

bool fix_point::operator<=(fix_point other) {
    return m_data <= other.m_data;
}

bool fix_point::operator>(fix_point other) {
    return m_data > other.m_data;
}

bool fix_point::operator>=(fix_point other) {
    return m_data >= other.m_data;
}

fix_point fix_point::operator+(fix_point other) {
    return fix_point(m_data + other.m_data);
}

fix_point fix_point::operator-(fix_point other) {
    return fix_point(m_data - other.m_data);
}

fix_point fix_point::operator*(fix_point other) {
    std::int64_t temp = std::int64_t(m_data) * std::int64_t(other.m_data);
    return fix_point(std::int32_t(temp >> Q));
}

fix_point fix_point::operator/(fix_point other) {
    std::int64_t temp = std::int64_t(m_data) << Q;
    std::int64_t result = temp / std::int64_t(other.m_data);
    return fix_point(std::int32_t(result));
}

void fix_point::operator+=(fix_point other) {
    m_data += other.m_data;
}

void fix_point::operator-=(fix_point other) {
    m_data -= other.m_data;
}

void fix_point::operator*=(fix_point other) {
    std::int64_t temp = std::int64_t(m_data) * std::int64_t(other.m_data);
    m_data = std::int32_t(temp >> 16);
}

void fix_point::operator/=(fix_point other) {
    std::int64_t temp = std::int64_t(m_data) << Q;
    std::int64_t result = temp / std::int64_t(other.m_data);
    m_data = std::int32_t(result);
}

float fix_point::to_float() {
    return float(m_data) / (1 << Q);
}

float fix_point::floor() {
    return float(m_data / (1 << Q));
}

float fix_point::frac() {
    // correct results for negative values
    if (m_data < 0) {
        return float(-m_data & 0xffff) / (1 << Q);
    }
    return float(m_data & 0xffff) / (1 << Q);
}


////---- prevent over-/underflow
////std::int32_t to_int32_t_with_saturation(std::int64_t n) {
////    if (n > std::int64_t(0x7fffffff)) {
////        n = 0x7fffffff;
////    } else if (n < std::int64_t(-0x7fffffff)) {
////        n = -0x7fffffff;
////    }
////    return std::int32_t(n);
////}
