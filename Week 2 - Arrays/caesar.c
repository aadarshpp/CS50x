#include <stdio.h>

int isnumber(char[]);
int tonumber(char[]);
void print_cipher(char[], int);

int main(int argc, char *argv[])
{
    int inValid = (argc != 2) || (!isnumber(argv[1]));
    if (inValid)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    char s[1000];
    printf("plaintext: ");
    fgets(s, sizeof(s), stdin);
    print_cipher(s, tonumber(argv[1]));

    return 0;
}

void print_cipher(char s[], int key)
{
    for (int i = 0; s[i] != '\0'; i++)
    {
        char c = s[i];
        int isLower = (c >= 'a' && c <= 'z');
        int isUpper = (c >= 'A' && c <= 'Z');
        char base = isLower ? 'a' : 'A';
        if (isLower || isUpper)
            s[i] = ((c - base) + key) % 26 + base;
    }
    printf("ciphertext: %s", s);
}

int isnumber(char s[])
{
    for (int i = 0; s[i] != '\0'; i++)
        if (!(s[i] >= '0' && s[i] <= '9'))
            return 0;
    return 1;
}

int tonumber(char s[])
{
    int n = 0;
    for (int i = 0; s[i] != '\0'; i++)
        n = n * 10 + (s[i] - '0');
    return n;
}
