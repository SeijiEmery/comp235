#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class LivingThing
{
    int m_legs = 0;
public:
    LivingThing() {}
    LivingThing(int legs) : m_legs(legs) {}
    virtual void move() { cout << "A living thing is moving!"; };
    int legs () const { return m_legs; }
};

class Human : public LivingThing
{
public:
    Human () : LivingThing(2) {}
    void move () override { cout << "A human is walking!";}
};

class Tiger : public LivingThing
{
public:
    Tiger () : LivingThing(4) {}
    void move () override { cout << "A tiger is prowling!"; }
};

int main()
{
    cout << "Part I. Static Bindings\n";
    cout << "=======================\n";
    {
        std::vector<LivingThing> things = {
            Human(),
            Tiger(),
            Human(),
            Tiger(),
        };
        for (auto& thing : things) {
            thing.move(); std::cout << " with " << thing.legs() << " legs\n";
        }
    }

    cout << "Part II. Dynamic Bindings\n";
    cout << "=========================\n";
    {
        std::vector<std::unique_ptr<LivingThing>> things;
        things.emplace_back(static_cast<LivingThing*>(new Human()));
        things.emplace_back(static_cast<LivingThing*>(new Tiger()));
        things.emplace_back(static_cast<LivingThing*>(new Human()));
        things.emplace_back(static_cast<LivingThing*>(new Tiger()));

        for (auto& thing : things) {
            thing->move(); std::cout << " with " << thing->legs() << " legs\n";
        }
    }
    return 0;
}
