#include "sportello.h"

int main(){
    int size = conta(file_name);
    if(size == -1){
        exit(1);
    }

    Abbonamento * array = genera_array(file_name, size);
    if(array == NULL){
        exit(1);
    }

    int index = 0;
    do{
        cout << "premi 0 emettere un nuovo abbonamento " << endl <<
                "premi 1 calcolare il guadagno totale " << endl <<
                "premi 2 calcolare il ricavo per tipologia di abbonamento " << endl <<
                "premi 3 per uscire" << endl;
        cin >> index;
        switch (index){
        case 0:
            {   
                static int max_s = size * 2;
                if(conta(file_name) == max_s - 1){
                    max_s *= 2;
                    Abbonamento * n_array = genera_array(file_name, max_s);
                    delete[] array;
                    array = n_array;
                }
                if(Inserisci(file_name, array, size)){
                    cout << "Inserimento completato" << endl;
                }
                break;
            }
        case 1:
            {
                double guadagno = Guadagno(array, size);
                cout << "Il guadagno è : " << guadagno << endl;
                break;
            }
        case 2:
            {
                int ar[4] = {};
                char max_ric = Elabora(array, size, ar);
                cout << "Il ricavo maggiore è quello del : " << max_ric << endl;
                break;
            }
        case 3:
            break;
        default:
            cout << "no bro metti un id valido" << endl;
            break;
        }

    } while(index != 3);


    delete[] array;
    return 0;
}