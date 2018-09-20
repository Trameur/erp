#include <stdio.h>
#include<iostream>

using namespace std;

class Employee {

    public:
        string name;
        string date;
        int role; // 0 = dev, 1 = chef

        Employee();

        Employee(string name, string date, int role)
        {
            this->name = name;
            this->date = date;
            this->role = role;
        }

        ~Employee() { }
};

class Projet {

    public:
        string name;
        string date;
        int dev;
        int gestion;

        Projet();

        Projet(string name, string date, int dev, int gestion)
        {
            this->name = name;
            this->date = date;
            this->dev = dev;
            this->gestion = gestion;
        }

        ~Projet() { }
};

void readConfiguration(char *filename)
{
    cout << filename << endl;
}

int main (int argc, char *argv[])
{   

    if(argc < 2)
    {
        cout << "Error usage " << argv[0] << " [filename]" << endl;
        return 1;
    }

    readConfiguration(argv[1]);

    Employee emp1("dev", "15/05/19", 0);
    Employee chef("chef", "15/05/19", 1);

    Projet airbus("airbus", "1/12/19", 150, 40);
    

    


    return 0;
}