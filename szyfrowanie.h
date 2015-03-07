#ifndef SZYFROWANIE_H_INCLUDED
#define SZYFROWANIE_H_INCLUDED

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <math.h>
#include "globals.h"
#include "redukcja.h"

struct slowo;
struct EPSP;

struct slowo
{
    unsigned char* bajt;
    unsigned char n;
    slowo();
    slowo(unsigned char a);
    slowo & operator= (const slowo &b);
    ~slowo() {delete [] bajt;};
    slowo & operator^ (const slowo &b);
    slowo & operator^=(const slowo &b);
    bool operator == (const slowo &b);
    slowo (const slowo& wzor);
    int liczba();
    void wypiszB();
};

struct EPSP
{
    slowo EP;
    slowo SP;
    EPSP(unsigned char a);
    EPSP(const EPSP &wzor);
};


void szyfrowanie(slowo & P, slowo & klucz, slowo & C, int* prime);
void sBoxy(slowo & mes);
void permutacja(slowo & mes);
void przesuniecielewo(slowo & klucz, unsigned char przes);
//void R(slowo & mes);
int* liczbypierwsze();
void Sortowanie( int left, int right);
bool test(slowo testowany, slowo klucz);

void menu();
void menuKlucza();
void tworzTablice();
void reszta(int& pocz, int& kon);
bool szukajKlucza( slowo klucz);
void zapisTablicy();
int Szukanie( slowo szukana, int left, int right);

#endif // SZYFROWANIE_H_INCLUDED
