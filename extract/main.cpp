#include "extract.h"

int main(){
    char stringa[80];
    cin >> stringa;
    int i = 0;
    int stop = 80;
    int id = 0;
    char * n_str = estrai(stringa, i, stop, id);
    cout << n_str << endl;
    delete[] n_str;
    return 0;
}