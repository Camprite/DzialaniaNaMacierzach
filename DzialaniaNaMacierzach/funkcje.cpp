#include "funkcje.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
using namespace std;
//----------------------------------------------DODAWANIE MACIERZY//----------------------------------------------
void addingMatrixs(int matrix1, int matrix2, int*** matrixarray, int** matrixspec, int* matrixnumber) {
	if (matrixspec[matrix1][0] != matrixspec[matrix2][0] || matrixspec[matrix1][1] != matrixspec[matrix2][1])
	{
		cout << "ROZMIARY MACIERZY NIE S¥ IDENTYCZNE!" << endl;

	}
	else {
		for (int i = 0;i < matrixspec[matrix1][0];i++) {
			for (int j = 0;j < matrixspec[matrix1][1];j++) {
				matrixarray[matrix1][i][j] = matrixarray[matrix1][i][j] + matrixarray[matrix2][i][j];
				cout << matrixarray[matrix1][i][j];

			}
		}
		//wypiszWynik(matrix1,xsize1,ysize1);
	}
}

//----------------------------------------------MNO¯ENIE MACIERZY//----------------------------------------------
void multiplyingMatrixs(int matrix1, int matrix2, int*** matrixarray, int** matrixspec, int* matrixnumber) {
	if ((matrixspec[matrix1][0] == matrixspec[matrix2][0] && matrixspec[matrix1][1] == matrixspec[matrix2][0]) ||
		(matrixspec[matrix1][1] == matrixspec[matrix2][0] && matrixspec[matrix1][0] == matrixspec[matrix2][1])) {
		int size = matrixspec[matrix1][0];   //DEKLARACJA ROZMIARÓW KOÑCOWEJ MACIERZY 
		int xmin = matrixspec[matrix1][0];
		if (matrixspec[matrix1][0] > matrixspec[matrix1][1]) {
			size = matrixspec[matrix1][0];
			xmin = matrixspec[matrix1][1];
		}
		int** tab;
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
		for (int i = 0;i < size;i++) { // iteracja po kolumnach docelowej macierzy
			for (int j = 0;j < size;j++) {// iteracja po wierszach docelowej macierzy
				cout << " " << tab[i][j] << " ";
			}
			cout << endl;
		}
		matrixspec[*matrixnumber][1] = size;
		matrixspec[*matrixnumber][2] = 0;
		for (int i = 0;i < size;i++) { // iteracja po kolumnach docelowej macierzy
			for (int j = 0;j < size;j++) {// iteracja po wierszach docelowej macierzy
				matrixarray[*matrixnumber][i][j] = tab[i][j];
				cout << matrixarray[*matrixnumber][i][j] << ". .";
			}
			cout << endl;
		}
		for (int i = 0;i < size;i++) {
			delete[] tab[i];
		}
		delete[] tab;
		*matrixnumber = *matrixnumber + 1;
	}
	else {
		cout << "Macierze nie mog¹ zostaæ pomno¿one! Z£Y ROZMIAR" << endl;
		return;
	}
}
//----------------------------------------------TRANSPOZYCJA MACIERZY//----------------------------------------------
void transpositionMatrix(int matrix1, int*** matrixarray, int** matrixspec, int* matrixnumber) {
	int** tab;
	tab = new int* [matrixspec[matrix1][1]];
	for (int i = 0;i < matrixspec[matrix1][1];i++) {
		tab[i] = new int[matrixspec[matrix1][0]];
	}
	for (int i = 0;i < matrixspec[matrix1][0];i++) {
		for (int j = 0;j < matrixspec[matrix1][1];j++) {
			tab[j][i] = matrixarray[matrix1][i][j];
		}
	}
	for (int i = 0;i < matrixspec[matrix1][1];i++) {
		for (int j = 0;j < matrixspec[matrix1][0];j++) {
			matrixarray[matrix1][i][j] = tab[i][j];
		}
	}
	int tempx = matrixspec[matrix1][0];
	int tempy = matrixspec[matrix1][1];
	matrixspec[matrix1][0] = tempy;
	matrixspec[matrix1][1] = tempx;
	for (int i = 0;i < matrixspec[matrix1][0];i++) {
		delete[] tab[i];
	}
	delete[] tab;
}
//----------------------------------------------WYZNACZNIK MACIERZY//----------------------------------------------
double determinantOfMatrix(int matrix1, int*** matrixarray, int** matrixspec, int n, int w, int* WK) {
	int    i, j, k, m, * KK;
	double s;
	if (n == 1)                     // sprawdzamy warunek zakoñczenia rekurencji
		return matrixarray[matrix1][w][WK[0]];    // macierz 1 x 1, wyznacznik równy elementowi
	else
	{
		KK = new int[n - 1];        // tworzymy dynamiczny wektor kolumn
		s = 0;                         // zerujemy wartoœæ rozwiniêcia
		m = 1;                         // pocz¹tkowy mno¿nik
		for (i = 0; i < n; i++)       // pêtla obliczaj¹ca rozwiniêcie
		{
			k = 0;                       // tworzymy wektor kolumn dla rekurencji
			for (j = 0; j < n - 1; j++) // ma on o 1 kolumnê mniej ni¿ WK
			{
				if (k == i) k++;          // pomijamy bie¿¹c¹ kolumnê
				KK[j] = WK[k++];     // pozosta³e kolumny przenosimy do KK
			}
			s += m * matrixarray[matrix1][w][WK[i]] * determinantOfMatrix(matrix1, matrixarray, matrixspec, n - 1, w + 1, KK);
			m = -m;                      // kolejny mno¿nik
		}
		delete[] KK;                 // usuwamy zbêdn¹ ju¿ tablicê dynamiczn¹
		return s;                      // ustalamy wartoœæ funkcji
	}
}
bool isDeterminantOfMatrixPossible(int matrix1, int*** matrixarray, int** matrixspec) {
	if (matrixspec[matrix1][0] == matrixspec[matrix1][1]) {
		return true;
	}
	else {
		return false;
	}
}
void determinantOfMatrixStarter(int matrix1, int*** matrixarray, int** matrixspec) {
	int n = matrixspec[matrix1][0];
	int i, j;
	int* WK = new int[n];
	for (int i = 0; i < n; i++)         // wype³niamy go numerami kolumn
	{
		WK[i] = i;
	}
	double score = determinantOfMatrix(matrix1, matrixarray, matrixspec, n, 0, WK);
	matrixspec[matrix1][2] = determinantOfMatrix(matrix1, matrixarray, matrixspec, n, 0, WK);
}

//------------WYPISYWANIE DANYCH ---------------
void coutAllMatrixs(int*** matrixarray, int** matrixspec, int* matrixnumber) {
	for (int i = 0;i < *matrixnumber;i++) {
		cout << "Macierz nr: " << i + 1 << ". " << endl;
		for (int j = 0;j < matrixspec[i][0];j++) {
			for (int k = 0;k < matrixspec[i][1];k++) {
				cout << matrixarray[i][j][k] << " ";
			}
			cout << endl;
		}
	}
}
void coutMatrix(int*** matrixarray, int** matrixspec, int matrixnumber) {
	int val = matrixnumber;
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
int positiveValueFunctionMenu(string message) {
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
		if (temp == "Exit" || temp == "exit") {
			return 0;
		}
		if (isNumber(temp, true)) {
			if (stoi(temp) == 0) {
				return 0;
			}
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
int positiveValueNonCLS(string message, int range) {
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
		if (temp == "exit" || temp == "Exit") {
			return 100;
		}
		if (isNumber(temp, true)) {
			int value = stoi(temp);
			if (value < range) {
				return value;  //ZMIENNA PRZECHOWUJ¥CA ILOSC MACIERZY
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

void enterMartixNumberFromKeyboard(int*** matrixarray, int** matrixspec, int* matrixnumber) {
	*matrixnumber = positiveValue("Podaj ilosæ macierzy któr¹ chcesz wpisaæ");
	cout << *matrixnumber;
	// matrixarray = new int** [*matrixnumber];
	// matrixspec = new int* [*matrixnumber];
	 // ---------------ZADEKLAROWANIE PAMIÊCI DLA SPECYFIKACJI DANEJ MACIERZY

  //   for (int i = 0;i < (*matrixnumber);i++) {
  //       matrixspec[i] = new int[3];
   //  }


	for (int i = 0;i < *matrixnumber;i++) {
		int lkolumn = intValue("Podaj liczbe kolumn: ");
		int lwierszy = intValue("Podaj liczbe wierszy: ");
		matrixspec[i][0] = lkolumn; //pobranie xsize
		matrixspec[i][1] = lwierszy; //pobranie ysize
		matrixspec[i][2] = 0; //pobranie wyznacznika macierzy domyœlnie 0
		//     matrixarray[i] = new int* [matrixspec[i][0]];
		   //  for (int j = 0;j < matrixspec[i][0];j++) {
			  //   matrixarray[i][j] = new int[matrixspec[i][1]];
	 //
		  //   }
		for (int j = 0;j < matrixspec[i][0];j++) {
			for (int k = 0;k < matrixspec[i][1];k++) {
				string tekst = "x: " + to_string(j + 1) + " y: " + to_string(k + 1);

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
	//  matrixarray = new int** [*matrixnumber];
   //   matrixspec = new int* [*matrixnumber];
	  // ---------------ZADEKLAROWANIE PAMIÊCI DLA SPECYFIKACJI DANEJ MACIERZY

	//  for (int i = 0;i < (*matrixnumber);i++) {
	  //    matrixspec[i] = new int[3];
	  //}


	for (int i = 0;i < *matrixnumber;i++) {
		int lkolumn = intValue("Podaj liczbe kolumn: ");
		int lwierszy = intValue("Podaj liczbe wierszy: ");

		int downRange = intValue("Podaj zakres OD: ");
		int upRange = intValue("Podaj zakres DO: ");
		matrixspec[i][0] = lkolumn; //pobranie xsize
		matrixspec[i][1] = lwierszy; //pobranie ysize
		matrixspec[i][2] = 0; //pobranie wyznacznika macierzy domyœlnie 0
		//   matrixarray[i] = new int* [matrixspec[i][0]];
		  // for (int j = 0;j < matrixspec[i][0];j++) {
		   //    matrixarray[i][j] = new int[matrixspec[i][1]];

		//   }
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
void saveAndQuit(int*** matrixarray, int** matrixspec, int* matrixnumber) {
	int option = positiveValueNonCLS("Wpisz 0 by wyjsæ bez zapisu lub 1 by zapisaæ macierze do pliku:");
	switch (option) {
	case 0: {
		return;
		break;
	}
	case 1: {
		bool isSaved = false;
		do {
			string filename;
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
			}
			else {
				isSaved = false;
			}
		} while (!isSaved);
		break;
	}
	}
}
//------------------------------------------MENU WYWO£YWANIA OPERACJI---------------------------------------
void operationMenu(int*** matrixarray, int** matrixspec, int* matrixnumber) {
	int option = INT_MAX;
	do {
		option = positiveValueFunctionMenu("Wpisz Exit by zapisaæ i wyjœæ \nDostêpne funkcje\n1. Dodawanie macierzy\n2. Mno¿enie macierzy\n3. Transpozycja macierzy\n4. Wyznacznik macierzy\n5. Wypisz wszystkie macierze \nPodaj funkcje której chcesz u¿yæ: ");
		switch (option)
		{
		case 0: {
			saveAndQuit(matrixarray, matrixspec, matrixnumber);
			break;
		}
		case 1: { //DODAWANIE MACIERZY
			system("CLS");
			cout << "Dostêpne macierze: " << endl;
			coutAllMatrixs(matrixarray, matrixspec, matrixnumber);

			int matrix1 = positiveValueNonCLS("Podaj numer pierwszej macierzy lub wpisz exit by wróciæ", *matrixnumber + 1);
			if (matrix1 == 100 || matrix1 == 0) {
				operationMenu(matrixarray, matrixspec, matrixnumber);
			}
			int* matrixOutput = &matrix1;
			int matrix2 = positiveValueNonCLS("Podaj numer drugiej macierzy lub wpisz exit by wróciæ", *matrixnumber + 1);
			if (matrix2 == 100 || matrix2 == 0) {
				operationMenu(matrixarray, matrixspec, matrixnumber);
			}
			addingMatrixs(matrix1 - 1, matrix2 - 1, matrixarray, matrixspec, matrixnumber);
			//TUTAJ WYWO£ANIE FUNKCJI 
			cout << endl;

			coutMatrix(matrixarray, matrixspec, matrix1 - 1);
			break;
		}
		case 2: {//MNO¯ENIE MACIERZY
			system("CLS");
			cout << "Dostêpne macierze: " << endl;
			coutAllMatrixs(matrixarray, matrixspec, matrixnumber);

			int matrix1 = positiveValueNonCLS("Podaj numer pierwszej macierzy lub wpisz exit by wróciæ", *matrixnumber + 1);
			if (matrix1 == 100 || matrix1 == 0) {
				operationMenu(matrixarray, matrixspec, matrixnumber);
			}
			int matrix2 = positiveValueNonCLS("Podaj numer drugiej macierzy lub wpisz exit by wróciæ", *matrixnumber + 1);
			if (matrix2 == 100 || matrix2 == 0) {
				operationMenu(matrixarray, matrixspec, matrixnumber);
			}
			multiplyingMatrixs(matrix1 - 1, matrix2 - 1, matrixarray, matrixspec, matrixnumber);
			//  coutMatrix(matrixarray, matrixspec, matrix1 - 1);
			  //TUTAJ WYWO£ANIE FUNKCJI DZIA£ANIA
			break;
		}
		case 3: {//TRANSPOZYCJA MACIERZY
			system("CLS");
			cout << "Dostêpne macierze: " << endl;
			coutAllMatrixs(matrixarray, matrixspec, matrixnumber);

			int matrix1 = positiveValueNonCLS("Podaj numer macierzy lub wpisz exit by wróciæ", *matrixnumber + 1);
			if (matrix1 == 100 || matrix1 == 0) {
				operationMenu(matrixarray, matrixspec, matrixnumber);
			}
			transpositionMatrix(matrix1 - 1, matrixarray, matrixspec, matrixnumber);
			//TUTAJ WYWO£ANIE FUNKCJI DZIA£ANIA
			break;
		}
		case 4: {//WYZNACZNIK MACIERZY
			system("CLS");
			cout << "Dostêpne macierze: " << endl;
			coutAllMatrixs(matrixarray, matrixspec, matrixnumber);

			int matrix1 = positiveValueNonCLS("Podaj numer macierzy lub wpisz exit by wróciæ", *matrixnumber + 1);
			if (matrix1 == 100 || matrix1 == 0) {
				operationMenu(matrixarray, matrixspec, matrixnumber);
			}
			if (isDeterminantOfMatrixPossible(matrix1 - 1, matrixarray, matrixspec) == true) {
				determinantOfMatrixStarter(matrix1 - 1, matrixarray, matrixspec);
				cout << "Wyznacznik macierzy wynosi: " << matrixspec[matrix1 - 1][2] << endl;
				system("PAUSE");
			}
			else {
				cout << "NIE MO¯NA WYKONAC OPERACJI" << endl;
				system("PAUSE");
			}

			break;
		}
		case 5:
		{
			system("CLS");
			coutAllMatrixs(matrixarray, matrixspec, matrixnumber);
			cout << "WCIŒNIJ DOWOLNY KLAWISZ BY KONTYNUOWAÆ" << endl;
			system("PAUSE");
			operationMenu(matrixarray, matrixspec, matrixnumber);
		}
		default:
			break;
		}
	} while (option != 0);
}

void wypiszWynik(int** matrix, int xsize, int ysize) {
	for (int i = 0;i < xsize;i++) {
		for (int j = 0;j < ysize;j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
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




