#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <conio.h>

/*-------function List------*/
void logOut();
void adminPanelHome();
void home();
void menuUI(char headingName[]);
void showUI();
void adminSignIn();
void adminSignUp();
void adminPanelAuthentication();
void customerPanelAuthentication();
void customerSignIn();
void customerSignUp();

/*-------Global Variable Section------*/
char current_user_admin[25];
char current_user_customer[25];
int customerLoginStatus = 0;
//
//
//
/*------------------------This is for welcome page-----------------------------------------------*/
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

// its created for navber only
void printCentered2(const char *userName, const char *text, int color)
{
    int width = getConsoleWidth();
    int len = strlen(text);
    int len2 = strlen(userName);
    int space = (width - len) - (len2 + 6);

    setColor(color);
    printf("user: %s", userName);
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
/*-------------Main Program start from here----------------------------------------------*/
/*------------Admin Panel Authentication Start---------*/
void adminPanelAuthentication()
{
    char headingName[40] = "ADMIN PANEL AUTHENTICATION SYSTEM";
    menuUI(headingName);
    printf("\n\n");
    printCentered("1. Sign In.", 10);
    printCentered("2. Sign Up.", 10);
    printCentered("  3. Home Page.", 10);
    printCentered("     0. Exit Program.", 10);
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
/*------------Admin Panel Authentication END---------*/
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
    setColor(11);
    printf("Enter UserName : ");
    setColor(7);
    scanf("%s", userName);
    setColor(11);
    printf("Enter Password : ");
    setColor(7);
    scanf("%s", userPass);

    // data received from file and cheak user authencity
    FILE *fp;
    fp = fopen("admin_data/data.txt", "r");

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
        printCentered("Error userName or password.\n", 12);
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
/*-------------Admin Sign in END----------*/
//
//
//
/*----------------Admin Sign Up Start---------------*/
void adminSignUp()
{
    char headingName[40] = "ADMIN PANEL AUTHENTICATION SYSTEM";
    menuUI(headingName);
    printCentered("Registration", 10);
    printCentered("------------------------", 10);

    char userName[25];
    char userPass[25];
    char userEmail[30];

    setColor(11);
    printf("Enter UserName : ");
    setColor(7);
    scanf("%s", userName);
    setColor(11);
    printf("Enter Password : ");
    setColor(7);
    scanf("%s", userPass);
    setColor(11);
    printf("Enter Email    : ");
    setColor(7);
    scanf("%s", userEmail);

    // User data send to file
    FILE *fp;
    fp = fopen("admin_data/data.txt", "a");
    fprintf(fp, "%s %s %s\n", userName, userPass, userEmail);
    fclose(fp);
    printf("\n\n");
    printCentered("Registration is successfull.", 10);
    printCentered("press any key to login......", 10);

    _getch(); // to hold user
    adminSignIn();
}
/*---------------Admin Sign Up END-------------*/
//
//
//

void logOut()
{
    home(); // for user and admin
}
/*-----------------ADMIN PANEL START HOME----------------------*/
void adminPanelHome()
{
    char headingName[20] = "ADMIN PANEL";
    menuUI(headingName);

    // printCentered("OneMart", 10);
    // printCentered("-----------------", 10);
    char userName[20] = "mostakin";
    printCentered2(userName, "Home | Contact | About | Profile. ", 11);

    printf("\n\n\n");
    // operation List
    printCentered(" 1. Sales.                        2. Stock.                        3. Online Store.", 10);
    printf("\n");
    printCentered("        4. Accounts.                     5. Product Management.           6. Supplier Management.", 10);
    printf("\n");
    setColor(10);
    printCentered("     7. Admin Management.", 10);
    setColor(7);

    printf("\n\n\n\n\n\n\n\n\n");
    printCentered("Press 0 to logout_________________11 to EXIT", 4);
    int option;
    printf("\nEnter your choice: ", 10);
    scanf("%d", &option);

    switch (option)
    {
    case 0:
        // logOut();
        adminPanelAuthentication();
        break;
    case 11:
        system("cls");
        printCentered("Goodbye!", 12);
        break;
    default:
        printCentered("Invalid Choice!", 12);
        _getch();
        adminPanelHome();
    }
}
/*--------------------ADMIN PANEL HOME END------------------------*/
//
//
///*------------CUSTOMER Panel Authentication Start---------*/
void customerPanelAuthentication()
{
    char headingName[40] = "CUSTOMER AUTHENTICATION SYSTEM";
    menuUI(headingName);
    printf("\n\n");
    printCentered("1. Sign In.", 10);
    printCentered("2. Sign Up.", 10);
    printCentered(" 3. Home Page.", 10);
    printCentered("    0. Exit Program.", 10);
    int option;
    printf("\n\nEnter your choice: ");
    scanf("%d", &option);
    switch (option)
    {
    case 1:
        customerSignIn();
        break;
    case 2:
        customerSignUp();
        break;
    case 3:
        home();
        break;
    case 0:
        system("cls");
        printCentered("Goodbye!", 12);
        break;
    default:
        printCentered("Invalid Choice!", 12);
        _getch();
        customerPanelAuthentication();
    }
}
/*------------CUSTOMER Panel Authentication END---------*/
//
//
//
/*------------CUSTOMER SIGN UP START---------*/
void customerSignUp()
{
    char headingName[40] = "CUSTOMER AUTHENTICATION SYSTEM";
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
    customerSignIn();
}
/*------------CUSTOMER SIGN UP END----------------*/
//
//
//
/*------------CUSTOMER SIGN IN START---------*/
void customerSignIn()
{
    char headingName[40] = "CUSTOMER AUTHENTICATION SYSTEM";
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
            strcpy(current_user_customer, userName);
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (found) // user found
    {
        // use this function when we manage customer profile or order place
        // adminPanelHome();
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
            customerSignIn();
            break;
            // reset pass not yet done
        case 3:
            customerPanelAuthentication();
            break;
        case 0:
            system("cls");
            printCentered("Goodbye!", 12);
            break;
        default:
            printCentered("Invalid Choice!", 12);
            _getch();
            customerPanelAuthentication();
        }
    }
}
/*----------------CUSTOMER SIGN IN END------------*/
//
//
///*-----------------2nd HOME START----------------------*/

void home2()
{
    char headingName[10] = "OneMart";
    menuUI(headingName);
    printf("\n\n\n\n\n\n\n\n");
    printCentered("Are you admin?", 15);
    printCentered(" 1. YES", 11);
    printCentered("2. NO", 12);

    int option;
    printf("\n\n\nEnter your choice: ");
    scanf("%d", &option);
    switch (option)
    {
    case 1:
        adminPanelAuthentication();
        break;
    case 2:
        home();
        break;
    default:
        printCentered("Invalid Choice!", 12);
        _getch();
        home2();
    }
}
///*-----------------2nd HOME END----------------------*/
/*-----------------HOME START----------------------*/
void home()
{
    char headingName[10] = "HOME";
    menuUI(headingName);

    char userName[20] = "mostakin";
    printCentered2(userName, "Home | Contact | About | Profile. ", 11);
    printf("\n\n\n\n\n\n\n\n\n\n");
    printCentered("Press 11 for customer panel.", 10);
    printCentered("Press 0 for Exits.", 10);
    int option;
    printf("\nEnter your choice: ");
    scanf("%d", &option);
    switch (option)
    {
    case 11:
        customerPanelAuthentication();
        break;
    case 0:
        system("cls");
        printCentered("Goodbye!", 12);
        break;
    default:
        printCentered("Invalid Choice!", 12);
        _getch();
        home();
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
        home2();
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

//      g++ main.c && ./a.exe
// tonmoy 2
// mostakin
// tonmoy

//shafat