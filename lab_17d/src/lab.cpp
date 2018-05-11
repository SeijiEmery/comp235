#include <vector>
#include <iostream> 
#include <algorithm> 
using namespace std;

struct Employee
{
    int salary = 0; //let's just use whole numbers
    int bonus = 0;
};

int main()
{
    vector<Employee> myEmployees(5); 
    int employeeID = 0;
    
    cout << "Enter annual sales: ";
    int sales;
    cin >> sales;
    
    //1. Assign random salaries, using range $50,000 to $200,000, to each of the 5 employees

    //2. If annual sales exceed $1,000,000 then assign bonuses of 10% based on each salary.
    if (sales > 1000000)  
    
    //3. Display salaries and bonuses, along with employee ID: 1, 2, 3, 4, 5. Use employeeID in your capture list
     

int sum = 0;
//4. Accumulate all salaries and bonuses and display that as a single sum, Use sum in the capture list

    cout << sum << endl;
    
    cout << endl;
    return 0;
}
