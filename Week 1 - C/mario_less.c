#include <stdio.h>

// prints right slanted pyramid of size n
void printPyramid(int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (j <= n - i)
                printf(" ");
            else
                printf("#");
        }
        printf("\n");
    }
}

int main(void)
{
    int n;
    while (1)
    {
        printf("Height: ");
        if (scanf("%d", &n) != 1)
        {
            while (getchar() != '\n')
                ;
            continue;
        }
        if (n >= 1 && n <= 8)
        {
            printPyramid(n);
            break;
        }
    }
    return 0;
}
