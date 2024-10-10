#include <stdexcept>

template <typename T>
class ResizingStack {
public:
    // първоначален капацитет на стека
    static const size_t INITIAL_CAPACITY = 10;

    // означение, че стекът е празен
    static const int EMPTY_STACK = 0;

private:
    // елементите на стека
    T* data;

    // броя на елементите в стека
    size_t number_of_elements;

    // капацитет на стека
    size_t capacity;

    bool full() const {
        return number_of_elements == capacity;
    }
public:
    ResizingStack() : number_of_elements(EMPTY_STACK), capacity(INITIAL_CAPACITY) {
        data = new T[capacity];
    }
    ~ResizingStack() {
        delete[] data;
    }

    // проверка дали стек е празен
    bool empty() const {
        return number_of_elements == EMPTY_STACK;
    }

    // включване на елемент в стек
    void push(T const& x) {
        if (full())
            throw std::runtime_error("Опит за включване в пълен стек");
        data[number_of_elements++] = x;
    }

    // изключване на елемент от стек
    T pop() {
        if (empty())
            throw std::runtime_error("Опит за изключване от празен стек");
        return data[--number_of_elements];
     }

    // поглеждане на елемента на върха на стека
    T const& peek() const { 
        if (empty())
            throw std::runtime_error("Опит за поглеждане в празен стек");
        return data[number_of_elements];
     }
};