#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // validate input parameters
    if (argc != 2 || !isalpha(argv[1][0])) {
        printf("Expected input with single word only!");
        return 1;
    }
    string key = argv[1];
    int key_length = strlen(key);
    int k = 0, shift = 0;
    for (int i = 0, n = key_length; i < n; i++) 
        if (isalpha(key[i]) == false) 
        {
            printf("Expected input with single word only!");
            return 1;
        }
        
    // get message to encrypt from user
    string msg = GetString();
    // if input null, repeat until get at least on character
    if (msg == NULL) 
        do 
        {
            msg = GetString();
        } while (strlen(msg) > 0);

    // encrypt and output result
    for (int i = 0, n = strlen(msg); i < n; i++)
    {   
        if (isalpha(msg[i])) 
        {
            if (isupper(key[k])) 
                shift = key[k] - 65;
            else
                shift = key[k] - 97;
            if (isupper(msg[i])) 
                msg[i] = (msg[i] - 65 + shift) % 26 + 65;
            else
                msg[i] = (msg[i] - 97 + shift) % 26 + 97;
            k = (k+1) % key_length;
        }
        printf("%c", msg[i]);
    }
    printf("\n"); // break line. required for test to pass.
}