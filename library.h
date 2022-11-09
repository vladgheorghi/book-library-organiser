/**
 * Copyright 2022 Gheorghiu Doru-Vlad (21gheorghi@gmail.com)
 * Facultatea de Automatica si Calculatoare, UPB
 * Year 1, Semester 2
 * Data Structures - Homework #2 - The Library of HashBabel
 * library.h (main header file)
 **/

#ifndef LIBRARY_H_
#define LIBRARY_H_

#define MAXINPUTLEN 100  // max input line length
#define MAXPARAM 5  // max number of parameters

// enum for each command (used in switch case)
typedef enum commands {
    ADD_BOOK,
    GET_BOOK,
    RMV_BOOK,
    ADD_DEF,
    GET_DEF,
    RMV_DEF,
    ADD_USER,
    BORROW,
    RETURN,
    LOST,
    EXIT,
    INVALID,
    EMPTY
} command;

// function for breaking input lines into parameters (returns a command)
command assign_command(char *input, char **param);

// function for storing each parameter
void assign_param(char *input, unsigned int *n, char **param);

#endif  // LIBRARY_H_
