#ifndef LIST_UTILS_HPP
#define LIST_UTILS_HPP

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
};

 
#endif // LIST_UTILS_HPP