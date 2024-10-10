template <typename T>
class Stack {
public:
    // проверка дали стек е празен
    bool empty() const { throw "Not implemented"; }

    // включване на елемент в стек
    void push(T const& x) {}

    // изключване на елемент от стек
    T pop() { throw "Not implemented"; }

    // поглеждане на елемента на върха на стека
    T const& peek() const { throw "Not implemented"; }
};