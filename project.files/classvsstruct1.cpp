#include<iostream>

using namespace std;

struct course{

    string Major;
    int ID;

    course(string aMajor, int aID){
    cout << "My major is " << aMajor << " and my ID is " << aID << endl;
    }
};

class student{

    public:
    string Name;
    int Age;

    student(string aName, int aAge){
    cout << "My name is " << aName << " and I'm " << aAge << " years old." << endl;
    }

};

int main()
{
    course c1("Information System", 123);

    student s1("Jimmy", 20);

    return 0;
}

