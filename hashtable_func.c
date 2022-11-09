/**
 * Copyright 2022 Gheorghiu Doru-Vlad (21gheorghi@gmail.com)
 * Facultatea de Automatica si Calculatoare, UPB
 * Year 1, Semester 2
 * Data Structures - Homework #2 - The Library of HashBabel
 * hashtable_func.c (source file for hashtable functions)
 **/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hashtable.h"
#include "linkedlist.h"

// function that returns a new hashtable
hashtable *ht_create(unsigned int hmax, unsigned int (*hash_function)(void*),
                     int (*compare_function)(void*, void*))
{
    hashtable *new_ht = malloc(sizeof(hashtable));
    if (!new_ht) {
        fprintf(stderr, "Malloc failed: new_ht.\n");
        exit(-1);
    }

    new_ht -> hmax = hmax;
    new_ht -> size = 0;
    new_ht -> hash_function = hash_function;
    new_ht -> compare_function = compare_function;

    new_ht -> buckets = malloc(new_ht -> hmax * sizeof(linked_list *));
    if (!new_ht -> buckets) {
        fprintf(stderr, "Malloc failed: new_ht -> buckets.\n");
        exit(-1);
    }

    for (unsigned int i = 0; i < new_ht -> hmax; i++)
        new_ht -> buckets[i] = ll_create(sizeof(info));

    return new_ht;
}

// function thats adds a key value pair to a hashtable
void ht_put(hashtable *ht, void *key, unsigned int key_size,
            void *value, unsigned int value_size, int mode)
{
	unsigned int index = ht -> hash_function(key) % ht -> hmax;

    node *parc = ht -> buckets[index] -> head;
    node *node_t = NULL;

    while (parc) {
        if (ht -> compare_function(((info *)parc -> data) -> key, key) == 0) {
            node_t = parc;
            break;
        }

        parc = parc -> next;
    }

    if (!parc) {
        info entry;

        entry.key = malloc(key_size);
        memcpy(entry.key, key, key_size);

        if (mode == 0) {
            entry.value = malloc(value_size);
            memcpy(entry.value, value, value_size);
        } else {
            entry.value = value;
        }

        add_node(ht -> buckets[index], 0, &entry);

    } else {
        if (mode == 0) {
            info *entry_p = ((info *)node_t -> data);
            entry_p -> value = realloc(entry_p -> value, value_size);

            memcpy(entry_p -> value, value, value_size);
        } else {
            ((info *)node_t -> data) -> value = value;
        }
    }

    ht -> size++;
}

// function that resizes a full hashtable
void ht_resize(hashtable *ht)
{
    // in this method, im concatenating all hashtable nodes to a newly created
    // list, then im resizing the hashtable and then I assign a new hashed
    // index to each node of the hashtable and then I'm freeing the list
    linked_list *conc_buckets = ll_create(sizeof(info));
    node *prev = NULL;

    // concatenating each hashtable node to the list
    for (unsigned int i = 0; i < ht -> hmax; i++) {
        node *parc = ht -> buckets[i] -> head;
        while (parc) {
            if (!conc_buckets -> head) {
                conc_buckets -> head = parc;
                conc_buckets -> size++;
            } else if (conc_buckets -> size == 1) {
                prev = conc_buckets -> head;
                prev -> next = parc;
                conc_buckets -> size++;
            } else {
                prev = prev -> next;
                prev -> next = parc;
                conc_buckets -> size++;
            }
            parc = parc -> next;
        }
        ht -> buckets[i] -> head = NULL;
        ht -> buckets[i] -> size = 0;
    }

    // adds NULL at the end of the list
    prev = conc_buckets -> head;
    for (unsigned int i = 0; i < conc_buckets -> size - 1; i++)
        prev = prev -> next;
    prev -> next = NULL;

    // resizing the hashtable
    unsigned int new_hmax = ht -> hmax * 2;

    ht -> buckets = realloc(ht -> buckets, new_hmax * sizeof(linked_list *));
    for (unsigned int i = ht -> hmax; i < new_hmax; i++)
        ht -> buckets[i] = ll_create(sizeof(info));

    ht -> hmax = new_hmax;

    // adding back the elements with new assigned index
    prev = conc_buckets -> head;
    unsigned int ind;
    node *parc2 = NULL;
    while (prev) {
        ind = ht -> hash_function(((info *)prev -> data) -> key) % ht -> hmax;
        if (!ht -> buckets[ind] -> head) {
            ht -> buckets[ind] -> head = prev;
            ht -> buckets[ind] -> size++;
        } else {
            parc2 = ht -> buckets[ind] -> head;
            for (unsigned int i = 0; i < ht -> buckets[ind] -> size - 1; i++)
                parc2 = parc2 -> next;
            parc2 -> next = prev;
            ht -> buckets[ind] -> size++;
        }
        prev = prev -> next;
    }

    // free the list
    conc_buckets -> head = NULL;
    free(conc_buckets);

    // adds NULL at the end of every hashtable list
    int n;
    for (unsigned int i = 0; i < ht -> hmax; i++) {
        parc2 = ht -> buckets[i] -> head;

        n = ht -> buckets[i] -> size;
        for (int j = 0; j < n - 1; j++) {
            parc2 = parc2 -> next;
        }
        if (parc2)
            parc2 -> next = NULL;
    }
}

// function that removes a node from the hashtable
void ht_remove_entry(hashtable *ht, void *key)
{
	unsigned int index = ht -> hash_function(key) % ht -> hmax;

    node *parc = ht -> buckets[index] -> head;

    node *delete;

    for (unsigned int i = 0; i < ht -> buckets[index] -> size; i++) {
        if (ht -> compare_function(((info *)(parc -> data)) -> key, key) == 0) {
            delete = remove_node(ht -> buckets[index], i);
            free(((info *)(delete -> data)) -> key);
            free(((info *)(delete -> data)) -> value);
            free(delete -> data);
            free(delete);
            ht -> size--;
            break;
        }

        parc = parc -> next;
    }
}

// function that frees the memory of a hashtable
void ht_free(hashtable *ht)
{
    for (unsigned int i = 0; i < ht -> hmax; i++) {
        while (ht -> buckets[i] -> head) {
            info *entry = ht -> buckets[i] -> head -> data;
            ht_remove_entry(ht, entry -> key);
        }

        ll_free(&(ht -> buckets[i]));
    }

    free(ht -> buckets);
    free(ht);
}

// function that returns the value of a node in a hashtable
void *ht_get(hashtable *ht, void *key)
{
	unsigned int index = ht -> hash_function(key) % ht -> hmax;

    node *parc = ht -> buckets[index] -> head;

    while (parc) {
        info *entry = (info *)(parc -> data);

        if (ht -> compare_function(entry -> key, key) == 0)
            return entry -> value;

        parc = parc -> next;
    }

	return NULL;
}
