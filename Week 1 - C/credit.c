#include <stdio.h>

// prints INVALID if the number is invalid otherwise the card company name
void print_card(long n)
{
    int len = 0;
    int luhn_sum = 0;
    int doubleDigit = 0;
    int digit;
    int firstTwoDigits = -1;
    while (n > 0)
    {
        if (n <= 99 && firstTwoDigits == -1)
        {
            firstTwoDigits = (int) n;
        }
        digit = n % 10;
        n = n / 10;
        if (doubleDigit)
        {
            digit *= 2;
            if (digit > 9)
            {
                digit = digit - 9;
            }
        }
        luhn_sum += digit;
        len += 1;
        doubleDigit = !doubleDigit;
    }
    if (luhn_sum % 10 == 0)
    {
        if (firstTwoDigits / 10 == 4 && (len == 13 || len == 16))
        {
            printf("VISA\n");
        }
        else if ((firstTwoDigits == 34 || firstTwoDigits == 37) && len == 15)
        {
            printf("AMEX\n");
        }
        else if (firstTwoDigits >= 51 && firstTwoDigits <= 55 && len == 16)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

int main(void)
{
    long n;
    while (1)
    {
        printf("Change owed: ");
        if (scanf("%ld", &n) != 1)
        {
            while (getchar() != '\n')
                ;
            continue;
        }

        if (n >= 0)
        {
            print_card(n);
            break;
        }
    }
    return 0;
}
