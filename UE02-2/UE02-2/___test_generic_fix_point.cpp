#include "fix_point.hpp"
#include <cassert>
#include <cmath>
#include <iostream>

using namespace std;


template< typename NumberType >
void test( float f1 = 6.375f , float f2 = -4.0f )
{
    using fix_point_t = NumberType;

    const fix_point_t fp1( f1 );
    const fix_point_t fp2 = f2;

    // ----------------------------------------------------------
    // integral and fractional parts

//    cout << floor(fp1) << endl;
//    cout << std::floor(f1) << endl;
//    cout << endl;

    assert( floor(fp1) ==  std::floor(f1) );
    assert( fp1.frac() ==  fix_point_t( f1 - std::floor(f1) ) );
    assert( frac(fp1)  ==  fix_point_t( f1 - std::floor(f1) ) );


    assert( floor(fp2) ==  std::floor(f2) );
    assert( fp2.frac() ==  fix_point_t( f2 - std::floor(f2) ) );
    assert( frac(fp2)  ==  fix_point_t( f2 - std::floor(f2) ) );

    // ----------------------------------------------------------
    // comparison and ordering
    assert( fp1 == f1 );
    assert( fp2 != fp1 );
    assert( fp2 < fp1  );
    assert( fp1 > fp2  );
    assert( fp2 <= fp1 );
    assert( fp1 >= fp2 );
    assert( fp1 <= fix_point_t(f1) );
    assert( fp1 >= fix_point_t(f1) );


    float df = 1.f / float(1 << (NumberType::post_point_bits-1));

    // ----------------------------------------------------------
    // arithmetics

//    cout << "###### fix_point<" << NumberType::pre_point_bits << ", " << NumberType::post_point_bits << ">";
//    cout << ", f1: " << f1 << ", f2: " << f2 << " ######" << endl;
//    cout << "fp1        : " << fp1 << endl;
//    cout << "fp2        : " << fp2 << endl;
//    cout << "fp1 + fp2  : " << fp1 + fp2 << endl;
//    cout << "fp(f1 + f2): " << fix_point_t( f1+f2 ) << endl;
//    cout << "f1 + f2    : " << f1+f2 << endl;
//    cout << endl;

    // TODO comment back in ---------------------------->
//    assert( fp1 + fp2 == fix_point_t( f1+f2 ) );
//    assert( fp1 - fp2 == fix_point_t( f1-f2 ) );
//    assert( fp1 * fp2 == fix_point_t( f1*f2 ) );
    // <-------------------------------------------------

//    cout << NumberType::post_point_bits << endl;
//    cout << fix_point_t(df).m_data << endl;
//    cout << fix_point_t(df) << endl;
//    cout << endl;

//    cout << (fp2) << endl;
//    cout << fix_point_t(f2-df*100) << endl;
//    cout << (fp1 / fp2) << endl;
//    cout << fix_point_t( f1/f2-df ) << endl;
//    cout << fix_point_t(f1/f2+df) << endl;
//    cout << (fp1 / fp2 >  fix_point_t( f1/f2-df )) << endl;
//    cout << (fp1 / fp2 <  fix_point_t(f1/f2+df)) << endl;
//    cout << endl;

    assert( fp1 / fp2 >  fix_point_t( f1/f2-df )  &&   fp1/fp2 < fix_point_t(f1/f2+df) );

    // ----------------------------------------------------------
    // arithmetics assignment

//    fix_point_t fp33 = fp1;
//    cout << "###### fix_point<" << NumberType::pre_point_bits << ", " << NumberType::post_point_bits << ">";
//    cout << ", fp33: " << fp33 << ", fp2: " << fp2 << " ######" << endl;
//    cout << "fp33       : " << fp33 << endl;
//    cout << "fp2        : " << fp2 << endl;
//    fp33 += fp2;
//    cout << "fp33 += fp2: " << fp33 << endl;
//    cout << "f1 + f2    : " << f1+f2 << endl;
//    cout << "fp(f1 + f2): " << fix_point_t(f1+f2) << endl;
//    cout << endl;


    fix_point_t
    fp3 = fp1;  fp3 += fp2;     assert( fp3 == fix_point_t(f1+f2) );
    fp3 = fp1;  fp3 -= fp2;     assert( fp3 == fix_point_t(f1-f2) );
    fp3 = fp1;  fp3 *= fp2;     assert( fp3 == fix_point_t(f1*f2) );
    fp3 = fp1;  fp3 /= fp2;     assert( fp3 >  fix_point_t(f1/f2-df)  &&  fp3 < fix_point_t(f1/f2+df) );

    // ----------------------------------------------------------
    // pre/post - increment/decrement
    fp3 = fp1;  assert( ++fp3 == f1+1.f );
    fp3 = fp1;  assert( --fp3 == f1-1.f );
    fp3 = fp1;  assert( fp3++ == f1 );  assert( fp3 == f1+1.f  );
    fp3 = fp1;  assert( fp3-- == f1 );  assert( fp3 == f1-1.f  );
}


int main()
{
    test< fix_point<16,16> >();
    test< fix_point<8,24>  >();
    test< fix_point<27,5>  >();
    test< fix_point<7,9>   >();
    test< fix_point<16,16> >( 3.7, 2.3 );
//    test< fix_point<16,16> >( 3.7, 2.25 ); // for debuggin -> another val
//    test< fix_point<4,4>   >( 3.7 , 2.3 );
//    test< fix_point<4,4>   >( 3.7 , 2.25 ); // for debuggin -> another val

    cout << "pow: " << fix_point<8, 8>(3.f).pow(4) << endl;
    cout << "sin(pi/2): " << sin(fix_point<16, 16>(3.14159f/2.f)) << endl;
    cout << "sin(1)   : " << sin(fix_point<16, 16>(1.f)) << endl;
    cout << "cos(pi/2): " << cos(fix_point<16, 16>(3.14159f/2.f)) << endl;
    cout << "cos(0)   : " << cos(fix_point<16, 16>(0.f)) << endl;

    cout << "done" << endl;
}
