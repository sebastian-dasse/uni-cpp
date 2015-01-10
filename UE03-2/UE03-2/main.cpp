#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <future>
#include <chrono>
#include <functional>
#include "fix_point.hpp"

using namespace std;
using fix_point_vec = std::vector< fix_point<16, 16> >;

static const int NUM_ELEMENTS = 1 << 16;

std::mutex sum_mutex;

fix_point<16, 16> dot_product_threads(fix_point_vec& v1, fix_point_vec& v2) {
    const auto numThreads = std::thread::hardware_concurrency();
    fix_point<16, 16> sum(0.f);
    std::thread threads[numThreads];
//    std::vector<std::thread> threads;
    for (int i = 0; i < int(numThreads); i++) {
        int lo = i * v1.size() / numThreads;
        int hi = (i+1) * v1.size() / numThreads;
        threads[i] = std::thread([&](int hi, int lo){
//        threads.emplace_back([&](int hi, int lo){
            fix_point<16, 16> sliceSum = 0.f;
            for (auto it1 = v1.begin() + lo, it2 = v2.begin() + lo; it1 != v1.begin() + hi; it1++, it2++) {
                sliceSum += *it1 * *it2;
            }
            sum_mutex.lock();
            sum += sliceSum;
            sum_mutex.unlock();
        }, hi, lo);
    }
    for (auto &thread: threads) {
        thread.join();
    }
    return sum;
}

fix_point<16, 16> dot_product_async(fix_point_vec& v1, fix_point_vec& v2) {
    const auto numThreads = std::thread::hardware_concurrency();
    fix_point<16, 16> sum(0.f);
    std::future< fix_point<16, 16> > futures[numThreads];
//    std::vector< std::future< fix_point<16, 16> > > futures;
    for (int i = 0; i < int(numThreads); i++) {
        int lo = i * v1.size() / numThreads;
        int hi = (i+1) * v1.size() / numThreads;
//        futures.push_back(std::async(std::launch::async, [&](int hi, int lo){
        futures[i] = std::async(std::launch::async, [&](int hi, int lo){
            fix_point<16, 16> sliceSum = 0.f;
            for (auto it1 = v1.begin() + lo, it2 = v2.begin() + lo; it1 != v1.begin() + hi; it1++, it2++) {
                sliceSum += *it1 * *it2;
            }
            return sliceSum;
        }, hi, lo);
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
