#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int get_length(long number);

int main(void)
{
    long card_number = get_long("Number: ");
    long init_card_number = card_number;
    int count = 0;
    int multi_sum = 0;
    int raw_sum = 0;
    int overall_summ;
    long first_two = card_number;

    for (long i = 10; card_number > 0; card_number /= 10)
    {
        long digit = card_number % i;

        if (count)
        {
            digit *= 2;
            multi_sum += (digit / 10) + (digit % 10);
        }
        if (!count)
        {
            raw_sum += (digit / 10) + (digit % 10);
        }
        count = !count;
    }

    overall_summ = multi_sum + raw_sum;

    while (first_two >= 100)
    {
        first_two /= 10;
    }

    int first_num = first_two / 10;
    printf("first_num: %i\n", first_num);

    if (overall_summ % 10 == 0)
    {
        int card_number_length = get_length(init_card_number);
        printf("card_number_length: %i\n", card_number_length);
        if (card_number_length == 15)
        {
            switch (first_two)
            {
                case 34:
                case 37:
                    printf("AMEX\n");
                    break;
                default:
                    printf("INVALID\n");
                    break;
            }
        }
        else if (card_number_length == 16)
        {
            switch (first_two)
            {
                case 51:
                case 52:
                case 53:
                case 54:
                case 55:
                    printf("MASTERCARD\n");
                    break;
                default:
                    if (first_num == 4)
                    {
                        printf("VISA\n");
                    }
                    else
                    {
                        printf("INVALID\n");
                    }
                    break;
            }
        }
        else if (card_number_length == 13 && first_num == 4)
        {
            printf("VISA\n");
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

int get_length(long number)
{
    int length = 0;
    if (number == 0)
    {
        return 1;
    }
    while (number != 0)
    {
        number /= 10;
        length++;
    }
    return length;
}
