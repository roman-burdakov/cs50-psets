/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
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
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    int row = 0;
    int n = d * d - 1;
    do
    {   
        int i = 0;
        while (i < d) 
        {   
            board[row][i++] = n--;
        }
        row++;
    } while(n > 0);
    
    // if board size is even, swap last two tiles
<<<<<<< HEAD
=======
    // NB: "0" represents missing tile.
>>>>>>> Updating workspace from C9 IDE after PSET5
    if (d % 2 == 0) {
        // swap using XOR to avoid overflow.
        board[d-1][d-2] = board[d-1][d-2] ^ board[d-1][d-3];
        board[d-1][d-3] = board[d-1][d-2] ^ board[d-1][d-3];
        board[d-1][d-2] = board[d-1][d-2] ^ board[d-1][d-3];
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for (int i = 0; i < d; i++) 
    {
        printf("  ");
        for (int j = 0; j < d; j++) 
        {
            // print value
            if (board[i][j] == 0)
                printf(" __");
            else
                printf(" %2i", board[i][j]);
        }
        //break line
        printf("\n\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // sanity check
    if (tile > d*d || tile < 0)
        return false;
    // find position of the tile in array
    int i = 0;
    int j = 0;
    for (int n = 0; n < d; n++) 
        for (int m = 0; m < d; m++) 
            if (board[n][m] == tile) {
                i = n;
                j = m;
                // found tile. exit loop
                break;
            }
    
<<<<<<< HEAD
    // shift if it is possible otherwise return false
=======
    // shift tile if it is possible otherwise return false
>>>>>>> Updating workspace from C9 IDE after PSET5
    if (i-1 >= 0 && board[i-1][j] == 0) {
        // shift up
        board[i-1][j] = board[i][j];
        board[i][j] = 0;
    } else if (j-1 >=0 && board[i][j-1] == 0) {
        // shift left
        board[i][j-1] = board[i][j];
        board[i][j] = 0;
    } else if (j+1 < d && board[i][j+1] == 0) {
        // shift right
        board[i][j+1] = board[i][j];
        board[i][j] = 0;
    } else if (i+1 < d && board[i+1][j] == 0) {
        // shift down
        board[i+1][j] = board[i][j];
        board[i][j] = 0;
    } else {
        return false;
    }
    // shift successful
    return true;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    int prev = 0;
    // quick check if last time isn't empty (value = 0)
    if (board[d-1][d-1] != 0) 
        return false;
<<<<<<< HEAD
    for (int i = 0; i < d; i++) 
    {
=======
    // verify that array is sorted in ascending order with last el. being 0
    for (int i = 0; i < d; i++) 
>>>>>>> Updating workspace from C9 IDE after PSET5
        for (int j = 0; j < d; j++) 
        {
            if (prev + 1 > board[i][j] && board[i][j] != 0) 
                return false;
            prev = board[i][j];
        }
<<<<<<< HEAD
    }
=======
>>>>>>> Updating workspace from C9 IDE after PSET5
    return true;
}