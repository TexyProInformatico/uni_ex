#include "extract.h"

int main(){
    char stringa[80];
    cin >> stringa;
    char * n_str = estrai(stringa);
    cout << n_str << endl;
    delete[] n_str;
    return 0;
}