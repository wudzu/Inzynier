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
        printf("Tablica %d -ta stworzona\n",i);
    }
    pudla=0;

}

void hellman::tworz(unsigned char daneN, unsigned int daneT, unsigned int daneM, unsigned int daneR, slowo& plain)
{
    tablica.clear();
    n=daneN;
    t=daneT;
    m=daneM;
    r=daneR;

    plaintext=plain;
    tablicaH pom1(n);
    for (int i=0;i<r;++i)
    {
        pom1.wypelnij(plaintext, n, t, m);
        tablica.push_back(pom1);
        //printf("Tablica %d -ta stworzona\n",i);
    }
}

bool hellman::testuj(slowo& klucz)
{
    int* prime=liczbypierwsze();
    slowo C0;
    //bool jest=0;
    szyfrowanie (plaintext, klucz, C0, prime);
    for (int i=0;i<r;++i)
    {
        if (tablica[i].sprawdz(C0, klucz))
        {
            delete [] prime;
            return 1;
            break;
        }
    }

    delete [] prime;
    return 0;
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
    pudla=0;
    for (int i=0;i<r;++i)
    {
        pudla+=tablica[i].getPudla();
    }
    return trafienia;
}

void hellman::menuHellman()
{
    tworz();
    printf("Stworzono.\n");
    printf("\n\n%d\n\n",statystyka());
    printf("%d", pudla);
}

void hellman::menuHellmanZapis()
{
    unsigned int pom[4],pom4,rodzaj,wzrost,krok;

    printf("\n\nPodaj n: ");
    scanf("%d", &pom[0]);
    slowo pom5(pom[0]);

    printf("\nPodaj t: ");
    scanf("%d", &pom[1]);

    printf("\nPodaj m: ");
    scanf("%d", &pom[2]);
    printf("\nPodaj r: ");
    scanf("%d", &pom[3]);
    slowo sl(pom[0]);
    printf("Podaj plaintext: ");
    for (int i=0;i<pom[0];++i)
    scanf("%d", &(sl.bajt[i]));
    printf("Podaj seed liczb losowych: ");
    scanf("%d", &pom4);
    srand(pom4);
    printf("Ktora zmienna ma rosnac:\n0 - n\n1 - t\n2 - m\n3 - r\n");
    scanf("%d", &rodzaj);
    printf("O ile ma sie ostatecznie zwiekszyc?\n");
    scanf("%d", &wzrost);
    wzrost+=pom[rodzaj];
    printf("Z jakim krokiem?\n");
    scanf("%d", &krok);
    FILE* output;
    output=fopen("dane.txt","wt");
    fprintf(output,"Plaintext testu to ");
    for (int i=0;i<pom[0];++i)
    {
        fprintf(output,"%d ",sl.bajt[i]);
    }
    fprintf(output,"\nSeed liczb losowych to %d\n", pom4);
    while(pom[rodzaj]<wzrost)
    {
        fprintf(output,"Zestaw %d, %d, %d, %d\n",pom[0],pom[1],pom[2],pom[3]);
        for (int i=0;i<10;i++)
        {
            tworz(pom[0],pom[1],pom[2],pom[3],sl);
            fprintf(output,"%d\t",statystyka());
            fprintf(output,"%d\n",pudla);
        }
        pom[rodzaj]+=krok;
    }
    fclose(output);

}

hellman::hellman()
{

}

hellman::~hellman()
{

}
