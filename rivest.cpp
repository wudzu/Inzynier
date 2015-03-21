#include "szyfrowanie.h"

rivest16::rivest16()
{

}

void rivest16::tworz()
{
    printf("\nPodaj maksymalne t: ");
    scanf("%d", &t);
    printf("\nPodaj m: ");
    scanf("%d", &m);
    printf("\nPodaj r: ");
    scanf("%d", &r);
    printf("Podaj plaintext (hexadecymalnie): ");
    scanf("%x", &plaintext);
    printf("Podaj seed liczb losowych: ");
    int a;
    scanf("%d", &a);
    srand(a);
    tworz(t,m,r,plaintext);

}

void rivest16::tworz(unsigned int daneT, unsigned int daneM, unsigned int daneR, unsigned short plain)
{
    tablica.clear();
    t=daneT+2;
    m=daneM;
    r=daneR;

    plaintext=plain;
    tablicaR16 pom1;
    int a=0;
    for (int i=0;i<r;++i)
    {
        pom1.wypelnij(plaintext, t, m);
        tablica.push_back(pom1);
        if (pom1.getT()>a)
            a=pom1.getT();
        //printf("Tablica %d -ta stworzona\n",i);
    }
    t=a;
}

bool rivest16::testuj(unsigned short klucz)
{
    unsigned short C0;
    unsigned short test1,test2;
    szyfrowanie16 (plaintext+1,     klucz, test1);
    szyfrowanie16 (plaintext+256,   klucz, test2);
    szyfrowanie16 (plaintext, klucz, C0);
    for (int i=0;i<r;++i)
    {
        if (tablica[i].sprawdz(C0, test1, test2))
        {
            //printf("\n%x",klucz);

            return 1;
            break;
        }
    }


    return 0;
}

int rivest16::statystyka()
{
    int trafienia=0;
    for (int i=0;i<65536;++i)
    {

            if (testuj(i))
                ++trafienia;

    }
    pudla=0;
    for (int i=0;i<r;++i)
    {
        pudla+=tablica[i].getPudla();
    }
    return trafienia;
}

void rivest16::menuRivest()
{
    tworz();
    printf("Stworzono.\n");
    printf("\n\n%d\n\n",statystyka());
    printf("%d", pudla);
}
