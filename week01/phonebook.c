#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct user_t {
    char name[50];
    char phoneNumber[20];
} user;

int compareFunction(const void *a, const void *b);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Syntax: ./phonebook filename\n");
        return 1;
    }
    FILE *fp;
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Can not open file %s\n", argv[1]);
        return 1;
    }
    int i = 0;
    char buff[200];
    user* data = (user *)malloc(sizeof(user));
    while(!feof(fp)) {
        data = (user *)realloc(data, (i + 1) * sizeof(user));
        
        fgets(buff, sizeof(buff), fp);
        buff[strcspn(buff, "\n")] = 0;
        strcpy(data[i].name, buff);

        fgets(buff, sizeof(buff), fp);
        buff[strcspn(buff, "\n")] = 0;
        strcpy(data[i].phoneNumber, buff);
        i++;
    }

    qsort(data, i, sizeof(user), compareFunction);

    int j;
    for (j = 0; j < i; j++) {
        printf("%s %s\n", data[j].name, data[j].phoneNumber);
    }

    free(data);
    fclose(fp);
    return 0;
}

int compareFunction(const void *a, const void *b) {
    const char *ia = (const char *)a;
    const char *ib = (const char *)b;
    return strcmp(ia, ib);
}