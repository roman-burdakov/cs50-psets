#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // validate input parameters
    if (argc != 2 || !isdigit(argv[1][0]) || atoi(argv[1]) < 0) {
        printf("Expected input with single positive number only!");
        return 1;
    }
    int k = atoi(argv[1]);
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
        if (isalpha(msg[i])) {
            if (isupper(msg[i])) 
                msg[i] = (msg[i] - 65 + k) % 26 + 65;
            else
                msg[i] = (msg[i] - 97 + k) % 26 + 97;
        }
        printf("%c", msg[i]);
    }
    printf("\n"); // break line. required for test to pass.
}