#ifndef SZYFROWANIE_H_INCLUDED
#define SZYFROWANIE_H_INCLUDED

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <math.h>
#include "globals.h"
#include "redukcja.h"
#include "tablicaH.h"
#include "hellman.h"

struct slowo;
struct EPSP;
struct tablicaH;
struct hellman;

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

struct tablicaH
{
    private:
    slowo plaintext;
    std::vector<EPSP> tablica;
    redukcja funkcjaRedukcji;
    unsigned char n;
    unsigned int t;
    unsigned int m;

    public:
    tablicaH();
    tablicaH(int n);
    ~tablicaH();
    void wypelnij(slowo& daneMessage, unsigned char& daneN, unsigned int& daneT, unsigned int& daneM);
    //void ustawGlowne();
    void sortowanie(int left, int right);
    bool sprawdz(slowo C0, slowo klucz);
    int szukanie(slowo szukana, int left, int right);
    void pozostale(int& pocz, int& kon);
    void wypisz();
};

struct hellman
{
    private:
        std::vector<tablicaH> tablica;
        unsigned char n;
        unsigned int t;
        unsigned int m;
        unsigned int r;
        slowo plaintext;
    public:
        hellman();
        ~hellman();
        void menuHellman();
        void tworz();
        bool testuj(slowo& klucz);
        int statystyka();
};


void szyfrowanie(slowo & P, slowo & klucz, slowo & C, int* prime);
void sBoxy(slowo & mes);
void permutacja(slowo & mes);
void przesuniecieprawo(slowo & klucz, unsigned char przes);
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
