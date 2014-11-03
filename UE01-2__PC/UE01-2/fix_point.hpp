#include <cstdint>

#ifndef FIX_POINT_H
#define FIX_POINT_H


struct fix_point {
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
    operator int() const;
    float floor() const;
    float frac() const;
    fix_point operator++();
    fix_point operator++(int);
    fix_point operator--();
    fix_point operator--(int);
    fix_point operator-();
    fix_point operator%(fix_point other) const;
    fix_point operator%=(fix_point other);
    fix_point pow(int exp) const;
private:
    std::int32_t m_data;
    fix_point(std::int32_t data);
};


fix_point sin(fix_point x);
fix_point cos(fix_point x);

float frac(fix_point value);


#endif // FIX_POINT_H
