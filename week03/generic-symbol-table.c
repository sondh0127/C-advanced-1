#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "generic-symbol-table.h"

int main() {
    SymbolTable phoneBook = createSymbolTable(makePhone, comparePhone);
    long number = 971971085;
    addEntry("Nguyen Dinh Tuan", &number, &phoneBook);
    number = 971971086;
    addEntry("Nguyen Dinh Tuan", &number, &phoneBook);
    number = 91723594;
    addEntry("Nguyen Tien Dat", &number, &phoneBook);
    number = 917246674;
    addEntry("Ngo Duy Anh Tuan", &number, &phoneBook);
    int i;
    for (i = 0; i < phoneBook.total; i++) {
        printf("%s, %ld\n", (char *)phoneBook.entries[i].key, *(long *)phoneBook.entries[i].value);
    }

    return 0;
}