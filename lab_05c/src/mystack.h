
#ifndef mystack_h
#define mystack_h
#include <utility> // std::initializer_list

class MyStack {
public: 
    MyStack(); 
    MyStack(std::initializer_list<int> pInitList); 

    void push(int p_newItem); 
    void pop(); 
    int top() const; 
    int getSize() const; 

    //Declare a public constant called CAPACITY (value of 5)
    const static int CAPACITY = 5;
private:
    int m_arr[CAPACITY];
    int m_size = 0;
};

#endif //mystack_h