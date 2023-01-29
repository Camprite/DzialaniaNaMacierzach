#include <iostream>
#include <locale.h>
#include <fstream>
#include "funkcje.h"
#include <time.h>
#include <cstdlib>
using namespace std;
int main()
{
	int*** matrixarray = new int** [50];
	int** matrixspec = new int* [50];
	int* matrixnumber = new int[50];//ilosć macierzy
	for (int i = 0;i < 50;i++) {
		matrixarray[i] = new int* [50];
		matrixspec[i] = new int[50];
		for (int j = 0;j < 50;j++) {
			matrixarray[i][j] = new int[50];
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
	operationMenu(matrixarray, matrixspec, matrixnumber);
	return 1;
}