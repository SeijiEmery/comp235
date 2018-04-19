// bst.hpp
//
// Implements a simple / trivial binary search tree.
// version 2 (improved / optimized), see bst.h for v1
//
// copyright (c) Seiji Emery 2018, All rights reserved.
//
#pragma once
#include <iostream>     // std::cout, std::ostream
#include <cstdlib>      // rand()

// Simple (ie. non-balancing) binary search tree implementation
// for a lower division CS class. This BST operates as a set type
// and does not permit duplicate elements.
template <class T>
class BST {
public:
    // Constructors
    BST () {}

    // Generic iterator / range constructor
    template <typename It>
    BST (It begin, It end) {
        for (; begin != end; ++begin) {
            insert(*begin);
        }
    }

    // Used to implement the initializer list ctor 
    BST (std::initializer_list<T> values)
        : BST(values.begin(), values.end()) {}

    // But not the copy ctor since I didn't actually end up implementing iterators :/ 
    // (somewhat non-trivial w/out backtrack pointers (too much complexity) 
    // or additional memory allocations (inefficient)). Iterating w/ callbacks / visitors 
    // is simple and efficient, but not as general or composable. :| 
    BST (const BST<T>& other) {
        other.traverseInOrder([&](const T& value) {
            insert(value);
        });
    }

    // Move constructor + assignment is implemented
    // BST instance data consists of only one pointer (nice!)
    BST (BST<T>&& other)
        : root(std::move(other.root)) {}

    BST<T>& operator= (BST<T>&& other) {
        std::swap(root, other.root);
        return *this;
    }

    // Assignment operator implemented in terms of the other two; is efficient as BST<T>
    // is once again a single, null-initialized pointer by default.
    BST<T>& operator= (const BST<T>& other) {
        BST<T> temp { other };
        return *this = std::move(temp);
    }

    // Defer memory deallocation to another method (DRY)
    ~BST () { clear(); }

    // bool conversion
    operator bool () const { return root != nullptr; }

    // Removes and deallocates all nodes allocated by this BST
    void clear () {
        // std::cout << "\nclear()";
        // printTree(); 
        removeAll(root); 
        // printTree();
        // std::cout << '\n' << '\n';
    }

    // Uniquely inserts an element (if duplicate exists, does nothing)
    void insert (T value) {
        // std::cout << "\ninsert(" << value << ")";
        // printTree(); 
        insertInto(root, value); 
        // printTree(); 
        // std::cout << '\n' << '\n';
    }

    // Removes a single / unique element
    void remove (T value) {
        // std::cout << "\nremove(" << value << ")";
        // printTree(); 
        removeFrom(root, value); 
        // printTree(); 
        // std::cout << '\n' << '\n';
    }

    // Check if the BST contains this value
    bool contains (T value) {
        return find(root, value) != nullptr;
    }

    // Tree traversal using the visitor pattern (ie. any functor / function-like callback)
    // Method signature should be
    //      void operator ()(const T&) { ... }   (from const / non-const reference)
    // or   void operator ()(T&)       { ... }   (from non-const reference only)
    // or   void operator ()(T)        { ... }   (for trivial / POD types w/ zero-cost copies)

    #define DECL_VISITOR_METHOD(traversal) \
    template <typename Visitor> void traversal (const Visitor& visitor)

    #define DEFN_VISITOR_METHOD(traversal) \
    DECL_VISITOR_METHOD(traversal)       { traversal(visitor, root); } \
    DECL_VISITOR_METHOD(traversal) const { traversal(visitor, root); }

    DEFN_VISITOR_METHOD(traverseInOrder)
    DEFN_VISITOR_METHOD(traversePreOrder)
    DEFN_VISITOR_METHOD(traversePostOrder)

    #undef DEFN_VISITOR_METHOD
    #undef DECL_VISITOR_METHOD

    // Special case used for in-order traversal w/ indented output (or something).
    // method signature is
    //      void operator ()(const T& value, size_t depth)
    template <typename Visitor>
    void traverseAllWithDepth (const Visitor& visitor) {
        traverseAllWithDepth(visitor, root, 0);
    }

    // Default implementation of a nested tree printout.
    // is reasonably customizable (ie. print eol character before / after line, which strings / 
    // characters to print as indentation and/or delimters); for more control see traverseAllWithDepth()
    void printTree (std::ostream& os, const char* indent = "| ", const char* preEol = "\n", const char* postEol = "") {
        traverseAllWithDepth([&](const T& value, size_t depth) {
            os << preEol;
            while (depth --> 0) {
                os << indent;
            }
            os << value;
            os << postEol;
        });
    }

    // Default printout of the tree (with "(null)" to visualize empty tree)
    // Exists for debugging purposes.
    void printTree () {
        if (root) {
            printTree(std::cout);
        } else {
            std::cout << "\n(null)";
        }
    }

    // Pretty printing, displaying BST<T> as an in-order set
    friend std::ostream& operator<< (std::ostream& os, const BST<T>& tree) {
        if (tree) {
            os << "{ ";
            bool first = true;
            tree.traverseInOrder([&](const T& value) {
                os << (first ? first = false, "" : ", ") << value;
            });
            return os << " }";
        } else {
            return os << "{}";
        }
    }
private:
    //
    // Actual BST implementation
    //

    struct Node {
        T     value;
        Node* left  = nullptr;
        Node* right = nullptr;

        Node (T value) : value(value) {}
        Node (const Node&) = delete;
        Node& operator= (const Node&) = delete;
        Node& operator= (Node&& other) {
            std::swap(value, other.value);
            std::swap(left, other.left);
            std::swap(right, other.right);
            return *this;
        }
        Node (Node&& other) { std::swap(*this, other); }
        ~Node () {}
    };
    Node* root = nullptr;

    //
    // Method implementations here since it's simpler to write these algorithms
    // as functions w/ pointer references than as OOP methods.
    //

    static void removeAll (Node*& node) {
        if (node) {
            removeAll(node->left);
            removeAll(node->right);
            delete node;
            node = nullptr;
        }
    }
    static void insertInto (Node*& node, const T& value) {
        if (!node) {
            node = new Node(value);
        } else if (value != node->value) {
            insertInto(value < node->value ?
                    node->left :
                    node->right,
                value);
        }
    }
    static Node*& find (Node*& node, const T& value) {
        if (!node) {
            static Node* emptyNode = nullptr;
            assert(emptyNode == nullptr);
            return emptyNode;
        } else if (value == node->value) {
            return node;
        } else {
            return find(value < node->value ?
                node->left :
                node->right,
            value);
        }
    }
    static void removeFrom (Node*& parent, const T& value) {
        Node*& node = find(parent, value);
        if (!node) { return; }
        if (!(node->left) || !(node->right)) {
            // 0-1 children, simple case: promote left or right subtree, delete this node
            Node* ptr = node;
            node = node->left ? node->left :
                node->right ? node->right :
                nullptr;
            // assert(ptr->left == nullptr && ptr->right == nullptr);
            delete ptr;
        } else {
            // 2 children, more complex case: find min / max child in right / left subtree,
            // swap value with child (note: order is preserved), and then delete that child
            // (which should be a much simpler case, or can continue doing so recursively forever)

            // Since this is a trivial tree, and we can choose left OR right, we simply
            // randomly choose left / right to attempt to leave the tree reasonably balanced

            if (rand() & 1) {
                Node*& child = node->left; assert(child != nullptr);
                while (child->right) { child = child->right; }
                std::swap(child->value, node->value);
                removeFrom(child, value);
            } else {
                Node*& child = node->right; assert(child != nullptr);
                while (child->left) { child = child->left; }
                std::swap(child->value, node->value);
                removeFrom(child, value);
            }
        }
    }
    template <typename Visitor>
    static void traverseInOrder (const Visitor& visitor, Node* node) {
        if (node) {
            traverseInOrder(visitor, node->left);
            visitor(node->value);
            traverseInOrder(visitor, node->right);
        }
    }
    template <typename Visitor>
    static void traversePreOrder (const Visitor& visitor, Node* node) {
        if (node) {
            visitor(node->value);
            traverseInOrder(visitor, node->left);
            traverseInOrder(visitor, node->right);
        }
    }
    template <typename Visitor>
    static void traversePostOrder (const Visitor& visitor, Node* node) {
        if (node) {
            traverseInOrder(visitor, node->left);
            traverseInOrder(visitor, node->right);
            visitor(node->value);
        }
    }
    template <typename Visitor>
    static void traverseAllWithDepth (const Visitor& visitor, Node* node, size_t depth) {
        if (node) {
            visitor(node->value, depth);
            traverseAllWithDepth(visitor, node->left, depth + 1);
            traverseAllWithDepth(visitor, node->right, depth + 1);
        }
    }
public:
    // These methods are required according to the assignment spec;
    // they simply print out the values as a comma separated, EOL-delimited
    // list (using either in order, pre order, or post order traversal)

    #define DEFN_PRINT_METHOD(name, traverse) \
    void name () { \
        bool first = true; \
        traverse([&](const T& value) { \
            std::cout \
                << (first ? (first = false, "") : ", ") \
                << value; \
        }); \
        std::cout << '\n'; \
    }
    DEFN_PRINT_METHOD(inOrder, traverseInOrder)
    DEFN_PRINT_METHOD(preOrder, traversePreOrder)
    DEFN_PRINT_METHOD(postOrder, traversePostOrder)
    #undef DEFN_PRINT_METHOD
};
