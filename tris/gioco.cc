#include "gioco.h"

void inizializzaMatrice(char matrice[DIM][DIM]){
    for(int i = 0; i < DIM; i += 1){
        for(int j = 0; j < DIM; j += 1){
            matrice[i][j] = '*';
        }
    }
}

void stampaMatrice(const char matrice[DIM][DIM]){
    for(int i = 0; i < DIM; i += 1){
        for(int j = 0; j < DIM; j += 1){
            cout << matrice[i][j] << ' ';
        }
        cout << endl;
    }
}

bool gioca(char matrice[DIM][DIM], bool turnoUtente, char simboloUtente, char simboloComputer){
    if(turnoUtente){
        bool again = false;
        int index = 0;
        do{
            cout << "premi un numero da 1 a 9 su dove vuoi inserire il tuo simbolo (da 1 a 3 per la prima riga poi 4 a 6 e 7 a 9)" << endl;
            cin >> index;
            cout << endl;
            if(index < 1 && index > 9){
                cout << "numero invalido" << endl;
                again = true;
            }
            else if(index >= 1 && index <= 3){
                if(matrice[0][index - 1] != '*'){
                    cout << "nuh huh non puoi mettere un coso qui" << endl;
                    again = true;
                }
                else{
                    matrice[0][index - 1] = simboloUtente;
                    again = false;
                }
            }
            else if(index >= 4 && index <= 6){
                if(matrice[1][index - 4] != '*'){
                    cout << "nuh huh non puoi mettere un coso qui" << endl;
                    again = true;
                }
                else{
                    matrice[1][index - 4] = simboloUtente;
                    again = false;
                }
            }
            else{
                if(matrice[2][index - 7] != '*'){
                    cout << "nuh huh non puoi mettere un coso qui" << endl;
                    again = true;
                }
                else{
                    matrice[2][index - 7] = simboloUtente;
                    again = false;
                }
            }
        } while (again);
    }
    else{
        bool again = false;
        do{
            int index = rand() % 10;
            if(index >= 1 && index <= 3){
                if(matrice[0][index - 1] != '*'){
                    again = true;
                }
                else{
                    matrice[0][index - 1] = simboloComputer;
                    again = false;
                }
            }
            else if(index >= 4 && index <= 6){
                if(matrice[1][index - 4] != '*'){
                    again = true;
                }
                else{
                    matrice[1][index - 4] = simboloComputer;
                    again = false;
                }
            }
            else{
                if(matrice[2][index - 7] != '*'){
                    again = true;
                }
                else{
                    matrice[2][index - 7] = simboloComputer;
                    again = false;
                }
            }
        } while (again);
    }
    turnoUtente = !turnoUtente;
    return turnoUtente;
}

bool controllaVincita(const char matrice[DIM][DIM], char simbolo, bool &pareggio){
    bool vincita = false;
    for(int i = 0; i < DIM && vincita == false; i += 1){
        switch (i){
            case 0:
                if(matrice[i][i] == matrice[i][i + 1] && matrice[i][i] == matrice[i][i + 2] && matrice[i][i] != '*'){
                    vincita = true;
                    pareggio = false;
                }
                else if(matrice[i][i] == matrice[i + 1][i] && matrice[i][i] == matrice[i + 2][i] && matrice[i][i] != '*'){
                    vincita = true;
                    pareggio = false;
                }
                else if(matrice[i][i] == matrice[i + 1][i + 1] && matrice[i][i] == matrice[i + 2][i + 2] && matrice[i][i] != '*'){
                    vincita = true;
                    pareggio = false;
                }
                break;
            case 1:
                if(matrice[i][i] == matrice[i][i - 1] && matrice[i][i] == matrice[i][i + 1] && matrice[i][i] != '*'){
                    vincita = true;
                    pareggio = false;
                }
                else if(matrice[i][i] == matrice[i - 1][i] && matrice[i][i] == matrice[i + 1][i] && matrice[i][i] != '*'){
                    vincita = true;
                    pareggio = false;
                }
                else if(matrice[i][i] == matrice[i + 1][i - 1] && matrice[i][i] == matrice[i - 1][i + 1] && matrice[i][i] != '*'){
                    vincita = true;
                    pareggio = false;
                }
                break;
            case 2:
                if(matrice[i][i] == matrice[i][i - 1] && matrice[i][i] == matrice[i][i - 2] && matrice[i][i] != '*'){
                    vincita = true;
                    pareggio = false;
                }
                else if(matrice[i][i] == matrice[i - 1][i] && matrice[i][i] == matrice[i - 2][i] && matrice[i][i] != '*'){
                    vincita = true;
                    pareggio = false;
                }
                break;
        }
    }
    return vincita;
}

void iniziaGioco(){
    char matrice[DIM][DIM];
    bool turnoUtente = false;
    char simbolo = '0';
    char simboloUtente = '0';
    char simboloComputer = '0';
    bool pareggio = true;
    bool turno = false;
    bool vincita = false;
    inizializzaMatrice(matrice);
    stampaMatrice(matrice);
    cout << "premi 0 per iniziare con le croci, 1 per giocare con i cerchi e andare secondo" << endl;
    int index = 0;
    cin >> index;

    if(index == 0){
        turnoUtente = true;
        simboloUtente = 'X';
        simboloComputer = 'O';
    }
    else{
        turnoUtente = false;
        simboloUtente = 'O';
        simboloComputer = 'X';
    }

    for(int i = 1; i <= 9 || pareggio == true; i += 1){
        
        if(i % 2 != 0){
            simbolo = 'X';
        }
        else{
            simbolo = 'O';
        }

        turno = gioca(matrice, turnoUtente, simboloUtente, simboloComputer);
        turnoUtente = turno;
        
        stampaMatrice(matrice);
        cout << endl;
        vincita = controllaVincita(matrice, simbolo, pareggio);
        if(vincita && simbolo == 'X'){
            cout << "Vince P1" << endl;
            exit(1);
        }
        else if(vincita && simbolo == 'O'){
            cout << "Vince P2" << endl;
            exit(1);
        }

    }

    if(pareggio){
        cout << "avete pareggiato LMAO" << endl;
    }
} //da richiamare nel main