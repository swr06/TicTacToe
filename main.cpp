

/*
Author : Samuel Wesley Rasquinha
Email : samuelrasquinha@gmail.com
Title : Tic Tac Toe
Age : 12
Description : Tic Tac Toe game with basic Artificial Intelligence
Version : 1.0 Beta
Updates : 2018 - 8 - 27
Comments : Yes
Reference : Myself
*/

/* Errors / Bugs


*/

/* Todo
1 : Create a menu where you can choose to play with another player or the computer
*/
#include <bits/stdc++.h> // I know this is bad... like it makes the program 1 MB+
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

#define ROW 3
#define COL 3
#define CIRCLE 'O'
#define CROSS  'X'
#define true 1
#define false 0


using namespace std ;

char player_char = CROSS ;
char computer_char = CIRCLE ;
// where the user's last move was..
int user_x = 0 ;
int user_y = 2 ;
// to check if the computer already displayed the winning sequence
int win_chk_ = false ;
int while_loop ;
int amount_computer ;
const int none = 1 ;

enum board_enum
{
    vacant = -1, player = 2, computer = 3
};

int board[ROW][COL] ;
int *free_space[ROW * COL] ;
int *computer_space[ROW * COL] ;

//  Function Prototypes
int AI_() ; // the heart of this whole project.. the main function is to check if the player can win in the next move and block accordingly
void scrclr() ; // clear the screen
int is_full_board() ; // check if any spaces in the board is empty and return the values accordingly
int is_full(int x, int y) ; // check if board[x][y] is full and return the values accordingly
int empty_chk(int x, int y) ; // check if board[x][y] is vacant and return the values accordingly
int user_interface_computer() ; // display the board and execute the functions for the player to play against the computer : user_input, AI_ and win_chk functions
void user_input() ; // tell the user to enter the x and y co ordinate to play his/her move
void print_board() ; // print the entire board
int initialize_board() ; // initialize the whole board to vacant
void play(int x, int y) ; // tell the computer to play at a particular x and y co- ordinate
int win_chk_computer(int) ; // to check if the computer has won
int win_chk_player() ; // to check if the player has won
// PLAN_ OR PLAN__ are AI_ can't block the player
int PLAN_() ; // for loop to check if the subsequent box is empty
int PLAN__() ; // use of the rand() function (using an efficient method) which is currently used
void init_free_space() ; // initialize the free space pointer array to NULL
int rand_gen(int range) ; // to return a random digit to a particular range (0 - user_defined) (use of rand function, just for convenience)
void run() ; // to run all the initialize functions and user interface
void choose_character() ; // ask the player which character he/she wants and initialise the two variables
int get_best_move() ;
void undo_play() ;

int main()
{
    run() ;
    _getch() ;

    return 0 ;

}

void run()
{
    init_free_space() ;
    choose_character() ;
    initialize_board() ;
    user_interface_computer() ;
}

int initialize_board()
{
    for (int i = 0 ; i < ROW ; i++)
    {
        for (int j = 0 ; j < COL ; j++)
        {
            board[i][j] = vacant ;
        }
    }
}

void print_board()
{
    for (int i = 0 ; i < ROW ; i++)
    {
        cout << "|" ;

        for (int j = 0 ; j < COL ; j++)
        {
            if (board[i][j] == player)
            {
                cout << " " << player_char ;
                cout << " |" ;
            }

            else if (board[i][j] == computer)
            {
                cout << " " << computer_char ;
                cout << " |" ;
            }

            else
            {
                cout << "  " ;
                cout << " |" ;
            }
        }

        cout << endl ;
        cout << "-------------" ;
        cout << endl ;
    }
}

void user_input()
{
    int temp = 1 ;
    int input_user_x ;
    int input_user_y ;

    if (while_loop == 1)
    {
        while (temp == 1)
        {
            temp = 0 ;
            scrclr() ;
            print_board() ;

            cout << endl ;
            cout << "Enter a x co-ordinate (0-2) : " ;
            cin >> input_user_x ;
            cout << "\nEnter a y co-ordinate (0-2) : " ;
            cin >> input_user_y ;

            if (input_user_x > 2 | input_user_y > 2 | input_user_x < 0 | input_user_y < 0 | board[input_user_x][input_user_y] != vacant)
            {
                temp = 1 ;
            }
        }
    }

    user_x = input_user_x ;
    user_y = input_user_y ;
    board[user_x][user_y] = player ;
}

int user_interface_computer()
{
    int win ;
    int ai_return ;
    int full_chk ;
    int plan_return ;
    int temp = 0 ;

    while_loop = 1 ;

    while (while_loop == 1)
    {
        if (win_chk_computer(temp) == 0) // if nobody or sombody won
        {
            return 0 ;
        }

        user_input() ;

        if (win_chk_player() == 0)
        {
            return 0 ;
        }

        get_best_move() ;
    }
}

void choose_character()
{
    int char_num ;
    int chk = true ;

    while (chk == true)
    {
        chk = false ;
        scrclr() ;
        cout << "Tic Tac Toe V01 Beta By Samuel (samuelrasquinha@gmail.com)" ;
        cout << endl << endl ;
        cout << "1 = X" << endl ;
        cout << "2 = O" << endl ;
        cout << "Choose your character (1 or 2) : " ;
        cin >> char_num ;

        if (char_num > 2 | char_num < 1)
        {
            chk = true ;
        }

        else if (char_num == 1)
        {
            player_char = CROSS ;
            computer_char = CIRCLE ;
        }

        else if (char_num == 2)
        {
            player_char = CIRCLE ;
            computer_char = CROSS ;
        }

        else
        {
            cout << "This should not happen" ;

            _getch() ;
        }
    }

    scrclr() ;
}

int empty_chk(int x, int y)
{
    /* Return Values ::
    1 = board[x][y] is vacant
    0 = board[x][y] is not vacant
    */

    if (board[x][y] == vacant)
    {
        return 1 ;
    }

    else
    {
        return 0 ;
    }
}

int is_full(int x, int y)
{
    /* Return Values ::
    1 = board[x][y] is full
    0 = board[x][y] is vacant
    */

    if (board[x][y] != vacant)
    {
        return 1 ;
    }

    else if (board[x][y] == vacant)
    {
        return 0 ;
    }
}

int is_full_board()
{
    /* Return Values ::
    1 = the whole board is full
    0 = there is at least one empty space
    */

    int return_value = 1 ;

    for (int i = 0 ; i < ROW ; i++)
    {
        for (int j = 0 ; j < COL ; j++)
        {
            if (board[i][j] == vacant)
            {
                return_value = 0 ;

                break ;
            }
        }
    }

    return return_value ;
}

void scrclr()
{
    system("@cls") ;
}

void play(int x, int y)
{
    board[x][y] = computer ;
}

void undo_play(int x, int y)
{
    board[x][y] = vacant ;
}

int AI_()
{
    /* Return Values ::
    1 = Computer has played
    -1 = No Need for blocking ie : the player has not done the move in a place where he/she can win in the next move
    -2 = error
    */
    int target_x ; // these are the 2 co-ordinates that will tell the computer where to play the move
    int target_y ;

    /// ROW 1

    // If the player plays the moves at 0,0
    if (user_x == 0 && user_y == 0)
    {
        // Down

        if (board[1][0] == player && board[2][0] == vacant) // Checking and initializing to check if board[0][1] has player in it if it has then the computer should play at board[2][0]
        {
            target_x = 2 ;
            target_y = 0 ;
        }

        else if (board[1][0] == vacant && board[2][0] == player) // Vice Versa
        {
            target_x = 1 ;
            target_y = 0 ;
        }

        //Right

        else if (board[0][1] == player && board[0][2] == vacant) // Checking
        {
            target_x = 0 ;
            target_y = 2 ;
        }

        else if (board[0][1] == vacant && board[0][2] == player) // Vice Versa
        {
            target_x = 0 ;
            target_y = 1 ;
        }

        // Diagonal

        else if (board[1][1] == player && board[2][2] == vacant) // Checking
        {
            target_x = 2 ;
            target_y = 2 ;
        }

        else if (board[1][1] == vacant && board[2][2] == player) // Vice Versa
        {
            target_x = 1 ;
            target_y = 1 ;
        }

        else
        {
            return -1 ;  // Return -1 because there is no need for blocking and then the computer can launch its own plan
        }
    }

    // If the player plays the moves at 0,1

    else if (user_x == 0 && user_y == 1)
    {
        // Down

        if (board[1][1] == player && board[2][1] == vacant) // Checking
        {
            target_x = 2 ;
            target_y = 1 ;
        }

        else if (board[1][1] == vacant && board[2][1] == player) // Vice Versa
        {
            target_x = 1 ;
            target_y = 1 ;
        }

        //Right

        else if (board[0][0] == player && board[0][2] == vacant) // Checking
        {
            target_x = 0 ;
            target_y = 2 ;
        }

        else if (board[0][0] == vacant && board[0][2] == player) // Vice Versa
        {
            target_x = 0 ;
            target_y = 0 ;
        }

        else
        {
            return -1 ;
        }
    }

    // If the player plays the moves at 0,2

    else if (user_x == 0 && user_y == 2)
    {
        // Down

        if (board[1][2] == player && board[2][2] == vacant) // Checking
        {
            target_x = 2 ;
            target_y = 2 ;
        }

        else if (board[1][2] == vacant && board[2][2] == player) // Vice Versa
        {
            target_x = 1 ;
            target_y = 2 ;
        }

        //Left

        else if (board[0][0] == player && board[0][1] == vacant) // Checking
        {
            target_x = 0 ;
            target_y = 1 ;
        }

        else if (board[0][0] == vacant && board[0][1] == player) // Vice Versa
        {
            target_x = 0 ;
            target_y = 0 ;
        }

        // Diagonal

        else if (board[1][1] == player && board[2][0] == vacant) // Checking
        {
            target_x = 2 ;
            target_y = 0 ;
        }

        else if (board[1][1] == vacant && board[2][0] == player) // Vice Versa
        {
            target_x = 1 ;
            target_y = 1 ;
        }

        else
        {
            return -1 ;
        }
    }

    /// ROW 2

    // If the player plays the moves at 1,0

    else if (user_x == 1 && user_y == 0)
    {
        // Down

        if (board[0][0] == player && board[2][0] == vacant) // Checking
        {
            target_x = 2 ;
            target_y = 0 ;
        }

        else if (board[0][0] == vacant && board[2][0] == player) // Vice Versa
        {
            target_x = 0 ;
            target_y = 0 ;
        }

        //Right

        else if (board[1][1] == player && board[1][2] == vacant) // Checking
        {
            target_x = 1 ;
            target_y = 2 ;
        }

        else if (board[1][1] == vacant && board[1][2] == player) // Vice Versa
        {
            target_x = 1 ;
            target_y = 1 ;
        }

        else
        {
            return -1 ;
        }
    }

    //If the player plays the moves at 1,1

	else if (user_x == 1 && user_y == 1)
    {
        // Down

        if (board[0][1] == player && board[2][1] == vacant) // Checking
        {
            target_x = 2 ;
            target_y = 1 ;
        }

        else if (board[0][1] == vacant && board[2][1] == player) // Vice Versa
        {
            target_x = 0 ;
            target_y = 1 ;
        }

        //Right

        else if (board[1][0] == player && board[1][2] == vacant) // Checking
        {
            target_x = 1 ;
            target_y = 2 ;
        }

        else if (board[1][0] == vacant && board[1][2] == player) // Vice Versa
        {
            target_x = 1 ;
            target_y = 0 ;
        }

        // Diagonal

        else if (board[0][0] == player && board[2][2] == vacant) // Checking
        {
            target_x = 2 ;
            target_y = 2 ;
        }

        else if (board[0][0] == vacant && board[2][2] == player) // Vice Versa
        {
            target_x = 0 ;
            target_y = 0 ;
        }

        else
        {
            return -1 ;
        }
    }

    //If the player plays the moves at 1,2

	else if (user_x == 1 && user_y == 2)
    {
        // Down

        if (board[0][2] == player && board[2][2] == vacant) // Checking
        {
            target_x = 2 ;
            target_y = 2 ;
        }

        else if (board[0][2] == vacant && board[2][2] == player) // Vice Versa
        {
            target_x = 0 ;
            target_y = 2 ;
        }

        //Left

        else if (board[1][0] == player && board[1][1] == vacant) // Checking
        {
            target_x = 1 ;
            target_y = 1 ;
        }

        else if (board[1][0] == vacant && board[1][1] == player) // Vice Versa
        {
            target_x = 1 ;
            target_y = 0 ;
        }

        else
        {
            return -1 ;
        }
    }

    /// ROW 3

    //If the player plays the moves at 2,0

	else if (user_x == 2 && user_y == 0)
    {
        // Up

        if (board[1][0] == player && board[0][0] == vacant) // Checking
        {
            target_x = 0 ;
            target_y = 0 ;
        }

        else if (board[1][0] == vacant && board[0][0] == player) // Vice Versa
        {
            target_x = 1 ;
            target_y = 0 ;
        }

        //Right

        else if (board[2][1] == player && board[2][2] == vacant) // Checking
        {
            target_x = 2 ;
            target_y = 2 ;
        }

        else if (board[2][1] == vacant && board[2][2] == player) // Vice Versa
        {
            target_x = 2 ;
            target_y = 1 ;
        }

        // Diagonal

        else if (board[1][1] == player && board[0][2] == vacant) // Checking
        {
            target_x = 0 ;
            target_y = 2 ;
        }

        else if (board[1][1] == vacant && board[0][2] == player) // Vice Versa
        {
            target_x = 1 ;
            target_y = 1 ;
        }

        else
        {
            return -1 ;
        }
    }

    //If the player plays the moves at 2,1

	else if (user_x == 2 && user_y == 1)
    {
        // Up

        if (board[1][1] == player && board[0][1] == vacant) // Checking
        {
            target_x = 0 ;
            target_y = 1 ;
        }

        else if (board[1][1] == vacant && board[0][1] == player) // Vice Versa
        {
            target_x = 1 ;
            target_y = 1 ;
        }

        //Right

        else if (board[2][2] == player && board[2][0] == vacant) // Checking
        {
            target_x = 2 ;
            target_y = 0 ;
        }

        else if (board[2][2] == vacant && board[2][0] == player) // Vice Versa
        {
            target_x = 2 ;
            target_y = 2 ;
        }

        else
        {
            return -1 ;
        }
    }

    //If the player plays the moves at 2,2

	else if (user_x == 2 && user_y == 2)
    {
        // Up

        if (board[1][2] == player && board[0][2] == vacant) // Checking
        {
            target_x = 0 ;
            target_y = 2 ;
        }

        else if (board[1][2] == vacant && board[0][2] == player) // Vice Versa
        {
            target_x = 1 ;
            target_y = 2 ;
        }

        //Left

        else if (board[2][1] == player && board[2][0] == vacant) // Checking
        {
            target_x = 2 ;
            target_y = 0 ;
        }

        else if (board[2][1] == vacant && board[2][0] == player) // Vice Versa
        {
            target_x = 2 ;
            target_y = 1 ;
        }

        // Diagonal

        else if (board[1][1] == player && board[0][0] == vacant) // Checking
        {
            target_x = 0 ;
            target_y = 0 ;
        }

        else if (board[1][1] == vacant && board[0][0] == player) // Vice Versa
        {
            target_x = 1 ;
            target_y = 1 ;
        }

        else
        {
            return -1 ;
        }
    }

    // Play the move
    play(target_x,target_y) ;
}

int win_chk_player()
{
    /* Return Values
    1 = None
    2 = Player
    */

    const int none = 1 ;
    int return_val ;

    /// Horizontal checks

    // x0

    if (board[0][0] == player && board[0][1] == player && board[0][2] == player)
    {
        return_val = player ;
    }

    //x1

    else if (board[1][0] == player && board[1][1] == player && board[1][2] == player)
    {
        return_val = player ;
    }

    //x2

    else if (board[2][0] == player && board[2][1] == player && board[2][2] == player)
    {
        return_val = player ;
    }

    /// Vertical checks

    //y1

    else if (board[0][0] == player && board[1][0] == player && board[2][0] == player)
    {
        return_val = player ;
    }

    //y2

    else if (board[0][1] == player && board[1][1] == player && board[2][1] == player)
    {
        return_val = player ;
    }

    //y3

    else if (board[0][2] == player && board[1][2] == player && board[2][2] == player)
    {
        return_val = player ;
    }

    /// Diagonal

    // d1

    else if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
    {
        return_val = player ;
    }

    // d2

    else if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
    {
        return_val = player ;
    }

    else
    {
        return_val = none ;
    }

    if (win_chk_ == false && return_val == player)
    {
        while_loop = 0 ;
        win_chk_ = true ;
        scrclr() ;
        cout << "Player (" << player_char << ") has won!" ;
        cout << endl << endl ;
        print_board() ;

        return 0 ;
    }

    else if (is_full_board() == 1 && return_val == 1)
    {
        while_loop = 0 ;
        win_chk_ = true ;
        scrclr() ;
        cout << "Nobody Won ! Neither " << player_char << " nor " << computer_char << " (Draw Match) " ;

        return 0 ;
    }

    return return_val ;
}

int win_chk_computer(int ai_chk)
{
    /* Return Values
    1 = None
    3 = Computer has won
    */

    const int none = 1 ;
    int return_val ;

    /// Horizontal checks

    // x0

    if (board[0][0] == computer && board[0][1] == computer && board[0][2] == computer)
    {
        return_val = computer ;
    }

    //x1

    else if (board[1][0] == computer && board[1][1] == computer && board[1][2] == computer)
    {
        return_val = computer ;
    }

    //x2

    else if (board[2][0] == computer && board[2][1] == computer && board[2][2] == computer)
    {
        return_val = computer ;
    }

    /// Vertical checks

    //y1

    else if (board[0][0] == computer && board[1][0] == computer && board[2][0] == computer)
    {
        return_val = computer ;
    }

    //y2

    else if (board[0][1] == computer && board[1][1] == computer && board[2][1] == computer)
    {
        return_val = computer ;
    }

    //y3

    else if (board[0][2] == computer && board[1][2] == computer && board[2][2] == computer)
    {
        return_val = computer ;
    }

    /// Diagonal

    // d1

    else if (board[0][2] == computer && board[1][1] == computer && board[2][0] == computer)
    {
        return_val = computer ;
    }

    // d2

    else if (board[0][0] == computer && board[1][1] == computer && board[2][2] == computer)
    {
        return_val = computer ;
    }

    else
    {
        return_val = none ;
    }

    if (ai_chk == 0)
    {
        if (win_chk_ == false && return_val == computer)
        {
            while_loop = 0 ;
            win_chk_ = true ;
            scrclr() ;
            cout << "Computer (" << computer_char << ") has won!" ;
            cout << endl << endl ;
            print_board() ;

            return 0 ;
        }

        else if (is_full_board() == 1 && return_val == 1)
        {
            while_loop = 0 ;
            win_chk_ = true ;
            scrclr() ;
            cout << "Nobody Won ! Neither " << player_char << " nor " << computer_char << " (Draw Match) " ;

            return 0 ;
        }
    }

    return return_val ;
}

int PLAN_() // this is not used in this current program
{
    /* Return Values
    -1 = impossible (i.e :- Board is full)
    1 = played
    2 = didn't play
    */

    int played = false ;

    if (is_full_board() == 1)
    {
        return -1 ;
    }


    for (int i = 0 ; i < ROW ; i++)
    {
        for (int j = 0 ; j < COL ; j++)
        {
            if (board[i][j] == vacant)
            {
               play(i,j) ;
               played = true ;

               break ;
            }
        }

        if (played == true)
        {
            break ;
        }
    }

    return played ;
}

int PLAN__()
{
    /* Return Values ::
    -1 = error
    1 = played
    */

    int vacant_chk = 0 ;
    int i = 0 ;
    int xy ;

    for (int i = 0 ; i < ROW ; i++)
    {
        for (int j = 0 ; j < COL ; j++)
        {
            if (board[i][j] == vacant)
            {
                free_space[vacant_chk] = &board[i][j] ;
                vacant_chk = vacant_chk + 1 ;
            }
        }
    }

    xy = rand_gen(vacant_chk) ;

    if (*free_space[xy] == vacant)
    {
        *free_space[xy] = computer ; // Play the move ;

        return 1 ;
    }

    else
    {
        return -1 ;
    }
}

void init_free_space()
{
    for (int i = 0 ; i < ROW * COL ; i++)
    {
        free_space[i] = NULL ;
    }
}

/*int rand_gen(int range)
{
    //Return Values ::
    //returns a random value from (0 - range)


    int result ;
    int rand ;

    result = (int) rand % range ;

    return result ;
}*/

int rand_gen(int range)
{
    /* Return Values ::
    returns a random value from (0 - range)
    */

    int result ;

    result = (int) rand() % range ;

    return result ;
}

int get_best_move()
{
    /* Return Values ::
    -1 = error
    1 = played a move that will make the computer win
    2 = played a move with the AI__() function
    3 = played a move with the PLAN__() function
    */

    int best_move = 0 ;
    int return_value = -1 ;

    for (int i = 0 ; i < ROW ; i++)
    {
        for (int j = 0 ; j < COL ; j++)
        {
            if (board[i][j] == vacant)
            {
                play(i,j) ;

                if (win_chk_computer(1) == computer)
                {
                    best_move = 1 ;
                    return_value = 1 ;

                    break ;
                }

                else if (win_chk_computer(1) == none)
                {
                    undo_play(i,j) ;
                }
            }
        }
    }

    if (best_move == 0) // if it cant win in the next move
    {
        if (AI_() == -1) // if it can't block the player
        {
            if (PLAN__() == -1) // then try to play at a random place.. and if that fails show an error message
            {
                scrclr() ;
                cout << "This should not happen" ;
                _getch() ;
            }

            else
            {
                return_value = 3 ;
            }
        }

        else
        {
            return_value = 2 ;
        }
    }

    return return_value ;
}

/*----END----*/
