// linked_list.h
// Implements a doubly linked list.
// Note: this is for an assignment; I did not design this API.
//
#pragma once
#include <iostream>
#include <cassert>

template<class T>
class List
{
public:
    List();
    List (const List&);
    List& operator= (const List&);
    ~List();

    /*** getters ***/
    void displayListForward();
    void displayListBackward();

    /*** setter ***/
    void push_front(T p_newValue);
    void push_back(T p_newValue);
    void pop_front();
    void pop_back();
    void removeAll(T p_eraseItem);

private:

    struct Node
    {
        T value;
        Node *llink;
        Node *rlink;

        Node (T value, Node* left, Node* right)
            : value(value), llink(left), rlink(right) {}
        Node (const Node&) = delete;
        Node& operator= (const Node&) = delete;
        ~Node () {}
    };

    Node *headPtr = nullptr;
    Node *tailPtr = nullptr;
};

template <typename T>
List<T>::List () {}

template <typename T>
List<T>::List (const List& other) { *this = other; }

template <typename T>
List<T>& List<T>::operator= (const List<T>& other) {
    for (Node* node = other.headPtr; node != nullptr; node = node->rlink) {
        push_back(node->value);
    }
}

template <typename T>
List<T>::~List () {
    for (Node* node = headPtr; node; ) {
        Node* next = node->rlink;
        delete node;
        node = next;
    }
}

template <typename T>
void List<T>::removeAll (T value) {
    for (Node* node = headPtr; node != nullptr; ) {
        Node* next = node->rlink;
        if (node->value == value) {
            if (node->llink) {
                assert(node->llink->rlink == node);
                node->llink->rlink = node->rlink;
            } else {
                assert(node == headPtr);
                headPtr = node->rlink;
            }
            if (node->rlink) {
                assert(node->rlink->llink == node);
                node->rlink->llink = node->llink;
            } else {
                assert(node == tailPtr);
                tailPtr = node->llink;
            }
            delete node;
        }
        node = next;
    }
}

template <typename T>
void List<T>::displayListForward () {
    bool first = true;
    for (Node* node = headPtr; node != nullptr; node = node->rlink) {
        std::cout 
            << (first ? first = false, "" : ", ")
            << node->value;
    }
}

template <typename T>
void List<T>::displayListBackward () {
    bool first = true;
    for (Node* node = tailPtr; node != nullptr; node = node->llink) {
        std::cout 
            << (first ? first = false, "" : ", ")
            << node->value;
    }
}

template <typename T>
void List<T>::push_front (T value) {
    Node* node = new Node(value, nullptr, headPtr);
    if (headPtr) { 
        assert(headPtr->llink == nullptr);
        headPtr->llink = node;
    }
    assert((headPtr == nullptr) == (tailPtr == nullptr));
    headPtr = node;
    if (!tailPtr) { tailPtr = node; }
}

template <typename T>
void List<T>::push_back (T value) {
    Node* node = new Node(value, tailPtr, nullptr);
    if (tailPtr) { 
        assert(tailPtr->rlink == nullptr);
        tailPtr->rlink = node;
    }
    assert((headPtr == nullptr) == (tailPtr == nullptr));
    tailPtr = node;
    if (!headPtr) { headPtr = node; }
}

template <typename T>
void List<T>::pop_front () {
    Node* node = headPtr;
    if (headPtr == tailPtr) {
        assert(node->llink == nullptr);
        assert(node->rlink == nullptr);
        headPtr = tailPtr = nullptr;
    } else {
        assert(node->rlink != nullptr);
        assert(node->rlink->llink == node);
        node->rlink->llink = nullptr;
        headPtr = node->rlink;
        assert(headPtr->llink == nullptr);
    }
    delete node;
}

template <typename T>
void List<T>::pop_back () {
    Node* node = tailPtr;
    if (headPtr == tailPtr) {
        assert(node->llink == nullptr);
        assert(node->rlink == nullptr);
        headPtr = tailPtr = nullptr;
    } else {
        assert(node->llink != nullptr);
        assert(node->llink->rlink == node);
        node->llink->rlink = nullptr;
        tailPtr = node->llink;
        assert(tailPtr->rlink == nullptr);
    }
    delete node;
}

