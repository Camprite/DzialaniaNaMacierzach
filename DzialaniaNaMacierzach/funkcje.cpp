#include "funkcje.h"
#include <iostream>
using namespace std;

int enterMartixNumber() {
    cout << "Podaj ilo�� macierzy (1-4): "; //trzeba to zmieni� na funkcje :)
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
    cout << endl << "Dzia�ania na macierzach" << endl << endl;
    cout << "Podaj spos�b wprowadzania danych: " << endl;
    cout << "1. Dane z pliku " << endl;
    cout << "2. Dane wprowadzone z klawiatury " << endl;
    cout << "3. Dane pseudolosowe " << endl;
    bool validation = false;
    int option = 0;
    do {
        cin >> option;
        if (option == 1 || option == 2 || option == 3) {
            validation = true;
        }
    } while (!validation);
    system("cls");//Czyszczenie konsoli

    return option;
}



/*
void mnozenie() {


	
}void dodawanie() {


	
}void transpozycja() {


	
}int wyznacznik(int n) {
	return n;


	
}*/