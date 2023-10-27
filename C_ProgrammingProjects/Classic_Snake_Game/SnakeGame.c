#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>  // Include time.h for srand

#define WIDTH 70
#define HEIGHT 20
#define SNAKE_LENGTH WIDTH * HEIGHT
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
// Function to clear the screen by overwriting characters with spaces
void clearScreen() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            gotoxy(j, i);
            printf(" ");
        }
    }
}
// Function to set text color
void SetColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Function to set the cursor position at a specific (x, y) coordinate
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int gameover, score;
int x, y, foodY, foodX, tailX[SNAKE_LENGTH], tailY[SNAKE_LENGTH];
int nTail;
int direction;

// Set up the initial game state.
void setup() {
    gameover = 0;
    score = 0;
    direction = RIGHT;
    srand(time(NULL));

    foodX = rand() % WIDTH;
    foodY = rand() % HEIGHT;

    x = WIDTH / 2;
    y = HEIGHT / 2;
}

// Draw the game board, including the snake and the food in the middle of the console.
void draw() {
    SetColor(0); // Set border color to black

    int consoleWidth = 80; // Set the width of the console
    int consoleHeight = 24; // Set the height of the console

    // Calculate the position to center the game board
    int centerX = (consoleWidth - WIDTH - 2) / 2;
    int centerY = (consoleHeight - HEIGHT - 2) / 2;

    gotoxy(centerX - 1, centerY - 1); // Move the cursor to the top-left corner of the border

    for (int i = 0; i < WIDTH + 2; i++) {
        SetColor(11); // Set text color to a different color, e.g., light cyan
        printf("*");
    }

    for (int i = 0; i < HEIGHT; i++) {
        gotoxy(centerX - 1, centerY + i); // Move the cursor to the left border
        SetColor(11); // Set text color to a different color, e.g., light cyan

        for (int j = 0; j < WIDTH; j++) {
            if (j == 0) {
                SetColor(11); // Set text color to a different color, e.g., light cyan
                printf("*");
            }
            if (i == y && j == x) {
                SetColor(10); // Set text color to green for the snake's head
                printf("O");
            } else if (foodY == i && foodX == j) {
                SetColor(12); // Set text color to red for the food
                printf("D");
            } else {
                int printTail = 0;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        SetColor(10); // Set text color to green for the snake's tail
                        printf("*");
                        printTail = 1;
                    }
                }
                if (printTail == 0) {
                    SetColor(15); // Set text color to white
                    printf(" ");
                }
            }
            if (j == WIDTH - 1) {
                SetColor(11); // Set text color to a different color, e.g., light cyan
                printf("*");
            }
        }
        gotoxy(centerX + WIDTH - 1, centerY + i); // Move the cursor to the right border
        SetColor(11); // Set text color to a different color, e.g., light cyan
    }

    gotoxy(centerX - 1, centerY + HEIGHT); // Move the cursor to the bottom-left corner of the border

    for (int i = 0; i < WIDTH + 2; i++) {
        SetColor(11); // Set text color to a different color, e.g., light cyan
        printf("*");
    }

    gotoxy(centerX, centerY + HEIGHT + 2); // Move the cursor below the border
    SetColor(15); // Set text color to white
    printf("SCORE: %d", score);
}

// Handle user input for changing the snake's direction.
void input() {
    if (kbhit()) {
        int key = getch();  // Get the ASCII value of the pressed key

        // Check the ASCII value of the key
        switch (key) {
            case 224:  // Arrow keys start with 224
                key = _getch();  // Get the specific arrow key
                switch (key) {
                    case 75:  // Left arrow
                        if (direction != RIGHT)  // Prevent moving into itself
                            direction = LEFT;
                        break;
                    case 77:  // Right arrow
                        if (direction != LEFT)
                            direction = RIGHT;
                        break;
                    case 72:  // Up arrow
                        if (direction != DOWN)
                            direction = UP;
                        break;
                    case 80:  // Down arrow
                        if (direction != UP)
                            direction = DOWN;
                        break;
                }
                break;
            case 'x':
                gameover = 1;
                break;
        }
    }
}

void logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (direction) {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
    }

    // Check for collisions with walls or the tail
    if (x >= WIDTH) x = 0;
    else if (x < 0) x = WIDTH - 1;
    if (y >= HEIGHT) y = 0;
    else if (y < 0) y = HEIGHT - 1;

    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y)
            gameover = 1;
    }

    // Check if the snake ate the food
    if (x == foodX && y == foodY) {
        score += 10;
        foodX = rand() % WIDTH;
        foodY = rand() % HEIGHT;
        nTail++;
    }
}
// Function to print game instructions
void printInstructions() {
    SetColor(4);
    printf("\n");
    printf("    *Welcome to the Classic Snake Game!\n");
    printf("                           SHIMAA FATHI\n\n");

    SetColor(2);// Set text color to white
    printf("\n");
    printf("\n");


    printf("    *Use arrow keys to control the snake.\n\n");
    printf("    *Eat the food (D) to grow and earn points.\n\n");
    printf("    *Avoid running into walls and yourself.\n\n");
    printf("    *Press 'x' to exit the game.\n\n");
    SetColor(4);// Set text color to white
    printf("\n");
    printf("\n");
    printf("    Press any key to start...");
    getch(); // Wait for user input before starting the game
}
// Function to display a loading screen
void showLoadingScreen() {
    clearScreen();
    SetColor(15); // Set text color to white
    printf("Loading");
    for (int i = 0; i < 3; i++) {
        Sleep(800); // Sleep for 800 milliseconds
        printf(".");
        fflush(stdout);
    }
    clearScreen();
}
// Function to display "Game Over"
void displayGameOver() {
    int consoleWidth = 80;
    int consoleHeight = 24;
    int centerX = (consoleWidth - 9) / 2; // Center "Game Over"
    int centerY = (consoleHeight - 1) / 2; // Center vertically

    gotoxy(centerX, centerY);
    SetColor(12); // Set text color to red
    printf("Game Over!");
    SetColor(15); // Set text color to white
}

int main() {
    printInstructions(); // Display instructions before starting the game
    showLoadingScreen(); // Display a loading screen
    system("cls");

    setup();
    clearScreen();

    // Hide the console cursor
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = 0; // Set to 0 for false (hide)
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    while (!gameover) {
        draw();
        input();
        logic();
        Sleep(1);  // Sleep for 1 milliseconds
    }

    // Display "Game Over" when the game is over
    displayGameOver();

    // Restore the console cursor when the game is over if needed
    cursorInfo.bVisible = 1; // Set to 1 for true (show)
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    // Wait for a key press to exit
    getch();

    return 0;
}


