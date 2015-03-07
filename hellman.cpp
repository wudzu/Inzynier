#include "szyfrowanie.h"

void hellman::tworz()
{
    printf("\n\nPodaj n: ");
    scanf("%d", &n);
    printf("\nPodaj t: ");
    scanf("%d", &t);
    printf("\nPodaj m: ");
    scanf("%d", &m);
    printf("\nPodaj r: ");
    scanf("%d", &r);
    slowo pom(n);
    printf("Podaj plaintext: ");
    for (int i=0;i<n;++i)
    scanf("%d", &(pom.bajt[i]));
    printf("Podaj seed liczb losowych: ");
    int a;
    scanf("%d", &a);
    srand(a);
    plaintext=pom;
    tablicaH pom1(n);
    for (int i=0;i<r;++i)
    {
        pom1.wypelnij(plaintext, n, t, m);
        tablica.push_back(pom1);
        printf("Tablica %d -ta stworzona",i);
    }

}

bool hellman::testuj(slowo& klucz)
{
    int* prime=liczbypierwsze();
    slowo C0;
    bool jest=0;
    szyfrowanie (plaintext, klucz, C0, prime);
    for (int i=0;i<r;++i)
    {
        if (tablica[i].sprawdz(C0))
        {
            jest=1;
            break;
        }
    }

    delete [] prime;
    return jest;
}

int hellman::statystyka()
{
    int trafienia=0;
    slowo klucz(n);
    for (int i=0;i<256;++i)
    {
        klucz.bajt[1]=i;
        for (int j=0;j<256;++j)
        {
            klucz.bajt[0]=j;
            if (testuj(klucz))
                ++trafienia;
        }
    }
    return trafienia;
}

void hellman::menuHellman()
{
    tworz();
    printf("Stworzono.");
    printf("\n\n%d\n\n",statystyka());
}

hellman::hellman()
{

}

hellman::~hellman()
{

}
