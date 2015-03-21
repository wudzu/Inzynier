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
    t=daneT;
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

void rivest16::menuRivestZapis()
{
    unsigned int pom[3],pom4,pom6,rodzaj,wzrost,krok;

    printf("\nPodaj maksymalne t: ");
    scanf("%d", &pom[0]);

    printf("\nPodaj m: ");
    scanf("%d", &pom[1]);

    printf("\nPodaj r: ");
    scanf("%d", &pom[2]);

    printf("Podaj plaintext (hexadecymalnie): ");
    scanf("%x", &plaintext);

    printf("Podaj seed liczb losowych: ");
    scanf("%d", &pom4);
    srand(pom4);

    printf("Ktora zmienna ma rosnac:\n0 - t\n1 - m\n2 - r\n");
    scanf("%d", &rodzaj);
    printf("O ile ma sie ostatecznie zwiekszyc?\n");
    scanf("%d", &wzrost);
    printf("Z jakim krokiem?\n");
    scanf("%d", &krok);
    printf("Ile testow na zestaw?\n");
    scanf("%d", &pom6);
    FILE* output;
    output=fopen("dane.txt","wt");
    fprintf(output,"Plaintext testu to ");
        fprintf(output,"%x",plaintext);

    fprintf(output,"\nSeed liczb losowych to %d\n", pom4);
    fprintf(output,"\nLiczba zestawow to %d\n", wzrost);
    wzrost+=pom[rodzaj];
    while(pom[rodzaj]<wzrost)
    {
        fprintf(output,"Zestaw %d, %d, %d\n",pom[0],pom[1],pom[2]);
        printf("Zestaw %d, %d, %d\n",pom[0],pom[1],pom[2]);
        for (int i=0;i<pom6;i++)
        {
            tworz(pom[0],pom[1],pom[2],plaintext);
            fprintf(output,"%d\t",statystyka());
            fprintf(output,"%d\n",pudla);
            printf("%d\t",statystyka());
            printf("%d\n",pudla);
        }
        pom[rodzaj]+=krok;
    }
    fclose(output);

}
