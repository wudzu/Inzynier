#include "szyfrowanie.h"

using namespace std;


Menu::Menu()
{

}

Menu::~Menu()
{

}

void Menu::menu()
{
    plik=fopen("temp.txt","rt");
    unsigned char wybor=0;
    fscanf(plik,"Metoda: %d\n", &wybor);/*
    printf("\n\n");
    printf("����������������");
    printf("\n\n");

    printf("Jakiego rodzaju test chcesz wykonac?\n");

    printf("0 - hellman 16 bitowy\n");
    printf("1 - rivest 16 bitowy\n");
    printf("2 - teczowa 16 bitowy\n");

    printf("3 - hellman 32 bitowy\n");
    printf("4 - rivest 32 bitowy\n");
    printf("5 - teczowa 32 bitowy\n");

    scanf("%d", &wybor);*/
    switch (wybor)
    {
    case 1:
        hell16();
        break;
    case 2:
        rive16();
        break;
    case 3:
        tecz16();
        break;
    case 4:
        hell32();
        break;
    case 5:
        rive32();
        break;
    case 6:
        tecz32();
        break;
    }
}

void Menu::hell16()
{
    hellman16 h16;
    h16.menuHellmanZapis();
}

void Menu::rive16()
{
    rivest16 r16;
    r16.menuRivestZapis();
}

void Menu::tecz16()
{
    teczowa16 t16;
    t16.menuTeczowaZapis();
}

void Menu::hell32()
{
    hellman32 h32;
    h32.menuHellmanZapis();
}

void Menu::rive32()
{
    rivest32 r32;
    r32.menuRivestZapis();
}

void Menu::tecz32()
{
    teczowa32 t32;
    t32.menuTeczowaZapis();
}


void menu()
{
    unsigned char wybor=0;
    fscanf(plik,"Metoda: %d\n", &wybor);
    printf("\n\n------------------\n\n");

    printf("Co robic? \n 0 - Tworz jedna tablice\n 1 - Szukaj klucza\n 2 - Zapisz tabele do pliku\n 3 - Wiele tablic metoda Hellmana\n 4 - Statystyka wielu tablic Hellmana\n 5 - Hellman, 16-bitowe zmienne\n 6 - Rivest, 16-bitowe zmienne\n 7 - Oechslin, 16-bitowe zmienne\n");
    printf(" 8 - Test czasu\n");
    scanf("%d", &wybor);
        hellman16 hel16;
        rivest16 riv16;
        teczowa16 tecz16;
        hellman32 hel32;
        rivest32 riv32;
        teczowa32 tecz32;
        unsigned int blabla=0x1f2f4f;
    switch (wybor)
    {
    case 5:

        hel16.menuHellmanZapis();
        break;
    case 6:

        riv16.menuRivestZapis();
        break;

    case 7:
        tecz16.menuTeczowaZapis();
        break;
    case 8:
        int czas[6];
        czas[0]=hel16.testCzasuLamania();
        czas[1]=hel16.testCzasuTworzenia();
        czas[2]=riv16.testCzasuLamania();
        czas[3]=riv16.testCzasuTworzenia();
        czas[4]=tecz16.testCzasuLamania();
        czas[5]=tecz16.testCzasuTworzenia();

        printf("Czas tworzenia tablicy hellmana to %d, a lamania to %d\n",czas[1],czas[0]);
        printf("Czas tworzenia tablicy rivesta to %d, a lamania to %d\n",czas[3],czas[2]);
        printf("Czas tworzenia tablicy teczowej to %d, a lamania to %d\n",czas[5],czas[4]);

        break;
    case 9:
        printf("Czas lamania rivesta32 to %d\n",riv32.testCzasuLamania());
        break;
    case 10:
        int czas1[6];
        czas1[0]=hel32.testCzasuLamania();
        czas1[1]=hel32.testCzasuTworzenia();
        printf("Czas tworzenia tablicy hellmana to %d, a lamania to %d\n",czas1[1],czas1[0]);

        czas1[2]=riv32.testCzasuLamania();
        czas1[3]=riv32.testCzasuTworzenia();
        printf("Czas tworzenia tablicy rivesta to %d, a lamania to %d\n",czas1[3],czas1[2]);

        czas1[4]=tecz32.testCzasuLamania();
        czas1[5]=tecz32.testCzasuTworzenia();
        printf("Czas tworzenia tablicy teczowej to %d, a lamania to %d\n",czas1[5],czas1[4]);

        break;
    case 11:
        printf("Czas tworzenia tablicy rivesta to %d, a lamania to %d\n",riv32.testCzasuTworzenia(),riv32.testCzasuLamania());
        break;
    case 12:
        tecz32.tworz(256,256*256,0x20202020);
        printf("\nTrafienia teczowej: %d \n",tecz32.statystyka());
        hel32.tworz(256,256,256,0x20202020); //1626
        printf("\nTrafienia hellmana: %d \n",hel32.statystyka());
        riv32.tworz(40000,256,256,0x20202020, (0xFFFFFFFF << (32 - 14)));
        printf("\nTrafienia rivesta: %d \n",riv32.statystyka());


        break;
    case 13:
        riv32.tworz(40000,1626,1626,0x20202020, (0xFFFFFFFF << (32 - 14)));
        printf("\nSrednia dlugosc lancucha to: %d\n",riv32.getSredniT());
        break;
    case 14:
        hel32.menuHellmanZapis();
        break;
    case 15:
        riv32.menuRivestZapis();
        break;
    case 16:
        tecz32.menuTeczowaZapis();
        break;
    case 17:
        hel32.testowyMenuHellmanZapis();
        break;
    }
}

void czytoten( int pozycja)
{

}

