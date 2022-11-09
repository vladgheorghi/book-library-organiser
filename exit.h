/**
 * Copyright 2022 Gheorghiu Doru-Vlad (21gheorghi@gmail.com)
 * Facultatea de Automatica si Calculatoare, UPB
 * Year 1, Semester 2
 * Data Structures - Homework #2 - The Library of HashBabel
 * exit.h (header file for exiting the program and showing the rankings)
 **/

#ifndef EXIT_H_
#define EXIT_H_

// function that sorts the top books and prints them
void book_rankings(linked_list *books);

// function that sorts the top users and prints them
void user_rankings(linked_list *users);

// function that frees all allocated data and prints the top books and users
void exit_library(hashtable *library, hashtable *user_list,
                  char **param, char *input);

#endif  // EXIT_H_
