#include "szyfrowanie.h"

using namespace std;

FILE* plik;
unsigned char n=2;
struct EPSP;
redukcja currentRedukcja(n);
std::vector<EPSP> tablica;
unsigned int t;
slowo wejscie(n);
unsigned int m;

unsigned char sBox01(unsigned char wejscie);
unsigned char sBox23(unsigned char wejscie);
bool jestTablica=0;

int main()
{
    bool dziala=1;
    while(dziala)
    {
       menu();
       printf("Kontynuowac?\n");
       scanf("%d",&dziala);
    }

}













