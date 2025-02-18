// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <windows.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
#define N 10001

// Hash table
node *table[N];

unsigned int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    char word_copy[strlen(word)];
    for (int i = 0; i < (strlen(word)); i++)
    {
        word_copy[i] = tolower(word[i]);
    }
    word_copy[strlen(word)] = '\0';
    int hashed = hash(word_copy);
    node *cursor = table[hashed];
    while (cursor != NULL)
    {
        if (strcmp(cursor->word, word_copy) == 0)
            return true;

        else
            cursor = cursor->next;

    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    unsigned int hash = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        hash = (word[i] << 2) ^ word[i];
    }

    return hash % N;
}


// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];
    while (fscanf(dict, "%s", word)  != EOF)
    {
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            unload();
            return false;
        }

        strcpy(new_node->word, word);
        node *head = table[hash(word)];
        if (head == NULL)
        {
            table[hash(word)] = new_node;
            word_count++;
        }

        else
        {
            new_node->next = table[hash(word)];
            table[hash(word)] = new_node;
            word_count++;
        }
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *head = table[i];
        node *cursor = head;
        // freeing linked lists
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}