
#include "szyfrowanie.h"



tablicaH32::tablicaH32()
{

}

tablicaH16::tablicaH16()
{

}

unsigned int tablicaH16::getPudla()
{
    return pudla;
}

unsigned int tablicaH32::getPudla()
{
    return pudla;
}

void tablicaH32::wypelnij(unsigned int& daneMessage, unsigned int& daneT, unsigned int& daneM)
{
    pudla=0;
    plaintext=daneMessage;

    t=daneT;
    m=daneM;

    unsigned int C;
    unsigned int klucz;

    tablica.clear();
    tablica.resize(m);
    funkcjaRedukcji.reset();

    EPSP32 pom1;

    for(int i=0; i<m; i++)
	{
	    klucz=getRand32();

        pom1.SP=klucz;

        for (int k=0;k<t;++k)
        {
            szyfrowanie32 (plaintext, klucz, C);
            funkcjaRedukcji.f(C);
            klucz=C;
        }

        pom1.EP=klucz;

        tablica[i]=pom1;
	}

	sortowanie( 0,m-1);
}

void tablicaH16::wypelnij(unsigned short& daneMessage, unsigned int& daneT, unsigned int& daneM)
{
    pudla=0;
    plaintext=daneMessage;

    t=daneT;
    m=daneM;

    unsigned short C;
    unsigned short klucz;

    tablica.clear();
    tablica.resize(m);
    funkcjaRedukcji.reset();

    EPSP16 pom1;

    for(int i=0; i<m; i++)
	{
	    klucz=rand();

        pom1.SP=klucz;

        for (int k=0;k<t;++k)
        {
            szyfrowanie16 (plaintext, klucz, C);
            funkcjaRedukcji.f(C);
            klucz=C;
        }

        pom1.EP=klucz;

        tablica[i]=pom1;
	}

	sortowanie( 0,m-1);
}

void tablicaH32::sortowanie(int left, int right)
{
    int i = left;
    int j = right;
    int x = tablica[(left+right)/2].EP;

    do
    {
        while(tablica[i].EP>x )
            i++;

        while(tablica[j].EP<x )
            j--;

        if(i<= j)
        {
            std::swap( tablica[i].EP, tablica[j].EP );
            std::swap( tablica[i].SP, tablica[j].SP );
            i++;
            j--;
        }

    } while(i<=j);

    if(left<j) sortowanie(left,j);
    if(right>i) sortowanie(i,right);
}

void tablicaH16::sortowanie(int left, int right)
{

    int i = left;
    int j = right;
    int x = tablica[(left+right)/2].EP;

    do
    {
        while(tablica[i].EP>x )
            i++;

        while(tablica[j].EP<x )
            j--;

        if(i<= j)
        {
            std::swap( tablica[i].EP, tablica[j].EP );
            std::swap( tablica[i].SP, tablica[j].SP );
            i++;
            j--;
        }

    } while(i<=j);

    if(left<j) sortowanie(left,j);
    if(right>i) sortowanie(i,right);
}

int tablicaH32::szukanie(unsigned int szukana, int left, int right)
{
    int middle;

    while (left <= right)
    {
        middle = (left + right)/2;

        if (tablica[middle].EP == szukana)
            return middle;
        else if (tablica[middle].EP < szukana)
            right=middle-1;
        else
            left=middle+1;
      }
      return -1;
}

int tablicaH16::szukanie(unsigned short szukana, int left, int right)
{
    int middle;

    while (left <= right)
    {
        middle = (left + right)/2;

        if (tablica[middle].EP == szukana)
            return middle;
        else if (tablica[middle].EP < szukana)
            right=middle-1;
        else
            left=middle+1;
    }
      return -1;
}

void tablicaH32::pozostale(int& pocz, int& kon)
{
    int a=pocz;
    kon=pocz;

    while(pocz-1>0)
    {
        if (tablica[a].EP == tablica[pocz-1].EP)
        {
            pocz--;
        }
        else
            break;
    }
    while(kon+1 < m)
    {
        if (tablica[a].EP == tablica[kon+1].EP)
        {
            kon++;
        }
        else
            break;
    }
}

void tablicaH16::pozostale(int& pocz, int& kon)
{
    int a=pocz;
    kon=pocz;

    while(pocz-1>0)
    {
        if (tablica[a].EP == tablica[pocz-1].EP)
        {
            pocz--;
        }
        else
            break;
    }
    while(kon+1 < m)
    {
        if (tablica[a].EP == tablica[kon+1].EP)
        {
            kon++;
        }
        else
            break;
    }
}

bool tablicaH32::sprawdz(unsigned int C0, unsigned int test1, unsigned int test2)
{
    int pozycja;
    int koniec=1;
    unsigned int element, elementpop;

    unsigned int* odtwarzanie;
    odtwarzanie= new unsigned int [t+1];
    funkcjaRedukcji.f(C0);
    element=elementpop=C0;


    for (int i=1;i<t+1;++i)
    {
        pozycja=szukanie(element,0,m-1);
        if (pozycja!=-1)
        {
            pozostale(pozycja,koniec);

            for (;pozycja<=koniec;pozycja++)
            {
                odtwarzanie[0]=tablica[pozycja].SP;

                for (int j=1;j<t;++j)
                {
                    szyfrowanie32(plaintext,odtwarzanie[j-1],odtwarzanie[j]);
                    funkcjaRedukcji.f(odtwarzanie[j]);
                }

                odtwarzanie[t]=tablica[pozycja].EP;

                if ((odtwarzanie[t-i+1]== C0) )
                {
                    unsigned int test01,test02;
                    szyfrowanie32(plaintext+1,odtwarzanie[t-i],test01);
                    szyfrowanie32(plaintext+256,odtwarzanie[t-i],test02);
                    if ((test01 == test1) && (test02 == test2))
                    {
                        delete [] odtwarzanie;
                        return 1;
                    }
                    else
                    {
                        ++pudla;
                    }
                }
            }
        }
        szyfrowanie32(plaintext, elementpop, element);
        funkcjaRedukcji.f(element);
        elementpop=element;
    }

    delete [] odtwarzanie;

    return 0;
}

bool tablicaH16::sprawdz(unsigned short C0, unsigned short test1, unsigned short test2)
{
    int pozycja;
    int koniec=1;
    unsigned short element, elementpop;

    unsigned short* odtwarzanie;
    odtwarzanie= new unsigned short [t+1];
    funkcjaRedukcji.f(C0);
    element=elementpop=C0;

    for (int i=1;i<t+1;++i)
    {
        pozycja=szukanie(element,0,m-1);
        if (pozycja!=-1)
        {
            pozostale(pozycja,koniec);
            for (;pozycja<=koniec;pozycja++)
            {
                odtwarzanie[0]=tablica[pozycja].SP;

                for (int j=1;j<t;++j)
                {
                    szyfrowanie16(plaintext,odtwarzanie[j-1],odtwarzanie[j]);
                    funkcjaRedukcji.f(odtwarzanie[j]);
                }

                odtwarzanie[t]=tablica[pozycja].EP;

                if ((odtwarzanie[t-i+1]== C0) )
                {
                    unsigned short test01,test02;
                    szyfrowanie16(plaintext+1,odtwarzanie[t-i],test01);
                    szyfrowanie16(plaintext+256,odtwarzanie[t-i],test02);

                    if ((test01 == test1) && (test02 == test2))
                    {
                        delete [] odtwarzanie;
                        return 1;
                    }
                    else
                    {
                        ++pudla;
                    }
                }
            }
        }
        szyfrowanie16(plaintext, elementpop, element);
        funkcjaRedukcji.f(element);
        elementpop=element;
    }

    delete [] odtwarzanie;

    return 0;
}

void tablicaH32::dodajT(int dt)
{
    pudla=0;

    t+=dt;

    unsigned int C;
    unsigned int klucz;
    unsigned int pom0;

    for(int i=0; i<m; i++)
	{

			klucz=tablica[i].EP;

            for (int k=0;k<dt;++k)
            {
                szyfrowanie32 (plaintext, klucz, C);
                funkcjaRedukcji.f(C);
                klucz=C;
            }

            tablica[i].EP=klucz;
	}

	sortowanie( 0,m-1);
}


void tablicaH32::dodajM(int dm)
{
    pudla=0;

    m+=dm;

    unsigned int C;
    unsigned int klucz;

    EPSP32 pom1;

    for(int i=0; i<dm; i++)
	{
	    klucz=getRand32();

			pom1.SP=klucz;

            for (int k=0;k<t;++k)
            {
                szyfrowanie32 (plaintext, klucz, C);
                funkcjaRedukcji.f(C);
                klucz=C;
            }

        pom1.EP=klucz;

        tablica.push_back(pom1);
	}

	sortowanie( 0,m-1);
}
