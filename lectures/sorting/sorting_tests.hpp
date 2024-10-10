#include <algorithm>
#include "doctest.h"
#include "bubblesorter.hpp"

TEST_CASE("Test BubbleSorter with custom array") {
    int array[] = {5, 3, 1, 2, 4};
    BubbleSorter::sort(array, 5);
    CHECK_EQ(array[0], 1);
    CHECK_EQ(array[1], 2);
    CHECK_EQ(array[2], 3);
    CHECK_EQ(array[3], 4);
    CHECK_EQ(array[4], 5);
}

TEST_CASE("Test BubbleSorted with singleton array") {
    int array[] = {1};
    BubbleSorter::sort(array, 1);
    CHECK_EQ(array[0], 1);
}

TEST_CASE("Test BubbleSorter with array sorted in reverse order") {
    int array[] = {5, 4, 3, 2, 1};
    BubbleSorter::sort(array, 5);
    CHECK_EQ(array[0], 1);
    CHECK_EQ(array[1], 2);
    CHECK_EQ(array[2], 3);
    CHECK_EQ(array[3], 4);
    CHECK_EQ(array[4], 5);
}

TEST_CASE("Test BubbleSorter with array, which is already sorted") {
    int array[] = {1, 2, 3, 4, 5};
    BubbleSorter::sort(array, 5);
    CHECK_EQ(array[0], 1);
    CHECK_EQ(array[1], 2);
    CHECK_EQ(array[2], 3);
    CHECK_EQ(array[3], 4);
    CHECK_EQ(array[4], 5);
}

TEST_CASE("Test BubbleSorter with 10000 random elements") {
    const int N = 10000;
    int array[N];
    for (int i = 0; i < N; i++)
        array[i] = rand();
    BubbleSorter::sort(array, N);
    CHECK(std::is_sorted(std::begin(array), std::end(array)));
}
