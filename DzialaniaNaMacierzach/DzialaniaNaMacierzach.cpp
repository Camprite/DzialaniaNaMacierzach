#include <iostream>
#include <locale.h>
#include <fstream>
#include "funkcje.h"

using namespace std;

/*struct matrix {
    int xsize;
    int ysize;
    int** matrix;
    matrix = new int* [xsize];
    for (int i = 0;i < xsize;i++) {
        matrix[i] = new int[ysize];
};*/
int*** matrixarray;//tablica dynamiczna z macierzami
int** matrixspec ;//tablica przechowująca dane poszczególnej macierzy
int* matrixnumber = new int;//ilosć macierzy
int main()
{
    //system("color 0a"); // alternatywna wersja kolorków
    system("color f0"); //zmiana koloru konsoli :)
    setlocale(LC_CTYPE, "Polish"); //polskie znaczki 

    /*
    cout << endl << "Działania na macierzach" << endl << endl;
    cout << "Podaj sposób wprowadzania danych: " << endl;
    cout << "1. Dane z pliku " << endl;
    cout << "2. Dane wprowadzone z klawiatury " << endl;
    cout << "3. Dane pseudolosowe " << endl;
    bool validation = false;
    int option = 0;
    do{
        cin >> option;
        if (option == 1 || option == 2 || option == 3) {
            validation = true;
        }
    } while (!validation);
    system("cls");//Czyszczenie konsoli*/
    int option = startMenu();
    switch (option)
    {
    case 1: {
        string plik;
        //cin >> plik;
        //wczytajPlik(plik);
          do {
            cout << "Podaj nazwe pliku: ";
            cin >> plik;
        }while (!walidacjaPliku(plik));
        if (walidacjaPliku(plik)) {
            wczytajPlik(plik,matrixarray,matrixspec,matrixnumber);
        }
        break;
    }
    case 2: {
        int ilosc = enterMartixNumber();

        break;
    }
    case 3: {
        int ilosc = enterMartixNumber();
        cout << "Udało się";
        break;
    }
    default:
        break;
    }
    return 1;
}




// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
