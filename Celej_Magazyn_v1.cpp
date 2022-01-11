// program wykonal Celej Adam z grupy D104
#include <iostream>
#include <random>
#include <ctime>
#include <algorithm>

using namespace std;

default_random_engine generator(time(0));
uniform_int_distribution<> losowa(1, 100);

void zliczZapotrzebowanie(int zamowienia[][2], int nZamowien, int nProduktow, int zapotrzebowania[][2]){
    //zmienna i oznacza konkretny produkt
    for (int i = 0; i < nProduktow; ++i)
    {
        zapotrzebowania[i][0] = 1;
        zapotrzebowania[i][1] = 0;
    }
    for (int i = 0; i < nZamowien; ++i)
    {
        zapotrzebowania[ zamowienia[i][0] ][1] += zamowienia[i][1];
    }
}

void zliczZamowieniaProduktu(int zamowienia[][2], int nZamowien, int nProduktow, int zliczoneZamowienia[][2]) {
    for (int i=0;i<nProduktow;i++)
    {
        zliczoneZamowienia[i][0]=i;
        zliczoneZamowienia[i][1]=0;
    }

    for (int i=0;i<nZamowien;i++)
    {
        zliczoneZamowienia[ zamowienia[i][0] ][1]++;
    }
}

void sortujWzgledem2KolumnyMalejaco(int zapotrzebowania[][2], int n){
    for (int i = 0; i < n; i++)
    {
        bool zmieniono = false;
        for (int j = 1; j < n - i; j++)
        {
            if (zapotrzebowania[j-1][1] < zapotrzebowania[j][1])
            {
                swap(zapotrzebowania[j-1], zapotrzebowania[j]);
                zmieniono = true;
            }
        }
        //jesku instrukcja zawiera tylko jedno polecenie to nie trzeba dawac nawiasow klamrowych
        if (!zmieniono)
            break;
    }
}




int main()
{
    //deklaruje zmienna n oznaczajaca liczbe roznych produktow, towarow w magazynie i prosze uzytkownika o podanie tej liczby
    int n;
    cout << "Podaj liczbe roznych produktow znajdujacych sie w magazynie: ";
    cin >> n;

    //deklaruje tablice zawierajaca stan magazynu czyli przechowywana liczbe sztuk kazdego produktu
    int wmagazynie[n];
    for (int i=0; i<n; i++)
    {
        wmagazynie[i]=losowa(generator);
    }

    uniform_int_distribution<> losowZamowienie(0, n);
    //deklarujemy tablice z zamowieniami
    int liczbaZamowien = losowa(generator) + 100;
    int Zamowienia[liczbaZamowien][2];

    //wpisujemy wartosci do tablicy z zamowieniami
    for (int i=0;i<liczbaZamowien;i++)
    {
        Zamowienia[i][0] = losowZamowienie(generator);
        Zamowienia[i][1] = losowa(generator);
    }

    //deklaruje tablice z zapotrzebowaniem
    int Zapotrzebowanie[n][2];

    zliczZapotrzebowanie(Zamowienia, liczbaZamowien, n, Zapotrzebowanie);

    // Sortuje tablice Zapotrzebowanie od produktu z najwiekszym nakladem do tego z najmniejszym
    sortujWzgledem2KolumnyMalejaco(Zapotrzebowanie, n);

    //Sprawdzam ile razy byl zamowiony dany produkt
    //lzdp = liczba zamowien danego produktu
    int lzdp[n][2];
    zliczZamowieniaProduktu(Zamowienia, liczbaZamowien, n, lzdp);

    // Sorotwanie tablicy minimalnie mniej naiwnym bubble sortem, malejące z flagą
    sortujWzgledem2KolumnyMalejaco(lzdp, n);

    char wybor;
    do
    {
        cout << "Aby wyswietlic stan magazynu wpisz 1" << endl;
        cout << "Aby wyswietlic zamowienia wpisz 2" << endl;
        cout << "Aby wyswietlic zapotrzebowanie na produkty w kolejnosci malejacej wpisz 3" << endl;
        cout << "Aby wyswietlic produkty od najczesciej do najrzadziej zamawianych wpisz 4" << endl;
        cout << "Aby wyswietlic produkty od najrzadziej do najczesciej zamawianych wpisz 5" << endl;
        cout << "Aby wyswietlic produkty zamawiane w najmniejszych ilosciach wpisz 6" << endl;
        cout << "Aby wyswietlic w ilu zamowieniach pojawiaja sie poszczegolne produkty wpisz 7" << endl;
        cout << "Twoj wybor to: ";
        cin >> wybor;
        switch (wybor)
        {
            case '1':
                for (int i=0; i<n; i++)
                {
                    cout << wmagazynie[i] << endl;
                }
                break;

            case '2':
                //wypisuje wartosci tablicy
                for (int i=0;i<liczbaZamowien;i++)
                {
                    for (int j=0;j<2;j++)
                    {
                        cout << Zamowienia[i][j] << " ";
                    }
                    cout << "\n";
                }
                break;

            case '3':
                cout << "Produkty zamawiane w najwiekszych ilosciach a wiec z najwiekszym zapotrzebowaniem to: " << endl;
                for (int i=0;i<n;i++)
                {
                    cout << "Zapotrzebowanie na produkt o id " << Zapotrzebowanie[i][0] << " wynosi " << Zapotrzebowanie[i][1] << endl;
                }
                break;

            case '4':
                //wypisuje wartosci tablicy lzdp
                cout << "Najczesciej zamawiane produkty to:" << endl;
                for (int i=0;i<n;i++)
                {
                    cout << lzdp[i][0] << " w ilosci " << lzdp[i][1];
                    cout << "\n";
                }
                break;

            case '5':
                //wypisuje wartosci tablicy lzdp od konca
                cout << "Najrzadziej zamawiane produkty to:" << endl;
                for (int i=n-1;i>=0;i--)
                {
                    cout << lzdp[i][0] << " w ilosci " << lzdp[i][1];
                    cout << "\n";
                }
                break;

            case '6':
                cout << "Produkty zamawiane w najmniejszych ilosciach a wiec z najmniejszym zapotrzebowaniem to: " << endl;
                for (int i=n-1;i>=0;i--)
                {
                    cout << "Produkt o id " << Zapotrzebowanie[i][0] << " zostal zamowiony " << Zapotrzebowanie[i][1] << " razy" << endl;
                }
                break;

            case '7':
                int idproduktu;
                cout << "Podaj id produktu dla ktorego chcesz sprawdzic liczbe zamowien ";
                cin >> idproduktu;
                cout << "Produkt o id " << idproduktu << " byl zamowiony " << lzdp[idproduktu][1] << " razy\n" << endl;
                break;
        }
        cout << "Jesli chcesz zakonczyc prace programu wybierz 0" << endl;
        cout << "Jesli chcesz kontynuować to wcisnij dowolny inny klawisz" << endl;
        cout << "Twoj wybor to: " << endl;
        cin >> wybor;
        /*if ('0' == wybor)
            exit(0);*/
        //system("CLS"); //czyscimy ekran
    }
    while (wybor != '0');
    return 0;
}
