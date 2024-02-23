#include <cs50.h>
#include <stdio.h>

void pyramid_spaces(int length);
void pyramid_hashes(int length);

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height <= 0 || height > 9);

    for (int j = height; j > 0; j--)
    {
        pyramid_spaces(j - 1);
        pyramid_hashes(height - (j - 1));
        printf("  ");
        pyramid_hashes(height - (j - 1));
        printf("\n");
    }
}

void pyramid_spaces(int length)
{
    for (int i = length; i > 0; i--)
    {
        printf(" ");
    }
}

void pyramid_hashes(int length)
{
    for (int i = length; i > 0; i--)
    {
        printf("#");
    }
}
