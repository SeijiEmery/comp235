
#ifndef Vehicle_h
#define Vehicle_h

class Vehicle {
public:
    Vehicle (int wheels = 4);
    static int howManyVehicles ();
private:
    static int totalVehicles;
    int m_wheels;
};

#endif // Vehicle_h
