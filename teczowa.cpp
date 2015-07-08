#include "szyfrowanie.h"

teczowa16::teczowa16()
{

}

teczowa32::teczowa32()
{

}

void teczowa16::tworz()
{
    printf("\nPodaj t: ");
    scanf("%d", &t);
    printf("\nPodaj m: ");
    scanf("%d", &m);
    printf("\nPodaj plaintext (hexadecymalnie): ");
    scanf("%x", &plaintext);
    printf("Podaj seed liczb losowych: ");
    int a;
    scanf("%d", &a);
    srand(a);
    tworz(t,m,plaintext);


}

void teczowa32::tworz()
{
    printf("\nPodaj t: ");
    scanf("%d", &t);
    printf("\nPodaj m: ");
    scanf("%d", &m);
    printf("\nPodaj plaintext (hexadecymalnie): ");
    scanf("%x", &plaintext);
    printf("Podaj seed liczb losowych: ");
    int a;
    scanf("%d", &a);
    srand(a);
    tworz(t,m,plaintext);


}

void teczowa16::tworz(unsigned int daneT, unsigned int daneM, unsigned short plain)
{

    t=daneT+1;
    m=daneM;


    plaintext=plain;
    tablica.wypelnij(plaintext,t,m);


}

void teczowa32::tworz(unsigned int daneT, unsigned int daneM, unsigned int plain)
{

    t=daneT+1;
    m=daneM;


    plaintext=plain;
    tablica.wypelnij(plaintext,t,m);


}

bool teczowa16::testuj(unsigned short klucz)
{
    unsigned short C0;
    unsigned short test1,test2;
    szyfrowanie16 (plaintext+1,     klucz, test1);
    szyfrowanie16 (plaintext+256,   klucz, test2);
    szyfrowanie16 (plaintext, klucz, C0);


        if (tablica.sprawdz(C0, test1, test2))
        {
            //printf("\n%x",klucz);

            return 1;

        }



    return 0;
}

bool teczowa32::testuj(unsigned int klucz)
{
    unsigned int C0;
    unsigned int test1,test2;
    szyfrowanie32 (plaintext+1,     klucz, test1);
    szyfrowanie32 (plaintext+256,   klucz, test2);
    szyfrowanie32 (plaintext, klucz, C0);


        if (tablica.sprawdz(C0, test1, test2))
        {
            //printf("\n%x",klucz);

            return 1;

        }



    return 0;
}

int teczowa16::statystyka()
{
    int trafienia=0;
    for (int i=0;i<65536;++i)
    {

            if (testuj(i))
                ++trafienia;

    }


    pudla=tablica.getPudla();

    return trafienia;
}

int teczowa32::statystyka()
{
    int trafienia=0;
    for (int i=0;i<50000;++i)
    {

            if (testuj(i))
                ++trafienia;

    }


    pudla=tablica.getPudla();

    return trafienia;
}

void teczowa16::menuTeczowa()
{
    tworz();
    printf("Stworzono.\n");
    printf("\n\n%d\n\n",statystyka());
    printf("%d", pudla);
}

void teczowa32::menuTeczowa()
{
    tworz();
    printf("Stworzono.\n");
    printf("\n\n%d\n\n",statystyka());
    printf("%d", pudla);
}

int teczowa16::testCzasuTworzenia()
{
    clock_t zegar;
    zegar=clock();
    for (int i=0;i<100;++i)
    {
        tworz(42,1764,0x1234);
    }
    return clock()-zegar;
}

int teczowa32::testCzasuTworzenia()
{
    clock_t zegar;
    zegar=clock();
    for (int i=0;i<10;++i)
    {
        tworz(1626,1626*1626,0x20202020);
    }
    return clock()-zegar;
}

int teczowa16::testCzasuLamania()
{
    clock_t zegar;
    tworz(42,1764,0x1234);
    zegar=clock();
    for (int i=0;i<100;++i)
    {
        testuj(i);
    }
    return clock()-zegar;
}

int teczowa32::testCzasuLamania()
{
    clock_t zegar;
    tworz(1626,1626*1626,0x20202020);
    zegar=clock();
    for (int i=0;i<100;++i)
    {
        testuj(i);
    }
    return clock()-zegar;
}

void teczowa16::menuTeczowaZapis()
{
    unsigned int pom[3],pom4,pom6,rodzaj,wzrost,krok,teoria;

    printf("\nPodaj t: ");
    scanf("%d", &pom[0]);

    printf("\nPodaj m: ");
    scanf("%d", &pom[1]);

    printf("\nZachowac stosunek rozmiaru macierzy m*t?\n0 - nie\n1 - tak\n");
    scanf("%d", &teoria);

    printf("Podaj plaintext (hexadecymalnie): ");
    scanf("%x", &plaintext);

    printf("Podaj seed liczb losowych: ");
    scanf("%d", &pom4);
    srand(pom4);

    printf("Ktora zmienna ma rosnac:\n0 - t\n1 - m\n");
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
        if(teoria)
        {
            pom[2]=pom[0]*pom[1];
        }
        else
        {
            pom[2]=pom[1];
        }

        fprintf(output,"Zestaw %d, %d .\n",pom[0],pom[2]);
        printf("Zestaw %d, %d\n",pom[0],pom[2]);
        for (int i=0;i<pom6;i++)
        {
            tworz(pom[0],pom[2],plaintext);
            fprintf(output,"%d\t",statystyka());
            fprintf(output,"%d\n",pudla);
            printf("%d\t",statystyka());
            printf("%d\n",pudla);
        }
        pom[rodzaj]+=krok;
    }
    fclose(output);

}

void teczowa32::menuTeczowaZapis()
{
    unsigned int pom[3],pom4,pom6,rodzaj,wzrost,krok,teoria;

    printf("\nPodaj t: ");
    scanf("%d", &pom[0]);

    printf("\nPodaj m: ");
    scanf("%d", &pom[1]);

    printf("\nZachowac stosunek rozmiaru macierzy m*t?\n0 - nie\n1 - tak\n");
    scanf("%d", &teoria);

    printf("Podaj plaintext (hexadecymalnie): ");
    scanf("%x", &plaintext);

    printf("Podaj seed liczb losowych: ");
    scanf("%d", &pom4);
    srand(pom4);

    printf("Ktora zmienna ma rosnac:\n0 - t\n1 - m\n");
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
        if(teoria)
        {
            pom[2]=pom[0]*pom[1];
        }
        else
        {
            pom[2]=pom[1];
        }

        fprintf(output,"Zestaw %d, %d .\n",pom[0],pom[2]);
        printf("Zestaw %d, %d\n",pom[0],pom[2]);
        for (int i=0;i<pom6;i++)
        {
            tworz(pom[0],pom[2],plaintext);
            fprintf(output,"%d\t",statystyka());
            fprintf(output,"%d\n",pudla);
            printf("%d\t",statystyka());
            printf("%d\n",pudla);
        }
        pom[rodzaj]+=krok;
    }
    fclose(output);

}
