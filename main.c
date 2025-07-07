#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

/*-------function List------*/
void dateTime();
void logOut();
void adminPanelHome();
void home();
void menuUI(char headingName[]);
void showUI();

void adminSignIn(); // 1. Authorization & Authentication
void adminSignUp();
void adminPanelAuthentication();
void customerPanelAuthentication();
void customerSignIn();
void customerSignUp();

void adminPanelSales(); // 2. Admin Panel Sales - HOME
void newSales();
void salesHistory();
void searchSaleProduct();

void adminPanelStock(); // 3. Admin Panel Stock - Home
void AddNewProduct();
void deleteProduct();
void listOfProduct();
void stockCheak();
void updateStock();
void stockListByCategory();

void adminPanelOnlineStore(); // 4. Admin Panel Online Store - Home
void orderPendingList();
void orderDeliveredList();

void adminPanelAccounts(); // 5. Admin Panel Accounts - Home
void dailyIncome();
void monthlyIncome();
void HalfYearlyIncome();
void yearlyIncome();

void adminPanelSupplierManagement(); // 6. Admin Panel Supplier Management- Home
void addSupplier();
void deleteSupplier();
void productSearch();
void listOfProductBySupplier();

void adminPanelUserManagement(); // 6. Admin Panel User Management- Home
void addAdmin();
void deleteAdmin();
void adminPasswordReset();
void listOfAdmin();
void addCustomer();
void deleteCustomer();
void customerPasswordReset();
void listOfCustomer();

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
//
//
//
/*------------Date Time Start---------*/
void dateTime()
{
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    int width = getConsoleWidth();
    int len = 22;
    int len2 = 17;
    int space = (width - len - len2);

    setColor(10);
    printf("Live Time: %02d:%02d", t->tm_hour, t->tm_min);
    // printf("Live Time: %02d:%02d:%02d", t->tm_hour, t->tm_min, t->tm_sec);
    for (int i = 0; i <= space; i++)
    {
        printf(" ");
    }
    printf("Date: %04d-%02d-%02d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);
    setColor(7); // Reset color
}
/*------------Date Time END---------*/
//
//
//
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
        printCentered("      2. Reset Password.", 10);
        printCentered("        3. Authenticate Home.", 10);
        printCentered("   0. Exit Program.", 10);

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
//
/*-----------------ADMIN PANEL HOME START----------------------*/
void adminPanelHome() // DashBoard
{
    char headingName[20] = "ADMIN PANEL";
    menuUI(headingName);

    // printCentered("OneMart", 10);
    // printCentered("-----------------", 10);
    char userName[20] = "mostakin";
    printCentered2(userName, "Home | Contact | About | Profile. ", 11);

    printf("\n\n\n");
    printCentered("Stock & Inventory Management System", 11);
    printCentered("---------------------------------------------------------------------------------", 11);
    // operation List
    printCentered(" 1. Sales.                        2. Stock.                        3. Online Store.", 10);
    printf("\n");
    printCentered("    4. Accounts.                     5. Supplier Management.          6. User Management.", 10);
    printf("\n");

    printf("\n\n\n\n\n\n\n\n\n");
    dateTime();
    // printCentered("Press 0 to logout_________________11 to EXIT", 4);
    printCentered("             Press 0 to logout_______________11 to EXIT", 4);
    int option;
    printf("\nEnter your choice: ", 10);
    scanf("%d", &option);

    switch (option)
    {
    case 0:
        // logOut();
        adminPanelAuthentication();
        break;

    case 1:
        // Sales page
        adminPanelSales();
        break;

    case 2:
        // Stock page
        adminPanelStock();
        break;

    case 3:
        // Online Store page
        adminPanelOnlineStore();
        break;

    case 4:
        // Accounts page
        adminPanelAccounts();
        break;

    case 5:
        // Accounts page
        adminPanelSupplierManagement();
        break;

    case 6:
        // User page
        adminPanelUserManagement();
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
//
//*---------------Admin Panel sales start----------------*/
void adminPanelSales() // HOME
{
    char headingName[40] = "SALES";
    menuUI(headingName);
    char userName[20] = "mostakin";
    printCentered2(userName, "Home | Contact | About | Profile. ", 11);
    printf("\n\n");
    printCentered("OneMart", 10);
    printCentered("------------------------", 10);
    printf("\n");
    printCentered("Sales", 15);
    printCentered("------------------------", 15);
    printCentered("1. New Sale", 15);
    printCentered("     2. Sales History", 15);
    printCentered("           3. Search Sale Product", 15);
    printCentered("  0. Admin Home", 4);
    printf("\n\n\n");

    int option;
    printf("\n\nEnter your choice: ");
    scanf("%d", &option);
    switch (option)
    {
    case 1:
        newSales();
        break;
        // yet not done
    case 2:
        salesHistory();
        break;
        // yet not done
    case 3:
        searchSaleProduct();
        break;
        // yet not done
    case 0:
        adminPanelHome();
        break;
    default:
        printCentered("Invalid Choice!", 12);
        printCentered("Press any key", 10);
        _getch();
        adminPanelSales();
    }
}
//*---------------Admin Panel Sales End ----------------*/
//
//
//
//*---------------Admin Panel New Sales Start----------------*/
void newSales()
{
}
//*---------------Admin Panel New Sales End----------------*/
//
//
//
//*---------------Admin Panel Sales History Start----------------*/
void salesHistory()
{
}
//*---------------Admin Panel Sales History End----------------*/
//
//
//
/*---------------Admin Panel Search Sales Procduct Start----------------*/
void searchSaleProduct()
{
}
//*---------------Admin Panel Search Sales Product End----------------*/
//
//
//
//*---------------Admin Panel Stock start----------------*/
void adminPanelStock() // HOME
{
    char headingName[40] = "Stock / Product";
    menuUI(headingName);
    char userName[20] = "mostakin";
    printCentered2(userName, "Home | Contact | About | Profile. ", 11);
    printf("\n\n");
    printCentered("OneMart", 10);
    printCentered("------------------------", 10);
    printf("\n");
    printCentered("Stock & Product", 15);
    printCentered("------------------------", 15);
    printCentered("          1. Add New Product.", 15);
    printCentered("         2. Delete Product.", 15);
    printCentered("          3. List Of Product.", 15);
    printCentered("      4. Stock Cheak.", 15);
    printCentered("       5. Update Stock.", 15);
    printCentered("                 6. Stock List by Category.", 15);
    printCentered("     0. Admin-Home.", 4);
    printf("\n\n\n");

    int option;
    printf("\n\nEnter your choice: ");
    scanf("%d", &option);
    switch (option)
    {
    case 1:
        AddNewProduct();
        break;
        // yet not done
    case 2:
        deleteProduct();
        break;
        // yet not done
    case 3:
        listOfProduct();
        break;
    // yet not done
    case 4:
        stockCheak();
        break;
    // yet not done
    case 5:
        updateStock();
        break;
        // yet not done
    case 6:
        stockListByCategory();
        break;
        // yet not done
    case 0:
        adminPanelHome();
        break;
    default:
        printCentered("Invalid Choice!", 12);
        printCentered("Press any key", 10);
        _getch();
        adminPanelSales();
    }
}
//*---------------Admin Panel Stock End ----------------*/
//
//
//
//*---------------Admin Panel Add New Product Start----------------*/
void AddNewProduct()
{
}
//*---------------Admin Panel Add New Product End----------------*/
//
//
//
//*---------------Admin Panel Delete Product Start----------------*/
void deleteProduct()
{
}
//*---------------Admin Panel Delete Product End----------------*/
//
//
//
/*---------------Admin Panel List Of Product Start----------------*/
void listOfProduct()
{
}
//*---------------Admin Panel List Of Product End----------------*/
//
//
//
/*---------------Admin Panel stock Cheak Start----------------*/
void stockCheak()
{
}
//*---------------Admin Panel stock Cheak End----------------*/
//
//
//
/*---------------Admin Panel Update Stock Start----------------*/
void updateStock()
{
}
//*---------------Admin Panel Update Stock End----------------*/
//
//
//
/*---------------Admin Panel Stock List By Category Start----------------*/
void stockListByCategory()
{
}
//*---------------Admin Panel Stock List By Category End----------------*/
//
//
//
//*---------------Admin Panel Online Store start----------------*/
void adminPanelOnlineStore() // HOME
{
    char headingName[40] = "Admin Panel - Online Store";
    menuUI(headingName);
    char userName[20] = "mostakin";
    printCentered2(userName, "Home | Contact | About | Profile. ", 11);
    printf("\n\n");
    printCentered("OneMart", 10);
    printCentered("------------------------", 10);
    printf("\n");
    printCentered("Online Store", 15);
    printCentered("-------------------------------", 15);
    printCentered("          1. Order Pending List", 15);
    printCentered("            2. Order Delivered List", 15);
    printCentered("  0. Admin-Home", 4);
    printf("\n\n\n");

    int option;
    printf("\n\nEnter your choice: ");
    scanf("%d", &option);
    switch (option)
    {
    case 1:
        orderPendingList();
        break;
        // yet not done
    case 2:
        orderDeliveredList();
        break;
        // yet not done
    case 0:
        adminPanelHome();
        break;
    default:
        printCentered("Invalid Choice!", 12);
        printCentered("Press any key", 10);
        _getch();
        adminPanelSales();
    }
}
//*---------------Admin Panel  Online Store End ----------------*/
//
//
//
//*---------------Admin Panel(Online Store) Order Pending List Start----------------*/
void orderPendingList()
{
}
//*---------------Admin Panel (Online Store) Order Pending List End----------------*/
//
//
//
//*---------------Admin Panel (Online Store) Order Delivered List Start----------------*/
void orderDeliveredList()
{
}
//*---------------Admin Panel (Online Store) Order Delivered List End----------------*/
//
//
//
//*---------------Admin Panel Online Store start----------------*/
void adminPanelAccounts() // HOME
{
    char headingName[40] = "Admin Panel - Accounts";
    menuUI(headingName);
    char userName[20] = "mostakin";
    printCentered2(userName, "Home | Contact | About | Profile. ", 11);
    printf("\n\n");
    printCentered("OneMart", 10);
    printCentered("------------------------", 10);
    printf("\n");
    printCentered("Accounts", 15);
    printCentered("------------------------", 15);
    printCentered("  1. Daily Income", 15);
    printCentered("     2. Monthly Income", 15);
    printCentered("        3. Half Yearly Income", 15);
    printCentered("    4. Yearly Income", 15);
    printCentered(" 0. Admin-Home", 4);
    printf("\n\n\n");

    int option;
    printf("\n\nEnter your choice: ");
    scanf("%d", &option);
    switch (option)
    {
    case 1:
        dailyIncome();
        break;
        // yet not done
    case 2:
        monthlyIncome();
        break;
    // yet not done
    case 3:
        HalfYearlyIncome();
        break;
    // yet not done
    case 4:
        yearlyIncome();
        break;
        // yet not done
    case 0:
        adminPanelHome();
        break;
    default:
        printCentered("Invalid Choice!", 12);
        printCentered("Press any key", 10);
        _getch();
        adminPanelSales();
    }
}
//*---------------Admin Panel  Online Store End ----------------*/
//
//
//
//*---------------Admin Panel (Accounts) Daily Income Start----------------*/
void dailyIncome()
{
}
//*---------------Admin Panel (Accounts) Daily Income End----------------*/
//
//
//
//*---------------Admin Panel (Accounts) Monthly Income Start----------------*/
void monthlyIncome()
{
}
//*---------------Admin Panel (Accounts) Monthly Income End----------------*/
//
//
//
//*---------------Admin Panel (Accounts) Half Yearly Income Start----------------*/
void HalfYearlyIncome()
{
}
//*---------------Admin Panel (Accounts) Half Yearly Income End----------------*/
//
//
//
//*---------------Admin Panel (Accounts) Yearly Income Start----------------*/
void yearlyIncome()
{
}
//*---------------Admin Panel (Accounts) Yearly Income End----------------*/
//
//
//
//*---------------Admin Panel Supplier Management start----------------*/
void adminPanelSupplierManagement() // HOME
{
    char headingName[40] = "Supplier Management";
    menuUI(headingName);
    char userName[20] = "mostakin";
    printCentered2(userName, "Home | Contact | About | Profile. ", 11);
    printf("\n\n");
    printCentered("OneMart", 10);
    printCentered("------------------------", 10);
    printf("\n");
    printCentered("Supplier Management", 15);
    printCentered("------------------------", 15);
    printCentered("   1. Add Supplier", 15);
    printCentered("      2. Delete Supplier.", 15);
    printCentered("    3. Product Search", 15);
    printCentered("                 4. List Of Product by Supplier", 15);
    printCentered("  0. Admin-Home.", 4);
    printf("\n\n\n");

    int option;
    printf("\n\nEnter your choice: ");
    scanf("%d", &option);
    switch (option)
    {
    case 1:
        addSupplier();
        break;
        // yet not done

    case 2:
        deleteSupplier();
        break;
        // yet not done

    case 3:
        productSearch();
        break;
        // yet not done

    case 4:
        listOfProductBySupplier();
        break;
        // yet not done

    case 0:
        adminPanelHome();
        break;
    default:
        printCentered("Invalid Choice!", 12);
        printCentered("Press any key", 10);
        _getch();
        adminPanelSales();
    }
}
//*---------------Admin Panel Supplier Management End ----------------*/
//
//
//
//*---------------Admin Panel (Supplier) Add Supplier Start----------------*/
void addSupplier()
{
}
//*---------------Admin Panel (Supplier) Add Supplier End----------------*/
//
//
//
//*---------------Admin Panel (Supplier) Delete Supplier Start----------------*/
void deleteSupplier()
{
}
//*---------------Admin Panel (Supplier) Delete Supplier End----------------*/
//
//
//
//*---------------Admin Panel (Supplier) Product Search Start----------------*/
void productSearch()
{
}
//*---------------Admin Panel (Supplier) Product Search End----------------*/
//
//
//
//*---------------Admin Panel (Supplier) List Of Product By Supplier Start----------------*/
void listOfProductBySupplier()
{
}
//*---------------Admin Panel (Supplier) List Of Product By Supplier End----------------*/
//
//
//
//*---------------Admin Panel User Management start----------------*/
void adminPanelUserManagement() // HOME
{
    char headingName[40] = "User Management";
    menuUI(headingName);
    char userName[20] = "mostakin";
    printCentered2(userName, "Home | Contact | About | Profile. ", 11);
    printf("\n\n");
    printCentered("OneMart", 10);
    printCentered("------------------------", 10);
    printf("\n");
    printCentered("    Admin Management                      Customer Management", 11);
    printCentered("           ---------------------------           --------------------------", 11);
    printCentered(" 1. Add Admin                          5. Add Customer", 15);
    printCentered("    2. Delete Admin                       6. Delete Customer", 15);
    printCentered("  3. Password Reset                     7. Password Reset", 15);
    printCentered("    4. List Of Admin                      8. List Of Customer", 15);
    printf("\n");
    printCentered("0. Admin-Home.", 4);
    printf("\n\n\n");

    int option;
    printf("\n\nEnter your choice: ");
    scanf("%d", &option);
    switch (option)
    {
    case 1:
        addAdmin();
        break;
        // yet not done

    case 2:
        deleteAdmin();
        break;
        // yet not done

    case 3:
        adminPasswordReset();
        break;
        // yet not done

    case 4:
        listOfAdmin();
        break;
        // yet not done
    case 5:
        addCustomer();
        break;
        // yet not done

    case 6:
        deleteCustomer();
        break;
        // yet not done

    case 7:
        customerPasswordReset();
        break;
        // yet not done

    case 8:
        listOfCustomer();
        break;
        // yet not done

    case 0:
        adminPanelHome();
        break;
    default:
        printCentered("Invalid Choice!", 12);
        printCentered("Press any key", 10);
        _getch();
        adminPanelSales();
    }
}
//*---------------Admin Panel Supplier Management End ----------------*/
//
//
//
//*---------------Admin Panel (USER) Add Admin Start----------------*/
void addAdmin()
{
}
//*---------------Admin Panel (USER) Add Admin End----------------*/
//
//
//
//*---------------Admin Panel (USER) Delete Admin Start----------------*/
void deleteAdmin()
{
}
//*---------------Admin Panel (USER) Delete Admin End----------------*/
//
//
//
//*---------------Admin Panel (USER) Admin Pass Reset Start----------------*/
void adminPasswordReset()
{
}
//*---------------Admin Panel (USER) Admin Pass Reset End----------------*/
//
//
//
//*---------------Admin Panel (USER) Admin List Start----------------*/
void listOfAdmin()
{
}
//*---------------Admin Panel (USER) Admin List End----------------*/
//
//
//
//*---------------Admin Panel (USER) Add Customer Start----------------*/
void addCustomer()
{
}
//*---------------Admin Panel (USER) Admin Pass Reset End----------------*/
//
//
//
//*---------------Admin Panel (USER) Delete Customer Start----------------*/
void deleteCustomer()
{
}
//*---------------Admin Panel (USER) Delete Customer End----------------*/
//
//
//
//*---------------Admin Panel (USER) Customer Pass Reset Start----------------*/
void customerPasswordReset()
{
}
//*---------------Admin Panel (USER) Customer Pass Reset End----------------*/
//
//
//
//*---------------Admin Panel (USER) Customer List Start----------------*/
void listOfCustomer()
{
}
//*---------------Admin Panel (USER) Customer List End----------------*/
//
//
//
///*-----------------2nd HOME START----------------------*/
void home2() // Admin or not
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
//*-----------------2nd HOME END----------------------*/
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
// tonomoy
// mostakin