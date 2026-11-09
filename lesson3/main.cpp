#include "student.h"

#include <iostream>
#include <utility>

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

void demoCopyConstructor()
{
    cout << endl << "=== 5. Copy constructor ===" << endl;

    Student original(4, "Carla", 3);
    original.addGrade(10);
    original.addGrade(9);

    {
        Student copy = original;
        copy.addGrade(5); // changes only the copy

        cout << "  arrays on heap: " << Student::getArraysOnHeap()
             << " (two students, two separate arrays)" << endl;
        cout << "  copy:" << endl;
        copy.print();
    } // copy's destructor frees only the copy's own array

    cout << "  original is untouched and its array is still valid:" << endl;
    original.print();
} // original's destructor frees its own array, no double free

void demoMoveConstructor()
{
    cout << endl << "=== 6. Move constructor ===" << endl;

    Student dana(5, "Dana", 1000000); // array of one million ints
    dana.addGrade(8);

    // Copying allocates a second array of one million ints and copies the data.
    cout << "  copying:" << endl;
    Student copied = dana;
    cout << "  arrays on heap: " << Student::getArraysOnHeap() << endl;

    cout << "  moving:" << endl;
    Student moved = std::move(dana);
    cout << "  arrays on heap: " << Student::getArraysOnHeap() << " (unchanged, the array changed owner)" << endl;

    cout << "  moved:" << endl;
    moved.print();
    cout << "  dana after the move (empty):" << endl;
    dana.print();
}

int main()
{
    demoEncapsulation();
    demoInitializerList();
    demoDestructor();
    demoCopyConstructor();
    demoMoveConstructor();
    cout << endl << "arrays still on heap at the end: " << Student::getArraysOnHeap() << endl;
    return 0;
}
