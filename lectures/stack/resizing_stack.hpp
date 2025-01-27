#include <stdexcept>

template <typename T>
class ResizingStack {
public:
    // първоначален капацитет на стека
    static const size_t INITIAL_CAPACITY = 10;

    // означение, че стекът е празен
    static const int EMPTY_STACK = -1;

private:
    // елементите на стека
    T* data;
    // индекс на върха на стека
    int top;
    // капацитет на стека
    size_t capacity;

    bool full() const {
        return top == capacity - 1;
    }

    void copyData(const T* const other_data) {
        for (int i = 0; i <= top; i++)
            data[i] = other_data[i];
    }

    void copy(ResizingStack const& rs) {
        top = rs.top;
        capacity = rs.capacity;
        data = new T[capacity];
        copyData(rs.data);
    }

    void resize() {
        capacity *= 2;
        std::clog << "Разширяваме стека до големина " << capacity << std::endl;
        const T* const old_data = data;
        data = new T[capacity];
        copyData(old_data);
        delete[] old_data;
    }
public:
    ResizingStack() : top(EMPTY_STACK), capacity(INITIAL_CAPACITY) {
        data = new T[capacity];
    }

    ResizingStack(ResizingStack const& rs) {
        copy(rs);
    }

    ResizingStack& operator=(ResizingStack const& rs) {
        if (this != &rs) {
            delete[] data;
            copy(rs);
        }
        return *this;
    }

    ResizingStack(ResizingStack&& rs) noexcept 
        : top(rs.top), capacity(rs.capacity), data(rs.data) {
        rs.top = EMPTY_STACK;
        rs.capacity = INITIAL_CAPACITY;
        rs.data = nullptr;
    }

    ResizingStack& operator=(ResizingStack&& rs) noexcept {
        if(this != &rs) {
            delete[] data;

            top = rs.top;
            capacity = rs.capacity;
            data = rs.data;

            rs.top = EMPTY_STACK;
            rs.capacity = INITIAL_CAPACITY;
            rs.data = nullptr;
        }
        
        return *this;    
    }
    
    ~ResizingStack() {
        delete[] data;
    }

    // проверка дали стек е празен
    bool empty() const {
        return top == EMPTY_STACK;
    }

    // включване на елемент в стек
    // сложност в най-лошия случай: O(n)
    // амортизирана сложност в средния случай: O(1)
    void push(T const& x) {
        if (full())
            resize();
        data[++top] = x;
    }

    // изключване на елемент от стек
    T pop() {
        if (empty())
            throw std::runtime_error("Опит за изключване от празен стек");
        
        T topEl = data[top--];

        if (top > 0 && top < capacity / 4) {
            resize(std::max(capacity / 2, 1));
        }

        return topEl;
     }

    // поглеждане на елемента на върха на стека
    T const& peek() const { 
        if (empty())
            throw std::runtime_error("Опит за поглеждане в празен стек");
        return data[top];
     }
};
