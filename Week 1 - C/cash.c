#include <stdio.h>

// returns minimum number of coins needed to make n cents
int get_num(int n)
{
    int cost = 0;
    int coins[] = {25, 10, 5, 1};
    for (int i = 0; i < 4; i++)
    {
        if (n >= coins[i])
        {
            cost += (int) n / coins[i];
            n = n % coins[i];
        }
    }
    return cost;
}

int main(void)
{
    int n;
    while (1)
    {
        printf("Change owed: ");
        if (scanf("%d", &n) != 1)
        {
            while (getchar() != '\n')
                ;
            continue;
        }

        if (n >= 0)
        {
            printf("%d\n", get_num(n));
            break;
        }
    }
    return 0;
}
