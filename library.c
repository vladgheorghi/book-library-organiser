/**
 * Copyright 2022 Gheorghiu Doru-Vlad (21gheorghi@gmail.com)
 * Facultatea de Automatica si Calculatoare, UPB
 * Year 1, Semester 2
 * Data Structures - Homework #2 - The Library of HashBabel
 * library.c (main source file)
 **/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hashtable.h"
#include "library.h"
#include "misc.h"
#include "book.h"
#include "exit.h"
#include "user.h"
#include "definition.h"

int main(void)
{
    // the library hashtable
    hashtable *library = ht_create(HMAXINIT, hash_str, compare_str);

    // the user hashtable
    hashtable *user_list = ht_create(HMAXINIT, hash_str, compare_str);

    // macro for commands
    command comm = EMPTY;

    // reads each input line here
    char *input = malloc(MAXINPUTLEN * sizeof(char)), *p;
    if (!input) {
        fprintf(stderr, "Malloc failed: input.\n");
        exit(-1);
    }

    // each parameter of the input line is stored here
    char **param = malloc(MAXPARAM * sizeof(char *));
    if (!param) {
        fprintf(stderr, "Malloc failed: param.\n");
        exit(-1);
    }

    for (int i = 0; i < MAXPARAM; i++) {
        param[i] = malloc(MAXBOOKNAMELEN * sizeof(char));
        if (!param[i]) {
            fprintf(stderr, "Malloc failed: param[i].\n");
            exit(-1);
        }
    }

    while (comm != EXIT) {
        fgets(input, MAXINPUTLEN, stdin);  // reads input line
        p = strchr(input, '\n');
        if (p)
            *p = '\0';
        comm = assign_command(input, param);  // breaks input into parameters
        switch (comm) {
            case ADD_BOOK:
                add_book(library, param[1], atoi(param[2]));
                break;
            case GET_BOOK:
                get_book(library, param[1]);
                break;
            case RMV_BOOK:
                remove_book(library, param[1]);
                break;
            case ADD_DEF:
                add_def(library, param[1], param[2], param[3]);
                break;
            case GET_DEF:
                get_def(library, param[1], param[2]);
                break;
            case RMV_DEF:
                remove_def(library, param[1], param[2]);
                break;
            case ADD_USER:
                add_user(user_list, param[1]);
                break;
            case BORROW:
                borrow_book(user_list, library, param[1],
                            param[2], atoi(param[3]));
                break;
            case RETURN:
                return_book(user_list, library, param[1], param[2],
                            atoi(param[3]), atoi(param[4]));
                break;
            case LOST:
                lost_book(user_list, library, param[1], param[2]);
                break;
            case EXIT:
                exit_library(library, user_list, param, input);
                break;
            case INVALID:
                printf("Invalid command.\n");
                break;
            case EMPTY:
                break;
        }
    }
    return 0;
}

// function for breaking input lines into parameters
command assign_command(char *input, char **param)
{
    unsigned int n = 0;

    // breaks input into parameters
    assign_param(input, &n, param);

    // returns a command used in the switch case clause
    if (strcmp(param[0], "ADD_BOOK") == 0) {
        if (n == 3)
            return ADD_BOOK;
    } else if (strcmp(param[0], "GET_BOOK") == 0) {
        if (n == 2)
            return GET_BOOK;
    } else if (strcmp(param[0], "RMV_BOOK") == 0) {
        if (n == 2)
            return RMV_BOOK;
    } else if (strcmp(param[0], "ADD_DEF") == 0) {
        if (n == 4)
            return ADD_DEF;
    } else if (strcmp(param[0], "GET_DEF") == 0) {
        if (n == 3)
            return GET_DEF;
    } else if (strcmp(param[0], "RMV_DEF") == 0) {
        if (n == 3)
            return RMV_DEF;
    } else if (strcmp(param[0], "ADD_USER") == 0) {
        if (n == 2)
            return ADD_USER;
    } else if (strcmp(param[0], "BORROW") == 0) {
        if (n == 4)
            return BORROW;
    } else if (strcmp(param[0], "RETURN") == 0) {
        if (n == 5)
            return RETURN;
    } else if (strcmp(param[0], "LOST") == 0) {
        if (n == 3)
            return LOST;
    } else if (strcmp(param[0], "EXIT") == 0) {
        if (n == 1)
            return EXIT;
    }
    return INVALID;
}

// function for storing each parameter
void assign_param(char *input, unsigned int *n, char **param)
{
    int nr = 0, ok = 0, len = strlen(input);

    for (int i = 0; i < len; i++) {
        if (input[i] == ' ' && ok == 0) {
            nr++;
        } else if (input[i] == '"' && ok == 0) {
            ok = 1;
        } else if (input[i] == '"' && ok == 1) {
            ok = 0;
        }
    }

    nr++;

    if (nr > MAXPARAM)
        return;

    char *tok = strtok(input, " ");

    // storing each word into 'param' indexes accordingly
    while (tok) {
        if (tok[0] == '\"' && tok[strlen(tok) - 1] == '\"') {
            memcpy(param[(*n)++], tok, (strlen(tok) + 1) * sizeof(char));
        } else if (strchr(tok, '\"') && ok == 0) {
            ok = 1;
            memcpy(param[(*n)], tok, (strlen(tok) + 1) * sizeof(char));
        } else if (strchr(tok, '\"') && ok == 1) {
            memcpy(param[(*n)] + strlen(param[(*n)]), " \0", 2 * sizeof(char));
            memcpy(param[(*n)] + strlen(param[(*n)]), tok,
                   (strlen(tok) + 1) * sizeof(char));
            (*n)++;
            ok = 0;
        } else if (!strchr(tok, '\"') && ok == 1) {
            memcpy(param[(*n)] + strlen(param[(*n)]), " \0", 2 * sizeof(char));
            memcpy(param[(*n)] + strlen(param[(*n)]), tok,
                   (strlen(tok) + 1) * sizeof(char));
        } else if (!strchr(tok, '\"') && ok == 0) {
            memcpy(param[(*n)++], tok, (strlen(tok) + 1) * sizeof(char));
        }

        tok = strtok(NULL, " ");
    }

    // deletes the " "
    for (unsigned int i = 0; i < (*n); i++)
        if (param[i][0] == '\"') {
            memmove(param[i], param[i] + 1, strlen(param[i]) * sizeof(char));
            memmove(param[i] + strlen(param[i]) - 1,
                    param[i] + strlen(param[i]), sizeof(char));
        }
}
