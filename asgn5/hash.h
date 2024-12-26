#ifndef _HASH

#define _HASH

#include "ll.h"

#define MAX_BINS 100

typedef struct Hashtable Hashtable;

Hashtable *hash_create(void);

bool hash_put(Hashtable *, char *key, int val);

int *hash_get(Hashtable *, char *key);

void hash_destroy(Hashtable **);

#endif
