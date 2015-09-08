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
#include <time.h>
#include <random>

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

struct EPSP16
{
    unsigned short SP;
    unsigned short EP;
};

struct EPSP32
{
    unsigned int SP;
    unsigned int EP;
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
    unsigned int pudla;

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
    unsigned int getPudla();
};

struct tablicaH16
{
    private:
    unsigned short plaintext;
    std::vector<EPSP16> tablica;
    redukcja16 funkcjaRedukcji;
    unsigned int t;
    unsigned int m;
    unsigned int pudla;

    public:
    tablicaH16();
    void wypelnij(unsigned short& daneMessage, unsigned int& daneT, unsigned int& daneM);
    //void ustawGlowne();
    void sortowanie(int left, int right);
    bool sprawdz(unsigned short C0, unsigned short test1, unsigned short test2);
    int szukanie(unsigned short szukana, int left, int right);
    void pozostale(int& pocz, int& kon);
    unsigned int getPudla();
};

struct tablicaH32
{
    private:
    unsigned int plaintext;
    std::vector<EPSP32> tablica;
    redukcja32 funkcjaRedukcji;
    unsigned int t;
    unsigned int m;
    unsigned int pudla;

    public:
    tablicaH32();
    void wypelnij(unsigned int& daneMessage, unsigned int& daneT, unsigned int& daneM);
    //void ustawGlowne();
    void sortowanie(int left, int right);
    bool sprawdz(unsigned int C0, unsigned int test1, unsigned int test2);
    int szukanie(unsigned int szukana, int left, int right);
    void pozostale(int& pocz, int& kon);
    unsigned int getPudla();
    void dodajT(int dt);
    void dodajM(int dm);
};

struct tablicaT16
{
    private:
    unsigned short plaintext;
    std::vector<EPSP16> tablica;
    std::vector<redukcja16> funkcjaRedukcji;
    unsigned int t;
    unsigned int m;
    unsigned int pudla;

    public:
    tablicaT16();
    void wypelnij(unsigned short& daneMessage, unsigned int& daneT, unsigned int& daneM);
    //void ustawGlowne();
    void sortowanie(int left, int right);
    bool sprawdz(unsigned short C0, unsigned short test1, unsigned short test2);
    int szukanie(unsigned short szukana, int left, int right);
    void pozostale(int& pocz, int& kon);
    unsigned int getPudla();
};

struct tablicaT32
{
    private:
    unsigned int plaintext;
    std::vector<EPSP32> tablica;
    std::vector<redukcja32> funkcjaRedukcji;
    unsigned int t;
    unsigned int m;
    unsigned int pudla;

    public:
    tablicaT32();
    void wypelnij(unsigned int& daneMessage, unsigned int& daneT, unsigned int& daneM);
    //void ustawGlowne();
    void sortowanie(int left, int right);
    bool sprawdz(unsigned int C0, unsigned int test1, unsigned int test2);
    int szukanie(unsigned int szukana, int left, int right);
    void pozostale(int& pocz, int& kon);
    unsigned int getPudla();
};

struct tablicaR16
{
    private:
    unsigned short plaintext;
    std::vector<EPSP16> tablica;
    std::vector<unsigned int> dlugosc;
    redukcja16 funkcjaRedukcji;
    unsigned int t;
    unsigned int m;
    unsigned int pudla;

    public:
    int getT();
    tablicaR16();
    void wypelnij(unsigned short& daneMessage, unsigned int& daneT, unsigned int& daneM);
    //void ustawGlowne();
    void sortowanie(int left, int right);
    bool sprawdz(unsigned short C0, unsigned short test1, unsigned short test2);
    int szukanie(unsigned short szukana, int left, int right);
    void pozostale(int& pocz, int& kon);
    unsigned int getPudla();
};

struct tablicaR32
{
    private:
    unsigned int plaintext;
    std::vector<EPSP32> tablica;
    std::vector<unsigned int> dlugosc;
    redukcja32 funkcjaRedukcji;
    unsigned int t;
    unsigned int m;
    unsigned int pudla;
    unsigned int pRozroznialny;

    public:
    int getT();
    tablicaR32();
    void wypelnij(unsigned int& daneMessage, unsigned int& daneT, unsigned int& daneM, unsigned int zera);
    //void ustawGlowne();
    void sortowanie(int left, int right);
    bool sprawdz(unsigned int C0, unsigned int test1, unsigned int test2);
    int szukanie(unsigned int szukana, int left, int right);
    void pozostale(int& pocz, int& kon);
    unsigned int getPudla();
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
        unsigned int pudla;
    public:
        hellman();
        ~hellman();
        void menuHellman();
        void menuHellmanZapis();
        void tworz();
        void tworz(unsigned char daneN, unsigned int daneT, unsigned int daneM, unsigned int daneR, slowo& plain);
        bool testuj(slowo& klucz);
        int statystyka();
};

struct hellman32
{
    private:
        std::vector<tablicaH32> tablica;
        unsigned int t;
        unsigned int m;
        unsigned int r;
        unsigned int plaintext;


    public:
        unsigned int pudla;
        hellman32();
        //~hellman16);
        void menuHellman();
        void menuHellmanZapis();
        void testowyMenuHellmanZapis();
        void dodajT(int dt);
        void dodajR(int dr);
        void dodajM(int dm);
        void tworz();
        void tworz(unsigned int daneT, unsigned int daneM, unsigned int daneR, unsigned int plain);
        bool testuj(unsigned int klucz);
        int statystyka();
        int testCzasuTworzenia();
        int testCzasuLamania();
};

struct hellman16
{
    private:
        std::vector<tablicaH16> tablica;
        unsigned int t;
        unsigned int m;
        unsigned int r;
        unsigned short plaintext;
        unsigned int pudla;

    public:
        hellman16();
        //~hellman16);
        void menuHellman();
        void menuHellmanZapis();
        void tworz();
        void tworz(unsigned int daneT, unsigned int daneM, unsigned int daneR, unsigned short plain);
        bool testuj(unsigned short klucz);
        int statystyka();
        int testCzasuTworzenia();
        int testCzasuLamania();
};

struct rivest16
{
    private:
        std::vector<tablicaR16> tablica;
        unsigned int t;
        unsigned int m;
        unsigned int r;
        unsigned short plaintext;
        unsigned int pudla;

    public:
        rivest16();
        //~hellman16);
        void menuRivest();
        void menuRivestZapis();
        void tworz();
        void tworz(unsigned int daneT, unsigned int daneM, unsigned int daneR, unsigned short plain);
        bool testuj(unsigned short klucz);
        int statystyka();
        int testCzasuTworzenia();
        int testCzasuLamania();
};

struct rivest32
{
    private:
        std::vector<tablicaR32> tablica;
        unsigned int t;
        unsigned int m;
        unsigned int r;
        unsigned int plaintext;
        unsigned int pudla;
        unsigned int zera;

    public:
        rivest32();
        //~hellman16);
        unsigned int getSredniT();
        void menuRivest();
        void menuRivestZapis();
        void tworz();
        void tworz(unsigned int daneT, unsigned int daneM, unsigned int daneR, unsigned int plain, unsigned int zera);
        bool testuj(unsigned int klucz);
        int statystyka();
        int testCzasuTworzenia();
        int testCzasuLamania();
};

struct teczowa16
{
    private:
        tablicaT16 tablica;
        unsigned int t;
        unsigned int m;
        //unsigned int r;
        unsigned short plaintext;
        unsigned int pudla;

    public:
        teczowa16();
        //~hellman16);
        void menuTeczowa();
        void menuTeczowaZapis();
        void tworz();
        void tworz(unsigned int daneT, unsigned int daneM, unsigned short plain);
        bool testuj(unsigned short klucz);
        int statystyka();
        int testCzasuTworzenia();
        int testCzasuLamania();
};

struct teczowa32
{
    private:
        tablicaT32 tablica;
        unsigned int t;
        unsigned int m;
        //unsigned int r;
        unsigned int plaintext;
        unsigned int pudla;

    public:
        teczowa32();
        //~hellman16);
        void menuTeczowa();
        void menuTeczowaZapis();
        void tworz();
        void tworz(unsigned int daneT, unsigned int daneM, unsigned int plain);
        bool testuj(unsigned int klucz);
        int statystyka();
        int testCzasuTworzenia();
        int testCzasuLamania();
};


void szyfrowanie(slowo & P, slowo & klucz, slowo & C);
void szyfrowanie16(unsigned short P, unsigned short klucz, unsigned short &C);
void szyfrowanie32(unsigned int P, unsigned int klucz, unsigned int &C);
void sBoxy(slowo & mes);
void sBoxy16(unsigned short & mes);
void sBoxy32(unsigned int & mes);
void permutacja(slowo & mes);
void permutacja16(unsigned short &mes);
void permutacja32(unsigned int &mes);
void przesuniecieprawo(slowo & klucz, unsigned char przes);
void przesuniecieprawo16 (unsigned short &m, unsigned char przes);
void przesuniecieprawo32(unsigned int &m, unsigned char przes);
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

unsigned int getRand32();

#endif // SZYFROWANIE_H_INCLUDED
