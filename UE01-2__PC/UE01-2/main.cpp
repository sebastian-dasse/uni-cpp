//#include <iostream>
//#include <cstdint>
//#include <cmath>
//#include "fix_point.hpp"

//using namespace std;

//int main()
//{
//    cout << "starting... "<< endl;
//    cout << endl;

////    float fl1 = -3.0125f;
////    float fl2 = 2.0125f;
////    fix_point fp1 = fix_point(fl1);
////    fix_point fp2 = fix_point(fl2);
////    fix_point fp1 = fl1;
////    fix_point fp2 = fl2;

////    cout << float(fp1) << endl;
////    cout << float(fp2) << endl;
////    cout << (fp1 == fp1) << endl;
////    cout << (fp1 == fp2) << endl;
////    cout << (fp1 != fp1) << endl;
////    cout << (fp1 != fp2) << endl;
////    cout << endl;
////    cout << (fp1 < fp1) << endl;
////    cout << (fp1 < fp2) << endl;
////    cout << (fp2 < fp1) << endl;
////    cout << (fp1 > fp1) << endl;
////    cout << (fp1 > fp2) << endl;
////    cout << (fp2 > fp1) << endl;
////    cout << endl;
////    cout << (fp1 <= fp1) << endl;
////    cout << (fp1 <= fp2) << endl;
////    cout << (fp2 <= fp1) << endl;
////    cout << (fp1 >= fp1) << endl;
////    cout << (fp1 >= fp2) << endl;
////    cout << (fp2 >= fp1) << endl;
////    cout << endl;
//////    cout << float(fp1 + fp1) << endl;
//////    cout << float(fp1 + fp2) << endl;
//////    cout << float(fp2 + fp2) << endl;
//////    fp1 += fp1;
//////    cout << float(fp1) << endl;
//////    fp2 += fp1;
//////    cout << float(fp2) << endl;
//////    cout << endl;
////    cout << float(fp1 * fp1) << endl;
////    cout << float(fp1 * fp2) << endl;
////    cout << float(fp2 * fp2) << endl;
////    auto ret = fp1 += fp2;
////    cout << float(fp1) << endl;
////    cout << fp1.floor() << endl;
////    cout << fp1.frac() << endl;
////    cout << float(ret) << endl;
////    cout << endl;
////    fix_point fp3 = 29.2f;
//////    fix_point fp3 = 29;
//////    fix_point fp3 = 29*(1 << 16);
////    cout << float(fp3) << endl;
////    ++fp3;
////    cout << float(fp3) << endl;
////    --fp3;
////    cout << float(fp3) << endl;
////    fp3--;
////    cout << float(fp3) << endl;
////    auto test = fp3--;
////    cout << float(fp3) << endl;
////    cout << float(test) << endl;
////    cout << endl;

////    cout << float(pow(fix_point(2.f), -4)) << endl;
////    cout << endl;
////    cout << float(fix_point(17.f) % fix_point(5.f)) << endl;
////    cout << endl;

//    float pi = 3.14159;
//    float v0 =       .0f + 0.2f;
//    float v1 = pi * 0.5f + 0.2f;
//    float v2 = pi        + 0.2f;
//    float v3 = pi * 1.5f + 0.2f;
//    float v4 = pi * 10.f + 0.2f;
//    float v5 = pi * -10.f + 0.2f;

//    cout << "-- sin --" << endl;
//    float sinV0 = sin(v0);
//    float sinV1 = sin(v1);
//    float sinV2 = sin(v2);
//    float sinV3 = sin(v3);
//    float sinV4 = sin(v4);
//    float sinV5 = sin(v5);
//    float sinV0F = sin(fix_point(v0));
//    float sinV1F = sin(fix_point(v1));
//    float sinV2F = sin(fix_point(v2));
//    float sinV3F = sin(fix_point(v3));
//    float sinV4F = sin(fix_point(v4));
//    float sinV5F = sin(fix_point(v5));
//    cout << sinV0 << " " << sinV0F << " " << sinV0 - sinV0F << endl;
//    cout << sinV1 << " " << sinV1F << " " << sinV1 - sinV1F << endl;
//    cout << sinV2 << " " << sinV2F << " " << sinV2 - sinV2F << endl;
//    cout << sinV3 << " " << sinV3F << " " << sinV3 - sinV3F << endl;
//    cout << sinV4 << " " << sinV4F << " " << sinV4 - sinV4F << endl;
//    cout << sinV5 << " " << sinV5F << " " << sinV5 - sinV5F << endl;
//    cout << endl;

//    cout << "-- cos--" << endl;
//    float cosV0 = cos(v0);
//    float cosV1 = cos(v1);
//    float cosV2 = cos(v2);
//    float cosV3 = cos(v3);
//    float cosV4 = cos(v4);
//    float cosV5 = cos(v5);
//    float cosV0F = cos(fix_point(v0));
//    float cosV1F = cos(fix_point(v1));
//    float cosV2F = cos(fix_point(v2));
//    float cosV3F = cos(fix_point(v3));
//    float cosV4F = cos(fix_point(v4));
//    float cosV5F = cos(fix_point(v5));
//    cout << cosV0 << " " << cosV0F << " " << cosV0 - cosV0F << endl;
//    cout << cosV1 << " " << cosV1F << " " << cosV1 - cosV1F << endl;
//    cout << cosV2 << " " << cosV2F << " " << cosV2 - cosV2F << endl;
//    cout << cosV3 << " " << cosV3F << " " << cosV3 - cosV3F << endl;
//    cout << cosV4 << " " << cosV4F << " " << cosV4 - cosV4F << endl;
//    cout << cosV5 << " " << cosV5F << " " << cosV5 - cosV5F << endl;
//    cout << endl;

//    cout << "done"<< endl;

//    return 0;
//}

