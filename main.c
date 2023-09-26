#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct AccountNode *Accounthead = NULL;                                                    // global account node pointer that stores the head of the account linked list.
struct ContactNode *Contacthead = NULL;                                                    // global contact node pointer that stores the head of the contact linked list.
void login(char *name, char *password);                                                    // provides the options available after logging in.
void freeAccountList();                                                                    // frees the global linked list that stores accounts
void freeContactList();                                                                    // frees the global linked list that stores contacts
struct AccountNode *createAccountNode(const char *name, const char *password);             // creates and initializes account node
struct ContactNode *createContactNode(const char *name, const char *number);               // creates and initializes contact node
void appendAccountNode(struct AccountNode **head, const char *name, const char *password); // adds a new account node to the start of the linked list
void printAccountList();                                                                   // prints the information account linked list
void loadAccountsCSV();                                                                    // loads data from csv file to linked list
void unloadAccountCSV();                                                                   // unloads data from linked list to csv file.
void freeContactList();                                                                    // frees the contact linked list
struct ContactNode *createContactNode(const char *name, const char *number);               // creates and initializes a new contact node.
void appendContactNode(struct ContactNode **head, const char *name, const char *number);   // adds a contact node to start of contact linked list.
void printContactList();                                                                   // prints the contact linked list.
void loadContactCSV(char *filename);                                                       // loads the information from csv file to contacts linked list.
void unloadContactCSV(char *filename);                                                     // unloads the information from contacts linked list to csv file.
void newAccount();                                                                         // creates new account
void loggingIn();                                                                          // logs in user to their account
void deleteAccount();                                                                      // deletes a user's account
void forgetPassword();                                                                     // changes a user's account after taking the admin's password
void newcontact(char *name, char *password);                                               // creates a new contact
void deletecontact(char *name, char *password);                                            // deletes a contact
void editName(char *name, char *password);                                                 // changes the name of a contact
void editNumber(char *name, char *password);                                               // changes the number of a contact
char *searchContact(char *name, char *password);                                           // searches and displays a contact
void login(char *name, char *password);                                                    // provides all the options that are available after logging in.

struct AccountNode
{
    char name[100];
    char password[100];
    struct AccountNode *next;
};
void freeAccountList()
{
    struct AccountNode *head = Accounthead;
    while (head != NULL)
    {
        struct AccountNode *temp = head;
        head = head->next;
        free(temp);
    }
    Accounthead = NULL;
}
struct AccountNode *createAccountNode(const char *name, const char *password)
{
    struct AccountNode *newNode = (struct AccountNode *)malloc(sizeof(struct AccountNode));
    if (newNode == NULL)
    {
        perror("\t\t\t \033[1;32mMemory allocation failed\033[0m");
        exit(1);
    }
    strncpy(newNode->name, name, sizeof(newNode->name));
    strncpy(newNode->password, password, sizeof(newNode->password));
    newNode->next = NULL;
    return newNode;
}
void appendAccountNode(struct AccountNode **head, const char *name, const char *password)
{
    struct AccountNode *newNode = createAccountNode(name, password);
    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        struct AccountNode *current = *head;
        struct AccountNode *temp = current->next;
        current->next = newNode;
        newNode->next = temp;
    }
}
void printAccountList()
{
    struct AccountNode *current = Accounthead;
    while (current != NULL)
    {
        printf("\t\t\t \033[1;34mName: %s, Password: %s\033[0m\n", current->name, current->password);
        current = current->next;
    }
}
void loadAccountsCSV()
{
    freeAccountList();
    FILE *file = fopen("accounts.csv", "r");
    if (file == NULL)
    {
        perror("\t\t\t \033[1;31mError opening the file\033[0m");
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        char name[100];
        char password[100];
        if (sscanf(line, " %[^,],%s", name, password) == 2)
        {
            appendAccountNode(&Accounthead, name, password);
        }
    }
    fclose(file);
}
void unloadAccountCSV()
{
    FILE *fptr = fopen("accounts.csv", "w");
    if (fptr == NULL)
    {
        perror("\t\t\t \033[1;31mError opening the file\033[0m");
        return;
    }
    struct AccountNode *current = Accounthead;
    int numAccount = 0;
    while (current != NULL)
    {
        numAccount++;
        current = current->next;
    }
    struct AccountNode *accountArray = (struct AccountNode *)malloc(numAccount * sizeof(struct AccountNode));
    current = Accounthead;
    for (int i = 0; i < numAccount; i++)
    {
        strcpy(accountArray[i].name, current->name);
        strcpy(accountArray[i].password, current->password);
        current = current->next;
    }
    for (int i = 0; i < numAccount - 1; i++)
    {
        for (int j = i + 1; j < numAccount; j++)
        {
            if (strcmp(accountArray[i].name, accountArray[j].name) > 0)
            {
                struct AccountNode temp = accountArray[i];
                accountArray[i] = accountArray[j];
                accountArray[j] = temp;
            }
        }
    }
    for (int i = 0; i < numAccount; i++)
    {
        fprintf(fptr, "%s,%s\n", accountArray[i].name, accountArray[i].password);
    }
    fclose(fptr);
    free(accountArray);
    freeAccountList();
}

struct ContactNode
{
    char name[100];
    char number[100];
    struct ContactNode *next;
};
void freeContactList()
{
    struct ContactNode *head = Contacthead;
    while (head != NULL)
    {
        struct ContactNode *temp = head;
        head = head->next;
        free(temp);
    }
    Contacthead = NULL;
}
struct ContactNode *createContactNode(const char *name, const char *number)
{
    struct ContactNode *newNode = (struct ContactNode *)malloc(sizeof(struct ContactNode));
    if (newNode == NULL)
    {
        perror("\t\t\t \033[1;31mMemory allocation failed\033[0m");
        exit(1);
    }
    strncpy(newNode->name, name, sizeof(newNode->name));
    strncpy(newNode->number, number, sizeof(newNode->number));
    newNode->next = NULL;
    return newNode;
}
void appendContactNode(struct ContactNode **head, const char *name, const char *number)
{
    struct ContactNode *newNode = createContactNode(name, number);
    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        struct ContactNode *current = *head;
        struct ContactNode *temp = current->next;
        current->next = newNode;
        newNode->next = temp;
    }
}

void loadContactCSV(char *filename)
{
    freeContactList();
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("\t\t\t \033[1;31mError opening the file\033[0m");
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        char name[100];
        char number[100];
        if (sscanf(line, "%[^,],%s", name, number) == 2)
        {
            appendContactNode(&Contacthead, name, number);
        }
    }
    fclose(file);
}
void unloadContactCSV(char *filename)
{
    FILE *fptr = fopen(filename, "w");
    if (fptr == NULL)
    {
        perror("\t\t\t \033[1;31mError opening the file\033[0m");
        return;
    }
    struct ContactNode *current = Contacthead;
    int numContact = 0;
    while (current != NULL)
    {
        numContact++;
        current = current->next;
    }
    struct ContactNode *contactArray = (struct ContactNode *)malloc(numContact * sizeof(struct ContactNode));
    current = Contacthead;
    for (int i = 0; i < numContact; i++)
    {
        strcpy(contactArray[i].name, current->name);
        strcpy(contactArray[i].number, current->number);
        current = current->next;
    }
    for (int i = 0; i < numContact - 1; i++)
    {
        for (int j = i + 1; j < numContact; j++)
        {
            if (strcmp(contactArray[i].name, contactArray[j].name) > 0)
            {
                struct ContactNode temp = contactArray[i];
                contactArray[i] = contactArray[j];
                contactArray[j] = temp;
            }
        }
    }
    for (int i = 0; i < numContact; i++)
    {
        fprintf(fptr, "%s,%s\n", contactArray[i].name, contactArray[i].number);
    }
    fclose(fptr);
    free(contactArray);
    freeContactList();
}

void newAccount()
{

    char name[15];
    int flag = 0;
    char password[15];
    printf("\n\t\t\t \033[1;32mEnter your name: \033[0m\033[1;33m");
    scanf(" %[^\n]", name);
    printf("\033[0m");
    printf("\t\t\t \033[1;32mEnter your password: \033[0m\033[1;33m");
    scanf(" %[^\n]", password);
    printf("\033[0m");
    loadAccountsCSV();
    struct AccountNode *curr = Accounthead;
    while (curr != NULL)
    {
        if (strcmp(curr->name, name) == 0)
        {
            flag = 1;
        }
        curr = curr->next;
    }
    if (flag == 0)
    {
        appendAccountNode(&Accounthead, name, password);
        unloadAccountCSV(Accounthead);
        char filename[50];
        snprintf(filename, sizeof(filename), "%s%s.csv", name, password);
        FILE *file = fopen(filename, "w");
        if (file == NULL)
        {
            perror("\n\t\t\t \033[1;31mFailed to create file\033[0m");
            return;
        }
        fclose(file);
    }
}
void loggingIn()
{
    char name[15];
    char password[15];
    printf("\n\t\t\t \033[1;32mEnter your name: \033[0m\033[1;33m");
    scanf(" %[^\n]", name);
    printf("\033[0m");
    printf("\t\t\t \033[1;32mEnter your password: \033[0m\033[1;33m");
    scanf(" %[^\n]", password);
    printf("\033[0m");
    loadAccountsCSV();
    struct AccountNode *curr = Accounthead;
    while (curr != NULL)
    {
        if (strcmp(curr->name, name) == 0 && strcmp(curr->password, password) == 0)
        {
            login(name, password);
            return;
        }
        curr = curr->next;
    }
    printf("\n\t\t\t \033[1;31mLogin credentials not found!\033[0m\n");
}
void deleteAccount()
{
    char name[15];
    char password[15];
    printf("\n\t\t\t \033[1;32mEnter your name: \033[0m\033[1;33m");
    scanf(" %[^\n]", name);
    printf("\033[0m");
    printf("\n\t\t\t \033[1;32mEnter your password: \033[0m\033[1;33m");
    scanf("%s", password);
    printf("\033[0m");
    loadAccountsCSV();
    if (Accounthead == NULL)
    {
        printf("\n\t\t\t \033[1;31mNo accounts found.\033[0m\n");
        return;
    }
    struct AccountNode *curr = Accounthead;
    struct AccountNode *prev = NULL;
    while (curr != NULL)
    {
        if (strcmp(curr->name, name) == 0 && strcmp(curr->password, password) == 0)
        {
            if (prev == NULL)
            {
                Accounthead = Accounthead->next;
            }
            else
            {
                prev->next = curr->next;
            }
            free(curr);
            char filename[50];
            snprintf(filename, sizeof(filename), "%s%s.csv", name, password);
            if (remove(filename) == 0)
            {
                printf("\n\t\t\t \033[1;34mAccount '%s' has been deleted.\033[0m\n", name);
            }
            else
            {
                printf("\n\t\t\t \033[1;31mFailed to delete account '%s'.\033[0m\n", name);
            }
            unloadAccountCSV(Accounthead);

            return;
        }
        prev = curr;
        curr = curr->next;
    }
    printf("\n\t\t\t \033[1;31mAccount with name '%s' and password '%s' not found.\033[0m\n", name, password);
}
void forgetPassword()
{
    int adminPass;
    printf("\n\t\t\t \033[1;32mEnter admin password : \033[0m\033[1;33m");
    scanf("%d", &adminPass);
    printf("\033[0m");
    if (adminPass != 123)
    {
        printf("\t\t\t \033[1;31mWrong admin password!!\033[0m");
        return;
    }
    char name[15], newpass[15];
    printf("\t\t\t \033[1;32mEnter your name : \033[0m\033[1;33m");
    scanf(" %[^\n]", name);
    printf("\033[0m");
    loadAccountsCSV();
    struct AccountNode *current = Accounthead;
    while (current != NULL)
    {
        if ((strcmp(current->name, name) == 0))
        {

            printf("\t\t\t \033[1;32mEnter your new password : \033[0m\033[1;33m");
            scanf(" %[^\n]", newpass);
            printf("\033[0m");
            char oldName[35];
            strcpy(oldName, name);
            strcat(oldName, current->password);
            strcat(oldName, ".csv");
            char newName[35];
            strcpy(newName, name);
            strcat(newName, newpass);
            strcat(newName, ".csv");
            strcpy(current->password, newpass);
            unloadAccountCSV(Accounthead);
            // csvfile
            if (rename(oldName, newName) == 0)
            {
                printf("\t\t\t \033[1;34mFile renamed successfully.\033[0m\n");
            }
            else
            {
                perror("\t\t\t \033[1;31mError renaming file\033[0m\n");
            }
            return;
        }
        current = current->next;
    }
}

void newcontact(char *name, char *password)
{
    char contactname[15];
    char number[15];
    int flag = 0;
    printf("\t\t\t \033[1;32mEnter your name : \033[0m\033[1;33m");
    scanf(" %[^\n]", contactname);
    printf("\033[0m");
    printf("\t\t\t \033[1;32mEnter your number : \033[0m\033[1;33m");
    scanf(" %[^\n]", number);
    printf("\033[0m");
    char filename[50];
    snprintf(filename, sizeof(filename), "%s%s.csv", name, password);
    loadContactCSV(filename);
    struct ContactNode *curr = Contacthead;
    while (curr != NULL)
    {
        if (strcmp(curr->name, contactname) == 0 && strcmp(curr->number, number) == 0)
        {
            flag = 1;
        }
        curr = curr->next;
    }
    if (flag == 0)
    {
        appendContactNode(&Contacthead, contactname, number);
        unloadContactCSV(filename);
    }
}
void deletecontact(char *name, char *password)
{
    char contactname[15];
    char number[15];
    printf("\t\t\t \033[1;32mEnter your name : \033[0m\033[1;33m");
    scanf(" %[^\n]", contactname);
    printf("\033[0m");
    printf("\t\t\t \033[1;32mEnter your number : \033[0m\033[1;33m");
    scanf(" %[^\n]", number);
    printf("\033[0m");
    char filename[50];
    snprintf(filename, sizeof(filename), "%s%s.csv", name, password);
    loadContactCSV(filename);
    if (Contacthead == NULL)
    {
        printf("\t\t\t \033[1;31mNo contacts found.\033[0m");
        return;
    }
    struct ContactNode *curr = Contacthead;
    struct ContactNode *prev = NULL;
    while (curr != NULL)
    {
        if (strcmp(curr->name, contactname) == 0 && strcmp(curr->number, number) == 0)
        {
            if (prev == NULL)
            {
                Contacthead = Contacthead->next;
            }
            else
            {
                prev->next = curr->next;
            }
            free(curr);
            unloadContactCSV(filename);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    printf("\t\t\t \033[1;31mAccount with name '%s' and number '%s' not found.\033[0m\n", contactname, number);
}
void editName(char *name, char *password)
{
    char filename[50];
    snprintf(filename, sizeof(filename), "%s%s.csv", name, password);
    loadContactCSV(filename);
    printf("\t\t\t \033[1;32mEnter the number whose name you want to edit : \033[0m\033[1;33m");
    char number[15];
    scanf(" %[^\n]", number);
    printf("\033[0m");
    char Contactname[15];
    printf("\t\t\t \033[1;32mEnter the new name : \033[0m\033[1;33m");
    scanf(" %[^\n]", Contactname);
    printf("\033[0m");
    struct ContactNode *curr = Contacthead;
    while (curr != NULL)
    {
        if (strcmp(curr->number, number) == 0)
        {
            strcpy(curr->name, Contactname);
            break;
        }
        curr = curr->next;
    }
    unloadContactCSV(filename);
}
void editNumber(char *name, char *password)
{
    char filename[50];
    snprintf(filename, sizeof(filename), "%s%s.csv", name, password);
    loadContactCSV(filename);
    printf("\t\t\t \033[1;32mEnter the name whose number you want to edit : \033[0m\033[1;33m");
    char Contactname[15];
    scanf(" %[^\n]", Contactname);
    printf("\033[0m");
    char number[15];
    printf("\t\t\t \033[1;32mEnter the new number : \033[0m\033[1;33m");
    scanf(" %[^\n]", number);
    printf("\033[0m");

    struct ContactNode *curr = Contacthead;
    while (curr != NULL)
    {
        if (strcmp(curr->name, Contactname) == 0)
        {
            strcpy(curr->number, number);
            break;
        }
        curr = curr->next;
    }
    unloadContactCSV(filename);
}
char *searchContact(char *name, char *password)
{
    char filename[50];
    snprintf(filename, sizeof(filename), "%s%s.csv", name, password);
    loadContactCSV(filename);
    char contactName[15];
    char contactNumber[15];
    printf("\t\t\t \033[1;32mEnter the name of the contact : \033[0m\033[1;33m");
    scanf(" %[^\n]", contactName);
    printf("\033[0m");
    struct ContactNode *curr = Contacthead;
    while (curr != NULL)
    {
        if (strcmp(curr->name, contactName) == 0)
        {
            strcpy(contactNumber, curr->number);
            freeContactList();
            printf("\t\t\t \033[1;34mThis is the contact number : %s\033[0m\n", contactNumber);
            return contactNumber;
        }
        curr = curr->next;
    }
    freeContactList();
    printf("\t\t\t \033[1;31mNo account found\033[0m\n", contactNumber);
    return "-1";
}
void printContactList(char *name, char *password)
{
    char filename[50];
    snprintf(filename, sizeof(filename), "%s%s.csv", name, password);
    loadContactCSV(filename);
    struct ContactNode *current = Contacthead;
    while (current != NULL)
    {
        printf("\t\t\t \033[1;32mName: %s \t Phone-number: %s\033[0m\n", current->name, current->number);
        current = current->next;
    }
}
void login(char *name, char *password)
{
    printf("\t\t\t \033[1;31m------------------------------------------\033[0m\n");
    printf("\t\t\t \033[1;31;43mWELCOME %s!\033[0m\n", name);

    while (1)
    {
        int choice;
        printf("\t\t\t \033[1;31m------------------------------------------\033[0m\n");
        printf("\t\t\t \033[1;34m1. CREATE NEW CONTACT\033[0m\n");
        printf("\t\t\t \033[1;34m2. DELETE A CONTACT\033[0m\n");
        printf("\t\t\t \033[1;34m3. EDIT NAME\033[0m\n");
        printf("\t\t\t \033[1;34m4. EDIT NUMBER\033[0m\n");
        printf("\t\t\t \033[1;34m5. SEARCH A CONTACT\033[0m\n");
        printf("\t\t\t \033[1;34m6. DISPLAY CONTACT\033[0m\n");
        printf("\t\t\t \033[1;34m7. EXIT\033[0m\n");
        printf("\t\t\t \033[1;34mENTER YOUR CHOICE: \033[0m\033[1;33m");
        scanf("%d", &choice);
        printf("\033[0m\n");
        switch (choice)
        {
        case 1:
            newcontact(name, password);
            printf("\t\t\t \033[1;34mNew contact has been added\033[0m\n");
            break;
        case 2:
            deletecontact(name, password);
            break;
        case 3:
            editName(name, password);
            break;
        case 4:
            editNumber(name, password);
            break;
        case 5:
            searchContact(name, password);
            break;
        case 6:
            printContactList(name, password);
            break;
        case 7:
            return;
        default:
            printf("\t\t\t \033[1;32mWRONG CHOICE\033[0m\n\n");
        }
    }
}
int main()
{
    printf("\t\t\t \033[1;31m------------------------------------------\t\t\t \033[0m\n");
    printf("\t\t\t\033[1;31m|\033[0m \033[1;31;43mWELCOME TO OUR PHONE DIRECTORY\033[0m \033[1;31m|\033[0m\n");
    printf("\t\t\t \033[1;31m------------------------------------------\033[0m\n");
    while (1)
    {
        int choice;
        printf("\t\t\t \033[1;31m------------------------------------------\033[0m\n");
        printf("\t\t\t \033[1;34m1. NEW USER RESIGTRATION\033[0m\n");
        printf("\t\t\t \033[1;34m2. LOGIN/SIGNIN\033[0m\n");
        printf("\t\t\t \033[1;34m3. DELETION ACCOUNT\033[0m\n");
        printf("\t\t\t \033[1;34m4. FORGOT PASSWORD\033[0m\n");
        printf("\t\t\t \033[1;34m5. EXIT\033[0m\n");
        printf("\t\t\t \033[1;34mENTER YOUR CHOICE: \033[0m\033[1;33m");

        scanf("%d", &choice);
        printf("\033[0m\n");
        switch (choice)
        {
        case 1:
            newAccount();
            printf("\t\t\t \033[1;32mYour account has been successfully created!\033[0m\n\n");
            break;
        case 2:
            loggingIn();
            printf("\t\t\t \033[1;31mYour account is not found, please create a new account to login\033[0m\n");
            break;
        case 3:
            deleteAccount();
            break;
        case 4:
            forgetPassword();
            break;
        case 5:
            exit(0);
        default:
            printf("\t\t\t \033[1;32mWRONG CHOICE\033[0m\n\n");
        }
    }
}