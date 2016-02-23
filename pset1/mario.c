#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height = 0;
    // constants for drawing pyramid
    char space = ' ';
    char block = '#';
    
    // get height. Repeat input if less than 0 or more than 23
    do {
        printf("Height: ");
        height = GetInt();
    } while (height < 0 || height > 23); 
 
    // print half-pyramid
    for (int i = 1; i <= height; i++) {
        // I think we could have done better here if we could construct
        // a string wiht a given size and init it with a given character.
        for (int j = height; i<j; j--) {
          printf("%c", space);  
        }
        for (int j = 0; j <= i; j++) {
          printf("%c", block);  
        }
        printf("\n");
    }
}