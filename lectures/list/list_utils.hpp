#ifndef LIST_UTILS_HPP
#define LIST_UTILS_HPP

template <typename T, typename List>
class ListUtils {
public:
    static void append(List& list1, List const& list2) {
        for(T const& x : list2)
            list1.insertLast(x);
    }
};

 
#endif // LIST_UTILS_HPP