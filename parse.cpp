#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Employee {

    public:
        string name;
        string date;
        int role; // 0 = dev, 1 = chef

        Employee()
        {

        }
        Employee(string name, string date, int role)
        {
            this->name = name;
            this->date = date;
            this->role = role;
        }
        ~Employee()
        {

        }

};
