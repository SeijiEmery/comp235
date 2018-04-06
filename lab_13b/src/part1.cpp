#include <iostream>
using namespace std;

// Note: I DID NOT WRITE OR DESIGN THIS CODE!!!!

class GameParkAnimal {
public:
    GameParkAnimal(string food = "") : foodType(food) {}
    virtual int getDailyAmount() { return 0; }
    string foodType;
};
//Each tiger eats 20 rabbits a day
class Tiger : public GameParkAnimal {
public:
    Tiger() : GameParkAnimal("rabbit") {}
    int getDailyAmount() override { return 20; }
};
//Each Fox eats 2 chicken a day
class Fox : public GameParkAnimal {
public:
    Fox() : GameParkAnimal("chicken") {}
    int getDailyAmount() override { return 2; }
};

//Each polar bear eats 30 fish a day
class PolarBear : public GameParkAnimal { public:
    PolarBear() : GameParkAnimal("fish") {}
    int getDailyAmount() override { return 30; }
};
void dailyConsumption(GameParkAnimal* arr[], size_t arrSize, int& chkn, int& fish, int&rabbit)
{
    for (size_t i = arrSize; i --> 0; ) {
        if (auto ptr = dynamic_cast<Tiger*>(arr[i])) { rabbit += ptr->getDailyAmount(); }
        else if (auto ptr = dynamic_cast<Fox*>(arr[i])) { chkn += ptr->getDailyAmount(); }
        else if (auto ptr = dynamic_cast<PolarBear*>(arr[i])) { fish += ptr->getDailyAmount(); }
        else { assert(0); }
    }
}
int main() {
    //Do not change anything in the driver
    const int numOfAnimals = 150;
    int numChicken = 0;
    int numFish = 0;
    int numRabbits = 0;
    srand(10); //produces the same sequence of random numbers
    GameParkAnimal* arr[numOfAnimals];
    for (int i = 0; i < numOfAnimals; i++) {
        int selectAnimal = 1 + rand() % 3;
        switch (selectAnimal)
        {
        case 1: arr[i] = new Tiger(); break;
        case 2: arr[i] = new Fox(); break;
        case 3: arr[i] = new PolarBear(); break;
        }
    }
    dailyConsumption(arr, numOfAnimals, numChicken, numFish, numRabbits);
    cout << "\nDaily consumptions of animals...\n";
    cout << numChicken << " chicken" << endl;
    cout << numFish << " fish" << endl;
    cout << numRabbits << " rabbits" << endl;
    return 0; 
}
