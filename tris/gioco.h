#ifndef GIOCO_H
#define GIOCO_H
#include <iostream>
#include <ctime>
using namespace std;

const int DIM = 3;

void inizializzaMatrice(char [DIM][DIM]);
void stampaMatrice(const char [DIM][DIM]);
bool gioca(char [DIM][DIM], bool, char, char);
bool controllaVincita(const char [DIM][DIM], char, bool &);
void iniziaGioco();

#endif