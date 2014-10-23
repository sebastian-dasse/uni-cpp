#include <cstdint>

#ifndef FIX_POINT_H
#define FIX_POINT_H

#endif // FIX_POINT_H

struct fix_point {
    fix_point(float f);
    fix_point(std::int32_t data);

    void is(float f);
    bool operator==(fix_point other);
    bool operator<(fix_point other);
    bool operator<=(fix_point other);
    bool operator>(fix_point other);
    bool operator>=(fix_point other);
    fix_point operator+(fix_point other);
    fix_point operator-(fix_point other);
    fix_point operator*(fix_point other);
    fix_point operator/(fix_point other);
    void operator+=(fix_point other);
    void operator-=(fix_point other);
    void operator*=(fix_point other);
    void operator/=(fix_point other);
    float to_float();
    float floor();
    float frac();
    void incrementPre();
    void incrementPost();
    void decrementPre();
    void decrementPost();
private:
    std::int32_t m_data;
};

//fix_point to_fix_point(float value);
//float to_float(fix_point value);

//float floor(fix_point value);
//float frac(fix_point value);

//bool equals(fix_point lhs, fix_point rhs);
//bool less_than(fix_point lhs, fix_point rhs);

//fix_point add(fix_point lhs, fix_point rhs);
//fix_point sub(fix_point lhs, fix_point rhs);
//fix_point mul(fix_point lhs, fix_point rhs);
//fix_point div(fix_point lhs, fix_point rhs);
