#include <iostream>
#include <locale.h>
#include <fstream>
#include "funkcje.h"
#include <time.h>
#include <cstdlib>

using namespace std;



int main()
{
    int*** matrixarray = new int** [10];
    int** matrixspec = new int* [10];
    int* matrixnumber = new int[10];//ilosć macierzy
    for (int i = 0;i < 10;i++) {
        matrixarray[i] = new int* [10];
        matrixspec[i] = new int[10];
        for (int j = 0;j < 10;j++) {
            matrixarray[i][j] = new int[10];
        }
    }

    srand(time(NULL));
    //system("color 0a"); // alternatywna wersja kolorków
    system("color f0"); //zmiana koloru konsoli :)
    setlocale(LC_CTYPE, "Polish"); //polskie znaczki 

        switch (startMenu())
    {
    case 1: { //---------DANE-------Z--------PLIKU-----------
        string plik;
       enterMartixNumberFromFile(plik, matrixarray, matrixspec, matrixnumber);
        break;
    }
    case 2: {//---------DANE--------Z--------KLAIWATURY-----------
        enterMartixNumberFromKeyboard(matrixarray, matrixspec, matrixnumber);

        break;
    }
    case 3: {//---------DANE--------PSEUDOLOSOWE------------
       enterMartixNumberFromRandom(matrixarray, matrixspec, matrixnumber);
        cout << "Udało się";
        break;
    }
    default:
        return 0;
    } 
        cout << "tseas" << matrixspec[0][0] << endl;
        operationMenu(matrixarray, matrixspec, matrixnumber);



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
