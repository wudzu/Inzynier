#ifndef REDUKCJA_H_INCLUDED
#define REDUKCJA_H_INCLUDED

#include "szyfrowanie.h"

struct redukcja
{
public:
    redukcja(int n);
    void reset (int n);
    void f(slowo& mes);
    void ustaw(unsigned char n, unsigned char a);
    void ustaw(unsigned char* tab, int n);
private:
    std::vector<unsigned char> dane;
};

struct redukcja16
{
public:
    redukcja16();
    void reset();
    void f(unsigned short &mes);

private:
    std::vector<unsigned char> dane;
};

void testowanie();

#endif // REDUKCJA_H_INCLUDED
