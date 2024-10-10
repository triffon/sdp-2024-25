#include <utility>
class QuickSorter {
private:
    static int partition(int array[], size_t n, int pivot) {
        int left = 0, right = n - 1;
        while (left != right) {
            if (array[left] < pivot) left++;
            else
              // array[left] не си е на мястото
              if (array[right] >= pivot) right--;
              else {
                // array[right] не си е на мястото, да ги разменим!
                std::swap(array[left], array[right]);
                left++;
                right--;
              }
        }
        // left == right
        // array[left] == array[right] на в коя част трябва да е?
        if (array[left] < pivot)
            // трябва да е в лявата част
            // оста трябва да дойде на мястото на array[left]
            return left;
        // трябва да е в дясната част
        // оста трябва да дойде на мястото на array[left - 1]
        return left - 1;
    }
public:
    static void sort(int array[], size_t n) {
        // 1. Избираме елемент от масива (``ос'')
        int& pivot = array[0];

        // 2. Разделяме масива на две части:
        //   - елементи по-малки от оста
        //   - елементи по-големи или равни на оста
        int pivot_index = partition(array + 1, n - 1, pivot);

        // 3. поставяме оста между двете части на масива
        std::swap(pivot, array[pivot_index]);

        // 4. сортираме поотделно двете части на масива
        sort(array, pivot_index);
        sort(array + pivot_index + 1, n - pivot_index - 1);
    }
};