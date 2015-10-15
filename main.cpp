#include "szyfrowanie.h"

using namespace std;

FILE* plik;


unsigned int t;

unsigned int m;



int main()
{
    unsigned short P=0xabba;
    unsigned short K=0x0fac;
    unsigned short C;
    szyfrowanie16(P,K,C);
    /*
    bool dziala=1;
    Menu m;
    while(dziala)
    {
       m.menu();
       printf("Kontynuowac?\n");
       scanf("%d",&dziala);
    }
    */
}













