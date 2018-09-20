#include <iostream>
#include <fstream>

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

 void parse(string path, Employee e1, Employee e2,Employee e3,Employee e4){
    ifstream fichier(path);
    string name;
    string date;
    int role;

    int dev,chef,projet;

    if(!fichier.eof())
        fichier >> dev >> chef >> projet;

    for(int i=0; i < dev+chef; i++){

        if(!fichier.eof())
            fichier >> name >> date >> role;

        switch(i){
        case 0 : e1.name=name;   e1.date = date; e1.role = 1; break;
        case 1 : e2.name=name;   e2.date = date; e2.role = 0; break;
        case 2 : e3.name=name;   e3.date = date; e3.role = 0; break;
        case 3 : e4.name=name;   e4.date = date; e4.role = 0; break;
        default : break;

        }
        cout << name << date << role << endl;

    }


    fichier.close();


}

int main()
{
    Employee e1;
    Employee e2;
    Employee e3;
    Employee e4;
    parse("data",e1,e2,e3,e4);



    return 0;
}
