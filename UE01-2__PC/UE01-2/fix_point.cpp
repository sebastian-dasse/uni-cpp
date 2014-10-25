//#include <cstdint>
#include <iostream> // TODO not used here?
#include "fix_point.hpp"

static const int Q = 16; // number of bits of the fractional part
static const int Q_ONE = 1 << Q; // 1 expressed as 2**Q

fix_point::fix_point(float f)
    : m_data(std::int32_t(f * Q_ONE)) {}

fix_point::fix_point(double f)
    : m_data(std::int32_t(f * Q_ONE)) {}

fix_point::fix_point(std::int32_t data)
    : m_data(data) {}

//-- not necessary?
fix_point fix_point::operator =(float f) {
    return fix_point(f);
}

bool fix_point::operator==(fix_point other) const {
    return m_data == other.m_data;
}

bool fix_point::operator==(float other) const {
    return float(*this) == other;
}

bool fix_point::operator==(double other) const {
    return float(*this) == other;
}

bool fix_point::operator!=(fix_point other) const {
//    return m_data != other.m_data;
    return !(*this == other);
}

bool fix_point::operator<(fix_point other) const {
    return m_data < other.m_data;
}

bool fix_point::operator>(fix_point other) const {
    return other.m_data < m_data;
}

bool fix_point::operator<=(fix_point other) const {
    return !(m_data > other.m_data);
}

bool fix_point::operator>=(fix_point other) const {
    return !(m_data < other.m_data);
}

fix_point fix_point::operator+(fix_point other) const {
//    return fix_point(m_data + other.m_data);
    return fix_point(m_data) += other;
}

fix_point fix_point::operator-(fix_point other) const {
//    return fix_point(m_data - other.m_data);
    return fix_point(m_data) -= other;
}

fix_point fix_point::operator*(fix_point other) const {
//    std::int64_t tmp = std::int64_t(m_data) * std::int64_t(other.m_data);
//    return fix_point(std::int32_t(tmp >> Q));
    return fix_point(m_data) *= other;
}

fix_point fix_point::operator/(fix_point other) const {
//    std::int64_t tmp = std::int64_t(m_data) << Q;
//    std::int64_t result = tmp / std::int64_t(other.m_data);
//    return fix_point(std::int32_t(result));
    return fix_point(m_data) /= other;
}

fix_point fix_point::operator+=(fix_point other) {
    return m_data += other.m_data;
}

fix_point fix_point::operator-=(fix_point other) {
    return m_data -= other.m_data;
}

fix_point fix_point::operator*=(fix_point other) {
    std::int64_t tmp = std::int64_t(m_data) * std::int64_t(other.m_data);

//    // TODO ok ???
//    tmp += (1 << (Q-1)); // round up mid values

    return m_data = std::int32_t(tmp >> Q);
}

fix_point fix_point::operator/=(fix_point other) {
    std::int64_t tmp = std::int64_t(m_data) << Q;
    std::int64_t result = tmp / std::int64_t(other.m_data);

//    // TODO ok ???
//    tmp += other.m_data / 2; // round up mid values

    return m_data = std::int32_t(result);
}

fix_point::operator float() const {
    return float(m_data) / Q_ONE;
}

float fix_point::to_float() const {
    return float(m_data) / Q_ONE;
}

fix_point::operator int() const {
    return float(m_data / Q_ONE);
}

float fix_point::floor() const {
    return float(m_data / Q_ONE);
}

float fix_point::frac() const {
    if (m_data < 0) {
        return float(-m_data & 0xffff) / Q_ONE;
    }
    return float(m_data & 0xffff) / Q_ONE;
}

fix_point fix_point::operator++() {
    return m_data += Q_ONE;
}

fix_point fix_point::operator--() {
    return m_data -= Q_ONE;
}

fix_point fix_point::operator++(int) {
    fix_point tmp = fix_point(m_data);
    m_data += Q_ONE;
    return tmp;
}

fix_point fix_point::operator--(int) {
    fix_point tmp = fix_point(m_data);
    m_data -= Q_ONE;
    return tmp;
}

fix_point fix_point::operator-() {
    return -m_data;
}



//static fix_point pi = fix_point(3.1415926536f);
static fix_point pi = fix_point(3.14159f);
static fix_point pi_half = pi * fix_point(0.5f);
static fix_point three_times_pi_half = pi * fix_point(1.5f);
static fix_point two_times_pi = pi * fix_point(2.f);

static fix_point fac[] = {
    { std::int32_t(1 << Q) },
    { std::int32_t(1 << Q) },
    { std::int32_t(2 << Q) },
    { std::int32_t(6 << Q) },
    { std::int32_t(24 << Q) },
    { std::int32_t(120 << Q) },
    { std::int32_t(720 << Q) },
    { std::int32_t(5040 << Q) },
    { std::int32_t(40320 << Q) },
    { std::int32_t(362880 << Q) },
    { std::int32_t(3628800 << Q) },
    { std::int32_t(39916800 << Q) },
    { std::int32_t(479001600 << Q) }

//    fix_point(1.f),
//    fix_point(1.f),
//    fix_point(2.f),
//    fix_point(6.f),
//    fix_point(24.f),
//    fix_point(120.f),
//    fix_point(720.f),
//    fix_point(5040.f),
//    fix_point(40320.f),
//    fix_point(362880.f),
//    fix_point(3628800.f),
//    fix_point(39916800.f),
//    fix_point(479001600.f)
};

static std::int32_t fac_int[] = {
    1,
    1,
    2,
    6,
    24,
    120,
    720,
    5040,
    40320,
    362880,
    3628800,
    39916800,
    479001600
};

int fact(int x) {
    int f = 1;
    for (int i = 1; i <= x; i++) {
        f *= i;
    }
    return f;
}

fix_point sin(fix_point x) {
    // TODO check if x inside [0, pi]

    if (x > pi_half) {
        return sin(pi - x);
    } else if (x > pi) {
        return -sin(x - pi);
    } else if (x > three_times_pi_half) {
        return -sin(two_times_pi - x);
    }
//    if (x > pi) return -sin(x - pi);

//    std::int64_t tmp = x.m_data
    auto result = x
                - x * x * x / fac[3]
                + x * x * x * x * x / fac[5]
                - x * x * x * x * x * x * x / fac[7]
                /*+ x * x * x * x * x * x * x * x * x / fac[9]
                - x * x * x * x * x * x * x * x * x / fac[11]*/;

//    std::int64_t x_ = x.m_data;

//    auto x0 = x;
//    auto x1 = x * x / fix_point(2.f * 3.f);
//    auto x2 = x * x / fix_point(4.f * 5.f);
//    auto x3 = x * x / fix_point(6.f * 7.f);
//    auto x4 = x * x / fix_point(8.f * 9.f);
//    auto x5 = x * x / fix_point(10.f * 11.f);

//    auto result = x0
//                - x0 * x1
//                + x0 * x1 * x2
//                - x0 * x1 * x2 * x3
//                + x0 * x1 * x2 * x3 * x4
//                - x0 * x1 * x2 * x3 * x4 * x5;

    return result;
}

fix_point cos(fix_point x) {
    // TODO
//    return fix_point(-1.f);

//    auto result = fac_int[0]
//                /*- x * x / fac_int[2]
//                + x * x * x * x / fac_int[4]
//                - x * x * x * x * x * x / fac_int[6]
//                + x * x * x * x * x * x * x * x / fac_int[8]
//                - x * x * x * x * x * x * x * x * x * x / fac_int[10]*/;

    auto x0 = fix_point(1.f);
    auto x1 = x * x / fix_point(1.f * 2.f);
    auto x2 = x * x / fix_point(3.f * 4.f);
    auto x3 = x * x / fix_point(5.f * 6.f);
    auto x4 = x * x / fix_point(7.f * 8.f);
    auto x5 = x * x / fix_point(9.f * 10.f);

    auto tmp    = x0
                - x0 * x1
                + x0 * x1 * x2
                - x0 * x1 * x2 * x3
                + x0 * x1 * x2 * x3 * x4
                - x0 * x1 * x2 * x3 * x4 * x5;

    return tmp;
}




float frac(fix_point value) {
    return value.frac();
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
