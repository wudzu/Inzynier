#include "szyfrowanie.h"

using namespace std;


void menu()
{
    unsigned char wybor=0;
    printf("\n\n------------------\n\n");
    if (jestTablica)
    {
        printf("Tablica w pamieci. ");
    }
    else
        printf("Brak tablicy w pamieci. ");
    printf("Co robic? \n 0 - Tworz jedna tablice\n 1 - Szukaj klucza\n 2 - Zapisz tabele do pliku\n 3 - Wiele tablic metoda Hellmana\n 4 - Statystyka wielu tablic Hellmana\n 5 - Hellman, 16-bitowe zmienne\n 6 - Rivest, 16-bitowe zmienne\n 7 - Oechslin, 16-bitowe zmienne\n");
    printf(" 8 - Test czasu\n");
    scanf("%d", &wybor);
        hellman hel;
        hellman16 hel16;
        rivest16 riv16;
        teczowa16 tecz16;
        hellman32 hel32;
        rivest32 riv32;
        teczowa32 tecz32;
        unsigned int blabla=0x1f2f4f;
    switch (wybor)
    {
    case 0:
        tworzTablice();
        jestTablica=1;
    break;
    case 1:
        if (jestTablica)
        menuKlucza();
    break;
    case 2:
        zapisTablicy();
    break;
    //case 3:
    //    testowanie();
    //break;
    case 3:
        //hellman hel;
        hel.menuHellman();
        break;
    case 4:
        //hellman hel0;
        hel.menuHellmanZapis();
        break;
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
        unsigned int bubu0=0x20202020;
        unsigned int bubu1=1626;
        unsigned int bubu3=100000;
        unsigned int bubu2=(0xFFFFFFFF << (32 - 14));
        unsigned int testow= 200;
        unsigned long long suma=0;
        tablicaR32 pom1;
        for (int i=0;i<testow;++i)
        {
            pom1.wypelnij(bubu0,bubu3,bubu1,bubu2);
            suma+=pom1.getT();
            printf("\nDlugosc max %d-tej tablicy to: %d",i,pom1.getT());
        }
        suma/=testow;
        printf("\n\nSrednia dlugosc to: %d", suma);
    }
}



void tworzTablice()
{


    printf("Podaj ile bajtow ma slowo:  ");
    scanf("%d", &n);
    slowo P(n);
    slowo klucz(n);
    slowo C(n);

	tablica.clear();


	//unsigned int t; //ilosc szyfrowan
	//unsigned int m; //przydzial pamieci
    //unsigned int pom0;

    cout << "Podaj plaintext: ";
    for (int i=0;i<n;++i)
    scanf("%d", &P.bajt[i]);

	cout<< "Podaj ilosc pamieci: ";
	scanf("%d",&m);
	if (m%2)
        m++;

	cout << "Podaj dlugosc lancucha: ";
	scanf("%d", &t);
	if (t%2)
        t++;

	cout << "Podaj seed liczb losowych: ";
	int seed;
	scanf("%d", &seed);
	srand(seed);
	currentRedukcja.reset(n);

    EPSP pom1(n);
	for(int i=0; i<m; i++)
	{
	    for (int j=0;j<n;++j)
        {
            klucz.bajt[j]=rand();
        }

			pom1.SP=klucz;

            for (int k=0;k<t;++k)
            {
                szyfrowanie (P, klucz, C);
                currentRedukcja.f(C);
                klucz=C;
            }

            pom1.EP=klucz;

        tablica.push_back(pom1);

	}
		Sortowanie( 0,m-1);

    return;
}

void menuKlucza()
{
    int dobre=0;
    float procent;
    printf("\nPlaintext to %d %d", P.bajt[1], P.bajt[0]);
    slowo klucz(n);
    //printf("Podaj klucz jaki mamy sprawdzic: ");
    //scanf("%d %d", klucz.bajt, klucz.bajt+1);
    for (int a=0;a<255;++a)
    {
        for (int b=0;b<255;b++)
        {
            klucz.bajt[0]=a;klucz.bajt[1]=b;
            if (szukajKlucza(klucz))
            {
                dobre++;
            }

        }

    }
    procent=dobre;
    procent/=65536.0f;
    printf("\n\n Szansa trafienia to %f , a ilosc trafien to %d \n\n ", procent, dobre);


}

bool szukajKlucza(slowo klucz)
{

    int pozycja;
    int koniec=1;
    //unsigned int t;
    //unsigned int m;
    //printf("\n%d %d \n",klucz.bajt[1],klucz.bajt[0]);
    slowo element(n), elementpop(n);
    //slowo message(n);
    slowo* odtwarzanie;
    odtwarzanie = new slowo [t];


    elementpop=klucz;
    for (int i=1;i<t-1;++i)
    {
        //printf("\n%d\n",m);
        szyfrowanie(P, elementpop, element);
        currentRedukcja.f(element);
        elementpop=element;
        pozycja=Szukanie(element,0,m-1);
        if (pozycja!=-1)
        {

        //printf("\n%d %d", &tablica[pozycja].EP.bajt[0], &tablica[pozycja].EP.bajt[1]);
        reszta(pozycja,koniec);
        for (;pozycja<=koniec;pozycja++)
        {
            //printf("%d %d\n", klucz.bajt[1],klucz.bajt[0]);
            //printf("%d %d\n", tablica[pozycja].SP.bajt[0], tablica[pozycja].SP.bajt[1]);
            //printf("%d %d\n\n", tablica[pozycja].EP.bajt[0], tablica[pozycja].EP.bajt[1]);

            odtwarzanie[0]=tablica[pozycja].SP;
            for (int j=1;j<t;++j)
            {
                szyfrowanie(P,odtwarzanie[j-1],odtwarzanie[j]);
                currentRedukcja.f(odtwarzanie[j]);
                //printf("%d : %d %d\n", j, odtwarzanie[j].bajt[0],odtwarzanie[j].bajt[1]);
            }
            if (test(odtwarzanie[t-i], klucz ))
            {
                delete [] odtwarzanie;
                return 1;
            }
        }
        }
    }

    //printf("\n\n Szansa trafienia to %0.000f \n\n ", procent);

    delete [] odtwarzanie;

return 0;
}

int Szukanie(slowo szukana, int left, int right)
{
    int middle;
    int temp;

      while (left <= right) {
            middle = (left + right)/2;

            if (tablica[middle].EP == szukana)
                  return middle;
            else if (tablica[middle].EP.liczba() < szukana.liczba())
                  right=middle-1;
            else
                  left=middle+1;
      }
      return -1;

}

bool test(slowo testowany, slowo klucz)
{
    if (testowany == klucz)
    {
        printf("\nKluczem jest ");
        for (int i=0;i<n;++i)
        {
            printf("%d ", testowany.bajt[i]);
        }
        printf("\n\n");
        return 1;
    }
    return 0;

}

void reszta(int& pocz, int& kon)
{
     int a=pocz;
     unsigned int m;
     kon=pocz;
    while(pocz-1)
    {
        if (tablica[a].EP.liczba() == tablica[pocz-1].EP.liczba())
        {
            pocz--;
        }
        else
            break;
    }
    while(kon+1 < m)
    {
        if (tablica[a].EP.liczba() == tablica[kon+1].EP.liczba())
        {
            kon++;
        }
        else
            break;
    }
}

void czytoten( int pozycja)
{

}

void zapisTablicy()
{

    slowo P(n);
    slowo klucz(n);
    slowo C(n);

	unsigned int t; //ilosc szyfrowan
	unsigned int m; //przydzial pamieci
    unsigned int pom0;
		plik=fopen("chains.txt", "w");
    cout << "Podaj plaintext: ";
    scanf("%d %d", P.bajt, (P.bajt+1));
	fprintf(plik,"%d\t%d\n",P.bajt[0],P.bajt[1]);
	cout<< "Podaj ilosc pamieci(2 do x): ";
	scanf("%d",&m);pom0=1;
	for (int i=0;i<m;i++)
    {
        pom0*=2;
    }
    m=pom0;

	cout << "Podaj dlugosc lancucha (2 do x): ";
	scanf("%d", &t);pom0=1;
	for (int i=0;i<t;i++)
    {
        pom0*=2;
    }
	t=pom0;
	cout << "Podaj seed liczb losowych: ";
	int seed;
	scanf("%d", &seed);
	srand(seed);

    EPSP pom1(n);
	for(int i=0; i<m; i++)
	{
	    for (int j=0;j<n;++j)
        {
            klucz.bajt[j]=rand();

        }

			pom1.SP=klucz;
			for (int k=n-1;k>=0;--k)
                fprintf(plik,"%d\t", klucz.bajt[k]);
			//   To zapis do pliku
            for (int k=0;k<t;++k)
            {

                szyfrowanie (P, klucz, C);
                currentRedukcja.f(C);
                klucz=C;
                for (int k=n-1;k>=0;--k)
                    fprintf(plik,"%d\t", klucz.bajt[k]);
            }

        fprintf(plik,"\n");
	}


		fclose(plik);

    return;
}

