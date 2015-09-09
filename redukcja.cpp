#include "szyfrowanie.h"


redukcja16::redukcja16()
{
    bool powtorzenia;
    unsigned short a;
    for (int i=0;i<16;++i)
    {
        powtorzenia=1;
        while(powtorzenia)
        {
            a=rand()%16;
            powtorzenia=0;
            for (int j=0;j<i;++j)
            {
                if (dane[j]==a)
                {
                    powtorzenia=1;
                    break;
                }
            }
        }
        dane.push_back(a);
    }
}

redukcja32::redukcja32()
{
    bool powtorzenia;
    unsigned short a;
    for (int i=0;i<32;++i)
    {
        powtorzenia=1;
        while(powtorzenia)
        {
            a=rand()%32;
            powtorzenia=0;
            for (int j=0;j<i;++j)
            {
                if (dane[j]==a)
                {
                    powtorzenia=1;
                    break;
                }
            }
        }
        dane.push_back(a);
    }
}

void redukcja16::reset()
{
    dane.clear();
    bool powtorzenia;
    unsigned short a;
    for (int i=0;i<16;++i)
    {
        powtorzenia=1;
        while(powtorzenia)
        {
            a=rand()%16;
            powtorzenia=0;
            for (int j=0;j<i;++j)
            {
                if (dane[j]==a)
                {
                    powtorzenia=1;
                    break;
                }
            }
        }
        dane.push_back(a);
    }
}

void redukcja32::reset()
{
    dane.clear();
    bool powtorzenia;
    unsigned short a;
    for (int i=0;i<32;++i)
    {
        powtorzenia=1;
        while(powtorzenia)
        {
            a=rand()%32;
            powtorzenia=0;
            for (int j=0;j<i;++j)
            {
                if (dane[j]==a)
                {
                    powtorzenia=1;
                    break;
                }
            }
        }
        dane.push_back(a);
    }
}

void redukcja16::f(unsigned short & mes)
{
    unsigned short pom=0;
    for (int i=0;i<16;++i)
    {
        if (mes&(1 << dane[i]))
            pom|=1<<i;
    }
    mes=pom;
}

void redukcja32::f(unsigned int & mes)
{
    unsigned int pom=0;
    for (int i=0;i<32;++i)
    {
        if (mes&(1 << dane[i]))
            pom|=1<<i;
    }
    mes=pom;
}

