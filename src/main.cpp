#include <cmath>
#include <iostream>

#include "test.h"
#include "measure_performance.h"

/*
My copy for POD types and contiguous iterators is up to 5 percents slower than standard one
on my machine in release mode because I am using std::memmove to allow copying
into overlapping range instead of std::memcpy
*/

int main()
{
    testCopy();
    std::cout << "Correctness tests for my_copy passed (if run in debug mode)..." << std::endl;
    testTransform();
    std::cout << "Correctness tests for my_transform passed (if run in debug mode)..." << std::endl;
    testMapReduce();
    std::cout << "Correctness tests for my_map_reduce passed (if run in debug mode), measuring performance..." << std::endl;

    size_t iters = 100;
    size_t arrSize = 10000000;

    double myCopyPerformance = measure_pod_my_copy_performance(iters, arrSize);
    double standardCopyPerformance = measure_pod_standard_copy_performance(iters, arrSize);

    std::cout << "My copy performance: " << myCopyPerformance << "ms" << std::endl;
    std::cout << "Standard copy performance: " << standardCopyPerformance << "ms" << std::endl;

    std::cout << "My copy is " << std::round(
        (myCopyPerformance / standardCopyPerformance - 1) * 10000
        ) / 100 << " percents slower than standard" << std::endl;

    return 0;
}
