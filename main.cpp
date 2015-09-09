#include "szyfrowanie.h"

using namespace std;

FILE* plik;


unsigned int t;

unsigned int m;



int main()
{
    bool dziala=1;
    Menu m;
    while(dziala)
    {
       m.menu();
       printf("Kontynuowac?\n");
       scanf("%d",&dziala);
    }

}













