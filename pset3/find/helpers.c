/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if (n < 0) 
        return false;
    else 
    {
        // first path - requirement to use linear search
        // for (int i = 0; i < n; i++) 
        //     if (values[i] == value)
        //         return true;
        // second path - binary after sorting was implemented
        int low = 0;
        int high = n - 1;
        int m = (low + high) / 2; // midpoint
        if (low > high) 
            return false;
        // search in binary fashion
        while (low <= high) {
            if (values[m] == value)
                return true;
            if (values[m] < value) 
                low = m + 1;
            else
                high = m - 1;
            m = (low + high) / 2;
        }
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // sorting using insertion sort (O(n^2)) based on requirements
    int el, j = 0;
    if (n > 0)
        for (int i = 1; i < n; i++) {
            el = values[i];
            j = i-1;
            while (j >= 0 && values[j] > el)
            {
                values[j+1] = values[j];
                j = j - 1;
            }
            values[j+1] = el;
        }
    return;
}