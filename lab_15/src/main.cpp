// main.cpp
// Implements a doubly linked list and forward / reverse iterators.
// written (rewritten?) by Seiji Emery
//

#include <iostream>
using namespace std;

class Node
{
public:
    Node() {}
    Node(char data, Node* prev = nullptr, Node* next = nullptr)
        : m_data(data), m_prev(prev), m_next(next) {}

    char const& data () const { return m_data; }
    Node const* prev () const { return m_prev; }
    Node const* next () const { return m_next; }

    char&  data () { return m_data; }
    Node*& prev () { return m_prev; }
    Node*& next () { return m_next; }
private:
    char m_data = 0;
    Node* m_prev = nullptr;
    Node* m_next = nullptr;
};

class DequeIterator
{
public:
    typedef DequeIterator This;
    typedef char          value;

    DequeIterator (const Node* node = nullptr) : node(node) {}
    DequeIterator (const This& other) : node(other.node) {}
    This& operator= (const This& other) { node = other.node; return *this; }
    ~DequeIterator () {}

    operator bool () const { return node != nullptr; }

    value operator *() const { 
        assert(node != nullptr);
        return node->data(); 
    }
    This& operator++ () {
        assert(node != nullptr);
        node = node->next();
        return *this;
    }
    This& operator-- () {
        assert(node != nullptr);
        node = node->prev();
        return *this;
    }
    This& operator++ (int) {
        This copy { *this };
        return ++(*this), copy;
    }
    This& operator-- (int) {
        This copy { *this };
        return --(*this), copy;
    }
    friend bool operator== (const This& a, const This& b) {
        return (!a && !b) || a.node == b.node;
    }
    friend bool operator!= (const This& a, const This& b) {
        return !(a == b);
    }
private:
    const Node* node = nullptr;
};

template <typename It>
class ReverseIt {
    It it;
public:
    typedef ReverseIt<It> This;
    typedef typename  It::value     value;

    ReverseIt (It it) : it(it) {}
    ReverseIt (const This&) = default;
    This& operator= (const This&) = default;

    value operator* () const { return *it; }
    This& operator++ ()      { return --it, *this; }
    This& operator-- ()      { return ++it, *this; }
    This& operator++ (int)   { This copy { *this }; return --(*this), copy; }
    This& operator-- (int)   { This copy { *this }; return ++(*this), copy; }
    friend bool operator== (const This& a, const This& b) {
        return a.it == b.it;
    }
    friend bool operator!= (const This& a, const This& b) {
        return a.it != b.it;
    }
};

class Deque
{
public:
    typedef Deque         This;
    typedef DequeIterator Iterator;

    Deque () {}

    template <typename It>  Deque (It begin, It end)  { insert(begin, end); }
    template <typename Seq> Deque (const Seq& values) { insert(values); }
    template <typename Seq> This& operator= (const Seq& values) { return clear(), insert(values), *this; }

    Deque (This&& other) { std::swap(*this, other); }
    This& operator= (This&& other) {
        std::swap(front, other.front);
        std::swap(back,  other.back);
        return *this;
    }
    ~Deque () {
        clear();
    }

    void insert (char value) {
        pushFront(value);
    }
    template <typename It>
    void insert (It begin, It end) {
        for (; begin != end; ++begin) {
            insert(*begin);
        }
    }
    template <typename Sequence>
    void insert (const Sequence& sequence) {
        insert(sequence.begin(), sequence.end());
    }

    void clear () {
        assert((front == nullptr) == (back == nullptr));
        Node* node = front;
        for (Node* next; node != nullptr; node = next) {
            next = node->next();
            delete node;
        }
        // assert((node == back));
        front = back = nullptr;
    }

    operator bool () const {
        assert((front == nullptr) == (back == nullptr));
        return front != nullptr;
    }
    void pushFront (char value) {
        front = new Node(value, nullptr, front);
        if (Node* next = front->next()) {
            assert(next->prev() == nullptr);
            next->prev() = front;
        }
        if (back == nullptr) {
            back = front;
        }
    }
    void pushBack (char value) {
        back = new Node(value, back, nullptr);
        if (Node* prev = back->prev()) {
            assert(prev->next() == nullptr);
            prev->next() = back;
        }
        if (front == nullptr) {
            front = back;
        }
    }

    void popFront () {
        if (Node* node = front) {
            front = node->next();
            delete node;
            if (front == nullptr) {
                back = nullptr;
            }
            assert((front != nullptr) == (back != nullptr));
        }
    }
    void popBack () {
        if (Node* node = back) {
            back = node->prev();
            delete node;
            if (back == nullptr) {
                front = nullptr;
            }
            assert((front != nullptr) == (back != nullptr));
        }
    }

    Iterator begin  () const { return Iterator(front); }
    Iterator end    () const { return Iterator();      }

    ReverseIt<Iterator> rbegin () const { return {{ back }}; }
    ReverseIt<Iterator> rend   () const { return {{}}; }

private:
    Node *front = nullptr; //Points to the head of a linked list. 
                            //Items are removed at the head. 
    Node *back = nullptr; //Points to the node at the other end of 
                          //Items are added at this end.
};

template <typename Seq>
class Reversal {
    Seq& seq;
public:
    Reversal (Seq& seq) : seq(seq) {}
    auto begin  () -> decltype(seq.rbegin()) { return seq.rbegin(); }
    auto end    () -> decltype(seq.rend())   { return seq.rend();   }
    auto rbegin () -> decltype(seq.begin())  { return seq.begin();  }
    auto rend   () -> decltype(seq.end())    { return seq.end();    }

    auto begin  () const -> decltype(seq.rbegin()) { return seq.rbegin(); }
    auto end    () const -> decltype(seq.rend())   { return seq.rend();   }
    auto rbegin () const -> decltype(seq.begin())  { return seq.begin();  }
    auto rend   () const -> decltype(seq.end())    { return seq.end();    }
};
template <typename Seq>
auto reversed (Seq& seq) -> Reversal<Seq> { return { seq }; }

template <typename Seq>
auto reversed (const Seq& seq) -> Reversal<const Seq> { return { seq }; }

int main()
{
    char next, ans;
    do {
        Deque q;
        cout << "Enter characters:\t";
        cin.get(next);

        while (next != '\n')
        {
            q.pushBack(next);
            cin.get(next);
        }
        cout << "You entered:\t\t";
        for (auto value : reversed(reversed(q))) {
            cout << value;
        }
        cout << "\nReversed: \t\t";
        for (auto value : reversed(reversed(reversed(q)))) {
            cout << value;
        }
        cout << endl;
        cout << "Again?(y/n): ";
        cin >> ans;
        cin.ignore(10000, '\n');
    } while (ans != 'n' && ans != 'N');

    return 0;
}
