#include "extract.h"

char * estrai(char * stringa){
    char * n_str = new (nothrow) char[80];
    if(n_str == NULL){
        cout << "Error in allocating new string" << endl;
        return NULL;
    }

    int id = 0;
    for(int i = 0; i < 80; i += 1){
        if (stringa[i] >= 'A' && stringa[i] <= 'Z')
        {
            n_str[id] = stringa[i];
            id += 1;
        }
    }
    return n_str;
}