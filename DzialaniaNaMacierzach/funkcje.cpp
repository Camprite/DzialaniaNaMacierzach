#include "funkcje.h"
#include <iostream>
#include <fstream>
using namespace std;

//-----------------------WCZYTYWANIE DANYCH Z PLIKU-----------------------
bool walidacjaPliku(string plik) {


    return true; // TESTOWO
}
void wczytajPlik(string plik,int*** matrixarray,int** matrixspec,int* matrixnumber) {
    bool walidacja = false;
    ifstream file;
    do {
        try {
            cout << "Podaj nazwe pliku: ";
            cin >> plik;
            file.open(plik, ios::in);
            if (file.good()) {
                walidacja = true;
            }
            if (!file.good()) {
                throw 'e';
            }
        }
        catch (...) {
            cout << "Coœ posz³o nie tak, Kliknij dowolny klawisz by spróbowaæ jeszcze raz" << endl;
            system("PAUSE");
        }
    } while (!walidacja);

    
    
    file >> *matrixnumber;
    cout << *matrixnumber;
    matrixarray = new int** [*matrixnumber];
    matrixspec = new int* [*matrixnumber];
    // ---------------ZADEKLAROWANIE PAMIÊCI DLA SPECYFIKACJI DANEJ MACIERZY
    for (int i = 0;i < *matrixnumber;i++) { 
        matrixspec[i] = new int[3];
    }

    // ----------------WCZYTYWANIE DANYCH -----------------------
    for(int i=0;i< *matrixnumber;i++){
        file >> matrixspec[i][0]; //pobranie xsize
        file >> matrixspec[i][1]; //pobranie ysize
        file >> matrixspec[i][2]; //pobranie wyznacznika macierzy domyœlnie 0
        cout << "Matrixspecx: " << matrixspec[i][0] << endl;
        cout << "Matrixspecy: " << matrixspec[i][1] << endl;
        cout << "Matrixspect: " << matrixspec[i][2] << endl;
        matrixarray[i] = new int* [matrixspec[i][0]];
        for (int j = 0;j < matrixspec[i][0];j++) {
            //matrixarray[i] = new int* [matrixspec[i][0]];
            matrixarray[i][j] = new int[matrixspec[i][1]];
           // for (int k = 0;k < matrixspec[i][1];k++) {
              //  matrixarray[i][j] = new int [matrixspec[i][1]];
          //  }
        } 
        for (int j = 0;j < matrixspec[i][0];j++) {
            for (int k = 0;k < matrixspec[i][1];k++) {
                
                int test;
                file >> test;
                cout << test << " - ";
                matrixarray[i][j][k] = test;
                
                // cout << "i: " << i << "j: " << j << "k: " << k << endl;
            }
            cout << endl;
        }
    }    

    //------------WYPISYWANIE DANYCH CHWILOWE ---------------
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
//-----------------------KONIEC WCZYTYWANIA DANYCH Z PLIKU----------------

void wypiszWynik(int** matrix, int xsize, int ysize) {
    for (int i = 0;i < xsize;i++) {
        for (int j = 0;j < ysize;j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int enterMartixNumber() {
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
}
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
            if (wybor == "Exit" && wybor == "exit") {
                return 0;
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