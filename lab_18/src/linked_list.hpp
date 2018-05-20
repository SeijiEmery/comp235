#pragma once
#include <memory>
#include <utility>
#include <ostream>

template <typename T>
class LinkedList {
    struct Node;
    typedef std::unique_ptr<Node> NodePtr;
    struct Node {
        NodePtr next;
        T       data;

        Node (T data) : data(data) {}
        Node (const Node& other) : data(other.data) {
            if (other.next) {
                next = std::move(std::make_unique<Node>(*other.next));
            }
        }
    };
    NodePtr head;
public:
    typedef LinkedList<T> This;

    LinkedList () {}
    LinkedList (std::initializer_list<T> values) {
        for (auto it = rbegin(values), end = rend(values); it != end; ++it) {
            push_front(*it);
        }
    }
    LinkedList (const This& other) {
        if (other.head) {
            head = std::move(std::make_unique<Node>(*other.head));
        }
    }
    LinkedList (This&& other) { std::swap(head, other.head); }
    This& operator= (const This& other) {
        This temp { other };
        std::swap(temp, *this);
        return *this;
    }
    This& operator= (This&& other) {
        std::swap(head, other.head);
        return *this;
    }
    operator bool () const { return static_cast<bool>(head); }
    bool empty () const { return !*this; }

    const T& front () const { assert(*this); return head->data; }
    T& front () { assert(*this); return head->data; }

    void push_front (const T& value) {
        NodePtr newNode { new Node(value) };
        std::swap(head, newNode->next);
        std::swap(head, newNode);
    }
    void pop_front () {
        assert(*this);
        NodePtr temp;
        std::swap(head->next, temp);
        std::swap(head, temp);
    }

    void push_back (const T& value) {
        if (!head) {
            push_front(value);
        } else {
            NodePtr* node = &head;
            while ((*node)->next) {
                node = &(*node)->next;
            }
            assert(*node && !(*node)->next);
            NodePtr newNode { new Node(value) };
            std::swap(newNode, (*node)->next);
        }
    }
    void pop_back () {
        assert(*this);
        if (!head->next) {
            pop_front();
        } else {
            NodePtr* node = &head;
            while ((*node)->next->next) {
                node = &(*node)->next;
            }
            NodePtr empty;
            std::swap((*node)->next, empty);
        }
    }
private:
    template <typename Node, typename V>
    struct Iterator {
        friend class LinkedList;
    private:
        Node* ptr = nullptr;
    public:
        typedef Iterator<Node, V> This;

        Iterator () {}
        Iterator (Node* ptr) : ptr(ptr) {}
        Iterator (const This&) = default;
        This& operator= (const This&) = default;
        ~Iterator () {}

        operator bool () const { return ptr != nullptr; }

        friend bool operator== (const This& a, const This& b) {
            return (!a && !b) || a.ptr == b.ptr;
        }
        friend bool operator!= (const This& a, const This& b) {
            return !(a == b);
        }
        V& operator*  () const { assert(*this); return ptr->data; }
        V* operator-> () const { assert(*this); return &(ptr->data); }

        This& operator++ () { assert(*this); return ptr = (ptr->next).get(), *this; }
    };
public:
    typedef Iterator<Node, T> iterator;
    typedef Iterator<const Node, const T> const_iterator;

    iterator begin () { return { head ? head.get() : nullptr }; }
    iterator end   () { return {}; }

    const_iterator begin () const { return { head ? head.get() : nullptr }; }
    const_iterator end   () const { return {}; }

    const_iterator cbegin () const { return begin(); }
    const_iterator cend   () const { return end(); }

    iterator find (const T& value) {
        auto it = begin();
        for (; it != end(); ++it) {
            if (*it == value) {
                break;
            }
        }
        return it;
    }
    const_iterator find (const T& value) const {
        auto it = begin();
        for (; it != end(); ++it) {
            if (*it == value) {
                break;
            }
        }
        return it;
    }

    void insert (const T& value, iterator it) {
        if (it) {
            NodePtr newNode { new Node(value) };
            std::swap(newNode->next, it.ptr->next);
            std::swap(newNode,       it.ptr->next);
        } else {
            push_back(value);
        }
    }

private:
    void remove (const Node* ptr) {
        if (!head) {}
        else if (head.get() == ptr) {
            pop_front();
        } else {
            NodePtr* node = &head;
            while ((*node)->next.get() != ptr) {
                node = &(*node)->next;
            }
            NodePtr empty;
            if (ptr) {
                std::swap((*node)->next->next, empty);
            }
            std::swap((*node)->next, empty);
        }
    }
public:
    void remove (const T& value) {
        remove(find(value));
    }
    void remove (iterator it) {
        remove(it.ptr);
    }
    void remove (const_iterator it) {
        remove(it.ptr);
    }

    friend std::ostream& operator<< (std::ostream& os, const This& self) {
        if (self) {
            os << "{ ";
            bool first = true;
            for (const auto& v : self) {
                if (first) { first = false; } else { os << ", "; }
                os << v;
            }
            return os << " }";
        } else {
            return os << "{}";
        }
    }
};
