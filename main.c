#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <conio.h>

/*-------function List Start------*/
void logOut();
void adminPanelHome();
void home();
void menuUI(char headingName[]);
void showUI();
void adminSignIn();
void adminSignUp();

/*-------Global Variable Section------*/
char current_user_admin[25];
char current_user_customer[25];

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
    char headingName[40] = "ADMIN PANEL AUTHENTICATION SYSTEM";
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
    char headingName[40] = "ADMIN PANEL AUTHENTICATION SYSTEM";
    menuUI(headingName);
    printCentered("Sign In", 10);
    printCentered("------------------------", 10);

    int found = 0;
    char userName[25];
    char userName1[25];
    char userPass[25];
    char userPass1[25];
    char userEmail[30];
    char userEmail1[30];

    printf("Enter UserName : ");
    scanf("%s", userName);
    printf("Enter Password : ");
    scanf("%s", userPass);

    // data received from file and cheak user authencity
    FILE *fp;
    fp = fopen("customer_data/data.txt", "r");

    while (fscanf(fp, "%s %s %s", userName1, userPass1, userEmail1) != EOF)
    {
        if (strcmp(userName, userName1) == 0 && strcmp(userPass, userPass1) == 0)
        {
            strcpy(current_user_admin, userName);
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (found) // user found
    {
        adminPanelHome();
    }

    else if (found == 0) // user not found
    {
        printf("\n\n");
        printCentered("Error userName or password.\n", 10);
        printCentered("1. Try Again.", 10);
        printCentered("    2. Reset Password.", 10);
        printCentered("      3. Authenticate Home.", 10);
        printCentered("  0. Exit Program.", 10);

        int option;
        printf("\n\nEnter your choice: ");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            adminSignIn();
            break;
        case 3:
            adminPanelAuthentication();
            break;
        case 0:
            system("cls");
            printCentered("Goodbye!", 12);
            break;
        default:
            printCentered("Invalid Choice!", 12);
            _getch();
            adminPanelAuthentication();
        }
    }
}
/*------------Admin Sign in END---------*/
//
//
//
/*------------Admin Sign Up Start---------*/
void adminSignUp()
{
    char headingName[40] = "ADMIN PANEL AUTHENTICATION SYSTEM";
    menuUI(headingName);
    printCentered("Registration", 10);
    printCentered("------------------------", 10);

    char userName[25];
    char userPass[25];
    char userEmail[30];
    printf("Enter UserName : ");
    scanf("%s", userName);
    printf("Enter Password : ");
    scanf("%s", userPass);
    printf("Enter Email    : ");
    scanf("%s", userEmail);

    // User data send to file
    FILE *fp;
    fp = fopen("customer_data/data.txt", "a");
    fprintf(fp, "%s %s %s\n", userName, userPass, userEmail);
    fclose(fp);
    printf("\n\n");
    printCentered("Registration is successfull.", 10);
    printCentered("press any key to login......", 10);

    _getch(); // to hold user
    adminSignIn();
}
/*------------Admin Sign Up END---------*/
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
    printCentered("\n\n\nPress 0 for Exits.", 10);
    int option;
    printf("\n\nEnter your choice: ");
    scanf("%d", &option);
    switch (option)
    {
    case 111:
        adminPanelAuthentication();
        break;
    case 0:
        system("cls");
        printCentered("Goodbye!", 12);
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
