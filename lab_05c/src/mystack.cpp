#include "mystack.h"
#include <stdexcept>

void enforce (bool condition, const char* msg) {
    if (!condition) {
        throw std::runtime_error(msg);
    }
}

MyStack::MyStack () {}

MyStack::MyStack (std::initializer_list<int> items) {
    enforce(items.size() < CAPACITY, "Stack initializer has too many elements");

    for (const auto& item : items) {
        push(item);
    }
}

void MyStack::push (int item) {
    enforce(m_size < CAPACITY, "Stack capacity exceeded");

    m_arr[m_size++] = item;
}

void MyStack::pop () {
    enforce(m_size > 0, "Stack undeflow (cannot pop from empty stack)");

    m_size--;
}

int MyStack::top () const {
    enforce(m_size > 0, "Stack empty, cannot dereference top()");

    return m_arr[m_size - 1];
}

int MyStack::getSize () const {
    return m_size;
}
