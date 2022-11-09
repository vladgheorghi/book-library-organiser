/**
 * Copyright 2022 Gheorghiu Doru-Vlad (21gheorghi@gmail.com)
 * Facultatea de Automatica si Calculatoare, UPB
 * Year 1, Semester 2
 * Data Structures - Homework #2 - The Library of HashBabel
 * linkedlist_func.c (source file for linked list function definitions)
 **/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "linkedlist.h"

// function that returns a new linked list
linked_list *ll_create(unsigned int data_size)
{
    // allocates memory
    linked_list *new_ll = malloc(sizeof(linked_list));
    if (!new_ll) {
        fprintf(stderr, "Malloc failed: new_ll.\n");
        exit(-1);
    }

    // assign initial data to the list
    new_ll -> size = 0;
    new_ll -> data_size = data_size;
    new_ll -> head = NULL;

    return new_ll;
}

// function for adding a node inside a linked list
void add_node(linked_list* list, unsigned int n, const void* new_data)
{
	node *parc = list -> head;

    // allocate memory for the node and for the data stored in it
    node *new_node = malloc(sizeof(node));
    new_node -> data = malloc(list -> data_size);
    memcpy(new_node -> data, new_data, list -> data_size);

    // if the list is empty
    if (parc == NULL || n == 0) {
        new_node -> next = list -> head;
        list -> head = new_node;
        list -> size++;
        return;
    }

    int ok = 1;
    for (unsigned int i = 0; i < n - 1 && ok == 1; i++) {
        if (parc -> next != NULL)
            parc = parc -> next;
        else
            ok = 0;
    }

    if (parc -> next == NULL) {
        parc -> next = new_node;
        new_node -> next = NULL;
    } else {
        new_node -> next = parc -> next;
        parc -> next = new_node;
    }

    list -> size++;
}

// function that deletes a node from a list and returns it
node *remove_node(linked_list* list, unsigned int n)
{
    node *prev, *curr;

    if (!list || !list->head) {
        return NULL;
    }

    // if given n is greater than size of the list it will delete the end node
    if (n > list->size - 1) {
        n = list->size - 1;
    }

    curr = list->head;
    prev = NULL;
    while (n > 0) {
        prev = curr;
        curr = curr->next;
        --n;
    }

    if (prev == NULL) {
        list->head = curr->next;
    } else {
        prev->next = curr->next;
    }

    list->size--;

    return curr;
}

// function that frees a given list
void ll_free(linked_list** pp_list)
{
    node *currNode;

    if (!pp_list || !*pp_list) {
        return;
    }

    // deletes each node
    while ((*pp_list) -> size > 0) {
        currNode = remove_node(*pp_list, 0);
        free(currNode->data);
        currNode->data = NULL;
        free(currNode);
        currNode = NULL;
    }

    // frees the list
    free(*pp_list);
    *pp_list = NULL;
}

// function that adds given node at the end of the list (node -> next != NULL)
void link_node(linked_list *list, node *node_link)
{
    if (!list -> head) {
        list -> head = node_link;
        list -> size++;
        return;
    }

    node *parc = list -> head;
    for (unsigned int i = 0; i < list -> size - 1; i++) {
        parc = parc -> next;
    }

    parc -> next = node_link;
    list -> size++;
}

// function for swapping two given nodes (!!! the pointers will also swap)
void swap_nodes(linked_list *list, node *prevX, node *currX,
                node *prevY, node *currY)
{
    // If either x or y is not present, nothing to do
    if (currX == NULL || currY == NULL)
        return;

    // If x is not head of linked list
    if (prevX != NULL)
        prevX -> next = currY;
    else  // Else make y as new head
        list -> head = currY;

    // If y is not head of linked list
    if (prevY != NULL)
        prevY -> next = currX;
    else  // Else make x as new head
        list -> head = currX;

    // Swap next pointers
    node *temp = currY->next;
    currY->next = currX->next;
    currX->next = temp;
}

// function that returns the nth node from a list
node *get_node(linked_list *list, unsigned int n)
{
    if (n >= list -> size)
        n = list -> size - 1;

    node *parc = list -> head;
    for (unsigned int i = 0; i < n; i++)
        parc = parc -> next;

    return parc;
}
