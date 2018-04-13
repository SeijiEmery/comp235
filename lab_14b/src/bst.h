#pragma once
#include <cstdlib>


template <class T>
class BST {
public:
    BST () {}
    ~BST ();
    bool insert (T value);
    void remove (T value);

    /*** Tree traversals ***/
    void inOrder ();
    void preOrder ();
    void postOrder ();
private:
    struct Node {
        friend class BST<T>;
        T value;
        Node* left = nullptr;
        Node* right = nullptr;

        Node (T value) : value(value) {}
        ~Node () {
            if (left)  delete left;
            if (right) delete right;
        }
    private:
        Node* remove (T value) {
            if (value == this->value) {
                if (left != nullptr && right != nullptr) {
                    Node* node;
                    if (rand() & 1) {
                        for (node = left; node->right; node = node->right);
                        std::swap(this->value, node->value);
                        node = left = node->remove(value);
                    } else {
                        for (node = right; node->left; node = node->left);
                        std::swap(this->value, node->value);
                        node = right = node->remove(value);
                    }
                    return this;
                }
                Node* ptr = nullptr;
                if (left != nullptr) {
                    std::swap(left, ptr);
                    assert(left == nullptr && right == nullptr);
                } else if (right != nullptr) {
                    std::swap(right, ptr);
                    assert(left == nullptr && right == nullptr);
                }
                delete this;
                return ptr;
            }
            if (value < this->value) { if (left)  left  = left->remove(value); }
            else                     { if (right) right = right->remove(value); }
            return this;
        }
        template <typename Visitor>
        void preOrder (const Visitor& visitor) {
            visitor(value);
            if (left) { left->preOrder(visitor); }
            if (right) { right->preOrder(visitor); }
        }
        template <typename Visitor>
        void postOrder (const Visitor& visitor) {
            if (left) { left->postOrder(visitor); }
            if (right) { right->postOrder(visitor); }
            visitor(value);
        }
        template <typename Visitor>
        void inOrder (const Visitor& visitor) {
            if (left) { left->inOrder(visitor); }
            visitor(value);
            if (right) { right->inOrder(visitor); }
        }
    };
    Node* root = nullptr;
    //Helper functions

    friend void insertInto (Node*& node, T value) {
        if (node == nullptr) {
            node = new Node(value);
        } else if (node->value != value) {
            insertInto(value < node->value ? node->left : node->right, value);
        }
    }
};

template <typename T>
BST<T>::~BST () {
    if (root) delete root;
}

template <typename T>
bool BST<T>::insert (T value) {
    insertInto(root, value);
    return true;
}

template <typename T>
void BST<T>::remove (T value) {
    if (root) {
        root = root->remove(value);
    }
}

template <typename T>
void BST<T>::preOrder () {
    bool first = true;
    if (root) { root->preOrder([&](T& value) { std::cout << (first ? (first = false, "") : ", ") << value; }); }
    std::cout << '\n';
}

template <typename T>
void BST<T>::inOrder () {
    bool first = true;
    if (root) { root->inOrder([&](T& value) { std::cout << (first ? (first = false, "") : ", ") << value; }); }
    std::cout << '\n';
}

template <typename T>
void BST<T>::postOrder () {
    bool first = true;
    if (root) { root->postOrder([&](T& value) { std::cout << (first ? (first = false, "") : ", ") << value; }); }
    std::cout << '\n';
}
