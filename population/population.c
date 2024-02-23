#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{

    string answer = get_string("What's your name? ");

    if (strcmp(answer, "Kek") == 0) {
        printf("%s Cheburek\n", answer);
    } else if (strcmp(answer, "lol") == 0) {
        printf("karvalol\n");
    } else {
        printf("Allo, ti che napisal tut??\n");
    }



    // int x = get_int("What's x? ");
    // int y = get_int("What's y? ");

    // if (x > y) {
    //     printf("x is greate than y\n");
    // } else if (x < y) {
    //     printf("x is lesser than y\n");
    // } else {
    //     printf("x is equal to y");
    // }
    // TODO: Prompt for start size

    // TODO: Prompt for end size

    // TODO: Calculate number of years until we reach threshold

    // TODO: Print number of years
}
