/**
 * Copyright 2022 Gheorghiu Doru-Vlad (21gheorghi@gmail.com)
 * Facultatea de Automatica si Calculatoare, UPB
 * Year 1, Semester 2
 * Data Structures - Homework #2 - The Library of HashBabel
 * hashtable.h (header file for hashtable struct definition and functions)
 **/

#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#define HMAXINIT 7  // initial max size of buckets array

#include "linkedlist.h"

typedef struct infos {
    void *key;
    void *value;
} info;

// struct for the actual generic hashtable
typedef struct hashtables {
    linked_list **buckets;  // array of linked lists

    unsigned int hmax;  // max size of buckets array (HMAXINIT initially)
    unsigned int size;  // current occupied buckets (0 initially)

    unsigned int (*hash_function)(void*);  // pointer to a generic hash func

    int (*compare_function)(void*, void*);  // pointer to a generic compare func
} hashtable;

// function that returns a new hashtable
hashtable *ht_create(unsigned int hmax, unsigned int (*hash_function)(void*),
                     int (*compare_function)(void*, void*));

// function thats adds a key value pair to a hashtable
void ht_put(hashtable *ht, void *key, unsigned int key_size,
            void *value, unsigned int value_size, int mode);

// function that resizes a full hashtable
void ht_resize(hashtable *ht);

// function that removes a node from the hashtable
void ht_remove_entry(hashtable *ht, void *key);

// function that frees the memory of a hashtable
void ht_free(hashtable *ht);

// function that returns the value of a node in a hashtable
void *ht_get(hashtable *ht, void *key);

#endif  // HASHTABLE_H_
