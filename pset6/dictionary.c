/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"


int wordcount = 0;
node* root;

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary) 
{    
    /*open dictionary*/
    FILE* dictionaryptr = fopen(dictionary, "r");
    if(dictionaryptr == NULL)
    {   
        return false;
    }
    
    /*reserve some space for the first node, used calloc since i'm sure that the values inside the box are set to NULL
    otherwist with malloc you dont know whats initially inthere. It is important you can be sure that it's set to NULL for the
    rest of the code to function properly*/
    root = calloc(sizeof(node), 1); 
    node* currentNode;
    currentNode = root;//set currentNode to root only 1 time in the beginning.
    
    //every character in the dictionary is converted to a number until the end of file is reached. When converted it is checked
    //if the number == NULL (Which in the beginning al 27 children are definitely NULL due to calloc). A new node needs to be created
    //and the currentNode needs to update. If there is already a node for that number only currentNode is uploaded.
    //if '\n' is found isWord returns true. Everytime a new word is loaded it will increment wordcount + 1;
    for (int c = fgetc(dictionaryptr); c != EOF; c = fgetc(dictionaryptr))
    {
        int number = convert(c);
        
        
        if(c != '\n')
        {
            if(currentNode -> children[number] == NULL)
            {
                currentNode -> children[number] = calloc(sizeof(node), 1);
                currentNode = currentNode -> children[number];
            }
            else 
            {
                currentNode = currentNode -> children[number];
            }   
        }        
        else
        {
            currentNode -> isWord = true;
            wordcount = wordcount + 1; 
            currentNode = root;           
        }
     
    }   
    fclose(dictionaryptr);    
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return wordcount;
}


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    node* currentNode = root;
    /* with every word this function starts again. therefore the root node is set to current Node only at the beginning of the function
    while currentNode != NULL (suggesting that at least root node is not equal to NULL (which is very safe to assume). Starting with 
    index = 0, which is the first letter, convert it to a character. If \0 is found it returns isWord (either true or false).
    Otherwise the character is converted to a number through a function written by me. currentNode is that updated and index is incremented.
    
    */
    int index;
    int character;
    int number;
    
    index = 0;
    
    while(currentNode != NULL)
    {
        character = word[index];
        if(character == '\0')
        {
            return currentNode -> isWord;
        }
        number = convert(character);
        
        currentNode = currentNode -> children[number];

        index ++;
    }
    return false;
}
/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
 // unload calls another function called unloadNote and gives with the argument root
bool unload(void)
{   
    unloadNode(root);
    return true;
}

//wrote a recursive function to unload (free) all of the children if not NULL and then free the node.
void unloadNode(node* currentNode)
{
    for(int i = 0; i < 27; i ++)
    {
        if(currentNode -> children[i] != NULL)
        {
            unloadNode(currentNode -> children[i]);
        }
    }
    
    free(currentNode);
}

int convert(int c)
{
    if(c >= 65 && c < 91)
    {
        c = c + 32;
        c = c - 97;
        return c;
    }   
    else if(c >= 97 && c < 123)
    {
        c = c - 97;
        return c;
    }
    else if(c == 39)
    {
        c = c - 13;
        return c;
    }
    else
    {
        return -1;
    }
}
