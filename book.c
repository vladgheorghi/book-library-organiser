/**
 * Copyright 2022 Gheorghiu Doru-Vlad (21gheorghi@gmail.com)
 * Facultatea de Automatica si Calculatoare, UPB
 * Year 1, Semester 2
 * Data Structures - Homework #2 - The Library of HashBabel
 * book.c (source file for book operations)
 **/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "library.h"
#include "hashtable.h"
#include "misc.h"
#include "definition.h"
#include "book.h"

// function for adding a book in the library
void add_book(hashtable *ht, char *name, int def_number)
{
    // allocates memory for the book
    book *new_book = malloc(sizeof(book));

    // assign initial values for each field
    memcpy(new_book -> name, name, (strlen(name) + 1) * sizeof(char));
    new_book -> borrowed = 0;
    new_book -> rating = 0;
    new_book -> borrow_count = 0;

    // creates a hashtable for the definitions
    new_book -> defs = ht_create(HMAXINIT, hash_str, compare_str);

    // each pair of definitions will be read as a whole line
    char *input = malloc(MAXDEFLINE * sizeof(char));

    // each pair of definitions will be stored here
    char def_key[MAXDEFLEN], def_val[MAXDEFLEN];

    char *tok, *p;

    for (int i = 0; i < def_number; i++) {
        fgets(input, MAXINPUTLEN, stdin);

        tok = strtok(input, " ");
        p = strchr(tok, '\n');
        if (p)
            *p = '\0';

        memcpy(def_key, tok, (strlen(tok) + 1) * sizeof(char));

        tok = strtok(NULL, " ");
        p = strchr(tok, '\n');
        if (p)
            *p = '\0';

        memcpy(def_val, tok, (strlen(tok) + 1) * sizeof(char));

        // adds the definition into the definitions hashtable
        ht_put(new_book -> defs, def_key, (strlen(def_key) + 1) * sizeof(char),
               def_val, (strlen(def_val) + 1) * sizeof(char), 0);

        // resizes the hashtable if needed
        if (new_book -> defs -> size > new_book -> defs -> hmax)
            ht_resize(new_book -> defs);
    }

    free(input);

    // verifies if the book already exists and if does, it deletes it
    book *verify = (book *)ht_get(ht, name);

    if (verify) {
        unsigned int index = ht -> hash_function(name) % ht -> hmax;

        node *parc = ht -> buckets[index] -> head;

        node *delete;

        for (unsigned int i = 0; i < ht -> buckets[index] -> size; i++) {
            info *entry = ((info *)parc -> data);

            if (ht -> compare_function(entry -> key, name) == 0) {
                delete = remove_node(ht -> buckets[index], i);

                ht_free(verify -> defs);
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

    // adds the book into the library hashtable
    ht_put(ht, name, (strlen(name) + 1) * sizeof(char), new_book,
           sizeof(book), 1);

    // resizes if needed
    if (ht -> size > ht -> hmax)
        ht_resize(ht);
}

// function that returns book details by its key
void get_book(hashtable *library, void *book_key)
{
    book *curr_book = (book *)ht_get(library, book_key);

    if (!curr_book) {
        printf("The book is not in the library.\n");
        return;
    }

    printf("Name:%s ", curr_book -> name);
    if (curr_book -> borrow_count) {
        double rat = (double)curr_book -> rating / curr_book -> borrow_count;
        printf("Rating:%.3f ", rat);
    } else {
        printf("Rating:%.3f ", (double)curr_book -> rating);
    }
    printf("Purchases:%d\n", curr_book -> borrow_count);
}

// function that removes a book from the library hashtable
void remove_book(hashtable *library, void *book_key)
{
    unsigned int index = library -> hash_function(book_key) % library -> hmax;
    node *book_node = library -> buckets[index] -> head;
    int n = 0;

    while (book_node) {
        info *entry = ((info *)book_node -> data);

        if (library -> compare_function(book_key, entry -> key) == 0) {
            book_node = remove_node(library -> buckets[index], n);
            ht_free(((book *)entry -> value) -> defs);
            free(entry -> value);
            free(entry -> key);
            free(book_node -> data);
            free(book_node);
            return;
        }

        n++;
        book_node = book_node -> next;
    }

    printf("The book is not in the library.\n");
}
