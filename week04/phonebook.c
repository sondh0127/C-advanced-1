#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Libfdr/jrb.h"

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

    JRB book = make_jrb();
    JRB node;
    char name[50];
    char number[20];
    int i = 0;
    char buff[200];

    while(!feof(fp)) {
        fgets(buff, sizeof(buff), fp);
        buff[strcspn(buff, "\n")] = 0;
        strcpy(name, buff);
        // printf("%s\n", name);

        fgets(buff, sizeof(buff), fp);
        buff[strcspn(buff, "\n")] = 0;
        strcpy(number, buff);
        // printf("%s\n", number);
        jrb_insert_str(book, strdup(name), 
        new_jval_l(atol(number)));
        i++;
    }

    jrb_traverse(node, book) {
        printf("%s\t\t%ld\n", jval_s(node->key), jval_l(node->val));
    }

    fclose(fp);

    return 0;
}