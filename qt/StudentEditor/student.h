#ifndef STUDENT_H
#define STUDENT_H
#include <string>
using std::string;


class Student {
private:
    string name;
    int age;
    string group;
    int course;
    static const int STUDENT_MIN_AGE = 15;
public:
    Student();

    string getName() const;
    void setName(const string &value);
    int getAge() const;
    void setAge(int value);
    string getGroup() const;
    void setGroup(const string &value);
    int getCourse() const;
    void setCourse(int value);
};

#endif // STUDENT_H
