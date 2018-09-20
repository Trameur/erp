#include <stdio.h>
#include<iostream>

using namespace std;


void readConfiguration(char *filename)
{
    cout << filename << endl;
}

int main (int argc, char *argv[])
{   

    if(argc < 2)
        cout << "Error usage " << argv[0] << " [filename]" << endl;
    else
    {
        readConfiguration(argv[1]);
    }
    
    



    return 0;
}