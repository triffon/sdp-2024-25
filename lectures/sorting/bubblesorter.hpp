#ifndef __BUBBLESORTER_HPP
#define __BUBBLESORTER_HPP

#include <utility>

class BubbleSorter {
public:
    static void sort(int array[], int n) {
        for (int i = 0; i < n - 1; i++) {
            for (int j = n - 2; j >= 0; j--) {
                if (array[j] > array[j + 1])
                    std::swap(array[j], array[j + 1]);
            }
        }
    }
};

#endif