//Michał Guzek
//bar.cpp

#include <cstdio>
using namespace std;

char ciag[1000005];

int przebiegaj(int pocz, int kon, int druga_roznica_v1)
{
    int najwieksza_roznica = 1;

    while(pocz < kon)
    {
        int akt_roznica = 0, pocz_pozycja_p = pocz, ost_pozyzcja_p;

        for( ; akt_roznica >= 0 && pocz <= kon ; ++pocz)
        {
            if(ciag[pocz] == 'p')
            {
                ++akt_roznica;
                ost_pozyzcja_p = pocz;
            }
            else
            {
                --akt_roznica;
            }
        }

        if(akt_roznica < 0)
        {
            while(ciag[pocz] == 'j')
                ++pocz;
        }

        int pierwsza_roznica = ost_pozyzcja_p-pocz_pozycja_p+1, druga_roznica_v2 = 0;

        akt_roznica = 0;

        int od_konca = ost_pozyzcja_p, do_roznicy = ost_pozyzcja_p;

        for( ; od_konca >= pocz_pozycja_p ; --od_konca)
        {
            if(ciag[od_konca] == 'p')
            {
                ++akt_roznica;
                ost_pozyzcja_p = od_konca;
            }
            else
            {
                --akt_roznica;
            }

            if(akt_roznica < 0)
            {
                if((do_roznicy-ost_pozyzcja_p+1) > druga_roznica_v1)
                {
                    druga_roznica_v2 = przebiegaj(ost_pozyzcja_p, do_roznicy, druga_roznica_v1);

                    if(druga_roznica_v2 > druga_roznica_v1)
                        druga_roznica_v1 = druga_roznica_v2;
                }

                while(ciag[--od_konca] == 'j');
                akt_roznica = 0;
                do_roznicy = od_konca;
                ++od_konca;
            }
        }

        druga_roznica_v2 = do_roznicy-pocz_pozycja_p+1;

        if(druga_roznica_v2 > druga_roznica_v1)
            druga_roznica_v1 = druga_roznica_v2;

        if(pierwsza_roznica < druga_roznica_v1)
            druga_roznica_v1 = pierwsza_roznica;

        if(druga_roznica_v1 > najwieksza_roznica)
            najwieksza_roznica = druga_roznica_v1;

        druga_roznica_v1 = najwieksza_roznica;
    }

    return najwieksza_roznica;
}

int main()
{
    int n;
    scanf("%d%s", &n, ciag);

    int pocz = 0, kon = n-1;

    for( ; pocz < kon && ciag[pocz] == 'j' ; ++pocz);
    for( ; kon > 0 && ciag[kon] == 'j' ; --kon);

    if((pocz > kon) || ((n == 1) && (ciag[0] == 'j')))
    {
        printf("0");
    }
    else
    {
        printf("%d", przebiegaj(pocz, kon, 0));
    }

    return 0;
}
