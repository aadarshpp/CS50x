#include <stdio.h>

// prints two pyramid of size n
void printPyramid(int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= 2 * n + 2; j++)
        {
            if ((j <= n - i) || (j == n + 1) || (j == n + 2))
                printf(" ");
            else if (!(j > n + 2 + i))
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
