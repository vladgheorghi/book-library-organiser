/**
 * Copyright 2022 Gheorghiu Doru-Vlad (21gheorghi@gmail.com)
 * Facultatea de Automatica si Calculatoare, UPB
 * Year 1, Semester 2
 * Data Structures - Homework #2 - The Library of HashBabel
 * user.c (source file for user operations)
 **/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hashtable.h"
#include "user.h"
#include "book.h"

// function for adding a new user into the user hashtable
void add_user(hashtable *ht, char *name)
{
    // allocates memory for the new user
    user *new_user = malloc(sizeof(user));

    // adds initial values to each field
    memcpy(new_user -> name, name, (strlen(name) + 1) * sizeof(char));
    new_user -> score = SCOREINIT;
    new_user -> return_days = -1;
    new_user -> ban = 0;
    new_user -> borrowed = 0;
    memcpy(new_user -> borrowed_book, "\0", sizeof(char));

    // verifies if the user is already registeres
    user *verify = (user *)ht_get(ht, name);

    if (verify) {
        printf("User is already registered.\n");
        free(new_user);
        return;
    }

    // adds the new user into the user hashtable
    ht_put(ht, name, (strlen(name) + 1) * sizeof(char), new_user,
           sizeof(user), 1);

    // resizes if needed
    if (ht -> size > ht -> hmax)
        ht_resize(ht);
}

// function for borrowing a book from a library by a specific user
void borrow_book(hashtable *user_list, hashtable *library, void *name_key,
                 void *book_key, int return_days)
{
    // returns the borrower if it exists
    user *borrower = (user *)ht_get(user_list, name_key);

    if (!borrower) {
        printf("You are not registered yet.\n");
        return;
    }

    if (borrower -> ban == 1) {
        printf("You are banned from this library.\n");
        return;
    }

    if (borrower -> borrowed == 1) {
        printf("You have already borrowed a book.\n");
        return;
    }

    // returns the book if it exists
    book *borrowed_book = (book *)ht_get(library, book_key);

    if (!borrowed_book) {
        printf("The book is not in the library.\n");
        return;
    }

    if (borrowed_book -> borrowed == 1) {
        printf("The book is borrowed.\n");
        return;
    }

    // the user now borrowed a book
    borrower -> borrowed = 1;
    borrower -> return_days = return_days;

    // the book is now borrowed
    borrowed_book -> borrowed = 1;

    memcpy(borrower -> borrowed_book, book_key,
           (strlen(book_key) + 1) * sizeof(char));
}

// function that returns a book to the library by a user
void return_book(hashtable *user_list, hashtable *library, void* name_key,
                 void *book_key, int days_since_borrow, int rating)
{
    // returns the returner if it exists
    user *returner = (user *)ht_get(user_list, name_key);

    if (returner -> ban == 1) {
        printf("You are banned from this library.\n");
        return;
    }

    if (returner -> borrowed == 0) {
        printf("You didn't borrow this book.\n");
        return;
    }

    // returns the book if it exists
    book *returned_book = (book *)ht_get(library, book_key);

    if (library -> compare_function(returner -> borrowed_book, book_key)) {
        printf("You didn't borrow this book.\n");
        return;
    }

    // adds or subtracts score to the user by the day they returned the book
    if (returner -> return_days < days_since_borrow) {
        returner -> score -= (days_since_borrow - returner -> return_days) * 2;
        if (returner -> score < 0) {
            returner -> ban = 1;
            printf("The user %s has been banned from this library.\n",
                   ((char *)name_key));
        }
    } else {
        returner -> score += returner -> return_days - days_since_borrow;
    }

    // the returned now returned the book
    returner -> return_days = -1;
    returner -> borrowed = 0;

    // the book has now been returned
    returned_book -> rating += rating;
    returned_book -> borrow_count++;
    returned_book -> borrowed = 0;
}

// function for declaring a book as lost by an user
void lost_book(hashtable *user_list, hashtable *library, void *user_key,
               void *book_key)
{
    // returns the user if it exists
    user *curr_user = (user *)ht_get(user_list, user_key);

    if (!curr_user) {
        printf("You are not registered yet.\n");
        return;
    }

    if (curr_user -> ban == 1) {
        printf("You are banned from this library.\n");
        return;
    }

    // subtracts 50 points from the user for losing the book
    curr_user -> score -= 50;
    curr_user -> borrowed = 0;
    memcpy(curr_user -> borrowed_book, "\0", sizeof(char));
    curr_user -> return_days = -1;

    // if the user's score is below 0 he is banned
    if (curr_user -> score < 0) {
        curr_user -> ban = 1;
        printf("The user %s has been banned from this library.\n",
               curr_user -> name);
    }

    // removes the book from the library hashtable
    remove_book(library, book_key);
}
