//made by Adam Celej
#include <iostream>
#include <random>
#include <ctime>

using namespace std;

default_random_engine generator(time(0));
uniform_int_distribution<> losowa(1, 100);

void swap_colls_2D(int **arr, size_t nRows, size_t toSwap1, size_t toSwap2) {
    for (int i = 0; i < nRows; i++) {
        swap(arr[i][toSwap1], arr[i][toSwap2]);
    }
}

void sort_2D_array_coll_wise(int **arr, size_t nRows, size_t nColls,
    size_t index_sort) {
    for (int i = 0; i < (nColls - 1); i++) {
        bool anythingChanged = false;
        for (int j = 1; j < (nColls - i); j++) {
            if (arr[index_sort][j] < arr[index_sort][j-1]) {
                anythingChanged = true;
                // Wywo³aniem tego typu funkcji zastêpujemy zamianê pojedynczych
                // elementów dla algorytmu sortowania tablicy jednowymiarowej.
                swap_colls_2D(arr, nRows, j-1, j);
            }
        }
        if (!anythingChanged) {
            break;
        }
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
        cout << wmagazynie[i] << endl;
    }
    //deklarujemy tablice z zamowieniami
    int liczbaZamowien = losowa(generator) + 100;
    int Zamowienia[liczbaZamowien][2];

    //wpisujemy wartosci do tablicy
    for (int i=0;i<liczbaZamowien;i++)
    {
        for (int j=0;j<2;j++)
        {
            //jesli kolumna odpowiada za id produktu to wartosc komorki moze przyjac wartosc od 0 do n-1
            if (j==0)
            {
                while (Zamowienia[i][j]>n || Zamowienia[i][j]<0)
                {
                    Zamowienia[i][j] = losowa(generator);
                }
            }
            else
               Zamowienia[i][j] = losowa(generator);

        }
    }

    //wypisuje wartosci tablicy
    for (int i=0;i<liczbaZamowien;i++)
    {
        for (int j=0;j<2;j++)
        {
            cout << Zamowienia[i][j] << " ";
        }
        cout << "\n";
    }

    //deklaruje tablice z zapotrzebowaniem
    int Zapotrzebowanie[n];
    for (int i=0;i<n;i++)
    {
        Zapotrzebowanie[i]=0;
        for (int j=0;j<liczbaZamowien;j++)
        {
            if (Zamowienia[j][0]==i)
                Zapotrzebowanie[i]=Zapotrzebowanie[i]+Zamowienia[j][1];
        }
        cout << "Zapotrzebowanie na produkt o id " << i << " wynosi " << Zapotrzebowanie[i] << endl;
    }

    //Sprawdzam ile razy byl zamowiony dany produkt
    //lzdp = liczba zamowien danego produktu
    int lzdp[n];
    for (int i=0;i<n;i++)
    {
        lzdp[i]=0;
        for (int j=0;j<liczbaZamowien;j++)
        {
            if (Zamowienia[j][0]==i)
                lzdp[i]++;
        }
        cout << "Produkt o id " << i << " byl zamowiony " << lzdp[i] << " razy" << endl;
    }
    //Sprawdzam ktore z produktow sa najszesciej zamawiane
    //Sortuje tablice
    int maks[n][2];
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<2;j++)
        {
            if (0==j)
            {
                maks[i][j]=i;
            }
            else
            {
                maks[i][j]=lzdp[i];
            }
            cout << maks[i][j] << " ";
        }
    }
    sort_2D_array_coll_wise(maks);
    //wypisuje wartosci tablicy
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<2;j++)
        {
            cout << maks[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}
