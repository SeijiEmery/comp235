// d1.h
#pragma once
#include "base.h"

namespace my_wonderful_namespace {

class D1 : public Base {
public:
    D1 () : d(2) {}
    ~D1 () override {}
    D1 (const D1& other) { *this = other; }
    D1& operator= (const D1& other) {
        static_cast<Base&>(*this) = static_cast<const Base&>(other);
        d = other.getD();
        return *this; 
    }

    int getD () const { return d; }
    void setD (int v) { d = v; }

    int addAll () const { 
        return getX() + getY() + getD();
    }

    void action () override;
private:
    int d;
};

} // namespace my_wonderful_namespace
