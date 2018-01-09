//Michał Guzek
//kur.cpp

#include <cstdio>
#include <map>
#include <queue>
using namespace std;

struct przedzial_czasowy
{
    map<int, int> licznik_paczek;
    map<int, int> jaki_dominuje;
};

struct zakres
{
    int skad, dokad;
};

int paczki[500005];
przedzial_czasowy przedzialy[500005];
queue<zakres> kolejka;

int main()
{
    int liczba_przesylek, ilosc_przedzialow_czasowych;
    scanf("%d%d", &liczba_przesylek, &ilosc_przedzialow_czasowych);

    for(int i = 1 ; i <= liczba_przesylek ; ++i)
    {
        scanf("%d", &paczki[i]);
    }

    for(int i = 0 ; i < ilosc_przedzialow_czasowych ; ++i)
    {
        zakres temp;
        scanf("%d%d", &temp.skad, &temp.dokad);

        kolejka.push(temp);

        przedzialy[temp.skad].jaki_dominuje[temp.dokad];
        przedzialy[temp.dokad].jaki_dominuje[temp.skad];
    }

    for(int i = 1 ; i <= 500000 ; ++i)
    {
        if(przedzialy[i].jaki_dominuje.size())
        {
            przedzialy[i].jaki_dominuje[i] = paczki[i];

            map<int, int>::iterator it;
            for(it = przedzialy[i].jaki_dominuje.begin() ; (it->first <= i) && (it != przedzialy[i].jaki_dominuje.end()) ; ++it);

            if(it != przedzialy[i].jaki_dominuje.end())
            {
                przedzialy[i].licznik_paczek.clear();
                ++przedzialy[i].licznik_paczek[paczki[i]];

                int poprzednik = i;

                //przebiegamy wszystkie zakresy zaczynajace sie w "i":
                for(it = ++(przedzialy[i].jaki_dominuje.find(i)) ; it != przedzialy[i].jaki_dominuje.end() ; poprzednik = it->first, ++it)
                {
                    int ile_wystarczy = ((it->first-i+1)/2)+1;

                    map<int, int>::iterator do_spr = przedzialy[it->first].jaki_dominuje.find(i);

                    //czy istnieje droga na skroty:
                    if((do_spr != przedzialy[it->first].jaki_dominuje.begin()) && ((it->first - i) > (it->first - (--do_spr)->first)/2))
                    {
                        for(int odejmowanie = do_spr->first ; odejmowanie < i ; ++odejmowanie)
                        {
                            --przedzialy[it->first].licznik_paczek[paczki[odejmowanie]];
                        }

                        przedzialy[i].jaki_dominuje[it->first] = 0;

                        for(map<int, int>::iterator do_licznika = przedzialy[it->first].licznik_paczek.begin()
                                ;
                            do_licznika != przedzialy[it->first].licznik_paczek.end() ; ++do_licznika)
                        {
                            if(do_licznika->second >= ile_wystarczy)
                            {
                                przedzialy[i].jaki_dominuje[it->first] = do_licznika->first;
                                break;
                            }
                        }

                        przedzialy[i].licznik_paczek = przedzialy[it->first].licznik_paczek;
                    }
                    else    //jesli nie to reczne dodawanie
                    {
                        if(przedzialy[i].licznik_paczek[przedzialy[i].jaki_dominuje[poprzednik]] >= ile_wystarczy)
                        {
                            przedzialy[i].jaki_dominuje[it->first] = przedzialy[i].jaki_dominuje[poprzednik];
                        }
                        else
                        {
                            przedzialy[i].jaki_dominuje[it->first] = 0;
                        }

                        for(int dodawanie = poprzednik+1 ; dodawanie <= (it->first) ; ++dodawanie)
                        {
                            if((++(przedzialy[i].licznik_paczek[paczki[dodawanie]])) >= ile_wystarczy)
                            {
                                przedzialy[i].jaki_dominuje[it->first] = paczki[dodawanie];
                            }
                        }

                        if(przedzialy[it->first].jaki_dominuje.size() > 1)
                        {
                            przedzialy[it->first].licznik_paczek = przedzialy[i].licznik_paczek;
                        }
                    }
                }
            }
        }
    }

    while(!kolejka.empty())
    {
        zakres temp = kolejka.front();
        kolejka.pop();

        printf("%d\n", przedzialy[temp.skad].jaki_dominuje[temp.dokad]);
    }

    return 0;
}
