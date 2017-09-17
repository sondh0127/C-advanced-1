#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "phonebook.h"

int main() {
    PhoneBook book = createPhoneBook();
    addPhoneNumber("Nguyen Dinh Tuan", 971971085, &book);
    addPhoneNumber("Nguyen Tien Dat", 971971545, &book);
    addPhoneNumber("Ngo Duy Anh Tuan", 971971012, &book);
    addPhoneNumber("Cao Mai Linh", 9719710245, &book);

    int i;
    for (i = 0; i < book.total; i++) {
        printf("%s, %ld\n", book.entries[i].name, book.entries[i].number);
    }
    
    return 0;
}