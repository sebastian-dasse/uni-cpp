#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <functional>
#include <string>
#include <cstdio>
#include <utility>
#include <tuple>
#include <future>
#include "fix_point.hpp"

using namespace std;
using fix_point_vec = std::vector< fix_point<16, 16> >;

static const int NUM_ELEMENTS = 1 << 16;

std::mutex sum_mutex;

struct Slice {
    using ite = const fix_point_vec::iterator;
    ite begin1;
    ite begin2;
    ite end1;
    ite end2;
    Slice(ite b1, ite e1, ite b2, ite e2) : begin1(b1), end1(e1), begin2(b2), end2(e2) {}
};


void calc_threads(fix_point<16, 16>& sum, Slice slice) {
    fix_point<16, 16> sliceSum = 0.f;
    for (auto it1 = slice.begin1, it2 = slice.begin2; it1 != slice.end1; it1++, it2++) {
        sliceSum += *it1 * *it2;
    }
    sum_mutex.lock();
    sum += sliceSum;
    sum_mutex.unlock();
}

fix_point<16, 16> dot_product_threads(fix_point_vec& v1, fix_point_vec& v2) {
    const auto numThreads = std::thread::hardware_concurrency();
    fix_point<16, 16> sum(0.f);
//    std::vector<std::thread> threads;
    std::thread threads[numThreads];
    for (int i = 0; i < int(numThreads); i++) {
        int lo = i * v1.size() / numThreads;
        int hi = (i+1) * v1.size() / numThreads;
        Slice slice(v1.begin() + lo,
                    v1.begin() + hi,
                    v2.begin() + lo,
                    v2.begin() + hi);
//        threads.emplace_back( calc_threads, std::ref(sum), slice );
        threads[i] = std::thread(calc_threads, std::ref(sum), slice);
//        cout << "thread #" << i << " created (" << lo << ", " << hi << ")" << endl;
    }

    for (auto &thread: threads) {
        thread.join();
//        cout << "joined #" << i << endl;
    }
//    for (int i = 0; i < int(numThreads); i++) {
//        threads[i].join();
//        cout << "joined #" << i << endl;
//    }
    return sum;
}

fix_point<16, 16> calc_async(Slice slice) {
    fix_point<16, 16> sliceSum = 0.f;
    for (auto it1 = slice.begin1, it2 = slice.begin2; it1 != slice.end1; it1++, it2++) {
        sliceSum += *it1 * *it2;
    }
    return sliceSum;
}

fix_point<16, 16> dot_product_async(fix_point_vec& v1, fix_point_vec& v2) {
    const auto numThreads = std::thread::hardware_concurrency();
    fix_point<16, 16> sum(0.f);
    /*
     * TODO
     */

//    std::vector< std::future< fix_point<16, 16> > > futures;
    std::future< fix_point<16, 16> > futures[numThreads];
    for (int i = 0; i < int(numThreads); i++) {
        int lo = i * v1.size() / numThreads;
        int hi = (i+1) * v1.size() / numThreads;
        Slice slice(v1.begin() + lo,
                    v1.begin() + hi,
                    v2.begin() + lo,
                    v2.begin() + hi);
        futures[i] = std::async(std::launch::async, calc_async, slice);
//        futures.push_back(std::async(std::launch::async, calc_async, slice));
//        futures.emplace_back(std::launch::async, calc_async, slice );
//        cout << "thread #" << i << " created (" << lo << ", " << hi << ")" << endl;
    }

    for (auto &future : futures) {
        sum += future.get();
    }

    return sum;
}

fix_point<16, 16> executeClocked(std::function<fix_point<16, 16>(fix_point_vec&, fix_point_vec&)> func,
                                 fix_point_vec v1,
                                 fix_point_vec v2) {
    const auto start = std::chrono::high_resolution_clock::now();

    const auto result = func(v1, v2);

    const auto end = std::chrono::high_resolution_clock::now();
    const auto elapsed_nanoseconds = (end - start).count();
//    cout << "elapsed nanoseconds: " << elapsed_nanoseconds << endl;
    cout << "elapsed microseconds: " << elapsed_nanoseconds/1000 << endl;
//    cout << "elapsed milliseconds: " << elapsed_nanoseconds/1000000 << endl;

    return result;
}

int main() {
    cout << "<<<< let's begin! >>>>\n" << endl;

    const auto vec1 = std::vector< fix_point<16, 16> >(NUM_ELEMENTS, 0.5f);
    const auto vec2 = std::vector< fix_point<16, 16> >(NUM_ELEMENTS, 0.25f);

    cout << "-- threads calculation --" << endl;
    auto result1 = executeClocked(dot_product_threads, vec1, vec2);
    cout << "result = " << result1 << endl;

    cout << endl;

    cout << "-- async calculation --" << endl;
    auto result2 = executeClocked(dot_product_async, vec1, vec2);
    cout << "result = " << result2 << endl;

    cout << "\n<<<< done. >>>>" << endl;
    return 0;
}
