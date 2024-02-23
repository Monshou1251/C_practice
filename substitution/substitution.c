#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool check_arguments(int argc, string argv[]);
bool check_length(string key);
bool check_alpha(string key);
bool check_duplicates(string key);

int main(int argc, string argv[])
{
    if (!check_arguments(argc, argv))
        return 1;

    string key = argv[1];

    if (!check_length(key) || !check_alpha(key) || !check_duplicates(key))
        return 1;

    string plaintext = get_string("plaintext: ");
    // string ciphertext[] = {0}

    for (int i = 0, len = strlen(plaintext); i < len; i++)
    {
        char letter = plaintext[i];
        if (isalpha(letter))
        {
            if (isupper(letter))
            {
                plaintext[i] = toupper(key[letter - 'A']);
            }
            else
            {
                plaintext[i] = tolower(key[toupper(letter) - 'A']);
            }
        }
    }

    printf("ciphertext: %s\n", plaintext);
}

bool check_arguments(int argc, string argv[])
{
    if (argc != 2 || !argv[1])
    {
        printf("Usage: ./substitution key\n");
        return false;
    }
    return true;
}

bool check_length(string key)
{
    int len = strlen(key);
    if (len != 26)
    {
        printf("Key must contain 26 characters.\n");
        return false;
    }
    return true;
}

bool check_alpha(string key)
{
    int len = strlen(key);
    for (int i = 0; i < len; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Key must only contain alphabetic characters.\n");
            return false;
        }
    }
    return true;
}

bool check_duplicates(string key)
{
    int occurrences[26] = {0};
    int len = strlen(key);
    for (int i = 0; i < len; i++)
    {
        int index = toupper(key[i]) - 'A';
        if (occurrences[index] > 0)
        {
            printf("Key must not contain repeated letters.\n");
            return false;
        }
        occurrences[index]++;
    }
    return true;
}
