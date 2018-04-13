#pragma once

template <class T>
class BST {
public:
    BST ();
    void insert (T value);
    void remove (T value);

    /*** Tree traversals ***/
    void inOrder ();
    void preOrder ();
    void postOrder ();
private:
    struct Node {
        T data;
        Node* left = nullptr;
        Node* right = nullptr;
    };
    Node* root = nullptr;
    //Helper functions
};
