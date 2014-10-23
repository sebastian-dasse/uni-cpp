#include <iostream>
#include <cstdint>
#include "fix_point.h"

using namespace std;

int main()
{
    float fl1 = 3.0125f;
    float fl2 = -2.0125f;
//    float fl2 = 9234.5678f;

    fix_point fp1 = fix_point(fl1);
    fix_point fp2 = fix_point(fl2);

    cout << "starting... "<< endl;
    cout << (fp1 == fp1) << endl;
    cout << (fp1 == fp2) << endl;
    cout << endl;
    cout << (fp1 < fp1) << endl;
    cout << (fp1 < fp2) << endl;
    cout << (fp2 < fp1) << endl;
    cout << (fp1 <= fp1) << endl;
    cout << (fp1 <= fp2) << endl;
    cout << (fp2 <= fp1) << endl;
    cout << endl;
    cout << (fp1 > fp1) << endl;
    cout << (fp1 > fp2) << endl;
    cout << (fp2 > fp1) << endl;
    cout << (fp1 >= fp1) << endl;
    cout << (fp1 >= fp2) << endl;
    cout << (fp2 >= fp1) << endl;
    cout << endl;
    cout << (fp1 + fp1).to_float() << endl;
    cout << (fp1 + fp2).to_float() << endl;
    cout << (fp2 + fp2).to_float() << endl;
    fp1 += fp1;
    cout << fp1.to_float() << endl;
    fp2 += fp1;
    cout << fp2.to_float() << endl;
    cout << endl;
    cout << (fp1 * fp1).to_float() << endl;
    cout << (fp1 * fp2).to_float() << endl;
    cout << (fp2 * fp2).to_float() << endl;
    fp1 *= fp1;
    cout << fp1.to_float() << endl;
    cout << fp1.floor() << endl;
    cout << fp1.frac() << endl;
    cout << endl;

//    cout << fp1 << endl;
//    cout << fp1.m_data << endl;
    cout << "done"<< endl;

    return 0;
}

