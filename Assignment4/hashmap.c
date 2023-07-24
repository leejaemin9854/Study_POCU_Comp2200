#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"
#include "hashmap.h"


int is_prime(int num)
{
	if (num < 2) {
		return 0;
	}

	for (int i = 2; i <= num / 2; i++) {
		if (num % i == 0) {
			return 0;
		}

	}

	return 1;
}

int get_upper_prime_num(const int standard)
{
	int prime = standard;

	while (!is_prime(prime++));

	return --prime;
}

int get_hash_key(const char* key, unsigned int length)
{
	if (key == NULL) {
		return -1;
	}

	int value = 0;
	while (*key != '\0') {
		value += *key++;
	}

	return value % length;
}

hash_index_t get_hash_position(const hashmap_t* hashmap, const char* key)
{
	hash_index_t position;
	position.pos[0] = -1;
	position.pos[1] = 0;

	int index = get_hash_key(key, hashmap->length);
	if (hashmap->plist[index] == NULL) {
		return position;
	}

	position.pos[0] = index;

	node_t* node = hashmap->plist[index];
	while (strcmp(node->key, key) != 0) {
		
		node = node->next;
		position.pos[1]++;
		
		if (node == NULL) {
			position.pos[1] *= -1;
			break;
		}
	}


	return position;
}


hashmap_t* init_hashmap_malloc(size_t length, unsigned int (*p_hash_func)(const char* key))
{
	hashmap_t* new_hashmap = malloc(sizeof(hashmap_t));

	new_hashmap->hash_func = p_hash_func;
	new_hashmap->plist = calloc(length, sizeof(node_t*));

	new_hashmap->length = length;

	return new_hashmap;
}


int add_key(hashmap_t* hashmap, const char* key, const int value)
{
	int index = get_hash_key(key, hashmap->length);
	hash_index_t position = get_hash_position(hashmap, key);

	if (!(position.pos[0] < 0 || position.pos[1] < 0)) {
		return FALSE;
	}
	
	node_t* new_node = calloc(1, sizeof(node_t));
	
	new_node->key = calloc(strlen(key) + 1, sizeof(char));
	strncpy(new_node->key, key, strlen(key));
	new_node->key[strlen(key)] = '\0';
	new_node->value = value;
	new_node->next = NULL;


	if (position.pos[1] == 0) {
		hashmap->plist[index] = new_node;
	}
	else {
		node_t* node = hashmap->plist[index];
		while (node->next != NULL) {
			node = node->next;
		}

		node->next = new_node;
	}
	
	return TRUE;
}



int get_value(const hashmap_t* hashmap, const char* key)
{
	hash_index_t position = get_hash_position(hashmap, key);
	
	if (position.pos[0] < 0 || position.pos[1] < 0) {
		return -1;
	}

	node_t* node = hashmap->plist[position.pos[0]];
	for (int i = 0; i < position.pos[1]; i++) {
		node = node->next;

	}

	return node->value;

}



int update_value(hashmap_t* hashmap, const char* key, int value)
{
	hash_index_t position = get_hash_position(hashmap, key);

	if (position.pos[0] < 0 || position.pos[1] < 0) {
		return FALSE;
	}

	node_t* node = hashmap->plist[position.pos[0]];
	for (int i = 0; i < position.pos[1]; i++) {
		node = node->next;
	}

	node->value = value;

	return TRUE;
}

int remove_key(hashmap_t* hashmap, const char* key)
{
	hash_index_t position = get_hash_position(hashmap, key);

	if (position.pos[0] < 0 || position.pos[1] < 0) {
		return FALSE;
	}

	node_t* delete_node = NULL;
	if (position.pos[1] == 0) {
		delete_node = hashmap->plist[position.pos[0]];
		hashmap->plist[position.pos[0]] = hashmap->plist[position.pos[0]]->next;

	}
	else {
		node_t* node = hashmap->plist[position.pos[0]];
		for (int i = 0; i < position.pos[1] - 1; i++) {
			node = node->next;
		}

		delete_node = node->next;

		node->next = delete_node->next;
	}

	free(delete_node->key);
	free(delete_node);


	return TRUE;
}

void destroy(hashmap_t* hashmap)
{

	for (int i = 0; i < hashmap->length; i++) {

		node_t* node = hashmap->plist[i];
		if (node != NULL) {
			
			while (hashmap->plist[i] != NULL) {
				hashmap->plist[i] = hashmap->plist[i]->next;
				free(node->key);
				free(node);
				node = hashmap->plist[i];
			}

		}

	}
	free(hashmap->plist);
	free(hashmap);
}

