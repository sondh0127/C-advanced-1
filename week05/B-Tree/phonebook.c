#include <stdio.h>
#include "bt/inc/btree.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Syntax: ./phonebook filename\n");
        return 1;
    }
    BTA *btfile;
    btinit();

    char name[50] = "Nguyen Dinh Tuan";
    long number = 123123123;

    // Open bt file
    btfile = btopn(argv[1], 0, FALSE);
    if (btfile == NULL) {
        // If the file doesn't exist, create a new one
        btfile = btcrt(argv[1], 0, FALSE);
        printf("Can not find file %s, creating a new one.\n", argv[1]);
        // binsky(btfile, name, number);
    } else {
        //print
        binsky(btfile, name, number);
    }

    int val;
    // Return 0 if founded, non-zero if not founded
    printf("Found: %d\n", bfndky(btfile, name, &val));
    printf("%d\n", val);

    int menu = 0;
    while (menu != -1) {
        printf("\t--Phonebook application using B-Tree--\n");
        printf("1. Print all entries\n");
        printf("2. Add/modify an entry\n");
        printf("3. Delete an entry\n");
        printf("4. Save to file\n");
        printf("5. Exit\n");
        printf("Selection: ");
        scanf("%d", &menu);
        switch(menu) {
            case 1:
                
                break;
            case 2:
                //add/modify
                break;
            case 3:
                //delete
                break;
            case 4:
                //write
                break;
            case 5:
                menu = -1;
                break;
            default:
                menu = 0;
                printf("Invalid selection.\n");
                break;
        }
    }
    // Close bt file
    btcls(btfile);

    return 0;
}