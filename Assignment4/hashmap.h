#ifndef HASHMAP_H
#define HASHMAP_H

#include <stddef.h>
#include "node.h"

#define TRUE (1)
#define FALSE (0)

typedef struct hashmap {
    unsigned int (*hash_func)(const char* key);
    node_t** plist;
    size_t length;
} hashmap_t;

typedef struct hash_index {
    int pos[2];
    /*
    *If the position is not valid, pos[0] has a value of - 1, and if the connection does not exist in node*, it returns a number of negative values to the node* .
    */
} hash_index_t;

int get_hash_key(const char* key, unsigned int length);

hash_index_t get_hash_position(const hashmap_t* hashmap, const char* key);

hashmap_t* init_hashmap_malloc(size_t length, unsigned int (*p_hash_func)(const char* key));

int add_key(hashmap_t* hashmap, const char* key, const int value);

int get_value(const hashmap_t* hashmap, const char* key);

int update_value(hashmap_t* hashmap, const char* key, int value);

int remove_key(hashmap_t* hashmap, const char* key);

void destroy(hashmap_t* hashmap);

#endif /* HASHMAP_H */
