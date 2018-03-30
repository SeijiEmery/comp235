// base.h
#pragma once

namespace my_wonderful_namespace {

class Base
{
public:
    Base() : x(3), y(new int(5)) {}
    virtual ~Base()     { delete y; }
    virtual int getX()  { return x;  }
    virtual int getY()  { return *y; }
    virtual void setX(int v) { this->x = v; }
    virtual void setY(int v) { *(this->y) = v; }

    virtual void action() = 0;
protected:
    int  x;
private:
    int* y;
};

} // namespace my_wonderful_namespace
