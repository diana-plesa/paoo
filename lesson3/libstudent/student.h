#pragma once

#include <string>

class Student
{
public:
    Student(int id, const std::string& name, std::size_t capacity);
    Student(const Student& other);     // copy constructor
    Student(Student&& other) noexcept; // move constructor
    ~Student();

    int getId() const;
    const std::string& getName() const;
    std::size_t getGradeCount() const;
    int getGrade(std::size_t index) const;
    double getAverage() const;

    bool addGrade(int grade);

    void print() const;

    // How many grade arrays are currently allocated on the heap (for all students)
    static int getArraysOnHeap();

private:
    const int id;         // const: can only be set in the initializer list
    std::string name;
    int* grades;          // heap-allocated array
    std::size_t count;    // how many grades are stored
    std::size_t capacity; // size of the allocated array

    static int arraysOnHeap; // shared by all Student objects
};
