#include<iostream>

using namespace std;

struct course{

    string Major;
    int ID;

};

class student{

    public:
    string Name;
    int Age;

};

int main()
{
    course c1;
    c1.Major = "Information System";
    c1.ID = 123;

    cout << "My major is " << c1.Major << " and my ID is " << c1.ID << endl;

    student s1;
    s1.Name = "Jimmy";
    s1.Age = 20;

    cout << "My name is " << s1.Name << " and I'm " << s1.Age << " years old." << endl;
    return 0;
}
