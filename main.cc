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

    Employee emp1("dev", "01/06/19", 0);
    Employee chef("chef", "01/06/19", 1);

    Projet airbus("airbus", "01/12/19", 150, 40);

    int counter = 0;
    int days = 0;
    bool toutFini = false;

    while(!toutFini)
    {
        if(days < 5)
        {
            if(airbus.dev > 0)
                airbus.dev--;

            if(airbus.gestion > 0)
                airbus.gestion--;
        }
        
        days++;
        if(days > 6)
            days = 0;

        counter++;

        if(airbus.dev == 0 && airbus.gestion == 0)
        {
            toutFini = true;
        }
    }

    cout << "Nombre de jours : " << counter << endl;



    return 0;
}