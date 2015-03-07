#include "szyfrowanie.h"

unsigned char sBox0[16]={0x9A,0x39,0x5F,0x00,0x18,0xA1,0x27,0xFE,0xB2,0x63,0xCD,0xE6,0x84,0x4C,0x7B,0xD5};
unsigned char sBox1[16]={0x30,0x4C,0x21,0xF2,0x07,0x19,0x8A,0x74,0x53,0xC8,0xA6,0xEF,0xBB,0x6D,0xD5,0x9E};

unsigned char sBox01( unsigned char P)
{
    return (0xF0&(sBox0[P >> 4])) | (0x0F&(sBox0[P &(0x0F)]));
}

unsigned char sBox23( unsigned char P)
{
    return (0xF0&(sBox1[P >> 4])) | (0x0F&(sBox1[P &(0x0F)]));
}

void sBoxy( slowo & mes)
{
    if (mes.n == 2)
    {
    mes.bajt[0]=sBox01(mes.bajt[0]);
    mes.bajt[1]=sBox23(mes.bajt[1]);
    }
    else
    {
        for (int i=0;i<mes.n;++i)
        {
            mes.bajt[i]=sBox01(mes.bajt[i]);
        }
    }
}

void permutacja(slowo & mes)
{
    if (mes.n==2)
    {
        unsigned char pom0, pom1;
        pom0=   mes.bajt[0]&(0x21) | ((mes.bajt[0]>>3)&0x02) | ((mes.bajt[1]<<2)&0x04) | ((mes.bajt[1]>>1)&0x08) | ((mes.bajt[0]<<3)&0x10) | ((mes.bajt[1]<<5)&0x40) | ((mes.bajt[1]<<2)&0x80);
        pom1=   mes.bajt[1]&(0x84) | ((mes.bajt[0]>>2)&0x01) | ((mes.bajt[0]>>5)&0x02) | ((mes.bajt[1]>>3)&0x08) | ((mes.bajt[0]<<1)&0x10) | ((mes.bajt[0]>>2)&0x20) | ((mes.bajt[1]<<3)&0x40);
        mes.bajt[0]=pom0;
        mes.bajt[1]=pom1;
    }
}

void szyfrowanie(slowo & P, slowo & klucz, slowo & C, int* prime)
{
    slowo m=P;
    slowo kluczrundowy=klucz;
    for (int i=0;i<8;++i)
    {
        przesuniecieprawo(kluczrundowy,prime[i]);
        m^=kluczrundowy;
        kluczrundowy=klucz;
        sBoxy(m);
        permutacja(m);

    }
    currentRedukcja.f(m);
    C=m;

}
/*
void R(slowo & mes)
{

}
*/
void przesuniecieprawo (slowo & klucz, unsigned char przes)
{
    przes%=8;
	unsigned char pom0,pom1,pom2;
	/*if (klucz.n == 2)
    {


        pom0=klucz.bajt[1] << (8 - przes);
        pom1=klucz.bajt[0] << (8 - przes);
        klucz.bajt[0]=(klucz.bajt[0] >> przes)|pom0;
        klucz.bajt[1]=(klucz.bajt[1] >> przes)|pom1;
    }*/

    pom0=klucz.bajt[n-1] << (8 - przes);
    pom1=klucz.bajt[0]   << (8 - przes);

    for (int i=0;i<klucz.n-1;++i)
    {
        pom2=klucz.bajt[i] << (8 - przes);
        klucz.bajt[i]=(klucz.bajt[i] >> przes)|pom0;
        pom0=pom2;
    }
    klucz.bajt[n-1]=(klucz.bajt[n-1] >> przes)|pom1;

}
/*
void przesuniecieprawo (unsigned char* klucz, unsigned char przes)
{
    przes%=8;
	unsigned char pom0,pom1;
	pom0=klucz[1] >> (8 - przes);
	pom1=klucz[0] >> (8 - przes);
	klucz[0]=(klucz[0] << przes)|pom0;
	klucz[1]=(klucz[1] << przes)|pom1;
}
*/

slowo::slowo() :bajt(0), n(0)
{
}

void slowo::wypiszB()
{
    for (int i=n-1;i>=0;--i)
    {
        for (int j=7;j>=0;--j)
        {
            if (bajt[i]&(1<<j))
                printf("1");
            else
                printf("0");
        }
        printf(" ");
    }
    printf("\n");

}

slowo::slowo(unsigned char a) : n(a), bajt(0)
{
    bajt=new unsigned char[a];
}

slowo & slowo::operator=(const slowo &b)
{
    if (n != b.n)
    {
        delete [] bajt;
        bajt= new unsigned char[b.n];
        n=b.n;
    }
    for (int i=0;i<n;++i)
        bajt[i]=b.bajt[i];
    return *this;
}

slowo & slowo::operator^=(const slowo &b)
{
    for (int i=0;i<n;++i)
    {
        bajt[i]^=b.bajt[i];
    }
    return *this;
}

slowo::slowo (const slowo & wzor) : bajt(0)
{
    n=wzor.n;
    bajt=new unsigned char[n];
    for (int i=0;i<n;++i)
    {
        bajt[i]=wzor.bajt[i];
    }
}

slowo & slowo::operator ^(const slowo & b)
{
    slowo a(b.n);
    for (int i=0;i<a.n;++i)
    {
        a.bajt[i]=bajt[i]^b.bajt[i];
    }
    return a;
}

int slowo::liczba()
{
    int a=0;
    int b=0;
    for (int i=n-1;i>=0;--i)
    {
        a*=256;
        a+=bajt[i];
    }
    return a;
}

bool slowo::operator == (const slowo &b)
{
    if (n!=b.n)
        return 0;
    for (int i=0;i<n;++i)
    {
        if (bajt[i]!=b.bajt[i])
            return 0;
    }
    return 1;
}

EPSP::EPSP (unsigned char a) : EP(a), SP(a)
{

}

int* liczbypierwsze()
{
    int* prime;
    prime = new int[25];
    int k=0;
     for (int i=2; i<100; i++)
        for (int j=2; j*j<=i; j++)
        {
            if (i % j == 0)
                break;
            else if (j+1 > sqrt(i)) {
                prime[k]=i;
                k++;
            }

        }
        return prime;
}

EPSP::EPSP (const EPSP &wzor) : EP(wzor.EP), SP(wzor.SP)
{

}

void Sortowanie(int left, int right)
{
    int i = left;
    int j = right;
    int x = tablica[(left+right)/2].EP.liczba();
    slowo pom0;

    do
    {
        while(tablica[i].EP.liczba()>x )
            i++;

        while(tablica[j].EP.liczba()<x )
            j--;

        if(i<= j)
        {
            std::swap( tablica[i].EP.bajt, tablica[j].EP.bajt );
            std::swap( tablica[i].SP.bajt, tablica[j].SP.bajt );
            i++;
            j--;
        }

    } while(i<=j);

    if(left<j) Sortowanie(left,j);
    if(right>i) Sortowanie(i,right);
}
