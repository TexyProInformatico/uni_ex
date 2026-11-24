#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

struct Studente{
    char nome[30];
    char cognome[30];
    int matricola;
    float media;
};

void stampa_studente(Studente *);
Studente * genera_studente(char[], char[], int, float);
Studente ** carica_database(char[], int, int);
int cerca_matricola(Studente **, int, int);
int cerca_nome_e_cognome(Studente **, char *, char *, int);
int studente_top_media(Studente **, int);
Studente ** add_student(Studente **, char[], char[], int, float, int);
void change_student(Studente **, char[], char[], int, float, int);
void save_students(Studente **, char[], int);


int main(int argc, char * argv[]){
    
    if(argc != 4){
        cout << "Usage : <.a.out> <inputxt> <n_row_of_file> <n_max_of_students>" << endl;
        exit(1);
    }
    char nome[30] = {};
    char cognome[30] = {};
    int matricola = 0;
    float media = 0;
    int n_righe = atoi(argv[2]);
    int max_n_studenti = atoi(argv[3]);
    int n_studenti = n_righe;
    if(n_righe > max_n_studenti){
        cout << "il file ha troppi studenti per questo misero database" << endl;
        return 0;
    }
    char file_name[100];
    strcpy(file_name, argv[1]);

    Studente ** database = carica_database(file_name, n_righe, max_n_studenti);
    if(database == NULL){
        return 0;
    }
    
    int index = 0;
    int id = 0;
    do{
        cout << "premi 0 per cercare uno studente dalla matricola, " << endl <<
                "premi 1 per cercare uno studente da nome e cognome " << endl <<
                "premi 2 per cercare lo studente con la miglior media " << endl <<
                "premi 3 per aggiungere un utente al sistema " << endl <<
                "premi 4 pre modificare un utente nel sistema" << endl <<
                "premi 5 per salvare gli studenti in un file esterno " << endl <<
                "premi 6 per uscire" << endl;
        cin >> index;

        switch (index){
        case 0:
            cout << "dammi la matricola che vuoi" << endl;
            cin >> matricola;
            cout << endl;
            id = cerca_matricola(database, matricola, n_studenti);
            break;
        case 1:
            cout << "dammi il nome e il cognome" << endl;
            cin >> nome >> cognome;
            cout << endl;
            id = cerca_nome_e_cognome(database, nome, cognome, n_studenti); 
            break;
        case 2:
            cout << endl;
            id = studente_top_media(database, n_studenti);
            break;
        case 3:
            {
                if(n_studenti == max_n_studenti){
                    cout << "database pieno" << endl;
                    break;
                }
                n_studenti += 1;
                cout << "dammi nome cognome matricola e media" << endl;
                cin >> nome >> cognome >> matricola >> media;
                cout << endl;
                Studente ** n_database = add_student(database, nome, cognome, matricola, media, n_studenti);
                if(n_database == NULL){
                    n_studenti -= 1;
                }
                else{
                    database = n_database;
                }
                break;
            }
        case 4:
            {
                cout << endl;
                int change_id = 0;
                cout << "immettere l'id dello studente da cambiare, se non si sà l'id dello studente lo si cerchi con gli appositi comandi, per tornare indietro immettere -1" << endl;
                cin >> change_id;
                if(change_id == -1){
                    break;
                }
                cout << "dammi nome cognome matricola e media nuovi" << endl;
                cin >> nome >> cognome >> matricola >> media;
                change_student(database, nome, cognome, matricola, media, change_id);
                break;
            }
        case 5:
            {
                char output[100];
                char file[100];
                cout << endl << "immetti il nome del file di output" << endl;
                cin >> file;
                cout << endl;
                strcpy(output, file);
                save_students(database, output, n_studenti);
                break;
            }
        case 6:
            break;
        default:
            cout << "no bro metti un id valido" << endl;
            break;
        }

        if(id == -1){
            cout << "non ho trovato lo studente" << endl;
        }
        else if(id != -1 && index >= 0 && index <= 2){
            cout << "l'id dello studente è : " << id << endl;
        }
    } while(index != 6);

    for(int i = 0; i < n_studenti; i += 1){
        delete database[i];
    }
    delete[] database;
    return 0;
}

Studente ** carica_database(char file_name[], int n_righe, int max_n_studenti){
    char nome[30] = {};
    char cognome[30] = {};
    int matricola = 0;
    float media = 0;
    
    fstream input;
    input.open(file_name, ios::in);
    if(input.fail()){
        cout << "Error in opening text" << endl;
        return NULL;
    }

    Studente **database = new (nothrow) Studente * [max_n_studenti];
    if(database == NULL){
        input.close();
        cout << "Error in allocating database" << endl;
        return NULL;
    }

    for(int i = 0; i < n_righe && i < max_n_studenti; i += 1){
        input >> nome >> cognome >> matricola >> media;
        Studente * studente = genera_studente(nome, cognome, matricola, media);
        if(studente == NULL){
            input.close();
            cout << "error in allocating student" << endl;
            return NULL;
        }
        database[i] = studente;
        stampa_studente(studente);
        cout << endl;
    }

    input.close();
    return database;
}

Studente * genera_studente(char nome[], char cognome[], int matricola, float media_ponderata){
    Studente * studente = new (nothrow) Studente;
    if(studente == NULL){
        cout << "Error in allocatin memorys" << endl;
        return NULL;
    }
    strcpy(studente->nome, nome);
    strcpy(studente->cognome, cognome);
    studente->matricola = matricola;
    studente->media = media_ponderata;

    return studente;
}

void stampa_studente(Studente * studente){
    cout << "name : " << studente->nome << endl 
         << "cognome : " << studente->cognome << endl 
         << "matricola : " << studente->matricola << endl 
         << "media : " << studente->media << endl;
}

int cerca_matricola(Studente ** database, int matricola, int len){
    int id = -1;
    for(int i = 0; i < len; i += 1){
        if(database[i]->matricola == matricola){
            id = i;
            stampa_studente(database[i]);
        }
    }
    return id;
}

int cerca_nome_e_cognome(Studente ** database, char * nome, char * cognome, int len){
    int id = -1;
    for(int i = 0; i < len; i += 1){
        if(!strcmp(database[i]->nome, nome) && !strcmp(database[i]->cognome, cognome)){
            id = i;
            stampa_studente(database[i]);
        }
    }
    return id;
}

int studente_top_media(Studente ** database, int len){
    int id = 0;
    for(int i = 1; i < len; i += 1){
        if(database[i]->media >= database[id]->media){
            id = i;
        }
    }
    stampa_studente(database[id]);
    return id;
}

Studente ** add_student(Studente ** database, char * nome, char * cognome, int matricola, float media, int n_studenti){
    Studente ** n_database = new (nothrow) Studente * [n_studenti];
    if(n_database == NULL){
        cout << "Error in allocating new database" << endl;
        return NULL;
    }

    for(int i = 0; i < n_studenti - 1; i += 1){
        n_database[i] = database[i];
    }
    n_database[n_studenti - 1] = genera_studente(nome, cognome, matricola, media);
    delete[] database;
    return n_database;
}

void change_student(Studente ** database, char * nome, char * cognome, int matricola, float media, int change_id){
    strcpy(database[change_id]->nome, nome);
    strcpy(database[change_id]->cognome, cognome);
    database[change_id]->matricola = matricola;
    database[change_id]->media = media;
}

void save_students(Studente ** database, char * filename, int n_studenti){
    fstream output;
    output.open(filename, ios::out);
    if(output.fail()){
        cout << "Error in generating output file" << endl;
        return;
    }

    for(int i = 0; i < n_studenti; i += 1){
        output << database[i]->nome << ' ' << database[i]->cognome << ' '
               << database[i]->matricola << ' ' << database[i]->media << endl;
    }

    output.close();
}