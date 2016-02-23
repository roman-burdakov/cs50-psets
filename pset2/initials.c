#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    string name = GetString();

    // if input null, repeat until get at least on character
    if (name == NULL) 
        do 
        {
            name = GetString();
        } while (strlen(name) > 0);

    printf("%c", toupper(name[0])); // print first uppercased initial
    for (int i = 0, n = strlen(name); i < n; i++) 
        if (isblank(name[i]) && i + 1 < n && isalpha(name[i + 1]))
            printf("%c", toupper(name[++i])); // print uppercased initial
    printf("\n"); // break line. required for test to pass.
}