#include <algorithm>
#include "doctest.h"
#include "bubblesorter.hpp"
#include "quicksorter.hpp"

#define SORTERS BubbleSorter, QuickSorter

TEST_CASE_TEMPLATE("Test sorter with custom array", Sorter, SORTERS) {
    int array[] = {5, 3, 1, 2, 4};
    Sorter::sort(array, 5);
    CHECK_EQ(array[0], 1);
    CHECK_EQ(array[1], 2);
    CHECK_EQ(array[2], 3);
    CHECK_EQ(array[3], 4);
    CHECK_EQ(array[4], 5);
}

TEST_CASE_TEMPLATE("Test sorter with singleton array", Sorter, SORTERS) {
    int array[] = {1};
    Sorter::sort(array, 1);
    CHECK_EQ(array[0], 1);
}

TEST_CASE_TEMPLATE("Test sorter with array sorted in reverse order", Sorter, SORTERS) {
    int array[] = {5, 4, 3, 2, 1};
    Sorter::sort(array, 5);
    CHECK_EQ(array[0], 1);
    CHECK_EQ(array[1], 2);
    CHECK_EQ(array[2], 3);
    CHECK_EQ(array[3], 4);
    CHECK_EQ(array[4], 5);
}

TEST_CASE_TEMPLATE("Test sorter with array, which is already sorted", Sorter, SORTERS) {
    int array[] = {1, 2, 3, 4, 5};
    Sorter::sort(array, 5);
    CHECK_EQ(array[0], 1);
    CHECK_EQ(array[1], 2);
    CHECK_EQ(array[2], 3);
    CHECK_EQ(array[3], 4);
    CHECK_EQ(array[4], 5);
}

TEST_CASE_TEMPLATE("Test sorter with 10000 random elements", Sorter, SORTERS) {
    const int N = 10000;
    int array[N];
    for (int i = 0; i < N; i++)
        array[i] = rand();
    Sorter::sort(array, N);
    CHECK(std::is_sorted(std::begin(array), std::end(array)));
}
