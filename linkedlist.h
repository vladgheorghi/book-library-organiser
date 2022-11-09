/**
 * Copyright 2022 Gheorghiu Doru-Vlad (21gheorghi@gmail.com)
 * Facultatea de Automatica si Calculatoare, UPB
 * Year 1, Semester 2
 * Data Structures - Homework #2 - The Library of HashBabel
 * linkedlist_func.h (header file for linked list struct and functions)
 **/

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

// struct for a generic node
typedef struct nodes node;
struct nodes {
    void *data;  // node generic data

    node *next;  // pointer to the next node
};

// struct for a generic linked list
typedef struct linked_lists {
    node *head;  // pointer to the head of the list

    unsigned int size;  // linked list length (number of nodes)

    unsigned int data_size;  // memory size for the data (for memory allocation)
} linked_list;

// function that returns a new linked list
linked_list *ll_create(unsigned int data_size);

// function for adding a node inside a linked list
void add_node(linked_list* list, unsigned int n, const void* new_data);

// function that deletes a node from a list and returns it
node *remove_node(linked_list* list, unsigned int n);

// function that frees a given list
void ll_free(linked_list** pp_list);

// function that adds given node at the end of the list (node -> next != NULL)
void link_node(linked_list *list, node *node_link);

// function for swapping two given nodes (!!! the pointers will also swap)
void swap_nodes(linked_list *list, node *prevX, node *currX,
                node *prevY, node *currY);

// function that returns the nth node from a list
node *get_node(linked_list *list, unsigned int n);

#endif  // LINKEDLIST_H_

