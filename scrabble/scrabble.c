#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int SCORE[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int count_score(string str_player);

int main(void)
{

    string str_player1 = get_string("Player 1: ");
    string str_player2 = get_string("Player 2: ");

    int result1 = count_score(str_player1);
    int result2 = count_score(str_player2);

    if (result1 > result2)
    {
        printf("Player 1 wins!\n");
    }
    else if (result1 < result2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!");
    }
}

int count_score(string str_player)
{
    int local_score = 0;
    // converting input from player to uppercase
    for (int i = 0, len = strlen(str_player); i < len; i++)
    {
        // check if it is char, other thing will be ignored
        if (isalpha(str_player[i]))
        {
            str_player[i] = toupper(str_player[i]);
            int letter = SCORE[str_player[i] - 'A'];
            local_score += letter;
        }
    }

    return local_score;
}
