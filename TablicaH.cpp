
#include "szyfrowanie.h"

tablicaH::tablicaH(): funkcjaRedukcji(1)
{

}

tablicaH::tablicaH(int n): funkcjaRedukcji(n)
{

}

tablicaH32::tablicaH32()
{

}

tablicaH16::tablicaH16()
{

}

tablicaH::~tablicaH()
{

}

unsigned int tablicaH::getPudla()
{
    return pudla;
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
    std::random_device rd;
    std::mt19937 gen(rd());
    //std::uniform_int_distribution<unsigned int> dis(0,4294967295);

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
	    klucz=gen();

			pom1.SP=klucz;

            for (int k=0;k<t;++k)
            {
                szyfrowanie32 (plaintext, klucz, C);
                funkcjaRedukcji.f(C);
                klucz=C;
            }

            pom1.EP=klucz;


        tablica[i]=pom1;
        //tablica.push_back(pom1);


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
        //tablica.push_back(pom1);


	}

	sortowanie( 0,m-1);


}

void tablicaH::wypelnij(slowo& daneMessage, unsigned char& daneN, unsigned int& daneT, unsigned int& daneM)
{

    pudla=0;
    plaintext=daneMessage;

    n=daneN;
    t=daneT;
    m=daneM;

    //slowo P(n);
    slowo klucz(n);
    slowo C(n);

    tablica.clear();
    //tablica.resize(m);
    funkcjaRedukcji.reset(n);

    EPSP pom1(n);
	for(int i=0; i<m; i++)
	{
	    for (int j=0;j<n;++j)
        {
            klucz.bajt[j]=rand();
        }

			pom1.SP=klucz;

            for (int k=0;k<t;++k)
            {
                szyfrowanie (plaintext, klucz, C);
                funkcjaRedukcji.f(C);
                klucz=C;
            }

            pom1.EP=klucz;



        tablica.push_back(pom1);
        //tablica[i]=pom1;

	}

	sortowanie( 0,m-1);
}

void tablicaH32::sortowanie(int left, int right)
{
    int i = left;
    int j = right;
    int x = tablica[(left+right)/2].EP;

    //unsigned short pom0;

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

    //unsigned short pom0;

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

void tablicaH::sortowanie(int left, int right)
{

    int i = left;
    int j = right;
    int x = tablica[(left+right)/2].EP.liczba();

    //slowo pom0;

    do
    {
        while(tablica[i].EP.liczba()>x )
            i++;

        while(tablica[j].EP.liczba()<x )
            j--;

        if(i<= j)
        {
            std::swap( tablica[i].EP.bajt, tablica[j].EP.bajt );
            std::swap( tablica[i].SP.bajt, tablica[j].SP.bajt );
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
    //int temp;

      while (left <= right) {
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
    //int temp;

      while (left <= right) {
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

int tablicaH::szukanie(slowo szukana, int left, int right)
{
    int middle;
    //int temp;

      while (left <= right) {
            middle = (left + right)/2;

            if (tablica[middle].EP == szukana)
                  return middle;
            else if (tablica[middle].EP.liczba() < szukana.liczba())
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

void tablicaH::pozostale(int& pocz, int& kon)
{
    int a=pocz;
    kon=pocz;
    while(pocz-1>0)
    {
        if (tablica[a].EP.liczba() == tablica[pocz-1].EP.liczba())
        {
            pocz--;
        }
        else
            break;
    }
    while(kon+1 < m)
    {
        if (tablica[a].EP.liczba() == tablica[kon+1].EP.liczba())
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
        //printf("\n%d\n",m);

        pozycja=szukanie(element,0,m-1);
        if (pozycja!=-1)
        {

        //printf("\n%d %d", &tablica[pozycja].EP.bajt[0], &tablica[pozycja].EP.bajt[1]);
        pozostale(pozycja,koniec);
        for (;pozycja<=koniec;pozycja++)
        {
            //printf("%d %d\n", klucz.bajt[1],klucz.bajt[0]);
            //printf("%d %d\n", tablica[pozycja].SP.bajt[0], tablica[pozycja].SP.bajt[1]);
            //printf("%d %d\n\n", tablica[pozycja].EP.bajt[0], tablica[pozycja].EP.bajt[1]);

            odtwarzanie[0]=tablica[pozycja].SP;
            for (int j=1;j<t;++j)
            {
                szyfrowanie32(plaintext,odtwarzanie[j-1],odtwarzanie[j]);
                funkcjaRedukcji.f(odtwarzanie[j]);
                //printf("%d : %d %d\n", j, odtwarzanie[j].bajt[0],odtwarzanie[j].bajt[1]);
            }
            odtwarzanie[t]=tablica[pozycja].EP;
            if ((odtwarzanie[t-i+1]== C0) )
            {
                unsigned int test01,test02;
                szyfrowanie32(plaintext+1,odtwarzanie[t-i],test01);
                szyfrowanie32(plaintext+256,odtwarzanie[t-i],test02);
                if ((test01 == test1) && (test02 == test2))
                {

                    /*
                    for (int b=n-1;b>=0;--b)
                        printf("%d ", (odtwarzanie[t-i].bajt[b]));
                    printf("\n");
                    */
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
        //printf("\n%d\n",m);

        pozycja=szukanie(element,0,m-1);
        if (pozycja!=-1)
        {

        //printf("\n%d %d", &tablica[pozycja].EP.bajt[0], &tablica[pozycja].EP.bajt[1]);
        pozostale(pozycja,koniec);
        for (;pozycja<=koniec;pozycja++)
        {
            //printf("%d %d\n", klucz.bajt[1],klucz.bajt[0]);
            //printf("%d %d\n", tablica[pozycja].SP.bajt[0], tablica[pozycja].SP.bajt[1]);
            //printf("%d %d\n\n", tablica[pozycja].EP.bajt[0], tablica[pozycja].EP.bajt[1]);

            odtwarzanie[0]=tablica[pozycja].SP;
            for (int j=1;j<t;++j)
            {
                szyfrowanie16(plaintext,odtwarzanie[j-1],odtwarzanie[j]);
                funkcjaRedukcji.f(odtwarzanie[j]);
                //printf("%d : %d %d\n", j, odtwarzanie[j].bajt[0],odtwarzanie[j].bajt[1]);
            }
            odtwarzanie[t]=tablica[pozycja].EP;
            if ((odtwarzanie[t-i+1]== C0) )
            {
                unsigned short test01,test02;
                szyfrowanie16(plaintext+1,odtwarzanie[t-i],test01);
                szyfrowanie16(plaintext+256,odtwarzanie[t-i],test02);
                if ((test01 == test1) && (test02 == test2))
                {

                    /*
                    for (int b=n-1;b>=0;--b)
                        printf("%d ", (odtwarzanie[t-i].bajt[b]));
                    printf("\n");
                    */
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

bool tablicaH::sprawdz(slowo C0, slowo klucz)
{

    int pozycja;
    int koniec=1;
    slowo element(n), elementpop(n);

    slowo* odtwarzanie;
    odtwarzanie = new slowo [t];
    funkcjaRedukcji.f(C0);
    element=elementpop=C0;


    for (int i=1;i<t;++i)
    {
        //printf("\n%d\n",m);

        pozycja=szukanie(element,0,m-1);
        if (pozycja!=-1)
        {

        //printf("\n%d %d", &tablica[pozycja].EP.bajt[0], &tablica[pozycja].EP.bajt[1]);
        pozostale(pozycja,koniec);
        for (;pozycja<=koniec;pozycja++)
        {
            //printf("%d %d\n", klucz.bajt[1],klucz.bajt[0]);
            //printf("%d %d\n", tablica[pozycja].SP.bajt[0], tablica[pozycja].SP.bajt[1]);
            //printf("%d %d\n\n", tablica[pozycja].EP.bajt[0], tablica[pozycja].EP.bajt[1]);

            odtwarzanie[0]=tablica[pozycja].SP;
            for (int j=1;j<t;++j)
            {
                szyfrowanie(plaintext,odtwarzanie[j-1],odtwarzanie[j]);
                funkcjaRedukcji.f(odtwarzanie[j]);
                //printf("%d : %d %d\n", j, odtwarzanie[j].bajt[0],odtwarzanie[j].bajt[1]);
            }
            if ((odtwarzanie[t-i+1]== C0) )
            {
                if (odtwarzanie[t-i]== klucz)
                {

                    /*
                    for (int b=n-1;b>=0;--b)
                        printf("%d ", (odtwarzanie[t-i].bajt[b]));
                    printf("\n");
                    */
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
        szyfrowanie(plaintext, elementpop, element);
        funkcjaRedukcji.f(element);
        elementpop=element;
    }

    //printf("\n\n Szansa trafienia to %0.000f \n\n ", procent);

    delete [] odtwarzanie;

    return 0;
}

void tablicaH::wypisz()
{
    printf("\nSklad Tablicy:\nSP\nEP");
    for (int i=0;i<m;++i)
    {
        printf("\n");
        for (int j=n-1;j>=0;--j)
            printf("%d ", tablica[i].SP.bajt[j]);
        printf("\t");
        for (int j=n-1;j>=0;--j)
            printf("%d ", tablica[i].EP.bajt[j]);
    }
}

//bool tablicaH::
