#include <vector>
#include <iostream> 
#include <algorithm>
#include <cstdlib> 
using namespace std;

struct Employee
{
    int salary = 0; //let's just use whole numbers
    int bonus = 0;

    Employee (int salary = 0, int bonus = 0)
        : salary(salary), bonus(bonus) {}
    Employee (const Employee&) = default;
    Employee& operator= (const Employee&) = default;
};

struct Dollars {
    int value;

    Dollars (int value) : value(value) {}
    Dollars (const Dollars&) = default;
    Dollars& operator= (const Dollars&) = default;

    static void writeDolllarValue (std::ostream& os, int value) {
        if (value > 1000) {
            writeDolllarValue(os, value / 1000);
            os << ',' << (value % 1000);
        } else {
            os << '$' << value;
        }
    }
    friend std::ostream& operator<< (std::ostream& os, const Dollars& dollars) {
        return writeDolllarValue(os, dollars.value), os;
    }
};
Dollars dollars (int value) { return { value }; }


int main()
{
    srand(time(nullptr));
    vector<Employee> myEmployees(5); 
    int employeeID = 0;
    
    cout << "Enter annual sales: ";
    int sales;
    cin >> sales;

    constexpr int salary_min = 50 * 1000;
    constexpr int salary_max = 200 * 1000;

    //1. Assign random salaries, using range $50,000 to $200,000, to each of the 5 employees
    std::generate(myEmployees.begin(), myEmployees.end(), []() -> Employee {
        return { salary_min + rand() % (salary_max - salary_min) };
    });

    //2. If annual sales exceed $1,000,000 then assign bonuses of 10% based on each salary.
    if (sales > 1000000) {
        std::for_each(myEmployees.begin(), myEmployees.end(), [](Employee& employee) {
            employee.bonus += employee.salary * 0.1;
        });
    }
    
    //3. Display salaries and bonuses, along with employee ID: 1, 2, 3, 4, 5. Use employeeID in your capture list
    std::for_each(myEmployees.begin(), myEmployees.end(), [&employeeID](const Employee& employee) {
        std::cout << "Employee " << ++employeeID 
            << " Salary " << dollars(employee.salary)
            << ", Bonus " << dollars(employee.bonus) << '\n';
    });

    int sum = 0;
    //4. Accumulate all salaries and bonuses and display that as a single sum, Use sum in the capture list
    std::for_each(myEmployees.begin(), myEmployees.end(), [&sum](const Employee& employee) {
        sum += employee.salary + employee.bonus;
    });
    std::cout << "Total payments to employees: " << dollars(sum) << '\n';
    
    cout << endl;
    return 0;
}
