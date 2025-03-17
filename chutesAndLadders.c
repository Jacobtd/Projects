/*
Jacob Doerr Programming Assignment 4

Note: I encountered a strange error where I could not reference the constant SIZE. In some cases, 100 is used where SIZE should be used instead. This obviously makes it 
harder for the code to be updated if you decided to change the board size, but for time's sake I just used 100. These areas are marked in the comments. 

Our code runs a simulated game of chutes and ladders, where if a player lands on an 'a-m', it is a chute, and an 'o-z', it is a ladder. There are also F and B squares, 
for forwards and backwards, which send players to the nearest H - haven square - in that direction. If a player goes too far forward without finding an H, they stay at 
the same position, and if a player goes too far backwards without finding an H, they start at the beginning. All havens, chutes, and ladders, are replaced after being 
used by a player. To implement this, we start by defining a constant, SIZE, which is the size of the board. Then, we declare function prototypes for our four functions 
outside of main, called move, printBoard, findHaven, and chuteLadder. Once in main, we initialize our board array, which is hardcoded, as board[]. We then create two 
pointers, one for each player, called p1 and p2, on the board array.Then, we open up our file which will print out the board after every turn. We set our random number
generator using srand, and then we start out gameplay loop. As long as both p1 and p2 are below the SIZE threshold, we continue to loop throughout our game. Inside the 
loop, we only have 3 lines of code - calling the move function for each player, then printing out the board with the printBoard function after the turn is completed. 

When calling the move function for a player, we input a pointer for each player, me being the pointer for the moving player and you being the pointer for the stationary 
player. We also input playernum, so we can output which player moved, and a pointer for our board array called board. We use an int, called roll, to store our randomized
dice roll, then move the me player pointer forward by that amount of spaces by addition. Once this is done, we print out a simple line that tells us what was rolled and
where the player ended up. After this, we compare me to you to check for collision.If there was collision, we move me back one space. After this, we check to see if the 
player landed on a special square. if we landed on a B or an F, we call the findHaven function, and if we land on an a-m or an o-z, we call the chuteLadder function. 
Once we make these checks, we check for collision again, in case moving to a haven or up/down a chute/ladder has placed us at the same position as the other player, 
and if it does, we move back one square again. Once all this is done, we return the player’s new position.

The findHaven function, which is called if the move function notices that the player has landed on an F or a B, takes the pointer to the player’s position and the 
pointer to the board as inputs. We check if we have landed on a B first, and if we have, we iterate backwards through the board from our current position until we 
locate an H. Once we find an H, we remove it, and replace it with a *. If we do not find an H, the player is returned back to the beginning of the board. Otherwise, 
if the player landed on an F, we do the same thing, but this time we iterate forward through the board until an H is found. If no H is found, we stay put and return 
the player’s current position, as the player cannot win by taking an F all the way to the end of the board.

The chuteLadder function, which is called if the move function notices that the player has landed on an ‘a-m’ or ‘o-z’, takes the pointer to the player’s position and
the pointer to the board as inputs. Using the integer moveAmount, we subtract the value at the player’s current position with ‘n’, our character we are using to judge
how far forward/back the player goes. This subtraction may leave us with a positive or negative number, dictating whether we go forward or backwards, and how far. Then, 
we return our new position.

Finally, we have our printBoard function. printBoard starts at the beginning of the board, and prints the contents slowly as we increment. Along the way, we check to
make sure that either p1 or p2 are not also at that position. If they are, we print a 1 or a 2 depending on which player pointer is there, and we continue looping 
until we reach the end of the board. 

Once all of this is done and the game is finished, we have a simple if/elif/else statement that compares the players’ final positions and declares a winner based on
who made it the furthest. The “tie” function here should never execute due to collision, but was left as a test that handles any potential errors around the collision 
as a game ends off of the board. 

*/


#include <stdio.h>  
#include <stdlib.h>
#include <time.h>
#define CRT_SECURE_NO_WARNINGS
#define SIZE 100; //constant used to reference the size of the board. In some loops where I wanted to use SIZE, I received an error that I could not resolve, so I used the number 100 instead.
// If we wanted to be able to change the size of the board easier, this would need to be resolved, but for now, I left those areas with the number 100 instead of the constant SIZE

// Function prototypes
char* move(char* me, char* you, int player_num, char* board); //move() prototype, requires pointers me and you, which point to each player's position, player_num, which identifies each player, and board, a pointer to where we are on the board.
void printBoard(const char* board, char* p1, char* p2, FILE* fp); //printBoard() prototype, again has a pointer for the board, as well as pointers p1 and p2 for the players, and a file pointer that is used to output the board to our file
char* findHaven(char* me, char* board); //findHaven() prototype, uses the pointer me to point to where the player is, and a pointer for the board
char* chuteLadder(char* me, char* board); //chuteLadder() prototype, uses the pointer me to point to where the player is, and a pointer for the board

void main() {
    char board[] = "  mHk  H l B He Flq p H  hByHlho H B  jr H B ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHF hoH B  "; // Initialize our board.Removed the 'n' on the board, replaced with a blank space
    char* p1 = board;  // Initialize player 1's position to the start of the board
    char* p2 = board;  // Initialize player 2's position to the start of the board
    FILE* fp = fopen("game_output.txt", "w");  // Open a file to write the game board

    if (fp == NULL) { //error handling for if we cannot find our file
        printf("Error opening file!\n");
        return;
    }
    srand(time(NULL));  // Set the random number generator

    // Main game loop: iterate while both players are within the board
    while (p1 < board + 100 && p2 < board + 100) { //100 here should be SIZE, but an error occurs, so for simplicity, we use 100 for SIZE. 
        p1 = move(p1, p2, 1, board);  // Move player 1
        p2 = move(p2, p1, 2, board);  // Move player 2
        printBoard(board, p1, p2, fp);  // Print the current state of the board to the file
    }

    // Determine the winner based on who reached further if both players reach the 100+ threshold
    if (p1 > p2) { //p1 wins with a higher number
        fprintf(fp, "Player 1 wins!\n");
        printf("Player 1 wins!\n");
    }
    else if (p2 > p1) { //p2 wins with a higher number
        fprintf(fp, "Player 2 wins!\n");
        printf("Player 2 wins!\n");
    }
    else { // Should not occur, just a safety check. I included this else as a check to ensure collision worked properly for the end of the game
        fprintf(fp, "It's a tie!\n");  
        printf("It's a tie!\n");
    }

    fclose(fp);  // Close the file
}

// Function to print the game board
void printBoard(const char* board, char* p1, char* p2, FILE* fp) {
    const char* current = board;  // Start pointer at the beginning of the board

    // Loop through the board until reaching the end character
    while (*current != '\0') {
        if (current == p1) { //If the current position is where p1 is,
            fputc('1', fp);  // Then mark '1' for player 1
        }
        else if (current == p2) { //If the current position is where p2 is,
            fputc('2', fp);  // Then mark '2' for player 2
        }
        else { //no player at this position on the board
            fputc(*current, fp);  // Output the current board character
        }
        current++;  // Move to the next character in the board
    }

    fputc('\n', fp);  // Newline at the end of the board state for readability
}


// Function to handle player movement
char* move(char* me, char* you, int playerNum, char* board) {
    // Rolls the die (random value between 1 and 6)
    int roll = rand() % 6 + 1;
    printf("Player %d rolls a %d\n", playerNum, roll); //Outputs the current player's dice roll

    me = me + roll;  // Move forward by the roll amount
    printf("Player %d moves to position %ld\n", playerNum, me - board);

    if (me == you) { //check for possible collision
        printf("Player %d collided with Player %d! Moving back 1 space.\n", playerNum, playerNum == 1 ? 2 : 1);
        me = me - 1;  // Move back 1 square. The ? operator is cool and can be used as an if/else inside these print statements. I don't remember if we went over this in class,
        //but I thought it was interesting enough to note and it is pretty useful in this case to save space without needing two seperate print statements for each case. I use this 
        //often throughout this function, and maybe in a few other locations. 
    }

    if (*me == 'B' || *me == 'F') { //Check if player landed on a forward or backward space
        me = findHaven(me, board, *me == 'B' ? -1 : 1);  // -1 for 'B', +1 for 'F'
        printf("Player %d landed on a '%c'. New position is %ld\n", playerNum, *me, me - board);
    }
    else if (*me >= 'a' && *me <= 'm') {  // Check if player landed on a chute
        me = chuteLadder(me, board);  // Slide down the chute
        printf("Player %d slid down a chute to position %ld\n", playerNum, me - board);
    }
    else if (*me >= 'o' && *me <= 'z') {  // Check if player landed on a ladder
        me = chuteLadder(me, board);  // Climb the ladder
        printf("Player %d climbed a ladder to position %ld\n", playerNum, me - board);
    }

    if (me == you) { //check for collision (After potentially hitting a F, B, Chute, or Ladder)
        printf("Player %d collided with Player %d again after moving. Moving back 1 space.\n", playerNum, playerNum == 1 ? 2 : 1);
        me = me - 1;
    }

    return me; //returns the player's current position
}

// Function to locate a haven position
char* findHaven(char* me, char* board) {
    if (*me == 'B') { //If we land on a backwards square
        // Move backward to the previous 'H' haven or to the beginning of the board.
        while (me > board && *me != 'H') { //loops until an H is found, or until the beginning of the board
            me--; //decrement player position
        }
        if (*me == 'H') { //If we find a Haven, 
            *me = '*'; //remove haven
            return me; //return player position
        }
        else {
            return board; // If no haven found, return the beginning of the board.
        }
    }
    else if (*me == 'F') { //If we land on a forwards square
        // Move forward to the next 'H' haven or to the end of the board.
        while (me < board + 100 && *me != 'H') { //continue until we find a haven
            me++; //increment player position
        }
        if (*me == 'H') { //If we find a Haven, 
            *me = '*'; //remove haven
            return me; //return player position
        }
        else {
            // If no haven found, stay at the current position. (Cannot win by hitting an F all the way to the end of the board)
            return me;
        }
    }
    // If not 'B' or 'F', return the original position (no haven found).
    return me;
}

// Function to handle chute or ladder logic
char* chuteLadder(char* me, char* board) {
    int moveAmount = *me - 'n';  // 'n' is the base reference character for both chutes and ladders
    char* newPosition = me + moveAmount; // Calculate the new position by adjusting the player's position with the move amount
    *me = '-'; // Remove the chute or ladder by replacing the character with '-'
    return newPosition;

/*
Player 1 rolls a 3
Player 1 moves to position 3
Player 2 rolls a 6
Player 2 moves to position 6
Player 1 rolls a 2
Player 1 moves to position 5
Player 2 rolls a 1
Player 2 moves to position 7
Player 1 rolls a 2
Player 1 moves to position 7
Player 1 collided with Player 2! Moving back 1 space.
Player 2 rolls a 5
Player 2 moves to position 12
Player 1 rolls a 5
Player 1 moves to position 11
Player 1 landed on a '*'. New position is 7
Player 2 rolls a 5
Player 2 moves to position 17
Player 2 slid down a chute to position 15
Player 1 rolls a 5
Player 1 moves to position 12
Player 2 rolls a 5
Player 2 moves to position 20
Player 2 climbed a ladder to position 22
Player 1 rolls a 5
Player 1 moves to position 17
Player 2 rolls a 5
Player 2 moves to position 27
Player 2 climbed a ladder to position 38
Player 1 rolls a 2
Player 1 moves to position 19
Player 2 rolls a 1
Player 2 moves to position 39
Player 2 climbed a ladder to position 43
Player 1 rolls a 2
Player 1 moves to position 21
Player 2 rolls a 2
Player 2 moves to position 45
Player 2 slid down a chute to position 40
Player 1 rolls a 4
Player 1 moves to position 25
Player 1 slid down a chute to position 19
Player 2 rolls a 3
Player 2 moves to position 43
Player 2 landed on a '*'. New position is 41
Player 1 rolls a 4
Player 1 moves to position 23
Player 2 rolls a 6
Player 2 moves to position 47
Player 1 rolls a 2
Player 1 moves to position 25
Player 2 rolls a 1
Player 2 moves to position 48
Player 2 slid down a chute to position 44
Player 1 rolls a 3
Player 1 moves to position 28
Player 2 rolls a 4
Player 2 moves to position 48
Player 1 rolls a 5
Player 1 moves to position 33
Player 2 rolls a 5
Player 2 moves to position 53
Player 2 landed on a '*'. New position is 62
Player 1 rolls a 5
Player 1 moves to position 38
Player 1 slid down a chute to position 34
Player 2 rolls a 3
Player 2 moves to position 65
Player 2 slid down a chute to position 61
Player 1 rolls a 6
Player 1 moves to position 40
Player 2 rolls a 1
Player 2 moves to position 62
Player 1 rolls a 2
Player 1 moves to position 42
Player 2 rolls a 4
Player 2 moves to position 66
Player 2 landed on a '*'. New position is 50
Player 1 rolls a 1
Player 1 moves to position 43
Player 1 landed on a '*'. New position is 33
Player 2 rolls a 4
Player 2 moves to position 54
Player 1 rolls a 2
Player 1 moves to position 35
Player 1 landed on a '*'. New position is 28
Player 2 rolls a 4
Player 2 moves to position 58
Player 2 slid down a chute to position 51
Player 1 rolls a 4
Player 1 moves to position 32
Player 2 rolls a 1
Player 2 moves to position 52
Player 1 rolls a 2
Player 1 moves to position 34
Player 2 rolls a 5
Player 2 moves to position 57
Player 1 rolls a 5
Player 1 moves to position 39
Player 2 rolls a 5
Player 2 moves to position 62
Player 1 rolls a 5
Player 1 moves to position 44
Player 2 rolls a 3
Player 2 moves to position 65
Player 1 rolls a 4
Player 1 moves to position 48
Player 2 rolls a 2
Player 2 moves to position 67
Player 1 rolls a 3
Player 1 moves to position 51
Player 2 rolls a 5
Player 2 moves to position 72
Player 1 rolls a 6
Player 1 moves to position 57
Player 2 rolls a 5
Player 2 moves to position 77
Player 2 slid down a chute to position 72
Player 1 rolls a 6
Player 1 moves to position 63
Player 2 rolls a 4
Player 2 moves to position 76
Player 1 rolls a 4
Player 1 moves to position 67
Player 2 rolls a 1
Player 2 moves to position 77
Player 1 rolls a 6
Player 1 moves to position 73
Player 2 rolls a 5
Player 2 moves to position 82
Player 2 slid down a chute to position 81
Player 1 rolls a 4
Player 1 moves to position 77
Player 2 rolls a 2
Player 2 moves to position 83
Player 1 rolls a 5
Player 1 moves to position 82
Player 2 rolls a 4
Player 2 moves to position 87
Player 1 rolls a 3
Player 1 moves to position 85
Player 1 landed on a '*'. New position is 79
Player 2 rolls a 5
Player 2 moves to position 92
Player 2 slid down a chute to position 86
Player 1 rolls a 5
Player 1 moves to position 84
Player 1 climbed a ladder to position 85
Player 2 rolls a 5
Player 2 moves to position 91
Player 1 rolls a 2
Player 1 moves to position 87
Player 2 rolls a 4
Player 2 moves to position 95
Player 1 rolls a 2
Player 1 moves to position 89
Player 2 rolls a 1
Player 2 moves to position 96
Player 2 landed on a '*'. New position is 94
Player 1 rolls a 6
Player 1 moves to position 95
Player 2 rolls a 6
Player 2 moves to position 100
Player 2 wins!

This board is from a different run than the above terminal output, but should still demonstrate the game working as intended. 
 1-Hk2 H l B He Flq p H  hByHlho H B  jr H B ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHF hoH B
  -Hk 21 - B He Flq p H  hByHlho H B  jr H B ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHF hoH B
  -Hk  21- B He Flq p H  hByHlho H B  jr H B ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHF hoH B
  -Hk  H2- B1He Flq p H  hByHlho H B  jr H B ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHF hoH B
  -Hk  H - B2He Flq p 1  hByHlho H B  jr H B ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHF hoH B
  -Hk  H - B He2F-q p *1 hByHlho H B  jr H B ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHF hoH B
  -Hk  H - B He F2q1p *  -ByHlho H B  jr H B ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHF hoH B
  -Hk  H - B He F-q p2*1 -ByHlho H B  jr H B ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHF hoH B
  -Hk  H - B He F-q p *  -B2Hlho H B  1r H B ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHF hoH B
  -Hk  H - B He F-q p *  -B-Hlh-2H B  jr H1B ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHF hoH B
  -Hk  H - B He F-q p *  -B-Hlh- H2B  jr 1 B ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHF hoH B
  -Hk  H - B He F-q p *  -B-Hlh- H2B  -r * B ir1j H  F ku gd  H pjB mH x  BF i H  m oB HlHF hoH B
  -Hk  H - B He F-q p *  -B-Hlh- H B  -r2* B ir j H  F ku gd  1 pjB mH x  BF i H  m oB HlHF hoH B
  -Hk  H - B He F-q p *  -B-Hlh- H B  -r2* B -r j H  F ku gd  * pjB1mH x  BF i H  m oB HlHF hoH B
  -Hk  H - B He F-q p *  -B-Hlh- 2 B  -r * B -r j H  F ku gd  * pjB m1 x  BF i H  m oB HlHF hoH B
  -Hk  H - B He F-q p *  -B-Hlh- * B 2-r * B -r j H  F ku gd  * pjB mH x 1BF i H  m oB HlHF hoH B
  -Hk  H - B He F-q p *  -B-Hlh- * B  -r2* B -r j H  F ku gd  * pjB mH x  BF i 1  m oB HlHF hoH B
  -Hk  H - B He F-q p *  -B-2lh- * B  -r * B -r j H  F ku gd  * pjB m1 x  BF i *  m oB HlHF hoH B
  -Hk  H - B He F-q p *  -B-*lh-2* B  -r * B -r j H  F ku gd  * pjB m* x1 BF i *  m oB HlHF hoH B
  -Hk  H - B He F-q p *  -B-*lh- * B2 -r * B -r j H  F ku gd  * pjB m* x  BF i *  m oB 1lHF hoH B
  -Hk  H - B He F-q p *  -B-*lh- * B  -- * 2 -r j H  F ku gd  * pjB m* x  BF i *  m oB *lHF h-1 B
  -Hk  H - B He F-q p *  -B-*lh- * B  -- * B 2r j H  F ku gd  * pjB m* x  BF i *  m oB *lHF h-H B1
  -Hk  H - B He F-q p *  -B-*lh- * B  -- * B -- j 2  F ku gd  * pjB m* x  BF i *  m oB *lHF h-H B
  -Hk  H - B He F-q p *  -B-*lh- * B  -- * B -- j H  F ku gd  * pjB m* x  BF i *  m oB *l2F h-H B
Player 1 wins!
*/
}
