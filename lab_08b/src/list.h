#pragma once

class List
{
public:
    List();
    List(int);
    /*List(const List&);*/

    void addItem(int newItem);
    void printList();
    void decrementAll();

    /*List& operator= (const List&);*/
    /*~List();*/
private:
    int *dataList;
    int length;
    int capacity;
};