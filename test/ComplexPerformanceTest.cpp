#include "doctest.h"
#include <chrono>
#include <iostream>
#include <iomanip>
#include <vector>
#include <random>

#include "../src/Complex.hpp"

using namespace std;
using namespace std::chrono;

// Helper function to generate random complex numbers
Complex random_complex() {
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_real_distribution<double> dis(-2.0, 2.0);
    return Complex{dis(gen), dis(gen)};
}

// Helper function to print timing results
void print_timing(const string& operation, nanoseconds duration, size_t iterations) {
    double avg_ns = static_cast<double>(duration.count()) / iterations;
    cout << fixed << setprecision(2)
         << operation << ": "
         << avg_ns << " ns per operation"
         << " (" << (1000000.0 / avg_ns) << " ops/sec)"
         << endl;
}

TEST_CASE("Performance measurements for Complex operations") {
    const size_t iterations = 1000000;
    vector<Complex> numbers(iterations);
    
    // Generate random numbers
    for (size_t i = 0; i < iterations; ++i) {
        numbers[i] = random_complex();
    }

    // Test squared() operation
    {
        auto start = high_resolution_clock::now();
        for (size_t i = 0; i < iterations; ++i) {
            [[maybe_unused]] auto result = numbers[i].squared();
        }
        auto end = high_resolution_clock::now();
        print_timing("squared()", duration_cast<nanoseconds>(end - start), iterations);
    }

    // Test square_and_add() operation
    {
        auto start = high_resolution_clock::now();
        for (size_t i = 0; i < iterations; ++i) {
            numbers[i].square_and_add(random_complex());
        }
        auto end = high_resolution_clock::now();
        print_timing("square_and_add()", duration_cast<nanoseconds>(end - start), iterations);
    }

    // Test operator+() operation
    {
        auto start = high_resolution_clock::now();
        for (size_t i = 0; i < iterations; ++i) {
            [[maybe_unused]] auto result = numbers[i] + random_complex();
        }
        auto end = high_resolution_clock::now();
        print_timing("operator+()", duration_cast<nanoseconds>(end - start), iterations);
    }

    // Test norm() operation
    {
        auto start = high_resolution_clock::now();
        for (size_t i = 0; i < iterations; ++i) {
            [[maybe_unused]] auto result = numbers[i].norm();
        }
        auto end = high_resolution_clock::now();
        print_timing("norm()", duration_cast<nanoseconds>(end - start), iterations);
    }
} 