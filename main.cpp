#include "student.h"

#include <iostream>
#include <utility>
#include <vector>

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
        // Without our copy constructor, C++ would generate one that copies every
        // member as-is. `grades` is a pointer, so only the address would be
        // copied: both students would share ONE array, the copy's destructor
        // would free it, and later the original's destructor would free the
        // same address again (double free -> the program crashes with
        // heap corruption, exit code 0xC0000374).
        // Our copy constructor allocates a NEW array and copies the grades.
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

    // std::move says "I don't need dana anymore", so the move constructor runs:
    // it takes dana's array (same address, nothing allocated or copied) and
    // leaves dana empty.
    cout << "  moving:" << endl;
    Student moved = std::move(dana);
    cout << "  arrays on heap: " << Student::getArraysOnHeap() << " (unchanged, the array changed owner)" << endl;

    cout << "  moved:" << endl;
    moved.print();
    cout << "  dana after the move (empty):" << endl;
    dana.print();

    // Moves also happen automatically for temporary objects, e.g. when putting
    // a newly created Student into a vector: the temporary is moved in, not copied.
    cout << "  adding a temporary to a vector:" << endl;
    vector<Student> group;
    group.push_back(Student(6, "Eva", 1000000));
    cout << "  arrays on heap: " << Student::getArraysOnHeap() << endl;
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
