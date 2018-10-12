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
        bool CanWork(int jour, int mois, int annee)
        {
            int date1 =  this->jour + this->mois*100 + this->annee*10000;
            int date2 =  jour + mois*100 + annee*10000;  

            return date1 <= date2;
                
        }

        ~Employee() { }
};

class Projet {

    public:
        string name;
        int jour, mois, annee;
        float dev;
        float gestion;
        float devBase;
        float gestionBase;


        int jourFinDev, moisFinDev, anneeFinDev;
        int jourFinChef, moisFinChef, anneeFinChef;
        float multiplicateur = 0.8;

        Projet();

        Projet(string name, int dev, int gestion, int jour, int mois, int annee, float multiplicateur)
        {
            this->name = name;
            this->dev = dev;
            this->gestion = gestion;
            this->jour = jour;
            this->mois = mois;
            this->annee = annee;

            this->devBase = dev;
            this->gestionBase = gestion;

            this->multiplicateur = multiplicateur;
        }

        ~Projet() { }

        bool NotOverlapDev()
        {
            int date1 =  this->jour + this->mois*100 + this->annee*10000;
            int date2 =  this->jourFinDev + this->moisFinDev*100 + this->anneeFinDev*10000;

            return date1 < date2; 
        }

        bool NotOverlapChef()
        {
            int date1 =  this->jour + this->mois*100 + this->annee*10000;
            int date2 =  this->jourFinChef + this->moisFinChef*100 + this->anneeFinChef*10000;

            return date1 < date2; 
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

       tabEmp.push_back(emp);

   }
   fichier.close();

   return tabEmp;

}

vector<Projet> parseProject(string path, float multiplicateur){
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

       tabProjet.push_back(Projet(name, dev, gestion, jour, mois, annee, multiplicateur));
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

    if(argc < 3)
    {
        cout << "Error usage " << argv[0] << " [filename] [multiplicateur]" << endl;
        return 1;
    }

    vector<Employee> allEmployees = parseEmployee(argv[1]);

    vector<Projet> allProjects = parseProject(argv[1], atof(argv[2]));

    bool recrutementDev = false;
    bool recrutementChef = false;

    // multiplicateur
    // nombre de dev
    bool simulation = true;

    int counter = 0;
    int days = 4;
    bool toutFini = false;
    int projetDev = 0;
    int projetChef = 0;
    
    struct tm date = { 0 , 0 , 8 } ;
    struct tm dateTemp = { 0 , 0 , 8 } ;
    int year = 2018;
    int month = 6;
    int day = 1;
    int nbDev = 0;
    int nbChef = 0;


    date.tm_year = year - 1900;
    date.tm_mon = month - 1;
    date.tm_mday = day;

    dateTemp.tm_year = year - 1900;
    dateTemp.tm_mon = month - 1;
    dateTemp.tm_mday = day;

    while(simulation)
    {       
        counter = 0;
        days = 4;
        toutFini = false;
        projetDev = 0;
        projetChef = 0;
        year = 2018;
        month = 6;
        day = 1;

        date.tm_year = year - 1900;
        date.tm_mon = month - 1;
        date.tm_mday = day;

        dateTemp.tm_year = year - 1900;
        dateTemp.tm_mon = month - 1;
        dateTemp.tm_mday = day;
        nbDev = 0;
        nbChef = 0;

        if(recrutementDev)
        {
            Employee emp("nom", 0, 1, 10, 2018);
            allEmployees.push_back(emp);  
        }
        if(recrutementChef)
        {
            Employee emp("nom", 1, 1, 10, 2018);
            allEmployees.push_back(emp);  
        }
        simulation = false;
        recrutementDev = false;
        recrutementChef = false;

        for(auto it = allEmployees.begin(); it != allEmployees.end() ; it++)
        {
            if(it->role == 0)
            {
                nbDev++;
            }
            else
            {
                nbChef++;
            }
        }


        cout << "\t ===================== Parametres de la simulation =================" << endl << endl;
        cout << "\t\t Nombre de dev : " << nbDev <<  endl;
        cout << "\t\t Nombre de chef : " << nbChef <<  endl << endl;
        for(auto it = allProjects.begin(); it != allProjects.end() ; it++)
        {
            cout << "\t\t Nom du projet : " << it->name << endl;
            cout << "\t\t Multiplicateur : " << it->multiplicateur << endl << endl;
        }
        cout << "\t ===================================================================" << endl << endl;

        while(!toutFini)
        {

            if(days < 5)
            {
                for(auto it = allEmployees.begin(); it != allEmployees.end() ; it++)
                {
                    if(!it->CanWork(date.tm_mday,date.tm_mon + 1,date.tm_year + 1900))
                        continue;

                        
                    if(it->role == 0)
                    {
                        if(allProjects[projetDev].dev > 0)
                        {
                            allProjects[projetDev].dev-=allProjects[projetDev].multiplicateur;
                            if(allProjects[projetDev].dev < 0 && allProjects.size() > projetDev)
                            {
                            allProjects[projetDev + 1].dev += allProjects[projetDev].dev;
                            }

                        }
                        else if(allProjects.size() > projetDev)
                        {
                            allProjects[projetDev].jourFinDev = date.tm_mday;
                            allProjects[projetDev].moisFinDev = date.tm_mon + 1;
                            allProjects[projetDev].anneeFinDev = date.tm_year + 1900;
                            projetDev++;
                            allProjects[projetDev].dev-= allProjects[projetDev].multiplicateur;
                        }
                    }
                    else if(it->role == 1)
                    {
                        if(allProjects[projetChef].gestion > 0)
                        {
                            allProjects[projetChef].gestion-=allProjects[projetChef].multiplicateur;
                            if(allProjects[projetChef].gestion < 0 && allProjects.size() > projetChef)
                            {
                                allProjects[projetChef + 1].gestion += allProjects[projetChef].gestion;
                            }

                        }
                        else if(allProjects.size() > projetChef)
                        {
                            allProjects[projetChef].jourFinChef = date.tm_mday;
                            allProjects[projetChef].moisFinChef = date.tm_mon + 1;
                            allProjects[projetChef].anneeFinChef = date.tm_year + 1900;
                            projetChef++;
                            allProjects[projetChef].gestion-= allProjects[projetChef].multiplicateur;
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
            it->gestion = it->gestionBase;
            it->dev = it->devBase;
            if(!it->NotOverlapDev() && !it->NotOverlapChef())
            {
                cout << "Le projet " << it->name << " est dans les temps, il devait finir le " 
                << asctime(&getDate(dateTemp, it->jour, it->mois, it->annee)) << ", les devs ont fini le "
                << asctime(&getDate(dateTemp, it->jourFinDev, it->moisFinDev, it->anneeFinDev)) << " et les chefs ont fini le "
                << asctime(&getDate(dateTemp, it->jourFinChef, it->moisFinChef, it->anneeFinChef)) << endl;


            }
            else if(it->NotOverlapDev() && it->NotOverlapChef())
            {
                if(it->multiplicateur < 1.2)
                {
                    it->multiplicateur += 0.05;
                }
                else
                {
                    it->multiplicateur = 0.8;
                    recrutementDev = true;
                    recrutementChef = true;
                }
                
                cout << "Le projet " << it->name << " est en retard, il devait finir le " 
                << asctime(&getDate(dateTemp, it->jour, it->mois, it->annee)) << ", les devs ont fini en retard le "
                << asctime(&getDate(dateTemp, it->jourFinDev, it->moisFinDev, it->anneeFinDev)) << "  et les chefs ont fini en retard le "
                << asctime(&getDate(dateTemp, it->jourFinChef, it->moisFinChef, it->anneeFinChef)) << endl;

                simulation = true;
            }
            else if(it->NotOverlapChef())
            {
                cout << "Le projet " << it->name << " est en retard, il devait finir le " 
                << asctime(&getDate(dateTemp, it->jour, it->mois, it->annee)) << ", les devs ont fini le "
                << asctime(&getDate(dateTemp, it->jourFinDev, it->moisFinDev, it->anneeFinDev)) << "  mais les chefs ont fini en retard le "
                << asctime(&getDate(dateTemp, it->jourFinChef, it->moisFinChef, it->anneeFinChef)) << endl;

                if(it->multiplicateur < 1.2)
                {
                    it->multiplicateur += 0.05;
                }
                else
                {
                    it->multiplicateur = 0.8;
                    recrutementChef = true;
                }

                simulation = true;
            }
            else if(it->NotOverlapDev())
            {
                cout << "Le projet " << it->name << " est en retard, il devait finir le " 
                << asctime(&getDate(dateTemp, it->jour, it->mois, it->annee)) << ", les devs ont fini en retard le "
                << asctime(&getDate(dateTemp, it->jourFinDev, it->moisFinDev, it->anneeFinDev)) << "  et les chefs ont fini le "
                << asctime(&getDate(dateTemp, it->jourFinChef, it->moisFinChef, it->anneeFinChef)) << endl;

                if(it->multiplicateur < 1.2)
                {
                    it->multiplicateur += 0.05;
                }
                else
                {
                    it->multiplicateur = 0.8;
                    recrutementDev = true;
                    recrutementChef = true;
                }

                simulation = true;
            }
        }

        cout << "Nombre de jours : " << counter << endl;
        cout << "Fin prévue : " << asctime(&date) << endl;

    }



    return 0;
}
