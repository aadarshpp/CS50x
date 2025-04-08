#include <stdio.h>

int roundToInt(float);
int memberOf(char, char[]);
float get_score(char[]);
void print_grade(float);

int main(void)
{
    char paragraph[1000];
    printf("Text: ");
    fgets(paragraph, sizeof(paragraph), stdin);

    print_grade(get_score(paragraph));

    return 0;
}

// Returns the Coleman-Liau index
float get_score(char paragraph[])
{
    int letters_count = 0;
    int word_count = 0;
    int sentence_count = 0;

    int word_start = 0;
    int one_word_in_sentence = 0;

    for (int i = 0; paragraph[i] != '\0'; i++)
    {
        char c = paragraph[i];
        if (!memberOf(c, ", .?!"))
        {
            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
            {
                letters_count += 1;
                word_start = 1;
            }
        }
        else
        {
            if (word_start)
            {
                word_count += 1;
                word_start = 0;
                one_word_in_sentence = 1;
            }

            if (memberOf(c, ".?!"))
            {
                if (one_word_in_sentence)
                {
                    sentence_count += 1;
                    one_word_in_sentence = 0;
                }
            }
        }
    }

    float L = letters_count / (word_count / 100.0f);
    float S = sentence_count / (word_count / 100.0f);
    float score = 0.0588 * L - 0.296 * S - 15.8;

    return score;
}

// Prints the grade according to the score
void print_grade(float score)
{
    if (score < 1)
        printf("Before Grade 1\n");
    else if (score > 16)
        printf("Grade 16+\n");
    else
        printf("Grade %d\n", roundToInt(score));
}

// Checks if char is a member of a string
int memberOf(char c, char string[])
{
    for (int i = 0; string[i] != '\0'; i++)
    {
        if (string[i] == c)
            return 1;
    }

    return 0;
}

// Rounds a float to the nearest integer
int roundToInt(float n)
{
    int a = (int) n;
    float f = n - a;

    if (f < 0.5)
    {
        return a;
    }
    else
    {
        return a + 1;
    }
}
