#include <cstdint>

#ifndef FIX_POINT_H
#define FIX_POINT_H


template<int N> struct round_up_pow2 { static const int value = round_up_pow2<N+1>::value; };
template<> struct round_up_pow2<8> { static const int value = 8; };
template<> struct round_up_pow2<16> { static const int value = 16; };
template<> struct round_up_pow2<32> { static const int value = 32; };


template<int N> struct int_type_for {};
template<> struct int_type_for<8> { using type = std::int8_t; using doubletype = std::int16_t; };
template<> struct int_type_for<16> { using type = std::int16_t; using doubletype = std::int32_t; };
template<> struct int_type_for<32> { using type = std::int32_t; using doubletype = std::int64_t; };


struct intern {};

template<int L, int R>
class fix_point {
public:
    static const int pre_point_bits = L;
    static const int post_point_bits = R;

//    fix_point(); // standard constructor?
    fix_point(float f);
    fix_point(double d);

    fix_point operator=(float f);
    bool operator==(fix_point other) const;
    bool operator==(float other) const;
    bool operator==(double other) const;
    bool operator!=(fix_point other) const;
    bool operator<(fix_point other) const;
    bool operator>(fix_point other) const;
    bool operator<=(fix_point other) const;
    bool operator>=(fix_point other) const;
    fix_point operator+(fix_point other) const;
    fix_point operator+=(fix_point other);
    fix_point operator-(fix_point other) const;
    fix_point operator-=(fix_point other);
    fix_point operator*(fix_point other) const;
    fix_point operator*=(fix_point other);
    fix_point operator/(fix_point other) const;
    fix_point operator/=(fix_point other);
    operator float() const;
//    operator int() const; // FIXME comment back in when everything works -- provokes ambiguous overload
    float floor() const;
    float frac() const;
    fix_point operator++();
    fix_point operator++(int);
    fix_point operator--();
    fix_point operator--(int);
    fix_point operator-() const;
    fix_point operator%(fix_point other) const;
    fix_point operator%=(fix_point other);
    fix_point pow(int exp) const;
private:
    static const int Q = post_point_bits; // number of bits of the fractional part
    static const int Q_ONE = 1 << post_point_bits; // 1 expressed as 2**Q

    static const int bits = round_up_pow2<L + R>::value;
    using Type = typename int_type_for<bits>::type;
    using DoubleType = typename int_type_for<bits>::doubletype;

    Type m_data;
    fix_point(Type data, intern flag);
};

template<int L, int R> float floor(fix_point<L, R> value);
template<int L, int R> float frac(fix_point<L, R> value);
template<int L, int R> fix_point<L, R> sin(fix_point<L, R> x);
template<int L, int R> fix_point<L, R> cos(fix_point<L, R> x);


#include "fix_point.tpp"


#endif // FIX_POINT_H
