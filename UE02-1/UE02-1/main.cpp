//#include <iostream>
//#include "fix_point_collection.h"
//#include "fix_point.h"

//using namespace std;

//int main()
//{
//// ----> strange
////    fix_point& fpo = *(new fix_point(1.2f));
//    fix_point *afp = new fix_point(1.2f);
//    fix_point& fpo = *afp;
//    cout << float(fpo) << endl;

//    fpo = 4.5f;
//    cout << float(fpo) << endl;

//    fpo = float(4.5f);
//    cout << float(fpo) << endl;

//    fpo = *(new fix_point(3456.f));
//    cout << float(fpo) << endl;
//// <---- strange

//    fix_point_collection fpc = fix_point_collection();
////    cout << float(fpc.pop_back()) << endl; // THROWS EXCEPTION
//    fpc.push_back(1.f);
//    fpc.push_back(2.f);
//    fpc.push_back(3.f);

//    const fix_point_collection cfpc = fpc;
//    cout << float(cfpc[0]) << endl;
//    cout << float(cfpc[1]) << endl;
//    cout << float(cfpc[2]) << endl;
////    cout << float(cfpc[-1]) << endl; // THROWS EXCEPTION

//    cout << "size = " << fpc.size() << endl;
//    cout << float(cfpc[2]) << endl;
//    cout << float(cfpc[fix_point(1.9f)]) << endl;
//    cout << float(fpc[1]) << endl;

////    cfpc[1] = fix_point(17.f); // DOES NOT COMPILE - WHICH IS OK
////    cout << float(cfpc[1]) << endl;
//    fpc[1] = fix_point(17.f); // works
////    fpc[1] = 17.f; // should work, but does not
//    cout << "should be 17 -> " << float(fpc[1]) << endl;

////    sum(&fpc);
//    cout << "sum = " << float(sum(fpc)) << endl;

//    cout << float(fpc.pop_back()) << endl;
//    cout << float(fpc.pop_back()) << endl;
//    cout << float(fpc.pop_back()) << endl;
////    cout << float(fpc.pop_back()) << endl; // THROWS EXCEPTION
//    cout << "size = " << fpc.size() << endl;

//    fpc.push_back(2.2f);
//    fpc.push_back(2.2f);
//    fpc.push_back(2.2f);
//    fpc.push_back(2.2f);
//    fpc.push_back(2.2f);
//    cout << "count = " << float(count_value(fpc, 2.2f)) << endl;

//    cout << "---- done ----" << endl;
//    return 0;
//}

