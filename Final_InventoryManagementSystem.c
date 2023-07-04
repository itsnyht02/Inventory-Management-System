// Made By TEAM C
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h> // only using it for getch();
#include <time.h> // only using it for getting the local time
#include <unistd.h> // only using it for sleep();

#define MAX_TRANSACTIONS 9999  // Maximum number of transactions

// User Login Variables
char username[100];
char password[100];
char loggedinUser[100];
char loggedinDepartment[100];
char ch;
char newName[100];

// FIXED ACCOUNTS
char userAdmin[] = "admin";
char userAdminpassword[] = "1234";
char user1[] = "cosuser";
char user1password[] = "1234";
char user2[] = "coeuser";
char user2password[] = "1234";
char user3[] = "cieuser";
char user3password[] = "1234";
char user4[] = "cituser";
char user4password[] = "1234";
char user5[] = "clauser";
char user5password[] = "1234";
char user6[] = "cafauser";
char user6password[] = "1234";


//Making Struct for the product
struct product {
    int id;
    char name[20];
    char department[100];
    char category[100];
    char unit[20]; // Added field for unit
    int quantity;
    float price;
    int reorderlevel;
    char lastModified[20]; // Added field for last modified date
};
struct product prod[100];
int count = 0;
FILE *f; //pointer for the FILE 


struct Transaction {
    char date[11];
    char time[9];
    int productId;
    char productName[50];
    int quantity;
};
struct Transaction transactions[MAX_TRANSACTIONS];
int transactionCount = 0;


// Functions
int writeFile();
int readFile();
int checkID(int id);
void addItem();
void editItem();
void restockItem();
void searchItemPerm();
void searchItem();
void getItem();
void viewItems();
void display_allItems();
void display_perCategory();
void display_perDepartment();
void nopermission();
void check_Reorderlevel();
void ReportandAnalytics();
void addTransaction();
void getItemFromInventory();
void generateDailyReport();
void generateDailyReportOnExit();
void generateWeeklyReport();
void generateWeeklyReportonExit();


// Users Menu
void account_check();
void adminMenu();
void normalMenu();
void userLogin();
void userLogout();
void userExit();

// Extra Functions
void chooseDepartment();
void chooseCategory();

// Main Function, Main of the program
int main(){
    count = readFile();

    userLogin();
    // display_allItems();
    return 0;
}

// Function for login
void userLogin(){
    int i = 0;

    system("cls");
    printf("   * * * * * * * *	    **********	***    ***     	******\n");
    printf(" *                 *	       ***	** *  * **     **     \n");
    printf("*   T U P I A N S   *          ***	**  **  **      ****  \n");
    printf("  *                *	       ***	**	**          **    \n");
    printf("   * * * * * * * *	    *********	**	**      *****     \n");
    printf("\n||===========================||");
    printf("\n||Enter Username: ");
    fflush(stdin);
    gets(username);
    printf("||===========================||\n\n");
    printf("||===========================||");
    printf("\n||Enter Password: ");
    while(1){
        ch=getch();
        if (ch==13){
            password[i]='\0';
            break;
        }
        else if(ch == 8){ // Backspace
            if (i>0){
                i--;
                printf("\b \b");
            }
        }
        else{
            password[i]=ch;
            i++;
            printf("*");
        }
    }
    if (strcmp(username, userAdmin) == 0){
        if(strcmp(password, userAdminpassword) == 0){
            printf("\n||===========================||");
            printf("\n||Logging in....             ||\n");
            sleep(1);
            printf("||===========================||\n");
            printf("\n=====================================\n");
            printf("||      LOGGED IN SUCCESFULLY      ||\n");
            printf("=====================================\n");
            strcpy(loggedinUser, userAdmin);
            sleep(2);
            // system("cls");
            adminMenu();
        }
        else{
            printf("\n||===========================||");
            printf("\n||Logging in....             ||\n");
            printf("||===========================||\n");
            sleep(2);
            printf("\n||===========================||");
            printf("\n||Incorrect Password         ||\n");
            printf("||===========================||");
            sleep(1);
            userLogin();
        }
    }
    else if (strcmp(username, user1) == 0 || strcmp(username, user2) == 0 || strcmp(username, user3) == 0 || strcmp(username, user4) == 0 || strcmp(username, user5) == 0 || strcmp(username, user6) == 0){

        if(strcmp(password, user1password) == 0 || strcmp(password, user2password) == 0 || strcmp(password, user3password) == 0 || strcmp(password, user4password) == 0 || strcmp(password, user5password) == 0 || strcmp(password, user6password) == 0){
            printf("\n||===========================||");
            printf("\n||Logging in....             ||\n");
            sleep(1);
            printf("||===========================||\n");
            printf("\n=====================================\n");
            printf("||      LOGGED IN SUCCESFULLY      ||\n");
            printf("=====================================\n");
            strcpy(loggedinUser, username);
            sleep(2);
            normalMenu();
        }
        else{
            printf("\n||===========================||");
            printf("\n||Logging in....             ||\n");
            printf("||===========================||\n");
            sleep(2);
            printf("\n||===========================||");
            printf("\n||Incorrect Password         ||\n");
            printf("||===========================||");
            sleep(1);
            userLogin();
        }
    }
    else{
        printf("\n||===========================||");
        printf("\n||Logging in....             ||\n");
        printf("||===========================||\n");
        sleep(2);
        printf("\n||===========================||");
        printf("\n||Account not Found          ||\n");
        printf("||===========================||");
        sleep(1);
        userLogin();
    }
}

// Function that checks if the account is an admin account or department account and displays a text that indicated their respective department
void account_check(){
    if(strcmp(loggedinUser, user1) == 0 ){
        printf("\t||COLLEGE OF SCIENCE DEPARTMENT               ||\n");

    }
    else if (strcmp(loggedinUser, user2) == 0 ){
        printf("\t||COLLEGE OF ENGINEERING DEPARTMENT           ||\n");
    }
    else if (strcmp(loggedinUser, user3) == 0 ){
        printf("\t||COLLEGE OF INDUSTRIAL EDUCATION DEPARTMENT  ||\n");
        // printf("College of Industrial Education Department\n");
    }
    else if (strcmp(loggedinUser, user4) == 0 ){
        printf("\t||COLLEGE OF INDUSTRIAL TECHNOLOGY DEPARTMENT ||\n");
        // printf("College of Industrial Technology Department\n");
    }
    else if (strcmp(loggedinUser, user5) == 0 ){
        printf("\t||COLLEGE OF LIBERAL ARTS DEPARTMENT          ||\n");
        // printf("College of Liberal Arts Department\n");
    }
    else if (strcmp(loggedinUser, user6) == 0 ){
        printf("\t||COLLEGE OF ARCHITECTURE AND FINE ARTS DEPT. ||\n");
        // printf("College of Architecture and Fine Arts Department\n");
    }
}

// Function for admin account
void adminMenu(){
    system("cls");
    int choice;
    printf("\\\\==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+//\n");
    printf(" \\\\                                                             //\n");
    printf("  \\\\                                                           //\n");
    printf("    +++++=== Welcome to TUP Inventory Management System ===+++++\n");
    printf("  //                                                           \\\\\n");
    printf(" //                                                             \\\\\n");
    printf("//==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+\\\\\n");

    printf("\t++============================================++\n");
    printf("\t||Logged In: %-5s                            ||\n", loggedinUser);
    printf("\t||============================================||\n");
    printf("\t||WELCOME ADMINISTRATOR                       ||\n");
    printf("\t++============================================++\n");
    printf("\t||            <<<< MAIN MENU >>>>             ||\n");
    printf("\t||____________________________________________||\n");
    printf("\t||   [1] Add Item                             ||\n");
    printf("\t||____________________________________________||\n");
    printf("\t||   [2] Edit Item                            ||\n");
    printf("\t||____________________________________________||\n");
    printf("\t||   [3] Restock Item                         ||\n");
    printf("\t||____________________________________________||\n");
    printf("\t||   [4] Search Item                          ||\n");
    printf("\t||____________________________________________||\n");
    printf("\t||   [5] Get Item                             ||\n");
    printf("\t||____________________________________________||\n");
    printf("\t||   [6] View Items                           ||\n");
    printf("\t||____________________________________________||\n");
    printf("\t||   [7] Report and Analytics                 ||\n");
    printf("\t||____________________________________________||\n");
    printf("\t||   [8] Log out                              ||\n");
    printf("\t||____________________________________________||\n");
    printf("\t||   [9] Exit Program                         ||\n");
    printf("\t||____________________________________________||\n");
    printf("Enter choice: ");
    scanf("%d", &choice);



    switch(choice){
        case 1:
            addItem();
            break;
        case 2:
            editItem();
            break;
        case 3:
            restockItem();
            break;
        case 4:
            searchItem();
            break;
        case 5:
            getItem();
            break;
        case 6:
            viewItems();
            break;
        case 7:
            ReportandAnalytics();
            break;
        case 8:
            userLogout();
            break;
        case 9:
            userExit();
            break;
        default:
            while (getchar() != '\n');
            system("cls");
            return adminMenu();
    }

}

// Function for normal account or department account
void normalMenu(){
    int choice;
    system("cls");
    printf("\\\\==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+//\n");
    printf(" \\\\                                                             //\n");
    printf("  \\\\                                                           //\n");
    printf("    +++++=== Welcome to TUP Inventory Management System ===+++++\n");
    printf("  //                                                           \\\\\n");
    printf(" //                                                             \\\\\n");
    printf("//==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+\\\\\n");
    printf("\t++============================================++\n");
    printf("\t||Logged In: %-8s                         ||\n", loggedinUser);
    printf("\t||============================================||\n");
    account_check();
    printf("\t++============================================++\n");
    printf("\t||            <<<< MAIN MENU >>>>             ||\n");
    printf("\t||____________________________________________||\n");
    printf("\t||   [1] Get Item                             ||\n");
    printf("\t||____________________________________________||\n");
    printf("\t||   [2] Search Item                          ||\n");
    printf("\t||____________________________________________||\n");
    printf("\t||   [3] View Items                           ||\n");
    printf("\t||____________________________________________||\n");
    printf("\t||   [4] Log Out                              ||\n");
    printf("\t||____________________________________________||\n");
    printf("\t||   [5] Exit Program                         ||\n");
    printf("\t||____________________________________________||\n");
    printf("Enter choice: ");
    scanf("%d", &choice);


    switch(choice){
        case 1:
            getItem();
            break;
        case 2:
            searchItem();
            break;
        case 3:
            viewItems();
            break;
        case 4:
            userLogout();
            break;
        case 5:
            userExit();
            break;
        default:
            while (getchar() != '\n');
            // system("cls");
            return normalMenu();
    }
}

// Function when a user logout
void userLogout(){
    char loggedinUser;
    printf("\n||===========================||");
    printf("\n||Logging out....            ||\n");
    printf("||===========================||\n");
    sleep(1);
    printf("\\\\==============================//\n");
    printf("||   SUCCESSFULLY LOGGED OUT    ||\n");
    printf("//==============================\\\\\n");
    sleep(1);
    userLogin();
}

// Function when a users wants to close or end the program
void userExit(){ // Need ayusin
    generateDailyReportOnExit();
    generateWeeklyReportonExit();
    system("cls");
    printf("\\\\================================//\n");
    printf("||Thank you for using our Service!||\n");
    printf("//================================\\\\\n");
    exit(0);
}

// READ FILE AND WRITE FILE
// Function for Writing files
int writeFile(){ //write file function
    int i;
    f = fopen("inventories/inventory.txt", "w");  // ayaw i append; change from f = fopen("inventory.txt", "a");
    if (f == NULL)
        return -1;
    fprintf(f, "%d\n", count);
    for (i = 0; i < count; ++i) // writing all the details from all the function to the text file.
    {
        // Changed
        fprintf(f, "%d\n", prod[i].id);
        fputs(prod[i].name, f);
        fprintf(f, "\n");
        fputs(prod[i].department, f);
        fprintf(f, "\n");
        fputs(prod[i].category, f);
        fprintf(f, "\n");
        fputs(prod[i].unit, f); // Write unit
        fprintf(f, "\n");
        fprintf(f, "%d\n", prod[i].quantity);
        fprintf(f, "%f\n", prod[i].price);
        fprintf(f, "%d\n", prod[i].reorderlevel);
        fputs(prod[i].lastModified, f); // Write last modified date
        fprintf(f, "\n");
    }
    fclose(f);
    return 0;
}
// Function for reading the file (HARD)
int readFile() {
    int n = 0;
    int i;
    f = fopen("inventories/inventory.txt", "r");
    if (f == NULL)
        return -1;
    fscanf(f, "%d\n", &n);
    count = n;
    for (i = 0; i < n; ++i) {
        fscanf(f, "%d\n",&prod[i].id);
        fgets(prod[i].name, sizeof(prod[i].name), f);
        prod[i].name[strcspn(prod[i].name, "\n")] = '\0';
        fgets(prod[i].department, sizeof(prod[i].department), f);
        prod[i].department[strcspn(prod[i].department, "\n")] = '\0';
        fgets(prod[i].category, sizeof(prod[i].category), f);
        prod[i].category[strcspn(prod[i].category, "\n")] = '\0';
        fgets(prod[i].unit, sizeof(prod[i].unit), f); // Read unit
        prod[i].unit[strcspn(prod[i].unit, "\n")] = '\0';
        fscanf(f, "%d", &prod[i].quantity);
        fscanf(f, "%f", &prod[i].price);
        fscanf(f, "%d\n", &prod[i].reorderlevel);
        fgets(prod[i].lastModified, sizeof(prod[i].lastModified), f); // Read last modified date
        prod[i].lastModified[strcspn(prod[i].lastModified, "\n")] = '\0';
    }
    fclose(f);
    return n;
}


// Function the checks the product ID if it already exists or not
int checkID(int id) {
    int i;
    count = readFile();
    for (i = 0; i < count; i++) {
        if (prod[i].id == id) {
            return 1; // ID already exists
        }
    }
    return 0; // ID is available
}

// Function for adding an item from the inventory
void addItem() {
    int departmentChoice;
    int categoryChoice;

    time_t currentTime;
    time(&currentTime);
    struct tm* localTime = localtime(&currentTime);

    strftime(prod[count].lastModified, sizeof(prod[count].lastModified), "%Y-%m-%d", localTime);

    printf("ENTER NEW PRODUCTS\n");
    readFile();

    if (count > 0) {
        count = readFile();
    }

    int newID;
    while (1) {
        printf("Product ID Number: ");
        if (scanf("%d", &newID) != 1 || newID <= 0) {
            printf("Wrong Input. Please enter a valid ID.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');
        if (checkID(newID)) {
            printf("ID already exists. Please try again.\n");
        } else {
            break;
        }
    }

    prod[count].id = newID;
    printf("Product Name: ");
    fflush(stdin);
    gets(prod[count].name);
    printf("Choose which Department\n");
    chooseDepartment();
    printf("Choose a Category\n");
    chooseCategory();
    printf("Units of the product: ");
    fflush(stdin);
    gets(prod[count].unit);
    fflush(stdin);
    
    while(1){ // Problem here
        printf("Quantity of the product: ");
        if (scanf("%d", &prod[count].quantity) != 1 || prod[count].quantity <= 0){
            printf("Enter only valid Input\n");
            while (getchar() != '\n');
            continue;
        }
        else{
            break;
        }
    }
    while(1){
        printf("Price of the product: ");
        if (scanf("%f", &prod[count].price) != 1 || prod[count].price <= 0){
            printf("Enter only valid Input\n");
            while (getchar() != '\n');
            continue;
        }
        else{
            break;
        }
    }

while(1){
        printf("Reorder Level: ");
        if (scanf("%d", &prod[count].reorderlevel) != 1 || prod[count].reorderlevel <= 0){
            printf("Enter only valid Input\n");
            while (getchar() != '\n');
            continue;
        }
        else{
            break;
        }
    }

    count++;
    writeFile();
    sleep(1);
    printf("<>==============================<>\n");
    printf("||  Items Added Successfully!	||\n");
    printf("<>==============================<>\n");
    sleep(1);
    system("cls");
    display_allItems();
    adminMenu();
}

// Extra funciton for addItem();
void chooseDepartment(){
    int departmentChoice;
    printf("\t\\\\<><><><><><><><><><><><><><><><><><><><><><>//\n");
    printf("\t|| [1] COS Department                         ||\n");
    printf("\t|]============================================[|\n");
    printf("\t|] [2] COE Department                         ||\n");
    printf("\t|]============================================[|\n");
    printf("\t|] [3] CIE Department                         ||\n");
    printf("\t|]============================================[|\n");
    printf("\t|| [4] CIT Department                         ||\n");
    printf("\t|]============================================[|\n");
    printf("\t|| [5] CLA Department                         ||\n");
    printf("\t|]============================================[|\n");
    printf("\t|| [6] CAFA Department                        ||\n");
    printf("\t|]============================================[|\n");
    printf("Enter Department: ");
    scanf("%d", &departmentChoice);

    switch (departmentChoice) {
        case 1:
            strcpy(prod[count].department, "COS");
            break;
        case 2:
            strcpy(prod[count].department, "COE");
            break;
        case 3:
            strcpy(prod[count].department, "CIE");
            break;
        case 4:
            strcpy(prod[count].department, "CIT");
            break;
        case 5:
            strcpy(prod[count].department, "CLA");
            break;
        case 6:
            strcpy(prod[count].department, "CAFA");
            break;
        default:
            printf("Invalid department choice. Department set as 'Other'.\n");
            strcpy(prod[count].department, "Other");
            break;
    }
}

// Extra function for addItem();
void chooseCategory(){
    int categoryChoice;
        printf("\t<>====+=====+=====+=====+=====+=====+=====+====<>\n");
        printf("\t\\\\    [1] Cleaning Supply                      //\n");
        printf("\t+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+\n");
        printf("\t//    [2] Office Supply                        \\\\\n");
        printf("\t+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+\n");
    printf("Choose a category: ");
    scanf("%d", &categoryChoice);
    switch (categoryChoice) {
        case 1:
            strcpy(prod[count].category, "Cleaning Supply");
            break;
        case 2:
            strcpy(prod[count].category, "Office Supply");
            break;
        default:
            printf("Invalid category choice. Category set as 'Other'.\n");
            strcpy(prod[count].category, "Other");
            break;
    }
}

// Function for editing an item from the inventory incase of typo
void editItem(){
    int id;
    int check;
    int i;
    int choice;
    int departmentChoice;
    int categoryChoice;
    int newId;
    while(1){
        printf("EDIT A PRODUCT!\n");
        printf("Enter the id of the product that you want to edit: ");
        if(scanf("%d", &id) != 1 || id <= 0){
            printf("Invalid Input or id not. Try Again\n");
            while(getchar() != '\n');
            continue;
        }
        else{
            break;
        }
    }
    check = checkID(id);
    if (check == 0){
        printf("The product with ID %d is not found.", id);
        sleep(2);
    }
    else{
        readFile();
        for(i = 0; i < count; i++){
            if(prod[i].id == id){
            printf("<>==============================<>\n");
            printf("||  Item Searching...       	||\n");
            printf("<>==============================<>\n");
            sleep(1);
            system("cls");
                printf("============================================================================================================================================================");
                printf("\n|\t\t\t\t\t\t          *****  PRODUCT FOUND *****                                                                       |\n");
                printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
                printf("| S.N. |  PRODUCT ID  |    PRODUCT NAME    |   DEPARTMENT   |      CATEGORY      |    UNIT    |  QUANTITY  |   PRICE   |  REORDER LEVEL  |  LAST MODIFIED  | \n");
                printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
                printf("|%3d   |     %-8d |   %-16s |      %-10s|  %-16s  |  %-9s |     %-6d |   P%-6.2f |       %-9d |  %-14s |\n",
                i + 1, prod[i].id, prod[i].name, prod[i].department, prod[i].category, prod[i].unit, prod[i].quantity,prod[i].price, prod[i].reorderlevel, prod[i].lastModified);
                printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
                sleep(1);
                printf("\n\t++==============================================++\n");
                printf("\t|| [1] Update product ID number?                ||\n");
                printf("\t||______________________________________________||\n");
                printf("\t|| [2] Update Name of the product?              ||\n");
                printf("\t||______________________________________________||\n");
                printf("\t|| [3] Update Department of the product?        ||\n");
                printf("\t||______________________________________________||\n");
                printf("\t|| [4] Update Category of the product?          ||\n");
                printf("\t||______________________________________________||\n");
                printf("\t|| [5] Update Unit of the product?              ||\n");
                printf("\t||______________________________________________||\n");
                printf("\t|| [6] Update Quantity of the product?          ||\n");
                printf("\t||______________________________________________||\n");
                printf("\t|| [7] Update Price of the product?             ||\n");
                printf("\t||______________________________________________||\n");
                printf("\t|| [8] Update Reorder of the product            ||\n");
                printf("\t||______________________________________________||\n");
                printf("\t|| [9] Back                                     ||\n");
                printf("\t||______________________________________________||\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);
                switch (choice){
                    case 1:
                        while(1){
                            printf("Enter new ID: ");
                            if(scanf("%d", &newId) != 1 || newId <=0){
                                printf("Invalid Input. Try Again\n");
                                while (getchar() != '\n');
                                continue;
                            }
                            else if(checkID(newId)){
                                printf("ID Already Exists. Try Again\n");
                                continue;
                            }
                            else{
                                prod[i].id = newId;
                                break;
                            }
                        }
                        break;
                    case 2:
                        printf("Enter new Name: ");
                        fflush(stdin);
                        gets(prod[i].name);
                        break;
                    case 3:
                        printf("\t\\<><><><><><><><><><><><><><><><>><><><><><><><//\n");
                        printf("\t||          Choose which Department             ||\n");
                        printf("\t|]==============================================[|\n");
                        printf("\t|| [1] COS Department                           ||\n");
                        printf("\t|]==============================================[|\n");
                        printf("\t|| [2] COE Department                           ||\n");
                        printf("\t|]==============================================[|\n");
                        printf("\t|| [3[ CIE Department                           ||\n");
                        printf("\t|]==============================================[|\n");
                        printf("\t|| [4] CIT Department                           ||\n");
                        printf("\t|]==============================================[|\n");
                        printf("\t|| [5] CLA Department                           ||\n");
                        printf("\t|]==============================================[|\n");
                        printf("\t|| [6] CAFA Department                          ||\n");
                        printf("\t|]==============================================[|\n");
                        printf("Enter Department: ");
                        scanf("%d", &departmentChoice);
                        switch (departmentChoice) {
                            case 1:
                                strcpy(prod[i].department, "COS");
                                break;
                            case 2:
                                strcpy(prod[i].department, "COE");
                                break;
                            case 3:
                                strcpy(prod[i].department, "CIE");
                                break;
                            case 4:
                                strcpy(prod[i].department, "CIT");
                                break;
                            case 5:
                                strcpy(prod[i].department, "CLA");
                                break;
                            case 6:
                                strcpy(prod[i].department, "CAFA");
                                break;
                            default:
                                printf("Invalid department choice. Department set as 'Other'.\n");
                                strcpy(prod[i].department, "Other");
                                break;
                        }
                        break;
                    case 4:
                        printf("\t<>==============================================>\n");
                        printf("\t||            Choose a new Category            ||\n");
                        printf("\t<>====+=====+=====+=====+=====+=====+=====+====<>\n");
                        printf("\t\\\\    [1] Cleaning Supply                      //\n");
                        printf("\t+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+\n");
                        printf("\t//    [2] Office Supply                        \\\\\n");
                        printf("\t+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+\n");
                        printf("Choose a category: ");
                        scanf("%d", &categoryChoice);
                        switch (categoryChoice) {
                            case 1:
                                strcpy(prod[i].category, "Cleaning Supply");
                                break;
                            case 2:
                                strcpy(prod[i].category, "Office Supply");
                                break;
                            default:
                                printf("Invalid category choice. Category set as 'Other'.\n");
                                strcpy(prod[i].category, "Other");
                                break;
                        }
                        break;
                    case 5:
                        printf("Enter the new unit: ");
                        fflush(stdin);
                        gets(prod[i].unit);
                        break;
                    case 6:
                        while(1){
                            printf("Enter the new Quantity: ");
                            if(scanf("%d", &prod[i].quantity) != 1 || prod[i].quantity <=0){
                                printf("Invalid Input. Try Again\n");
                                while (getchar() != '\n');
                                continue;
                            }
                            else{
                                break;
                            }
                        }
                        break;
                    case 7:
                        while(1){
                            printf("Enter the new price: ");
                            if(scanf("%f", &prod[i].price) != 1 || prod[i].price <=0){
                                printf("Invalid Input. Try Again\n");
                                while (getchar() != '\n');
                                continue;
                            }
                            else{
                                break;
                            }
                        }
                        break;
                    case 8:
                        while(1){
                            printf("Enter the new reorder level: ");
                            if(scanf("%d", &prod[i].reorderlevel) != 1 || prod[i].reorderlevel <=0){
                                printf("Invalid Input. Try Again\n");
                                while (getchar() != '\n');
                                continue;
                            }
                            else{
                                break;
                            }
                        }
                        break;
                    case 9:
                        adminMenu();
                        break;
                    default:
                        while (getchar() != '\n');
                        return adminMenu();
                        
                }

                time_t currentTime;
                time(&currentTime);
                struct tm* localTime = localtime(&currentTime);
                strftime(prod[i].lastModified, sizeof(prod[i].lastModified), "%Y-%m-%d", localTime);




                writeFile();
                break;
            }
        }
        printf("\t<>================================<>\n");
        printf("\t||        ITEM UPDATING...        ||\n");
        printf("\t<>================================<>\n");
        sleep(2);
        printf("\t<>================================<>\n");
        printf("\t||         ITEM UPDATED!!         ||\n");
        printf("\t<>================================<>\n");
        sleep(1);
    }
    adminMenu();
}

// Function that restocks an item from the inventory
void restockItem() {
    int productId, quantity;

    while(1){
        printf("Enter the product ID to restock: ");
        if(scanf("%d", &productId) != 1 || productId <= 0){
            printf("Invalid Input. Try Again\n");
            while(getchar() != '\n');
            continue;
        }
        else{
            break;
        }
    }

    int found = 0;

    readFile();

    printf("<>==============================<>\n");
    printf("||  Item Searching...       	||\n");
    printf("<>==============================<>\n");
    sleep(1);

    for (int i = 0; i < count; i++) {
        if (prod[i].id == productId) {
            system("cls");
            printf("============================================================================================================================================================");
            printf("\n|\t\t\t\t\t\t          *****  PRODUCT FOUND *****                                                                       |\n");
            printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
            printf("| S.N. |  PRODUCT ID  |    PRODUCT NAME    |   DEPARTMENT   |      CATEGORY      |    UNIT    |  QUANTITY  |   PRICE   |  REORDER LEVEL  |  LAST MODIFIED  | \n");
            printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
            printf("|%3d   |     %-8d |   %-16s |      %-10s|  %-16s  |  %-9s |     %-6d |   P%-6.2f |       %-9d |  %-14s |\n",
            i + 1, prod[i].id, prod[i].name, prod[i].department, prod[i].category, prod[i].unit, prod[i].quantity,prod[i].price, prod[i].reorderlevel, prod[i].lastModified);
            printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

            while(1){
                printf("\nEnter the quantity to add: ");
                if(scanf("%d", &quantity)!= 1 || quantity <= 0){
                    printf("Invalid Input. Try Again\n");
                    while(getchar() != '\n');
                    continue;
                }
                else{
                    break;
                }
            }

            time_t currentTime;
            time(&currentTime);
            struct tm* localTime = localtime(&currentTime);
            strftime(prod[i].lastModified, sizeof(prod[i].lastModified), "%Y-%m-%d", localTime);

            prod[i].quantity += quantity;
            found = 1;

            // Add the restocking action to the transaction history
            char currentDate[20];
            char currentTime1[20];
            strftime(currentDate, sizeof(currentDate), "%Y-%m-%d", localTime);
            strftime(currentTime1, sizeof(currentTime1), "%H:%M:%S", localTime);
            addTransaction(currentDate, currentTime1, prod[i].id, prod[i].name, quantity);
            break;
        }
    }

    if (found) {
        writeFile();  // Update the product information in your data source
        printf("<>==============================<>\n");
        printf("|| Product restocking...        ||\n");
        printf("<>==============================<>\n");
        sleep(1);
        printf("<>==============================<>\n");
        printf("||Product restocked successfully||\n");
        printf("<>==============================<>\n");
        sleep(2);
    } else {
        printf("<>=================<>\n");
        printf("||Product not found||\n");
        printf("<>=================<>\n");
        sleep(2);
    }

    adminMenu();
}

// Function used to only permit admin to access all Items while normal account can only access their respective Items according to their department
void searchItemPerm(){
    if(strcmp(loggedinUser, user1) == 0 ){
        strcpy(newName, "COS");
    }
    else if (strcmp(loggedinUser, user2) == 0 ){
        strcpy(newName, "COE");
    }
    else if (strcmp(loggedinUser, user3) == 0 ){
        strcpy(newName, "CIE");
    }
    else if (strcmp(loggedinUser, user4) == 0 ){
        strcpy(newName, "CIT");

    }
    else if (strcmp(loggedinUser, user5) == 0 ){
        strcpy(newName, "CLA");

    }
    else if (strcmp(loggedinUser, user6) == 0 ){
        strcpy(newName, "CAFA");
    }
}

// Function for searching an item from the inventory
void searchItem() {
    int id;
    int i;
    int found = 0;

    printf("<>==============================<>\n");
    printf("||        Search an Item        ||\n");
    printf("<>==============================<>\n");
    while(1){
        printf("Enter the ID of the product you want to search: ");
        if(scanf("%d", &id) != 1 || id <= 0){
            printf("Invalid Input. Try Again\n");
            while(getchar() != '\n');
            continue;
        }
        else{
            break;
        }
    }

    count = readFile(); // Read the items from the file

    printf("<>==============================<>\n");
    printf("||  Item Searching...       	||\n");
    printf("<>==============================<>\n");
    sleep(1);

    searchItemPerm();

    for (i = 0; i < count; i++) {
        if (strcmp(loggedinUser, userAdmin) == 0 || strcmp(prod[i].department, newName) == 0) {
            if (prod[i].id == id) {
                system("cls");
                printf("============================================================================================================================================================");
                printf("\n|\t\t\t\t\t\t          *****  PRODUCT FOUND *****                                                                       |\n");
                printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
                printf("| S.N. |  PRODUCT ID  |    PRODUCT NAME    |   DEPARTMENT   |      CATEGORY      |    UNIT    |  QUANTITY  |   PRICE   |  REORDER LEVEL  |  LAST MODIFIED  | \n");
                printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
                printf("|%3d   |     %-8d |   %-16s |      %-10s|  %-16s  |  %-9s |     %-6d |   P%-6.2f |       %-9d |  %-14s |\n",
                i + 1, prod[i].id, prod[i].name, prod[i].department, prod[i].category, prod[i].unit, prod[i].quantity, prod[i].price, prod[i].reorderlevel, prod[i].lastModified);
                printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
                found = 1;

                sleep(1);
                printf("<>==========================<>\n");
                printf("||  Going back to Menu...   ||\n");
                printf("<>==========================<>\n");
                sleep(5);
                break;
            }
        }
    }

    if (!found) {
        printf("<>=============================================================================<>\n");
        printf("||  Item with ID %-8d not found or existed in other department.	       ||\n", id);
        printf("<>=============================================================================<>\n");
        sleep(2);
    }

    if (strcmp(loggedinUser, userAdmin) == 0) {
        adminMenu();
    } else {
        normalMenu();
    }
}

// Function for getting an item from the inventory
void getItem() {
    int id;
    int i;
    int found = 0;

    printf("<>===========================<>\n");
    printf("||        Get an Item        ||\n");
    printf("<>===========================<>\n");
    while(1){
        printf("Enter the ID of the product you want to get: ");
        if(scanf("%d", &id)!=1 || id <= 0){
            printf("Invalid Input. Try Again\n");
            while(getchar() != '\n');
            continue;
        }
        else{
            break;
        }
    }
    count = readFile(); // Read the items from the file

    printf("<>==============================<>\n");
    printf("||  Item Searching...       	||\n");
    printf("<>==============================<>\n");
    sleep(1);

    searchItemPerm();

    for (i = 0; i < count; i++) {
        if (prod[i].id == id) {
            found = 1;

            if (strcmp(loggedinUser, userAdmin) == 0 || strcmp(newName, prod[i].department) == 0) {
                if (prod[i].quantity > 0) {
                    system("cls");
                    printf("============================================================================================================================================================");
                    printf("\n|\t\t\t\t\t\t          *****  PRODUCT FOUND *****                                                                       |\n");
                    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
                    printf("| S.N. |  PRODUCT ID  |    PRODUCT NAME    |   DEPARTMENT   |      CATEGORY      |    UNIT    |  QUANTITY  |   PRICE   |  REORDER LEVEL  |  LAST MODIFIED  | \n");
                    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
                    printf("|%3d   |     %-8d |   %-16s |      %-10s|  %-16s  |  %-9s |     %-6d |   P%-6.2f |       %-9d |  %-14s |\n",
                           i + 1, prod[i].id, prod[i].name, prod[i].department, prod[i].category, prod[i].unit, prod[i].quantity, prod[i].price, prod[i].reorderlevel, prod[i].lastModified);
                    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

                    // Ask for the quantity to purchase
                    int quantity;
                    while(1){
                        printf("Enter the quantity to get: ");
                        if(scanf("%d", &quantity) != 1 || quantity <= 0){
                            printf("Invalid Input. Try Again\n");
                            while(getchar() != '\n');
                            continue;
                        }
                        else{
                            break;
                        }
                    }
                    if (quantity > prod[i].quantity) {
                    printf("<>=====================================================================<>\n");
                    printf("||  Insufficient stock. Only %-4d item(s) available.	               ||\n", prod[i].quantity);
                    printf("<>=====================================================================<>\n");
                    sleep(2);
                    } else {
                        prod[i].quantity -= quantity; // Reduce the quantity

                        // Update Local Time
                        time_t currentTime;
                        time(&currentTime);
                        struct tm *localTime = localtime(&currentTime);
                        strftime(prod[i].lastModified, sizeof(prod[i].lastModified), "%Y-%m-%d", localTime);

                        // Update the file with the new quantity
                        writeFile();
                        printf("<>==============================<>\n");
                        printf("|| Getting the product...       ||\n");
                        printf("<>==============================<>\n");
                        sleep(1);
                        printf("\t<><><><><><><><><><><><><><><><><><><><><><><><><>\n");
                        printf("\t\\\\ Product Successfully Taken!                  //\n");
                        printf("\t//----------------------------------------------\\\\\n");
                        printf("\t\\\\ Number of Supplies Taken: %d                 //\n", quantity);
                        printf("\t//----------------------------------------------\\\\\n");
                        printf("\t\\\\ Number of Supplies Left: %d                  //\n", prod[i].quantity);
                        printf("\t//----------------------------------------------\\\\\n");
                        printf("\t<><><><><><><><><><><><><><><><><><><><><><><><><>\n");
                        sleep(1);
                        printf("<>==========================<>\n");
                        printf("||  Going back to Menu...   ||\n");
                        printf("<>==========================<>\n");
                        sleep(2);

                        // Record the transaction
                        getItemFromInventory(prod[i].id, prod[i].name, -quantity); // By adding a "-" to the quantity, the Item now will have a -sign in the transaction history.
                    }
                } else {
                    printf("<>==================================================<>\n");
                    printf("||  Product out of Stock!! Please restock.          ||\n");
                    printf("<>==================================================<>\n");
                    sleep(2);
                }
            } else {
                printf("<>======================================================<>\n");
                printf("||  You do not have permission to get this item.        ||\n");
                printf("<>======================================================<>\n");
                sleep(1);
            }

            break;
        }
    }

    if (!found) {
        printf("Item with ID %d not found.\n", id);
    }

    if (strcmp(loggedinUser, userAdmin) == 0) {
        adminMenu();
    } else {
        normalMenu();
    }
}


// Menu for viewItems
void viewItems(){
    int choice;
    printf("\t\\\\============================================//\n");
    printf("\t||  [1] View All Items (ADMIN)                ||\n");
    printf("\t||============================================||\n");
    printf("\t||  [2] View Per Category (ADMIN)             ||\n");
    printf("\t||============================================||\n");
    printf("\t||  [3] View Department's Items               ||\n");
    printf("\t||============================================||\n");
    printf("\t||  [4] Check Reorder Levels (ADMIN)          ||\n");
    printf("\t||============================================||\n");
    printf("\t||  [5] Back                                  ||\n");
    printf("\t//============================================\\\\\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    switch(choice){
        case 1:
            if(strcmp(loggedinUser, userAdmin)== 0){
                printf("<>============================<>\n");
                printf("||  Viewing All Items...      ||\n");
                printf("<>============================<>\n");
                sleep(1);
                system("cls");
                display_allItems();
            }
            else{
                printf("<>======================================================<>\n");
                printf("||  You don't have permission to use this feature.      ||\n");
                printf("<>======================================================<>\n");
                sleep(2);
                viewItems();
            }
            break;
        case 2:
            display_perCategory();
            break;
        case 3:
            display_perDepartment();
            break;
        case 4:
            check_Reorderlevel();
            break;
        case 5:
            if(strcmp(loggedinUser, userAdmin) == 0){
                adminMenu();
            }
            else{
                normalMenu();
            }
            break;
        default:
            while (getchar() != '\n');
            system("cls");
            return viewItems();
    }
}

// Function that display all the items that has been recorded so far
void display_allItems() {
    int i;
    int choice;
    count = readFile(); // the output is how many products inside the file.
    if (count < 0)
    puts("cannot open file");
    printf("============================================================================================================================================================");
    printf("\n|\t\t\t\t\t\t      *****  TUP'S ALL INVENTORY ITEMS *****                                                               |\n");
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| S.N. |  PRODUCT ID  |    PRODUCT NAME    |   DEPARTMENT   |      CATEGORY      |    UNIT    |  QUANTITY  |   PRICE   |  REORDER LEVEL  |  LAST MODIFIED  | \n");
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    for (i = 0; i < count; i++) { // getting the details on each product updates.
        printf("|%3d   |     %-8d |   %-16s |      %-10s|  %-16s  |  %-9s |     %-6d |   P%-6.2f |       %-9d |  %-14s |\n",
    i + 1, prod[i].id, prod[i].name, prod[i].department, prod[i].category, prod[i].unit, prod[i].quantity,prod[i].price, prod[i].reorderlevel, prod[i].lastModified);
    }
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    
    printf("\t\\\\<><><><><><><><><><><><><><><><>><><><><><><><><//\n");
    printf("\t||          Are you done Checking?                ||\n");
    printf("\t|]================================================[|\n");
    printf("\t|| [1] Yes                                        ||\n");
    printf("\t|]================================================[|\n");
    printf("\t|| [2] View Other Items                           ||\n");
    printf("\t|]================================================[|\n");
    printf("\n Are you done checking?: ");
    scanf("%d", &choice);

    switch(choice){
        case 1:
            if (strcmp(loggedinUser, userAdmin) == 0) {
                adminMenu();
            } else {
                normalMenu();
            }
            break;
        case 2:
            viewItems();
            break;
        default:
            while (getchar() != '\n');
            system("cls");
            return display_allItems();
            


    }

    // viewItems();
}

// Function for printf permission for reusing purposes only
void nopermission(){
    printf("<>======================================================<>\n");
    printf("||  You don't have permission to use this feature.      ||\n");
    printf("<>======================================================<>\n");
}

// Function that display items according to their respective department
void display_perDepartment() {
    int choice;
    printf("\t\\\\<><><><><><><><><><><><><><><><>><><><><><><><><//\n");
    printf("\t||          Select your Department                ||\n");
    printf("\t|]================================================[|\n");
    printf("\t|| [1] COS Department                             ||\n");
    printf("\t|]================================================[|\n");
    printf("\t|| [2] COE Department                             ||\n");
    printf("\t|]================================================[|\n");
    printf("\t|| [3] CIE Department                             ||\n");
    printf("\t|]================================================[|\n");
    printf("\t|| [4] CIT Department                             ||\n");
    printf("\t|]================================================[|\n");
    printf("\t|| [5] CLA Department                             ||\n");
    printf("\t|]================================================[|\n");
    printf("\t|| [6] CAFA Department                            ||\n");
    printf("\t|]================================================[|\n");
    printf("\t|| [7] Back                                       ||\n");
    printf("\t|]================================================[|\n");
    printf("Enter Department: ");
    scanf("%d", &choice);

    char department[20];

    switch (choice) {
        case 1:
            if(strcmp(loggedinUser, user1)==0 || strcmp(loggedinUser, userAdmin) == 0 ){
                strcpy(department, "COS");
            }
            else{
                nopermission();
                sleep(1);
                display_perDepartment();
            }
            break;
        case 2:
            if(strcmp(loggedinUser, user2)==0 || strcmp(loggedinUser, userAdmin) == 0 ){
                strcpy(department, "COE");
            }
            else{
                nopermission();
                sleep(1);
                // system("cls");
                display_perDepartment();
            }
            break;
        case 3:
            if(strcmp(loggedinUser, user3)==0 || strcmp(loggedinUser, userAdmin) == 0 ){
                strcpy(department, "CIE");
            }
            else{
                nopermission();
                sleep(1);
                // system("cls");
                display_perDepartment();
            }
            break;
        case 4:
            if(strcmp(loggedinUser, user4)==0 || strcmp(loggedinUser, userAdmin) == 0 ){
                strcpy(department, "CIT");
            }
            else{
                nopermission();
                sleep(1);
                // system("cls");
                display_perDepartment();
            }
            break;
        case 5:
            if(strcmp(loggedinUser, user5)==0 || strcmp(loggedinUser, userAdmin) == 0 ){
                strcpy(department, "CLA");
            }
            else{
                nopermission();
                sleep(1);
                display_perDepartment();
            }
            break;
        case 6:
            if(strcmp(loggedinUser, user6)==0 || strcmp(loggedinUser, userAdmin) == 0 ){
                strcpy(department, "CAFA");
            }
            else{
                nopermission();
                sleep(1);
                display_perDepartment();
            }
            break;
        case 7:
            // system("cls");
            viewItems();
            break;
        default:
            while (getchar() != '\n');
            printf("\t<>=============================================<>\n");
            printf("\t||              Invalid Choice                 ||\n");
            printf("\t<>====+=====+=====+=====+=====+=====+=====+====<>\n");
            sleep(1);
            system("cls");
            display_perDepartment();
            return;
    }

    printf("\t<>=============================================<>\n");
    printf("\t||           Loading please wait.              ||\n");
    printf("\t<>====+=====+=====+=====+=====+=====+=====+====<>\n");
    sleep(1);

    system("cls");
    printf("============================================================================================================================================================");
    printf("\n|\t\t\t\t\t\t          *****  PRODUCTS IN DEPARTMENT: %-4s *****                                                        |\n", department);
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| S.N. |  PRODUCT ID  |    PRODUCT NAME    |   DEPARTMENT   |      CATEGORY      |    UNIT    |  QUANTITY  |   PRICE   |  REORDER LEVEL  |  LAST MODIFIED  | \n");
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    int found = 0;

    readFile();

    for (int i = 0; i < count; i++) {
        if (strcmp(prod[i].department, department) == 0) {
            printf("|%3d   |     %-8d |   %-16s |      %-10s|  %-16s  |  %-9s |     %-6d |   P%-6.2f |       %-9d |  %-14s |\n",
                i + 1, prod[i].id, prod[i].name, prod[i].department, prod[i].category, prod[i].unit, prod[i].quantity,prod[i].price, prod[i].reorderlevel, prod[i].lastModified);
            found = 1;
        }
    }

    if (!found) {
        printf("No products found in the department: %s\n", department);
    }

    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    if(strcmp(loggedinUser, userAdmin)== 0){
        viewItems();
    }
    else{
        viewItems();
    }

}

// Function that display items according to their respective category
void display_perCategory(){
    int choice;
    if(strcmp(loggedinUser, userAdmin)== 0){
        printf("\t<>=============================================<>\n");
        printf("\t||              Choose a Category              ||\n");
        printf("\t<>====+=====+=====+=====+=====+=====+=====+====<>\n");
        printf("\t\\\\    [1] Cleaning Supply                      //\n");
        printf("\t+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+\n");
        printf("\t//    [2] Office Supply                        \\\\\n");
        printf("\t+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+\n");
    printf("Enter Category: ");
    scanf("%d", &choice);

    char category[100];

    switch (choice) {
        case 1:
            strcpy(category, "Cleaning Supply");
            break;
        case 2:
            strcpy(category, "Office Supply");
            break;
        default:
            while (getchar() != '\n');
            printf("\t<>=============================================<>\n");
            printf("\t||              Invalid Choice                 ||\n");
            printf("\t<>====+=====+=====+=====+=====+=====+=====+====<>\n");
            sleep(1);
            system("cls");
            display_perCategory();
            return;
    }
                printf("\t<>=============================================<>\n");
                printf("\t||           Loading please wait.              ||\n");
                printf("\t<>====+=====+=====+=====+=====+=====+=====+====<>\n");
                sleep(1);

                system("cls");
                printf("============================================================================================================================================================");
                printf("\n|\t\t\t\t\t\t  *****  PRODUCTS IN CATEGORY: %-15s *****                                                       |\n", category);
                printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
                printf("| S.N. |  PRODUCT ID  |    PRODUCT NAME    |   DEPARTMENT   |      CATEGORY      |    UNIT    |  QUANTITY  |   PRICE   |  REORDER LEVEL  |  LAST MODIFIED  | \n");
                printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    int found = 0;

    readFile();

    for (int i = 0; i < count; i++) {
        if (strcmp(prod[i].category, category) == 0) {
            printf("|%3d   |     %-8d |   %-16s |      %-10s|  %-16s  |  %-9s |     %-6d |   P%-6.2f |       %-9d |  %-14s |\n",
                i + 1, prod[i].id, prod[i].name, prod[i].department, prod[i].category, prod[i].unit, prod[i].quantity,prod[i].price, prod[i].reorderlevel, prod[i].lastModified);
            found = 1;
        }
    }

    if (!found) {
        printf("No products found in the category: %s\n", category);
    }

    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    viewItems();
    }
    else{
        nopermission();
        sleep(1);
        viewItems();
    }

}

// Function that lists the items that needs to be restock
void check_Reorderlevel() {
    if(strcmp(loggedinUser, userAdmin)== 0 ){

                printf("\t<>=============================================<>\n");
                printf("\t|| Checking Items Need to be Restock...        ||\n");
                printf("\t<>====+=====+=====+=====+=====+=====+=====+====<>\n");
                sleep(2);

                printf("============================================================================================================================================================");
                printf("\n|\t\t\t\t\t\t      *****  PRODUCTS NEEDING RESTOCK*****                                                                 |\n");
                printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
                printf("| S.N. |  PRODUCT ID  |    PRODUCT NAME    |   DEPARTMENT   |      CATEGORY      |    UNIT    |  QUANTITY  |   PRICE   |  REORDER LEVEL  |  LAST MODIFIED  | \n");
                printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    int found = 0;

    readFile();

    for (int i = 0; i < count; i++) {
        if (prod[i].quantity <= prod[i].reorderlevel) {
                printf("|%3d   |     %-8d |   %-16s |      %-10s|  %-16s  |  %-9s |     %-6d |   P%-6.2f |       %-9d |  %-14s |\n",
                i + 1, prod[i].id, prod[i].name, prod[i].department, prod[i].category, prod[i].unit, prod[i].quantity,prod[i].price, prod[i].reorderlevel, prod[i].lastModified);
            found = 1;
        }
    }

    if (!found) {
        printf("No products need to be restocked at the moment.\n");
    }

    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------\n");


    viewItems();
    }
    else{
        nopermission();
        sleep(1);
        viewItems();
    }
}

// This function will get the Item from the Inventory and Record the transaction and add it to addTransaction function
void getItemFromInventory(int productId, const char* productName, int quantity) {
    // ... Code to get the item details from the inventory ...

    // Get the current date and time
    time_t currentTime = time(NULL);
    struct tm* localTime = localtime(&currentTime);
    char dateString[11];
    char timeString[9];
    strftime(dateString, sizeof(dateString), "%Y-%m-%d", localTime);
    strftime(timeString, sizeof(timeString), "%H:%M:%S", localTime);

    // Record the transaction
    addTransaction(dateString, timeString, productId, productName, quantity);
}

// Menu for ReportandAnalytics
void ReportandAnalytics(){
    int choice;
    printf("\t\\\\==============================================//\n");
    printf("\t||   Welcome to Report and Analytics Section    ||\n");
    printf("\t||==============================================||\n");
    printf("\t||   [1] Daily Report                           ||\n");
    printf("\t||==============================================||\n");
    printf("\t||   [2] Weekly Report                          ||\n");
    printf("\t||==============================================||\n");
    printf("\t||   [3] Back                                   ||\n");
    printf("\t||==============================================||\n");
    printf("Enter Choice: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        printf("\t||==============================================||\n");
        printf("\t||  GENERATING DAILY REPORT...                  ||\n");
        printf("\t||==============================================||\n");
        sleep(1);
        system("cls");
        generateDailyReport();
        sleep(1);
        ReportandAnalytics();
        break;
    case 2:
        printf("\t||==============================================||\n");
        printf("\t||  GENERATING WEEKLY REPORT...                 ||\n");
        printf("\t||==============================================||\n");
        sleep(1);
        system("cls");
        generateWeeklyReport();
        sleep(1);
        ReportandAnalytics();
    case 3:
        adminMenu();
        break;
    default:
        while (getchar() != '\n');
        system("cls");
        return ReportandAnalytics();
        
    }
}


// Function that records the transaction made so far and write it in the transaction_history.txt file
void addTransaction(const char *date, const char *time, int productId, const char *productName, int quantity) {
    if (transactionCount < MAX_TRANSACTIONS) {
        strcpy(transactions[transactionCount].date, date);
        strcpy(transactions[transactionCount].time, time);
        transactions[transactionCount].productId = productId;
        strcpy(transactions[transactionCount].productName, productName);
        transactions[transactionCount].quantity = quantity;
        transactionCount++;

        // Open the transaction history file in append mode
        FILE *transactionFile = fopen("inventories/transaction_history.txt", "a");
        if (transactionFile == NULL) {
            printf("Error opening the transaction history file.\n");
            return;
        }

        // Write the transaction details to the file
        fprintf(transactionFile, "| %-10s | %-8s |  %-10d |   %-16s |  %-9d |\n",
                date, time, productId, productName, quantity);

        // Close the transaction history file
        fclose(transactionFile);
    } else {
        printf("Transaction limit reached. Cannot add more transactions.\n");
    }
}


// Functions that generates today's daily report
void generateDailyReport() {
    // Get the current date
    time_t currentTime = time(NULL);
    struct tm *localTime = localtime(&currentTime);
    char dateString[20];
    strftime(dateString, sizeof(dateString), "%Y-%m-%d", localTime);

    // Create a filename for the report using the current date
    char filename[50];
    sprintf(filename, "dailyreports/daily_report_%s.txt", dateString);

    // Open the file for appending
    FILE *reportFile = fopen(filename, "w");
    if (reportFile == NULL) {
        printf("Error opening the report file.\n");
        return;
    }

    // Write the report header
    fprintf(reportFile, "DAILY REPORT - %s\n", dateString);
    fprintf(reportFile, "----------------------------------------\n");

    // Read the items from the file
    int count = readFile();  // Assuming you have a readFile() function to retrieve item count

    // Write the report content
    fprintf(reportFile, "Number of Items: %d\n", count);

    // Calculate the total value of all items
    float totalValue = 0.0;
    for (int i = 0; i < count; i++) {
        float itemValue = prod[i].quantity * prod[i].price;
        totalValue += itemValue;
    }
    fprintf(reportFile, "Total Value of All Items: P%.2f\n", totalValue);

    // Write the individual item details
    fprintf(reportFile, "\nItem Details:\n");
    fprintf(reportFile, "-----------------------------------------------------------------------------------------------------------------------------\n");
    fprintf(reportFile, "| S.N. |  PRODUCT ID  |    PRODUCT NAME    |   DEPARTMENT   |      CATEGORY      |  QUANTITY  |   PRICE   |  REORDER LEVEL  |\n");
    fprintf(reportFile, "-----------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        fprintf(reportFile, "|%3d   |     %-8d |   %-16s |      %-10s|  %-16s  |     %-6d |   P%-6.2f |       %-9d |\n",
                i + 1, prod[i].id, prod[i].name, prod[i].department, prod[i].category, prod[i].quantity, prod[i].price, prod[i].reorderlevel);
    }
    fprintf(reportFile, "-----------------------------------------------------------------------------------------------------------------------------\n");

    // Write the current transaction history for today
    fprintf(reportFile, "\nCurrent Transaction History (Today):\n");
    fprintf(reportFile, "-----------------------------------------------------------------------------------------------------------------------------\n");
    fprintf(reportFile, "|   DATE    |   TIME    |  PRODUCT ID  |    PRODUCT NAME    |  QUANTITY  |\n");
    fprintf(reportFile, "-----------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < transactionCount; i++) {
        // Check if the transaction date matches today's date
        if (strcmp(transactions[i].date, dateString) == 0) {
            fprintf(reportFile, "| %-10s | %-8s |  %-10d |   %-16s |  %-9d |\n",
                    transactions[i].date, transactions[i].time, transactions[i].productId, transactions[i].productName, transactions[i].quantity);
        }
    }
    fprintf(reportFile, "-----------------------------------------------------------------------------------------------------------------------------\n");

    // Write the transaction history
    fprintf(reportFile, "\nTransaction History:\n");
    fprintf(reportFile, "-----------------------------------------------------------------------------------------------------------------------------\n");
    fprintf(reportFile, "|   DATE    |   TIME    |  PRODUCT ID  |    PRODUCT NAME    |  QUANTITY  |\n");
    fprintf(reportFile, "-----------------------------------------------------------------------------------------------------------------------------\n");

    // Write the previous transaction history from the file
    FILE *previousReportFile = fopen("inventories/transaction_history.txt", "r");
    if (previousReportFile != NULL) {
        char line[100];
        while (fgets(line, sizeof(line), previousReportFile) != NULL) {
            // Extract the date from the line
            char transactionDate[20];
            sscanf(line, "| %s", transactionDate);

            // Check if the transaction date matches today's date
            if (strcmp(transactionDate, dateString) == 0) {
                fprintf(reportFile, "%s", line);
            }
        }
        fclose(previousReportFile);
    }

    // Close the report file
    fclose(reportFile);
    printf("Daily report generated successfully. Filename: %s\n\n", filename);

}


// Function that automatically generates today's daily report when a user exits the program
void generateDailyReportOnExit() {
    // Get the current date
    time_t currentTime = time(NULL);
    struct tm *localTime = localtime(&currentTime);
    char dateString[20];
    strftime(dateString, sizeof(dateString), "%Y-%m-%d", localTime);

    // Create a filename for the report using the current date
    char filename[50];
    sprintf(filename, "dailyreports/daily_report_%s.txt", dateString);

    // Open the file for appending
    FILE *reportFile = fopen(filename, "w");
    if (reportFile == NULL) {
        printf("Error opening the report file.\n");
        return;
    }

    // Write the report header
    fprintf(reportFile, "DAILY REPORT - %s\n", dateString);
    fprintf(reportFile, "----------------------------------------\n");

    // Read the items from the file
    int count = readFile();  // Assuming you have a readFile() function to retrieve item count

    // Write the report content
    fprintf(reportFile, "Number of Items: %d\n", count);

    // Calculate the total value of all items
    float totalValue = 0.0;
    for (int i = 0; i < count; i++) {
        float itemValue = prod[i].quantity * prod[i].price;
        totalValue += itemValue;
    }
    fprintf(reportFile, "Total Value of All Items: P%.2f\n", totalValue);

    // Write the individual item details
    fprintf(reportFile, "\nItem Details:\n");
    fprintf(reportFile, "-----------------------------------------------------------------------------------------------------------------------------\n");
    fprintf(reportFile, "| S.N. |  PRODUCT ID  |    PRODUCT NAME    |   DEPARTMENT   |      CATEGORY      |  QUANTITY  |   PRICE   |  REORDER LEVEL  |\n");
    fprintf(reportFile, "-----------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        fprintf(reportFile, "|%3d   |     %-8d |   %-16s |      %-10s|  %-16s  |     %-6d |   P%-6.2f |       %-9d |\n",
                i + 1, prod[i].id, prod[i].name, prod[i].department, prod[i].category, prod[i].quantity, prod[i].price, prod[i].reorderlevel);
    }
    fprintf(reportFile, "-----------------------------------------------------------------------------------------------------------------------------\n");

    // Write the current transaction history for today
    fprintf(reportFile, "\nCurrent Transaction History (Today):\n");
    fprintf(reportFile, "-----------------------------------------------------------------------------------------------------------------------------\n");
    fprintf(reportFile, "|   DATE    |   TIME    |  PRODUCT ID  |    PRODUCT NAME    |  QUANTITY  |\n");
    fprintf(reportFile, "-----------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < transactionCount; i++) {
        // Check if the transaction date matches today's date
        if (strcmp(transactions[i].date, dateString) == 0) {
            fprintf(reportFile, "| %-10s | %-8s |  %-10d |   %-16s |  %-9d |\n",
                    transactions[i].date, transactions[i].time, transactions[i].productId, transactions[i].productName, transactions[i].quantity);
        }
    }
    fprintf(reportFile, "-----------------------------------------------------------------------------------------------------------------------------\n");

    // Write the transaction history
    fprintf(reportFile, "\nTransaction History:\n");
    fprintf(reportFile, "-----------------------------------------------------------------------------------------------------------------------------\n");
    fprintf(reportFile, "|   DATE    |   TIME    |  PRODUCT ID  |    PRODUCT NAME    |  QUANTITY  |\n");
    fprintf(reportFile, "-----------------------------------------------------------------------------------------------------------------------------\n");

    // Write the previous transaction history from the file
    FILE *previousReportFile = fopen("inventories/transaction_history.txt", "r");
    if (previousReportFile != NULL) {
        char line[100];
        while (fgets(line, sizeof(line), previousReportFile) != NULL) {
            // Extract the date from the line
            char transactionDate[20];
            sscanf(line, "| %s", transactionDate);

            // Check if the transaction date matches today's date
            if (strcmp(transactionDate, dateString) == 0) {
                fprintf(reportFile, "%s", line);
            }
        }
        fclose(previousReportFile);
    }

    // Close the report file
    fclose(reportFile);

    printf("Daily report generated successfully. Filename: %s\n\n", filename);
}

// Functions that generates weekly report
void generateWeeklyReport() {
    // Get the current date
    time_t currentTime = time(NULL);
    struct tm *localTime = localtime(&currentTime);
    char startDateString[20];
    char endDateString[20];

    // Calculate the start and end dates of the week
    int currentDayOfWeek = localTime->tm_wday;
    int daysSinceStartOfWeek = (currentDayOfWeek + 7 - 1) % 7; // Assuming Sunday is the first day of the week
    time_t startDate = currentTime - (daysSinceStartOfWeek * 24 * 60 * 60);
    time_t endDate = startDate + (6 * 24 * 60 * 60);

    // Format the start and end dates as strings
    strftime(startDateString, sizeof(startDateString), "%Y-%m-%d", localtime(&startDate));
    strftime(endDateString, sizeof(endDateString), "%Y-%m-%d", localtime(&endDate));

    // Create a filename for the report using the start and end dates
    char filename[50];
    sprintf(filename, "weeklyreports/weekly_report_%s_to_%s.txt", startDateString, endDateString);

    // Open the file for appending
    FILE *reportFile = fopen(filename, "w");
    if (reportFile == NULL) {
        printf("Error opening the report file.\n");
        return;
    }

    // Write the report header
    fprintf(reportFile, "\n\n");
    fprintf(reportFile, "WEEKLY REPORT - %s to %s\n", startDateString, endDateString);
    fprintf(reportFile, "----------------------------------------\n");

    // Read the items from the file
    int count = readFile();

    // Write the report content
    fprintf(reportFile, "Number of Items: %d\n", count);

    // Calculate the total value of all items
    float totalValue = 0.0;
    for (int i = 0; i < count; i++) {
        float itemValue = prod[i].quantity * prod[i].price;
        totalValue += itemValue;
    }
    fprintf(reportFile, "Total Value of All Items: P%.2f\n", totalValue);

    // Write the individual item details
    fprintf(reportFile, "\nItem Details:\n");
    fprintf(reportFile, "-----------------------------------------------------------------------------------------------------------------------------\n");
    fprintf(reportFile, "| S.N. |  PRODUCT ID  |    PRODUCT NAME    |   DEPARTMENT   |      CATEGORY      |  QUANTITY  |   PRICE   |  REORDER LEVEL  |\n");
    fprintf(reportFile, "-----------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        fprintf(reportFile, "|%3d   |     %-8d |   %-16s |      %-10s|  %-16s  |     %-6d |   P%-6.2f |       %-9d |\n",
                i + 1, prod[i].id, prod[i].name, prod[i].department, prod[i].category, prod[i].quantity, prod[i].price, prod[i].reorderlevel);
    }
    fprintf(reportFile, "-----------------------------------------------------------------------------------------------------------------------------\n");

    // Write the current transaction history
    fprintf(reportFile, "\nCurrent Transaction History:\n");
    fprintf(reportFile, "-----------------------------------------------------------------------------------------------------------------------------\n");
    fprintf(reportFile, "|   DATE    |   TIME    |  PRODUCT ID  |    PRODUCT NAME    |  QUANTITY  |\n");
    fprintf(reportFile, "-----------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < transactionCount; i++) {
        fprintf(reportFile, "| %-10s | %-8s |  %-10d |   %-16s |  %-9d |\n",
                transactions[i].date, transactions[i].time, transactions[i].productId, transactions[i].productName, transactions[i].quantity);
    }
    fprintf(reportFile, "-----------------------------------------------------------------------------------------------------------------------------\n");


    // Write the transaction history from previous reports
    FILE *previousReportFile = fopen("inventories/transaction_history.txt", "r");
    if (previousReportFile != NULL) {
        fprintf(reportFile, "\nTransaction History:\n");
        fprintf(reportFile, "-----------------------------------------------------------------------------------------------------------------------------\n");
        fprintf(reportFile, "|   DATE    |   TIME    |  PRODUCT ID  |    PRODUCT NAME    |  QUANTITY  |\n");
        fprintf(reportFile, "-----------------------------------------------------------------------------------------------------------------------------\n");

        char line[100];
        while (fgets(line, sizeof(line), previousReportFile) != NULL) {
            // Split the date into year, month, and day
            int transactionYear, transactionMonth, transactionDay;
            sscanf(line, "| %d-%d-%d", &transactionYear, &transactionMonth, &transactionDay);

            // Split the start and end date into year, month, and day
            int startYear, startMonth, startDay;
            sscanf(startDateString, "%d-%d-%d", &startYear, &startMonth, &startDay);

            int endYear, endMonth, endDay;
            sscanf(endDateString, "%d-%d-%d", &endYear, &endMonth, &endDay);

            // Compare the year, month, and day to filter transactions within the week
            if (transactionYear >= startYear && transactionYear <= endYear &&
                transactionMonth >= startMonth && transactionMonth <= endMonth &&
                transactionDay >= startDay && transactionDay <= endDay) {
                fprintf(reportFile, "%s", line);
            }
        }

        fclose(previousReportFile);
    }

    // Close the report file
    fclose(reportFile);

    printf("Weekly report generated successfully. Filename: %s\n", filename);
}

// Function that automatically generates weekly report when a user exits the program
void generateWeeklyReportonExit() {
    // Get the current date
    time_t currentTime = time(NULL);
    struct tm *localTime = localtime(&currentTime);
    char startDateString[20];
    char endDateString[20];

    // Calculate the start and end dates of the week
    int currentDayOfWeek = localTime->tm_wday;
    int daysSinceStartOfWeek = (currentDayOfWeek + 7 - 1) % 7; // Assuming Sunday is the first day of the week
    time_t startDate = currentTime - (daysSinceStartOfWeek * 24 * 60 * 60);
    time_t endDate = startDate + (6 * 24 * 60 * 60);

    // Format the start and end dates as strings
    strftime(startDateString, sizeof(startDateString), "%Y-%m-%d", localtime(&startDate));
    strftime(endDateString, sizeof(endDateString), "%Y-%m-%d", localtime(&endDate));

    // Create a filename for the report using the start and end dates
    char filename[50];
    sprintf(filename, "weeklyreports/weekly_report_%s_to_%s.txt", startDateString, endDateString);

    // Open the file for appending
    FILE *reportFile = fopen(filename, "w");
    if (reportFile == NULL) {
        printf("Error opening the report file.\n");
        return;
    }

    // Write the report header
    fprintf(reportFile, "\n\n");
    fprintf(reportFile, "WEEKLY REPORT - %s to %s\n", startDateString, endDateString);
    fprintf(reportFile, "----------------------------------------\n");

    // Read the items from the file
    int count = readFile();

    // Write the report content
    fprintf(reportFile, "Number of Items: %d\n", count);

    // Calculate the total value of all items
    float totalValue = 0.0;
    for (int i = 0; i < count; i++) {
        float itemValue = prod[i].quantity * prod[i].price;
        totalValue += itemValue;
    }
    fprintf(reportFile, "Total Value of All Items: P%.2f\n", totalValue);

    // Write the individual item details
    fprintf(reportFile, "\nItem Details:\n");
    fprintf(reportFile, "-----------------------------------------------------------------------------------------------------------------------------\n");
    fprintf(reportFile, "| S.N. |  PRODUCT ID  |    PRODUCT NAME    |   DEPARTMENT   |      CATEGORY      |  QUANTITY  |   PRICE   |  REORDER LEVEL  |\n");
    fprintf(reportFile, "-----------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        fprintf(reportFile, "|%3d   |     %-8d |   %-16s |      %-10s|  %-16s  |     %-6d |   P%-6.2f |       %-9d |\n",
                i + 1, prod[i].id, prod[i].name, prod[i].department, prod[i].category, prod[i].quantity, prod[i].price, prod[i].reorderlevel);
    }
    fprintf(reportFile, "-----------------------------------------------------------------------------------------------------------------------------\n");

    // Write the current transaction history
    fprintf(reportFile, "\nCurrent Transaction History:\n");
    fprintf(reportFile, "-----------------------------------------------------------------------------------------------------------------------------\n");
    fprintf(reportFile, "|   DATE    |   TIME    |  PRODUCT ID  |    PRODUCT NAME    |  QUANTITY  |\n");
    fprintf(reportFile, "-----------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < transactionCount; i++) {
        fprintf(reportFile, "| %-10s | %-8s |  %-10d |   %-16s |  %-9d |\n",
                transactions[i].date, transactions[i].time, transactions[i].productId, transactions[i].productName, transactions[i].quantity);
    }
    fprintf(reportFile, "-----------------------------------------------------------------------------------------------------------------------------\n");


    // Write the transaction history from previous reports
    FILE *previousReportFile = fopen("inventories/transaction_history.txt", "r");
    if (previousReportFile != NULL) {
        fprintf(reportFile, "\nTransaction History:\n");
        fprintf(reportFile, "-----------------------------------------------------------------------------------------------------------------------------\n");
        fprintf(reportFile, "|   DATE    |   TIME    |  PRODUCT ID  |    PRODUCT NAME    |  QUANTITY  |\n");
        fprintf(reportFile, "-----------------------------------------------------------------------------------------------------------------------------\n");

        char line[100];
        while (fgets(line, sizeof(line), previousReportFile) != NULL) {
            // Split the date into year, month, and day
            int transactionYear, transactionMonth, transactionDay;
            sscanf(line, "| %d-%d-%d", &transactionYear, &transactionMonth, &transactionDay);

            // Split the start and end date into year, month, and day
            int startYear, startMonth, startDay;
            sscanf(startDateString, "%d-%d-%d", &startYear, &startMonth, &startDay);

            int endYear, endMonth, endDay;
            sscanf(endDateString, "%d-%d-%d", &endYear, &endMonth, &endDay);

            // Compare the year, month, and day to filter transactions within the week
            if (transactionYear >= startYear && transactionYear <= endYear &&
                transactionMonth >= startMonth && transactionMonth <= endMonth &&
                transactionDay >= startDay && transactionDay <= endDay) {
                fprintf(reportFile, "%s", line);
            }
        }

        fclose(previousReportFile);
    }

    // Close the report file
    fclose(reportFile);

    printf("Weekly report generated successfully. Filename: %s\n", filename);
}
