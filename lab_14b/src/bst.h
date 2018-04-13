#pragma once
#include <cstdlib>
#include <functional>


static int indent = 0;

#if 0

std::ostream& debugln () {
    std::cout << '\n';
    for (int n = indent; n --> 0; ) {
        std::cout << "| ";
    }
    return std::cout;
}
template <typename F>
struct Scoped {
    const F& out;
    Scoped (const F& in, const F& out) : out(out) { in(); }
    ~Scoped () { out(); }
};
#define MAKE_SCOPED \
    Scoped<std::function<void()>> _scoped ## __COUNTER__

#define DESCRIBE_THIS_METHOD() \
    static_cast<void*>(this) << ": " << _methodName << "() in " __FILE__ ":" << __LINE__

#define DEBUG(msg...) \
    debugln() << msg;

#define THIS static_cast<void*>(this)

#define DEBUG_THIS \
    const char* _methodName = __FUNCTION__; \
    MAKE_SCOPED { \
        [&](){ debugln() << DESCRIBE_THIS_METHOD(); ++indent; }, \
        [&](){ --indent; debugln() << DESCRIBE_THIS_METHOD(); }};

#else
#define THIS
#define DEBUG_THIS
#define DEBUG(msg...)
#endif


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
    struct Node;

    friend void displayTree (Node* node) {
        DEBUG("Tree structure:"); ++indent;
        if (node) {
            node->showTree();
        } else {
            DEBUG("null");
        }
        --indent;
    }
    void showTree () { displayTree(root); }


    struct Node {
        friend class BST<T>;
        T value;
        Node* left = nullptr;
        Node* right = nullptr;

        Node (T value) : value(value) { DEBUG_THIS }
        ~Node () {
            DEBUG_THIS
            if (left)  delete left;
            if (right) delete right;
        }
    private:
        Node* remove (T value) {
            DEBUG_THIS
            if (value == this->value) {
                DEBUG("deleting this node " << THIS)
                if (left != nullptr && right != nullptr) {
                    Node* node;
                    if (rand() & 1) {
                        for (node = left; node->right; node = node->right);
                        DEBUG("swapping " << this->value << " <-> " << node->value);
                        std::swap(this->value, node->value);
                        DEBUG("removing value from subtree");
                        displayTree(node);
                        node = left = node->remove(value);
                        displayTree(node);
                    } else {
                        for (node = right; node->left; node = node->left);
                        DEBUG("swapping " << this->value << " <-> " << node->value);
                        std::swap(this->value, node->value);
                        DEBUG("removing value from subtree");
                        displayTree(node);
                        node = right = node->remove(value);
                        displayTree(node);
                    }
                    return this;
                }
                DEBUG("deleting " << THIS)
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
            if (!left && !right) { DEBUG("Value not found " << value << ", no item removed"); }
            if (value < this->value) { if (left)  left  = left->remove(value); }
            else                     { if (right) right = right->remove(value); }
            return this;
        }
        template <typename Visitor>
        void preOrder (const Visitor& visitor) {
            // DEBUG_THIS
            visitor(value);
            if (left) { left->preOrder(visitor); }
            if (right) { right->preOrder(visitor); }
        }
        template <typename Visitor>
        void postOrder (const Visitor& visitor) {
            // DEBUG_THIS
            if (left) { left->postOrder(visitor); }
            if (right) { right->postOrder(visitor); }
            visitor(value);
        }
        template <typename Visitor>
        void inOrder (const Visitor& visitor) {
            // DEBUG_THIS
            if (left) { left->inOrder(visitor); }
            visitor(value);
            if (right) { right->inOrder(visitor); }
        }

        void showTree () {
            DEBUG(THIS << " " << value); ++indent;
            if (left) left->showTree();
            if (right) right->showTree();
            --indent;   
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
    DEBUG_THIS
    showTree();
    if (root) delete root;
}

template <typename T>
bool BST<T>::insert (T value) {
    DEBUG_THIS
    DEBUG("inserting " << value)
    showTree();
    insertInto(root, value);
    showTree();
    return true;
}

template <typename T>
void BST<T>::remove (T value) {
    DEBUG_THIS
    DEBUG("removing " << value)
    showTree();
    if (root) {
        root = root->remove(value);
    }
    showTree();
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
