#ifndef LIST_UTILS_HPP
#define LIST_UTILS_HPP

#include <stdexcept>

template <typename T, typename List>
class ListUtils {
public:
    // конкатенира list2 към list1
    // O(n) по време и по O(n) по памет
    static void append(List& list1, List const& list2) {
        for(T const& x : list2)
            list1.insertLast(x);
    }

    // обръща реда на елементите в l
    // O(n) по време и O(1) по памет
    // TODO: да се направи конкретна реализация директно с представянето
    static void reverse(List& l) {
        typename List::Iterator it = l.begin();
        if (it.valid())
            while (it.next().valid()) {
                T x;
                l.deleteAfter(x, it);
                l.insertFirst(x);
            }
    }

    // разделя елементите на list в list1 и list2 така, че да са с приблизително
    // равна дължина
    // O(n) по време и по памет
    // TODO: да се направи реализация, която е O(1) по допълнителна памет
    // TODO: да се направи конкретна реализация, директно с представянето 
    static void split(List const& list, List& list1, List& lsit2) {
        if (!list1.empty() || !list2.empty())
            throw std::invalid_argument("Списъците list1 и list2 трябва да са празни!");
        List *me = &list1, *you = &list2;
        for(T const& x : list) {
            me->insertLast(x);
            std::swap(me, you);
        }
    }
};

 
#endif // LIST_UTILS_HPP