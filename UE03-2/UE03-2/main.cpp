#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <functional>
#include <string>
#include "fix_point.hpp"

using namespace std;

std::mutex sum_mutex;

//fix_point<16, 16> calculate(std::vector< fix_point<16, 16> >::const_iterator& it1,
//                            std::vector< fix_point<16, 16> >::const_iterator& it2) {
//    return *it1 * *it2;
//}

fix_point<16, 16> dot_product_threads(std::vector< fix_point<16, 16> >& v1, std::vector< fix_point<16, 16> >& v2) {
    if (v1.size() != v2.size()) {
        throw "The vectors have not the same size";
    }
    fix_point<16, 16> result = 0.f;
    for (auto it1 = v1.begin(), it2 = v2.begin(); it1 != v1.end(); it1++, it2++) {
        result += *it1 * *it2;
    }
    return result;
}

void demo1() {

//    auto v = std::vector< fix_point<16, 16> >(10, 123);
//    auto v = std::vector< int >(3, 123);
//    cout << "fp = " << fix_point<16, 16>(123.45f) << endl;

//    for (int i : v) {
//        cout << "fp = " << i << endl;
//    }

//    int count = 0;
//    for (int& i : v) {
//        i += ++count;
//    }


//    for (auto it = v.begin(); it != v.end(); it++) {
//        cout << "fp = " << *it << endl;
//    }


    const int NUM_ELEMENTS = 1 << 16;
//    const int NUM_ELEMENTS = 1 << 16;
    auto v1 = std::vector< fix_point<16, 16> >(NUM_ELEMENTS, 1.f);
//    auto v2 = std::vector< fix_point<16, 16> >(NUM_ELEMENTS, 2.f);
    auto v2 = std::vector< fix_point<16, 16> >(NUM_ELEMENTS, 0.25f);

    cout << "v1.size = " << v1.size() << endl;
    cout << "v2.size = " << v2.size() << endl;
    cout << "*v1.begin() = " << *v1.begin() << endl;
    cout << "*v2.begin() = " << *v2.begin() << endl;

    auto result = dot_product_threads(v1, v2);
    cout << "v1 x v2 = " << result << endl;
}

void f1(fix_point<16, 16>& sum, fix_point<16, 16>& num) {
//    cout << "f1: num:" << num << endl;
//        cout << "f1: num:" << num << " num2: " << num2 << endl;
    sum += num;
}


struct Slice {
    vector< fix_point<16, 16> > data;
    unsigned low;
    unsigned high;
    Slice(vector< fix_point<16, 16> > d, unsigned l, unsigned h): data(d), low(l), high(h) {}
};

void calculate(fix_point<16, 16>& sum, Slice slice) {
    for (int i = slice.low; i < slice.high; i++) {
        sum_mutex.lock();
        sum += slice.data[i];
        cout << i << ": " << slice.data[i] << endl;
//        if (i % 10000 == 0) cout << i << ": " << slice.data[i] << endl;
        sum_mutex.unlock();
    }
}

void demo2() {
    auto numThreads = std::thread::hardware_concurrency();
    fix_point<16, 16> sum = 0.f;

//    int NUM = 100000;
    int NUM = 10;
    cout << "NUM = " << NUM << endl;
    auto vec = std::vector< fix_point<16, 16> >(NUM, 0.f);
//    auto vec = std::vector< fix_point<16, 16> >(NUM, 0.0625f);
//    cout << "vec.size = " << vec.size() << endl;
    cout << "------" << endl;
    for(int i = 0; i < NUM; i++) {
//        vec.push_back(float(i+1));
//        vec[i] = (float(i+1)/(10*NUM));
        vec[i] = (float(i+1));
//        cout << "  " << i << ": " << vec[i] << endl;
    }
    cout << "------" << endl;

    auto start = std::chrono::high_resolution_clock::now();

    //---------------------
    numThreads = 4;
    std::thread t1(calculate, std::ref(sum), Slice(vec, 0 * vec.size() / numThreads, 1 * vec.size() / numThreads));
    std::thread t2(calculate, std::ref(sum), Slice(vec, 1 * vec.size() / numThreads, 2 * vec.size() / numThreads));
    std::thread t3(calculate, std::ref(sum), Slice(vec, 2 * vec.size() / numThreads, 3 * vec.size() / numThreads));
    std::thread t4(calculate, std::ref(sum), Slice(vec, 3 * vec.size() / numThreads, 4 * vec.size() / numThreads));
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    //---------------------

//    //---------------------
//    numThreads = 1;
//    auto threads = std::vector<std::thread>();
//    for (int i = 0; i < int(numThreads); i++) {
//        cout << "thread #" << i << " created (" << (i * vec.size() / numThreads) << ", " << ((i+1) * vec.size() / numThreads) << ")" << endl;
//        Slice s(vec, i * vec.size() / numThreads, (i+1) * vec.size() / numThreads);
////        std::thread t(calculate, std::ref(sum), std::ref(s));
////        threads.push_back(t);
////        t.join();

//        threads.push_back(std::thread(calculate, std::ref(sum), std::ref(s)));
//    }

////    int count = 1;
////    for (auto& t : threads) {
////        t.join();
////        cout << "joining #" << count << endl;
////        count++;
////    }

//    for (int i = 0; i < int(numThreads); i++) {
//        cout << "joining #" << i << endl;
//        threads[i].join();
//    }
//    //---------------------


    cout << "sum: " << sum << endl;

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    cout << "elapsed_milliseconds: " << elapsed_milliseconds << endl;
    auto elapsed_nanoseconds = (end - start).count();
    cout << "elapsed_nanoseconds: " << elapsed_nanoseconds << endl;

    cout << "<<<< demo 2 >>>>" << endl;
}

int main() {
    cout << "<<<< let's begin! >>>>" << endl;
//    auto start = std::chrono::high_resolution_clock::now();
//    demo1();
    demo2();

//    auto end = std::chrono::high_resolution_clock::now();
//    auto elapsed_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//    cout << "elapsed_milliseconds: " << elapsed_milliseconds << endl;
//    auto elapsed_nanoseconds = (end - start).count();
//    cout << "elapsed_nanoseconds: " << elapsed_nanoseconds << endl;
    cout << "<<<< done. >>>>" << endl;
    return 0;
}
