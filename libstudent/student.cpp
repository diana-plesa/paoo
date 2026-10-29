#include "student.h"
#include <iostream>
using namespace std;

Student::Student(const string& name, size_t capacity)
{
    this->name = name;
    this->capacity = capacity;
    this->count = 0;
    this->grades = new int[capacity];
    cout << "[Student] constructor: " << name << endl;
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
    std::cout << "  " << name << " grades: [";
    for (size_t i = 0; i < count; ++i)
    {
        cout << grades[i] << (i + 1 < count ? ", " : "");
    }
    cout << "] average: " << getAverage() << endl;
}
