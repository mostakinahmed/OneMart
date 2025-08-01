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
void buyProduct();
void dateTimeForExpireProduct();
void cardData();
void currentDateTime();

void encripTech(struct user Data[100], int index); // Caesar Cypher - For Password
void decripTech(struct user Data[100], int index);

void adminSignIn(); // 1. Authorization & Authentication
void adminSignUp();
void adminPanelAuthentication();
void customerPanelAuthentication();
void customerSignIn();
void customerSignUp();
void adminLogOut();
void menuContact();
void menuAbout();
void menuProfile();
void customerLogOut();

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
void expireProductList();

void adminPanelOnlineStore(); // 4. Admin Panel Online Store - Home
void orderPendingList();
void orderDeliveredList();
void OnePayManagement();
void listOfCard();
void rechargeCard();
void generateTransactionNumber(char *transactionNum, int length);

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
void listOfCustomerData();
void listOfAdminData();

/*-------Global Variable Section------*/
char current_user_admin[25];
char current_user_customer[25];
int customerLoginStatus = 0;
int adminLoginStatus = 0;
int currentCustomerID = 0;

/*-------Global Structure Section------*/
// date structure
struct date
{
    int day;
    int mon;
    int year;
};
struct date date[100];   // not used
struct date currentDate; // used for expired product list

struct product
{
    int pID;
    int proSupID; // product supplier ID
    char pCat[15];
    char pName[20];
    int pPrice;
    int pUnit;
    struct date expDate;
    // for sales management
    struct date SaleDate;
    int customerID;
    float totalPrice;
    char storeLocation[10];
};
struct product allProduct[500];
struct product allSalesProduct[500];

// struct product allProductCatList[500];

// for supplier only
struct supplier
{
    int supplierID;
    char supName[20];
    char supPhn[15];
    char supCompName[25];
};
struct supplier supplierData[100];

// for admin & customer
struct user
{
    int id;
    char Name[30];
    char Pass[20];
    char Email[50];
    char phn[15];
};
struct user adminData[50];
struct user customerData[100];

// customer payment-card data
struct card
{
    int cusID;
    char cardHolderName[20];
    int cardNum;
    int cvv;
    struct date cardDate;
    float balance;
};
struct card card[100];
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

// genarate random transection num
void generateTransactionNumber(char *transactionNum, int length)
{
    char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int charsetSize = sizeof(charset) - 1;

    for (int i = 0; i < length; i++)
    {
        transactionNum[i] = charset[rand() % charsetSize];
    }
    transactionNum[length] = '\0';
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
void dateTime() // Admin Home
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

void dateTimeForExpireProduct()
{
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    setColor(10);
    for (int i = 0; i <= 118; i++)
    {
        printf(" ");
    }
    printf("Date: %02d-%02d-%04d", t->tm_mday, t->tm_mon + 1, t->tm_year + 1900);
    setColor(7); // Reset color

    // take date for expired list
    currentDate.day = t->tm_mday;
    currentDate.mon = t->tm_mon + 1;
    currentDate.year = t->tm_year + 1900;
}
/*------------Date Time END---------*/
//
void currentDateTime()
{
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    currentDate.day = t->tm_mday;
    currentDate.mon = t->tm_mon + 1;
    currentDate.year = t->tm_year + 1900;
}
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

    listOfAdminData(); // encripted data here
    FILE *fp;
    int index;
    fp = fopen("admin_data/admin_index.txt", "r");
    fscanf(fp, "%d", &index);
    fclose(fp);

    decripTech(adminData, index); // decripted data

    for (int i = 0; i < index; i++)
    {
        if (strcmp(userName, adminData[i].Name) == 0 &&
            strcmp(userPass, adminData[i].Pass) == 0)
        {
            // update login status
            adminLoginStatus = 1;
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

    if (found) // user found
    {
        OnlineHome();
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

    // using caesar cypher
    for (int i = 0; (i < 100 && userPass[i] != '\0'); i++)
    {
        userPass[i] = userPass[i] + 5;
    }

    // User data send to file
    FILE *fp;
    fp = fopen("admin_data/data.txt", "a");
    fprintf(fp, "%s %s %s\n", userName, userPass, userEmail);
    fclose(fp);
    printf("\n\n");
    printCentered("Registration is successfull.", 10);
    printCentered("press any key to login......", 10);

    listOfAdminData();
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
    adminLoginStatus = 0;
    fp = fopen("login_Logout_status/logData.txt", "w");
    fprintf(fp, "%d", adminLoginStatus);
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

    // file management
    FILE *fp;
    int cID;
    fp = fopen("customer_data/customerID.txt", "r");
    fscanf(fp, "%d", &cID);
    fclose(fp);

    char userName[25];
    char userPass[25];
    char userEmail[30];
    char phn[15];

    int width = getConsoleWidth();
    int space = (width - 10) / 2;
    setColor(15); // start
    for (int i = 0; i < space; i++)
        printf(" ");
    printf("   ID : %d\n", cID);

    //-------space/input management for name-------//
    space = (width - 29) / 2;
    for (int i = 0; i < space; i++)
        printf(" ");
    printf(" Customer Name : ");
    scanf("%s", userName);

    //-------space/input management for password-------//
    space = (width - 35) / 2;
    for (int i = 0; i < space; i++)
        printf(" ");
    printf("Customer Password : ");
    scanf("%s", userPass);

    //-------space/input management for email-------//
    space = (width - 31) / 2;
    for (int i = 0; i < space; i++)
        printf(" ");
    printf(" Customer Email : ");
    scanf("%s", userEmail);

    //-------space/input management for Phone-------//
    space = (width - 31) / 2;
    for (int i = 0; i < space; i++)
        printf(" ");
    printf(" Customer Phone : ");
    scanf("%s", phn);

    printf("\n\n");
    // print payment card info
    // received data from file
    int cardNum, cardCVV, day, mon, year, balance;
    fp = fopen("payment_card/cardInfo.txt", "r");
    fscanf(fp, "%d %d %d %d %d %d\n", &cardNum, &cardCVV, &day, &mon, &year, &balance);
    fclose(fp);

    printCentered("Your Payment Card Info:", 9);
    printCentered("----------------------------", 9);
    space = (width - 26) / 2;
    for (int i = 0; i < space; i++)
        printf(" ");
    printf("  Card Holder Name: %s\n", userName);

    space = (width - 15) / 2;
    for (int i = 0; i < space; i++)
        printf(" ");
    printf(" Card Number: %ld\n", cardNum);

    space = (width - 13) / 2;
    for (int i = 0; i < space; i++)
        printf(" ");
    printf(" Card - CVV: %d\n", cardCVV);

    space = (width - 19) / 2;
    for (int i = 0; i < space; i++)
        printf(" ");
    printf("   Expire Date: %d-%d-%d\n", day, mon, year);

    space = (width - 24) / 2;
    for (int i = 0; i < space; i++)
        printf(" ");
    printf("  Opening Balance: %d\n", balance);

    // card info send to file
    fp = fopen("payment_card/cardData.txt", "a");
    fprintf(fp, "%d %s %d %d %d %d %d %d\n", cID, userName, cardNum, cardCVV, day, mon, year, balance);
    cardNum++, cardCVV++, year++;
    fclose(fp);

    // update card info
    fp = fopen("payment_card/cardInfo.txt", "w");
    fprintf(fp, "%d %d %d %d %d %d\n", cardNum, cardCVV, day, mon, year, balance);
    fclose(fp);

    // using caesar cypher
    for (int i = 0; (i < 100 && userPass[i] != '\0'); i++)
    {
        userPass[i] = userPass[i] + 5;
    }

    // User data send to file
    fp = fopen("customer_data/data.txt", "a");
    fprintf(fp, "%d %s %s %s %s\n", cID, userName, userPass, userEmail, phn);
    fclose(fp);

    // customer id send to file
    ++cID;
    fp = fopen("customer_data/customerID.txt", "w");
    fprintf(fp, "%d", cID);
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

    char current_user_customer2[20];
    int found = 0;
    int cusID2;
    char userName[25];
    char userName1[25];
    char userPass[25];
    char userPass1[25];
    char userEmail[30];
    char userEmail1[30];

    printf("Customer ID       : ");
    scanf("%d", &cusID2);
    printf("Customer Password : ");
    scanf("%s", userPass);

    // encripted data here
    listOfCustomerData();
    FILE *fp;
    int index;
    fp = fopen("customer_data/customer_index.txt", "r");
    fscanf(fp, "%d", &index);
    fclose(fp);
    int index2 = index;
    decripTech(customerData, index); // decripted data

    for (int i = 0; i < index; i++)
    {
        if (cusID2 == customerData[i].id &&
            strcmp(userPass, customerData[i].Pass) == 0)
        {
            // update login status
            customerLoginStatus = 1;
            fp = fopen("login_Logout_status/logData_customer.txt", "w");
            fprintf(fp, "%d", customerLoginStatus);
            fclose(fp);
            // update current customer name

            // find customer name
            for (int i = 0; i < index2; i++)
            {
                if (cusID2 == customerData[i].id)
                {
                    strcpy(current_user_customer2, customerData[i].Name);
                    fp = fopen("customer_data/current_user_customer.txt", "w");
                    fprintf(fp, "%s", current_user_customer2);
                    fclose(fp);

                    fp = fopen("customer_data/current_user_customer_ID.txt", "w");
                    fprintf(fp, "%d", cusID2);
                    fclose(fp);
                }
            }

            found = 1;
            break;
        }
    }

    if (found) // user found
    {
        // use this function when we manage customer profile or order place
        printf("log in successfull\n");
        _getch();
        OnlineHome();
    }

    else if (found == 0) // user not found
    {
        printf("\n\n");
        printCentered("Error userName or password.\n", 4);
        printCentered("1. Try Again.", 15);
        printCentered("    2. Reset Password.", 15);
        printCentered("      3. Authenticate Home.", 15);
        printCentered("  0. Exit Program.", 4);

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
void customerLogOut()
{

    FILE *fp;
    customerLoginStatus = 0;
    fp = fopen("login_Logout_status/logData_customer.txt", "w");
    fprintf(fp, "%d", customerLoginStatus);
    fclose(fp);
    OnlineHome(); // for custmer
}
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
    printCentered("          7. Expired Product.", 15);
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
    case 2:
        deleteProduct();
        break;
    case 3:
        listOfProduct();
        break;
    case 4:
        stockCheak();
        break;
    case 5:
        updateStock();
        break;
    case 6:
        stockListByCategory();
        break;
    case 7:
        expireProductList();
        break;
    case 0:
        adminPanelHome();
        break;
    default:
        printCentered("Invalid Choice!", 12);
        printCentered("Press any key", 10);
        _getch();
        adminPanelStock();
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
    printCentered("Input Product Information:", 15);
    printCentered(" -----------------------------------------------------", 9);

    int pID;
    char pName[20];
    int pPrice;
    int pUnit;
    char pCat[15];
    int proSupID; // product supplier id
    int day, mon, year;

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

    //-------space/input management for Category-------//
    space = (width - 17) / 2;
    for (int i = 0; i < space; i++)
        printf(" ");
    printf("  Expire Date : ", 15);
    scanf("%d %d %d", &day, &mon, &year);

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
    fprintf(fp, "%d %d %s %d %d %s %d %d %d\n", pID, proSupID, pName, pPrice, pUnit, pCat, day, mon, year);
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
            // delete process
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
                fprintf(fp, "%d %d %s %d %d %s %d %d %d\n", allProduct[j].pID, allProduct[j].proSupID, allProduct[j].pName, allProduct[j].pPrice, allProduct[j].pUnit, allProduct[j].pCat, allProduct[j].expDate.day, allProduct[j].expDate.mon, allProduct[j].expDate.year);
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
    printCentered("  ------------------------------------------------------------------------------------------------------------------------------", 9);
    printCentered("     NO:     Product-ID:     Supplier-ID      Product-Name:     Product-Price:        Unit:       Category:        Expire Date:", 15);
    printCentered("  ------------------------------------------------------------------------------------------------------------------------------", 9);
    allProductData();
    int index, serNum = 1;
    FILE *fp;
    fp = fopen("Stock/index/all_product_index.txt", "r");
    fscanf(fp, "%d", &index);
    // pID, proSupID, pCat, pName, pPrice, pUnit);
    for (int i = 0; i < index; i++)
    {
        printf("                   %d        %d          %d             %s           %d.00TK           %d (P)        %s         %d-%d-%d\n", serNum++, allProduct[i].pID, allProduct[i].proSupID, allProduct[i].pName, allProduct[i].pPrice, allProduct[i].pUnit, allProduct[i].pCat, allProduct[i].expDate.day, allProduct[i].expDate.mon, allProduct[i].expDate.year);
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
            fprintf(fp, "%d %d %s %d %d %s %d %d %d\n", allProduct[j].pID, allProduct[j].proSupID, allProduct[j].pName, allProduct[j].pPrice, allProduct[j].pUnit, allProduct[j].pCat, allProduct[i].expDate.day, allProduct[i].expDate.mon, allProduct[i].expDate.year);
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
            printCentered("      NO:     Product-ID:     Supplier-ID      Product-Name:     Product-Price:        Unit:       Category:        Expire Date:", 15);
            printCentered("     --------------------------------------------------------------------------------------------------------------------------", 12);

            for (int j = i; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "computer") == 0)
                {
                    printf("                      %d        %d          %d             %s           %d.00TK           %d (P)        %s          %d-%d-%d\n", serNum++, allProduct[j].pID, allProduct[j].proSupID, allProduct[j].pName, allProduct[j].pPrice, allProduct[j].pUnit, allProduct[j].pCat, allProduct[j].expDate.day, allProduct[j].expDate.mon, allProduct[j].expDate.year);
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
            printCentered("      NO:     Product-ID:     Supplier-ID      Product-Name:     Product-Price:        Unit:       Category:        Expire Date:", 15);
            printCentered("     --------------------------------------------------------------------------------------------------------------------------", 12);

            for (int j = i; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "books") == 0)
                {
                    printf("                     %d        %d          %d             %s           %d.00TK           %d (P)        %s          %d-%d-%d\n", serNum++, allProduct[j].pID, allProduct[j].proSupID, allProduct[j].pName, allProduct[j].pPrice, allProduct[j].pUnit, allProduct[j].pCat, allProduct[j].expDate.day, allProduct[j].expDate.mon, allProduct[j].expDate.year);
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
            printCentered("      NO:     Product-ID:     Supplier-ID      Product-Name:     Product-Price:        Unit:       Category:        Expire Date:", 15);
            printCentered("     --------------------------------------------------------------------------------------------------------------------------", 12);

            for (int j = i; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "medicine") == 0)
                {
                    printf("                     %d        %d          %d             %s           %d.00TK           %d (P)        %s          %d-%d-%d\n", serNum++, allProduct[j].pID, allProduct[j].proSupID, allProduct[j].pName, allProduct[j].pPrice, allProduct[j].pUnit, allProduct[j].pCat, allProduct[j].expDate.day, allProduct[j].expDate.mon, allProduct[j].expDate.year);
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
            printCentered("      NO:     Product-ID:     Supplier-ID      Product-Name:     Product-Price:        Unit:       Category:        Expire Date:", 15);
            printCentered("     --------------------------------------------------------------------------------------------------------------------------", 12);

            for (int j = i; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "camera") == 0)
                {
                    printf("                     %d        %d          %d             %s           %d.00TK           %d (P)        %s          %d-%d-%d\n", serNum++, allProduct[j].pID, allProduct[j].proSupID, allProduct[j].pName, allProduct[j].pPrice, allProduct[j].pUnit, allProduct[j].pCat, allProduct[j].expDate.day, allProduct[j].expDate.mon, allProduct[j].expDate.year);
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
            printCentered("      NO:     Product-ID:     Supplier-ID      Product-Name:     Product-Price:        Unit:       Category:        Expire Date:", 15);
            printCentered("     --------------------------------------------------------------------------------------------------------------------------", 12);

            for (int j = i; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "television") == 0)
                {
                    printf("                     %d        %d          %d             %s           %d.00TK           %d (P)        %s          %d-%d-%d\n", serNum++, allProduct[j].pID, allProduct[j].proSupID, allProduct[j].pName, allProduct[j].pPrice, allProduct[j].pUnit, allProduct[j].pCat, allProduct[j].expDate.day, allProduct[j].expDate.mon, allProduct[j].expDate.year);
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
            printCentered("Watches", 12);
            printCentered("  ----------------------", 12);
            printCentered("      NO:     Product-ID:     Supplier-ID      Product-Name:     Product-Price:        Unit:       Category:        Expire Date:", 15);
            printCentered("     --------------------------------------------------------------------------------------------------------------------------", 12);

            for (int j = i; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "watches") == 0)
                {
                    printf("                     %d        %d          %d             %s           %d.00TK           %d (P)        %s          %d-%d-%d\n", serNum++, allProduct[j].pID, allProduct[j].proSupID, allProduct[j].pName, allProduct[j].pPrice, allProduct[j].pUnit, allProduct[j].pCat, allProduct[j].expDate.day, allProduct[j].expDate.mon, allProduct[j].expDate.year);
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
            printCentered("      NO:     Product-ID:     Supplier-ID      Product-Name:     Product-Price:        Unit:       Category:        Expire Date:", 15);
            printCentered("     --------------------------------------------------------------------------------------------------------------------------", 12);

            for (int j = i; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "fragrances") == 0)
                {
                    printf("                     %d        %d          %d             %s           %d.00TK           %d (P)        %s          %d-%d-%d\n", serNum++, allProduct[j].pID, allProduct[j].proSupID, allProduct[j].pName, allProduct[j].pPrice, allProduct[j].pUnit, allProduct[j].pCat, allProduct[j].expDate.day, allProduct[j].expDate.mon, allProduct[j].expDate.year);
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
            printCentered("      NO:     Product-ID:     Supplier-ID      Product-Name:     Product-Price:        Unit:       Category:        Expire Date:", 15);
            printCentered("     --------------------------------------------------------------------------------------------------------------------------", 12);

            for (int j = i; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "beverages") == 0)
                {
                    printf("                     %d        %d          %d             %s           %d.00TK           %d (P)        %s          %d-%d-%d\n", serNum++, allProduct[j].pID, allProduct[j].proSupID, allProduct[j].pName, allProduct[j].pPrice, allProduct[j].pUnit, allProduct[j].pCat, allProduct[j].expDate.day, allProduct[j].expDate.mon, allProduct[j].expDate.year);
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
            printCentered("      NO:     Product-ID:     Supplier-ID      Product-Name:     Product-Price:        Unit:       Category:        Expire Date:", 15);
            printCentered("     --------------------------------------------------------------------------------------------------------------------------", 12);

            for (int j = i; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "mobile") == 0)
                {
                    printf("                     %d        %d          %d             %s           %d.00TK           %d (P)        %s          %d-%d-%d\n", serNum++, allProduct[j].pID, allProduct[j].proSupID, allProduct[j].pName, allProduct[j].pPrice, allProduct[j].pUnit, allProduct[j].pCat, allProduct[j].expDate.day, allProduct[j].expDate.mon, allProduct[j].expDate.year);
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
            printCentered("      NO:     Product-ID:     Supplier-ID      Product-Name:     Product-Price:        Unit:       Category:        Expire Date:", 15);
            printCentered("     --------------------------------------------------------------------------------------------------------------------------", 12);

            for (int j = i; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "software") == 0)
                {
                    printf("                     %d        %d          %d             %s           %d.00TK           %d (P)        %s          %d-%d-%d\n", serNum++, allProduct[j].pID, allProduct[j].proSupID, allProduct[j].pName, allProduct[j].pPrice, allProduct[j].pUnit, allProduct[j].pCat, allProduct[j].expDate.day, allProduct[j].expDate.mon, allProduct[j].expDate.year);
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
/*---------------Admin Panel Expired List Start----------------*/
void expireProductList()
{
    char headingName[40] = "Stock / Product";
    menuUI(headingName);
    printCentered2(current_user_admin, "Home | Contact | About | Profile. ", 11);
    printf("\n");
    printCentered("OneMart", 10);
    printCentered("------------------------", 10);
    printf("\n");

    printCentered("Expired Product List By Category", 9);
    printCentered("    -------------------------------------------------------------------------------------------------------------------------", 9);

    // take index num from file
    int index, serNum = 1;
    FILE *fp;
    fp = fopen("Stock/index/all_product_index.txt", "r");
    fscanf(fp, "%d", &index);
    fclose(fp);

    allProductData();           // get latest all product
    dateTimeForExpireProduct(); // get latest date - currentDate

    // For computer
    for (int i = 0; i < index; i++)
    {
        int serNum = 1;
        if (strcmp(allProduct[i].pCat, "computer") == 0)
        {
            for (int j = 0; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "computer") == 0)
                {
                    if (allProduct[j].expDate.year < currentDate.year ||
                        (allProduct[j].expDate.year == currentDate.year && allProduct[j].expDate.mon < currentDate.mon) ||
                        (allProduct[j].expDate.year == currentDate.year && allProduct[j].expDate.mon == currentDate.mon && allProduct[j].expDate.day < currentDate.day))
                    {
                        printf("\n\n");
                        printCentered("Computer", 12);
                        printCentered("  ----------------------", 12);
                        printCentered("      NO:     Product-ID:     Supplier-ID      Product-Name:     Product-Price:        Unit:       Category:        Expire Date:", 15);
                        printCentered("     --------------------------------------------------------------------------------------------------------------------------", 12);

                        for (int k = 0; k < index; k++)
                        {
                            if (strcmp(allProduct[k].pCat, "computer") == 0)
                            {
                                if (allProduct[k].expDate.year < currentDate.year ||
                                    (allProduct[k].expDate.year == currentDate.year && allProduct[k].expDate.mon < currentDate.mon) ||
                                    (allProduct[k].expDate.year == currentDate.year && allProduct[k].expDate.mon == currentDate.mon && allProduct[k].expDate.day < currentDate.day))
                                {
                                    printf("                    %d        %d          %d             %s           %d.00TK           %d (P)        %s          %d-%d-%d\n", serNum++, allProduct[k].pID, allProduct[k].proSupID, allProduct[k].pName, allProduct[k].pPrice, allProduct[k].pUnit, allProduct[k].pCat, allProduct[k].expDate.day, allProduct[k].expDate.mon, allProduct[k].expDate.year);
                                }
                            }
                        }
                        break;
                    }
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
            for (int j = 0; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "books") == 0)
                {
                    if (allProduct[j].expDate.year < currentDate.year ||
                        (allProduct[j].expDate.year == currentDate.year && allProduct[j].expDate.mon < currentDate.mon) ||
                        (allProduct[j].expDate.year == currentDate.year && allProduct[j].expDate.mon == currentDate.mon && allProduct[j].expDate.day < currentDate.day))
                    {
                        printf("\n\n");
                        printCentered("Books", 12);
                        printCentered("  ----------------------", 12);
                        printCentered("      NO:     Product-ID:     Supplier-ID      Product-Name:     Product-Price:        Unit:       Category:        Expire Date:", 15);
                        printCentered("     --------------------------------------------------------------------------------------------------------------------------", 12);

                        for (int k = 0; k < index; k++)
                        {
                            if (strcmp(allProduct[k].pCat, "books") == 0)
                            {
                                if (allProduct[k].expDate.year < currentDate.year ||
                                    (allProduct[k].expDate.year == currentDate.year && allProduct[k].expDate.mon < currentDate.mon) ||
                                    (allProduct[k].expDate.year == currentDate.year && allProduct[k].expDate.mon == currentDate.mon && allProduct[k].expDate.day < currentDate.day))
                                {
                                    printf("                     %d        %d          %d             %s           %d.00TK           %d (P)        %s          %d-%d-%d\n", serNum++, allProduct[k].pID, allProduct[k].proSupID, allProduct[k].pName, allProduct[k].pPrice, allProduct[k].pUnit, allProduct[k].pCat, allProduct[k].expDate.day, allProduct[k].expDate.mon, allProduct[k].expDate.year);
                                }
                            }
                        }
                        break;
                    }
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
            for (int j = 0; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "medicine") == 0)
                {
                    if (allProduct[j].expDate.year < currentDate.year ||
                        (allProduct[j].expDate.year == currentDate.year && allProduct[j].expDate.mon < currentDate.mon) ||
                        (allProduct[j].expDate.year == currentDate.year && allProduct[j].expDate.mon == currentDate.mon && allProduct[j].expDate.day < currentDate.day))
                    {
                        printf("\n\n");
                        printCentered("Medicine", 12);
                        printCentered("  ----------------------", 12);
                        printCentered("      NO:     Product-ID:     Supplier-ID      Product-Name:     Product-Price:        Unit:       Category:        Expire Date:", 15);
                        printCentered("     --------------------------------------------------------------------------------------------------------------------------", 12);

                        for (int k = 0; k < index; k++)
                        {
                            if (strcmp(allProduct[k].pCat, "medicine") == 0)
                            {
                                if (allProduct[k].expDate.year < currentDate.year ||
                                    (allProduct[k].expDate.year == currentDate.year && allProduct[k].expDate.mon < currentDate.mon) ||
                                    (allProduct[k].expDate.year == currentDate.year && allProduct[k].expDate.mon == currentDate.mon && allProduct[k].expDate.day < currentDate.day))
                                {
                                    printf("                     %d        %d          %d             %s           %d.00TK           %d (P)        %s          %d-%d-%d\n", serNum++, allProduct[k].pID, allProduct[k].proSupID, allProduct[k].pName, allProduct[k].pPrice, allProduct[k].pUnit, allProduct[k].pCat, allProduct[k].expDate.day, allProduct[k].expDate.mon, allProduct[k].expDate.year);
                                }
                            }
                        }
                        break;
                    }
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
            for (int j = 0; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "camera") == 0)
                {
                    if (allProduct[j].expDate.year < currentDate.year ||
                        (allProduct[j].expDate.year == currentDate.year && allProduct[j].expDate.mon < currentDate.mon) ||
                        (allProduct[j].expDate.year == currentDate.year && allProduct[j].expDate.mon == currentDate.mon && allProduct[j].expDate.day < currentDate.day))
                    {
                        printf("\n\n");
                        printCentered("Camera", 12);
                        printCentered("  ----------------------", 12);
                        printCentered("      NO:     Product-ID:     Supplier-ID      Product-Name:     Product-Price:        Unit:       Category:        Expire Date:", 15);
                        printCentered("     --------------------------------------------------------------------------------------------------------------------------", 12);

                        for (int k = 0; k < index; k++)
                        {
                            if (strcmp(allProduct[k].pCat, "camera") == 0)
                            {
                                if (allProduct[k].expDate.year < currentDate.year ||
                                    (allProduct[k].expDate.year == currentDate.year && allProduct[k].expDate.mon < currentDate.mon) ||
                                    (allProduct[k].expDate.year == currentDate.year && allProduct[k].expDate.mon == currentDate.mon && allProduct[k].expDate.day < currentDate.day))
                                {
                                    printf("                     %d        %d          %d             %s           %d.00TK           %d (P)        %s          %d-%d-%d\n", serNum++, allProduct[k].pID, allProduct[k].proSupID, allProduct[k].pName, allProduct[k].pPrice, allProduct[k].pUnit, allProduct[k].pCat, allProduct[k].expDate.day, allProduct[k].expDate.mon, allProduct[k].expDate.year);
                                }
                            }
                        }
                        break;
                    }
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
            for (int j = 0; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "television") == 0)
                {
                    if (allProduct[j].expDate.year < currentDate.year ||
                        (allProduct[j].expDate.year == currentDate.year && allProduct[j].expDate.mon < currentDate.mon) ||
                        (allProduct[j].expDate.year == currentDate.year && allProduct[j].expDate.mon == currentDate.mon && allProduct[j].expDate.day < currentDate.day))
                    {
                        printf("\n\n");
                        printCentered("Television", 12);
                        printCentered("  ----------------------", 12);
                        printCentered("      NO:     Product-ID:     Supplier-ID      Product-Name:     Product-Price:        Unit:       Category:        Expire Date:", 15);
                        printCentered("     --------------------------------------------------------------------------------------------------------------------------", 12);

                        for (int k = 0; k < index; k++)
                        {
                            if (strcmp(allProduct[k].pCat, "television") == 0)
                            {
                                if (allProduct[k].expDate.year < currentDate.year ||
                                    (allProduct[k].expDate.year == currentDate.year && allProduct[k].expDate.mon < currentDate.mon) ||
                                    (allProduct[k].expDate.year == currentDate.year && allProduct[k].expDate.mon == currentDate.mon && allProduct[k].expDate.day < currentDate.day))
                                {
                                    printf("                     %d        %d          %d             %s           %d.00TK           %d (P)        %s          %d-%d-%d\n", serNum++, allProduct[k].pID, allProduct[k].proSupID, allProduct[k].pName, allProduct[k].pPrice, allProduct[k].pUnit, allProduct[k].pCat, allProduct[k].expDate.day, allProduct[k].expDate.mon, allProduct[k].expDate.year);
                                }
                            }
                        }
                        break;
                    }
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
            for (int j = 0; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "watches") == 0)
                {
                    if (allProduct[j].expDate.year < currentDate.year ||
                        (allProduct[j].expDate.year == currentDate.year && allProduct[j].expDate.mon < currentDate.mon) ||
                        (allProduct[j].expDate.year == currentDate.year && allProduct[j].expDate.mon == currentDate.mon && allProduct[j].expDate.day < currentDate.day))
                    {
                        printf("\n\n");
                        printCentered("Watches", 12);
                        printCentered("  ----------------------", 12);
                        printCentered("      NO:     Product-ID:     Supplier-ID      Product-Name:     Product-Price:        Unit:       Category:        Expire Date:", 15);
                        printCentered("     --------------------------------------------------------------------------------------------------------------------------", 12);

                        for (int k = 0; k < index; k++)
                        {
                            if (strcmp(allProduct[k].pCat, "watches") == 0)
                            {
                                if (allProduct[k].expDate.year < currentDate.year ||
                                    (allProduct[k].expDate.year == currentDate.year && allProduct[k].expDate.mon < currentDate.mon) ||
                                    (allProduct[k].expDate.year == currentDate.year && allProduct[k].expDate.mon == currentDate.mon && allProduct[k].expDate.day < currentDate.day))
                                {
                                    printf("                     %d        %d          %d             %s           %d.00TK           %d (P)        %s          %d-%d-%d\n", serNum++, allProduct[k].pID, allProduct[k].proSupID, allProduct[k].pName, allProduct[k].pPrice, allProduct[k].pUnit, allProduct[k].pCat, allProduct[k].expDate.day, allProduct[k].expDate.mon, allProduct[k].expDate.year);
                                }
                            }
                        }
                        break;
                    }
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
            for (int j = 0; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "fragrances") == 0)
                {
                    if (allProduct[j].expDate.year < currentDate.year ||
                        (allProduct[j].expDate.year == currentDate.year && allProduct[j].expDate.mon < currentDate.mon) ||
                        (allProduct[j].expDate.year == currentDate.year && allProduct[j].expDate.mon == currentDate.mon && allProduct[j].expDate.day < currentDate.day))
                    {
                        printf("\n\n");
                        printCentered("Fragrances", 12);
                        printCentered("  ----------------------", 12);
                        printCentered("      NO:     Product-ID:     Supplier-ID      Product-Name:     Product-Price:        Unit:       Category:        Expire Date:", 15);
                        printCentered("     --------------------------------------------------------------------------------------------------------------------------", 12);

                        for (int k = 0; k < index; k++)
                        {
                            if (strcmp(allProduct[k].pCat, "fragrances") == 0)
                            {
                                if (allProduct[k].expDate.year < currentDate.year ||
                                    (allProduct[k].expDate.year == currentDate.year && allProduct[k].expDate.mon < currentDate.mon) ||
                                    (allProduct[k].expDate.year == currentDate.year && allProduct[k].expDate.mon == currentDate.mon && allProduct[k].expDate.day < currentDate.day))
                                {
                                    printf("                     %d        %d          %d             %s           %d.00TK           %d (P)        %s          %d-%d-%d\n", serNum++, allProduct[k].pID, allProduct[k].proSupID, allProduct[k].pName, allProduct[k].pPrice, allProduct[k].pUnit, allProduct[k].pCat, allProduct[k].expDate.day, allProduct[k].expDate.mon, allProduct[k].expDate.year);
                                }
                            }
                        }
                        break;
                    }
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
            for (int j = 0; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "beverages") == 0)
                {
                    if (allProduct[j].expDate.year < currentDate.year ||
                        (allProduct[j].expDate.year == currentDate.year && allProduct[j].expDate.mon < currentDate.mon) ||
                        (allProduct[j].expDate.year == currentDate.year && allProduct[j].expDate.mon == currentDate.mon && allProduct[j].expDate.day < currentDate.day))
                    {
                        printf("\n\n");
                        printCentered("Beverages", 12);
                        printCentered("  ----------------------", 12);
                        printCentered("      NO:     Product-ID:     Supplier-ID      Product-Name:     Product-Price:        Unit:       Category:        Expire Date:", 15);
                        printCentered("     --------------------------------------------------------------------------------------------------------------------------", 12);

                        for (int k = 0; k < index; k++)
                        {
                            if (strcmp(allProduct[k].pCat, "beverages") == 0)
                            {
                                if (allProduct[k].expDate.year < currentDate.year ||
                                    (allProduct[k].expDate.year == currentDate.year && allProduct[k].expDate.mon < currentDate.mon) ||
                                    (allProduct[k].expDate.year == currentDate.year && allProduct[k].expDate.mon == currentDate.mon && allProduct[k].expDate.day < currentDate.day))
                                {
                                    printf("                    %d        %d          %d             %s           %d.00TK           %d (P)        %s          %d-%d-%d\n", serNum++, allProduct[k].pID, allProduct[k].proSupID, allProduct[k].pName, allProduct[k].pPrice, allProduct[k].pUnit, allProduct[k].pCat, allProduct[k].expDate.day, allProduct[k].expDate.mon, allProduct[k].expDate.year);
                                }
                            }
                        }
                        break;
                    }
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
            for (int j = 0; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "mobile") == 0)
                {
                    if (allProduct[j].expDate.year < currentDate.year ||
                        (allProduct[j].expDate.year == currentDate.year && allProduct[j].expDate.mon < currentDate.mon) ||
                        (allProduct[j].expDate.year == currentDate.year && allProduct[j].expDate.mon == currentDate.mon && allProduct[j].expDate.day < currentDate.day))
                    {
                        printf("\n\n");
                        printCentered("Mobile", 12);
                        printCentered("  ----------------------", 12);
                        printCentered("      NO:     Product-ID:     Supplier-ID      Product-Name:     Product-Price:        Unit:       Category:        Expire Date:", 15);
                        printCentered("     --------------------------------------------------------------------------------------------------------------------------", 12);

                        for (int k = 0; k < index; k++)
                        {
                            if (strcmp(allProduct[k].pCat, "mobile") == 0)
                            {
                                if (allProduct[k].expDate.year < currentDate.year ||
                                    (allProduct[k].expDate.year == currentDate.year && allProduct[k].expDate.mon < currentDate.mon) ||
                                    (allProduct[k].expDate.year == currentDate.year && allProduct[k].expDate.mon == currentDate.mon && allProduct[k].expDate.day < currentDate.day))
                                {
                                    printf("                     %d        %d          %d             %s           %d.00TK           %d (P)        %s          %d-%d-%d\n", serNum++, allProduct[k].pID, allProduct[k].proSupID, allProduct[k].pName, allProduct[k].pPrice, allProduct[k].pUnit, allProduct[k].pCat, allProduct[k].expDate.day, allProduct[k].expDate.mon, allProduct[k].expDate.year);
                                }
                            }
                        }
                        break;
                    }
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
            for (int j = 0; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "software") == 0)
                {
                    if (allProduct[j].expDate.year < currentDate.year ||
                        (allProduct[j].expDate.year == currentDate.year && allProduct[j].expDate.mon < currentDate.mon) ||
                        (allProduct[j].expDate.year == currentDate.year && allProduct[j].expDate.mon == currentDate.mon && allProduct[j].expDate.day < currentDate.day))
                    {
                        printf("\n\n");
                        printCentered("Software", 12);
                        printCentered("  ----------------------", 12);
                        printCentered("      NO:     Product-ID:     Supplier-ID      Product-Name:     Product-Price:        Unit:       Category:        Expire Date:", 15);
                        printCentered("     --------------------------------------------------------------------------------------------------------------------------", 12);

                        for (int k = 0; k < index; k++)
                        {
                            if (strcmp(allProduct[k].pCat, "software") == 0)
                            {
                                if (allProduct[k].expDate.year < currentDate.year ||
                                    (allProduct[k].expDate.year == currentDate.year && allProduct[k].expDate.mon < currentDate.mon) ||
                                    (allProduct[k].expDate.year == currentDate.year && allProduct[k].expDate.mon == currentDate.mon && allProduct[k].expDate.day < currentDate.day))
                                {
                                    printf("                     %d        %d          %d             %s           %d.00TK           %d (P)        %s          %d-%d-%d\n", serNum++, allProduct[k].pID, allProduct[k].proSupID, allProduct[k].pName, allProduct[k].pPrice, allProduct[k].pUnit, allProduct[k].pCat, allProduct[k].expDate.day, allProduct[k].expDate.mon, allProduct[k].expDate.year);
                                }
                            }
                        }
                        break;
                    }
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
    printCentered("1. OnePay", 15);
    printCentered("           2. Order Pending List", 15);
    printCentered("             3. Order Delivered List", 15);
    printCentered("   0. Admin-Home", 4);
    printf("\n\n\n");

    int option;
    printf("\n\nEnter your choice: ");
    scanf("%d", &option);
    switch (option)
    {
    case 1:
        OnePayManagement();
        break;
    case 2:
        orderPendingList();
        break;
        // yet not done
    case 3:
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
//*------------------Onepay Management Start----------------*/
void OnePayManagement()
{
    char headingName[40] = "OnePay - Online Card";
    menuUI(headingName);
    printCentered2(current_user_admin, "Home | Contact | About | Profile. ", 11);
    printf("\n\n");
    printCentered("OneMart", 10);
    printCentered("------------------------", 10);
    printf("\n");
    printCentered("OnePay Maanagement", 15);
    printCentered("-------------------------------", 15);
    printCentered("     1. List OnePay Card", 15);
    printCentered("          2. Recharge OnePay Card", 15);
    printCentered("0. Admin-Home", 4);
    printf("\n\n\n");

    int option;
    printf("\n\nEnter your choice: ");
    scanf("%d", &option);
    switch (option)
    {
    case 1:
        listOfCard();
        break;
    case 2:
        rechargeCard();
        break;
        // yet not done
    case 0:
        adminPanelHome();
        break;
    default:
        printCentered("Invalid Choice!", 12);
        printCentered("Press any key", 10);
        _getch();
        OnePayManagement();
    }

    _getch();
}
//*------------------Onepay Management End------------------*/
//
//
//
//*------------------list of Onepay start------------------*/
void listOfCard()
{
    char headingName[40] = "OnePay - Online Card";
    menuUI(headingName);
    printCentered2(current_user_admin, "Home | Contact | About | Profile. ", 11);
    printf("\n\n");
    printCentered("OneMart", 10);
    printCentered("------------------------", 10);

    printCentered("All OnePay Card List", 9);
    printCentered("  ------------------------------------------------------------------------------------------------------------------------------", 9);
    printCentered("    No.       Card-No:       Card Holder-Id:         Card Holder-Name:         CVV:            Balance:            Expire Date:", 15);
    printCentered("  ------------------------------------------------------------------------------------------------------------------------------", 9);
    cardData();

    int index, serNum = 1;
    FILE *fp;
    fp = fopen("payment_card/card_index.txt", "r");
    fscanf(fp, "%d", &index);
    fclose(fp);
    for (int i = 0; i < index; i++)
    {
        printf("                  %d         %d          %d               %s                 %d               %f Tk.          %d-%d-%d\n", serNum++, card[i].cardNum, card[i].cusID, card[i].cardHolderName, card[i].cvv, card[i].balance, card[i].cardDate.day, card[i].cardDate.mon, card[i].cardDate.year);
    }

    printf("\n\n\n");
    printCentered("Press any key to return Home.....", 10);
    _getch();
    adminPanelOnlineStore();
}
//*------------------list of Onepay End------------------*/
//
//
//
//*------------------Onepay Recharge start------------------*/
void rechargeCard()
{
}
//*------------------Onepay Management End------------------*/
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
    printCentered("    1. Daily Income", 15);
    printCentered("     2. Monthly Income", 15);
    printCentered("          3. Half Yearly Income", 15);
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
    printCentered("  1. Add Supplier", 15);
    printCentered("      2. Delete Supplier.", 15);
    printCentered("    3. Product Search", 15);
    printCentered("                 4. List Of Product by Supplier", 15);
    printCentered("   5. Supplier List", 15);
    printCentered(" 0. Admin-Home.", 4);
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

    case 3:
        productSearch();
        break;
        // yet not done

    case 4:
        listOfProductBySupplier();
        break;

    case 5:
        supplierList();
        break;

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

    // supplier id send to file
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
                        printf("                               %d        %d          %d            %s            %d.00TK         %d (P)      %s\n", serNum++, allProduct[j].pID, allProduct[j].proSupID, allProduct[j].pName, allProduct[j].pPrice, allProduct[j].pUnit, allProduct[j].pCat);
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
        printf("                                               %d     %d       %s      %s       %s\n", serNum, supplierID, supName);
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
    printCentered("    3. Password Reset                     7. Password Reset", 15);
    printCentered("      4. List Of Admin                      8. List Of Customer", 15);
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

    case 2:
        deleteAdmin();
        break;

    case 3:
        adminPasswordReset();
        break;

    case 4:
        listOfAdmin();
        break;

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
        printCentered("Press any key to return home..", 10);
        _getch();
        adminPanelUserManagement();
    }
}
//*---------------Admin Panel Supplier Management End ----------------*/
//
//
//
//*---------------Admin Panel (USER) Add Admin Start----------------*/
void addAdmin()
{
    // adding admin
    char headingName[40] = "Admin Management";
    menuUI(headingName);
    printCentered2(current_user_admin, "Home | Contact | About | Profile. ", 11);
    printf("\n\n");
    printCentered("OneMart", 10);
    printCentered("------------------------", 10);
    printf("\n");
    printCentered("Input Admin Information:", 15);
    printCentered("------------------------------", 15);

    // variable declare
    char adName[30];
    char adPass[20];
    char adEmail[50];
    int adIndex;

    int width = getConsoleWidth();
    int space = (width - 5) / 2;
    setColor(15);

    //-------space/input management for name-------//
    space = (width - 12) / 2;
    for (int i = 0; i < space; i++)
        printf(" ");
    printf("  User Name  : ");
    scanf("%s", adName);

    //-------space/input management for password-------//
    space = (width - 14) / 2;
    for (int i = 0; i < space; i++)
        printf(" ");
    printf("    Password  : ");
    scanf("%s", adPass);

    //-------space/input management for email-------//
    space = (width - 11) / 2;
    for (int i = 0; i < space; i++)
        printf(" ");
    printf("     Email  : ", 15);
    scanf("%s", adEmail);
    setColor(7); // reset color

    // using caesar cypher to encript
    for (int i = 0; (i < 100 && adPass[i] != '\0'); i++)
    {
        adPass[i] = adPass[i] + 5;
    }

    // data send to file
    FILE *fp;
    fp = fopen("admin_data/data.txt", "a");
    fprintf(fp, "%s %s %s\n", adName, adPass, adEmail);
    fclose(fp);

    // admin index send to file
    fp = fopen("admin_data/admin_index.txt", "r");
    fscanf(fp, "%d", &adIndex);
    fclose(fp);

    adIndex = adIndex + 1;

    fp = fopen("admin_data/admin_index.txt", "w");
    fprintf(fp, "%d", adIndex);
    fclose(fp);

    printf("\n\n\n");
    printCentered("'Admin Added'....Press any key to return Home.", 10);
    _getch();
    adminPanelUserManagement(); // home
}
//*---------------Admin Panel (USER) Add Admin End----------------*/
//
//
//
//*---------------Admin Panel (USER) Delete Admin Start----------------*/
void deleteAdmin()
{
    char headingName[40] = "Admin Management";
    menuUI(headingName);
    printCentered2(current_user_admin, "Home | Contact | About | Profile. ", 11);
    printf("\n");
    printCentered("OneMart", 10);
    printCentered("------------------------", 10);
    printf("\n\n");
    printCentered("Admin Deletation", 15);
    printCentered(" -----------------------", 9);

    int index;
    char Admin_Name[30];
    int width = getConsoleWidth();
    int space = (width - 18) / 2;
    setColor(15);
    for (int i = 0; i < space; i++)
        printf(" ");
    printf("Input Admin Name: ", 15);
    scanf("%s", Admin_Name);
    printf("\n");

    listOfAdminData(); // get latest Admin data
    FILE *fp;
    fp = fopen("admin_data/admin_index.txt", "r");
    fscanf(fp, "%d", &index); // get Admin Name
    fclose(fp);

    // find del position
    int deletePos, i, found = 0;
    for (i = 0; i < index; i++)
    {

        if (strcmp(adminData[i].Name, Admin_Name) == 0)
        {
            deletePos = i;
            found = 1;
            break;
        }
    }

    // if Admin found
    if (found)
    {
        printCentered("Admin Found...", 10);
        printCentered("-----------------------", 10);
        printCentered("   Name:            Email:    ", 15);
        printCentered("----------------------------------------------------------------", 9);

        printf("                                        %s             %s\n", adminData[deletePos].Name, adminData[deletePos].Email);
        printf("\n\n\n\n\n");
        printCentered("     Are you sure you want to delete?", 15);
        printCentered("     1. YES", 10);
        printCentered("    2. NO", 4);

        // take input
        int option;
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
                adminData[j] = adminData[j + 1];
            }
            index = index - 1;

            // Latest Data Send to Admin - FILE
            fp = fopen("admin_data/data.txt", "w"); // reset previous data
            fclose(fp);
            fp = fopen("admin_data/data.txt", "a");
            for (int j = 0; j < index; j++)
            {
                fprintf(fp, "%s %s %s\n", adminData[j].Name, adminData[j].Pass, adminData[j].Email);
            }
            fclose(fp);

            // send index to admin index
            fp = fopen("admin_data/admin_index.txt", "w");
            fprintf(fp, "%d", index);
            fclose(fp);

            printf("\n\n");
            printCentered("'Admin Deleted'....Press any key to return Home.", 4);
            _getch();
            adminPanelUserManagement();

        case 2:
            printCentered("Deletation cancel!", 4);
            printf("\n\n");
            printCentered("          Press any key to return Home.....", 10);
            _getch();
            adminPanelUserManagement();
        }
    }
    else
    {
        printCentered("     Admin has not been found!", 4);
        printf("\n\n");
        printCentered("          Press any key to return Home.....", 10);
        _getch();
        adminPanelUserManagement();
    }
}
//*---------------Admin Panel (USER) Delete Admin End----------------*/
//
//
//
//*---------------Admin Panel (USER) Admin Pass Reset Start----------------*/
void adminPasswordReset()
{
    char headingName[40] = "Admin Management";
    menuUI(headingName);
    printCentered2(current_user_admin, "Home | Contact | About | Profile. ", 11);
    printf("\n");
    printCentered("OneMart", 10);
    printCentered("------------------------", 10);
    printf("\n\n");
    printCentered("Admin Password Reset", 15);
    printCentered(" --------------------------", 9);
    printf("\n\n");

    int index;
    char adPass[20];
    char adName[30];

    FILE *fp;
    fp = fopen("admin_data/admin_index.txt", "r");
    fscanf(fp, "%d", &index);
    fclose(fp);

    listOfAdminData(); // encripted data
    decripTech(adminData, index);

    int width = getConsoleWidth();
    int space = (width - 18) / 2;
    setColor(15);
    for (int i = 0; i < space; i++)
        printf(" ");
    printf("Input Admin Name: ", 15);
    scanf("%s", adName);
    printf("\n");

    int pass, i, found = 0;
    for (i = 0; i < index; i++)
    {

        if (strcmp(adminData[i].Name, adName) == 0)
        {
            pass = i;
            found = 1;
            break;
        }
    }

    // Admin found
    if (found)
    {
        printCentered("Admin Found...", 10);
        printCentered("-----------------------", 10);
        printCentered("   Name:            Email:    ", 15);
        printCentered("----------------------------------------------------------------", 9);

        printf("                                                            %s                %s\n", adminData[pass].Name, adminData[pass].Email);
        printf("\n\n\n\n\n");
        printCentered("     Are you sure you want to change Password?", 15);
        printCentered("     1. YES", 10);
        printCentered("    2. NO", 4);

        // take input
        int option;
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

            for (int i = 0; i < space; i++)
                printf(" ");
            printf("Input New Password: ", 15);
            scanf("%s", adPass);
            printf("\n\n");

            strcpy(adminData[pass].Pass, adPass); // pass copy to another variable

            encripTech(adminData, index); // again encript all data before sending to file

            // Latest Data Send to Admin - FILE
            fp = fopen("admin_data/data.txt", "w"); // delete previous data
            fclose(fp);
            fp = fopen("admin_data/data.txt", "a");
            for (int j = 0; j < index; j++)
            {
                fprintf(fp, "%s %s %s\n", adminData[j].Name, adminData[j].Pass, adminData[j].Email);
            }
            fclose(fp);

            printf("\n\n");
            printCentered("'Password Reset Done'....Press any key to return Home.", 4);
            _getch();
            adminPanelUserManagement();

        case 2:
            printCentered("Password Reset cancel!", 4);
            printf("\n\n");
            printCentered("          Press any key to return Home.....", 10);
            _getch();
            adminPanelUserManagement();
        }
    }
    else
    {
        printCentered("     Admin has not been found!", 4);
        printf("\n\n");
        printCentered("          Press any key to return Home.....", 10);
        _getch();
        adminPanelUserManagement();
    }
}
//*---------------Admin Panel (USER) Admin Pass Reset End----------------*/
//
//
//
//*---------------Admin Panel (USER) Admin List Start----------------*/
void listOfAdmin()
{
    int index;

    listOfAdminData(); // get all list of admin by array
    char headingName[40] = "Admin Management";
    menuUI(headingName);
    printCentered2(current_user_admin, "Home | Contact | About | Profile. ", 11);
    printf("\n\n");
    printCentered("OneMart", 10);
    printCentered("------------------------", 10);
    printf("\n\n");
    printCentered("List of Admins", 9);
    printCentered("-----------------------------------------------------------", 9);
    printCentered("|    Name:          Password:            Email:             |", 9);
    printCentered("============================================================", 9);

    FILE *fp;
    fp = fopen("admin_data/admin_index.txt", "r");
    fscanf(fp, "%d", &index);
    fclose(fp);

    decripTech(adminData, index); // decript data
    for (int i = 0; i < index; i++)
    {
        printf("                                                  %s           %s            %s\n", adminData[i].Name, adminData[i].Pass, adminData[i].Email);
    }

    printf("\n\n\n");
    printCentered("Press any key to return Home.", 10);
    _getch();
    adminPanelUserManagement();
}
//*---------------Admin Panel (USER) Admin List End----------------*/
//
//
//
//*---------------Admin Panel (USER) Add Customer Start----------------*/
void addCustomer()
{
    // adding user
    char headingName[40] = "User Management";
    menuUI(headingName);
    printCentered2(current_user_admin, "Home | Contact | About | Profile. ", 11);
    printf("\n\n");
    printCentered("OneMart", 10);
    printCentered("------------------------", 10);
    printf("\n");
    printCentered("Input User Information:", 15);
    printCentered("------------------------------", 15);

    // variable declare
    char usName[30];
    char usPass[20];
    char usEmail[50];
    int usIndex;
    char phn[15];

    // file management
    FILE *fp;
    int cID;
    fp = fopen("customer_data/customerID.txt", "r");
    fscanf(fp, "%d", &cID);
    fclose(fp);

    int width = getConsoleWidth();
    int space = (width - 5) / 2;
    setColor(15); // start
    for (int i = 0; i < space; i++)
        printf(" ");
    printf("      ID : %d\n", cID);

    space = (width - 5) / 2;
    setColor(15);

    //-------space/input management for name-------//
    space = (width - 12) / 2;
    for (int i = 0; i < space; i++)
        printf(" ");
    printf("  User Name  : ");
    scanf("%s", usName);

    //-------space/input management for password-------//
    space = (width - 14) / 2;
    for (int i = 0; i < space; i++)
        printf(" ");
    printf("    Password  : ");
    scanf("%s", usPass);

    //-------space/input management for email-------//
    space = (width - 11) / 2;
    for (int i = 0; i < space; i++)
        printf(" ");
    printf("     Email  : ");
    scanf("%s", usEmail);

    //-------space/input management for email-------//
    space = (width - 11) / 2;
    for (int i = 0; i < space; i++)
        printf(" ");
    printf("     Phone  : ");
    scanf("%s", phn);
    setColor(7); // reset color

    printf("\n\n");
    // print payment card info
    // received data from file
    int cardNum, cardCVV, day, mon, year, balance;
    fp = fopen("payment_card/cardInfo.txt", "r");
    fscanf(fp, "%d %d %d %d %d %d\n", &cardNum, &cardCVV, &day, &mon, &year, &balance);
    fclose(fp);

    printCentered("Your Payment Card Info:", 9);
    printCentered("----------------------------", 9);
    space = (width - 26) / 2;
    for (int i = 0; i < space; i++)
        printf(" ");
    printf("  Card Holder Name: %s\n", usName);

    space = (width - 15) / 2;
    for (int i = 0; i < space; i++)
        printf(" ");
    printf(" Card Number: %ld\n", cardNum);

    space = (width - 13) / 2;
    for (int i = 0; i < space; i++)
        printf(" ");
    printf(" Card - CVV: %d\n", cardCVV);

    space = (width - 19) / 2;
    for (int i = 0; i < space; i++)
        printf(" ");
    printf("   Expire Date: %d-%d-%d\n", day, mon, year);

    space = (width - 24) / 2;
    for (int i = 0; i < space; i++)
        printf(" ");
    printf("  Opening Balance: %d\n", balance);

    // card data send to file
    fp = fopen("payment_card/cardData.txt", "a");
    fprintf(fp, "%d %s %d %d %d %d %d %d\n", cID, usName, cardNum, cardCVV, day, mon, year, balance);
    fclose(fp);

    cardNum++, cardCVV++, year++;
    // update card info
    fp = fopen("payment_card/cardInfo.txt", "w");
    fprintf(fp, "%d %d %d %d %d %d\n", cardNum, cardCVV, day, mon, year, balance);
    fclose(fp);

    int cardIndex;
    // PAYMENT index received from file
    fp = fopen("payment_card/card_index.txt", "r");
    fscanf(fp, "%d", &cardIndex);
    fclose(fp);
    cardIndex = cardIndex + 1;

    // index send to file
    fp = fopen("payment_card/card_index.txt", "w");
    fprintf(fp, "%d", cardIndex);
    fclose(fp);

    // using caesar cypher to encript
    for (int i = 0; (i < 100 && usPass[i] != '\0'); i++)
    {
        usPass[i] = usPass[i] + 5;
    }

    // data send to file
    fp = fopen("customer_data/data.txt", "a");
    fprintf(fp, "%d %s %s %s %s\n", cID, usName, usPass, usEmail, phn);
    fclose(fp);

    ++cID; // customer id update
    fp = fopen("customer_data/customerID.txt", "w");
    fprintf(fp, "%d", cID);
    fclose(fp);

    // Customer index received
    fp = fopen("customer_data/customer_index.txt", "r");
    fscanf(fp, "%d", &usIndex);
    fclose(fp);

    usIndex = usIndex + 1;

    //  Customer latest send index
    fp = fopen("customer_data/customer_index.txt", "w");
    fprintf(fp, "%d", usIndex);
    fclose(fp);

    printf("\n\n\n");
    printCentered("User Added'....Press any key to return Home.", 10);
    _getch();
    adminPanelUserManagement(); // home
}
//*---------------Admin Panel (USER) Admin Pass Reset End----------------*/
//
//
//
//*---------------Admin Panel (USER) Delete Customer Start----------------*/
void deleteCustomer()
{
    char headingName[40] = "User Management";
    menuUI(headingName);
    printCentered2(current_user_admin, "Home | Contact | About | Profile. ", 11);
    printf("\n");
    printCentered("OneMart", 10);
    printCentered("------------------------", 10);
    printf("\n\n");
    printCentered("User Deletation", 15);
    printCentered(" -----------------------", 9);

    int index;
    char usName[30];

    int width = getConsoleWidth();
    int space = (width - 18) / 2;
    setColor(15);
    for (int i = 0; i < space; i++)
        printf(" ");
    printf("Input User Name: ", 15);
    scanf("%s", usName);
    printf("\n");

    listOfCustomerData(); // get latest User data
    FILE *fp;
    fp = fopen("customer_data/customer_index.txt", "r");
    fscanf(fp, "%d", &index); // get User Name
    fclose(fp);

    // find del position
    int deletePos, i, found = 0;
    for (i = 0; i < index; i++)
    {

        if (strcmp(customerData[i].Name, usName) == 0)
        {
            deletePos = i;
            found = 1;
            break;
        }
    }

    // if user found
    if (found)
    {
        printCentered("User Found...", 10);
        printCentered("-----------------------", 10);
        printCentered("   Name:            Email:    ", 15);
        printCentered("----------------------------------------------------------------", 9);

        printf("                                                            %s                %s\n", customerData[deletePos].Name, customerData[deletePos].Email);
        printf("\n\n\n\n\n");
        printCentered("     Are you sure you want to delete?", 15);
        printCentered("     1. YES", 10);
        printCentered("    2. NO", 4);

        // take input
        int option;
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
                customerData[j] = customerData[j + 1];
            }
            index = index - 1;

            // Latest Data Send to User - FILE
            fp = fopen("customer_data/data.txt", "w"); // Reset previous data
            fclose(fp);
            fp = fopen("customer_data/data.txt", "a");
            for (int j = 0; j < index; j++)
            {
                fprintf(fp, "%d %s %s %s\n", customerData[i].id, customerData[j].Name, customerData[j].Pass, customerData[j].Email);
            }
            fclose(fp);

            // send index to admin index
            fp = fopen("customer_data/customer_index.txt", "w");
            fprintf(fp, "%d", index);
            fclose(fp);

            printf("\n\n");
            printCentered("'User Deleted'....Press any key to return Home.", 4);
            _getch();
            adminPanelUserManagement();

        case 2:
            printCentered("Deletation cancel!", 4);
            printf("\n\n");
            printCentered("          Press any key to return Home.....", 10);
            _getch();
            adminPanelUserManagement();
        }
    }
    else
    {
        printCentered("     User has not been found!", 4);
        printf("\n\n");
        printCentered("          Press any key to return Home.....", 10);
        _getch();
        adminPanelUserManagement();
    }
}
//*---------------Admin Panel (USER) Delete Customer End----------------*/
//
//
//
//*---------------Admin Panel (USER) Customer Pass Reset Start----------------*/
void customerPasswordReset()
{
    char headingName[40] = "User Management";
    menuUI(headingName);
    printCentered2(current_user_admin, "Home | Contact | About | Profile. ", 11);
    printf("\n");
    printCentered("OneMart", 10);
    printCentered("------------------------", 10);
    printf("\n\n");
    printCentered("User Password Reset", 15);
    printCentered(" --------------------------", 9);
    printf("\n\n");

    int index;
    char usPass[20];
    char usName[30];

    FILE *fp;
    fp = fopen("customer_data/customer_index.txt", "r");
    fscanf(fp, "%d", &index);
    fclose(fp);

    listOfCustomerData();
    decripTech(customerData, index); // for decript data
    int width = getConsoleWidth();
    int space = (width - 18) / 2;
    setColor(15);
    for (int i = 0; i < space; i++)
        printf(" ");
    printf("Input User Name: ", 15);
    scanf("%s", usName);
    printf("\n");

    int pass, i, found = 0;
    for (i = 0; i < index; i++)
    {

        if (strcmp(customerData[i].Name, usName) == 0)
        {
            pass = i;
            found = 1;
            break;
        }
    }

    // user found
    if (found)
    {
        printCentered("User Found...", 10);
        printCentered("-----------------------", 10);
        printCentered("|     ID:       Name:        Password:            Email:  |", 9);
        printCentered("==========================================================", 9);

        printf("                                                %d     %s      %s         %s \n", customerData[i].id, customerData[i].Name, customerData[i].Pass, customerData[i].Email);
        printf("\n\n\n\n\n");
        printCentered("     Are you sure you want to change Password?", 15);
        printCentered("     1. YES", 10);
        printCentered("    2. NO", 4);

        // take input
        int option;
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

            for (int i = 0; i < space; i++)
                printf(" ");
            printf("Input New Password: ", 15);
            scanf("%s", usPass);
            printf("\n\n");

            strcpy(customerData[pass].Pass, usPass);
            encripTech(customerData, index); // again encript data

            // Latest Data Send to Costomer - FILE
            fp = fopen("customer_data/data.txt", "w"); // delete previous data
            fclose(fp);
            fp = fopen("customer_data/data.txt", "a");
            for (int j = 0; j < index; j++)
            {
                fprintf(fp, "%d %s %s %s\n", customerData[j].id, customerData[j].Name, customerData[j].Pass, customerData[j].Email);
            }
            fclose(fp);

            printf("\n\n");
            printCentered("'Password Reset Done'....Press any key to return Home.", 4);
            _getch();
            adminPanelUserManagement();

        case 2:
            printCentered("Password Reset cancel!", 4);
            printf("\n\n");
            printCentered("          Press any key to return Home.....", 10);
            _getch();
            adminPanelUserManagement();
        default:
            printf("\n\n");
            printCentered("'Invalid option'...press any key to try again.", 4);
            _getch();
            customerPasswordReset();
        }
    }
    else
    {
        printCentered("     User has not been found!", 4);
        printf("\n\n");
        printCentered("          Press any key to return Home.....", 10);
        _getch();
        adminPanelUserManagement();
    }
}
//*---------------Admin Panel (USER) Customer Pass Reset End----------------*/
//
//
//
//*---------------Admin Panel (USER) Customer List Start----------------*/
void listOfCustomer()
{
    int index;
    listOfCustomerData();

    char headingName[40] = "List of User";
    menuUI(headingName);
    printCentered2(current_user_admin, "Home | Contact | About | Profile. ", 11);
    printf("\n\n");
    printCentered("OneMart", 10);
    printCentered("------------------------", 10);
    printf("\n\n");
    printCentered("List of User", 9);
    printCentered("----------------------------------------------------------", 9);
    printCentered("|     ID:       Name:        Password:            Email:  |", 9);
    printCentered("==========================================================", 9);

    FILE *fp;
    fp = fopen("customer_data/customer_index.txt", "r");
    fscanf(fp, "%d", &index);
    fclose(fp);

    for (int i = 0; i < index; i++)
    {
        printf("                                                      %d     %s      %s         %s \n", customerData[i].id, customerData[i].Name, customerData[i].Pass, customerData[i].Email);
    }

    printf("\n\n\n");
    printCentered("Press any key to return Home.", 10);
    _getch();
    adminPanelUserManagement();
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
    int day, mon, year;

    FILE *fp;
    fp = fopen("Stock/all_product.txt", "r");
    while (fscanf(fp, "%d %d %s %d %d %s %d %d %d\n", &pID2, &proSupID2, pName2, &pPrice2, &pUnit2, pCat2, &day, &mon, &year) != EOF)
    {

        allProduct[index].pID = pID2;
        allProduct[index].proSupID = proSupID2;
        allProduct[index].pPrice = pPrice2;
        allProduct[index].pUnit = pUnit2;
        allProduct[index].expDate.day = day;
        allProduct[index].expDate.mon = mon;
        allProduct[index].expDate.year = year;
        strcpy(allProduct[index].pName, pName2);
        strcpy(allProduct[index].pCat, pCat2);
        index++;
    }
    fclose(fp);
    fp = fopen("Stock/index/all_product_index.txt", "w");
    fprintf(fp, "%d", index);
    fclose(fp);
}
//*---------------ALL Product from FILE - End----------------*/
//
//
//
//*---------------ALL Admin from FILE - Start----------------*/
void listOfAdminData()
{
    int index = 0;
    char adminName[30];
    char adminPass[20];
    char adminEmail[50];

    FILE *fp;
    fp = fopen("admin_data/data.txt", "r");
    while (fscanf(fp, "%s %s %s\n", adminName, adminPass, adminEmail) != EOF)
    {
        strcpy(adminData[index].Name, adminName);
        strcpy(adminData[index].Pass, adminPass);
        strcpy(adminData[index].Email, adminEmail);
        index++;
    }
    fclose(fp);
    fp = fopen("admin_data/admin_index.txt", "w");
    fprintf(fp, "%d", index);
    fclose(fp);
}
//*---------------ALL Admin from FILE - End----------------*/
//
//
//
////*---------------Admin Panel (USER) Customer data start----------------*/
void listOfCustomerData()
{
    int index = 0;
    int cusID;
    char userName[30];
    char userPass[20];
    char userEmail[50];
    char phn2[15];

    FILE *fp;
    fp = fopen("customer_data/data.txt", "r");
    while (fscanf(fp, "%d %s %s %s %s\n", &cusID, userName, userPass, userEmail, phn2) != EOF)
    {
        customerData[index].id = cusID;
        strcpy(customerData[index].Name, userName);
        strcpy(customerData[index].Pass, userPass);
        strcpy(customerData[index].Email, userEmail);
        strcpy(customerData[index].phn, phn2);
        index++;
    }
    fclose(fp);
    fp = fopen("customer_data/customer_index.txt", "w");
    fprintf(fp, "%d", index);
    fclose(fp);
}
////*---------------Admin Panel (USER) Customer data End----------------*/
//
//
//
/*---------------cardData Start----------------*/
void cardData()
{
    int index = 0, cusID2, cardNum2, cvv2, day2, mon2, year2;
    float balance2;
    char cardHolderName2[20];

    FILE *fp;
    // received data from file
    fp = fopen("payment_card/cardData.txt", "r");
    while (fscanf(fp, "%d %s %d %d %d %d %d %f\n", &cusID2, cardHolderName2, &cardNum2, &cvv2, &day2, &mon2, &year2, &balance2) != EOF)
    {
        strcpy(card[index].cardHolderName, cardHolderName2);
        card[index].cusID = cusID2;
        card[index].cardNum = cardNum2;
        card[index].cvv = cvv2;
        card[index].cardDate.day = day2;
        card[index].cardDate.mon = mon2;
        card[index].cardDate.year = year2;
        card[index].balance = balance2;
        index++;
    }
    fclose(fp);

    // index send to file
    fp = fopen("payment_card/card_index.txt", "w");
    fprintf(fp, "%d", index);
    fclose(fp);
}
/*---------------cardData end----------------*/
//
//
//
/*---------------Encripton Start----------------*/
void encripTech(struct user Data[50], int index)
{
    for (int j = 0; j < index; j++)
    {
        for (int i = 0; (i < 100 && Data[j].Pass[i] != '\0'); i++)
        {
            Data[j].Pass[i] = Data[j].Pass[i] + 5;
        }
    }
}
//*---------------Encripton End----------------*/
//
//
//
//*---------------Decripton Start----------------*/
void decripTech(struct user Data[100], int index)
{
    for (int j = 0; j < index; j++)
    {
        for (int i = 0; (i < 100 && Data[j].Pass[i] != '\0'); i++)
        {
            Data[j].Pass[i] = Data[j].Pass[i] - 5;
        }
    }
}
//*---------------Decripton End----------------*/
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
//
//
//
void buyProduct()
{

    char headingName[10] = "OneMart";
    menuUI(headingName);
    printf("\n\n");

    printCentered("Purchase Product", 11);
    printCentered("=====================", 15);
    printf("\n\n");

    int pID2, productID = 0;
    char custAdrs[50];
    int width = getConsoleWidth();
    int space = (width - 18) / 2;
    setColor(15);
    for (int i = 0; i < space; i++)
        printf(" ");
    printf("Input Product ID: ", 15);
    scanf("%d", &pID2);
    printf("\n");

    // Picking product index number form file
    int index;
    FILE *fp;
    fp = fopen("Stock/index/all_product_index.txt", "r");
    fscanf(fp, "%d", &index);

    // Finding Product
    allProductData();
    int i, found = 0;
    for (i = 0; i < index; i++)
    {
        if (allProduct[i].pID == pID2)
        {
            productID = i;
            found = 1;
            break;
        }
    }

    // Product
    if (found)
    {
        printCentered("  Product Information:", 10);
        printCentered("  ----------------------", 10);
        printCentered("  Product-ID:        Product-Name:   Product-Price:        Unit:        Category:", 15);
        printCentered("  --------------------------------------------------------------------------------", 9);
        printf("                                        %d              %s         %d.00TK            %d (P)       %s\n",
               allProduct[i].pID, allProduct[i].pName, allProduct[i].pPrice, allProduct[i].pUnit, allProduct[i].pCat);
        printf("\n");
        int pUnit;

        // input unit
        width = getConsoleWidth();
        space = (width - 18) / 2;
        setColor(15);
        for (int i = 0; i < space; i++)
            printf(" ");
        printf("Input Product Unit : ", 15);
        scanf("%d", &pUnit);

        // input address
        width = getConsoleWidth();
        space = (width - 18) / 2;
        setColor(15);
        for (int i = 0; i < space; i++)
            printf(" ");
        printf("Input Adress       : ");
        // fgets(custAdrs, 30, stdin);
        scanf("%s", custAdrs);
        printf("\n\n");

        int totalPrice = pUnit * allProduct[productID].pPrice;
        printCentered("  Order Details:", 10);
        printCentered("  ------------------------", 10);

        printCentered("  ID           Description:        Qty           Unit-Price        Total Price", 15);
        printCentered("  ------------------------------------------------------------------------------", 15);
        printf("                                        %d         %s              %d      X       %d               %d.00\n",
               allProduct[productID].pID, allProduct[productID].pName, pUnit, allProduct[productID].pPrice, totalPrice);
        printCentered("  ------------------------------------------------------------------------------", 15);
        printCentered("                                                     ---------------------------", 4);

        printf("                                                                                           Subtotal        : %d.00\n", totalPrice);
        int discount = 10, shipFee = 10;
        float total, salesTax;
        salesTax = 0.15 * totalPrice;
        total = (totalPrice + shipFee + salesTax) - discount;

        printf("                                                                                           Discount (-)    : %d.00\n", discount);
        printf("                                                                                           Shipping fee    : %d.00\n", shipFee);
        printf("                                                                                           Tax rate        : 15%%\n");
        printf("                                                                                           Sales Tax       : %.2f\n", salesTax);
        setColor(4);
        printf("                                                                                           Total           : %.2f\n\n", total);
        setColor(7);

        printCentered("press any key to use virtual card 'OnePay'....", 9);
        _getch();

        printf("\n");
        printCentered("  Your Card Info:", 10);
        printCentered("  ----------------------", 10);

        cardData();                       // get all card data
        int index2, currentCardIndex = 0; // take card index
        fp = fopen("customer_data/customer_index.txt", "r");
        fscanf(fp, "%d", &index2);
        fclose(fp);

        // current card index
        for (int i = 0; i < index2; i++)
        {
            if (currentCustomerID == card[i].cusID)
            {
                currentCardIndex = i;
                break;
            }
        }

        printf("                                                                Card Holder Name : %s\n", card[currentCardIndex].cardHolderName);
        printf("                                                                Card Number      : %d\n", card[currentCardIndex].cardNum);
        printf("                                                                Card - CVV       : %d\n", card[currentCardIndex].cvv);
        printf("                                                                Expire Date      : %d-%d-%d\n", card[currentCardIndex].cardDate.day, card[currentCardIndex].cardDate.mon, card[currentCardIndex].cardDate.year);
        printf("                                                                Balance          : %.2f\n\n", card[currentCardIndex].balance);
        printf("\n\n");

        printCentered("  Input Card Data'", 10);
        printCentered("  ----------------------", 10);
        char cardHolderName2[20];
        int cardNum2, cardCVV2, cardDate, day, mon, year;
        // take input from customer
        printf("                                                                Card Holder Name : ");
        scanf("%s", cardHolderName2);
        printf("                                                                Card Number      : ");
        scanf("%d", &cardNum2);
        printf("                                                                Card - CVV       : ");
        scanf("%d", &cardCVV2);
        printf("                                                                Expire Date      : ");
        scanf("%d %d %d", &day, &mon, &year);

        if (cardNum2 == card[currentCardIndex].cardNum && cardCVV2 == card[currentCardIndex].cvv &&
            card[currentCardIndex].cardDate.day == day && card[currentCardIndex].cardDate.mon == mon && card[currentCardIndex].cardDate.year == year)
        {
            // take one random transectopn num
            char transactionNum[15];
            srand(time(NULL)); // send ran num
            generateTransactionNumber(transactionNum, 12);
            // take current date from this function
            currentDateTime();
            currentDate.day;
            currentDate.mon;
            currentDate.year;

            printf("\n\n");
            printCentered("||=====Payment Received=====||", 10);
            printCentered("Press any key to get invoice........", 4);
            printf("\n\n");
            _getch();

            char online[10] = "online";
            // sales update
            fp = fopen("sales/all_sales.txt", "a");
            fprintf(fp, "%d %d %s %s %d %d %d %d %s %s %0.2f\n",
                    currentCustomerID, allProduct[productID].pID, allProduct[productID].pName, allProduct[productID].pCat, pUnit,
                    currentDate.day, currentDate.mon, currentDate.year, online, transactionNum, total);
            fclose(fp);

            char headingName[10] = "OneMart";
            menuUI(headingName);
            printf("\n\n");
            // genarate invoice
            printCentered("--------------------------------", 10);
            printCentered("                 CUSTOMER INVOICE                 ", 10);
            printCentered("--------------------------------", 10);
            printf("                                                              Transaction No :     %s\n", transactionNum);
            printf("                                                              Customer ID    :     %d\n", currentCustomerID);
            printf("                                                              Customer Name  :     %s\n", current_user_customer);
            printf("                                                              Date           :     %02d-%02d-%04d\n", currentDate.day, currentDate.mon, currentDate.year);
            printf("                                                              Mode           :     %s\n", online);
            printCentered("--------------------------------", 15);
            printf("                                                              Product ID     :     %d\n", allProduct[productID].pID);
            printf("                                                              Product Name   :     %s\n", allProduct[productID].pName);
            printf("                                                              Category       :     %s\n", allProduct[productID].pCat);
            printf("                                                              Quantity       :     %d\n", pUnit);
            printCentered("--------------------------------", 10);
            printf("                                                              TOTAL AMOUNT   :     %.2f\n", total);
            printCentered("--------------------------------", 10);

            printf("\n\n\n\n\n\n\n");

            printCentered("Press Any Key to HOME......", 10);
            _getch();
            OnlineHome();
        }

        else
        {
            printCentered("Card Info Error", 4);
            printCentered("Press Any Key to HOME......", 10);
            _getch();
            OnlineHome();
        }
        _getch();
    }
}

void menuContact()
{
    char headingName[10] = "OneMart";
    menuUI(headingName);
    printf("\n\n");

    printCentered("CONTACT", 11);
    printCentered("================", 15);
    printf("\n\n");
    printCentered("#Organization Information", 9);
    printCentered("===========================", 9);
    printf("\n\n");
    printf("                                               # Name                    : OneMart Ltd.\n\n");
    printf("                                               # Adress                  : 123 Business Road, Dhaka 1207, Bangladesh\n\n");
    printf("                                               # General Inquiries E-mail: contact123&gmail.com\n\n");
    printf("                                               # Customer Service E-mail : customer123&gmail.com\n\n");
    printf("                                               # Warehouse E-mail        : warehouse123&gmail.com\n\n");
    printf("                                               # Admin E-mail            : contact123&gmail.com\n\n");
    printf("                                               # Shop Manager E-mail     : shop123&gmail.com\n\n");
    printf("                                               # Website                 : www.onemart.com.bd\n\n");
    printf("                                               # Operating time          : 8 AM to 10 PM\n\n");
    printCentered("Close Only on Friday\n", 4);

    _getch();
    OnlineHome();
}

void menuAbout()
{
    char headingName[10] = "OneMart";
    menuUI(headingName);
    printf("\n\n");

    printCentered(" ===========\n", 3);
    printCentered("About\n", 3);
    printCentered(" ===========\n", 3);
    printf("\n"); // alinment does not match for \n\n

    printf("                                                      Version       : 1.0.0\n");
    printf("                                                      Release Date  : August 2025\n");
    printf("                                                      Developed By  : Najmus Sakib\n");
    printf("                                                                    : Mostakin Ahmed\n");
    printf("                                                                    : Shardil Shafat\n");
    printf("                                                      Environment   : C Language, File Handling, CLI\n\n");

    printCentered("----------------------------------------------\n", 10);
    printCentered("Purpose:\n", 10);
    printf("                                                      Efficiently manage stock levels, monitor inventory\n");
    printf("                                                      changes, and support inventory operations for small\n");
    printf("                                                      to medium-sized businesses.\n\n");

    printCentered("----------------------------------------------\n", 10);
    printCentered("Developer Contact:\n", 10);
    printf("                                                      Dev-1\n");
    printf("                                                      Name  : Najmus Sakib\n");
    printf("                                                      Email : najmussakib528@gmail.com\n");
    printf("                                                      GitHub: github.com/NajmusSakib367\n\n");
    printf("                                                      Dev-2\n");
    printf("                                                      Name  : Mostakin Ahmed\n");
    printf("                                                      Email : mostakinahmed???@gmail.com\n");
    printf("                                                      GitHub: github.com/mostakinahmed\n\n");
    printf("                                                      Dev-3\n");
    printf("                                                      Name  : Shadril Shafat\n");
    printf("                                                      Email : shadrilshafat???@gmail.com\n");
    printf("                                                      GitHub: github.com/shadril\n\n");

    printCentered("----------------------------------------------\n", 10);
    printCentered("Organization:\n", 10);
    printf("                                                      Name   : Async Coders Ltd.\n");
    printf("                                                      Address: 123 Business Road, Dhaka 1207, Bangladesh\n");
    printf("                                                      Website: www.onemart.com.bd\n\n");

    printCentered("----------------------------------------------\n", 10);
    printCentered("License & Disclaimer:\n", 10);
    printf("                                                      This software is for academic or internal use only.\n");
    printf("                                                      Redistribution or commercial use is not permitted\n");
    printf("                                                      without prior permission.\n");
    printf("                                                      © 2025 . All Rights Reserved.\n\n");

    printCentered("----------------------------------------------\n", 10);
    printCentered("Need Help?\n", 10);
    printf("                                                      Contact: support.onemart@onemart.bd\n\n");

    printCentered("==============================================\n", 10);
    printCentered("  Press any key to exit...\n", 10);
    printCentered("==============================================\n", 10);

    _getch();
    OnlineHome();
}

void menuProfile()
{
    char headingName[10] = "OneMart";
    menuUI(headingName);

    listOfCustomerData(); // get customer latest data from array- customerData[]

    printf("\n\n");
    printCentered("PROFILE", 10);
    printCentered(" -----------------------------", 10);

    FILE *fp; // take customer index from file
    int index, currentCustomerIndex = 0;
    fp = fopen("customer_data/customer_index.txt", "r");
    fscanf(fp, "%d", &index);
    fclose(fp);
    for (int i = 0; i < index; i++)
    {
        if (currentCustomerID == customerData[i].id)
        {
            currentCustomerIndex = i;
            break;
        }
    }
    printf("                                                                ID               : %d\n", customerData[currentCustomerIndex].id);
    printf("                                                                Name             : %s\n", customerData[currentCustomerIndex].Name);
    printf("                                                                Password         : xxxxxxxxx\n");
    printf("                                                                Email            : %s\n", customerData[currentCustomerIndex].Email);
    printf("                                                                Phone            : %s\n\n", customerData[currentCustomerIndex].phn);

    printf("\n\n");
    printCentered("Card Info", 10);
    printCentered(" -----------------------------", 10);

    cardData();                       // get all card details
    int index2, currentCardIndex = 0; // take card index
    fp = fopen("customer_data/customer_index.txt", "r");
    fscanf(fp, "%d", &index2);
    fclose(fp);
    for (int i = 0; i < index2; i++)
    {
        if (currentCustomerID == card[i].cusID)
        {
            currentCardIndex = i;
            break;
        }
    }

    printf("                                                                Card Holder Name : %s\n", card[currentCardIndex].cardHolderName);
    printf("                                                                Card Number      : %d\n", card[currentCardIndex].cardNum);
    printf("                                                                Card - CVV       : %d\n", card[currentCardIndex].cvv);
    printf("                                                                Expire Date      : %d-%d-%d\n", card[currentCardIndex].cardDate.day, card[currentCardIndex].cardDate.mon, card[currentCardIndex].cardDate.year);
    printf("                                                                Balance          : %.2f\n\n", card[currentCardIndex].balance);

    printf("\n\n");
    printCentered("press any key to return HOME", 4);
    _getch();
    OnlineHome();
}
//
//
//
/*-----------------HOME START----------------------*/
void OnlineHome()
{
    char headingName[10] = "HOME";
    menuUI(headingName);

    cardData();

    FILE *fp;
    // take current customer name
    fp = fopen("customer_data/current_user_customer.txt", "r");
    fscanf(fp, "%s", current_user_customer);
    fclose(fp);

    // take current customer ID
    fp = fopen("customer_data/current_user_customer_ID.txt", "r");
    fscanf(fp, "%d", &currentCustomerID);
    fclose(fp);

    // get login status
    char notLoggedIn[10] = "None";
    fp = fopen("login_Logout_status/logData_customer.txt", "r");
    fscanf(fp, "%d", &customerLoginStatus);
    fclose(fp);

    // for nav section
    if (customerLoginStatus == 1)
    {
        printCentered2(current_user_customer, "Home | Contact | About | Profile. ", 11);
    }
    else if (customerLoginStatus == 0)
    {
        printCentered2(notLoggedIn, "Home | Contact | About | Profile. ", 11);
    }

    printCentered("OneMart - Online Shopping", 10);
    printCentered("--------------------------", 10);

    // take all product index num from file
    int index, serNum = 1;
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
            printf("                              Computer\n");
            setColor(7);
            printCentered("     ------------------------------------------------------------------------------------------------------", 9);
            printCentered("    NO:     Product-ID:    Supplier-ID      Product-Name:     Product-Price:      Unit:      Category:", 9);
            printCentered("     ------------------------------------------------------------------------------------------------------", 9);

            for (int j = i; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "computer") == 0)
                {
                    printf("                               %d        %d          %d            %s            %d.00TK         %d (P)      %s\n",
                           serNum++, allProduct[j].pID, allProduct[j].proSupID, allProduct[j].pName, allProduct[j].pPrice, allProduct[j].pUnit, allProduct[j].pCat);
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
            printf("                              Books\n");
            setColor(7);
            printCentered("     ------------------------------------------------------------------------------------------------------", 9);
            printCentered("    NO:     Product-ID:    Supplier-ID      Product-Name:     Product-Price:      Unit:      Category:", 9);
            printCentered("     ------------------------------------------------------------------------------------------------------", 9);

            for (int j = i; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "books") == 0)
                {
                    printf("                               %d        %d          %d            %s            %d.00TK         %d (P)      %s\n",
                           serNum++, allProduct[j].pID, allProduct[j].proSupID, allProduct[j].pName, allProduct[j].pPrice, allProduct[j].pUnit, allProduct[j].pCat);
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
            printf("                              Medicine\n");
            setColor(7);
            printCentered("     ------------------------------------------------------------------------------------------------------", 9);
            printCentered("    NO:     Product-ID:    Supplier-ID      Product-Name:     Product-Price:      Unit:      Category:", 9);
            printCentered("     ------------------------------------------------------------------------------------------------------", 9);

            for (int j = i; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "medicine") == 0)
                {
                    printf("                               %d        %d          %d            %s            %d.00TK         %d (P)      %s\n",
                           serNum++, allProduct[j].pID, allProduct[j].proSupID, allProduct[j].pName, allProduct[j].pPrice, allProduct[j].pUnit, allProduct[j].pCat);
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
            printf("                              Camera\n");
            setColor(7);
            printCentered("     ------------------------------------------------------------------------------------------------------", 9);
            printCentered("    NO:     Product-ID:    Supplier-ID      Product-Name:     Product-Price:      Unit:      Category:", 9);
            printCentered("     ------------------------------------------------------------------------------------------------------", 9);

            for (int j = i; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "camera") == 0)
                {
                    printf("                               %d        %d          %d            %s            %d.00TK         %d (P)      %s\n", serNum++,
                           allProduct[j].pID, allProduct[j].proSupID, allProduct[j].pName, allProduct[j].pPrice, allProduct[j].pUnit, allProduct[j].pCat);
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
            printf("                              Television\n");
            setColor(7);
            printCentered("     ------------------------------------------------------------------------------------------------------", 9);
            printCentered("    NO:     Product-ID:    Supplier-ID      Product-Name:     Product-Price:      Unit:      Category:", 9);
            printCentered("     ------------------------------------------------------------------------------------------------------", 9);

            for (int j = i; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "television") == 0)
                {
                    printf("                               %d        %d          %d            %s            %d.00TK         %d (P)      %s\n", serNum++,
                           allProduct[j].pID, allProduct[j].proSupID, allProduct[j].pName, allProduct[j].pPrice, allProduct[j].pUnit, allProduct[j].pCat);
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
            printf("                              Watches\n");
            setColor(7);
            printCentered("     ------------------------------------------------------------------------------------------------------", 9);
            printCentered("    NO:     Product-ID:    Supplier-ID      Product-Name:     Product-Price:      Unit:      Category:", 9);
            printCentered("     ------------------------------------------------------------------------------------------------------", 9);

            for (int j = i; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "watches") == 0)
                {
                    printf("                               %d        %d          %d            %s            %d.00TK         %d (P)      %s\n",
                           serNum++, allProduct[j].pID, allProduct[j].proSupID, allProduct[j].pName, allProduct[j].pPrice, allProduct[j].pUnit, allProduct[j].pCat);
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
            printf("                              Fragrances\n");
            setColor(7);
            printCentered("     ------------------------------------------------------------------------------------------------------", 9);
            printCentered("    NO:     Product-ID:    Supplier-ID      Product-Name:     Product-Price:      Unit:      Category:", 9);
            printCentered("     ------------------------------------------------------------------------------------------------------", 9);

            for (int j = i; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "fragrances") == 0)
                {
                    printf("                               %d        %d          %d            %s            %d.00TK         %d (P)      %s\n",
                           serNum++, allProduct[j].pID, allProduct[j].proSupID, allProduct[j].pName, allProduct[j].pPrice, allProduct[j].pUnit, allProduct[j].pCat);
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
            printf("                              Beverages\n");
            setColor(7);
            printCentered("     ------------------------------------------------------------------------------------------------------", 9);
            printCentered("    NO:     Product-ID:    Supplier-ID      Product-Name:     Product-Price:      Unit:      Category:", 9);
            printCentered("     ------------------------------------------------------------------------------------------------------", 9);

            for (int j = i; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "beverages") == 0)
                {
                    printf("                               %d        %d          %d            %s            %d.00TK         %d (P)      %s\n",
                           serNum++, allProduct[j].pID, allProduct[j].proSupID, allProduct[j].pName, allProduct[j].pPrice, allProduct[j].pUnit, allProduct[j].pCat);
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
            printf("                              Mobile\n");
            setColor(7);
            printCentered("     ------------------------------------------------------------------------------------------------------", 9);
            printCentered("    NO:     Product-ID:    Supplier-ID      Product-Name:     Product-Price:      Unit:      Category:", 9);
            printCentered("     ------------------------------------------------------------------------------------------------------", 9);
            for (int j = i; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "mobile") == 0)
                {
                    printf("                               %d        %d          %d            %s            %d.00TK         %d (P)      %s\n",
                           serNum++, allProduct[j].pID, allProduct[j].proSupID, allProduct[j].pName, allProduct[j].pPrice, allProduct[j].pUnit, allProduct[j].pCat);
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
            printf("                              Software\n");
            setColor(7);
            printCentered("     ------------------------------------------------------------------------------------------------------", 9);
            printCentered("    NO:     Product-ID:    Supplier-ID      Product-Name:     Product-Price:      Unit:      Category:", 9);
            printCentered("     ------------------------------------------------------------------------------------------------------", 9);
            for (int j = i; j < index; j++)
            {
                if (strcmp(allProduct[j].pCat, "software") == 0)
                {
                    printf("                               %d        %d          %d            %s            %d.00TK         %d (P)      %s\n",
                           serNum++, allProduct[j].pID, allProduct[j].proSupID, allProduct[j].pName, allProduct[j].pPrice, allProduct[j].pUnit, allProduct[j].pCat);
                }
            }
            break;
        }
    }

    printf("\n\n\n");
    printCentered("      1. Buy Product.", 10);
    printCentered("      2. Access Menu.", 10);
    if (customerLoginStatus == 0)
    {
        printCentered("             3. Authentication Page.", 10);
    }
    else
    {
        printCentered("4. Logout.", 10);
    }
    printCentered("0. Exit.  ", 12);

    int width, space;
    int option;
    width = getConsoleWidth();
    space = (width - 15) / 2;

    printf("\n");
    for (int i = 0; i < space; i++)
        printf(" ");
    printf("   Choose Option: ");
    scanf("%d", &option);
    switch (option)
    {
    case 1:
        if (customerLoginStatus == 1)
        {
            buyProduct();
        }
        else
        {
            printf("\n");
            printCentered("                      Please login first to continue.", 4);
            printCentered("                 Press any key to login...\n", 10);
            _getch();
            customerSignIn();
        }

        break;
    case 2:
        char optionMenu;
        width = getConsoleWidth();
        space = (width - 15) / 2;

        printf("\n");
        printCentered("                                   h -Home   a -About   c -Contact   p -Profile", 9);
        for (int i = 0; i < space; i++)
            printf(" ");
        printf("   Choose Option: ");
        scanf(" %c", &optionMenu);
        switch (optionMenu)
        {
        case 'h':
            OnlineHome();
            break;

        case 'c':
            menuContact();
            break;

        case 'a':
            menuAbout();
            break;

        case 'p':
            if (customerLoginStatus == 1)
            {
                menuProfile();
            }
            else
            {
                printCentered("⚠️ Please login first to continue.\n", 4);
                printCentered("Press any key to login...\n", 10);
                _getch();
                customerSignIn();
            }

            break;

        default:
            printCentered("Invalid Choice! 2", 12);
            _getch();
            OnlineHome();
            break;
        }
        break;
    case 0:
        system("cls");
        printCentered("Goodbye!", 12);
        break;
    case 3:
        customerPanelAuthentication();
        break;
    case 4:
        customerLogOut();
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
// tonmoy