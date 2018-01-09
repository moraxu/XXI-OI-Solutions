//Michał Guzek
//klo.cpp

#include <cstdio>
#include <cmath>
#include <queue>
using namespace std;

struct klocek
{
    int kolor, ilosc;

    bool operator<(const klocek k2) const
    {
        return ilosc < k2.ilosc;
    }
};

int ciag[1000005];
priority_queue<klocek> kolejka;

int main()
{
    int ile_kolorow, pocz, kon;
    scanf("%d%d%d", &ile_kolorow, &pocz, &kon);

    int ile_razy_zminusowac = 0;

    for(int i = 0 ; i < ile_kolorow ; ++i)
    {
        klocek temp;
        temp.kolor = i+1;
        scanf("%d", &temp.ilosc);

        if(i+1 == pocz)
        {
            if((--temp.ilosc) == 0)
                ++ile_razy_zminusowac;
        }
        if(i+1 == kon)
        {
            if((--temp.ilosc) == 0)
                ++ile_razy_zminusowac;

            if(temp.ilosc == -1)
            {
                if(ile_kolorow == 1 && pocz == 1 && kon == 1)
                {
                    printf("1");
                }
                else
                {
                    printf("0");
                }

                return 0;
            }
        }

        if(temp.ilosc)
            kolejka.push(temp);
    }

    for(int ile = 0 ; ile < ile_razy_zminusowac ; ++ile, --ile_kolorow);

    if((ile_kolorow == 0 && pocz == kon))
    {
        printf("0");
    }
    else if(ile_kolorow == 1)
    {
        klocek temp = kolejka.top();

        if((temp.kolor != pocz) && (temp.kolor != kon) && (temp.ilosc == 1))
        {
            printf("%d %d %d", pocz, temp.kolor, kon);
        }
        else
        {
            printf("0");
        }
    }
    else if(ile_kolorow == 0)
    {
        printf("%d %d", pocz, kon);
    }
    else
    {
        int i = 0;
        ciag[i++] = pocz;

        bool czy_bylo_odejmowanie = false;
        if(ile_kolorow > 2) czy_bylo_odejmowanie = true;

        while(ile_kolorow > 2)
        {
            klocek temp1 = kolejka.top();
            kolejka.pop();

            if(temp1.kolor != ciag[i-1])
            {
                ciag[i++] = temp1.kolor;

                if((--temp1.ilosc) == 0)
                    --ile_kolorow;
                else
                    kolejka.push(temp1);
            }
            else
            {
                klocek temp2 = kolejka.top();
                kolejka.pop();

                ciag[i++] = temp2.kolor;

                if((--temp2.ilosc) == 0)
                    --ile_kolorow;
                else
                    kolejka.push(temp2);

                kolejka.push(temp1);
            }
        }

        klocek temp1 = kolejka.top();
        kolejka.pop();
        klocek temp2 = kolejka.top();

        int kolor_do_warunku = ((temp1.ilosc > temp2.ilosc) ? temp1.kolor : temp2.kolor);

        if  ((abs(temp1.ilosc - temp2.ilosc) > 1)
                ||
            ((abs(temp1.ilosc - temp2.ilosc) == 1) && (kolor_do_warunku == ciag[i-1] || kolor_do_warunku == kon))
                ||
            ((czy_bylo_odejmowanie == false) && (pocz == kon) && (temp1.kolor == pocz || temp2.kolor == pocz)))
        {
            printf("0");
        }
        else
        {
            for(int start = (((temp1.kolor != ciag[i-1]) && ((temp1.kolor == kon) || (temp2.kolor != kon ) || (temp1.ilosc > temp2.ilosc))) ? 0 : 1)
                    ;
                temp1.ilosc || temp2.ilosc
                    ;
                (++start) %= 2
                )
            {
                if(start == 0)
                {
                    ciag[i++] = temp1.kolor;
                    --temp1.ilosc;
                }
                else
                {
                    ciag[i++] = temp2.kolor;
                    --temp2.ilosc;
                }
            }

            ciag[i] = kon;

            for(int it = 0 ; it <= i ; ++it)
            {
                printf("%d ", ciag[it]);
            }
        }
    }

    return 0;
}
