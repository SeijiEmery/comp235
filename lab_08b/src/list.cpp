/*** Implementations ***/
#include "list.h"
#include <iostream>
#include <algorithm> // std::swap, etc
using namespace std;

List::List() {
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
List::List(const List& other)
    : dataList(new int [other.capacity])
    , length (other.length)
    , capacity (other.capacity)
{
    std::copy(other.dataList, &other.dataList[other.length], dataList);
}

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

List& List::operator= (const List& other) {
    List copy { other };
    std::swap(dataList, copy.dataList);
    std::swap(length, copy.length);
    std::swap(capacity, copy.capacity);
    return *this;
}

List::~List()
{
    if (dataList) {
        delete[] dataList;
    }
}