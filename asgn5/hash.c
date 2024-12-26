#include "hash.h"

#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

typedef struct HashEntry {
    char *key;
    int val;
    struct HashEntry *next;
} HashEntry;

struct Hashtable {
    HashEntry *table[TABLE_SIZE];
};

size_t hash_function(const char *key) {
    size_t hash = 0;
    size_t len = strlen(key);

    for (size_t i = 0; i < len; i++) {
        hash = hash * 31u + (unsigned char) key[i];
    }

    return hash % TABLE_SIZE;
}

Hashtable *hash_create(void) {
    Hashtable *ht = (Hashtable *) malloc(sizeof(Hashtable));

    if (ht) {
        memset(ht->table, 0, sizeof(ht->table));
    }

    return ht;
}

bool hash_put(Hashtable *ht, char *key, int val) {
    size_t index = hash_function(key);
    HashEntry *new_entry = (HashEntry *) malloc(sizeof(HashEntry));

    if (!new_entry) {
        return false;
    }

    new_entry->key = strdup(key);
    new_entry->val = val;
    new_entry->next = ht->table[index];
    ht->table[index] = new_entry;

    return true;
}

int *hash_get(Hashtable *ht, char *key) {
    size_t index = hash_function(key);
    HashEntry *entry = ht->table[index];

    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            return &(entry->val);
        }
        entry = entry->next;
    }

    return NULL;
}

void hash_destroy(Hashtable **ht) {
    if (*ht) {
        for (size_t i = 0; i < TABLE_SIZE; i++) {
            HashEntry *entry = (*ht)->table[i];
            while (entry) {
                HashEntry *temp = entry;
                entry = entry->next;
                free(temp->key);
                free(temp);
            }
        }

        free(*ht);
        *ht = NULL;
    }
}
