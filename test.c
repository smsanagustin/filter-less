#include <stdio.h>
#include <math.h>
#include <cs50.h>

int main(void)
{
    int x = get_int("x: ");
    int y = get_int("y: ");
    switch(x)
    {
        case 1:
        printf("1 and 3\n");
        break;
        case 5:
        printf("5 and 2\n");
        default:
        printf("not specified\n");
        break;
    }
}