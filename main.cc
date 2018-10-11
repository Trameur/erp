#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
using namespace std;

class Employee {

    public:
        string name;
        int jour, mois, annee;
        int role; // 0 = dev, 1 = chef

        Employee();

        Employee(string name, int role, int jour, int mois, int annee)
        {
            this->name = name;
            this->role = role;
            this->jour = jour;
            this->mois = mois;
            this->annee = annee;
        }

        ~Employee() { }
};

class Projet {

    public:
        string name;
        int jour, mois, annee;
        int dev;
        int gestion;
        int jourFinDev, moisFinDev, anneeFinDev;
        int jourFinChef, moisFinChef, anneeFinChef;

        Projet();

        Projet(string name, int dev, int gestion, int jour, int mois, int annee)
        {
            this->name = name;
            this->dev = dev;
            this->gestion = gestion;
            this->jour = jour;
            this->mois = mois;
            this->annee = annee;
        }

        ~Projet() { }

        bool NotOverlapDev()
        {
            return (jour < jourFinDev && mois < moisFinDev && annee < anneeFinDev); 
        }

        bool NotOverlapChef()
        {
            return (jour < jourFinChef && mois < moisFinChef && annee < anneeFinChef); 
        }

};

vector<Employee> parseEmployee(string path){
   ifstream fichier(path);
   string name;
   string date;
   int role;
   int jour,mois, annee;       
   int dev, projet;

   if(!fichier.eof())
       fichier >> dev >> projet;

   vector<Employee> tabEmp;

   for(int i=0; i < dev; i++){

       if(!fichier.eof())
           fichier >> name >> jour  >> mois >> annee >> role;

       Employee emp(name, role, jour, mois, annee);
       cout << emp.name << emp.role << endl;

       tabEmp.push_back(emp);

   }
   fichier.close();

   return tabEmp;

}

vector<Projet> parseProject(string path){
   ifstream fichier(path);

   string name;
   int dev;
   int gestion;
   int projet;
   int role;

   int jour,mois, annee;

   if(!fichier.eof())
       fichier >> dev >> projet;

   vector<Projet> tabProjet;
   string s;
   for(int i=0; i < dev*3+1; i++){

       if(!fichier.eof())
           getline(fichier, s);
   }

   getline(fichier, s);

   for(int i=0; i < projet; i++){

       if(!fichier.eof())
           fichier >> name >> dev >> gestion >> jour  >> mois >> annee;

       tabProjet.push_back(Projet(name, dev, gestion, jour, mois, annee));
       cout << name << endl;
   }



   fichier.close();

   return tabProjet;

}

void datePlusDays(struct tm* date, int days)
{
    const time_t ONE_DAY = 24 * 60 * 60 ;

    // Seconds since start of epoch
    time_t date_seconds = mktime( date ) + (days * ONE_DAY) ;

    // Update caller's date
    // Use localtime because mktime converts to UTC so may change date
    *date = *localtime( &date_seconds ) ;
}

struct tm& getDate(struct tm& date, int jour, int mois, int annee)
{

    date.tm_year = annee - 1900;
    date.tm_mon = mois - 1;
    date.tm_mday = jour;

    datePlusDays(&date,0);

    return date;
}

int main (int argc, char *argv[])
{

    if(argc < 2)
    {
        cout << "Error usage " << argv[0] << " [filename]" << endl;
        return 1;
    }

    vector<Employee> allEmployees = parseEmployee(argv[1]);

    vector<Projet> allProjects = parseProject(argv[1]);

    int counter = 0;
    int days = 4;
    bool toutFini = false;
    int projetDev = 0;
    int projetChef = 0;
    
    struct tm date = { 0 , 0 , 18 } ;
    struct tm dateTemp = { 0 , 0 , 18 } ;
    int year = 2018;
    int month = 6;
    int day = 1;

    date.tm_year = year - 1900;
    date.tm_mon = month - 1;
    date.tm_mday = day;

    dateTemp.tm_year = year - 1900;
    dateTemp.tm_mon = month - 1;
    dateTemp.tm_mday = day;

    while(!toutFini)
    {

        if(days < 5)
        {
          for(auto it = allEmployees.begin(); it != allEmployees.end() ; it++)
          {

            if(it->role == 0)
            {
              if(allProjects[projetDev].dev > 0)
              {
                allProjects[projetDev].dev--;
              }
              else if(allProjects.size() > projetDev)
              {
                allProjects[projetDev].jourFinDev = date.tm_mday;
                allProjects[projetDev].moisFinDev = date.tm_mon + 1;
                allProjects[projetDev].anneeFinDev = date.tm_year + 1900;
                allProjects[++projetDev].dev--;
              }
            }
            else if(it->role == 1)
            {
              if(allProjects[projetChef].gestion > 0)
              {
                allProjects[projetChef].gestion--;
              }
              else if(allProjects.size() > projetChef)
              {
                allProjects[projetChef].jourFinChef = date.tm_mday;
                allProjects[projetChef].moisFinChef = date.tm_mon + 1;
                allProjects[projetChef].anneeFinChef = date.tm_year + 1900;
                allProjects[++projetChef].gestion--;
              }
            }
          }
        }

        days++;
        if(days > 6)
            days = 0;

        if(allProjects.size() == projetDev && allProjects.size() == projetChef)
        {
            toutFini = true;
        }
        else
        {
            counter++;
            datePlusDays(&date, 1);
        }
            
    }

    for(auto it = allProjects.begin(); it != allProjects.end() ; it++)
    {
        if(!it->NotOverlapDev())
        {
            cout << "Le projet " << it->name << " devait finir le " 
            << asctime(&getDate(dateTemp, it->jour, it->mois, it->annee)) << ", les devs ont fini le "
            << asctime(&getDate(dateTemp, it->jourFinDev, it->moisFinDev, it->anneeFinDev)) << " et les chefs ont fini le "
            << asctime(&getDate(dateTemp, it->jourFinChef, it->moisFinChef, it->anneeFinChef)) << endl;
        }
        if(!it->NotOverlapChef())
        {

        }
    }


    cout << "Nombre de jours : " << counter << endl;
    cout << "Fin prévue : " << asctime(&date) << endl;



    return 0;
}
