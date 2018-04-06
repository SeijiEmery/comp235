#include <iostream>
using namespace std;

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
//TO DO : Use dynamic casting, identify animal types and increment counts of // ‘chkn’, ‘fish’, and ‘rabbit’ with appropriate amounts
}
int main() {
    const int numOfAnimals = 150;
    int numChicken = 0;
    int numFish = 0;
    int numRabbits = 0;
    srand(10);
    //TO DO: Declare an arrary called ‘arr’ of pointers to your objects
    //TO DO
    //Using a loop, produce the same 150 animals in the array as part I
    for (int i = 0; i < numOfAnimals; i++) {
        int selectAnimal = 1 + rand() % 3;
        switch (selectAnimal)
        {
        case 1: arr[i] = //a tiger
        case 2: arr[i] = //a fox
        case 3: arr[i] = //a polar bear
        }
    }
    dailyConsumption(arr, numOfAnimals, numChicken, numFish, numRabbits);
    cout << "\nDaily consumptions of animals...\n";
    cout << numChicken << " chicken" << endl;
    cout << numFish << " fish" << endl;
    cout << numRabbits << " rabbits" << endl;
    return 0; 
}
