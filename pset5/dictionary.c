/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdio.h>
#include <ctype.h>
#include <strings.h>

#include "dictionary.h"

// our hashtable.
hashtable* dict;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    node* head = dict->bucket_arr[hash(word)];
    while (head != NULL)
    {
        if (strcasecmp(word, head->word) == 0)
            return true;
        head = head->next;
    }
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // open input file 
    FILE* inptr = fopen(dictionary, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return 1;
    }
    
    // allocatate memory for dictionary
    dict = malloc(sizeof(hashtable));
    // define index in the hashtable and word to be read
    int index;
    char word[LENGTH + 1];
    
    // go over entire file and read each line into word var until you won't get eof
    while (fscanf(inptr, "%s", word) == 1)
    {
        // create new node and copy word that we have read from a file
        node* new_node = malloc(sizeof(node));
        strcpy(new_node->word, word);
        
        // get linked list from hashtable for a given index from hash function
        index = hash(word);
        node* head = dict->bucket_arr[index];

        // sorting linked list didn't give fast total performance, so we just
        // insert new node as a head to existing list. That way load is fast and
        // with relativly big table (number of buckets) and relativly intermidiate
        // size of a dictinary, check() still performs resonably fast
        if (head != NULL) 
            new_node->next = head;
        // update table with new head.
        dict->bucket_arr[index] = new_node;
        // increment size of a dictionary
        dict->size++;
    }
    
    fclose(inptr);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return dict->size;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        // go through each bucket (linked list) in the table
        node* cursor = dict->bucket_arr[i];
        while (cursor != NULL)
        {
            // free memory one by one node. preserve reference
            // no the next node with tmp var.
            node* tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    // free memory allocated for hashtable itself
    free(dict);
    return true;
}

/**
 * Hash function to get an index of the bucket based on word value
 */
unsigned int hash(const char* word)
{
    // based on TA notes, it is advised to use this hash function.
    // my first own implementation was similar.
    unsigned long hash = 5381;
    int c;
    
    // apply hashing function to each letter and sum it. 
    // NB: Hashing ignores case.
    while ((c = *word++))
        hash = ((hash << 5) + hash) + tolower(c); /* hash * 33 + c */
    // adjust size to a size of the table.
    return (unsigned int) (hash % HASHTABLE_SIZE);
}