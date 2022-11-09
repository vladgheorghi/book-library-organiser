/**
 * Copyright 2022 Gheorghiu Doru-Vlad (21gheorghi@gmail.com)
 * Facultatea de Automatica si Calculatoare, UPB
 * Year 1, Semester 2
 * Data Structures - Homework #2 - The Library of HashBabel
 * misc.h (header file for miscellaneous function declarations)
 **/

#ifndef MISC_H_
#define MISC_H_

// function for comparing two integers
int compare_int(void *a, void *b);

// function for comparing two strings
int compare_str(void *a, void *b);

// function for hashing an integer
unsigned int hash_int(void *a);

// function for hashing a string
unsigned int hash_str(void *a);

#endif  // MISC_H_

