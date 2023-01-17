#include <iostream>
using namespace std;

int main() {
	int x = 3, y = 3;
	int tab1[3][3] = { -1,-2,3 }, {0,2,1}, {-1,3,0};
	int tab2[3][3] = { 1,5,1}, {2,1,2}, {3,2,3};
	void mnozenieMacierzy(tab1[][], tab2[][], x, y);
}
void mnozenieMacierzy(int tab1[][], int tab2[][], int x, int y) {
	//JEŒLI DYNAMICZNE TO JAK POTEM USUN¥Æ Z PAMIÊCI J¥ W FUNKCJI?	
	//int** tab;
	//tab = new * int[x];
	//	for (int i = 0;i < x;i++) {
	//		tab[i] = new int[y];
	//	}
	int tab[x][y];
	for (int i = 0;i < x;i++) {
		for (int j = 0;j < y;j++) {
			for (int k = 0;k < x;k++) {
				tab[i][j] = +tab1[k][i] * tab2[j][k];
			}
		}
		
	}
	przepiszWynikDoTab1(tab1[][], tab[][], x, y);
}
void przepiszWynikDoTab1(int tab1[][], int tab[][], int x, int y) {
	for (int i = 0;i < x;i++) {
		for (int j = 0;j < y;j++) {
			tab1[i][j] = tab[i][j];
		}
	}
	wypiszWynik(tab1, x, y);
	}