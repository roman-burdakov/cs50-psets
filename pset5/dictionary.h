/**
 * dictionary.h
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Declares a dictionary's functionality.
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45
// const for hashtable default size. gives good performanc results
#define HASHTABLE_SIZE 65536

// node structure for linked list
typedef struct node
{
    char word[LENGTH+1];
    struct node* next;
} node;

// hashtable to store dictionary
typedef struct hashtable
{
    unsigned int size;
    node* bucket_arr[HASHTABLE_SIZE];
} hashtable;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word);

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

/**
 * Hash function to return an index of the bucket for a hashtable where
 * a linked list of values is stored
 */
unsigned int hash(const char* word);

#endif // DICTIONARY_H
