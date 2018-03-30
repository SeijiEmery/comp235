// base.h
#pragma once

namespace my_wonderful_namespace {

class Base
{
public:
    Base() : x(3), y(new int(5)) {}
    Base (const Base& other) { *this = other; }
    Base& operator= (const Base& other) {
        setX(other.getX());
        setY(other.getY());
        return *this;
    }
    virtual ~Base()     { delete y; }
    int getX() const { return x;  }
    int getY() const { return *y; }
    void setX(int v) { this->x = v; }
    void setY(int v) { *(this->y) = v; }

    virtual void action();
protected:
    int  x;
private:
    int* y;
};

} // namespace my_wonderful_namespace
