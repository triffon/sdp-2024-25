#ifndef LIST_UTILS_HPP
#define LIST_UTILS_HPP

#include <stdexcept>

template <typename T, typename List>
class ListUtils {
public:
    static void append(List& list1, List const& list2) {
        for(T const& x : list2)
            list1.insertLast(x);
    }

    static void reverse(List& l) {
        typename List::Iterator it = l.begin();
        if (it.valid())
            while (it.next().valid()) {
                T x;
                l.deleteAfter(x, it);
                l.insertFirst(x);
            }
    }

    static void split(List const& list, List& l1, List& l2) {
        if (!l1.empty() || !l2.empty())
            throw std::invalid_argument("Списъците l1 и l2 трябва да са празни!");
        List *me = &l1, *you = &l2;
        for(T const& x : list) {
            me->insertLast(x);
            std::swap(me, you);
        }
    }
};

 
#endif // LIST_UTILS_HPP