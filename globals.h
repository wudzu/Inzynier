#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

#include "szyfrowanie.h"

extern	FILE* plik;
struct slowo;
struct redukcja;
extern slowo P;
extern unsigned char n;
extern unsigned int m;
extern unsigned int t;
extern redukcja currentRedukcja;
struct EPSP;
extern std::vector<EPSP> tablica;
extern unsigned char sBox01(unsigned char wejscie);
extern unsigned char sBox23(unsigned char wejscie);
extern bool jestTablica;
//extern int prime[25];

#endif // GLOBALS_H_INCLUDED
