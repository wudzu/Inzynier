#include "szyfrowanie.h"

tablicaR16::tablicaR16()
{

}

unsigned int tablicaR16::getPudla()
{
    return pudla;
}

void tablicaR16::wypelnij(unsigned short& daneMessage, unsigned int& daneT, unsigned int& daneM)
{

    pudla=0;
    plaintext=daneMessage;


    t=daneT;
    m=daneM;

    unsigned short pomt=1,aktualny;
    unsigned short C;
    unsigned short klucz;

    tablica.clear();
    dlugosc.clear();
    funkcjaRedukcji.reset();

    EPSP16 pom1;

    for(int i=0; i<m; i++)
	{

            do
            {
            klucz=rand();

			pom1.SP=klucz;

            for (aktualny=0;!(aktualny>=t || !(klucz&0xfc00));++aktualny) // miejsce 1.
            {
                szyfrowanie16 (plaintext, klucz, C);
                funkcjaRedukcji.f(C);
                klucz=C;
            }
            } while (klucz&0xfc00); // miejsce 2.

            if (aktualny>pomt)
                pomt=aktualny;

            pom1.EP=klucz;


        dlugosc.push_back(aktualny);
        tablica.push_back(pom1);


	}
	t=pomt;

	sortowanie( 0,m-1);


}

void tablicaR16::sortowanie(int left, int right)
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
            std::swap( dlugosc[i]    , dlugosc[j]);
            i++;
            j--;
        }

    } while(i<=j);

    if(left<j) sortowanie(left,j);
    if(right>i) sortowanie(i,right);
}

int tablicaR16::szukanie(unsigned short szukana, int left, int right)
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

void tablicaR16::pozostale(int& pocz, int& kon)
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

bool tablicaR16::sprawdz(unsigned short C0, unsigned short test1, unsigned short test2)
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
        if (!(element&0xfc00))  // miejsce 3. i ostatnie
        {
        pozycja=szukanie(element,0,m-1);
        if (pozycja!=-1)
        {

        //printf("\n%d %d", &tablica[pozycja].EP.bajt[0], &tablica[pozycja].EP.bajt[1]);
        pozostale(pozycja,koniec);
        for (;pozycja<=koniec;pozycja++)
        {
            if(dlugosc[pozycja]>=i)
            {

            //printf("%d %d\n", klucz.bajt[1],klucz.bajt[0]);
            //printf("%d %d\n", tablica[pozycja].SP.bajt[0], tablica[pozycja].SP.bajt[1]);
            //printf("%d %d\n\n", tablica[pozycja].EP.bajt[0], tablica[pozycja].EP.bajt[1]);

            odtwarzanie[0]=tablica[pozycja].SP;
            for (int j=1;j<dlugosc[pozycja];++j)
            {
                szyfrowanie16(plaintext,odtwarzanie[j-1],odtwarzanie[j]);
                funkcjaRedukcji.f(odtwarzanie[j]);
                //printf("%d : %d %d\n", j, odtwarzanie[j].bajt[0],odtwarzanie[j].bajt[1]);
            }
            odtwarzanie[t]=tablica[pozycja].EP;
            if ((odtwarzanie[dlugosc[pozycja]-i+1]== C0) )
            {
                unsigned short test01,test02;
                szyfrowanie16(plaintext+1,odtwarzanie[dlugosc[pozycja]-i],test01);
                szyfrowanie16(plaintext+256,odtwarzanie[dlugosc[pozycja]-i],test02);
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
        }
        }
        szyfrowanie16(plaintext, elementpop, element);
        funkcjaRedukcji.f(element);
        elementpop=element;
    }

    delete [] odtwarzanie;

    return 0;
}

int tablicaR16::getT()
{
    return t;
}



