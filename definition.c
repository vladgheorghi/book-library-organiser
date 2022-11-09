/**
 * Copyright 2022 Gheorghiu Doru-Vlad (21gheorghi@gmail.com)
 * Facultatea de Automatica si Calculatoare, UPB
 * Year 1, Semester 2
 * Data Structures - Homework #2 - The Library of HashBabel
 * definition.c (source file for definition operations)
 **/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hashtable.h"
#include "book.h"
#include "definition.h"

// function that adds a definition inside a book
void add_def(hashtable *library, void *book_key, void *def_key, void *def_val)
{
    // returns the given book if it exists
    book *curr_book = (book *)ht_get(library, book_key);

    if (!curr_book) {
        printf("The book is not in the library.\n");
        return;
    }

    // puts the definition inside the definition hashtable of the given book
    ht_put(curr_book -> defs, def_key, (strlen(def_key) + 1) * sizeof(char),
           def_val, (strlen(def_val) + 1) * sizeof(char), 0);

    // resizes if needed
    if (curr_book -> defs -> size > curr_book -> defs -> hmax)
        ht_resize(curr_book -> defs);
}

// prints information about a given key definition
void get_def(hashtable *library, void *book_key, void *def_key)
{
    // returns the given book if it exists
    book *curr_book = (book *)ht_get(library, book_key);

    if (!curr_book) {
        printf("The book is not in the library.\n");
        return;
    }

    // returns the pair of the definition key if it exists
    char *def_val = (char *)ht_get(curr_book -> defs, def_key);

    if (!def_val) {
        printf("The definition is not in the book.\n");
        return;
    }

    // prints the definition value
    printf("%s\n", def_val);
}

// function that removes a definition from a book
void remove_def(hashtable *library, void *book_key, void *def_key)
{
    // returns the given book if it exists
    book *curr_book = (book *)ht_get(library, book_key);

    if (!curr_book) {
        printf("The book is not in the library.\n");
        return;
    }

    if (ht_get(curr_book -> defs, def_key) == NULL) {
        printf("The definition is not in the book.\n");
        return;
    }

    // removes the definition from the definitions hashtable
    ht_remove_entry(curr_book -> defs, def_key);
}
