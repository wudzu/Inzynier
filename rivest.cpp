#include "szyfrowanie.h"

rivest16::rivest16()
{

}

rivest32::rivest32()
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

void rivest32::tworz()
{
    printf("\nPodaj maksymalne t: ");
    scanf("%d", &t);
    printf("\nPodaj m: ");
    scanf("%d", &m);
    printf("\nPodaj r: ");
    scanf("%d", &r);
    printf("Podaj plaintext (hexadecymalnie): ");
    scanf("%x", &plaintext);
    printf("Podaj liczbe zer punktu rozroznialnego: ");
    scanf("%d", &zera);
    zera=~( 0xFFFFFFFF << (32-zera));
    printf("Podaj seed liczb losowych: ");
    int a;
    scanf("%d", &a);
    srand(a);
    tworz(t,m,r,plaintext,zera);
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
    }
    t=a;
}

void rivest32::tworz(unsigned int daneT, unsigned int daneM, unsigned int daneR, unsigned int plain, unsigned int daneZera)
{
    tablica.clear();
    t=daneT;
    m=daneM;
    r=daneR;
    zera=daneZera;

    plaintext=plain;
    tablicaR32 pom1;
    int a=0;

    for (int i=0;i<r;++i)
    {
        pom1.wypelnij(plaintext, t, m,zera);
        tablica.push_back(pom1);
        if (pom1.getT()>a)
            a=pom1.getT();
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
            return 1;
        }
    }

    return 0;
}

bool rivest32::testuj(unsigned int klucz)
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
            return 1;
        }
    }

    return 0;
}

int rivest16::testCzasuTworzenia()
{
    clock_t zegar;
    zegar=clock();
    for (int i=0;i<100;++i)
    {
        tworz(42,42,42,0x1234);
    }
    return clock()-zegar;
}

int rivest32::testCzasuTworzenia()
{
    clock_t zegar;

    zegar=clock();
    for (int i=0;i<100;++i)
    {
        tworz(100000,1626,1626,0x20202020, (0xFFFFFFFF << (32 - 14)));
    }
    return clock()-zegar;
}

int rivest16::testCzasuLamania()
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

int rivest32::testCzasuLamania()
{
    clock_t zegar;

    tworz(100000,1626,1626,0x20202020, (0xFFFFFFFF << (32 - 14)));
    zegar=clock();
    for (int i=0;i<100;++i)
    {
        testuj(i);
    }
    return clock()-zegar;
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

int rivest32::statystyka()
{
    int trafienia=0;
    for (int i=0;i<65536;++i)
    {
            if (testuj(getRand32()))
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

void rivest32::menuRivest()
{
    tworz();
    printf("Stworzono.\n");
    printf("\n\n%d\n\n",statystyka());
    printf("%d", pudla);
}


void rivest16::menuRivestZapis(Menu* globalMenu)
{
    unsigned int pom[3],pom4,pom6,rodzaj,wzrost,krok,wyk;

    fscanf(plik,"Zmienna: %d\n", &rodzaj);
    fscanf(plik,"t: %d\n", &pom[0]);
    fscanf(plik,"m: %d\n", &pom[1]);
    fscanf(plik,"r: %d\n", &pom[2]);
    fscanf(plik,"Plaintext: %d\n", &plaintext);
    fscanf(plik,"Seed: %d\n",&pom4);
    fscanf(plik,"Finalna: %d\n", &wzrost);
    fscanf(plik,"Krok: %d\n",&krok);
    fscanf(plik,"Testy: %d\n",&pom6);
    fscanf(plik,"Zera: %d\n",&wyk);
    fscanf(plik,"Tablica: %d\n",&wyk);
    fscanf(plik,"Wykonano: %d\n",&wyk);

    wzrost=wzrost-pom[rodzaj];

    fclose(plik);

/*
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
    scanf("%d", &pom6);*/
    FILE* output;
    srand(pom4);

    if (globalMenu->getPoczatek())
    {
        output = fopen("dane.txt","at");
    }
    else
    {
        output=fopen("dane.txt","wt");
        fprintf(output,"Plaintext testu to ");
        fprintf(output,"%d",plaintext);
        fprintf(output,"\nSeed liczb losowych to %d\n", pom4);
        fprintf(output,"\nLiczba zestawow to %d\n", (wzrost/krok));

    }

    globalMenu->started(plaintext,pom4,wzrost+pom[rodzaj],krok,0,0,pom6,rodzaj);

    wzrost+=pom[rodzaj];
    while(pom[rodzaj]<wzrost)
    {
        if (wyk == 0)
        {
            fprintf(output,"Zestaw %d, %d, %d .\n",pom[0],pom[1],pom[2]);
            printf("Zestaw %d, %d, %d\n",pom[0],pom[1],pom[2]);
            wyk=1;
            globalMenu->update(pom[0],pom[1],pom[2],rand(),1);
        }

        for (int i=wyk;i<=pom6;i++)
        {
            tworz(pom[0],pom[1],pom[2],plaintext);
            fprintf(output,"%d\t",statystyka());
            fprintf(output,"%d\n",pudla);
            printf("%d\t",statystyka());
            printf("%d\n",pudla);
            globalMenu->update(pom[0],pom[1],pom[2],rand(),i+1);
        }
        wyk=0;
        pom[rodzaj]+=krok;
        globalMenu->update(pom[0],pom[1],pom[2],rand(),0);
    }
    fclose(output);

}

void rivest32::menuRivestZapis(Menu* globalMenu)
{
    unsigned int pom[3],pom4,pom6,rodzaj,wzrost,krok,pomStat,wyk;

    fscanf(plik,"Zmienna: %d\n", &rodzaj);
    fscanf(plik,"t: %d\n", &pom[0]);
    fscanf(plik,"m: %d\n", &pom[1]);
    fscanf(plik,"r: %d\n", &pom[2]);
    fscanf(plik,"Plaintext: %d\n", &plaintext);
    fscanf(plik,"Seed: %d\n",&pom4);
    fscanf(plik,"Finalna: %d\n", &wzrost);
    fscanf(plik,"Krok: %d\n",&krok);
    fscanf(plik,"Testy: %d\n",&pom6);
    fscanf(plik,"Zera: %d\n",&zera);
    fscanf(plik,"Tablica: %d\n",&wyk);
    fscanf(plik,"Wykonano: %d\n",&wyk);
    wzrost=wzrost-pom[rodzaj];

    fclose(plik);
/*
    printf("\nPodaj maksymalne t: ");
    scanf("%d", &pom[0]);

    printf("\nPodaj m: ");
    scanf("%d", &pom[1]);

    printf("\nPodaj r: ");
    scanf("%d", &pom[2]);

    printf("Podaj plaintext (hexadecymalnie): ");
    scanf("%x", &plaintext);

    printf("Podaj liczbe zer: ");
    scanf("%d", &zera);
    zera=(0xFFFFFFFF << (32 - zera));

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
    scanf("%d", &pom6);*/
    FILE* output;
    srand(pom4);

    if (globalMenu->getPoczatek())
    {
        output = fopen("dane.txt","at");
    }
    else
    {
        output=fopen("dane.txt","wt");
        fprintf(output,"Plaintext testu to ");
        fprintf(output,"%d",plaintext);
        fprintf(output,"\nSeed liczb losowych to %d\n", pom4);
        fprintf(output,"\nLiczba zestawow to %d\n", (wzrost/krok));

    }
    globalMenu->started(plaintext,pom4,wzrost+pom[rodzaj],krok,zera,0,pom6,rodzaj);


    wzrost+=pom[rodzaj];
    while(pom[rodzaj]<wzrost)
    {
        if (wyk == 0)
        {
            fprintf(output,"Zestaw %d, %d, %d .\n",pom[0],pom[1],pom[2]);
            printf("Zestaw %d, %d, %d\n",pom[0],pom[1],pom[2]);
            wyk=1;
            globalMenu->update(pom[0],pom[1],pom[2],rand(),1);
        }

        for (int i=wyk;i<=pom6;i++)
        {
            tworz(pom[0],pom[1],pom[2],plaintext,zera);
            pomStat=statystyka();
            fprintf(output,"%d\t",pomStat);
            fprintf(output,"%d\n",pudla);
            printf("%d\t",pomStat);
            printf("%d\n",pudla);
            globalMenu->update(pom[0],pom[1],pom[2],rand(),i+1);
        }
        wyk=0;
        pom[rodzaj]+=krok;
        globalMenu->update(pom[0],pom[1],pom[2],rand(),0);
    }
    fclose(output);

}

unsigned int rivest32::getSredniT()
{
    unsigned long long temp=0;
    for (int i=0;i<r;++i)
    {
        temp+=tablica[i].getT();
    }
    temp/=r;
    return temp;
}
