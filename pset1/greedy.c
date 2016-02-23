#include <stdio.h>
#include <math.h>
#include <cs50.h>

int main(void)
{
    // init data including available coins value in decimals
    float change = 0;
    int coints_count = 0;
    float available_coints[4] = {0.25, 0.1, 0.05, 0.01};
    
    // get amount of change owned
    do {
        printf("How much change is owed?:\n");
        change = GetFloat();
    } while (change <= 0);
    
    // Compute change
    for (int i = 0; i < sizeof(available_coints) / sizeof(float); i++) {
        coints_count += change / available_coints[i];
        // getFloat() function doesn't return precise float.
        // 0.41 would be stored as 0.409999996 . It won't work when
        // we would try to compute fmod(0.00999999978, 0.01). Thus we need
        // to round up any float to 2 decimal when updating remaining change
        change = roundf(fmod(change, available_coints[i]) * 100) / 100 ;
    }
    
    printf("%i\n", coints_count);
}