#include <stdio.h>
#include <windows.h>
#include <string.h>

/*-------function List Start------*/
void logOut();
void adminPanelHome();
void home();
void menuUI(char headingName[]);
void showUI();
void adminSignIn();
void adminSignUp();

/*-------function List END------*/
//
//
//
/*-------------This is for welcome page------------------------------*/
// Function to set text color
void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Function to get terminal width
int getConsoleWidth()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

// Function to print centered text
void printCentered(const char *text, int color)
{
    int width = getConsoleWidth();
    int len = strlen(text);
    int space = (width - len) / 2;

    setColor(color);
    for (int i = 0; i < space; i++)
        printf(" ");
    printf("%s\n", text);
    setColor(7); // Reset color
}

// Draw top/bottom border
void drawBorderLine(char ch)
{
    int width = getConsoleWidth();
    for (int i = 0; i < width; i++)
        printf("%c", ch);
    printf("\n");
}

// Main UI function
void showUI()
{
    system("cls");

    drawBorderLine('=');
    printCentered("Welcome to Our Stock & Inventory Management System App!", 11); // Cyan
    drawBorderLine('=');

    printf("\n\n");
    printCentered(" [1] Start", 10); // Green
    printCentered("[2] Help", 14);   // Yellow
    printCentered("[3] Exit", 12);   // Red

    printf("\n\n");
    drawBorderLine('=');
    printCentered("Use number keys to select.", 8);
    drawBorderLine('=');
}
// for heading only
void menuUI(char headingName[])
{
    system("cls");
    drawBorderLine('=');
    printCentered(headingName, 11);
    drawBorderLine('=');
    // drawBorderLine('=');
    // drawBorderLine('=');
}
/*-------------welcome page END-------------*/
//
//
//
/*-------------Main Program start from here---------*/
/*------------Admin Panel Authentication Start---------*/
void adminPanelAuthentication()
{
    char headingName[30] = "ADMIN PANEL AUTHENTICATION";
    menuUI(headingName);
    printf("\n\n");
    printCentered("1. Sign In.", 10);
    printCentered("2. Sign Up.", 10);
    printCentered(" 3. Home Page.", 10);
    int option;
    printf("\n\nEnter your choice: ");
    scanf("%d", &option);
    switch (option)
    {
    case 1:
        adminSignIn();
        break;
    case 2:
        adminSignUp();
        break;
    case 3:
        home();
        break;
    default:
        printCentered("Invalid Choice!", 12);
        adminPanelAuthentication();
    }
}
/*------------Admin Panel Authentication Start---------*/
//
//
//
/*------------Admin Sign in Start---------*/
void adminSignIn()
{
}
/*------------Admin Sign in Start---------*/
//
//
//
/*------------Admin Sign Up Start---------*/
void adminSignUp()
{
}
/*------------Admin Sign Up Start---------*/
//
//
//

void logOut()
{
    home(); // for user and admin
}
/*-----------------ADMIN PANEL START----------------------*/
void adminPanelHome()
{
    char headingName[20] = "ADMIN PANEL";
    menuUI(headingName);
    printCentered("\n\n\nPress 0 logout.", 10);
    int option;
    printf("\n\nEnter your choice: ");
    scanf("%d", &option);
    switch (option)
    {
    case 0:
        logOut();
        break;
    default:
        printCentered("Invalid Choice!", 12);
    }
}
/*-----------------ADMIN PANEL END----------------------*/
//
//
//
/*-----------------HOME START----------------------*/
void home()
{
    char headingName[10] = "HOME";
    menuUI(headingName);

    printCentered("\n\n\nPress 111 for admin panel.", 10);
    int option;
    printf("\n\nEnter your choice: ");
    scanf("%d", &option);
    switch (option)
    {
    case 111:
        adminPanelAuthentication();
        break;
    default:
        printCentered("Invalid Choice!", 12);
    }
}
/*-----------------HOME END----------------------*/
//
//
//
/*-----------------MAIN FUNCTION START----------------------*/
int main()
{
    showUI(); // for welcome page only

    int choice;
    printf("\n\nEnter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        system("cls");
        home();
        // printCentered("You chose to Start!", 10);
        break;
    case 2:
        system("cls");
        printCentered("Help Section Coming Soon!", 14);
        break;
    case 3:
        system("cls");
        printCentered("Goodbye!", 12);
        break;
    default:
        printCentered("Invalid Choice!", 12);
        main();
    }

    return 0;
}
/*-----------------MAIN FUNCTION END----------------------*/
