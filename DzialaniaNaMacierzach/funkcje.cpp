#include "funkcje.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
using namespace std;
//----------------FUNKCJE OGÓLENGO PRZEZNACZENIA--------------
//------------WYPISYWANIE DANYCH ---------------
void coutAllMatrixs(int*** matrixarray, int** matrixspec, int* matrixnumber) {
    for (int i = 0;i < *matrixnumber;i++) {
        cout << endl;
        cout << endl;
        cout << "Macierz nr: " << i << " " << endl;
        for (int j = 0;j < matrixspec[i][0];j++) {
            for (int k = 0;k < matrixspec[i][1];k++) {
                cout << matrixarray[i][j][k] << " ";

            }
            cout << endl;
        }
    }
   
}

void coutMatrix(int*** matrixarray, int** matrixspec, int* matrixnumber) {
    int val = *matrixnumber;
        for (int j = 0;j < matrixspec[val][0];j++) {
            for (int k = 0;k < matrixspec[val][1];k++) {
                cout << matrixarray[val][j][k] << " ";

            }
            cout << endl;
        }
    

}
int randomValue(int upRange, int downRange) {
    int zakres = upRange - downRange;
    int value = (rand() % zakres) + downRange;
    return value;
}
bool isNumber(string var, bool czyDodatnie) {
    int wartosc;
    try { wartosc = stoi(var); }
    catch (...) {
        return false;}
    if (czyDodatnie && wartosc >= 0) {
        return true; }
    if (!czyDodatnie && wartosc <= 0) {
        return false;}
    return true;
}


bool isNumber(string var) {
    int wartosc;
    try { wartosc = stoi(var); }
    catch (...) {
        return false;
    }
    return true;
}


int positiveValue(string message) {
    string temp;
    bool walidacja = false;
    bool czyDodatanie = true;
    bool tekst = false;
    do {
        system("cls");
        if (tekst == true) {
            cout << "Coœ posz³o nie tak, spróbuj jeszcze raz" << endl;
        }
        cout << message << endl;
        cin >> temp;
        if (isNumber(temp, true)) {
            return  stoi(temp); //ZMIENNA PRZECHOWUJ¥CA ILOSC MACIERZY
            walidacja = true;
        }
        else {
            tekst = true;
        }
    } while (!walidacja);
    return 0;
}
int positiveValueNonCLS(string message) {
    string temp;
    bool walidacja = false;
    bool czyDodatanie = true;
    bool tekst = false;
    do {
        if (tekst == true) {
            cout << "Coœ posz³o nie tak, spróbuj jeszcze raz" << endl;
        }
        cout << message << endl;
        cin >> temp;
        if (isNumber(temp, true)) {
            return  stoi(temp); //ZMIENNA PRZECHOWUJ¥CA ILOSC MACIERZY
            walidacja = true;
        }
        else {
            tekst = true;
        }
    } while (!walidacja);
    return 0;
}
int positiveValueNonCLS(string message,int range) {
    string temp;
    bool walidacja = false;
    bool czyDodatanie = true;
    bool tekst = false;
    do {
        if (tekst == true) {
            cout << "Coœ posz³o nie tak, spróbuj jeszcze raz" << endl;
        }
        cout << message << endl;
        cin >> temp;
        if (isNumber(temp, true)) {
            int value = stoi(temp);
            if (value < range) {
                return value;  //ZMIENNA PRZECHOWUJ¥CA ILOSC MACIERZY
            }
        }
        else {
            tekst = true;
        }
    } while (!walidacja);
    return 0;
}


int intValue(string message) {
    string temp;
    bool walidacja = false;
    bool tekst = false;
    do {
        system("cls");
        if (tekst == true) {
            cout << "Coœ posz³o nie tak, spróbuj jeszcze raz" << endl;
        }
        cout << message << endl;
        cin >> temp;
        if (isNumber(temp)) {
            return  stoi(temp); //ZMIENNA PRZECHOWUJ¥CA ILOSC MACIERZY
            walidacja = true;
        }
        else {
            tekst = true;
        }
    } while (!walidacja);
    return 0;
}


int intValue() {
    string temp;
    bool walidacja = false;
    bool tekst = false;
    do {
        system("cls");
        if (tekst == true) {
            cout << "Coœ posz³o nie tak, spróbuj jeszcze raz";
        }
        cin >> temp;
        if (isNumber(temp)) {
            return  stoi(temp); //ZMIENNA PRZECHOWUJ¥CA ILOSC MACIERZY
            walidacja = true;
        }
        else {
            tekst = true;
        }
    } while (!walidacja);
    return 0;
}


//-----------------------WCZYTYWANIE DANYCH Z PLIKU-----------------------
void enterMartixNumberFromFile(string plik, int*** matrixarray, int** matrixspec, int* matrixnumber) {
    bool walidacja = false;
    bool tekst = false;
    ifstream file;
    do {
        try {
            system("cls");
            if (tekst == true) {
                cout << "Coœ posz³o nie tak, spróbuj jeszcze raz" << endl;
            }
            cout << "Podaj nazwe pliku: ";
            cin >> plik;
            file.open(plik, ios::in);
            if (file.good()) {
                walidacja = true;
            }
            if (!file.good()) {
                tekst = true;
                throw 'e';
            }
        }
        catch (...) {
        }
    } while (!walidacja);
    // ---------------ZADEKLAROWANIE PAMIÊCI DLA ILOSCI MACIERZY
    file >> *matrixnumber;
    cout << "Matrix number:  " << *matrixnumber << "  ";

  //  matrixarray = new int** [*matrixnumber];
   // matrixspec = new int* [*matrixnumber];
    // ---------------ZADEKLAROWANIE PAMIÊCI DLA SPECYFIKACJI DANEJ MACIERZY
  //  for (int i = 0;i < *matrixnumber;i++) {
 //       matrixspec[i] = new int[3];
//}
    // ----------------WCZYTYWANIE DANYCH -----------------------
    for (int i = 0;i < *matrixnumber;i++) {
        file >> matrixspec[i][0]; //pobranie xsize
        file >> matrixspec[i][1]; //pobranie ysize
        file >> matrixspec[i][2]; //pobranie wyznacznika macierzy domyœlnie 0
        cout << "Matrixspecx: " << matrixspec[i][0] << endl;
        cout << "Matrixspecy: " << matrixspec[i][1] << endl;
        cout << "Matrixspect: " << matrixspec[i][2] << endl;
        //matrixarray[i] = new int* [matrixspec[i][1]];
        for (int j = 0;j < matrixspec[i][0];j++) {
         //   matrixarray[i][j] = new int[matrixspec[i][1]]; // change 1 to 0
        }
        for (int j = 0;j < matrixspec[i][0];j++) {
            for (int k = 0;k < matrixspec[i][1];k++) {// change 1 to 0
                int value;
                file >> value;
                cout << value << " - ";
                matrixarray[i][j][k] = value;
            }
            cout << endl;
        }
    }
}

    

//-----------------------KONIEC WCZYTYWANIA DANYCH Z PLIKU----------------


//----------------------WCZYTYWANIE DANYCH Z KLAWIATURY-------------------

void enterMartixNumberFromKeyboard(int*** matrixarray, int** matrixspec, int* matrixnumber){
    * matrixnumber = positiveValue("Podaj ilosæ macierzy któr¹ chcesz wpisaæ");
    cout << *matrixnumber;
    matrixarray = new int** [*matrixnumber];
    matrixspec = new int* [*matrixnumber];
    // ---------------ZADEKLAROWANIE PAMIÊCI DLA SPECYFIKACJI DANEJ MACIERZY
    
    for (int i = 0;i < (*matrixnumber);i++) {
        matrixspec[i] = new int[3];
    }
    

    for (int i = 0;i < *matrixnumber;i++) {
        int lkolumn = intValue("Podaj liczbe kolumn: ");
        int lwierszy = intValue("Podaj liczbe wierszy: ");
        matrixspec[i][0]=lkolumn; //pobranie xsize
        matrixspec[i][1]=lwierszy; //pobranie ysize
        matrixspec[i][2] = 0; //pobranie wyznacznika macierzy domyœlnie 0
        matrixarray[i] = new int* [matrixspec[i][0]];
        for (int j = 0;j < matrixspec[i][0];j++) {
            matrixarray[i][j] = new int[matrixspec[i][1]];

        }
        for (int j = 0;j < matrixspec[i][0];j++) {
            for (int k = 0;k < matrixspec[i][1];k++) {
                string tekst ="x: "+to_string(j+1)+" y: "+to_string(k+1);
          
                matrixarray[i][j][k] = intValue(tekst);

         
            }
            cout << endl;
        }
    }

    }
//----------------------KONIEC WCZYTYWANIE DANYCH Z KLAWIATURY-------------------



//----------------------WCZYTYWANIE DANYCH Z JAKO WARTOSCI LOSOWE-------------------

void enterMartixNumberFromRandom(int*** matrixarray, int** matrixspec, int* matrixnumber) {
    *matrixnumber = positiveValue("Podaj ilosæ macierzy któr¹ chcesz wype³niæ: ");
    cout << *matrixnumber;
    matrixarray = new int** [*matrixnumber];
    matrixspec = new int* [*matrixnumber];
    // ---------------ZADEKLAROWANIE PAMIÊCI DLA SPECYFIKACJI DANEJ MACIERZY

    for (int i = 0;i < (*matrixnumber);i++) {
        matrixspec[i] = new int[3];
    }


    for (int i = 0;i < *matrixnumber;i++) {
        int lkolumn = intValue("Podaj liczbe kolumn: ");
        int lwierszy = intValue("Podaj liczbe wierszy: ");
        
        int downRange = intValue("Podaj zakres OD: ");
        int upRange = intValue("Podaj zakres DO: ");
        matrixspec[i][0] = lkolumn; //pobranie xsize
        matrixspec[i][1] = lwierszy; //pobranie ysize
        matrixspec[i][2] = 0; //pobranie wyznacznika macierzy domyœlnie 0
        matrixarray[i] = new int* [matrixspec[i][0]];
        for (int j = 0;j < matrixspec[i][0];j++) {
            matrixarray[i][j] = new int[matrixspec[i][1]];

        }
        for (int j = 0;j < matrixspec[i][0];j++) {
            for (int k = 0;k < matrixspec[i][1];k++) {
                string tekst = "x: " + to_string(j + 1) + " y: " + to_string(k + 1);

                matrixarray[i][j][k] = randomValue(upRange, downRange);


            }
            
        }
    }
    for (int i = 0;i < *matrixnumber;i++) {
        cout << endl;
        cout << endl;
        cout << "Macierz nr: " << i << " " << endl;
        for (int j = 0;j < matrixspec[i][0];j++) {
            for (int k = 0;k < matrixspec[i][1];k++) {
                cout << matrixarray[i][j][k] << " ";

            }
            cout << endl;
        }
    }

}
//----------------------KONIEC WCZYTYWANIE DANYCH JAKO WARTOSCI LOSOWE-------------------


//----------------------MENU WYWO£YWANIA OPERACJI-------------------
void operationMenu(int*** matrixarray, int** matrixspec, int* matrixnumber) {
    int option = INT_MAX;

/*    cout << "Dostêpne funkcje" << endl;
    cout << "1. Dodawanie macierzy" << endl;
    cout << "2. Mno¿enie macierzy" << endl;
    cout << "3. Transpozycja macierzy" << endl;
    cout << "4. Wyznacznik macierzy" << endl;
    cout << endl;*/
    do {
        option = positiveValue("Dostêpne funkcje\n1. Dodawanie macierzy\n2. Mno¿enie macierzy\n3. Transpozycja macierzy\n4. Wyznacznik macierzy\nPodaj funkcje której chcesz u¿yæ: ");
        switch (option)
        {
        case 1: {
            system("CLS");
            cout << "Dostêpne macierze: " << endl;
            cout  << endl;
            cout << *matrixnumber << endl;
            cout << endl;
        
            for (int i = 0;i < *matrixnumber;i++) {
                cout << "Macierz nr: " << i <<  endl;
                cout << "weŸ kurwo zadzia³aj: " << matrixarray[0][2][1] << endl;
                cout << "weŸ kurwo zadzia³aj: " << matrixarray[1][1][1] << endl;
                cout << "weŸ kurwo zadzia³aj: " << matrixarray[2][0][1] << endl;

            }
            int matrix1 = positiveValueNonCLS("Podaj numer pierwszej macierzy", *matrixnumber);
            int matrix2 = positiveValueNonCLS("Podaj numer drugiej macierzy", *matrixnumber);

            break;
        }
        case 2: {
            cout << "œmigo" << endl;
            break;
        }
        case 3: {
            cout << "œmigo" << endl;
            break;
        }
        case 4: {
            cout << "œmigo" << endl;
            break;
        }
        default:
                break;
        }
    } while (option > 4);
}

void wypiszWynik(int** matrix, int xsize, int ysize) {
    for (int i = 0;i < xsize;i++) {
        for (int j = 0;j < ysize;j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

/* int enterMartixNumber() {
    cout << "Podaj iloœæ macierzy (1-4): "; //trzeba to zmieniæ na funkcje :)
    bool validation = false;
    int martixnumber = 0;
    do {
        cin >> martixnumber;
        if (martixnumber == 1 || martixnumber == 2 || martixnumber == 3 || martixnumber == 4) {
            validation = true;
        }
    } while (!validation);

	return martixnumber;
}*/
int startMenu() {
    string wybor;
    int option;
    bool validation = false;
    do {
        try {
            system("cls");
            cout << endl << "Dzia³ania na macierzach" << endl << endl;
            cout << "Podaj sposób wprowadzania danych: " << endl;
            cout << "1. Dane z pliku " << endl;
            cout << "2. Dane wprowadzone z klawiatury " << endl;
            cout << "3. Dane pseudolosowe " << endl;
            cout << endl;
            cout << "Wpisz Exit by zakoñczyæ program" << endl;
            cin >> wybor;
            if (wybor != "1" && wybor != "2" && wybor != "3"&& wybor != "Exit"&& wybor != "exit") {
                throw 'e';
            }
            if (wybor == "Exit" || wybor == "exit") {
                option = 0;
                validation = true;
            }
            else
            {
                option = stoi(wybor);
                validation = true;

            }
        }
        catch (...) {

        };
    } while (!validation);
    return option;
}


//DODAWANIE MACIERZY
/*
void dodawanie(int xsize1, int xsize2, int ysize1, int ysize2, int** matrix1, int** matrix2) {
    if (xsize1 != xsize2 || ysize1 != ysize2)
    {
        cout << "ROZMIARY MACIERZY NIE S¥ IDENTYCZNE!" << endl;
    }
    else {
        for (int i = 0;i < xsize1;i++) {
            for (int j = 0;j < ysize1;j++) {
                matrix1[i][j] += matrix2[i][j];
            }
        }
        wypiszWynik(matrix1,xsize1,ysize1);
    }
}
    */
    //KONIEC SEKCJI DODAWAWANIA MACIERZY

    //MNO¯ENIE MACIERZY
void przepiszWynikDoMatrix1(int** matrix1, int** tab, int xsize, int ysize) {
    for (int i = 0;i < xsize;i++) {
        for (int j = 0;j < ysize;j++) {
            matrix1[i][j] = tab[i][j];
        }
    }
    wypiszWynik(matrix1, xsize, ysize);
}
bool sprawdzanieMnozeniaMacierzy(int xsize1, int xsize2, int ysize1, int ysize2) {
    //Dwie macierze mo¿na pomno¿yæ tylko wtedy gdy liczba kolumn macierzy A jest równa liczbie wierszy macierzy B
    if (ysize1== xsize2 && ysize1==xsize2) {
        return true;
    }
    return false;
}
    void mnozenieMacierzy(int xsize1, int xsize2, int ysize1, int ysize2, int** matrix1, int** matrix2) {
        


        int xsize = xsize1;   //DEKLARACJA ROZMIARÓW KOÑCOWEJ MACIERZY
        int ysize = xsize2;
        if (xsize1 > xsize2) {
            xsize = xsize2;
        }
        if (ysize1 > ysize2) {
            ysize = ysize2;
        }

        //JEŒLI DYNAMICZNE TO JAK POTEM USUN¥Æ Z PAMIÊCI J¥ W FUNKCJI?	
        int** tab;
        tab = new int*[xsize];
        	for (int i = 0;i < xsize;i++) {
        		tab[i] = new int[ysize];
        	}
        //DZIA£A TYLKO DLA SYMETRYCZNYCH TRZEBA POPRAWIÆ!!!!!!!!!!!!  

        //int tab[xsize][ysize];
        for (int i = 0;i < xsize;i++) { // iteracja po kolumnach docelowej macierzy
            for (int j = 0;j < ysize;j++) {// iteracja po wierszach docelowej macierzy
                int temp = 0;
                for (int k = 0;k < xsize1;k++) { // a to leci po macierzy otrzymanej
       
                    temp += matrix1[k][i] * matrix2[j][k];
                }

                tab[i][j] = temp;
            }

        }
        przepiszWynikDoMatrix1(matrix1, tab, xsize, ysize);
    }

    //KONIEC SEKCJI MNO¯ENIA MACIERZY

    //TRANSPOZYCJA MACIERZY

	
    void transpozycja(int* xsize, int* ysize, int** matrix) {
        //TODO
        //TRZEBA ZMIENIÆ INPUT XSIZE I YSIZE NA WSKANIKI, PONIEWA¯ NA KOÑCU MUSZE ZAMIENIÆ MIEJSCAMI WARTOŒCI X I Y

        int** tab; //tworzenie macierzy pomocniczej
        tab = new int* [*ysize];
        for (int i = 0;i < *ysize;i++) {
            tab[i] = new int[*xsize];
        }
        for (int i = 0;i < *xsize;i++) {
            for (int j = 0;j < *ysize;j++) {
                tab[j][i] = matrix[i][j];
            }

            przepiszWynikDoMatrix1(matrix, tab, *ysize, *xsize);
            int temp = *xsize;
            *xsize = *ysize;
            *ysize = *xsize;

        }
    }

/*
int wyznacznik(int n) {
	return n;


	
}*/