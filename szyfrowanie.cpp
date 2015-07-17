#include "szyfrowanie.h"

unsigned char sBox0[16]={0x9A,0x39,0x5F,0x00,0x18,0xA1,0x27,0xFE,0xB2,0x63,0xCD,0xE6,0x84,0x4C,0x7B,0xD5};
unsigned char sBox1[16]={0x30,0x4C,0x21,0xF2,0x07,0x19,0x8A,0x74,0x53,0xC8,0xA6,0xEF,0xBB,0x6D,0xD5,0x9E};

int prime[23]={5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};

unsigned short sBox16[16]={0x309A,0x4C39,0x215F,0xF200,0x0718,0x19a1,0x8a27,0x74fe,0x53b2,0xc863,0xa6cd,0xefe6,0xbb84,0x6d4c,0xd57b,0x9ed5};

unsigned int sBox32[16]={0x673b2a77,0x514af6b1,0xb2cf4e6f,0xdc958843,0x20d0a204,0x95786052,0x795c3fe5,0xe8b3e72c,0xaef914fe,0x4d227ba0,0x3fe70c96,0xf48693db,0x0a6dbd1a,0xcb01c1cd,0x13a4d988,0x861e5539};

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

void sBoxy16(unsigned short &mes)
{
    mes=0xf000&sBox16[mes>>12] | (0x0f00&sBox16[(mes>>8) &0x0f]) | (0x00f0&sBox16[(mes>>4) & 0x0f]) | (0x000f&sBox16[mes & 0x0f]);
}

void sBoxy32(unsigned int &mes)
{
    mes=0xf0000000&sBox32[mes>>28] | 0x0f000000&sBox32[(mes>>24)&0x0f] | 0x00f00000&sBox32[(mes>>20)&0x0f] | 0x000f0000&sBox32[(mes>>16)&0x0f] | 0x0000f000&sBox32[(mes>>12)&0x0f] | 0x00000f00&sBox32[(mes>>8)&0x0f] | 0x000000f0&sBox32[(mes>>4)&0x0f] | 0x0f&sBox32[mes&0x0f];
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

void permutacja16(unsigned short &mes)
{
    mes=(mes&0x8421) | ((mes &0x0842)<< 3) | ((mes &0x84)<< 6) | ((mes &0x08)<< 9) | ((mes &0x4210)>> 3) | ((mes&0x2100) >> 6) | ((mes&0x1000)>>9);
}

void permutacja32(unsigned int &mes)
{
    mes=(mes&0x11111111) | ((mes&0x20200000)>>2) | ((mes&0x08080800)<<2) | ((mes&0x04040000)>>4) | ((mes&0x4000)<<4) | ((mes&0x20)<<5) | ((mes&0x40000000)>>7) | ((mes&0x8200)>>8) | ((mes&0x00800002)<<8) | ((mes&0x20000)>>15) | ((mes&0x04)<<15) | ((mes&0x80400000)>>16) | ((mes&0x80)<<19) | ((mes&0x02000000)>>22) | ((mes&0x08)<<22) | ((mes&0x40)<<24);
}

void szyfrowanie(slowo & P, slowo & klucz, slowo & C)
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
    //currentRedukcja.f(m);  Przenosze to poza szyfrowanie, potem bedziemy tego potrzebowac
    C=m;

}

void szyfrowanie16(unsigned short P, unsigned short klucz, unsigned short &C)
{
    unsigned short kluczrundowy=klucz;
    C=P;
    for (int i=0;i<8;++i)
    {
        przesuniecieprawo16(kluczrundowy, prime[i]);
        C^=kluczrundowy;
        kluczrundowy=klucz;
        sBoxy16(C);
        permutacja16(C);
    }
}

void szyfrowanie32(unsigned int P, unsigned int klucz, unsigned int &C)
{
    unsigned int kluczrundowy=klucz;
    C=P;
    for (int i=0;i<16;++i)
    {
        przesuniecieprawo32(kluczrundowy,prime[i]);
        C^=kluczrundowy;
        kluczrundowy=klucz;
        sBoxy32(C);
        permutacja32(C);
    }
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

void przesuniecieprawo16 (unsigned short &m, unsigned char przes)
{
    przes%=16;
    unsigned short a= m << (16 - przes);
    m=(m>>przes) | a;
}

void przesuniecieprawo32 (unsigned int &m, unsigned char przes)
{
    przes%=32;
    unsigned int a= m << (32 - przes);
    m=(m>>przes) | a;
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
    //int b=0;
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
