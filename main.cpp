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

void demoDestructor()
{
    cout << endl << "=== 4. Destructor ===" << endl;
    cout << "  arrays on heap before block: " << Student::getArraysOnHeap() << endl;
    {
        Student temp(3, "Temp", 1000);
        cout << "  arrays on heap inside block: " << Student::getArraysOnHeap() << endl;
    } // temp goes out of scope here, so its destructor runs
    cout << "  arrays on heap after block:  " << Student::getArraysOnHeap() << endl;
}

int main()
{
    demoEncapsulation();
    demoInitializerList();
    demoDestructor();
    cout << endl << "arrays still on heap at the end: " << Student::getArraysOnHeap() << endl;
    return 0;
}
