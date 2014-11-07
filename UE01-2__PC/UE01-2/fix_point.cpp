//#include <cstdint>
#include "fix_point.hpp"

static const int Q = 16; // number of bits of the fractional part
static const int Q_ONE = 1 << Q; // 1 expressed as 2**Q
static const fix_point ZERO = fix_point(0.f);
static const fix_point ONE = fix_point(1.f);
static const fix_point PI = fix_point(3.14159f);
static const fix_point PI_HALF = PI * fix_point(0.5f);
static const fix_point THREE_TIMES_PI_HALF = PI * fix_point(1.5f);
static const fix_point TWO_TIMES_PI = PI * fix_point(2.f);

fix_point::fix_point(float f)
    : m_data(std::int32_t(f * Q_ONE)) {}

fix_point::fix_point(double f)
    : m_data(std::int32_t(f * Q_ONE)) {}

fix_point::fix_point(std::int32_t data)
    : m_data(data) {}

fix_point fix_point::operator=(float f) {
    return fix_point(f);
}

bool fix_point::operator==(fix_point other) const {
    return m_data == other.m_data;
}

bool fix_point::operator==(float other) const {
    return *this == fix_point(other);
}

bool fix_point::operator==(double other) const {
    return *this == float(other);
}

bool fix_point::operator!=(fix_point other) const {
    return !(*this == other);
}

bool fix_point::operator<(fix_point other) const {
    return m_data < other.m_data;
}

bool fix_point::operator>(fix_point other) const {
    return other < *this;
}

bool fix_point::operator<=(fix_point other) const {
    return !(*this > other);
}

bool fix_point::operator>=(fix_point other) const {
    return !(*this < other);
}

fix_point fix_point::operator+(fix_point other) const {
    return fix_point(m_data) += other;
}

fix_point fix_point::operator+=(fix_point other) {
    return m_data += other.m_data;
}

fix_point fix_point::operator-(fix_point other) const {
    return fix_point(m_data) -= other;
}

fix_point fix_point::operator-=(fix_point other) {
    return m_data -= other.m_data;
}

fix_point fix_point::operator*(fix_point other) const {
    return fix_point(m_data) *= other;
}

fix_point fix_point::operator*=(fix_point other) {
    return m_data = std::int32_t( (std::int64_t(m_data) * std::int64_t(other.m_data)) >> Q );
}

fix_point fix_point::operator/(fix_point other) const {
    return fix_point(m_data) /= other;
}

fix_point fix_point::operator/=(fix_point other) {
    return m_data = std::int32_t( (std::int64_t(m_data) << Q) / std::int64_t(other.m_data) );
}

fix_point::operator float() const {
    return float(m_data) / Q_ONE;
}

fix_point::operator int() const {
    return int(m_data / Q_ONE);
}

float fix_point::floor() const {
    return float(m_data / Q_ONE);
}

float fix_point::frac() const {
    return float( (m_data < 0 ? -m_data : m_data) & 0xffff ) / Q_ONE;
}

fix_point fix_point::operator++() {
    return m_data += Q_ONE;
}

fix_point fix_point::operator++(int) {
    fix_point tmp = fix_point(m_data);
    m_data += Q_ONE;
    return tmp;
}

fix_point fix_point::operator--() {
    return m_data -= Q_ONE;
}

fix_point fix_point::operator--(int) {
    fix_point tmp = fix_point(m_data);
    m_data -= Q_ONE;
    return tmp;
}

fix_point fix_point::operator-() {
    return -m_data;
}

fix_point fix_point::operator%(fix_point other) const {
    return fix_point(m_data) %= other.m_data;
}

fix_point fix_point::operator%=(fix_point other) {
    return m_data %= other.m_data;
}

fix_point fix_point::pow(int exp) const {
    if (exp == 0) {
        return ONE;
    }
    return exp < 0 ? ONE / this->pow(-exp) : *this * this->pow(exp-1);
}


float floor(fix_point value) {
    return value.floor();
}

float frac(fix_point value) {
    return value.frac();
}


constexpr int fac(int n) {
    return n <= 1 ? 1 : n * fac(n-1);
}

fix_point taylor(fix_point x, int max, int offset) {
    fix_point res = ZERO;
    for (int i = 0; i < max; i++) {
        int exp = 2*i + offset;
        fix_point sig = (i % 2 == 0) ? ONE : ZERO - ONE;
        res += sig * x.pow(exp) / fix_point(float(fac(exp)));
    }
    return res;
}

fix_point sin(fix_point x) {
    x %= TWO_TIMES_PI;
    if (x < ZERO) {
        return sin(TWO_TIMES_PI + x);
    }
    if (PI_HALF < x && x <= PI) {
        return sin(PI - x);
    }
    if (PI < x && x <= THREE_TIMES_PI_HALF) {
        return -sin(x - PI);
    }
    if (THREE_TIMES_PI_HALF < x && x <= TWO_TIMES_PI) {
        return -sin(TWO_TIMES_PI - x);
    }
    return taylor(x, 4, 1);
}

fix_point cos(fix_point x) {
    x %= TWO_TIMES_PI;
    if (x < ZERO) {
        return cos(TWO_TIMES_PI + x);
    }
    if (PI_HALF < x && x <= PI) {
        return -cos(PI - x);
    }
    if (PI < x && x <= THREE_TIMES_PI_HALF) {
        return -cos(x - PI);
    }
    if (THREE_TIMES_PI_HALF < x && x <= TWO_TIMES_PI) {
        return cos(TWO_TIMES_PI - x);
    }
    return taylor(x, 4, 0);
}
