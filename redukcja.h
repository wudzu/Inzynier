#ifndef REDUKCJA_H_INCLUDED
#define REDUKCJA_H_INCLUDED

#include "szyfrowanie.h"

struct redukcja16
{
public:
    redukcja16();
    void reset();
    void f(unsigned short &mes);

private:
    std::vector<unsigned char> dane;
};

struct redukcja32
{
public:
    redukcja32();
    void reset();
    void f(unsigned int &mes);

private:
    std::vector<unsigned char> dane;
};

void testowanie();

#endif // REDUKCJA_H_INCLUDED
