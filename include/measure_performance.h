#ifndef MEASURE_PERFORMANCE_H
#define MEASURE_PERFORMANCE_H

#include <chrono>
#include <numeric>
#include <vector>
#include <algorithm>

#include "my_algorithm.h"

double measure_pod_my_copy_performance(size_t iters, size_t arrSize)
{
    std::vector<int> vals(arrSize);
    std::vector<int> copiedVals(arrSize);
    std::iota(vals.begin(), vals.end(), 0);

    auto startTime = std::chrono::steady_clock::now();

    for (size_t i = 0; i < iters; i++)
    {
        my_copy(vals.begin(), vals.end(), copiedVals.begin());
    }

    return static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(
        std::chrono::steady_clock::now() - startTime).count()) / 1000.0;
}

double measure_pod_standard_copy_performance(size_t iters, size_t arrSize)
{
    std::vector<int> vals(arrSize);
    std::vector<int> copiedVals(arrSize);
    std::iota(vals.begin(), vals.end(), 0);

    auto startTime = std::chrono::steady_clock::now();

    for (size_t i = 0; i < iters; i++)
    {
        std::copy(vals.begin(), vals.end(), copiedVals.begin());
    }

    return static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(
        std::chrono::steady_clock::now() - startTime).count()) / 1000.0;
}

#endif
