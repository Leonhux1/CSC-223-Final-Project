// Name: Faizan Rafieuddin
// Final Project

// Including necessary header files for added functionality
#include <iostream>
#include <iomanip>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <ncurses.h>

using namespace std;

// Function prototypes
void clearScreen();
string keypress();

int main() {
    
    // Initializing the srand function with a time seed
    srand(time(NULL));
    
    // Initializing the variables that are going to be used in the program
    int userx, usery, playerx, playery, trap1x, trap1y, trap2x, trap2y, trap3x, trap3y;
    int x, y, num, dir, mtrap1x, mtrap1y, mtrap2x, mtrap2y, mtrap3x, mtrap3y;
    bool var = true;
    bool flag = true;
    string move, result, press;

    // User input for the dimensions of the board
    cout << "Please enter the dimensions of the board in the sequence column -> row:" << endl;
    cin >> usery;
    cin >> userx;
    
    // Creating the program dynamically using dynamic arrays as instructed
    char **board;
    board = new char * [userx];
    
    for(int i = 0; i < userx; i++) {
        board[i] = new char[usery];
    }
    
    // Filling up the array with dots '.'
    for(int j = 0; j < usery; j++) {
        for(int k = 0; k < userx; k++) {
            board[k][j] = '.';
        }
    }
    
    // Creating the player and trap positions randomly
    playery = rand() % 2;
    playerx = rand() % usery;
    trap1x = rand() % usery;
    trap1y = rand() % (userx - 2) + 2;
    trap2x = rand() % usery;
    trap2y = rand() % (userx - 2) + 2;
    trap3x = rand() % usery;
    trap3y = rand() % (userx - 2) + 2;
    
    // Make sure trap1 is not equal to the end point
    if(trap1x == (usery - 1) && trap1y == (userx - 1)) {
        trap1x = rand() % usery;
        trap1y = rand() % (userx - 2) + 2;    
    }
    
    // Make sure trap2 is not equal to the end point
    if(trap2x == (usery - 1) && trap2y == (userx - 1)) {
        trap2x = rand() % usery;
        trap2y = rand() % (userx - 2) + 2;
    }
    
    // Make sure trap3 is not equal to the end point
    if(trap3x == (usery - 1) && trap3y == (userx - 1)) {
        trap3x = rand() % usery;
        trap3y = rand() % (userx - 2) + 2;
    }
    
    // Making sure that the traps dont overlap with each other. Making sure that the traps stay  
    // as diverse as possible to make the gameplay more exciting. Making sure that the traps dont 
    // overlap with the end point 'X' and the player 'G'
    while((trap1x == trap2x && trap1x == trap2y) || (trap2x == trap3x && trap2y == trap3y) || (trap1x == trap3x && trap1y == trap3y)) {
        if(trap1x == trap2x && trap1x == trap2y) {
            trap1x = rand() % usery;
            trap1y = rand() % (userx - 2) + 2;
            trap2x = rand() % usery;
            trap2y = rand() % (userx - 2) + 2;
        }
        if(trap2x == trap3x && trap2y == trap3y) {
            trap2x = rand() % usery;
            trap2y = rand() % (userx - 2) + 2;
            trap3x = rand() % usery;
            trap3y = rand() % (userx - 2) + 2;
        }
        if(trap1x == trap3x && trap1y == trap3y) {
            trap1x = rand() % usery;
            trap1y = rand() % (userx - 2) + 2;
            trap3x = rand() % usery;
            trap3y = rand() % (userx - 2) + 2;
        }
        
        while(trap1y == trap2y || trap2y == trap3y || trap1y == trap3y) {
            trap1y = rand() % (userx - 2) + 2;
            trap2y = rand() % (userx - 2) + 2;
            trap3y = rand() % (userx - 2) + 2;
        }
        
        while(trap1x == trap2x || trap2x == trap3x || trap1x == trap3x) {
            trap1x = rand() % usery;
            trap2x = rand() % usery;
            trap3x = rand() % usery;
        }
    }
    
    // Printing out the traps and the player on the dynamically created board
    board[trap1y][trap1x] = 'T';
    board[trap2y][trap2x] = 'T';
    board[trap3y][trap3x] = 'T';
    board[playery][playerx] = 'G';
    board[userx - 1][usery - 1] = 'X';
    
    // Storing the starting/original location of the player in variables 'x' and 'y'
    x = playerx;
    y = playery;
    
    // Storing the starting/original locations of the traps in respective variables
    mtrap1x = trap1x;
    mtrap1y = trap1y;
    mtrap2x = trap2x;
    mtrap2y = trap2y;
    mtrap3x = trap3x;
    mtrap3y = trap3y;
    
    // Clearing the screen
    clearScreen();
    
    // Printing out the board generated according to user preference
    for(int l = 0; l < userx; l++) {
        for(int s = 0; s < usery; s++) {
            cout << board[l][s];
        }
        cout << endl;
    }
    
    // Printing out the starting message and instructions
    cout << endl;
    cout << "Your " << userx << "(rows) x " << usery << "(columns) board is ready! Here's a glimpse of it." << endl;
    cout << endl;
    cout << "**Instructions**" << endl;
    cout << "1. You are labelled as 'G'. You have to avoid the traps 'T' and reach the treasure 'X' safely." << endl;
    cout << "2. Type 's' and press Enter to start the game." << endl;
    cout << "3. After that, press any KEY to VIEW the board and start navigating using ARROW KEYS. Good Luck!" << endl;
    
    // Storing the user response for the game to start
    cin >> press;
    
    // If the user enters the right response i.e. 's', the game gets started
    if(press == "s" || press == "S") {
        
        // While loop for a repeated view of the game
        while(var) {
            
            // Printing the board
            for(int m = 0; m < userx; m++) {
                for(int n = 0; n < usery; n++) {
                    cout << board[m][n];
                }
                cout << endl;
            }
            
            // Detecting the key pressed
            move = keypress();
            
            // A set of if, else if, and else statements that move the player
            // according to the key pressed. Also, making sure that the player
            // doesn't move out of the board
            if(move == "right") {
                if(x != (usery - 1)) {
                    board[y][x] = '.';
                    board[y][x + 1] = 'G';
                    x++;
                }
            }
            
            else if(move == "left") {
                if(x != 0) {
                    board[y][x] = '.';
                    board[y][x - 1] = 'G';
                    x--;
                }
            }
            
            else if(move == "up") {
                if(y != 0) {
                    board[y][x] = '.';
                    board[y - 1][x] = 'G';
                    y--;
                }
            }
            
            else if(move == "down") {
                if(y != (userx - 1)) {
                    board[y][x] = '.';
                    board[y + 1][x] = 'G';
                    y++;  
                }
            }
            
            // This block executes if an arrow key is not pressed during the gameplay
            else {
                cout << endl;
            }
            
            // Winning the game
            if(x == (usery - 1) && y == (userx - 1)) {
                result = "won";
                var = false;
            }
            
            // Hitting a trap
            if((x == trap1x && y == trap1y) || (x == trap2x && y == trap2y) || (x == trap3x && y == trap3y)) {
                result = "lost";
                var = false;
            }
            
            // Printing blank lines
            cout << endl;
            cout << endl;
            
            // Clearing the screen everytime for game like effect
            clearScreen();
            
        }
    }
    
    // Printing out the result according to the status of the player
    if(result == "won") {
        cout << "Congratulations! You won the game!" << endl;
    }
    if(result == "lost") {
        cout << "Ouch, you hit a trap! You loose!" << endl;
    }
    
    // Returning a 0 to the OS to indicate that the program has ended
    return 0;
}

// Function that clears the screen for game like effect
void clearScreen() {
    system("clear");
}

// Function that detects the arrow key pressed for moving the player
string keypress() {
    
    // Initializing contents within the ncurses library
    initscr();
    keypad(stdscr, true);
    
    // Getting input from the user and returning the arrow key pressed
    // according to the input.
    int input;
    input = getch();
    
    if(input == KEY_LEFT) { 
        return "left";
    }
    else if(input == KEY_RIGHT) {
        return "right";
    }
    else if(input == KEY_UP) {
        return "up";
    }
    else if (input == KEY_DOWN) { 
        return "down";
    }
    else { 
        return "none";
    }
    
    // A "none" is returned to the call-site if an arrow key is no pressed
    return "none";
}
