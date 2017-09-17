#include <string.h>

#define INITIAL_SIZE 1
#define INCREMENTAL_SIZE 1

typedef struct {
    char name[80];
    long number;
} PhoneEntry;

typedef struct {
    PhoneEntry * entries;
    int total;
    int size;
} PhoneBook;

PhoneBook createPhoneBook() {
    PhoneBook book;
    book.entries = (PhoneEntry *)malloc(INITIAL_SIZE * sizeof(PhoneEntry));
    book.total = 0;
    book.size = INITIAL_SIZE;
    return book;
}

void dropPhoneBook(PhoneBook * book) {
    free(book->entries);
    free(book);
}

void addPhoneNumber(char * name, long number, PhoneBook * book) {
    int i;
    int found = 0;
    for (i = 0; i < book->total; i++) {
        if (strcmp(name, book->entries[i].name) == 0) {
            book->entries[i].number = number;
            found = 1;
            break;
        }
    }

    if (found == 0) {
        if (book->total == book->size) {
            book->entries = (PhoneEntry *)realloc(book->entries, (book->size + INCREMENTAL_SIZE) * sizeof(PhoneEntry));
            book->size += INCREMENTAL_SIZE;
        }
        strcpy(book->entries[book->total].name, name);
        book->entries[book->total].number = number;
        book->total++;
    }
}

PhoneEntry * getPhoneNumber(char * name, PhoneBook * book) {
    int i;
    for (i = 0; i < book->total; i++) {
        if (strcmp(name, book->entries[i].name) == 0) {
            return &book->entries[i];
        }
    }
    return NULL;
}