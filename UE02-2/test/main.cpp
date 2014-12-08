#include <iostream>

using namespace std;


template<int x> struct int_type_for {};
template<> struct int_type_for<8> { using type = int8_t; using doubletype = int16_t; };
template<> struct int_type_for<16> { using type = int16_t; using doubletype = int32_t; };
template<> struct int_type_for<32> { using type = int32_t; using doubletype = int64_t; };

template<int L, int R>
class fix_point {
public:
    fix_point(float f) { m_data = static_cast<Type>(f); }
    void printSize() {
        cout << sizeof m_data << endl;
    }
    float getVal() {
        return m_data;
    }

private:
    using Type = typename int_type_for<L + R>::type;
    using DoubleType = typename int_type_for<L + R>::doubletype;
    Type m_data;
};


int main()
{
    cout << "starting" << endl;

    fix_point<5,3> x = fix_point<5,3>(123.456f);
    x.printSize();
    cout << x.getVal() << endl;

    cout << "done" << endl;
    return 0;
}

