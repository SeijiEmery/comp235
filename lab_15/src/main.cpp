// In section 17.3, the author implemented an ListIterator template class
//  to be used with a Node template class. The Node class uses a pointer
//  as its link field between Node objects.
//
// I have stripped away template syntax and namespaces. I have combined all
//  three files into one as well, to allow you to focus on the 
//  implementation of ListIterator and its use in the main()

#include <iostream>
using namespace std;

class Node
{
public:
    Node() {}
    Node(char theData, Node* theLink)
        : data(theData), link(theLink) {}

    const char& getData() const { return data; }
    Node* getLink() { return link; }
    void setData(const char& theData) { data = theData; }
    void setLink(Node* pointer) { link = pointer; }
private:
    char data = 0;
    Node *link = nullptr;
};

class ListIterator
{
public:
    ListIterator() : current(nullptr) {}
    ListIterator(Node* initial) : current(initial) {}

    const char& operator *() const { return current->getData(); }

    ListIterator& operator ++() { //Prefix form 
        current = current->getLink();
        return *this;
    }

    ListIterator operator ++(int) { //Postfix form 
        ListIterator startVersion(current);
        current = current->getLink();
        return startVersion;
    }

    bool operator ==(const ListIterator& rightSide) const {
        return (current == rightSide.current);
    }

    bool operator !=(const ListIterator& rightSide) const {
        return (current != rightSide.current);
    }
private:
    Node * current;
};

class Queue
{
public:
    typedef ListIterator Iterator;

    Queue() {}

    void add(int item) {

        Node *aNewNode = new Node(item, nullptr);
 
        if (front == nullptr) {         
            front = aNewNode;
            front->setLink(nullptr);
            back = front;
        }
        else {
            back->setLink(aNewNode);
            back = back->getLink();          
        }
    }
    int remove() { Node *temp = front; front = front->getLink(); delete temp; }

    bool isEmpty() const {
        if (front == nullptr)
            return true;
        else
            return false;
    }

    Iterator begin() const { return Iterator(front); }
    Iterator end() const { return Iterator(); }

private:
    Node * front = nullptr; //Points to the head of a linked list. 
                            //Items are removed at the head. 
    Node *back = nullptr; //Points to the node at the other end of 
                          //Items are added at this end.
};

int main()
{
    char next, ans;
    do {
        Queue q;
        cout << "Enter characters:\t";
        cin.get(next);

        while (next != '\n')
        {
            q.add(next);
            cin.get(next);
        }
        cout << "You entered:\t\t";

        Queue::Iterator i; 
        for (i = q.begin(); i != q.end(); i++) 
            cout << *i;

        cout << endl;
        cout << "Again?(y/n): ";
        cin >> ans;
        cin.ignore(10000, '\n');
    } while (ans != 'n' && ans != 'N');

    return 0;
}
