#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

#define WIDTH 20
#define HEIGHT 15

char userInput, name[30], word, control, save, resumeKey;
int score = 0, gameover = 0;
int length, data, print,check;
int i, j, k;
int headX, headY, tailX[100], tailY[100], fruitX, fruitY;
int prevX, prevY, prev2X, prev2Y;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN };
enum eDirecton dir;

// Function to display the front screen
void frontpage()
{
    system("cls");
    printf("==========================================================================\n\n\n\n");
    printf("\t\t\t       SNAKE GAME\n\n");
    printf("\t\t\t Press any key to start.\n\n\n\n");
    printf("==========================================================================\n");
}

// Function to display the main menu
void showMenu() 
{
    printf("============================ Snake Game Menu =============================\n\n\n");
    printf("\t\t\t\t1. Play\n\n");
    printf("\t\t\t\t2. History\n\n"); 
    printf("\t\t\t\t3. Quit Game\n\n\n");
    printf("==========================================================================\n");
}

// Function to check if there is more than 20 charactors
void checkname()
{
   fgets(name,30,stdin);
   if(strlen(name) > 21)
   {
    system("cls");
    printf("=========================================================================\n");
    printf("Limit has Exceeded! Please enter the name again!\n");
    printf("Player name:- \nLimit: upto 20 characters \nEnter your name: ");
    checkname();
    return;
   }   
}

// Function to display the rules to play the game
void gamerules()
{
    printf("================================= Rules =================================\n\n");
    printf("1. Control the Snake: Use keys (W,A,S,D) to steer.\n\n");
    printf("2. Eat Fruits: Devour the fruit ' * ' for points.\n\n");
    printf("3. Avoid Collisions: Stay clear of snake's tail.\n\n");
    printf("4. Score Points: Each ' * ' adds 10.\n\n");
    printf("5. Game Over: Collision with snake's tails ends it.\n\n");
    printf("6. Restart: Hit ' R ' to try again.\n\n");              
    printf("=========================================================================\n");
    printf("\t\t\tPress any key to go to menu.\n");
}

// Function to draw a loading screen
void loadScreen() {
    for(i = 0; i != 5; i++)
    {
        system("cls");
        printf("=========================================================================\n\n\n\n\n");
        printf("\t\t\tLoading the game");
        for(j = 0; j <= i; j++) 
        {
            printf(".");
        }   
        printf("\n\n\n\n\n=========================================================================\n"); 
        Sleep(300);   
    }
}

// Function to generate the fruit position
void generateFruit() 
{
    check = 0;
    do 
    {
        check = 0;
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;

        // Check if fruit position coincides with any part of the snake
        if (fruitX == headX && fruitY == headY)
            check = 1;
        for ( i = 0; i < length; i++) 
        {
            if (fruitX == tailX[i] && fruitY == tailY[i]) 
            {
                check = 1;
                break;
            }
        }
    } while (check);
}

// Function to initialize the game state
void setup() 
{
    gameover = 0;
    dir = STOP;
    headX = WIDTH / 2;
    headY = HEIGHT / 2;
    score = 0;
    length = 0;
    // Generate the initial fruit position
    generateFruit();
}

// Function to draw the game screen
void draw() 
{
    system("cls");
     printf("      Snake Game\n");
    if (!gameover) 
    {
        for (i = 0; i < WIDTH + 2; i++)
            printf("-");// Draw the top border
        printf("\n");

        // Draw the game area
        for (i = 0; i < HEIGHT; i++) 
        {
            for (j = 0; j < WIDTH; j++) 
            {
                if (j == 0)
                    printf("|");  // Draw the left borders
                if (i == headY && j == headX)
                    printf("O");  // Draw the snake's head
                else if (i == fruitY && j == fruitX)
                    printf("*");  // Draw the fruit
                else 
                {
                    print = 0;
                    for (k = 0; k < length; k++) 
                    {
                        if (tailX[k] == j && tailY[k] == i)
                         {
                            printf("o");  // Draw the snake's tail
                            print = 1;
                        }
                    }
                    if (!print)
                        printf(" ");  // Draw empty space
                }
                if (j == WIDTH - 1)
                    printf("|");  //Draw the right border
            }
            printf("\n");
        }
        for (i = 0; i < WIDTH + 2; i++)
            printf("-");// Draw the bottom border
        printf("\n");

        // Display the score and instructions
        printf("Player name: %s\n",name);
        printf("Score:%d\n", score);
        printf("Press 'Esc' to pause the game.\n");
    } 
}

// Function to handle user input
void input() 
{
    if (_kbhit()) 
    {
        control = getch();
        switch (control) 
        {
        case 'a':
        case 'A':
            if (dir != RIGHT)
                dir = LEFT;    // Move Left
            else if(length==0)
                dir = LEFT;
            break;
        case 'd':
        case 'D':
            if (dir != LEFT)  
                dir = RIGHT;   // Move Right
            else if(length==0)
                dir = RIGHT;    
            break;
        case 'w':
        case 'W':
            if (dir != DOWN)  
                dir = UP;      // Move Up
            else if(length==0)
                dir = UP;    
            break;
        case 's':
        case 'S':
            if (dir != UP)  
                dir = DOWN;    // Move Down
            else if(length==0)
                dir = DOWN;    
            break;

        case 27 :
            while (1) {
                system("cls");
                printf("============================== Game Paused ===============================\n\n\n");
                printf("\t\t\t\t1. Resume\n\n");
                printf("\t\t\t\t2. Restart\n\n"); 
                printf("\t\t\t\t3. Quit\n\n\n");
                printf("==========================================================================\n");
                
                if (_kbhit()) 
                {
                    resumeKey= getch();
                    if (resumeKey == '1' || resumeKey == 27) 
                    {
                        break; // Resume the game
                    } 
                    else if (resumeKey == '2') 
                    {
                        setup(); // Restart the game
                        break;
                    } 
                    else if (resumeKey == '3' || resumeKey == 'X') 
                    {
                        gameover = 1; // Quit the game
                        break;
                    }
                }
                Sleep(100);
            }
            break;
        default:
            break;
        }
    }
}

// Function to update the game state based on the game logic
void algorithm() 
{
    prevX = tailX[0];
    prevY = tailY[0];
    tailX[0] = headX;
    tailY[0] = headY;
    // Update the positions of the snake's tail
    for (i = 1; i < length; i++) 
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    // Update the position of the snake's head based on the current direction
    switch (dir) 
    {
    case LEFT:
        headX--;
        break;
    case RIGHT:
        headX++;
        break;
    case UP:
        headY--;
        break;
    case DOWN:
        headY++;
        break;
    default:
        break;
    }
    // Handle border wrapping
    if (headX >= WIDTH)
        headX = 0;
    else if (headX < 0)
        headX = WIDTH - 1;
    if (headY >= HEIGHT)
        headY = 0;
    else if (headY < 0)
        headY = HEIGHT - 1;
    // Check for collisions with the snake's tail
    for (i = 0; i < length; i++)
        if (tailX[i] == headX && tailY[i] == headY)
            gameover = 1;
    // Check if the snake eats the fruit
    if (headX == fruitX && headY == fruitY) 
    {
        score += 10;
        generateFruit(); // Generate new fruit position
        length++;
    }
}

// Function to save the score to a file
void saveScoreToFile() 
{   
    printf("\n\t\tWould you like to save the score(y/n)?");
    printf("\n\n\n\n=========================================================================\n");
    save = getch();
    switch(save)
    {
    case 'y':
    case 'Y':
        system("cls");
        FILE *file = fopen("history.txt", "a");
        if (file != NULL) 
        {
            fprintf(file, "Name : %s \nScore: %d\n\n",name,score);
            fclose(file);
        }
        printf("=========================================================================\n\n\n\n");
        printf("\t\t\t  Score has been saved.\n\n");
        break;
    case 'n':
    case 'N':
        system("cls");
        printf("=========================================================================\n\n\n\n");
        printf("\t\t\tScore has not been saved.\n\n");
        break;
    default:
        system("cls");
        printf("=========================================================================\n\n\n\n");        
        printf("\t\t   Game Over! You scored %d points.\n", score);
        saveScoreToFile();
        break;    
    }
}

// Function to view the game history
void viewHistory() 
{
    FILE *file = fopen("history.txt", "r");
    if (file != NULL) 
    {
        printf("========== Game History ==========\n\n");
        while ((data = fgetc(file)) != EOF) 
        {   
            putchar(data);
        }
        fclose(file);
        printf("==================================\n");
        printf("Press any key to go to menu.\n");
    } 
    else 
    {
        printf("=========================================================================\n\n\n\n");
        printf("\t\t            No history found.\n\n");
        printf("\t\t       Press any key to go to menu.\n\n\n\n");
        printf("=========================================================================\n");
    }
}

// Function to quit the program
void quit() {
    for(i = 0; i != 5; i++)
    {
        system("cls");
        printf("=========================================================================\n\n\n\n\n");
        printf("\t\t\tExiting the game");
        for(j = 0;j <= i; j++)
        {
            printf(".");
        }
        printf("\n\n\n\n\n=========================================================================\n"); 
        Sleep(500);   
    }
}

// Main function
int main() 
{
    system("cls");
    frontpage();
    getch();
    system("cls");
    srand(GetTickCount()); //To avoid predicting outcomes
    do 
    {
        showMenu();
        userInput = getch();
        switch (userInput) 
        {
        case '1':
            system("cls");
            printf("=========================================================================\n");
            printf("Player name:- \nLimit: upto 20 characters \nEnter your name: ");
            checkname();
            name[strcspn(name,"\n")]='\0';
            system("cls");
            gamerules();
            getch();
            system("cls");
            loadScreen();
            system("cls");
            setup();  // Initialize the game
            // Main game loop
            while (!gameover) 
            {
                draw();
                input();
                algorithm();
                Sleep(100);
            }
            system("cls");
            if(score!=0)
            {
                printf("=========================================================================\n\n\n\n");
                printf("\t\t   Game Over! You scored %d points.\n", score);
                saveScoreToFile(); // Save score to history after gameover
                printf("\t\t\t Press any key to start.\n\n\n\n");
                printf("=========================================================================\n");
                getch();
            }
            system("cls");
            break;
        case '2':
            system("cls");
            viewHistory();  // View game history
            getch();
            system("cls");
            break;
        case '3':
            quit(); // Exit
            break;
        default:
            system("cls");
            break;
        }

    } while (userInput != '3');
    return 0;
}