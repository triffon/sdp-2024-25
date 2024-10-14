#ifndef __ALTERNATIVEQUICKSORTER_HPP
#define __ALTERNATIVEQUICKSORTER_HPP

#include <utility>
#include <concepts>

/// <summary>
/// Ограничение, изискващо типов параметър да имплементира оператора '<'
/// </summary>
template <typename T>
concept IsLessThanComparable = requires(const T &x, const T &y) {
    { x < y } -> std::convertible_to<bool>;
};

template <IsLessThanComparable Type>
class AlternativeQuicksorter {
private:
    /// <summary>
    /// Намира позицията на оста и я мести на тази позиция
    /// </summary>
    /// <returns></returns>
    static unsigned partition(Type *const array, const int start, const int end) {
        Type &pivot = array[end];
        unsigned slowerPtr = start - 1;

        for (unsigned fasterPtr = start; fasterPtr < end; ++fasterPtr) {
            if (array[fasterPtr] < pivot) {
                std::swap(array[++slowerPtr], array[fasterPtr]);
            }
        }

        std::swap(array[++slowerPtr], array[end]);

        return slowerPtr;
    }

    /// <summary>
    /// Помощна функция, която отговаря за рекурсивните извиквания и по този начин за разделянето на проблема
    /// </summary>
    static void sortHelper(Type *const array, const int start, const int end) {
        if (start >= end)
            return;

        unsigned pivotPositionIndex = partition(array, start, end);

        sortHelper(array, start, pivotPositionIndex - 1);
        sortHelper(array, pivotPositionIndex + 1, end);
    }

public:
    /// <summary>
    /// Фасадна фунцкия
    /// </summary>
    static void sort(Type *const array, const size_t size) {
        sortHelper(array, 0, size - 1);
    }
};

#endif