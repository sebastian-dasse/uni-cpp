#include <iostream>
#include <cstdint>
#include <cmath>
#include <cassert>
#include "fix_point.hpp"

using namespace std;

int main()
{
    float fl1 = -3.0125f;
    float fl2 = 2.0125f;
//    float fl2 = 9234.5678f;

//    fix_point fp1 = fix_point(fl1);
//    fix_point fp2 = fix_point(fl2);
    fix_point fp1 = fl1;
    fix_point fp2 = fl2;

    cout << "starting... "<< endl;
    cout << fp1.to_float() << endl;
    cout << fp2.to_float() << endl;
    cout << (fp1 == fp1) << endl;
    cout << (fp1 == fp2) << endl;
    cout << (fp1 != fp1) << endl;
    cout << (fp1 != fp2) << endl;
    cout << endl;
    cout << (fp1 < fp1) << endl;
    cout << (fp1 < fp2) << endl;
    cout << (fp2 < fp1) << endl;
    cout << (fp1 > fp1) << endl;
    cout << (fp1 > fp2) << endl;
    cout << (fp2 > fp1) << endl;
    cout << endl;
    cout << (fp1 <= fp1) << endl;
    cout << (fp1 <= fp2) << endl;
    cout << (fp2 <= fp1) << endl;
    cout << (fp1 >= fp1) << endl;
    cout << (fp1 >= fp2) << endl;
    cout << (fp2 >= fp1) << endl;
    cout << endl;
//    cout << (fp1 + fp1).to_float() << endl;
//    cout << (fp1 + fp2).to_float() << endl;
//    cout << (fp2 + fp2).to_float() << endl;
//    fp1 += fp1;
//    cout << fp1.to_float() << endl;
//    fp2 += fp1;
//    cout << fp2.to_float() << endl;
//    cout << endl;
    cout << (fp1 * fp1).to_float() << endl;
    cout << (fp1 * fp2).to_float() << endl;
    cout << (fp2 * fp2).to_float() << endl;
    auto ret = fp1 += fp2;
    cout << fp1.to_float() << endl;
    cout << fp1.floor() << endl;
    cout << fp1.frac() << endl;
    cout << ret.to_float() << endl;
    cout << endl;
    fix_point fp3 = 29.2f;
//    fix_point fp3 = 29;
//    fix_point fp3 = 29*(1 << 16);
    cout << fp3.to_float() << endl;
    ++fp3;
    cout << fp3.to_float() << endl;
    --fp3;
    cout << fp3.to_float() << endl;
    fp3--;
    cout << fp3.to_float() << endl;
    auto test = fp3--;
    cout << fp3.to_float() << endl;
    cout << test.to_float() << endl;
    cout << endl;


//    assert( sin(fix_point(0.5f)) == fix_point(sin(0.5f)) );
//    assert( cos(fix_point(0.5f)) == fix_point(cos(0.5f)) );

    cout << ":: " << fact(3) << endl;
//    cout << ":: " << 6227020800.f << endl;
    cout << ": " << sin(fix_point(0.5f)).to_float() << endl;
    cout << ": " << fix_point(sin(0.5f)).to_float() << endl;
//    cout << ": " << cos(fix_point(0.5f)).to_float() << endl;
//    cout << ": " << fix_point(cos(0.5f)).to_float() << endl;

    float pi = 3.14159;
    float v0 = .0f + 0.2f;
    float v1 = pi * 0.5f + 0.2f;
    float v2 = pi + 0.2f;
    float v3 = pi * 1.5f + 0.2f;

//    cout << sin(fix_point(0.5f)).to_float() << endl;
//    cout << sin(0.5f) << endl;
    cout << endl;
    cout << "-- sin --" << endl;
    cout << sin(v0) << endl;
    cout << sin(v1) << endl;
    cout << sin(v2) << endl;
    cout << sin(v3) << endl;
    cout << endl;
    cout << sin(fix_point(v0)).to_float() << endl;
    cout << sin(fix_point(v1)).to_float() << endl;
    cout << sin(fix_point(v2)).to_float() << endl;
    cout << sin(fix_point(v3)).to_float() << endl;
    cout << endl;

    cout << "-- cos--" << endl;
    cout << cos(v0) << endl;
    cout << cos(v1) << endl;
    cout << cos(v2) << endl;
    cout << cos(v3) << endl;
    cout << endl;
    cout << cos(fix_point(v0)).to_float() << endl;
    cout << cos(fix_point(v1)).to_float() << endl;
    cout << cos(fix_point(v2)).to_float() << endl;
    cout << cos(fix_point(v3)).to_float() << endl;
    cout << endl;

//    cout << fp1 << endl;
//    cout << fp1.m_data << endl;
    cout << "done"<< endl;

    return 0;
}

