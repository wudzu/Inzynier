
#include "szyfrowanie.h"

tablicaH::tablicaH(): funkcjaRedukcji(1)
{

}

tablicaH::tablicaH(int n): funkcjaRedukcji(n*8)
{

}

tablicaH::~tablicaH()
{

}

void tablicaH::wypelnij(slowo& daneMessage, unsigned char& daneN, unsigned int& daneT, unsigned int& daneM)
{
    int* prime=liczbypierwsze();

    plaintext=daneMessage;

    n=daneN;
    t=daneT;
    m=daneM;
    for (int k=0;k<n;++k)
        printf("%d ",plaintext.bajt[k]);
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
            printf( "pom1 jest rowne ");
            for (int k=0;k<n;++k)
                printf("%d ",pom1.EP.bajt[k]);
            printf("\nCala macierz: \n");



        tablica.push_back(pom1);

        for (int j=0;j<i;++j)
        {
            printf("%d\t",j);
            for (int k=0;k<n;++k)
                printf("%d ",(tablica[j].EP.bajt[k]));
            printf("\n");
        }

	}
	printf("\n\n%d ",tablica[m-1].EP.liczba());
	sortowanie( 0,m-1);
	delete [] prime;
}

void tablicaH::sortowanie(int left, int right)
{
    printf("l%d#%d",left,right);
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

    if(left<j) Sortowanie(left,j);
    if(right>i) Sortowanie(i,right);
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
    while(pocz-1)
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

bool tablicaH::sprawdz(slowo& C0)
{
    int* prime=liczbypierwsze();
    int pozycja;
    int koniec=1;
    slowo element(n), elementpop(n);

    slowo* odtwarzanie;
    odtwarzanie = new slowo [t];
    funkcjaRedukcji.f(C0);
    element=elementpop=C0;


    for (int i=1;i<t-1;++i)
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
                szyfrowanie(P,odtwarzanie[j-1],odtwarzanie[j],prime);
                funkcjaRedukcji.f(odtwarzanie[j]);
                //printf("%d : %d %d\n", j, odtwarzanie[j].bajt[0],odtwarzanie[j].bajt[1]);
            }
            if ((odtwarzanie[t-i+1]== C0 ))
            {
                for (int b=0;b<n;++b)
                    printf("%d ", &(odtwarzanie[t-i].bajt[b]));

                delete [] odtwarzanie;
                delete [] prime;
                return 1;
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

//bool tablicaH::
