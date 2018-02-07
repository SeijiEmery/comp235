#include <iostream>

class MyClass
{
public:
    int m_data = 1111;
    struct MyStruct //MyStruct is a data type
    {
        int m_data = 9999;

        MyStruct () {}
        MyStruct (int data)
            : m_data(data) {}
        friend std::ostream& operator<< (std::ostream& os, const MyStruct& myStruct) {
            return os << "MyStruct { " << myStruct.m_data << " }";
        }
    } structObj; //structObj is a variable

    //1. TO DO: Initialize both 'm_data' using initializer list
    //  with a default value, 1
    MyClass() : m_data(1), structObj(1) {}

    //2. TO DO: Initialize 'm_data' using initializer list
    //  with parameter passed
    MyClass(int p_data)
        : m_data(p_data)
    {}
    //Precondition: p_data is targeted for int data
    //  member

    //3. TO DO: Initialize 'm_data' using initializer list
    //  with parameters passed
    MyClass(int p_data1, int p_data2 )
        : m_data(p_data1), structObj(p_data2)
    {}
    //Precondition: p_data is targeted for int data
    //  member. p_data2 is targeted for struct,
    //  MyStruct};

    friend std::ostream& operator<< (std::ostream& os, const MyClass& myClass) {
        return os << "MyClass { " << myClass.m_data << ", " << myClass.structObj << " }";
    }
};

int main()
{
    MyClass obj1;
    MyClass obj2 (235);
    MyClass obj3{ 2, 2020 };

    //4. TO DO: Write code to display all data members of each object
    std::cout << "obj1 = " << obj1 << '\n';
    std::cout << "obj2 = " << obj2 << '\n';
    std::cout << "obj3 = " << obj3 << '\n';
}