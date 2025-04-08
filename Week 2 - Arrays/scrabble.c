#include <stdio.h>

int get_word_value(char[]);

int main(void)
{
    char word1[50];
    char word2[50];

    printf("Player 1: ");
    scanf("%49s", word1);
    printf("Player 2: ");
    scanf("%49s", word2);

    int score1 = get_word_value(word1);
    int score2 = get_word_value(word2);

    if (score1 > score2)
        printf("Player 1 wins!\n");
    if (score1 < score2)
        printf("Player 2 wins!\n");
    else
        printf("Tie!\n");

    return 0;
}

int get_word_value(char word[])
{
    const int scores[] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                          1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    int value = 0;

    for (int i = 0; word[i] != '\0'; i++)
    {
        char c = word[i];
        if (c >= 'a' && c <= 'z')
            value += scores[c - 'a'];
        if (c >= 'A' && c <= 'Z')
            value += scores[c - 'A'];
    }

    return value;
}
