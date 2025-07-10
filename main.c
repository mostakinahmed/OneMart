#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

/*-------Extra function List------*/
void dateTime();
void adminPanelHome();
void OnlineHome();
void menuUI(char headingName[]);
void showUI();
void allProductData();

void adminSignIn(); // 1. Authorization & Authentication
void adminSignUp();
void adminPanelAuthentication();
void customerPanelAuthentication();
void customerSignIn();
void customerSignUp();
void adminLogOut();

void adminPanelSales(); // 2. Admin Panel Sales - HOME
void newSales();
void salesHistory();
void searchSaleProduct();

void adminPanelStock(); // 3. Admin Panel Product/Stock - Home
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
void supplierList();
void supplierLatestData();

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
int adminLoginStatus = 0;

/*-------Global Structure Section------*/
struct product
{
    int pID;
    int proSupID; // pruduct supplier ID
    char pCat[15];
    char pName[20];
    int pPrice;
    int pUnit;
};
struct product allProduct[500];
struct product allProductCatList[500];

struct supplier
{
    int supplierID;
    char supName[20];
    char supPhn[15];
    char supCompName[25];
};
struct supplier supplierData[100];
// mark
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

void printCenteredID(const int id, int color)
{
    int width = getConsoleWidth();
    // int len = strlen(id);
    int space = (width - 5) / 2;

    setColor(color);
    for (int i = 0; i < space; i++)
        printf(" ");
    printf("SKU   : %d\n", id);
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
    printCentered("     0. Exit Program.", 4);
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
        OnlineHome();
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
    char current_user_admin2[25];
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

            // update login status
            adminLoginStatus = 1;
            FILE *fp;
            fp = fopen("login_Logout_status/logData.txt", "w");
            fprintf(fp, "%d", adminLoginStatus);
            fclose(fp);
            // update current admin name
            strcpy(current_user_admin2, userName);
            fp = fopen("admin_data/current_user_admin.txt", "w");
            fprintf(fp, "%s", current_user_admin2);
            fclose(fp);
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
void adminLogOut()
{
    FILE *fp;
    customerLoginStatus = 0;
    fp = fopen("login_Logout_status/logData.txt", "w");
    fprintf(fp, "%d", customerLoginStatus);
    fclose(fp);
    adminPanelAuthentication(); // for admin
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
        OnlineHome();
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
    FILE *fp;
    fp = fopen("admin_data/current_user_admin.txt", "r");
    fscanf(fp, "%s", current_user_admin);
    fclose(fp);
    // 2nd menu ui
    printCentered2(current_user_admin, "Home | Contact | About | Profile. ", 11);

    printCentered("OneMart", 10);
    printCentered("-----------------", 10);
    printf("\n\n\n");
    printCentered("Stock & Inventory Management System", 11);
    printCentered("---------------------------------------------------------------------------------", 11);

    // Operation List
    printCentered(" 1. Sales.                        2. Stock.                        3. Online Store.", 10);
    printf("\n");
    printCentered("    4. Accounts.                     5. Supplier Management.          6. User Management.", 10);
    printf("\n");
    printf("\n\n\n\n\n\n\n\n\n");

    dateTime(); // for date and time
    printCentered("             Press 0 to logout_______________11 to EXIT", 4);

    int option;
    printf("\nEnter your choice: ", 10);
    scanf("%d", &option);
    switch (option)
    {
    case 0:
        adminLogOut();
        // adminPanelAuthentication();
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
    printCentered2(current_user_admin, "Home | Contact | About | Profile. ", 11);
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
    printCentered2(current_user_admin, "Home | Contact | About | Profile. ", 11);
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
        // yet not done?
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

    char headingName[40] = "Stock / Product";
    menuUI(headingName);
    printCentered2(current_user_admin, "Home | Contact | About | Profile. ", 11);
    printf("\n");
    printCentered("OneMart", 10);
    printCentered("------------------------", 10);
    printf("\n");

    printCentered("Available Category List", 9);
    printCentered(" -----------------------------------------------------", 9);
    printCentered("| computer    books   medicine  mobile     television |", 15);
    printCentered("| fragrances  camera  watches   beverages  software   |", 15);
    printCentered(" -----------------------------------------------------", 9);
    printf("\n");
    printCentered("Input Computer Information:", 15);
    printCentered(" -----------------------------------------------------", 9);

    int pID;
    char pName[20];
    int pPrice;
    int pUnit;
    char pCat[15];
    int proSupID; // product supplier id

    //-------space/input management for ID-------//
    FILE *fp;
    fp = fopen("Stock/productID.txt", "r");
    fscanf(fp, "%d", &pID);
    fclose(fp);
    int width = getConsoleWidth();
    int space = (width - 5) / 2;
    setColor(15); // start
    for (int i = 0; i < space; i++)
        printf(" ");
    printf("    SKU : %d\n", pID);
    ++pID;
    fp = fopen("Stock/productID.txt", "w");
    fprintf(fp, "%d", pID);
    fclose(fp);

    //-------space/input management for name-------//
    space = (width - 15) / 2;
    for (int i = 0; i < space; i++)
        printf(" ");
    printf("        Name : ");
    scanf("%s", pName);

    //-------space/input management for Price-------//
    space = (width - 15) / 2;
    for (int i = 0; i < space; i++)
        printf(" ");
    printf("       Price : ");
    scanf("%d", &pPrice);

    //-------space/input management for Unit-------//
    space = (width - 15) / 2;
    for (int i = 0; i < space; i++)
        printf(" ");
    printf("        Unit : ", 15);
    scanf("%d", &pUnit);

    //-------space/input management for Category-------//
    space = (width - 17) / 2;
    for (int i = 0; i < space; i++)
        printf(" ");
    printf("     Category : ", 15);
    scanf("%s", pCat);

    // Show Supplier List
    int supplierID;
    char supName[20];
    int supPhn[15];
    char supCompName[25];

    fp = fopen("supplier_data/supplier_list.txt", "r");
    printf("\n");
    printCentered("Available Supplier List", 9);
    printCentered("-----------------------", 9);
    printCentered(" ID      Name ", 15);
    printCentered(" -----   -------", 15);

    // print data from file
    while (fscanf(fp, "%d %s %s %s", &supplierID, supName, supPhn, supCompName) != EOF)
    {
        int width = getConsoleWidth();
        int space = (width - 15) / 2;
        for (int i = 0; i < space; i++)
            printf(" ");
        printf("%d   %s\n", supplierID, supName);
    }
    fclose(fp);

    //-------space/input management for Supplier ID-------//
    space = (width - 15) / 2;
    printf("\n");
    for (int i = 0; i < space; i++)
        printf(" ");
    printf("Supplier ID : ", 15);
    scanf("%d", &proSupID);
    setColor(7); // reset color

    // data send to file
    fp = fopen("Stock/all_product.txt", "a");
    fprintf(fp, "%d %d %s %d %d %s\n", pID, proSupID, pName, pPrice, pUnit, pCat);
    fclose(fp);

    printf("\n\n");
    printCentered("'Product Added'....Press any key to return Home.", 10);
    _getch();
    allProductData(); // refresh all product index
    adminPanelStock();
}
//*---------------Admin Panel Add New Product End----------------*/
//
//
//
//*---------------Admin Panel Delete Product Start----------------*/
void deleteProduct()
{
    int pID;
    char pName[20];
    int pPrice;
    int pUnit;
    char pCat[15];
    int proSupID;

    char headingName[40] = "Stock / Product";
    menuUI(headingName);
    printCentered2(current_user_admin, "Home | Contact | About | Profile. ", 11);
    printf("\n");
    printCentered("OneMart", 10);
    printCentered("------------------------", 10);
    printCentered("Product Delete", 15);
    printCentered(" --------------------------", 9);
    printf("\n\n");
    int pID2;
    int width = getConsoleWidth();
    int space = (width - 18) / 2;
    setColor(15);
    for (int i = 0; i < space; i++)
        printf(" ");
    printf("Input Product ID: ", 15);
    scanf("%d", &pID2);
    printf("\n\n");

    // Picking product index number form file
    int index;
    FILE *fp;
    fp = fopen("Stock/index/all_product_index.txt", "r");
    fscanf(fp, "%d", &index);

    // Finding Product
    allProductData();
    int deletePos, i, found = 0;
    for (i = 0; i < index; i++)
    {
        if (allProduct[i].pID == pID2)
        {
            deletePos = i;
            found = 1;
            break;
        }
    }

    // Product
    if (found)
    {
        printCentered("  Prduct Information:", 10);
        printCentered("  ------------------------", 10);
        printCentered("  Product-ID:     Supplier-ID    Product-Name:   Product-Price:        Unit:       Category:", 15);
        printCentered("  -------------------------------------------------------------------------------------------", 9);
        printf("                              %d           %d          %s         %d.00TK           %d (P)       %s\n", allProduct[i].pID, allProduct[i].proSupID, allProduct[i].pName, allProduct[i].pPrice, allProduct[i].pUnit, allProduct[i].pCat);

        int option;
        printf("\n\n\n\n\n");
        printCentered("    Are you confirm to delete?", 15);
        printCentered("     1. YES", 10);
        printCentered("    2. NO", 4);

        // take input
        width = getConsoleWidth();
        space = (width - 18) / 2;
        setColor(15);
        for (int i = 0; i < space; i++)
            printf(" ");
        printf("Choose Option:: ", 15);
        scanf("%d", &option);
        printf("\n\n");

        switch (option)
        {
        case 1:
            for (int j = deletePos; j < index; j++)
            {
                allProduct[j] = allProduct[j + 1];
            }
            index = index - 1;

            // Latest Data Send to allProduct-FILE
            fp = fopen("Stock/all_product.txt", "w");
            fclose(fp);
            fp = fopen("Stock/all_product.txt", "a");
            for (int j = 0; j < index; j++)
            {
                fprintf(fp, "%d %d %s %d %d %s\n", allProduct[j].pID, allProduct[j].proSupID, allProduct[j].pName, allProduct[j].pPrice, allProduct[j].pUnit, allProduct[j].pCat);
            }
            fclose(fp);

            fp = fopen("Stock/index/all_product_index.txt", "w");
            fprintf(fp, "%d", index);
            fclose(fp);

            printf("\n\n");
            printCentered("'Product Deleted'....Press any key to return Home.", 10);
            _getch();
            adminPanelStock();
            break;

        case 2:
            printCentered("Deletation cancel!", 4);
            _getch();
            adminPanelStock();
            break;
        }
    }
    else
    {
        printCentered("     Porduct has not been found!", 4);
        printf("\n\n");
        printCentered("          Press any key to return Home.....", 10);
        _getch();
        adminPanelStock();
    }
}
//*---------------Admin Panel Delete Product End----------------*/
//
//
//
/*---------------Admin Panel List Of Product Start----------------*/
void listOfProduct()
{
    char headingName[40] = "Stock / Product";
    menuUI(headingName);
    printCentered2(current_user_admin, "Home | Contact | About | Profile. ", 11);
    printf("\n");
    printCentered("OneMart", 10);
    printCentered("------------------------", 10);
    printf("\n\n");

    printCentered("All Product List", 9);
    printCentered("  ------------------------------------------------------------------------------------------------------", 9);
    printCentered("     NO:     Product-ID:     Supplier-ID      Product-Name:     Product-Price:        Unit:       Category:", 15);
    printCentered("  -------------------------------------------------------------------------------------------------------", 9);
    allProductData();
    int index, serNum = 1;
    FILE *fp;
    fp = fopen("Stock/index/all_product_index.txt", "r");
    fscanf(fp, "%d", &index);
    // pID, proSupID, pCat, pName, pPrice, pUnit);
    for (int i = 0; i < index; i++)
    {
        printf("                         %d        %d          %d            %s            %d.00TK         %d (P)      %s\n", serNum++, allProduct[i].pID, allProduct[i].proSupID, allProduct[i].pName, allProduct[i].pPrice, allProduct[i].pUnit, allProduct[i].pCat);
    }

    printf("\n\n\n");
    printCentered("Press any key to return Home.....", 10);
    _getch();
    adminPanelStock();
}
//*---------------Admin Panel List Of Product End----------------*/
//
//
//
/*---------------Admin Panel stock Cheak Start----------------*/
void stockCheak()
{
    char headingName[40] = "Stock / Product";
    menuUI(headingName);
    printCentered2(current_user_admin, "Home | Contact | About | Profile. ", 11);
    printf("\n");
    printCentered("OneMart", 10);
    printCentered("------------------------", 10);
    printf("\n");
    printCentered(" Stock Check", 15);
    printCentered(" --------------------------", 9);

    int pID2;
    int width = getConsoleWidth();
    int space = (width - 18) / 2;
    setColor(15);
    for (int i = 0; i < space; i++)
        printf(" ");
    printf("Input Product ID: ", 15);
    scanf("%d", &pID2);
    printf("\n\n");

    // Picking product index number form file
    int index;
    FILE *fp;
    fp = fopen("Stock/index/all_product_index.txt", "r");
    fscanf(fp, "%d", &index);

    // Finding Product
    allProductData();
    int i, found = 0, data;
    for (i = 0; i < index; i++)
    {
        if (allProduct[i].pID == pID2)
        {
            data = i;
            found = 1;
            break;
        }
    }

    // Product
    if (found)
    {
        printCentered("  Stock Information:", 10);
        printCentered("  ---------------------", 10);
        printCentered("    Product-ID:        Product-Name:         Unit:  ", 15);
        printCentered("  ------------------------------------------------", 9);
        printf("                                                   %d             %s             %d (P) \n", allProduct[data].pID, allProduct[data].pName, allProduct[data].pUnit);

        printf("\n\n");
        if (allProduct[data].pUnit > 0)
        {
            printCentered("  |----Stock Available----|", 14);
        }
        else
        {
            printCentered("|----Stock Out----|", 4);
        }

        printf("\n\n\n");
        printCentered("        Press any key to return Home.....", 10);
        _getch();
        adminPanelStock();
        _getch();
    }
    else
    {
        printCentered("     Porduct has not been found!", 4);
        printf("\n\n");
        printCentered("          Press any key to return Home.....", 10);
        _getch();
        adminPanelStock();
    }
}
//*---------------Admin Panel stock Cheak End----------------*/
//
//
//
/*---------------Admin Panel Update Stock Start----------------*/
void updateStock()
{

    int pID;
    char pName[20];
    int pPrice;
    int pUnit;
    char pCat[15];
    int proSupID;

    char headingName[40] = "Stock / Product";
    menuUI(headingName);
    printCentered2(current_user_admin, "Home | Contact | About | Profile. ", 11);
    printf("\n");
    printCentered("OneMart", 10);
    printCentered("------------------------", 10);
    printCentered("Update Stock", 15);
    printCentered(" -------------------", 9);
    printf("\n\n");

    int pID2;
    int width = getConsoleWidth();
    int space = (width - 18) / 2;
    setColor(15);
    for (int i = 0; i < space; i++)
        printf(" ");
    printf("Input Product ID: ", 15);
    scanf("%d", &pID2);
    printf("\n\n");

    // Picking product index number form file
    int index;
    FILE *fp;
    fp = fopen("Stock/index/all_product_index.txt", "r");
    fscanf(fp, "%d", &index);

    // Finding Product
    allProductData(); // to get latest all product in array
    int i, found = 0, data;
    for (i = 0; i < index; i++)
    {
        if (allProduct[i].pID == pID2)
        {
            data = i;
            found = 1;
            break;
        }
    }

    // Product
    if (found)
    {
        printCentered("  Prduct Information:", 10);
        printCentered("  ------------------------", 10);
        printCentered("  Product-ID:     Supplier-ID    Product-Name:    Product-Price:        Unit:       Category:", 15);
        printCentered("  -------------------------------------------------------------------------------------------", 9);
        printf("                              %d           %d       %s         %d.00TK           %d (P)       %s\n", allProduct[i].pID, allProduct[i].proSupID, allProduct[i].pName, allProduct[i].pPrice, allProduct[i].pUnit, allProduct[i].pCat);

        printf("\n");
        int unit;
        width = getConsoleWidth();
        space = (width - 18) / 2;
        setColor(15);
        for (int i = 0; i < space; i++)
            printf(" ");
        printf("Input Product Unit: ", 15);
        scanf("%d", &unit);
        printf("\n\n");

        // sum of unit
        allProduct[data].pUnit = allProduct[data].pUnit + unit;

        // show latest stock
        printCentered("  Latest Prduct Information:", 10);
        printCentered("  ----------------------------", 10);
        printCentered("  Product-ID:     Supplier-ID    Product-Name:    Product-Price:        Unit:       Category:", 15);
        printCentered("  -------------------------------------------------------------------------------------------", 9);
        printf("                              %d           %d       %s         %d.00TK           %d (P)       %s\n", allProduct[i].pID, allProduct[i].proSupID, allProduct[i].pName, allProduct[i].pPrice, allProduct[i].pUnit, allProduct[i].pCat);

        // Latest Data Send to allProduct-FILE
        fp = fopen("Stock/all_product.txt", "w");
        fclose(fp);
        fp = fopen("Stock/all_product.txt", "a");
        for (int j = 0; j < index; j++)
        {
            fprintf(fp, "%d %d %s %d %d %s\n", allProduct[j].pID, allProduct[j].proSupID, allProduct[j].pName, allProduct[j].pPrice, allProduct[j].pUnit, allProduct[j].pCat);
        }
        fclose(fp);

        printf("\n\n");
        printCentered("'Stock Updated'....Press any key to return Home.", 10);
        _getch();
        adminPanelStock();
    }
    else
    {
        printCentered("     Porduct has not been found!", 4);
        printf("\n\n");
        printCentered("          Press any key to return Home.....", 10);
        _getch();
        adminPanelStock();
    }
}
//*---------------Admin Panel Update Stock End----------------*/
//
//
//
/*---------------Admin Panel Stock List By Category Start----------------*/
void stockListByCategory()
{
    char headingName[40] = "Stock / Product";
    menuUI(headingName);
    printCentered2(current_user_admin, "Home | Contact | About | Profile. ", 11);
    printf("\n");
    printCentered("OneMart", 10);
    printCentered("------------------------", 10);
    printf("\n");

    printCentered("All Product List by Category", 9);
    printCentered("  ------------------------------------------------------------------------------------------------------", 9);

    // take index num from file
    int index, serNum = 1;
    FILE *fp;
    fp = fopen("Stock/index/all_product_index.txt", "r");
    fscanf(fp, "%d", &index);
    fclose(fp);
    allProductData(); // get latest all product

    // For computer
    for (int i = 0; i < index; i++)
    {
        int serNum = 1;
        if (strcmp(allProduct[i].pCat, "computer") == 0)
        {
            printf("\n\n");
            printCentered("Computer", 12);
            printCentered("  ----------------------", 12);
            printCentered("      NO:     Product-ID:     Supplier-ID      Product-Name:     Product-Price:        Unit:       Category:", 15);
            printCentered("     -------------------------------------------------------------------------------------------------------", 12);

            for (int j = i; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "computer") == 0)
                {
                    printf("                         %d        %d          %d            %s            %d.00TK         %d (P)      %s\n", serNum++, allProduct[j].pID, allProduct[j].proSupID, allProduct[j].pName, allProduct[j].pPrice, allProduct[j].pUnit, allProduct[j].pCat);
                }
            }
            break;
        }
    }

    // For books
    for (int i = 0; i < index; i++)
    {
        int serNum = 1;
        if (strcmp(allProduct[i].pCat, "books") == 0)
        {
            printf("\n\n");
            printCentered("Books", 12);
            printCentered("  ----------------------", 12);
            printCentered("      NO:     Product-ID:     Supplier-ID      Product-Name:     Product-Price:        Unit:       Category:", 15);
            printCentered("     -------------------------------------------------------------------------------------------------------", 12);

            for (int j = i; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "books") == 0)
                {
                    printf("                         %d        %d          %d            %s            %d.00TK         %d (P)      %s\n", serNum++, allProduct[j].pID, allProduct[j].proSupID, allProduct[j].pName, allProduct[j].pPrice, allProduct[j].pUnit, allProduct[j].pCat);
                }
            }
            break;
        }
    }

    // For medicine
    for (int i = 0; i < index; i++)
    {
        int serNum = 1;
        if (strcmp(allProduct[i].pCat, "medicine") == 0)
        {
            printf("\n\n");
            printCentered("Medicine", 12);
            printCentered("  ----------------------", 12);
            printCentered("      NO:     Product-ID:     Supplier-ID      Product-Name:     Product-Price:        Unit:       Category:", 15);
            printCentered("     -------------------------------------------------------------------------------------------------------", 12);

            for (int j = i; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "medicine") == 0)
                {
                    printf("                         %d        %d          %d            %s            %d.00TK         %d (P)      %s\n", serNum++, allProduct[j].pID, allProduct[j].proSupID, allProduct[j].pName, allProduct[j].pPrice, allProduct[j].pUnit, allProduct[j].pCat);
                }
            }
            break;
        }
    }

    // For camera
    for (int i = 0; i < index; i++)
    {
        int serNum = 1;
        if (strcmp(allProduct[i].pCat, "camera") == 0)
        {
            printf("\n\n");
            printCentered("Camera", 12);
            printCentered("  ----------------------", 12);
            printCentered("      NO:     Product-ID:     Supplier-ID      Product-Name:     Product-Price:        Unit:       Category:", 15);
            printCentered("     -------------------------------------------------------------------------------------------------------", 12);

            for (int j = i; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "camera") == 0)
                {
                    printf("                         %d        %d          %d            %s            %d.00TK         %d (P)      %s\n", serNum++, allProduct[j].pID, allProduct[j].proSupID, allProduct[j].pName, allProduct[j].pPrice, allProduct[j].pUnit, allProduct[j].pCat);
                }
            }
            break;
        }
    }

    // For television
    for (int i = 0; i < index; i++)
    {
        int serNum = 1;
        if (strcmp(allProduct[i].pCat, "television") == 0)
        {
            printf("\n\n");
            printCentered("Television", 12);
            printCentered("  ----------------------", 12);
            printCentered("      NO:     Product-ID:     Supplier-ID      Product-Name:     Product-Price:        Unit:       Category:", 15);
            printCentered("     -------------------------------------------------------------------------------------------------------", 12);

            for (int j = i; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "television") == 0)
                {
                    printf("                         %d        %d          %d            %s            %d.00TK         %d (P)      %s\n", serNum++, allProduct[j].pID, allProduct[j].proSupID, allProduct[j].pName, allProduct[j].pPrice, allProduct[j].pUnit, allProduct[j].pCat);
                }
            }
            break;
        }
    }

    // For watches
    for (int i = 0; i < index; i++)
    {
        int serNum = 1;
        if (strcmp(allProduct[i].pCat, "watches") == 0)
        {
            printf("\n\n");
            printCentered("Smart Watches", 12);
            printCentered("  ----------------------", 12);
            printCentered("      NO:     Product-ID:     Supplier-ID      Product-Name:     Product-Price:        Unit:       Category:", 15);
            printCentered("     -------------------------------------------------------------------------------------------------------", 12);

            for (int j = i; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "watches") == 0)
                {
                    printf("                         %d        %d          %d            %s            %d.00TK         %d (P)      %s\n", serNum++, allProduct[j].pID, allProduct[j].proSupID, allProduct[j].pName, allProduct[j].pPrice, allProduct[j].pUnit, allProduct[j].pCat);
                }
            }
            break;
        }
    }

    // For fragrances
    for (int i = 0; i < index; i++)
    {
        int serNum = 1;
        if (strcmp(allProduct[i].pCat, "fragrances") == 0)
        {
            printf("\n\n");
            printCentered("Fragrances", 12);
            printCentered("  ----------------------", 12);
            printCentered("      NO:     Product-ID:     Supplier-ID      Product-Name:     Product-Price:        Unit:       Category:", 15);
            printCentered("     -------------------------------------------------------------------------------------------------------", 12);

            for (int j = i; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "fragrances") == 0)
                {
                    printf("                         %d        %d          %d            %s            %d.00TK         %d (P)      %s\n", serNum++, allProduct[j].pID, allProduct[j].proSupID, allProduct[j].pName, allProduct[j].pPrice, allProduct[j].pUnit, allProduct[j].pCat);
                }
            }
            break;
        }
    }

    // For Beverages
    for (int i = 0; i < index; i++)
    {
        int serNum = 1;
        if (strcmp(allProduct[i].pCat, "beverages") == 0)
        {
            printf("\n\n");
            printCentered("Beverages", 12);
            printCentered("  ----------------------", 12);
            printCentered("      NO:     Product-ID:     Supplier-ID      Product-Name:     Product-Price:        Unit:       Category:", 15);
            printCentered("     -------------------------------------------------------------------------------------------------------", 12);

            for (int j = i; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "beverages") == 0)
                {
                    printf("                         %d        %d          %d            %s            %d.00TK         %d (P)      %s\n", serNum++, allProduct[j].pID, allProduct[j].proSupID, allProduct[j].pName, allProduct[j].pPrice, allProduct[j].pUnit, allProduct[j].pCat);
                }
            }
            break;
        }
    }

    // For Mobile
    for (int i = 0; i < index; i++)
    {
        int serNum = 1;
        if (strcmp(allProduct[i].pCat, "mobile") == 0)
        {
            printf("\n\n");
            printCentered("Mobile", 12);
            printCentered("  ----------------------", 12);
            printCentered("      NO:     Product-ID:     Supplier-ID      Product-Name:     Product-Price:        Unit:       Category:", 15);
            printCentered("     -------------------------------------------------------------------------------------------------------", 12);

            for (int j = i; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "mobile") == 0)
                {
                    printf("                         %d        %d          %d            %s            %d.00TK         %d (P)      %s\n", serNum++, allProduct[j].pID, allProduct[j].proSupID, allProduct[j].pName, allProduct[j].pPrice, allProduct[j].pUnit, allProduct[j].pCat);
                }
            }
            break;
        }
    }

    // For Software
    for (int i = 0; i < index; i++)
    {
        int serNum = 1;
        if (strcmp(allProduct[i].pCat, "software") == 0)
        {
            printf("\n\n");
            printCentered("Software", 12);
            printCentered("  ----------------------", 12);
            printCentered("      NO:     Product-ID:     Supplier-ID      Product-Name:     Product-Price:        Unit:       Category:", 15);
            printCentered("     -------------------------------------------------------------------------------------------------------", 12);

            for (int j = i; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "software") == 0)
                {
                    printf("                         %d        %d          %d            %s            %d.00TK         %d (P)      %s\n", serNum++, allProduct[j].pID, allProduct[j].proSupID, allProduct[j].pName, allProduct[j].pPrice, allProduct[j].pUnit, allProduct[j].pCat);
                }
            }
            break;
        }
    }

    printf("\n\n\n");
    printCentered("Press any key to return Home.....", 10);
    _getch();
    adminPanelStock();
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
    printCentered2(current_user_admin, "Home | Contact | About | Profile. ", 11);
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
    printCentered2(current_user_admin, "Home | Contact | About | Profile. ", 11);
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
    supplierLatestData();
    char headingName[40] = "Supplier Management";
    menuUI(headingName);
    printCentered2(current_user_admin, "Home | Contact | About | Profile. ", 11);
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
    printCentered("   5. Supplier List", 15);
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

    case 5:
        supplierList();
        break;
        // yet not done
    case 0:
        adminPanelHome();
        break;
    default:
        printCentered("Invalid Choice!", 4);
        printCentered("Press any key to return....", 10);
        _getch();
        adminPanelSupplierManagement();
    }
}
//*---------------Admin Panel Supplier Management End ----------------*/
//
//
//
//*---------------Admin Panel (Supplier) Add Supplier Start----------------*/
void addSupplier()
{
    char headingName[40] = "Supplier Management";
    menuUI(headingName);
    printCentered2(current_user_admin, "Home | Contact | About | Profile. ", 11);
    printf("\n\n");
    printCentered("OneMart", 10);
    printCentered("------------------------", 10);
    printf("\n");
    printCentered("Input Supplier Information:", 15);
    printCentered("------------------------------", 15);

    // variable declare
    int supplierID;
    char supName[20];
    char supPhn[20];
    char supCompName[25];

    //-------space/input management for ID-------//
    FILE *fp;
    fp = fopen("supplier_data/supplierID.txt", "r");
    fscanf(fp, "%d", &supplierID);
    fclose(fp);

    int width = getConsoleWidth();
    int space = (width - 5) / 2;
    setColor(15); // start
    for (int i = 0; i < space; i++)
        printf(" ");
    printf("ID    : %d\n", supplierID);

    //-------space/input management for name-------//
    space = (width - 12) / 2;
    for (int i = 0; i < space; i++)
        printf(" ");
    printf("    Name  : ");
    scanf("%s", supName);

    //-------space/input management for phone-------//
    space = (width - 11) / 2;
    for (int i = 0; i < space; i++)
        printf(" ");
    printf("   Phone : ");
    scanf("%s", supPhn);

    //-------space/input management for company name-------//
    space = (width - 12) / 2;
    for (int i = 0; i < space; i++)
        printf(" ");
    printf("Comp. Name: ", 15);
    scanf("%s", supCompName);
    setColor(7); // reset color

    // data send to file
    fp = fopen("supplier_data/supplier_list.txt", "a");
    fprintf(fp, "%d %s %s %s\n", supplierID, supName, supPhn, supCompName);
    fclose(fp);

    // dupplier id send to file
    ++supplierID;
    fp = fopen("supplier_data/supplierID.txt", "w");
    fprintf(fp, "%d", supplierID);
    fclose(fp);

    printf("\n\n");
    printCentered("'Supplier Added'....Press any key to return Home.", 10);
    printf("\n\n\n");
    _getch();
    supplierLatestData();
    adminPanelSupplierManagement(); // home
}
//*---------------Admin Panel (Supplier) Add Supplier End----------------*/
//
//
//
//*---------------Admin Panel (Supplier) Delete Supplier Start----------------*/
void deleteSupplier()
{
    char headingName[40] = "Supplier Management";
    menuUI(headingName);
    printCentered2(current_user_admin, "Home | Contact | About | Profile. ", 11);
    printf("\n");
    printCentered("OneMart", 10);
    printCentered("------------------------", 10);
    printf("\n\n");
    printCentered("Supplier Delete", 15);
    printCentered(" -----------------------", 9);

    int sID2, index;
    int width = getConsoleWidth();
    int space = (width - 18) / 2;
    setColor(15);
    for (int i = 0; i < space; i++)
        printf(" ");
    printf("Input Supplier ID: ", 15);
    scanf("%d", &sID2);
    printf("\n");

    supplierLatestData(); // get latest supplier data
    FILE *fp;
    fp = fopen("supplier_data/supplier_data_index.txt", "r");
    fscanf(fp, "%d", &index); // get supplier index
    fclose(fp);

    // find del position
    int deletePos, i, found = 0, serNum = 1;
    for (i = 0; i < index; i++)
    {
        if (supplierData[i].supplierID == sID2)
        {
            deletePos = i;
            found = 1;
            break;
        }
    }

    // Product
    if (found)
    {
        printCentered("Supplier Found...", 10);
        printCentered("-----------------------", 10);
        printCentered("    SN:         ID:            Name:          Phone:        Company:    ", 15);
        printCentered("----------------------------------------------------------------", 9);

        printf("                                        %d          %d         %s        %s    %s\n", serNum++, supplierData[i].supplierID, supplierData[i].supName, supplierData[i].supPhn, supplierData[i].supCompName);
        int option;
        printf("\n\n\n\n\n");
        printCentered("     Are you confirm to delete?", 15);
        printCentered("     1. YES", 10);
        printCentered("    2. NO", 4);

        // take input
        width = getConsoleWidth();
        space = (width - 18) / 2;
        setColor(15);
        for (int i = 0; i < space; i++)
            printf(" ");
        printf("Choose Option: ");
        scanf("%d", &option);
        printf("\n\n");

        switch (option)
        {
        case 1:
            for (int j = deletePos; j < index; j++)
            {
                supplierData[j] = supplierData[j + 1];
            }
            index = index - 1;

            FILE *fp;
            // Latest Data Send to Supplier - FILE
            fp = fopen("supplier_data/supplier_list.txt", "w"); // reset previous data
            fclose(fp);
            fp = fopen("supplier_data/supplier_list.txt", "a");
            for (int j = 0; j < index; j++)
            {
                fprintf(fp, "%d %s %s %s\n", supplierData[j].supplierID, supplierData[j].supName, supplierData[j].supPhn, supplierData[j].supCompName);
            }
            fclose(fp);

            // send index to supplier index
            fp = fopen("supplier_data/supplier_data_index.txt", "w");
            fprintf(fp, "%d", index);
            fclose(fp);

            printf("\n\n");
            printCentered("'Supplier Deleted'....Press any key to return Home.", 4);
            _getch();
            adminPanelSupplierManagement();

        case 2:
            printCentered("Deletation cancel!", 4);
            _getch();
            adminPanelSupplierManagement();
        }
    }
    else
    {
        printCentered("     Supplier has not been found!", 4);
        printf("\n\n");
        printCentered("          Press any key to return Home.....", 10);
        _getch();
        adminPanelSupplierManagement();
    }
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
    char headingName[40] = "Supplier Management";
    menuUI(headingName);
    printCentered2(current_user_admin, "Home | Contact | About | Profile. ", 11);
    printf("\n");
    printCentered("OneMart", 10);
    printCentered("------------------------", 10);
    printf("\n");

    printCentered("All Product List by Supplier", 9);
    printCentered("  ------------------------------------------------------------------------------------------------------", 9);

    FILE *fp;
    int supIndex;

    // take Product index num from file
    supplierLatestData(); // get all latest supplier list
    fp = fopen("supplier_data/supplier_data_index.txt", "r");
    fscanf(fp, "%d", &supIndex);
    fclose(fp);

    // take Product index num from file
    int pIndex;
    fp = fopen("Stock/index/all_product_index.txt", "r");
    fscanf(fp, "%d", &pIndex);
    fclose(fp);
    allProductData(); // get latest all product

    for (int i = 0; i < supIndex; i++)
    {
        // int serNum = 1;
        for (int k = 0; k < pIndex; k++)
        {
            if (supplierData[i].supplierID == allProduct[k].proSupID)
            {
                printf("\n\n");
                int serNum = 1;
                int width = getConsoleWidth();
                int space = (width - 8) / 2;
                setColor(15);
                for (int i = 0; i < space; i++)
                {
                    printf(" ");
                }
                printf("%s\n", supplierData[i].supName);
                printCentered("  ----------------------", 12);
                printCentered("      NO:     Product-ID:     Supplier-ID      Product-Name:     Product-Price:        Unit:       Category:", 15);
                printCentered("     -------------------------------------------------------------------------------------------------------", 12);

                for (int j = 0; j < pIndex; j++)
                {
                    if (supplierData[i].supplierID == allProduct[j].proSupID)
                    {
                        printf("                         %d        %d          %d            %s            %d.00TK         %d (P)      %s\n", serNum++, allProduct[j].pID, allProduct[j].proSupID, allProduct[j].pName, allProduct[j].pPrice, allProduct[j].pUnit, allProduct[j].pCat);
                    }
                }
                break;
            }
        }
    }
    fclose(fp);

    printf("\n\n\n");
    printCentered("Press any key to return Home.....", 10);
    _getch();
    adminPanelSupplierManagement();
}
//*---------------Admin Panel (Supplier) List Of Product By Supplier End----------------*/
//
//
//
//*---------------Admin Panel (Supplier) Supplier data start----------------*/
void supplierLatestData() // always return latest data
{
    int supplierID2;
    char supName2[20];
    char supPhn2[15];
    char supCompName2[25];

    // take all supplier name from file
    char sName[15];
    int index = 0;
    FILE *fp;
    fp = fopen("supplier_data/supplier_list.txt", "r");
    while (fscanf(fp, "%d %s %s %s", &supplierID2, supName2, supPhn2, supCompName2) != EOF)
    {
        supplierData[index].supplierID = supplierID2;
        strcpy(supplierData[index].supName, supName2);
        strcpy(supplierData[index].supPhn, supPhn2);
        strcpy(supplierData[index].supCompName, supCompName2);
        index++;
    }
    fclose(fp);
    fp = fopen("supplier_data/supplier_data_index.txt", "w");
    fprintf(fp, "%d", index);
    fclose(fp);
}
//*---------------Admin Panel (Supplier) Supplier data start----------------*/
//
//
//
//*---------------Admin Panel (Supplier) List Of Supplier Start----------------*/
void supplierList()
{
    char headingName[40] = "Supplier Management";
    menuUI(headingName);
    printCentered2(current_user_admin, "Home | Contact | About | Profile. ", 11);
    printf("\n\n");
    printCentered("OneMart", 10);
    printCentered("------------------------", 10);
    printf("\n\n");
    printCentered("Supplier List", 9);
    printCentered("------------------------------------------------------------------", 9);
    printCentered("| SN:     ID:          Name:          Phone:           Company:    |", 9);
    // printCentered("------------------------------------------------------------------", 9);
    printCentered("==================================================================", 9);
    int serNum = 1;
    int supplierID;
    char supName[20];
    char supPhn[15];
    char supCompName[25];

    FILE *fp;
    fp = fopen("supplier_data/supplier_list.txt", "r");

    // print data from file
    while (fscanf(fp, "%d %s %s %s", &supplierID, supName, supPhn, supCompName) != EOF)
    {
        printf("                                         %d     %d       %s      %s       %s\n", serNum, supplierID, supName);
        printCentered("------------------------------------------------------------------", 8);
        serNum++;
    }
    fclose(fp);

    printf("\n\n\n");
    printCentered("Press any key to return Home.", 10);
    _getch();
    adminPanelSupplierManagement();
}
//*---------------Admin Panel (Supplier) List Of supplier End----------------*/
//
//
//
//*---------------Admin Panel User Management start----------------*/
void adminPanelUserManagement() // HOME
{
    char headingName[40] = "User Management";
    menuUI(headingName);
    printCentered2(current_user_admin, "Home | Contact | About | Profile. ", 11);
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
//*---------------ALL Product from FILE - Start----------------*/
void allProductData()
{
    int pID2;
    int proSupID2;
    char pCat2[15];
    char pName2[20];
    int pPrice2;
    int pUnit2;
    int index = 0;

    FILE *fp;
    fp = fopen("Stock/all_product.txt", "r");
    while (fscanf(fp, "%d %d %s %d %d %s\n", &pID2, &proSupID2, pName2, &pPrice2, &pUnit2, pCat2) != EOF)
    {

        allProduct[index].pID = pID2;
        allProduct[index].proSupID = proSupID2;
        allProduct[index].pPrice = pPrice2;
        allProduct[index].pUnit = pUnit2;
        strcpy(allProduct[index].pName, pName2);
        strcpy(allProduct[index].pCat, pCat2);
        index++;
    }
    fclose(fp);
    fp = fopen("Stock/index/all_product_index.txt", "w");
    fprintf(fp, "%d", index);
    fclose(fp);
}
//*---------------ALL Product from FILE - Start----------------*/
//
//
//
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
    printCentered(" 1. YES", 10);
    printCentered("2. NO", 12);

    int option;
    printf("\n\n\nEnter your choice: ");
    scanf("%d", &option);
    int adminLoginStatus2;
    FILE *fp;
    fp = fopen("login_Logout_status/logData.txt", "r");
    fscanf(fp, "%d", &adminLoginStatus2);
    fclose(fp);
    switch (option)
    {
    case 1:

        if (adminLoginStatus2 == 1)
        {
            adminPanelHome();
        }
        else if (adminLoginStatus2 == 0)
        {
            adminPanelAuthentication();
        }

        break;
    case 2:
        OnlineHome();
        break;
    default:
        printCentered("Invalid Choice!", 12);
        _getch();
        home2();
    }
}
//*-----------------2nd HOME END----------------------*/
/*-----------------HOME START----------------------*/
void OnlineHome()
{
    char headingName[10] = "HOME";
    menuUI(headingName);

    char userName[20] = "mostakin";
    printCentered2(userName, "Home | Contact | About | Profile. ", 11);

    printCentered("OneMart - Online Shopping", 10);
    printCentered("--------------------------", 10);

    // take index num from file
    int index, serNum = 1;
    FILE *fp;
    fp = fopen("Stock/index/all_product_index.txt", "r");
    fscanf(fp, "%d", &index);
    fclose(fp);
    allProductData(); // get latest all product

    // For computer
    for (int i = 0; i < index; i++)
    {
        int serNum = 1;
        if (strcmp(allProduct[i].pCat, "computer") == 0)
        {
            printf("\n\n");
            setColor(12);
            printf("                        Computer\n");
            setColor(7);
            printCentered("     ------------------------------------------------------------------------------------------------------", 9);
            printCentered("    NO:     Product-ID:    Supplier-ID      Product-Name:     Product-Price:      Unit:      Category:", 9);
            printCentered("     ------------------------------------------------------------------------------------------------------", 9);

            for (int j = i; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "computer") == 0)
                {
                    printf("                         %d        %d          %d            %s            %d.00TK         %d (P)      %s\n", serNum++, allProduct[j].pID, allProduct[j].proSupID, allProduct[j].pName, allProduct[j].pPrice, allProduct[j].pUnit, allProduct[j].pCat);
                }
            }
            break;
        }
    }

    // For books
    for (int i = 0; i < index; i++)
    {
        int serNum = 1;
        if (strcmp(allProduct[i].pCat, "books") == 0)
        {
            printf("\n\n");
            setColor(12);
            printf("                        Books\n");
            setColor(7);
            printCentered("     ------------------------------------------------------------------------------------------------------", 9);
            printCentered("    NO:     Product-ID:    Supplier-ID      Product-Name:     Product-Price:      Unit:      Category:", 9);
            printCentered("     ------------------------------------------------------------------------------------------------------", 9);

            for (int j = i; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "books") == 0)
                {
                    printf("                         %d        %d          %d            %s            %d.00TK         %d (P)      %s\n", serNum++, allProduct[j].pID, allProduct[j].proSupID, allProduct[j].pName, allProduct[j].pPrice, allProduct[j].pUnit, allProduct[j].pCat);
                }
            }
            break;
        }
    }

    // For medicine
    for (int i = 0; i < index; i++)
    {
        int serNum = 1;
        if (strcmp(allProduct[i].pCat, "medicine") == 0)
        {
            printf("\n\n");
            setColor(12);
            printf("                        Medicine\n");
            setColor(7);
            printCentered("     ------------------------------------------------------------------------------------------------------", 9);
            printCentered("    NO:     Product-ID:    Supplier-ID      Product-Name:     Product-Price:      Unit:      Category:", 9);
            printCentered("     ------------------------------------------------------------------------------------------------------", 9);

            for (int j = i; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "medicine") == 0)
                {
                    printf("                         %d        %d          %d            %s            %d.00TK         %d (P)      %s\n", serNum++, allProduct[j].pID, allProduct[j].proSupID, allProduct[j].pName, allProduct[j].pPrice, allProduct[j].pUnit, allProduct[j].pCat);
                }
            }
            break;
        }
    }

    // For camera
    for (int i = 0; i < index; i++)
    {
        int serNum = 1;
        if (strcmp(allProduct[i].pCat, "camera") == 0)
        {
            printf("\n\n");
            setColor(12);
            printf("                        Camera\n");
            setColor(7);
            printCentered("     ------------------------------------------------------------------------------------------------------", 9);
            printCentered("    NO:     Product-ID:    Supplier-ID      Product-Name:     Product-Price:      Unit:      Category:", 9);
            printCentered("     ------------------------------------------------------------------------------------------------------", 9);

            for (int j = i; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "camera") == 0)
                {
                    printf("                         %d        %d          %d            %s            %d.00TK         %d (P)      %s\n", serNum++, allProduct[j].pID, allProduct[j].proSupID, allProduct[j].pName, allProduct[j].pPrice, allProduct[j].pUnit, allProduct[j].pCat);
                }
            }
            break;
        }
    }

    // For television
    for (int i = 0; i < index; i++)
    {
        int serNum = 1;
        if (strcmp(allProduct[i].pCat, "television") == 0)
        {
            printf("\n\n");
            setColor(12);
            printf("                        Television\n");
            setColor(7);
            printCentered("     ------------------------------------------------------------------------------------------------------", 9);
            printCentered("    NO:     Product-ID:    Supplier-ID      Product-Name:     Product-Price:      Unit:      Category:", 9);
            printCentered("     ------------------------------------------------------------------------------------------------------", 9);

            for (int j = i; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "television") == 0)
                {
                    printf("                         %d        %d          %d            %s            %d.00TK         %d (P)      %s\n", serNum++, allProduct[j].pID, allProduct[j].proSupID, allProduct[j].pName, allProduct[j].pPrice, allProduct[j].pUnit, allProduct[j].pCat);
                }
            }
            break;
        }
    }

    // For watches
    for (int i = 0; i < index; i++)
    {
        int serNum = 1;
        if (strcmp(allProduct[i].pCat, "watches") == 0)
        {
            printf("\n\n");
            setColor(12);
            printf("                        Watches\n");
            setColor(7);
            printCentered("     ------------------------------------------------------------------------------------------------------", 9);
            printCentered("    NO:     Product-ID:    Supplier-ID      Product-Name:     Product-Price:      Unit:      Category:", 9);
            printCentered("     ------------------------------------------------------------------------------------------------------", 9);

            for (int j = i; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "watches") == 0)
                {
                    printf("                         %d        %d          %d            %s            %d.00TK         %d (P)      %s\n", serNum++, allProduct[j].pID, allProduct[j].proSupID, allProduct[j].pName, allProduct[j].pPrice, allProduct[j].pUnit, allProduct[j].pCat);
                }
            }
            break;
        }
    }

    // For fragrances
    for (int i = 0; i < index; i++)
    {
        int serNum = 1;
        if (strcmp(allProduct[i].pCat, "fragrances") == 0)
        {
            printf("\n\n");
            setColor(12);
            printf("                        Fragrances\n");
            setColor(7);
            printCentered("     ------------------------------------------------------------------------------------------------------", 9);
            printCentered("    NO:     Product-ID:    Supplier-ID      Product-Name:     Product-Price:      Unit:      Category:", 9);
            printCentered("     ------------------------------------------------------------------------------------------------------", 9);

            for (int j = i; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "fragrances") == 0)
                {
                    printf("                         %d        %d          %d            %s         %d.00TK         %d (P)      %s\n", serNum++, allProduct[j].pID, allProduct[j].proSupID, allProduct[j].pName, allProduct[j].pPrice, allProduct[j].pUnit, allProduct[j].pCat);
                }
            }
            break;
        }
    }

    // For Beverages
    for (int i = 0; i < index; i++)
    {
        int serNum = 1;
        if (strcmp(allProduct[i].pCat, "beverages") == 0)
        {
            printf("\n\n");
            setColor(12);
            printf("                        Beverages\n");
            setColor(7);
            printCentered("     ------------------------------------------------------------------------------------------------------", 9);
            printCentered("    NO:     Product-ID:    Supplier-ID      Product-Name:     Product-Price:      Unit:      Category:", 9);
            printCentered("     ------------------------------------------------------------------------------------------------------", 9);

            for (int j = i; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "beverages") == 0)
                {
                    printf("                         %d        %d          %d            %s          %d.00TK         %d (P)      %s\n", serNum++, allProduct[j].pID, allProduct[j].proSupID, allProduct[j].pName, allProduct[j].pPrice, allProduct[j].pUnit, allProduct[j].pCat);
                }
            }
            break;
        }
    }

    // For Mobile
    for (int i = 0; i < index; i++)
    {
        int serNum = 1;
        if (strcmp(allProduct[i].pCat, "mobile") == 0)
        {
            printf("\n\n");
            setColor(12);
            printf("                        Mobile\n");
            setColor(7);
            printCentered("     ------------------------------------------------------------------------------------------------------", 9);
            printCentered("    NO:     Product-ID:    Supplier-ID      Product-Name:     Product-Price:      Unit:      Category:", 9);
            printCentered("     ------------------------------------------------------------------------------------------------------", 9);
            for (int j = i; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "mobile") == 0)
                {
                    printf("                         %d        %d          %d            %s            %d.00TK         %d (P)      %s\n", serNum++, allProduct[j].pID, allProduct[j].proSupID, allProduct[j].pName, allProduct[j].pPrice, allProduct[j].pUnit, allProduct[j].pCat);
                }
            }
            break;
        }
    }

    // For Software
    for (int i = 0; i < index; i++)
    {
        int serNum = 1;
        if (strcmp(allProduct[i].pCat, "software") == 0)
        {
            printf("\n\n");
            setColor(12);
            printf("                        Software\n");
            setColor(7);
            printCentered("     ------------------------------------------------------------------------------------------------------", 9);
            printCentered("    NO:     Product-ID:    Supplier-ID      Product-Name:     Product-Price:      Unit:      Category:", 9);
            printCentered("     ------------------------------------------------------------------------------------------------------", 9);
            for (int j = i; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "software") == 0)
                {
                    printf("                         %d        %d          %d            %s         %d.00TK         %d (P)      %s\n", serNum++, allProduct[j].pID, allProduct[j].proSupID, allProduct[j].pName, allProduct[j].pPrice, allProduct[j].pUnit, allProduct[j].pCat);
                }
            }
            break;
        }
    }

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
        OnlineHome();
    }
}
/*-----------------HOME END----------------------*/
//
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