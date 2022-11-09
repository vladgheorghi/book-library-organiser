/**
 * Copyright 2022 Gheorghiu Doru-Vlad (21gheorghi@gmail.com)
 * Facultatea de Automatica si Calculatoare, UPB
 * Year 1, Semester 2
 * Data Structures - Homework #2 - The Library of HashBabel
 * definition.h (header file for definition operations)
 **/

#ifndef DEFINITION_H_
#define DEFINITION_H_

#define MAXDEFLEN 21

// function that adds a definition inside a book
void add_def(hashtable *library, void *book_key, void *def_key, void *def_val);

// prints information about a given key definition
void get_def(hashtable *library, void *book_key, void *def_key);

// function that removes a definition from a book
void remove_def(hashtable *library, void *book_key, void *def_key);

#endif  // DEFINITION_H_
