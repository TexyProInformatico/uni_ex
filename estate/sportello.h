#ifndef SPORTELLO_H
#define SPORTELLO_H

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct Abbonamento
{
    int numero;
    char nome[32];
    char cognome[32];
    char tipo;
    int costo;
};

extern const char * file_name;

Abbonamento * genera_array(const char *, int);
bool Inserisci(const char *, Abbonamento *, int&);
int conta(const char *);
double Guadagno(Abbonamento *, int);
char Elabora(Abbonamento *, int, int[]);

#endif