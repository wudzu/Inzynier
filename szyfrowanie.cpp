#include "szyfrowanie.h"



int prime[23]={5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};

unsigned short sBox16[16]={0x309A,0x4C39,0x215F,0xF200,0x0718,0x19a1,0x8a27,0x74fe,0x53b2,0xc863,0xa6cd,0xefe6,0xbb84,0x6d4c,0xd57b,0x9ed5};

unsigned int sBox32[16]={0x673b2a77,0x514af6b1,0xb2cf4e6f,0xdc958843,0x20d0a204,0x95786052,0x795c3fe5,0xe8b3e72c,0xaef914fe,0x4d227ba0,0x3fe70c96,0xf48693db,0x0a6dbd1a,0xcb01c1cd,0x13a4d988,0x861e5539};


void sBoxy16(unsigned short &mes)
{
    mes =   0xf000&sBox16[mes>>12] |
            (0x0f00&sBox16[(mes>>8) &0x0f]) |
            (0x00f0&sBox16[(mes>>4) & 0x0f]) |
            (0x000f&sBox16[mes & 0x0f]);
}

void sBoxy32(unsigned int &mes)
{
    mes =   0xf0000000&sBox32[mes>>28] |
            0x0f000000&sBox32[(mes>>24)&0x0f] |
            0x00f00000&sBox32[(mes>>20)&0x0f] |
            0x000f0000&sBox32[(mes>>16)&0x0f] |
            0x0000f000&sBox32[(mes>>12)&0x0f] |
            0x00000f00&sBox32[(mes>>8)&0x0f] |
            0x000000f0&sBox32[(mes>>4)&0x0f] |
            0x0f&sBox32[mes&0x0f];
}

void permutacja16(unsigned short &mes)
{
    mes =   (mes&0x8421) |
            ((mes &0x0842)<< 3) |
            ((mes &0x84)<< 6) |
            ((mes &0x08)<< 9) |
            ((mes &0x4210)>> 3) |
            ((mes&0x2100) >> 6) |
            ((mes&0x1000)>>9);
}

void permutacja32(unsigned int &mes)
{
    mes =   (mes&0x11111111) |
            ((mes&0x20200000)>>2) |
            ((mes&0x08080800)<<2) |
            ((mes&0x04040000)>>4) |
            ((mes&0x4000)<<4) |
            ((mes&0x20)<<5) |
            ((mes&0x40000000)>>7) |
            ((mes&0x8200)>>8) |
            ((mes&0x00800002)<<8) |
            ((mes&0x20000)>>15) |
            ((mes&0x04)<<15) |
            ((mes&0x80400000)>>16) |
            ((mes&0x80)<<19) |
            ((mes&0x02000000)>>22) |
            ((mes&0x08)<<22) |
            ((mes&0x40)<<24);
}

void szyfrowanie16(unsigned short P, unsigned short klucz, unsigned short &C)
{
    unsigned short kluczRundowy=klucz;
    C=P;
    for (int i=0;i<8;++i)
    {
        printf("Runda %d\n",i);
        przesuniecieprawo16(kluczRundowy, prime[i]);
        printf("Message rundy: %x\n", C);
        C^=kluczRundowy;
        printf("Klucz rundy: %x\n",kluczRundowy);
        printf("Message po XOR: %x\n", C);
        kluczRundowy=klucz;
        sBoxy16(C);
        printf("Message po Sboxach: %x\n",C);
        permutacja16(C);
        printf("Message po permutacji: %x\n",C);
    }
    printf("Zaszyfrowne : %x\n", C);
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

unsigned int getRand32()
{
    return (rand()<<16) | (rand()&0xFFFF);
}
