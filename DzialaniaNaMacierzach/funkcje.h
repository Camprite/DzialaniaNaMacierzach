#include <iostream>
#include <string>
#ifndef FUNKCJE_H
#define FUNKCJE_H
using namespace std;

int enterMartixNumber();
int startMenu();
void operationMenu(int***, int**, int*);
void enterMartixNumberFromKeyboard(int***, int**, int*);
void enterMartixNumberFromRandom(int***, int**, int*);
void enterMartixNumberFromFile(string,int***,int**,int*);
bool walidacjaPliku(string);

 
#endif
 