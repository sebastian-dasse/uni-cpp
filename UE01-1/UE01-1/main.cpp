#include <iostream>
#include <cstdint>
#include "fix_point.h"

using namespace std;

int main()
{
    cout << "Hello World!" << endl;
//    cout << (7 * (1 << 16) * 3 * (1 << 16)) << endl;
//    cout << sizeof(std::int32_t) << endl;
//    cout << sizeof(std::int64_t) << endl;
//    cout << sizeof(float) << endl;
//    cout << (171 / 16) << endl;
//    cout << (171 >> 4) << endl;
//    std::int32_t res = (1.23 * (double) (1 << 16));
//    res >>= 16;
//    cout << res << endl;
//    res = (int) 0xffff0000 + 0xffff;
//    res = (int) 0xffff - 0ff;
//    res = (1 << 16)-1;
//    res >>= 16;
//    cout << res << endl;
//    cout << (1 << 16) << endl;

    float fl = -123.456f;
    fix_point fp = to_fix_point(fl);
    fix_point fp2 = to_fix_point(9234.5678f);
    fix_point fp3 = to_fix_point(7);
//    fix_point fp4 = to_fix_point(3);
    fix_point fp4 = to_fix_point(-3.2);

    cout << "float        = " << fl << endl;
    cout << "fp.data      = " << fp.data << endl;
    cout << "to_float(fp) = " << to_float(fp) << endl;
    cout << "floor(fp)    = " << floor(fp) << endl;
    cout << "frac(fp)     = " << frac(fp) << endl;

    cout << "to_float(fp) = " << to_float(fp) << endl;
    cout << "to_float(fp2) = " << to_float(fp2) << endl;

//    cout << "equals(fp, fp)  = " << equals(fp, fp) << endl;
//    cout << "equals(fp, fp2) = " << equals(fp, fp2) << endl;
//    cout << "equals(fp2, fp) = " << equals(fp2, fp) << endl;

//    cout << "less_than(fp, fp)  = " << less_than(fp, fp) << endl;
//    cout << "less_than(fp, fp2) = " << less_than(fp, fp2) << endl;
//    cout << "less_than(fp2, fp) = " << less_than(fp2, fp) << endl;

    cout << "fp3.data = " << fp3.data << endl;
    cout << "fp4.data = " << fp4.data << endl;
    cout << "to_float(fp3) = " << to_float(fp3) << endl;
    cout << "to_float(fp4) = " << to_float(fp4) << endl;

    cout << "to_float(add(fp3, fp4)) = " << to_float(add(fp3, fp4)) << endl;
    cout << "to_float(sub(fp3, fp4)) = " << to_float(sub(fp3, fp4)) << endl;
    cout << "to_float(mul(fp3, fp4)) = " << to_float(mul(fp3, fp4)) << endl;
    cout << "to_float(div(fp3, fp4)) = " << to_float(div(fp3, fp4)) << endl;

    const fix_point fpx = to_fix_point(-4.0f);
    cout << "floor(fpx) = " << floor(fpx) << endl;


    const fix_point fp01 = to_fix_point(6.375f);
    const fix_point fp02 = to_fix_point(-4.0f);

    cout << to_float(div(fp01, fp02)) << endl;
    cout << -1.59375f << endl;

    cout << to_float(mul(fp01, fp02)) << endl;
    cout << -25.5f << endl;

    return 0;
}

