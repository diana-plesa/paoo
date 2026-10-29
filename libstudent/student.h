#pragma once

#include <string>

class Student
{
public:
    Student(const std::string& name, std::size_t capacity);

    const std::string& getName() const;
    std::size_t getGradeCount() const;
    int getGrade(std::size_t index) const;
    double getAverage() const;

    bool addGrade(int grade);

    void print() const;

private:
    std::string name;
    int* grades;          // heap-allocated array
    std::size_t count;    // how many grades are stored
    std::size_t capacity; // size of the allocated array
};
