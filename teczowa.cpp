#include "szyfrowanie.h"

teczowa16::teczowa16()
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

void teczowa16::tworz(unsigned int daneT, unsigned int daneM, unsigned short plain)
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

void teczowa16::menuTeczowa()
{
    tworz();
    printf("Stworzono.\n");
    printf("\n\n%d\n\n",statystyka());
    printf("%d", pudla);
}

