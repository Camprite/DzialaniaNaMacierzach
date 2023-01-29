#include "funkcje.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
using namespace std;
//----------------------------------------------DODAWANIE MACIERZY----------------------------------------------
void addingMatrixs(int matrix1, int matrix2, int*** matrixarray, int** matrixspec, int* matrixnumber) {
	if (matrixspec[matrix1][0] != matrixspec[matrix2][0] || matrixspec[matrix1][1] != matrixspec[matrix2][1]) //Sprawdzanie czy macierze mog� zosta� dodane
	{
		cout << "ROZMIARY MACIERZY NIE S� IDENTYCZNE!" << endl;

	}
	else {
		for (int i = 0;i < matrixspec[matrix1][0];i++) { //P�tla dodaj�ca macierze do siebie
			for (int j = 0;j < matrixspec[matrix1][1];j++) {
				matrixarray[matrix1][i][j] = matrixarray[matrix1][i][j] + matrixarray[matrix2][i][j];
				cout << matrixarray[matrix1][i][j];

			}
		}
	}
}

//----------------------------------------------MNO�ENIE MACIERZY----------------------------------------------
void multiplyingMatrixs(int matrix1, int matrix2, int*** matrixarray, int** matrixspec, int* matrixnumber) {

	if ((matrixspec[matrix1][0] == matrixspec[matrix2][0] && matrixspec[matrix1][1] == matrixspec[matrix2][0]) || //Sprawdzanie czy macierze mog� zosta� dodane
		(matrixspec[matrix1][1] == matrixspec[matrix2][0] && matrixspec[matrix1][0] == matrixspec[matrix2][1])) {
		int size = matrixspec[matrix1][0];   
		int xmin = matrixspec[matrix1][0];
		if (matrixspec[matrix1][0] > matrixspec[matrix1][1]) {//DEKLARACJA ROZMIAR�W KO�COWEJ MACIERZY 
			size = matrixspec[matrix1][0];
			xmin = matrixspec[matrix1][1];
		}
		int** tab;					//Tymaczasowa tablica dynamiczna z wynikami
		tab = new int* [size];
		for (int i = 0;i < size;i++) {
			tab[i] = new int[size];
		}
		int wynik = 0;
		for (int i = 0;i < size;i++) {
			for (int j = 0;j < size;j++) {
				wynik = 0;
				for (int m1 = 0;m1 < xmin;m1++) {
					wynik = wynik + matrixarray[matrix2][m1][j] * matrixarray[matrix1][i][m1];
				}
				tab[i][j] = wynik;
			}
		}
		int temp = *matrixnumber;  //Debug, bez tego nie wiadomo dlaczego nie chce dzia�a�
		matrixspec[temp][0] = size;
		matrixspec[temp][1] = size;
		matrixspec[temp][2] = 0;	
		for (int i = 0;i < size;i++) { //Przepisanie tymczasowej macierzy do macierzy g��wnej
			for (int j = 0;j < size;j++) {
				matrixarray[temp][i][j] = tab[i][j];
			}
		}
		for (int i = 0;i < size;i++) { //Pozbycie si� macierzy tymczasowej
			delete[] tab[i];
		}
		delete[] tab;
		*matrixnumber = *matrixnumber + 1; // Zwi�kszenie licznika macierzy(Wynikiem jest nowa macierz)
	}
	else {
		cout << "Macierze nie mog� zosta� pomno�one! Z�Y ROZMIAR" << endl;
		system("PAUSE");
		return;
	}
}
//----------------------------------------------TRANSPOZYCJA MACIERZY----------------------------------------------
void transpositionMatrix(int matrix1, int*** matrixarray, int** matrixspec, int* matrixnumber) {
	int** tab;									//Tworzenie tymczasowej tablicy dynamicznej
	tab = new int* [matrixspec[matrix1][1]]; 
	for (int i = 0;i < matrixspec[matrix1][1];i++) {
		tab[i] = new int[matrixspec[matrix1][0]];
	}
	for (int i = 0;i < matrixspec[matrix1][0];i++) {		//Przepisanie wynik�w do tablicy tymczasowej
		for (int j = 0;j < matrixspec[matrix1][1];j++) {
			tab[j][i] = matrixarray[matrix1][i][j];
		}
	}
	for (int i = 0;i < matrixspec[matrix1][1];i++) {		//Przepisanie z tablicy tymczasowej do g��wnej
		for (int j = 0;j < matrixspec[matrix1][0];j++) {
			matrixarray[matrix1][i][j] = tab[i][j];
		}
	}
	int tempx = matrixspec[matrix1][0];						//Ustawienie nowych warto�ci dla tablicy
	int tempy = matrixspec[matrix1][1];
	matrixspec[matrix1][0] = tempy;
	matrixspec[matrix1][1] = tempx;
	for (int i = 0;i < matrixspec[matrix1][0];i++) {		//Usuni�cie tablicy tymczasowej
		delete[] tab[i];
	}
	delete[] tab;
}
//----------------------------------------------WYZNACZNIK MACIERZY----------------------------------------------
double determinantOfMatrix(int matrix1, int*** matrixarray, int** matrixspec, int n, int w, int* wierszKolumn) {
	int   k, m, * wektorKolumn;
	double s;
	if (n == 1)                     // sprawdzamy warunek zako�czenia rekurencji
		return matrixarray[matrix1][w][wierszKolumn[0]];    // macierz 1 x 1, wyznacznik r�wny elementowi
	else
	{
		wektorKolumn = new int[n - 1];        //Tworzymy dynamiczny wektor kolumn
		s = 0;                         //Zerujemy warto�� rozwini�cia
		m = 1;                         //Pocz�tkowy mno�nik
		for (int i = 0; i < n; i++)       //P�tla obliczaj�ca rozwini�cie
		{
			k = 0;                       //Tworzymy wektor kolumn dla rekurencji
			for (int j = 0; j < n - 1; j++) //Ma on o 1 kolumn� mniej ni� WK
			{
				if (k == i) k++;          //Pomijamy bie��c� kolumn�
				wektorKolumn[j] = wierszKolumn[k++];     //Pozosta�e kolumny przenosimy do KK
			}
			s += m * matrixarray[matrix1][w][wierszKolumn[i]] * determinantOfMatrix(matrix1, matrixarray, matrixspec, n - 1, w + 1, wektorKolumn);
			m = -m;                      //Kolejny mno�nik
		}
		delete[] wektorKolumn;                 //Usuwamy tymczasow� tablic� dynamiczn�
		return s;                      // Ustalamy warto�� funkcji
	}
}
//Sprawdzenie czy mo�na obliczy� wyznacznik dla danej macierzy
bool isDeterminantOfMatrixPossible(int matrix1, int*** matrixarray, int** matrixspec) {
	if (matrixspec[matrix1][0] == matrixspec[matrix1][1]) { 
		return true;
	}
	else {
		return false;
	}
}
//Funkcja wywo�uj�ca docelow� rekurencje
void determinantOfMatrixStarter(int matrix1, int*** matrixarray, int** matrixspec) {
	int n = matrixspec[matrix1][0];
	int i, j;
	int* WK = new int[n];
	for (int i = 0; i < n; i++)       //Stworzenie wektora kolumn
	{
		WK[i] = i;
	}
	double score = determinantOfMatrix(matrix1, matrixarray, matrixspec, n, 0, WK);
	matrixspec[matrix1][2] = determinantOfMatrix(matrix1, matrixarray, matrixspec, n, 0, WK); //Przypisanie wyniku do specyfikacji danej macierzy
}

//------------WYPISYWANIE WSZYSTIKICH DANYCH ---------------
void coutAllMatrixs(int*** matrixarray, int** matrixspec, int* matrixnumber) { 
	for (int i = 0;i < *matrixnumber;i++) {
		cout << "Macierz nr: " << i + 1 << ". " << matrixspec[i][0] << "|" << matrixspec[i][1] << endl;
		for (int j = 0;j < matrixspec[i][0];j++) {
			for (int k = 0;k < matrixspec[i][1];k++) {
				cout << matrixarray[i][j][k] << " ";
			}
			cout << endl;
		}
	}
}
//------------WYPISYWANIE POJEDY�CZYCH DANYCH (UNUSED)---------------
void coutMatrix(int*** matrixarray, int** matrixspec, int matrixnumber) {
	int val = matrixnumber;
	for (int j = 0;j < matrixspec[val][0];j++) {
		for (int k = 0;k < matrixspec[val][1];k++) {
			cout << matrixarray[val][j][k] << " ";
		}
		cout << endl;
	}
}
//------------PSEUDOLOSOWA LICZBA Z ZADANEGO ZAKRESU---------------
int randomValue(int upRange, int downRange) {
	if (upRange == downRange) { //Debug, gdy wpisane zostaj� te same warto�ci fukcja si� wywala�a
		return upRange;
	}
	int zakres = upRange - downRange;
	int value = (rand() % zakres) + downRange;
	return value;
}
//-------------SPRAWDZENIE CZY ZADANA WARTO�� JEST LICZB� DODATNI�------------
bool isNumber(string var, bool czyDodatnie) { 
	int wartosc;
	try { wartosc = stoi(var); }
	catch (...) {
		return false;
	}
	if (czyDodatnie && wartosc >= 0) {
		return true;
	}
	if (!czyDodatnie && wartosc <= 0) {
		return false;
	}
	return true;
}
//-------------SPRAWDZENIE CZY ZADANA WARTO�� JEST LICZB�------------
bool isNumber(string var) {
	int wartosc;
	try { wartosc = stoi(var); }
	catch (...) {
		return false;
	}
	return true;
}
//-------------POBRANIE WARTO�CI LICZBOWEJ------------
int positiveValue(string message) {
	string temp;
	bool walidacja = false;
	bool czyDodatanie = true;
	bool tekst = false;
	do {
		system("cls");
		if (tekst == true) {
			cout << "Co� posz�o nie tak, spr�buj jeszcze raz" << endl;
		}
		cout << message << endl;
		cin >> temp;
		if (isNumber(temp, true)) {
			return  stoi(temp);
			walidacja = true;
		}
		else {
			tekst = true;
		}
	} while (!walidacja);
	return 0;
}
//-------------POBRANIE WARTO�CI LICZBOWEJ TYLKO DLA MENU FUNKCJI Z UWZGL�DNIENIEM WYJ�CIA Z PROGRAMU------------
int positiveValueFunctionMenu(string message) {
	string temp;
	bool walidacja = false;
	bool czyDodatanie = true;
	bool tekst = false;
	do {
		system("cls");
		if (tekst == true) {
			cout << "Co� posz�o nie tak, spr�buj jeszcze raz" << endl;
		}
		cout << message << endl;
		cin >> temp;
		if (temp == "Exit" || temp == "exit") {
			return 0;
		}
		if (isNumber(temp, true)) {
			if (stoi(temp) == 0) {
				return 0;
			}
			return  stoi(temp); //ZMIENNA PRZECHOWUJ�CA ILOSC MACIERZY
			walidacja = true;
		}
		else {
			tekst = true;
		}
	} while (!walidacja);
	return 0;
}
//-----------POBRANIE WATO�CI DODATNIEJ Z WIADOMO�CI� PRZED------------
int positiveValueNonCLS(string message) {
	string temp;
	bool walidacja = false;
	bool czyDodatanie = true;
	bool tekst = false;
	do {
		if (tekst == true) {
			cout << "Co� posz�o nie tak, spr�buj jeszcze raz" << endl;
		}
		cout << message << endl;
		cin >> temp;
		if (isNumber(temp, true)) {
			return  stoi(temp);
			walidacja = true;
		}
		else {
			tekst = true;
		}
	} while (!walidacja);
	return 0;
}
//-----------POBRANIE WATO�CI DODATNIEJ OD 1 DO ZADANEJ WARTO�CI Z WIADOMO�CI� PRZED ORAZ UWZGL�DNIENIEM 0 I EXIT JAKO WYJ�CIE VALUE:100------------
int positiveValueNonCLS(string message, int range) {
	string temp;
	bool walidacja = false;
	bool czyDodatanie = true;
	bool tekst = false;
	do {
		if (tekst == true) {
			cout << "Co� posz�o nie tak, spr�buj jeszcze raz" << endl;
		}
		cout << message << endl;
		cin >> temp;
		if (temp == "exit" || temp == "Exit") {
			return 100;
		}
		if (isNumber(temp, true)) {
			int value = stoi(temp);
			if (value < range) {
				return value;
			}
			if (value == 0) {
				return 100;
			}
		}
		else {
			tekst = true;
		}
	} while (!walidacja);
	return 0;
}
//-------------POBRANIE WARTO�CI INT Z WIADOMO�CI� PRZED-----------------
int intValue(string message) {
	string temp;
	bool walidacja = false;
	bool tekst = false;
	do {
		system("cls");
		if (tekst == true) {
			cout << "Co� posz�o nie tak, spr�buj jeszcze raz" << endl;
		}
		cout << message << endl;
		cin >> temp;
		if (isNumber(temp)) {
			return  stoi(temp); //ZMIENNA PRZECHOWUJ�CA ILOSC MACIERZY
			walidacja = true;
		}
		else {
			tekst = true;
		}
	} while (!walidacja);
	return 0;
}
//-------------POBRANIE WARTO�CI INT-----------------
int intValue() {
	string temp;
	bool walidacja = false;
	bool tekst = false;
	do {
		system("cls");
		if (tekst == true) {
			cout << "Co� posz�o nie tak, spr�buj jeszcze raz";
		}
		cin >> temp;
		if (isNumber(temp)) {
			return  stoi(temp);
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
				cout << "Co� posz�o nie tak, spr�buj jeszcze raz" << endl;
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
	file >> *matrixnumber; //Ustawienie ilo�ci macierzy
	  // ----------------WCZYTYWANIE DANYCH -----------------------
	for (int i = 0;i < *matrixnumber;i++) {
		file >> matrixspec[i][0]; //pobranie xsize
		file >> matrixspec[i][1]; //pobranie ysize
		file >> matrixspec[i][2]; //pobranie wyznacznika macierzy (domy�lnie 0)
		for (int j = 0;j < matrixspec[i][0];j++) {
			for (int k = 0;k < matrixspec[i][1];k++) {
				int value;
				file >> value;
				matrixarray[i][j][k] = value;
			}
		}
	}
}
//----------------------WCZYTYWANIE DANYCH Z KLAWIATURY-------------------
void enterMartixNumberFromKeyboard(int*** matrixarray, int** matrixspec, int* matrixnumber) {
	*matrixnumber = positiveValue("Podaj ilos� macierzy kt�r� chcesz wpisa�");
	cout << *matrixnumber;	//Ustawienie ilo�ci macierzy
	for (int i = 0;i < *matrixnumber;i++) {
		int lkolumn = intValue("Podaj liczbe kolumn: ");
		int lwierszy = intValue("Podaj liczbe wierszy: ");
		matrixspec[i][0] = lkolumn; //Pobranie xsize
		matrixspec[i][1] = lwierszy; //Pobranie ysize
		matrixspec[i][2] = 0; //Ustawienie wyznacznika macierzy na warto�� domy�ln� = 0
		for (int j = 0;j < matrixspec[i][0];j++) {
			for (int k = 0;k < matrixspec[i][1];k++) {
				string tekst = "x: " + to_string(j + 1) + " y: " + to_string(k + 1);
				matrixarray[i][j][k] = intValue(tekst);
			}
			cout << endl;
		}
	}

}
//----------------------WCZYTYWANIE DANYCH Z JAKO WARTOSCI LOSOWE-------------------
void enterMartixNumberFromRandom(int*** matrixarray, int** matrixspec, int* matrixnumber) {
	*matrixnumber = positiveValue("Podaj ilos� macierzy kt�r� chcesz wype�ni�: ");
	cout << *matrixnumber;	//Ustawienie ilo�ci macierzy
	for (int i = 0;i < *matrixnumber;i++) {
		int lkolumn = intValue("Podaj liczbe kolumn: ");
		int lwierszy = intValue("Podaj liczbe wierszy: ");

		int downRange = intValue("Podaj zakres OD: ");
		int upRange = intValue("Podaj zakres DO: ");
		matrixspec[i][0] = lkolumn; //Pobranie xsize
		matrixspec[i][1] = lwierszy; //Pobranie ysize
		matrixspec[i][2] = 0; //Pobranie wyznacznika macierzy domy�lnie 0
		for (int j = 0;j < matrixspec[i][0];j++) {
			for (int k = 0;k < matrixspec[i][1];k++) {
				string tekst = "x: " + to_string(j + 1) + " y: " + to_string(k + 1);
				matrixarray[i][j][k] = randomValue(upRange, downRange);
			}
		}
	}
	for (int i = 0;i < *matrixnumber;i++) {
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
//----------------------KONIEC PROGRAMU ZAPIS DO PLIKU-------------------
void saveAndQuit(int*** matrixarray, int** matrixspec, int* matrixnumber) {
	int option = positiveValueNonCLS("Wpisz 0 by wyjs� bez zapisu lub 1 by zapisa� macierze do pliku:");
	switch (option) {
	case 0: {
		break;
	}
	case 1: {
		bool isSaved = false;
		do {
			string filename;
			cout << "PODAJ NAZWE NOWEGO PLIKU, W PRZYPADKU ISTNIENIA PLIKU DANE NIE ZOSTAN� POPRAWNIE ZAPISANE" << endl;
			cin >> filename;
			ofstream saving;
			saving.open(filename, ios::app);
			if (saving.good()) {
				saving << *matrixnumber << endl;
				for (int i = 0;i < *matrixnumber;i++) {
					saving << matrixspec[i][0] << " ";
					saving << matrixspec[i][1] << " ";
					saving << matrixspec[i][2] << endl;
					for (int j = 0;j < matrixspec[i][0];j++) {
						for (int k = 0; k < matrixspec[i][1];k++) {
							saving << matrixarray[i][j][k] << " ";
						}
						saving << endl;
					}
				}
				saving.close();
				isSaved = true;
				return;
			}
			else {
				isSaved = false;
			}
		} while (!isSaved);
	}
	}
}
//------------------------------------------MENU WYWO�YWANIA OPERACJI---------------------------------------
void operationMenu(int*** matrixarray, int** matrixspec, int* matrixnumber) {
	int option = INT_MAX;
	do {
		option = positiveValueFunctionMenu("Wpisz Exit by zapisa� i wyj�� \nDost�pne funkcje\n1. Dodawanie macierzy\n2. Mno�enie macierzy\n3. Transpozycja macierzy\n4. Wyznacznik macierzy\n5. Wypisz wszystkie macierze \nPodaj funkcje kt�rej chcesz u�y�: ");
		switch (option)
		{
		case 0: {
			saveAndQuit(matrixarray, matrixspec, matrixnumber);
			break;
		}
		case 1: { //--------------------------DODAWANIE MACIERZY--------------------------
			system("CLS");
			cout << "Dost�pne macierze: " << endl;
			coutAllMatrixs(matrixarray, matrixspec, matrixnumber);
			int matrix1 = positiveValueNonCLS("Podaj numer pierwszej macierzy lub wpisz exit by wr�ci�", *matrixnumber + 1);
			if (matrix1 == 100 || matrix1 == 0) {
				operationMenu(matrixarray, matrixspec, matrixnumber);
			}
			int* matrixOutput = &matrix1;
			int matrix2 = positiveValueNonCLS("Podaj numer drugiej macierzy lub wpisz exit by wr�ci�", *matrixnumber + 1);
			if (matrix2 == 100 || matrix2 == 0) {
				operationMenu(matrixarray, matrixspec, matrixnumber);
			}
			addingMatrixs(matrix1 - 1, matrix2 - 1, matrixarray, matrixspec, matrixnumber);
			cout << endl;
			coutMatrix(matrixarray, matrixspec, matrix1 - 1);
			break;
		}
		case 2: {//--------------------------MNO�ENIE MACIERZY--------------------------
			system("CLS");
			cout << "Dost�pne macierze: " << endl;
			coutAllMatrixs(matrixarray, matrixspec, matrixnumber);

			int matrix1 = positiveValueNonCLS("Podaj numer pierwszej macierzy lub wpisz exit by wr�ci�", *matrixnumber + 1);
			if (matrix1 == 100 || matrix1 == 0) {
				operationMenu(matrixarray, matrixspec, matrixnumber);
			}
			int matrix2 = positiveValueNonCLS("Podaj numer drugiej macierzy lub wpisz exit by wr�ci�", *matrixnumber + 1);
			if (matrix2 == 100 || matrix2 == 0) {
				operationMenu(matrixarray, matrixspec, matrixnumber);
			}
			multiplyingMatrixs(matrix1 - 1, matrix2 - 1, matrixarray, matrixspec, matrixnumber);
			break;
		}
		case 3: {//--------------------------TRANSPOZYCJA MACIERZY--------------------------
			system("CLS");
			cout << "Dost�pne macierze: " << endl;
			coutAllMatrixs(matrixarray, matrixspec, matrixnumber);
			int matrix1 = positiveValueNonCLS("Podaj numer macierzy lub wpisz exit by wr�ci�", *matrixnumber + 1);
			if (matrix1 == 100 || matrix1 == 0) {
				operationMenu(matrixarray, matrixspec, matrixnumber);
			}
			transpositionMatrix(matrix1 - 1, matrixarray, matrixspec, matrixnumber);
			break;
		}
		case 4: {//--------------------------WYZNACZNIK MACIERZY--------------------------
			system("CLS");
			cout << "Dost�pne macierze: " << endl;
			coutAllMatrixs(matrixarray, matrixspec, matrixnumber);
			int matrix1 = positiveValueNonCLS("Podaj numer macierzy lub wpisz exit by wr�ci�", *matrixnumber + 1);
			if (matrix1 == 100 || matrix1 == 0) {
				operationMenu(matrixarray, matrixspec, matrixnumber);
			}
			if (isDeterminantOfMatrixPossible(matrix1 - 1, matrixarray, matrixspec) == true) {
				determinantOfMatrixStarter(matrix1 - 1, matrixarray, matrixspec);
				cout << "Wyznacznik macierzy wynosi: " << matrixspec[matrix1 - 1][2] << endl;
				system("PAUSE");
			}
			else {
				cout << "NIE MO�NA WYKONAC OPERACJI" << endl;
				system("PAUSE");
			}
			break;
		}
		case 5: {//--------------------------WYPISANIE WYSZTKICH WARTOSCI--------------------------
			system("CLS");
			coutAllMatrixs(matrixarray, matrixspec, matrixnumber);
			cout << "WCI�NIJ DOWOLNY KLAWISZ BY KONTYNUOWA�" << endl;
			system("PAUSE");
			operationMenu(matrixarray, matrixspec, matrixnumber);
		}
		default:
			break;
		}
	} while (option != 0);
}

int startMenu() {//--------------------------MENU STARTOWE--------------------------
	string wybor;
	int option;
	bool validation = false;
	do {
		try {
			system("cls");
			cout << endl << "Dzia�ania na macierzach" << endl << endl;
			cout << "Podaj spos�b wprowadzania danych: " << endl;
			cout << "1. Dane z pliku " << endl;
			cout << "2. Dane wprowadzone z klawiatury " << endl;
			cout << "3. Dane pseudolosowe " << endl;
			cout << endl;
			cout << "Wpisz Exit by zako�czy� program" << endl;
			cin >> wybor;
			if (wybor != "1" && wybor != "2" && wybor != "3" && wybor != "Exit" && wybor != "exit") {
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