/*** Implementations ***/
#include "list.h"
#include <iostream>
using namespace std;

List::List()
{
    dataList = new int[10];
    length = 0;
    capacity = 10;
}

List::List(int p_cap)
{
    dataList = new int[p_cap];
    length = 0;
    capacity = p_cap;
}
//List::List(const List& p_obj)
//{
//  //Allocate separate memory
//  //Copy over attriutes of p_obj 
//}

void List::addItem(int newItem)
{
    if (length != capacity)
    {
        dataList[length] = newItem;
        length++;
    }
}
void List::printList()
{
    for (int i = 0; i < length; i++)
        cout << dataList[i] << ' ';
}
void List::decrementAll()
{
    for (int i = 0; i < length; i++)
        dataList[i]--;
}

//List& List::operator= (const List&)
//{
//  //Allocate separate memory
//  //Copy over attriutes of p_obj 
//}

//List::~List()
//{
//  //Deallocate dynamic array
//}