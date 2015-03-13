
#include "szyfrowanie.h"

tablicaH::tablicaH(): funkcjaRedukcji(1)
{

}

tablicaH::tablicaH(int n): funkcjaRedukcji(n)
{

}

tablicaH::~tablicaH()
{

}

unsigned int tablicaH::getPudla()
{
    return pudla;
}

void tablicaH::wypelnij(slowo& daneMessage, unsigned char& daneN, unsigned int& daneT, unsigned int& daneM)
{
    int* prime=liczbypierwsze();

    pudla=0;
    plaintext=daneMessage;

    n=daneN;
    t=daneT;
    m=daneM;

    //slowo P(n);
    slowo klucz(n);
    slowo C(n);

    tablica.clear();
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
                szyfrowanie (plaintext, klucz, C, prime);
                funkcjaRedukcji.f(C);
                klucz=C;
            }

            pom1.EP=klucz;



        tablica.push_back(pom1);


	}

	sortowanie( 0,m-1);
	delete [] prime;
}

void tablicaH::sortowanie(int left, int right)
{

    int i = left;
    int j = right;
    int x = tablica[(left+right)/2].EP.liczba();

    slowo pom0;

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

int tablicaH::szukanie(slowo szukana, int left, int right)
{
    int middle;
    int temp;

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

bool tablicaH::sprawdz(slowo C0, slowo klucz)
{
    int* prime=liczbypierwsze();
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
                szyfrowanie(plaintext,odtwarzanie[j-1],odtwarzanie[j],prime);
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
                    delete [] prime;
                    return 1;
                }
                else
                {
                    ++pudla;
                }
            }
        }
        }
        szyfrowanie(plaintext, elementpop, element, prime);
        funkcjaRedukcji.f(element);
        elementpop=element;
    }

    //printf("\n\n Szansa trafienia to %0.000f \n\n ", procent);

    delete [] odtwarzanie;
    delete [] prime;
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
