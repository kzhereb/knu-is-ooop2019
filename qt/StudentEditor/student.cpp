#include "student.h"
#include <stdexcept>

string Student::getName() const
{
    return name;
}

void Student::setName(const string &value)
{
    name = value;
}

int Student::getAge() const
{
    return age;
}

void Student::setAge(int value)
{
    if (value < STUDENT_MIN_AGE) {
        throw std::invalid_argument("age");
    }
    this->age = value;
}

string Student::getGroup() const
{
    return group;
}

void Student::setGroup(const string &value)
{
    group = value;
}

int Student::getCourse() const
{
    return course;
}

void Student::setCourse(int value)
{
    course = value;
}

Student::Student()
{

}
