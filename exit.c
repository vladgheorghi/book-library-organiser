/**
 * Copyright 2022 Gheorghiu Doru-Vlad (21gheorghi@gmail.com)
 * Facultatea de Automatica si Calculatoare, UPB
 * Year 1, Semester 2
 * Data Structures - Homework #2 - The Library of HashBabel
 * exit.c (source file for exiting the program and showing the rankings)
 **/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "library.h"
#include "hashtable.h"
#include "exit.h"
#include "book.h"
#include "user.h"

// function that sorts the top books and prints them
void book_rankings(linked_list *books)
{
    node *parc1 = books -> head, *prev1 = NULL;

    printf("Books ranking:\n");

    if (!parc1) {
        free(books);
        return;
    }

    node *parc2 = NULL, *prev2 = NULL;

    node *temp;

    book *book1, *book2;

    double rating1, rating2;

    // sorts the books accordingly
    for (unsigned int i = 0; i < books -> size - 1; i++) {
        prev2 = parc1;
        parc2 = parc1 -> next;
        for (unsigned int j = i + 1; j < books -> size; j++) {
            book1 = ((book *)((info *)parc1 -> data) -> value);
            book2 = ((book *)((info *)parc2 -> data) -> value);

            if (book1 -> borrow_count)
                rating1 = (double)book1 -> rating / book1 -> borrow_count;
            else
                rating1 = book1 -> rating;

            if (book2 -> borrow_count)
                rating2 = (double)book2 -> rating / book2 -> borrow_count;
            else
                rating2 = book2 -> rating;

            if (rating2 > rating1) {
                swap_nodes(books, prev1, parc1, prev2, parc2);
                temp = parc1;
                parc1 = parc2;
                parc2 = temp;
            } else if (rating2 == rating1) {
                if (book2 -> borrow_count > book1 -> borrow_count) {
                    swap_nodes(books, prev1, parc1, prev2, parc2);
                    temp = parc1;
                    parc1 = parc2;
                    parc2 = temp;
                } else if (book2 -> borrow_count == book1 -> borrow_count) {
                    if (strcmp(book1 -> name, book2 -> name) > 0) {
                        swap_nodes(books, prev1, parc1, prev2, parc2);
                        temp = parc1;
                        parc1 = parc2;
                        parc2 = temp;
                    }
                }
            }
            prev2 = parc2;
            parc2 = parc2 -> next;
        }
        prev1 = parc1;
        parc1 = parc1 -> next;
    }

    // prints the top books
    parc1 = books -> head;
    for (unsigned int i = 0; i < books -> size; i++) {
        printf("%d. ", i + 1);
        book1 = ((book *)((info *)parc1 -> data) -> value);

        printf("Name:%s ", book1 -> name);

        if (book1 -> borrow_count)
            rating1 = (double)book1 -> rating / book1 -> borrow_count;
        else
            rating1 = book1 -> rating;
        printf("Rating:%.3f ", rating1);

        printf("Purchases:%d\n", book1 -> borrow_count);

        parc1 = parc1 -> next;
    }

    // frees the book list and its books
    node *delete;
    parc1 = books -> head;
    while (parc1) {
        delete = parc1;
        parc1 = parc1 -> next;
        ht_free(((book *)((info *)delete -> data) -> value) -> defs);
        free(((info *)delete -> data) -> value);
        free(((info *)delete -> data) -> key);
        free(delete -> data);
        free(delete);
    }
    free(books);
}

// function that sorts the top users and prints them
void user_rankings(linked_list *users)
{
    node *parc1 = users -> head, *prev1 = NULL;

    printf("Users ranking:\n");

    if (!parc1) {
        free(users);
        return;
    }

    node *parc2 = NULL, *prev2 = NULL;

    node *temp;

    user *user1, *user2;

    // sorts the users accordingly
    for (unsigned int i = 0; i < users -> size - 1; i++) {
        prev2 = parc1;
        parc2 = parc1 -> next;
        for (unsigned int j = i + 1; j < users -> size; j++) {
            user1 = ((user *)((info *)parc1 -> data) -> value);
            user2 = ((user *)((info *)parc2 -> data) -> value);

            if (user1 -> ban == 1 && user2 -> ban == 0) {
                swap_nodes(users, prev1, parc1, prev2, parc2);
                temp = parc1;
                parc1 = parc2;
                parc2 = temp;
            } else if (user1 -> ban == 0 && user2 -> ban == 0) {
                if (user1 -> score < user2 -> score) {
                    swap_nodes(users, prev1, parc1, prev2, parc2);
                    temp = parc1;
                    parc1 = parc2;
                    parc2 = temp;
                } else if (user1 -> score == user2 -> score) {
                    if (strcmp(user1 -> name, user2 -> name) > 0) {
                        swap_nodes(users, prev1, parc1, prev2, parc2);
                        temp = parc1;
                        parc1 = parc2;
                        parc2 = temp;
                    }
                }
            }
            prev2 = parc2;
            parc2 = parc2 -> next;
        }
        prev1 = parc1;
        parc1 = parc1 -> next;
    }

    // prints the top users
    parc1 = users -> head;
    for (unsigned int i = 0; i < users -> size; i++) {
        user1 = ((user *)((info *)parc1 -> data) -> value);
        if (user1 -> ban == 0) {
            printf("%d. ", i + 1);

            printf("Name:%s ", user1 -> name);

            printf("Points:%d\n", user1 -> score);
        }

        parc1 = parc1 -> next;
    }

    // frees the user list and its users
    node *delete;

    parc1 = users -> head;
    while (parc1) {
        delete = parc1;
        parc1 = parc1 -> next;
        free(((info *)delete -> data) -> value);
        free(((info *)delete -> data) -> key);
        free(delete -> data);
        free(delete);
    }
    free(users);
}

// function that frees all allocated data and prints the top books and users
void exit_library(hashtable *library, hashtable *user_list,
                  char **param, char *input)
{
    free(input);

    for (int i = 0; i < MAXPARAM; i++)
        free(param[i]);
    free(param);

    // a single list where all books will be concatenated to it so they can
    // be sorted accordingly
    linked_list *books = ll_create(sizeof(info));

    node *book_node;

    // removes each book from the library hashtable and concatenates
    // to the book list
    for (unsigned int i = 0; i < library -> hmax; i++) {
        while (library -> buckets[i] -> head) {
            book_node = remove_node(library -> buckets[i], 0);

            link_node(books, book_node);
        }
        free(library -> buckets[i]);
    }

    // adds a NULL at the end of the list after all elements were added
    if (books -> head) {
        node *parc = books -> head;
        for (unsigned int i = 0; i < books -> size - 1; i++)
            parc = parc -> next;
        parc -> next = NULL;
    }

    // frees the library hashtable
    free(library -> buckets);
    free(library);

    // list where all users from the hashtable will be concatenated
    // so they can be sorted accordingly
    linked_list *users = ll_create(sizeof(info));

    node *user_node;

    // removes each node from the user hashtable and concatenates
    // it to the user list
    for (unsigned int i = 0; i < user_list -> hmax; i++) {
        while (user_list -> buckets[i] -> head) {
            user_node = remove_node(user_list -> buckets[i], 0);

            link_node(users, user_node);
        }
        free(user_list -> buckets[i]);
    }

    // adds NULL at the end of the user list
    if (users -> head) {
        node *parc = users -> head;
        for (unsigned int i = 0; i < users -> size - 1; i++)
            parc = parc -> next;
        parc -> next = NULL;
    }

    // frees the user hashtable
    free(user_list -> buckets);
    free(user_list);

    // makes the book and user rankings
    book_rankings(books);
    user_rankings(users);
}
