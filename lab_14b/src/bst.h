#pragma once

template <class T>
class BST {
public:
    BST ();
    void insert (T new_item);
    void delete (T delete_me);

    /*** Tree traversals ***/
    void inOrder ();
    void preOrder ();
    void postOrder ();
private:
    struct Node {
        T data;
        Node* llink = nullptr;
        Node* rlink = nullptr;
    };
    Node* m_root = nullptr;
    //Helper functions
};
