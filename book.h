/**
 * Copyright 2022 Gheorghiu Doru-Vlad (21gheorghi@gmail.com)
 * Facultatea de Automatica si Calculatoare, UPB
 * Year 1, Semester 2
 * Data Structures - Homework #2 - The Library of HashBabel
 * book.h (header file for book operations)
 **/

#ifndef BOOK_H_
#define BOOK_H_

#define MAXBOOKNAMELEN 41
#define MAXDEFLINE 45

#include "hashtable.h"
#include "misc.h"

typedef struct book {
    char name[MAXBOOKNAMELEN];
    int borrowed;
    int rating;
    int borrow_count;
    hashtable *defs;
} book;

// function for adding a book in the library
void add_book(hashtable *ht, char *name, int def_number);

// function that returns book details by its key
void get_book(hashtable *library, void *book_key);

// function that removes a book from the library hashtable
void remove_book(hashtable *library, void *book_key);

#endif  // BOOK_H_
