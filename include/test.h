#ifndef TEST_H
#define TEST_H

#include <vector>
#include <list>
#include <string>
#include <cassert>
#include <map>
#include <fstream>

#include "my_algorithm.h"

void testCopy()
{
    // test copy with contiguous iterator and POD type
    std::vector<int> srcVec{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::vector<int> destVec(srcVec.size());
    my_copy(srcVec.begin(), srcVec.end(), destVec.begin());
    assert(destVec == srcVec);

    // test copy of part of container
    my_copy(srcVec.begin() + 5, srcVec.end() - 2, destVec.begin() + 1);
    assert((destVec == std::vector<int>{ 1, 6, 7, 8, 5, 6, 7, 8, 9, 10 }));

    // test copy with inserter and empty dest
    destVec.clear();
    my_copy(srcVec.begin(), srcVec.end(), std::back_inserter(destVec));
    assert(destVec == srcVec);

    // test copy with inserter and non-empty dest
    destVec = { 1, 2, 3 };
    my_copy(srcVec.begin() + 3, srcVec.end(), std::back_inserter(destVec));
    assert(destVec == srcVec);

    // test copy with contiguous iterator and non-POD type
    std::vector<std::string> srcNonPodVec{ "str1", "str2", "str3", "str4", "str5" };
    std::vector<std::string> destNonPodVec(srcNonPodVec.size());
    my_copy(srcNonPodVec.begin(), srcNonPodVec.end(), destNonPodVec.begin());
    assert(destNonPodVec == srcNonPodVec);

    // test copy with non-contiguous iterator and POD type
    std::list<int> srcList{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::list<int> destList(srcList.size());
    my_copy(srcList.begin(), srcList.end(), destList.begin());
    assert(destList == srcList);

    // test self-copy with contiguous iterator and POD type
    destVec = srcVec;
    my_copy(destVec.begin(), destVec.end(), destVec.begin());
    assert(destVec == srcVec);
    my_copy(destVec.begin() + 3, destVec.end() - 2, destVec.begin() + 3);
    assert(destVec == srcVec);
}

void testTransform()
{
    // test one source range
    std::vector<int> srcVec{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::vector<int> destVec(srcVec.size());
    my_transform(srcVec.begin(), srcVec.end(), destVec.begin(),
        [](const int elem)
        {
            return elem + 10;
        });
    assert((destVec == std::vector<int>{ 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 }));

    // test two source range
    std::vector<int> secondSrcVec = srcVec;
    my_transform(
        destVec.begin(), destVec.end(),
        srcVec.begin(), destVec.begin(),
        [](const int firstElem, const int secondElem)
        {
            return firstElem - secondElem;
        });
    assert((destVec == std::vector<int>(10, 10)));
}

void testMapReduce()
{
    // test sum of squares (using specialization with explicit initial value)
    std::vector<int> numVec{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int sumOfSquares = my_map_reduce(numVec.begin(), numVec.end(), 0,
        [](const int sum, const int elem)
        {
            return sum + elem * elem;
        });
    assert(sumOfSquares == 385);

    std::vector<std::string> stringVec{
        "short",
        "tiny",
        "loooooooooongeeeeeest1",
        "medium",
        "biiiiiiig",
        "loooooooooongeeeeeest2",
        "huuuuuuuuugeeeee"
    };

    // test longest string
    // if there are few longest strings, returns first one
    std::string longestStr = my_map_reduce(stringVec.begin(), stringVec.end(), std::string{},
        [](const std::string& init, const std::string& str)
        {
            return init.size() < str.size() ? str : init;
        });
    assert(longestStr == stringVec[2]);

    // test specialization without explicit reduce function (implicitly std::plus),
    // but with initial value
    double sumWithInitVal = my_map_reduce(numVec.begin(), numVec.end(), 3.14);
    assert(sumWithInitVal == 58.14);

    // test specialization without explicit reduce function and initial value
    int simpleSum = my_map_reduce(numVec.begin(), numVec.end());
    assert(simpleSum == 55);

    // count words in text files
    std::vector<std::string> files{
        "../test_txt_files/1.txt",
        "../test_txt_files/2.txt",
        "../test_txt_files/3.txt"
    };

    std::map<std::string, int> wordsCount = my_map_reduce(files.begin(), files.end(),
        std::map<std::string, int>{}, [](std::map<std::string, int> init, const std::string& file)
        {
            std::ifstream txtFile(file);
            std::string word;
            while (txtFile >> word)
            {
                init[word]++;
            }
            return init;
        });
    assert(wordsCount["Unique"] == 1);
    assert(wordsCount["Lorem"] == 2);
    assert(wordsCount["ipsum"] == 2);
    assert(wordsCount["three_times"] == 3);
}

#endif
