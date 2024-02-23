#include <cs50.h>
#include <stdio.h>

int collatz(int num, int steps);

int main(void)
{
    int userInput = get_int("Please choose the number: ");

    int steps = 0;

    collatz(userInput, steps);
}

int collatz(int num, int steps)
{
    if (num == 1)
    {
        printf("steps: %i\n", steps);
        return 0;
    }
    else if (num % 2 == 0)
    {
        steps++;
        return 1 + collatz(num / 2, steps);
    }
    else
    {
        steps++;
        return 1 + collatz(3 * num + 1, steps);
    }
}
