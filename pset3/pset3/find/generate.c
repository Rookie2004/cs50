/**
 * generate.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Generates pseudorandom numbers in [0,LIMIT), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
       
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LIMIT 65536

int main(int argc, string argv[])
{
    // if argument count is not 2 or 3 stop the program and let the user now that they have to give either 1 or 2 arguments
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./generate n [s]\n");
        return 1;
    }

    // converts argument 1 which is a string (argc2) to an integer. Make a new variabel called int n.
    int n = atoi(argv[1]);

    // if argc is 3 the pseudorandomgenerator is seeded with a certain integer. Seeding the random generator makes the
    // output more random since the computer cannot generate real random numbers. srand unsigned int, means that the integer given
    // may not be negative and atoi argv2 suggests that argv2 which is a string is converted to an unsigned int. if argc is 3
    // meaning that someone gave a seed (integer) first line is executed when seed is not given it will not use srand.
    if (argc == 3)
    {
        srand((unsigned int) atoi(argv[2]));
    }
    else
    {
        srand((unsigned int) time(NULL));
    }

    // for int i = 0 (starts with 0) and i is smaller than n (formerly argv[1]) the number of pseudorandom numbers that need
    // to be generated, increment i bij 1 each time the loop executes. when it runs it prints random numbers (%i, rand())
    // % means modulo LIMIT which is set to 65536. This means that the values cannot exceed this number. It will start over
    // with counting starting with 1 (which basicly is 65537).
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", rand() % LIMIT);
    }

    // that's all folks
    return 0;
}
