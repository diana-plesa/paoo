#include "student.h"

#include <iostream>

using namespace std;

void demoEncapsulation()
{
    cout << "=== 2. Encapsulation ===" << endl;

    Student ana(1, "Ana", 3);
    ana.addGrade(9);
    ana.addGrade(42); // invalid value, rejected by addGrade()
    ana.addGrade(10);
    ana.addGrade(7);
    ana.addGrade(8);  // array is full, rejected
    ana.print();

    // None of these compile, because the members are private:
    // ana.grades[0] = 42;
    // ana.count = 100;

    cout << "  first grade via getter: " << ana.getGrade(0) << endl;
}

void demoInitializerList()
{
    cout << endl << "=== 3. Initializer list ===" << endl;

    Student bob(2, "Bob", 2);
    cout << "  bob.getId() = " << bob.getId() << endl;
}

int main()
{
    demoEncapsulation();
    demoInitializerList();
    return 0;
}
