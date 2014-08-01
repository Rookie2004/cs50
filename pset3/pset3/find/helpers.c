/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 rewrite search in such a way that it uses linear search, returning true if value is
 in values and false if values is not in values. Take care to return false
 right away if n isnt even positive.
 */
 /*
 Linear search
 bool search(int value, int values[], int n)
{
    if(n < 0)
    {
        return false;
    }
    
    for(int i = 0; i < n; i++)
    {
        if(value == values[i])
        {
            return true;
        }
    }
    return false;
}
*/
       
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    int begin = 0;
    int end = n - 1;    

    while(end >= begin)
    {
        int middle = (end - begin) / 2 + begin;
        if(values[middle] == value)
        {
            return true;
        }
        else if(values[middle] < value)
        {
            begin = middle + 1;
        }
        else
        {
            end = middle - 1;
        }
        printf("-");
    }
    return false; 
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    for(int i = 1;i < n; i++)
    { 
        int element = values[i];
        int j = i;

        while(j > 0 && values[j - 1] > element)
        {
            values[j] = values[j - 1];
            j = j - 1;    
        }
        
        values[j] = element;
    }
    /*
    for(int i = 0; i < n; i++)
    {
        printf("%i\n", values[i]);
    }
    
    */

    return;
}
