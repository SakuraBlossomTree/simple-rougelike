#include <curses.h>
#include <ncurses.h>

// 1. Setup ncurses in C. - Done
// 2. Add Player and Movement - Done
// 3. Hardcode map - Kinda
// 4. Add enemies

// Struct to define the player values like health, position and the character assigned to it
typedef struct{

    int health;
    int x_position;
    int y_position;
    char character[1];

} Player;

// Function to move the player to the x and y position
void movePlayer(Player *player, int x, int y){
    player->x_position += x;
    player->y_position += y;
}

// The main function 
int main(){
    
    initscr(); // Init screen ncurses
    cbreak(); // The input is immediately set to the terminal of screen
    noecho(); // This turns of echoing or printing of characters on the terminal
    keypad(stdscr, TRUE); // This allows for arrows keys to interact with.

    // Checking if ncurses is working or not.
    if (has_colors() == FALSE){
        endwin();
        printf("Your terminal does not support color\n");
        return 1;
    }
    
    start_color(); // Init color support on terminal
    init_pair(1, COLOR_WHITE, COLOR_BLACK); // And this is the color pair.

    // Hide the cursor
    curs_set(0);

    // Initlise the player 
    Player player = {100, 10, 10,'@'};


    // ncurses bullshit
    // printw("Hello World!");
    

    getch(); // Getting user input
    
    int ch; // Store the user input.

    // While loop for the player to move when the defined key is pressed in that direction.
    while ((ch = getch()) != 'q') {
        switch (ch) {
            case KEY_UP:
                movePlayer(&player, 0, -1);
                break;
            case KEY_LEFT:
                movePlayer(&player, -1, 0);
                break;
            case KEY_RIGHT:
                movePlayer(&player, 1, 0);
                break;
            case KEY_DOWN:
                movePlayer(&player, 0, 1);
                break;
            default:
                break;
        }

        // clear the screen
        clear();
        mvprintw(0, 0, "Player Health: %d", player.health); // Print the player health at the top-left of the screen
        mvaddch(player.y_position, player.x_position, player.character[0]); // Print the player character
        mvaddch(20, 20, '#'); // Just a reference to see if the player character was moving or not
        // Refresh the screen
        refresh();

    }

    // End ncurses
    endwin();
    
    return 0;
}
