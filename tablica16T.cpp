#include "szyfrowanie.h"

tablicaT16::tablicaT16()
{

}

tablicaT32::tablicaT32()
{

}

unsigned int tablicaT16::getPudla()
{
    return pudla;
}

unsigned int tablicaT32::getPudla()
{
    return pudla;
}

void tablicaT16::wypelnij(unsigned short& daneMessage, unsigned int& daneT, unsigned int& daneM)
{

    pudla=0;
    plaintext=daneMessage;


    t=daneT;
    m=daneM;

    unsigned short C;
    unsigned short klucz;

    redukcja16 pom2;
    funkcjaRedukcji.clear();
    for (int i=0;i<t;++i)
    {
        pom2.reset();
        funkcjaRedukcji.push_back(pom2);
    }
    tablica.clear();
    tablica.resize(m);
    //funkcjaRedukcji.reset();

    EPSP16 pom1;

    for(int i=0; i<m; i++)
	{
	    klucz=rand();

			pom1.SP=klucz;

            for (int k=0;k<t;++k)
            {
                szyfrowanie16 (plaintext, klucz, C);
                funkcjaRedukcji[k].f(C);
                klucz=C;
            }

            pom1.EP=klucz;



        //tablica.push_back(pom1);
        tablica[i]=pom1;

	}

	sortowanie( 0,m-1);


}

void tablicaT32::wypelnij(unsigned int& daneMessage, unsigned int& daneT, unsigned int& daneM)
{

    pudla=0;
    plaintext=daneMessage;


    t=daneT;
    m=daneM;

    unsigned int C;
    unsigned int klucz;

    redukcja32 pom2;
    funkcjaRedukcji.clear();
    for (int i=0;i<t;++i)
    {
        pom2.reset();
        funkcjaRedukcji.push_back(pom2);
    }
    tablica.clear();
    tablica.resize(m);
    //funkcjaRedukcji.reset();

    EPSP32 pom1;

    for(int i=0; i<m; i++)
	{
	    klucz=rand()*rand();

			pom1.SP=klucz;

            for (int k=0;k<t;++k)
            {
                szyfrowanie32 (plaintext, klucz, C);
                funkcjaRedukcji[k].f(C);
                klucz=C;
            }

            pom1.EP=klucz;



        //tablica.push_back(pom1);
        tablica[i]=pom1;

	}

	sortowanie( 0,m-1);


}

void tablicaT16::sortowanie(int left, int right)
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

void tablicaT32::sortowanie(int left, int right)
{

    int i = left;
    int j = right;
    unsigned int x = tablica[(left+right)/2].EP;

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

int tablicaT16::szukanie(unsigned short szukana, int left, int right)
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

int tablicaT32::szukanie(unsigned int szukana, int left, int right)
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

void tablicaT16::pozostale(int& pocz, int& kon)
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

void tablicaT32::pozostale(int& pocz, int& kon)
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

bool tablicaT16::sprawdz(unsigned short C0, unsigned short test1, unsigned short test2)
{
    int pozycja;
    int koniec=1;
    unsigned short element=C0, elementpop, C;

    unsigned short* odtwarzanie;
    odtwarzanie= new unsigned short [t+1];
    funkcjaRedukcji[t-1].f(element);

    C=elementpop=element;


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
                szyfrowanie16(plaintext,odtwarzanie[j-1],odtwarzanie[j]);
                funkcjaRedukcji[j-1].f(odtwarzanie[j]);
                //printf("%d : %d %d\n", j, odtwarzanie[j].bajt[0],odtwarzanie[j].bajt[1]);
            }
            odtwarzanie[t]=tablica[pozycja].EP;
            if ((odtwarzanie[t-i+1]== C) )
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
        C=C0;
        funkcjaRedukcji[t-i-1].f(C);
        element=elementpop=C;
        for (int k=0;k<i;++k)
        {
            szyfrowanie16(plaintext,elementpop,element);
            funkcjaRedukcji[t-i+k].f(element);
            elementpop=element;
        }
        //szyfrowanie16(plaintext, elementpop, element);
        //funkcjaRedukcji[i].f(element);
        //elementpop=element;
    }

    delete [] odtwarzanie;

    return 0;
}

bool tablicaT32::sprawdz(unsigned int C0, unsigned int test1, unsigned int test2)
{
    int pozycja;
    int koniec=1;
    unsigned int element=C0, elementpop, C;

    unsigned int* odtwarzanie;
    odtwarzanie= new unsigned int [t+1];
    funkcjaRedukcji[t-1].f(element);

    C=elementpop=element;


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
                szyfrowanie32(plaintext,odtwarzanie[j-1],odtwarzanie[j]);
                funkcjaRedukcji[j-1].f(odtwarzanie[j]);
                //printf("%d : %d %d\n", j, odtwarzanie[j].bajt[0],odtwarzanie[j].bajt[1]);
            }
            odtwarzanie[t]=tablica[pozycja].EP;
            if ((odtwarzanie[t-i+1]== C) )
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
        C=C0;
        funkcjaRedukcji[t-i-1].f(C);
        element=elementpop=C;
        for (int k=0;k<i;++k)
        {
            szyfrowanie32(plaintext,elementpop,element);
            funkcjaRedukcji[t-i+k].f(element);
            elementpop=element;
        }
        //szyfrowanie16(plaintext, elementpop, element);
        //funkcjaRedukcji[i].f(element);
        //elementpop=element;
    }

    delete [] odtwarzanie;

    return 0;
}
