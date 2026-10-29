#include "student.h"
#include <iostream>
using namespace std;

int Student::arraysOnHeap = 0;

// Members are initialized in the initializer list, before the body runs.
// Assigning them in the body instead would not work for `id`: it is const,
// so it cannot be assigned, only initialized.
Student::Student(int id, const string& name, size_t capacity)
    : id(id),
      name(name),
      grades(new int[capacity]),
      count(0),
      capacity(capacity)
{
    arraysOnHeap++;
    cout << "[Student] constructor: " << name << " (id " << id << "), array at " << grades << endl;
}

// Copy constructor (deep copy): the new student gets its OWN array and the
// grades are copied into it. Without this, C++ would only copy the pointer,
// so both students would share one array and both would free it (double free).
Student::Student(const Student& other)
    : id(other.id),
      name(other.name),
      grades(new int[other.capacity]),
      count(other.count),
      capacity(other.capacity)
{
    for (size_t i = 0; i < count; i++)
    {
        grades[i] = other.grades[i];
    }
    arraysOnHeap++;
    cout << "[Student] copy constructor: " << name << " (id " << id << "), new array at " << grades << endl;
}

// Move constructor: used when the source is about to disappear anyway (a
// temporary, or something passed through std::move). Instead of allocating and
// copying, the new student takes over the source's array, and the source is
// left empty (nullptr) so its destructor has nothing to free.
Student::Student(Student&& other) noexcept
    : id(other.id),
      name(move(other.name)),
      grades(other.grades),
      count(other.count),
      capacity(other.capacity)
{
    other.grades = nullptr;
    other.count = 0;
    other.capacity = 0;
    cout << "[Student] move constructor: " << name << " (id " << id << "), took array at " << grades << endl;
}

// The destructor runs automatically when a Student is destroyed (for example
// when it goes out of scope). `grades` was allocated with new[], so it must be
// released with delete[], otherwise the memory leaks.
Student::~Student()
{
    if (grades == nullptr)
    {
        cout << "[Student] destructor: id " << id << ", moved-from, nothing to free" << endl;
        return;
    }
    cout << "[Student] destructor: " << name << " (id " << id << "), freeing grades array at " << grades << endl;
    delete[] grades;
    arraysOnHeap--;
}

int Student::getId() const
{
    return id;
}

const string& Student::getName() const
{
    return name;
}

size_t Student::getGradeCount() const
{
    return count;
}

int Student::getGrade(size_t index) const
{
    if (index >= count)
    {
        return -1;
    }
    return grades[index];
}

double Student::getAverage() const
{
    if (count == 0)
    {
        return 0.0;
    }
    int sum = 0;
    for (size_t i = 0; i < count; ++i)
    {
        sum += grades[i];
    }
    return static_cast<double>(sum) / count;
}

bool Student::addGrade(int grade)
{
    if (grade < 1 || grade > 10)
    {
        cout << "  rejected grade " << grade << " (must be 1-10)" << endl;
        return false;
    }
    if (count == capacity)
    {
        cout << "  rejected grade " << grade << " (no more room)" << endl;
        return false;
    }
    grades[count++] = grade;
    return true;
}

void Student::print() const
{
    cout << "  #" << id << " " << name << " grades: [";
    for (size_t i = 0; i < count; ++i)
    {
        cout << grades[i] << (i + 1 < count ? ", " : "");
    }
    cout << "] average: " << getAverage() << endl;
}

int Student::getArraysOnHeap()
{
    return arraysOnHeap;
}
