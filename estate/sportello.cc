#include "sportello.h"

const char * file_name = "Abbonamenti2026.txt";

int conta(const char * file_name){
    int size = 0;
    fstream input;
    input.open(file_name, ios::in);
    if(input.fail()){
        cout << "Error in opening file" << endl;
        return -1;
    }
    char c;
    input.get(c);
    while(!input.eof()){
        if(c == '\n'){
            size += 1;
        }
        input.get(c);
    }
    size += 1; //because it doesnt read the last line
    input.close();
    return size;
}

Abbonamento * genera_array(const char * file_name, int size){
    fstream input;
    
    input.open(file_name, ios::in);
    if (input.fail()){
        cout << "Error in opening file" << endl;
        return NULL;
    }
    
    Abbonamento * array = new (nothrow) Abbonamento[size * 2];
    if(array == NULL){
        cout << "Error in allocating array" << endl;
        input.close();
        return NULL;
    }
    
    for(int i = 0; i < size; i += 1){
        input >> array[i].numero
              >> array[i].nome
              >> array[i].cognome
              >> array[i].tipo
              >> array[i].costo;
    }

    input.close();
    return array;
}

bool Inserisci(const char * file_name, Abbonamento * array, int & size){
    int numero = size + 1;
    int id = size;
    char nome[32] = {};
    char cognome[32] = {};
    char tipo = 'a';
    int costo = 0;
    cout << "dammi nome, cognome, tipo (s x sett. m x mens. a x annu. g x giorn.)" << endl;
    cin >> nome >> cognome >> tipo;
    if (tipo == 's') costo = 50;
    else if (tipo == 'm') costo = 150;
    else if (tipo == 'a') costo = 500;
    else if (tipo == 'g') costo = 15;
    else{
        cout << "Error : wrong type" << endl; 
        return false;
    }

    fstream output;
    output.open(file_name, ios::app);
    if (output.fail()){
        cout << "Error in opening output file" << endl;
        return false;
    }

    array[id].numero = numero;
    strcpy(array[id].nome, nome);
    strcpy(array[id].cognome, cognome);
    array[id].tipo = tipo;
    array[id].costo = costo;

    output << '\n'
           << array[id].numero << ' '
           << array[id].nome << ' '
           << array[id].cognome << ' '
           << array[id].tipo << ' '
           << array[id].costo;

    size += 1;
    output.close();
    return true;
}

double Guadagno(Abbonamento * array, int size){
    double guadagno = 0.0;
    for(int i = 0; i < size; i += 1){
        guadagno += (array[i].costo * 0.9);
    }
    return guadagno;
}

char Elabora(Abbonamento * array, int size, int r[4]){
    for(int i = 0; i < 4; i += 1){
        r[i] = 0;
    }
    
    char max_ric = 'a';
    for(int i = 0; i < size; i += 1){
        switch (array[i].tipo){
            case 'a':
                r[0] += array[i].costo;
            break;
            case 'm':
                r[1] += array[i].costo;
            break;
            case 's':
                r[2] += array[i].costo;
            break;
            case 'g':
                r[3] += array[i].costo;
            break;
        }
    }

    int max_id = 0;
    int max_val = 0;
    for(int i = 0; i < 4; i += 1){
        if(r[i] > max_val){
            max_id = i;
            max_val = r[i];
        }
    }

    switch (max_id)
    {
    case '0':
        max_ric = 'a';
        break;
    case '1':
        max_ric = 'm';
        break;
    case '2':
        max_ric = 's';
        break;
    case '3':
        max_ric = 'g';
        break;
    }

    return max_ric;
}