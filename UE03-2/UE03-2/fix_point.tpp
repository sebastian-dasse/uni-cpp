#include <cmath>
#include "fix_point.hpp"


//-- QUESTION: is there any way to have constants in template classes? --
//static const int Q = 16; // number of bits of the fractional part
//static const int Q_ONE = 1 << Q; // 1 expressed as 2**Q
////static const fix_point ZERO = fix_point(0.f);
////static const fix_point ONE = fix_point(1.f);
////static const fix_point PI = fix_point(3.14159f);
////static const fix_point PI_HALF = PI * fix_point(0.5f);
////static const fix_point THREE_TIMES_PI_HALF = PI * fix_point(1.5f);
////static const fix_point TWO_TIMES_PI = PI * fix_point(2.f);

// standard constructor?
template<int L, int R>
fix_point<L, R>::fix_point()
    : m_data(0) {}

template<int L, int R>
fix_point<L, R>::fix_point(float f)
    : m_data(Type(round(f * Q_ONE))) {}

template<int L, int R>
fix_point<L, R>::fix_point(double f)
    : m_data(Type(round(f * Q_ONE))) {}

template<int L, int R>
fix_point<L, R>::fix_point(Type data, intern flag)
    : m_data(data) {}

template<int L, int R>
fix_point<L, R> fix_point<L, R>::operator=(float f) {
    m_data = Type(round(f * Q_ONE));
    return *this;
}

template<int L, int R>
bool fix_point<L, R>::operator==(fix_point other) const {
    return m_data == other.m_data;
}

template<int L, int R>
bool fix_point<L, R>::operator==(float other) const {
    return *this == fix_point(other);
}

template<int L, int R>
bool fix_point<L, R>::operator==(double other) const {
    return *this == float(other);
}

template<int L, int R>
bool fix_point<L, R>::operator!=(fix_point other) const {
    return !(*this == other);
}

template<int L, int R>
bool fix_point<L, R>::operator<(fix_point other) const {
    return m_data < other.m_data;
}

template<int L, int R>
bool fix_point<L, R>::operator>(fix_point other) const {
    return other < *this;
}

template<int L, int R>
bool fix_point<L, R>::operator<=(fix_point other) const {
    return !(*this > other);
}

template<int L, int R>
bool fix_point<L, R>::operator>=(fix_point other) const {
    return !(*this < other);
}

template<int L, int R>
fix_point<L, R> fix_point<L, R>::operator+(fix_point other) const {
    return fix_point(m_data, intern()) += other;
}

template<int L, int R>
fix_point<L, R> fix_point<L, R>::operator+=(fix_point other) {
    m_data += other.m_data;
    return *this;
}

template<int L, int R>
fix_point<L, R> fix_point<L, R>::operator-(fix_point other) const {
    return fix_point(m_data, intern()) -= other;
}

template<int L, int R>
fix_point<L, R> fix_point<L, R>::operator-=(fix_point other) {
    m_data -= other.m_data;
    return *this;
}

template<int L, int R>
fix_point<L, R> fix_point<L, R>::operator*(fix_point other) const {
    return fix_point(m_data, intern()) *= other;
}

template<int L, int R>
fix_point<L, R> fix_point<L, R>::operator*=(fix_point other) {
    m_data = Type( (DoubleType(m_data) * DoubleType(other.m_data)) >> Q );
    return *this;
}

template<int L, int R>
fix_point<L, R> fix_point<L, R>::operator/(fix_point<L, R> other) const {
    return fix_point(m_data, intern()) /= other;
}

template<int L, int R>
fix_point<L, R> fix_point<L, R>::operator/=(fix_point<L, R> other) {
    m_data = Type( (DoubleType(m_data) << Q) / DoubleType(other.m_data) );
    return *this;
}

template<int L, int R>
fix_point<L, R>::operator float() const {
    return float(m_data) / Q_ONE;
}

// FIXME comment back in when everything works -- provokes ambiguous overload
//template<int L, int R>
//fix_point<L, R>::operator int() const {
//    return int(m_data / Q_ONE);
//}

template<int L, int R>
float fix_point<L, R>::floor() const {
    return float(m_data / Q_ONE);
}

template<int L, int R>
float fix_point<L, R>::frac() const {
    return float( (m_data < 0 ? -m_data : m_data) & (Q_ONE - 1) ) / Q_ONE;
}

template<int L, int R>
fix_point<L, R> fix_point<L, R>::operator++() {
    m_data += Q_ONE;
    return *this;
}

template<int L, int R>
fix_point<L, R> fix_point<L, R>::operator++(int) {
    fix_point tmp = fix_point(m_data, intern());
    m_data += Q_ONE;
    return tmp;
}

template<int L, int R>
fix_point<L, R> fix_point<L, R>::operator--() {
    m_data -= Q_ONE;
    return *this;
}

template<int L, int R>
fix_point<L, R> fix_point<L, R>::operator--(int) {
    fix_point tmp = fix_point(m_data, intern());
    m_data -= Q_ONE;
    return tmp;
}

template<int L, int R>
fix_point<L, R> fix_point<L, R>::operator-() const {
    return fix_point(-m_data, intern());
}

template<int L, int R>
fix_point<L, R> fix_point<L, R>::operator%(fix_point other) const {
    return fix_point(m_data, intern()) %= other;
}

template<int L, int R>
fix_point<L, R> fix_point<L, R>::operator%=(fix_point other) {
    m_data %= other.m_data;
    return *this;
}

template<int L, int R>
fix_point<L, R> fix_point<L, R>::pow(int exp) const {
    const auto ONE = fix_point<L, R>(1.f);
    if (exp == 0) {
        return ONE;
    }
    return exp < 0 ? ONE / this->pow(-exp) : *this * this->pow(exp-1);
}


template<int L, int R>
float floor(fix_point<L, R> value) {
    return value.floor();
}

template<int L, int R>
float frac(fix_point<L, R> value) {
    return value.frac();
}


constexpr int fac(int n) {
    return n <= 1 ? 1 : n * fac(n-1);
}

template<int L, int R>
fix_point<L, R> taylor(fix_point<L, R> x, int max, int offset) {
    const auto ZERO = fix_point<L, R>(0.f);
    const auto ONE = fix_point<L, R>(1.f);
    fix_point<L, R> res = ZERO;
    for (int i = 0; i < max; i++) {
        int exp = 2*i + offset;
        fix_point<L, R> sig = (i % 2 == 0) ? ONE : ZERO - ONE;
        res += sig * x.pow(exp) / fix_point<L, R>(float(fac(exp)));
    }
    return res;
}

template<int L, int R>
fix_point<L, R> sin(fix_point<L, R> x) {
    const auto ZERO = fix_point<L, R>(0.f);
    const auto PI = fix_point<L, R>(3.14159f);
    const auto PI_HALF = PI * fix_point<L, R>(0.5f);
    const auto THREE_TIMES_PI_HALF = PI * fix_point<L, R>(1.5f);
    const auto TWO_TIMES_PI = PI * fix_point<L, R>(2.f);

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

template<int L, int R>
fix_point<L, R> cos(fix_point<L, R> x) {
    const auto ZERO = fix_point<L, R>(0.f);
    const auto PI = fix_point<L, R>(3.14159f);
    const auto PI_HALF = PI * fix_point<L, R>(0.5f);
    const auto THREE_TIMES_PI_HALF = PI * fix_point<L, R>(1.5f);
    const auto TWO_TIMES_PI = PI * fix_point<L, R>(2.f);

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
