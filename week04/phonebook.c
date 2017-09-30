#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Libfdr/jrb.h"

int main() {
    FILE *fp;
    fp = fopen("phonebook.txt", "r");
    if (fp == NULL) {
        printf("Can not open file %s\n", "phonebook.txt");
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

        fgets(buff, sizeof(buff), fp);
        buff[strcspn(buff, "\n")] = 0;
        strcpy(number, buff);
        jrb_insert_str(book, strdup(name), new_jval_l(atol(number)));
        i++;
    }

    fclose(fp);

    // Menu
    int menu = 0;
    while (menu != -1) {
        printf("\t--Phonebook menu using JRB--\n");
        printf("1. Print current phonebook\n");
        printf("2. Add/modify an entry\n");
        printf("3. Delete an entry\n");
        printf("4. Save to file\n");
        printf("5. Exit\n");
        printf("Selection: ");
        scanf("%d", &menu);
        switch(menu) {
            case 1:
                jrb_traverse(node, book) {
                    printf("%s\t%ld\n", jval_s(node->key), jval_l(node->val));
                }
                break;
            case 2:
                printf("Name: ");
                while(getchar()!='\n');
                scanf("%[^\n]", name);
                printf("Number: ");
                while(getchar()!='\n');
                scanf("%s", number);

                node = jrb_find_str(book, name);
                if (node != NULL) {
                    // Entry already existed
                    jrb_delete_node(node);
                    printf("Modified entry %s\n", name);
                } else {
                    printf("Added new entry %s\n", name);
                }

                jrb_insert_str(book, strdup(name), new_jval_l(atol(number)));
                break;
            case 3:
                printf("Name: ");
                while(getchar()!='\n');
                scanf("%[^\n]", name);

                node = jrb_find_str(book, name);
                if (node != NULL) {
                    jrb_delete_node(node);
                    printf("Deleted entry %s\n", name);
                } else {
                    printf("Entry %s not found\n", name);
                }
                break;
            case 4:
                fp = fopen("phonebook.txt", "w");
                i = 1;
                jrb_traverse(node, book) {
                    if (i > 1) fprintf(fp, "\n");
                    fprintf(fp, "%s\n", jval_s(node->key));
                    fprintf(fp, "%ld", jval_l(node->val));
                    i++;
                    // This usage of fprintf instead of
                    // fprintf(fp, "%s\n", jval_s(node->key));
                    // fprintf(fp, "%ld\n", jval_l(node->val));
                    // ensure that there is no extra line at
                    // the end of the file
                }
                printf("Write to file completed\n");
                fclose(fp);
                break;
            case 5:
                menu = -1;
                break;
            default:
                menu = 0;
                printf("Invalid choice\n");
                break;
        }
    }

    node = jrb_find_str(book, "Nguyen Dinh Tuan");
    if (node != NULL) {
        jrb_delete_node(node);
        strcpy(name, "Nguyen Dinh Tuan");
        strcpy(number, "123123123");
        jrb_insert_str(book, strdup(name), new_jval_l(atol(number)));
    } else {
        printf("Not found\n");
    }

    jrb_free_tree(book);

    return 0;
}