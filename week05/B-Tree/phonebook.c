#include <stdio.h>
#include <stdlib.h>
#include "bt/inc/btree.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Syntax: ./phonebook filename\n");
        return 1;
    }
    BTA *btfile;
    btinit();

    // Open bt file
    btfile = btopn(argv[1], 0, FALSE);
    if (btfile == NULL) {
        // If the file doesn't exist, create a new one
        btfile = btcrt(argv[1], 0, FALSE);
        printf("Can not find file %s, creating a new one.\n", argv[1]);
    }

    int menu = 0;
    char name[50];
    char number[20];
    int val;
    while (menu != -1) {
        printf("\t--Phonebook application using B-Tree--\n");
        printf("1. Print all entries\n");
        printf("2. Add/modify an entry\n");
        printf("3. Delete an entry\n");
        printf("4. Save and exit\n");
        printf("Selection: ");
        scanf("%d", &menu);
        switch(menu) {
            case 1:
                // First position in the bt tree
                btpos(btfile, ZSTART);
                while(bnxtky(btfile, name, &val) == 0) {
                    printf("%s\t\t%d\n", name, val);
                }
                break;
            case 2:
                printf("Name: ");
                while(getchar()!='\n');
                scanf("%[^\n]", name);
                printf("Number: ");
                scanf("%s", number);
                if (bfndky(btfile, name, &val) == 0) {
                    bupdky(btfile, name, atoi(number));
                    printf("Modified entry %s\n", name);
                } else {
                    binsky(btfile, name, atoi(number));
                    printf("Added entry %s\n", name);
                }
                break;
            case 3:
                printf("Name: ");
                while(getchar()!='\n');
                scanf("%[^\n]", name);
                if (bfndky(btfile, name, &val) == 0) {
                    bdelky(btfile, name);
                    printf("Deleted entry %s\n", name);
                } else {
                    printf("Entry %s does not exists.\n", name);
                }
                break;
            case 4:
                menu = -1;
                // Close bt file
                btcls(btfile);
                break;
            default:
                menu = 0;
                printf("Invalid selection.\n");
                break;
        }
    }

    return 0;
}