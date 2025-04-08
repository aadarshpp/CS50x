#include <ctype.h>
#include <stdio.h>
#include <string.h>

int allalpha(char[]);
void print_cipher(char[], char[]);

int main(int argc, char *argv[])
{
    int inValid = (argc != 2) || (strlen(argv[1]) != 26) || (!allalpha(argv[1]));
    if (inValid)
    {
        if (argc != 2)
            printf("Usage: ./substitution key\n");
        else
            printf("Key must contain 26 alphabetic characters.\n");

        return 1;
    }

    char s[1000];
    printf("plaintext: ");
    fgets(s, sizeof(s), stdin);
    print_cipher(s, argv[1]);

    return 0;
}

void print_cipher(char s[], char key[])
{
    int offset[26];
    char base;

    for (int i = 0; i < 26; i++)
    {
        char c = key[i];
        base = (islower(c) ? 'a' : 'A') + i;
        offset[i] = c - base;
    }

    for (int i = 0; s[i] != '\0'; i++)
    {
        char c = s[i];
        base = islower(c) ? 'a' : 'A';
        if (islower(c) || isupper(c))
            s[i] = ((c - base) + offset[c - base]) % 26 + base;
    }

    printf("ciphertext: %s", s);
}

int allalpha(char s[])
{
    char base;
    int seen[26];

    for (int i = 0; i < 26; i++)
        seen[i] = 0;

    for (int i = 0; s[i] != '\0'; i++)
    {
        char c = s[i];
        if (!isalpha(c))
            return 0;
        base = islower(c) ? 'a' : 'A';
        if (seen[c - base])
            return 0;
        seen[c - base] = 1;
    }
    return 1;
}
