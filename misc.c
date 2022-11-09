/**
 * Copyright 2022 Gheorghiu Doru-Vlad (21gheorghi@gmail.com)
 * Facultatea de Automatica si Calculatoare, UPB
 * Year 1, Semester 2
 * Data Structures - Homework #2 - The Library of HashBabel
 * misc.c (source file for miscellaneous function definitions)
 **/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "misc.h"

// function for comparing two integers
int compare_int(void *a, void *b)
{
    int a_int = *((int *)a);
    int b_int = *((int *)b);

    if (a_int == b_int) {
        return 0;

    } else if (a_int > b_int) {
        return 1;
    }

    return -1;
}

// function for comparing two strings
int compare_str(void *a, void *b)
{
    char *a_str = (char *)a;
    char *b_str = (char *)b;

    return strcmp(a_str, b_str);
}

// function for hashing an integer
unsigned int hash_int(void *a)
{
	/*
	 * Credits: https://stackoverflow.com/a/12996028/7883884
	 */
	unsigned int uint_a = *((unsigned int *)a);

	uint_a = ((uint_a >> 16u) ^ uint_a) * 0x45d9f3b;
	uint_a = ((uint_a >> 16u) ^ uint_a) * 0x45d9f3b;
	uint_a = (uint_a >> 16u) ^ uint_a;
	return uint_a;
}

// function for hashing a string
unsigned int hash_str(void *a)
{
	/*
	 * Credits: http://www.cse.yorku.ca/~oz/hash.html
	 */
	unsigned char *puchar_a = (unsigned char*) a;
	unsigned int hash = 5381;
	int c;

	while ((c = *puchar_a++))
		hash = ((hash << 5u) + hash) + c; /* hash * 33 + c */

	return hash;
}
