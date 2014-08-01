/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements the Game of Fifteen (generalized to d x d).
 *
 * Usage: ./fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [MIN,MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// board's minimal dimension
#define MIN 3

// board's maximal dimension
#define MAX 9

// board, whereby board[i][j] represents row i and column j
int board[MAX][MAX];

// board's dimension
int d;

int blankRow;
int blankColumn;

// prototypes, functions
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void save(void);

int main(int argc, string argv[])
{
    // greet player
    greet();

    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./fifteen d\n");
        return 1;
    }

    // ensure valid dimensions. Make string into integer. Int is already declared above the main function.
    d = atoi(argv[1]);
    if (d < MIN || d > MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            MIN, MIN, MAX, MAX);
        return 2;
    }

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // saves the current state of the board (for testing)
        save();

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep for animation's sake
        usleep(500000);
    }

    // that's all folks
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player. Clears the screen then prints Game of fifteen, then wait 2000000 before usage comes in
 */
void greet(void)
{
    clear();
    printf("GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1,
 * (i.e., fills board with values but does not actually print them),
 * whereby board[i][j] represents row i and column j.
 */
void init(void)
{
    // TODO
    /*
    what I did: defined several variables and declared them. basicly did the same as in function move but + 1 number.
    for all even numbers ( or odd numbers ) i made exceptions concerning 1 & 2. (swapping them)
    */
    int number = (d * d) - 1;
    int row;
    int column;
    
    blankRow = d - 1;
    blankColumn = d - 1;

    for(row = 0; row < d; row++)
    {
        for(column = 0; column < d; column++)
        {
            board[row][column] = number;
            number = number - 1;
        }
    }
    if(d == 4 || d == 6 || d == 8)
    {    
        board[blankRow][blankColumn - 1] = 2;
        board[blankRow][blankColumn - 2] = 1;
    }
}



/**
 * Prints the board in its current state.
 */
void draw(void)
{
    /*
    what I did: drawn init to the screen. telling the function to replace 0 with _ and whenever there is a one digit number "write" 
    two by filling in an extra blank for example. (%2)
    */
    int row;
    int column;

    for(row = 0; row < d; row++)
    {
        for(column = 0; column < d; column++)
        {
            if(board[row][column] == 0)
            {
                printf(" _ ");
            }
            else
            {
                printf("%2d ", board[row][column]);
            }
        }
        printf("\n");
    }
         
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    /* what i did is as follows. You want the program to look above under and on left and right. so this is what the function does.
    when everything is correct it will return true and will give a new position to blank.
    */
    if(blankRow + 1 <= d - 1 && tile == board[blankRow + 1][blankColumn])
    {
        board[blankRow][blankColumn] = tile;
        board[blankRow + 1][blankColumn] = 0;
        blankRow = blankRow + 1;
        return true;
    }
    
    else if(blankRow - 1 >= 0 && tile == board[blankRow - 1][blankColumn])
    {
        board[blankRow][blankColumn] = tile;
        board[blankRow - 1][blankColumn] = 0;
        blankRow = blankRow - 1;
        return true;
    }
    
    else if(blankColumn + 1 <= d - 1 && tile == board[blankRow][blankColumn + 1])
    {
        board[blankRow][blankColumn] = tile;
        board[blankRow][blankColumn + 1] = 0;
        blankColumn = blankColumn + 1;
        return true;
    }
    
    else if(blankColumn - 1 >= 0 && tile == board[blankRow][blankColumn - 1])
    {
        board[blankRow][blankColumn] = tile;
        board[blankRow][blankColumn - 1] = 0;
        blankColumn = blankColumn - 1;
        return true;
    }
    
    else
    {
        return false;
    }
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 start of with number 1 since 0 is not important for now created nested for loop counting row and column to < d and increment by 1
 if the number is equal to the board row column number it will continue the loop and adding 1 to number. When arriving at number 16
 its important to compare with value 0 since _ == 0 therefore I implemented module %16. When everything is correct 'won' returns true.
 if not it will return false
 */
bool won(void)
{
    int number = 1;
    int row;
    int column;

    for(row = 0; row < d; row++)
    {
        for(column = 0; column < d; column++)
        {
            if(number == board[row][column])
            {
                number = number + 1;
                number = number % 16;
            }    
            else
            {    
                return false;
            }
        }

    }
    return true;
}
/**
 * Saves the current state of the board to disk (for testing).
 */
void save(void)
{
    // log
    const string log = "log.txt";

    // delete existing log, if any, before first save
    static bool saved = false;
    if (!saved)
    {
        unlink(log);
        saved = true;
    }

    // open log
    FILE* p = fopen(log, "a");
    if (p == NULL)
    {
        return;
    }

    // log board
    fprintf(p, "{");
    for (int i = 0; i < d; i++)
    {
        fprintf(p, "{");
        for (int j = 0; j < d; j++)
        {
            fprintf(p, "%i", board[i][j]);
            if (j < d - 1)
            {
                fprintf(p, ",");
            }
        }
        fprintf(p, "}");
        if (i < d - 1)
        {
            fprintf(p, ",");
        }
    }
    fprintf(p, "}\n");

    // close log
    fclose(p);
}
