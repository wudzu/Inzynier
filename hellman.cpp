#include "szyfrowanie.h"

hellman16::hellman16()
{

}

hellman32::hellman32()
{

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
            return 1;
            break;
        }
    }

    return 0;
}

int hellman32::statystyka()
{
    int trafienia=0;

    for (int i=0;i<10000;++i)
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

void hellman32::menuHellmanZapis()
{
    unsigned int pom[3],pom4,pom6,rodzaj,wzrost,krok, pomStat;

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
            pomStat=statystyka();
            fprintf(output,"%d\t",pomStat);
            fprintf(output,"%d\n",pudla);
            printf("%d\t",pomStat);
            printf("%d\n",pudla);
        }
        pom[rodzaj]+=krok;
    }
    fclose(output);

}

void hellman16::menuHellmanZapis()
{
    unsigned int pom[3],pom4,pom6,rodzaj,wzrost,krok;

    fscanf(plik,"Zmienna: %d\n", &rodzaj);
    fscanf(plik,"t: %d\n", &pom[0]);
    fscanf(plik,"m: %d\n", &pom[1]);
    fscanf(plik,"r: %d\n", &pom[2]);
    fscanf(plik,"Plaintext: %d\n", &plaintext);
    fscanf(plik,"Seed: %d\n",&pom4);
    fscanf(plik,"Finalna: %d\n", &wzrost);
    fscanf(plik,"Krok: %d\n",&krok);
    fscanf(plik,"Testy: %d\n",&pom6);

    wzrost=wzrost-pom[rodzaj];

    fclose(plik);

/*
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
    scanf("%d", &pom6);*/
    FILE* output;
    output=fopen("dane.txt","wt");
    fprintf(output,"Plaintext testu to ");
        fprintf(output,"%d",plaintext);

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

void hellman32::dodajM(int dm)
{
    for (int i=0;i<r;i++)
    {
        tablica[i].dodajM(dm);
    }
    m+=dm;
}

void hellman32::dodajT(int dt)
{
    for (int i=0;i<r;i++)
    {
        tablica[i].dodajT(dt);
    }
    t+=dt;
}

void hellman32::dodajR(int dr)
{
    tablicaH32 pom1;
    for (int i=0;i<dr;i++)
    {
        pom1.wypelnij(plaintext, t, m);
        tablica.push_back(pom1);
    }
    r+=dr;
}

void hellman32::testowyMenuHellmanZapis()
{
    unsigned int pom[3],pom4,pom6,rodzaj,wzrost,krok, pomStat;

    fscanf(plik,"Zmienna: %d\n", &rodzaj);
    fscanf(plik,"t: %d\n", &pom[0]);
    fscanf(plik,"m: %d\n", &pom[1]);
    fscanf(plik,"r: %d\n", &pom[2]);
    fscanf(plik,"Plaintext: %d\n", &plaintext);
    fscanf(plik,"Seed: %d\n",&pom4);
    fscanf(plik,"Finalna: %d\n", &wzrost);
    fscanf(plik,"Krok: %d\n",&krok);
    fscanf(plik,"Testy: %d\n",&pom6);

    wzrost=wzrost-pom[rodzaj];

    fclose(plik);
    /*
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
    scanf("%d", &pom6);*/
    FILE* output;
    output=fopen("dane.txt","wt");
    fprintf(output,"Plaintext testu to ");
        fprintf(output,"%d",plaintext);

    fprintf(output,"\nSeed liczb losowych to %d\n", pom4);
    fprintf(output,"\nLiczba zestawow to %d\n", (wzrost/krok));
    wzrost+=pom[rodzaj];
    std::vector<hellman32> dane;
    dane.resize(pom6);
    for (int i=0;i<pom6;i++)
    {
        dane[i].tworz(pom[0],pom[1],pom[2],plaintext);
    }
    while(pom[rodzaj]<wzrost)
    {
        fprintf(output,"Zestaw %d, %d, %d .\n",pom[0],pom[1],pom[2]);
        printf("Zestaw %d, %d, %d\n",pom[0],pom[1],pom[2]);
        for (int i=0;i<pom6;i++)
        {
            pomStat=dane[i].statystyka();
            fprintf(output,"%d\t",pomStat);
            fprintf(output,"%d\n",dane[i].pudla);
            printf("%d\t",pomStat);
            printf("%d\n",dane[i].pudla);
            switch(rodzaj)
            {
            case 0:
                dane[i].dodajT(krok);
                break;
            case 1:
                dane[i].dodajM(krok);
                break;
            case 2:
                dane[i].dodajR(krok);
                break;
            }
        }
        pom[rodzaj]+=krok;
    }
    fclose(output);

}
