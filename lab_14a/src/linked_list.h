// linked_list.h
// Implements a doubly linked list

#pragma once

template<class T>
class List
{
public:
    List();
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
        T data;
        Node *rlink;
        Node *llink;
    };

    Node *headPtr = nullptr;
    Node *tailPtr = nullptr;
};
