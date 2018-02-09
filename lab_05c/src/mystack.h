
#ifndef mystack_h
#define mystack_h

class MyStack {
public: 
    MyStack(); 
    MyStack(std::initializer_list<int> pInitList); 

    void push(int p_newItem); 
    void pop(); 
    int top(); 
    int getSize(); 

    //Declare a public constant called CAPACITY (value of 5)
    //HERE
private:
    int m_arr[CAPACITY];
    int m_size = 0;
};

#endif //mystack_h