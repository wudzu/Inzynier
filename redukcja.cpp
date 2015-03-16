#include "szyfrowanie.h"

redukcja::redukcja(int n)
{
    unsigned char a=0;
    bool powtorzenia=1;
    for (int i=0;i<n*8;++i)
    {
        powtorzenia=1;
        while(powtorzenia)
        {
            a=rand()%(n*8);
            powtorzenia=0;
            for (int j=0;j<i;++j)
            {
                if (dane[j]==a)
                {
                    powtorzenia=1;
                    break;
                }
            }
        }
        dane.push_back(a);
    }

}

redukcja16::redukcja16()
{
    bool powtorzenia;
    unsigned short a;
    for (int i=0;i<16;++i)
    {
        powtorzenia=1;
        while(powtorzenia)
        {
            a=rand()%16;
            powtorzenia=0;
            for (int j=0;j<i;++j)
            {
                if (dane[j]==a)
                {
                    powtorzenia=1;
                    break;
                }
            }
        }
        dane.push_back(a);
    }
}

void redukcja::ustaw(unsigned char n, unsigned char a)
{
    dane[n]=a;
}

void redukcja::ustaw(unsigned char* tab, int n)
{
    dane.clear();
    for (int i=0;i<n;++i)
    {
        dane.push_back(tab[i]);
    }
}

void redukcja::reset (int n)
{
    dane.clear();
    unsigned char a=0;
    bool powtorzenia=1;
    for (int i=0;i<n*8;++i)
    {
        powtorzenia=1;
        while(powtorzenia)
        {
            a=rand()%(n*8);
            powtorzenia=0;
            for (int j=0;j<i;++j)
            {
                if (dane[j]==a)
                {
                    powtorzenia=1;
                    break;
                }
            }
        }
        dane.push_back(a);
    }
}

void redukcja16::reset()
{
    dane.clear();
    bool powtorzenia;
    unsigned short a;
    for (int i=0;i<16;++i)
    {
        powtorzenia=1;
        while(powtorzenia)
        {
            a=rand()%16;
            powtorzenia=0;
            for (int j=0;j<i;++j)
            {
                if (dane[j]==a)
                {
                    powtorzenia=1;
                    break;
                }
            }
        }
        dane.push_back(a);
    }
}

void redukcja16::f(unsigned short & mes)
{
    unsigned short pom=0;
    for (int i=0;i<16;++i)
    {
        if (mes&(1 << dane[i]))
            pom|=1<<i;
    }
}

void redukcja::f(slowo& mes)
{
    slowo pom(mes.n);
    unsigned char a;
    for (int i=0;i<mes.n;++i)
    {
        a=0x00;
        for (int j=0;j<8;++j)
        {

            if (mes.bajt[dane[i*8+j]/8]&(0x01 << (dane[i*8+j]%8)))
            {
                a|=1<<j;
            }

        }
        pom.bajt[i]=a;
    }
    mes=pom;

    /*
    slowo pom(mes.n);
    unsigned char a;
    int c,d;
    int b;
    for (int i=mes.n-1;i>=0;--i)
    {
        printf("\nb = ");
        for (int j=0;j<8;++j)
        {
            //pom.bajt[i]&=!(0x01 << j);
            a=mes.bajt[dane[i*8+j]/8]&(0x01 << (dane[i*8+j]%8));
            c=dane[i*8+j]/8;
            d=dane[i*8+j]%8;
            printf(" %d %d ",c,d);
            //printf("%x  ",a);
            b=j-(dane[i*8+j]%8);
            if (b>0)
            {
                a << b;
            }
            if (b<0)
            {
                a >> -b;
            }
            //printf("%x  ",a);
            pom.bajt[i]|=a;
            //printf("\n%x", a);
            //printf("     %x %x \n", pom.bajt[1], pom.bajt[0]);
        }




    }
    mes=pom;
    */
}

void testowanie()
{
    slowo a(2);
    a.bajt[1]=0x55;
    a.bajt[0]=0xaa;
    srand(10);
    redukcja b(2);
    for (int i=0;i<16;i++)
    {
        b.ustaw(i,i);
    }

    for (int i=0;i<16;++i)
    {
        b.ustaw(0,i);
        b.ustaw(i,0);
        b.f(a);
        printf("%d daje ",i);
        a.wypiszB();
        a.bajt[1]=0x55;
        a.bajt[0]=0xaa;
        for (int i=0;i<16;i++)
        {
            b.ustaw(i,i);
        }
        printf("\n");
    }




    //printf("%2x %2x   ",a.bajt[1], a.bajt[0]);
}
