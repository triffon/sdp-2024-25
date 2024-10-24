#ifndef QUEUE_UTILS_HPP
#define QUEUE_UTILS_HPP
#include <stdexcept>

template <typename T, template <typename> class Queue>
class QueueUtils {
public:
    static T min(Queue<T>& queue) {
        if (queue.empty())
            throw std::invalid_argument("Очаквам непразна опашка");
        T sentinel;
        queue.enqueue(sentinel);
        T currentmin = queue.dequeue();
        while (queue.head() != sentinel) {
            T current = queue.dequeue();
            if (current < currentmin) {
                queue.enqueue(currentmin);
                currentmin = current;
            } else
                queue.enqueue(current);
        }
        // премахваме сентинела
        queue.dequeue();
        return currentmin;
    }
};
#endif // QUEUE_UTILS_HPP