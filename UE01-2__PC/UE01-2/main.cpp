#include <iostream>
#include <cstdint>
#include <cmath>
#include "fix_point.hpp"

using namespace std;

int main()
{
    cout << "starting... "<< endl;
    cout << endl;

//    float fl1 = -3.0125f;
//    float fl2 = 2.0125f;
//    fix_point fp1 = fix_point(fl1);
//    fix_point fp2 = fix_point(fl2);
//    fix_point fp1 = fl1;
//    fix_point fp2 = fl2;

//    cout << float(fp1) << endl;
//    cout << float(fp2) << endl;
//    cout << (fp1 == fp1) << endl;
//    cout << (fp1 == fp2) << endl;
//    cout << (fp1 != fp1) << endl;
//    cout << (fp1 != fp2) << endl;
//    cout << endl;
//    cout << (fp1 < fp1) << endl;
//    cout << (fp1 < fp2) << endl;
//    cout << (fp2 < fp1) << endl;
//    cout << (fp1 > fp1) << endl;
//    cout << (fp1 > fp2) << endl;
//    cout << (fp2 > fp1) << endl;
//    cout << endl;
//    cout << (fp1 <= fp1) << endl;
//    cout << (fp1 <= fp2) << endl;
//    cout << (fp2 <= fp1) << endl;
//    cout << (fp1 >= fp1) << endl;
//    cout << (fp1 >= fp2) << endl;
//    cout << (fp2 >= fp1) << endl;
//    cout << endl;
////    cout << float(fp1 + fp1) << endl;
////    cout << float(fp1 + fp2) << endl;
////    cout << float(fp2 + fp2) << endl;
////    fp1 += fp1;
////    cout << float(fp1) << endl;
////    fp2 += fp1;
////    cout << float(fp2) << endl;
////    cout << endl;
//    cout << float(fp1 * fp1) << endl;
//    cout << float(fp1 * fp2) << endl;
//    cout << float(fp2 * fp2) << endl;
//    auto ret = fp1 += fp2;
//    cout << float(fp1) << endl;
//    cout << fp1.floor() << endl;
//    cout << fp1.frac() << endl;
//    cout << float(ret) << endl;
//    cout << endl;
//    fix_point fp3 = 29.2f;
////    fix_point fp3 = 29;
////    fix_point fp3 = 29*(1 << 16);
//    cout << float(fp3) << endl;
//    ++fp3;
//    cout << float(fp3) << endl;
//    --fp3;
//    cout << float(fp3) << endl;
//    fp3--;
//    cout << float(fp3) << endl;
//    auto test = fp3--;
//    cout << float(fp3) << endl;
//    cout << float(test) << endl;
//    cout << endl;

    float pi = 3.14159;
    float v0 =       .0f + 0.2f;
    float v1 = pi * 0.5f + 0.2f;
    float v2 = pi        + 0.2f;
    float v3 = pi * 1.5f + 0.2f;

    cout << "-- sin --" << endl;
    float sinV0 = sin(v0);
    float sinV1 = sin(v1);
    float sinV2 = sin(v2);
    float sinV3 = sin(v3);
    float sinV0F = sin(fix_point(v0));
    float sinV1F = sin(fix_point(v1));
    float sinV2F = sin(fix_point(v2));
    float sinV3F = sin(fix_point(v3));
    cout << sinV0 << " " << sinV0F << " " << sinV0 - sinV0F << endl;
    cout << sinV1 << " " << sinV1F << " " << sinV1 - sinV1F << endl;
    cout << sinV2 << " " << sinV2F << " " << sinV2 - sinV2F << endl;
    cout << sinV3 << " " << sinV3F << " " << sinV3 - sinV3F << endl;
    cout << endl;

    cout << "-- cos--" << endl;
    float cosV0 = cos(v0);
    float cosV1 = cos(v1);
    float cosV2 = cos(v2);
    float cosV3 = cos(v3);
    float cosV0F = cos(fix_point(v0));
    float cosV1F = cos(fix_point(v1));
    float cosV2F = cos(fix_point(v2));
    float cosV3F = cos(fix_point(v3));
    cout << cosV0 << " " << cosV0F << " " << cosV0 - cosV0F << endl;
    cout << cosV1 << " " << cosV1F << " " << cosV1 - cosV1F << endl;
    cout << cosV2 << " " << cosV2F << " " << cosV2 - cosV2F << endl;
    cout << cosV3 << " " << cosV3F << " " << cosV3 - cosV3F << endl;
    cout << endl;

    cout << "done"<< endl;

    return 0;
}

