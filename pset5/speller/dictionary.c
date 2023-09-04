// Implements a dictionary's functionality

#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dictionary.h"
#include <ctype.h>

// Number of buckets in hash table
const unsigned int N = 27;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 2];
    struct node *next[N];
}
node;

//Address of the root for each tree (first array)
node *root[N] = {NULL};

//Function prototype
unsigned int aton(const char c);

//Global variable
unsigned int wordcount = 0;

// Returns true if word is in dictionary else false CHECK
bool check(const char *word)
{

    //Hash the 1st letter of words from the text and check if it's in the root
    int valtext = aton(word[0]);

    if (root[valtext] == NULL)
    {

        return false;

    }

    //Check the other letters in the word
    else
    {

        //Trav is the traversal
        node *trav = root[valtext];

        for (int vt = 1; vt < strlen(word); vt++)
        {

            if (trav->next[aton(word[vt])] == NULL)
            {

                return false;

            }

            else
            {

                trav = trav->next[aton(word[vt])];

            }

        }

        if (strcasecmp(word, trav->word) == 0)
        {

            return true;

        }


    }

    return false;

}

// Hashes word to a number HASH
unsigned int hash(const char *word)
{
    //Convert letters into a value for the 1st letter (address of each word)
    return aton(word[0]);
}

// Aton converts alphabet character to a number
unsigned int aton(const char c)
{
    //Convert letters into a value for the 1st letter (address of each word)
    if (islower(c))
    {
        return (unsigned int)(c - 97);
    }

    else if (isupper(c))
    {
        return (unsigned int)(c - 65);
    }

    else if (c == '\'')
    {
        return (unsigned int) 26;
    }

    else
    {
        // printf("Error: character not recognised in aton(...)!\n");
        return (unsigned int) 888;
    }

}

// Loads dictionary into memory, returning true if successful else false LOAD
bool load(const char *dictionary)
{
    //Declare current word
    char curword[LENGTH + 2];

    //Open dictionary file
    FILE *dictionarybuffer = fopen(dictionary, "r");
    if (dictionarybuffer == NULL)
    {
        return false;
    }

    //Read strings from file, one at the time
    while (fgets(curword, LENGTH + 2, dictionarybuffer) != NULL)
    {

        //Count each word as it gets in the trie
        wordcount++;

        //Declare the 1st letter in the root
        unsigned int index = hash(curword);

        //Declare the length of the current word, without \n that fgets reads
        int length = strlen(curword) - 1;

        //Replace \n with \0
        curword[length] = '\0';

        //Check if 1st letter in the root. If not, allocate memory
        if (root[index] == NULL)
        {

            root[index] = malloc(sizeof(node));
            if (root[index] == NULL)
            {
                printf("malloc failed to allocate for root[index]!\n");
                return false;
            }

            //Initialize *root[index]
            strcpy(root[index]->word, "");
            for (int i = 0; i < N; i++)
            {
                root[index]->next[i] = NULL;
            }

        }

        //Trav is the traversal
        node *trav = root[index];

        //Insert node into hash table at that location
        for (int letter = 1; letter < length; letter++)
        {
            //Declare indexaton
            unsigned int indexaton = aton(curword[letter]);

            //If no child, allocate memory
            if (trav->next[indexaton] == NULL)
            {
                trav->next[indexaton] = malloc(sizeof(node));
                if (trav->next[indexaton] == NULL)
                {
                    printf("malloc failed to allocate for trav->next[indexaton]!\n");
                    return false;
                }
                strcpy(trav->next[indexaton]->word, "");
                for (int i = 0; i < N; i++)
                {
                    trav->next[indexaton]->next[i] = NULL;
                }
            }

            trav = trav->next[indexaton];

        }

        //Copy the word in the word field at the end of the trie branch
        strcpy(trav->word, curword);

    }

    fclose(dictionarybuffer);

    return true;

}

// Returns number of words in dictionary if loaded else 0 if not yet loaded SIZE
unsigned int size(void)
{

    return wordcount;

}

//Function checking the trie before emptying it FREETRIE
bool freetrie(node *cursor)
{

    //Going through each array
    for (int i = 0; i < N; i++)
    {

        //If the i-th element in "next" array is not NULL
        if (cursor -> next[i] != NULL)
        {

            //If allnull is false, go to the address
            freetrie(cursor -> next[i]);

        }

    }

    //Free the space and return true
    free(cursor);

    return true;

}


// Unloads dictionary from memory, returning true if successful else false UNLOAD
bool unload(void)
{

    //Go to root array
    for (int i = 0; i < N; i++)
    {
        //Check if root[i] is NULL
        if (root[i] == NULL)
        {
            continue;
        }

        //Call freetrie for each address inside the array
        else if (!freetrie(root[i]))
        {

            return false;

        }

    }

    return true;

}
