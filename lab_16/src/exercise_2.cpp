#include <iostream>
#include <stdexcept>

struct StackOverflowException : public std::runtime_error {
    StackOverflowException (const char* msg)
        : std::runtime_error(msg) {}
};
struct StackUndeflowException : public std::runtime_error {
    StackUndeflowException (const char* msg)
        : std::runtime_error(msg) {}
};

template <typename T>
class Stack {
    size_t size;
    size_t next = 0;
    T*     data;
public:
    typedef Stack<T> This;
    Stack (size_t size)
        : size(size), data(new T[size]) {}
    Stack (const This&) = delete;
    This& operator= (const This&) = delete;
    ~Stack () {
        delete[] data;
    }
    operator bool () { return next > 0; }
    void push (const T& value) {
        if (next >= size) {
            throw StackOverflowException("Stack overflow");
        }
        data[next++] = value;
    }
    T pop () {
        if (next <= 0) {
            throw StackUndeflowException("Stack underflow");
        }
        return data[--next];
    }
};

template <typename Stack, typename Action>
bool tryStackAction (Stack& stack, const Action& action) {
    try {
        action();
    } catch (const StackOverflowException& e) {
        std::cerr << e.what() << '\n';
        return false;
    } catch (const StackUndeflowException& e) {
        std::cerr << e.what() << '\n';
        return false;
    }
    return true;
}
template <typename T>
void tryPush (Stack<T>& stack, T value) {
    std::cout << "Pushing " << value << ": ";
    tryStackAction(stack, [&](){ stack.push(value); })
        && (std::cout << "Ok.\n");
}
template <typename T>
void tryPop (Stack<T>& stack) {
    std::cout << "Popping value: ";
    tryStackAction(stack, [&](){ stack.pop(); })
        && (std::cout << "Ok.\n");
}

int main () {
    std::cout << "Creating stack with capacity of 3 elements\n";
    Stack<int> stack (3);
    tryPush(stack, 1);
    tryPush(stack, 2);
    tryPush(stack, 3);
    tryPush(stack, 4);
    tryPush(stack, 5);
    tryPop(stack);
    tryPop(stack);
    tryPop(stack);
    tryPop(stack);
    tryPop(stack);
    return 0;
}
