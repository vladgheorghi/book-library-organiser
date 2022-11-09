/**
 * Copyright 2022 Gheorghiu Doru-Vlad (21gheorghi@gmail.com)
 * Facultatea de Automatica si Calculatoare, UPB
 * Year 1, Semester 2
 * Data Structures - Homework #2 - The Library of HashBabel
 * user.h (header file for user operations)
 **/

#ifndef USER_H_
#define USER_H_

#include "book.h"

#define MAXUSERLEN 21  // max user name length
#define SCOREINIT 100  // initial user score

// struct for a user
typedef struct user {
    char name[MAXUSERLEN];
    int score;
    int return_days;
    int ban;
    int borrowed;
    char borrowed_book[MAXBOOKNAMELEN];
} user;

// function for adding a new user into the user hashtable
void add_user(hashtable *ht, char *name);

// function for borrowing a book from a library by a specific user
void borrow_book(hashtable *user_list, hashtable *library, void *name_key,
                 void *book_key, int return_days);

// function that returns a book to the library by a user
void return_book(hashtable *user_list, hashtable *library, void* name_key,
                 void *book_key, int days_since_borrow, int rating);

// function for declaring a book as lost by an user
void lost_book(hashtable *user_list, hashtable *library, void *user_key,
               void *book_key);

#endif  // USER_H_
