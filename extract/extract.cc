#include "extract.h"

char * estrai(char * stringa, int i, int stop, int id){
    char * n_str = new (nothrow) char[stop];
    if(n_str == NULL){
        cout << "Error in allocating new string" << endl;
        return NULL;
    }
    
    return estrai_ricorsiva(stringa, n_str, i, stop, id);
}

char * estrai_ricorsiva(char * stringa, char * n_str, int i, int stop, int id){
    if (i == stop || stringa[i] == '\0'){
        n_str[id] = '\0';
        return n_str;
    }
    if (stringa[i] >= 'A' && stringa[i] <= 'Z'){
            n_str[id] = stringa[i];
            id += 1;
    }
    return estrai_ricorsiva(stringa, n_str, ++i, stop, id);
}