#include "szyfrowanie.h"

hellman16::hellman16()
{

}

hellman32::hellman32()
{

}

void hellman::tworz()
{
    printf("\n\nPodaj n: ");
    scanf("%d", &n);
    printf("\nPodaj t: ");
    scanf("%d", &t);
    t+=2;
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

void hellman32::tworz()
{
    printf("\nPodaj t: ");
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

void hellman16::tworz()
{
    printf("\nPodaj t: ");
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

void hellman32::tworz(unsigned int daneT, unsigned int daneM, unsigned int daneR, unsigned int plain)
{
    tablica.clear();
    t=daneT;
    m=daneM;
    r=daneR;

    plaintext=plain;
    tablicaH32 pom1;

    for (int i=0;i<r;++i)
    {
        pom1.wypelnij(plaintext, t, m);
        tablica.push_back(pom1);
       // printf("Stworzono tablice %d \n",i);
        //printf("Tablica %d -ta stworzona\n",i);
    }
}

void hellman16::tworz(unsigned int daneT, unsigned int daneM, unsigned int daneR, unsigned short plain)
{
    tablica.clear();
    t=daneT;
    m=daneM;
    r=daneR;

    plaintext=plain;
    tablicaH16 pom1;

    for (int i=0;i<r;++i)
    {
        pom1.wypelnij(plaintext, t, m);
        tablica.push_back(pom1);
        //printf("Tablica %d -ta stworzona\n",i);
    }
}

void hellman::tworz(unsigned char daneN, unsigned int daneT, unsigned int daneM, unsigned int daneR, slowo& plain)
{
    tablica.clear();
    n=daneN;
    t=daneT+2;
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

bool hellman32::testuj(unsigned int klucz)
{
    unsigned int C0;
    unsigned int test1,test2;
    szyfrowanie32 (plaintext+1,     klucz, test1);
    szyfrowanie32 (plaintext+256,   klucz, test2);
    szyfrowanie32 (plaintext, klucz, C0);
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

bool hellman16::testuj(unsigned short klucz)
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

bool hellman::testuj(slowo& klucz)
{

    slowo C0;
    //bool jest=0;
    szyfrowanie (plaintext, klucz, C0);
    for (int i=0;i<r;++i)
    {
        if (tablica[i].sprawdz(C0, klucz))
        {

            return 1;
            break;
        }
    }


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

int hellman32::statystyka()
{
    int trafienia=0;
    for (int i=0;i<65536;++i)
    {

            if (testuj(rand()))
                ++trafienia;

    }
    pudla=0;
    for (int i=0;i<r;++i)
    {
        pudla+=tablica[i].getPudla();
    }
    return trafienia;
}

int hellman16::statystyka()
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

void hellman::menuHellman()
{
    tworz();
    printf("Stworzono.\n");
    printf("\n\n%d\n\n",statystyka());
    printf("%d", pudla);
}

void hellman32::menuHellman()
{
    tworz();
    printf("Stworzono.\n");
    printf("\n\n%d\n\n",statystyka());
    printf("%d", pudla);
}

void hellman16::menuHellman()
{
    tworz();
    printf("Stworzono.\n");
    printf("\n\n%d\n\n",statystyka());
    printf("%d", pudla);
}

void hellman::menuHellmanZapis()
{
    unsigned int pom[4],pom4,pom6,rodzaj,wzrost,krok;

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
    printf("Z jakim krokiem?\n");
    scanf("%d", &krok);
    printf("Ile testow na zestaw?\n");
    scanf("%d", &pom6);
    FILE* output;
    output=fopen("dane.txt","wt");
    fprintf(output,"Plaintext testu to ");
    for (int i=0;i<pom[0];++i)
    {
        fprintf(output,"%d ",sl.bajt[i]);
    }
    fprintf(output,"\nSeed liczb losowych to %d\n", pom4);
    fprintf(output,"\nLiczba zestawow to %d\n", wzrost);
    wzrost+=pom[rodzaj];
    while(pom[rodzaj]<wzrost)
    {
        fprintf(output,"Zestaw %d, %d, %d, %d\n",pom[0],pom[1],pom[2],pom[3]);
        printf("Zestaw %d, %d, %d, %d\n",pom[0],pom[1],pom[2],pom[3]);
        for (int i=0;i<pom6;i++)
        {
            tworz(pom[0],pom[1],pom[2],pom[3],sl);
            fprintf(output,"%d\t",statystyka());
            fprintf(output,"%d\n",pudla);
            printf("%d\t",statystyka());
            printf("%d\n",pudla);
        }
        pom[rodzaj]+=krok;
    }
    fclose(output);

}

void hellman32::menuHellmanZapis()
{
    unsigned int pom[3],pom4,pom6,rodzaj,wzrost,krok;

    printf("\nPodaj t: ");
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
    fprintf(output,"\nLiczba zestawow to %d\n", (wzrost/krok));
    wzrost+=pom[rodzaj];
    while(pom[rodzaj]<wzrost)
    {
        fprintf(output,"Zestaw %d, %d, %d .\n",pom[0],pom[1],pom[2]);
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


void hellman16::menuHellmanZapis()
{
    unsigned int pom[3],pom4,pom6,rodzaj,wzrost,krok;

    printf("\nPodaj t: ");
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
    fprintf(output,"\nLiczba zestawow to %d\n", (wzrost/krok));
    wzrost+=pom[rodzaj];
    while(pom[rodzaj]<wzrost)
    {
        fprintf(output,"Zestaw %d, %d, %d .\n",pom[0],pom[1],pom[2]);
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

int hellman32::testCzasuTworzenia()
{
    clock_t zegar;
    zegar=clock();
    for (int i=0;i<10;++i)
    {
        tworz(1626,1626,1626,0x20202020);
    }
    return clock()-zegar;
}

int hellman16::testCzasuTworzenia()
{
    clock_t zegar;
    zegar=clock();
    for (int i=0;i<100;++i)
    {
        tworz(42,42,42,0x1234);
    }
    return clock()-zegar;
}

int hellman32::testCzasuLamania()
{
    clock_t zegar;
    tworz(1626,1626,1626,0x20202020);
    //tworz(813,813,813,0x20202020);
    zegar=clock();
    for (int i=0;i<100;++i)
    {
        testuj(i);
    }
    return clock()-zegar;
}

int hellman16::testCzasuLamania()
{
    clock_t zegar;
    tworz(42,42,42,0x1234);
    zegar=clock();
    for (int i=0;i<100;++i)
    {
        testuj(i);
    }
    return clock()-zegar;
}

hellman::hellman()
{

}

hellman::~hellman()
{

}
