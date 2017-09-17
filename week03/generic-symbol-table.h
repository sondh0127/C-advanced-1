#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 1
#define INCREMENTAL_SIZE 1

typedef struct {
    void * key;
    void * value;
} Entry;

typedef struct {
    Entry * entries;
    int total;
    int size;
    Entry (*makeNode)(void *, void *);
    int (*compare)(void *, void *);
} SymbolTable;

SymbolTable createSymbolTable(Entry (*makeNode)(void *, void *), int (*compare)(void *, void *)) {
    SymbolTable s;
    s.entries = (Entry *)malloc(INITIAL_SIZE * sizeof(Entry));
    s.total = 0;
    s.size = INITIAL_SIZE;
    s.makeNode = makeNode;
    s.compare = compare;
    return s;
}

void dropSymbolTable(SymbolTable * s) {
    free(s->entries);
    s->total = 0;
    s->size = 0;
}

void addEntry(void * key, void * value, SymbolTable * s) {
    int i;
    int found = 0;
    for (i = 0; i < s->total; i++) {
        if (s->compare(key, s->entries[i].key) == 0) {
            s->entries[i] = s->makeNode(key, value);
            found = 1;
            break;
        }
    }

    if (found == 0) {
        if (s->total == s->size) {
            s->entries = (Entry *)realloc(s->entries, (s->size + INCREMENTAL_SIZE) * sizeof(Entry));
            s->size += INCREMENTAL_SIZE;
        }
        s->entries[s->total] = s->makeNode(key, value);
        s->total++;
    }
}

Entry * getEntry(void * key, SymbolTable s) {
    // int i;
    // for (i = 0; i < s->total; i++) {
    //     if (s->compare(key, s->entries[i].key) == 0) {
    //         return &s->entries[i];
    //     }
    // }
    return NULL;
}

Entry makePhone(void * name, void * phone) {
    Entry res;
    res.key = strdup((char *)name);
    res.value = malloc(sizeof(long));
    memcpy(res.value, phone, sizeof(long));
    return res;
}

int comparePhone(void * key1, void * key2) {
    return strcmp((char *)key1, (char *)key2);
}