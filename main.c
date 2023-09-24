#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct AccountNode *Accounthead = NULL;
struct ContactNode *Contacthead = NULL;

struct AccountNode
{
    char name[100];
    char password[100];
    struct AccountNode *next;
};
struct ContactNode
{
    char name[100];
    char number[100];
    struct ContactNode *next;
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

struct AccountNode *createAccountNode(const char *name, const char *password)
{
    struct AccountNode *newNode = (struct AccountNode *)malloc(sizeof(struct AccountNode));
    if (newNode == NULL)
    {
        perror("Memory allocation failed");
        exit(1);
    }
    strncpy(newNode->name, name, sizeof(newNode->name));
    strncpy(newNode->password, password, sizeof(newNode->password));
    newNode->next = NULL;
    return newNode;
}
struct ContactNode *createContactNode(const char *name, const char *number)
{
    struct ContactNode *newNode = (struct ContactNode *)malloc(sizeof(struct ContactNode));
    if (newNode == NULL)
    {
        perror("Memory allocation failed");
        exit(1);
    }
    strncpy(newNode->name, name, sizeof(newNode->name));
    strncpy(newNode->number, number, sizeof(newNode->number));
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
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
    }
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
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
    }
}

void printAccountList()
{
    struct AccountNode *current = Accounthead;
    while (current != NULL)
    {
        printf("Name: %s, Password: %s\n", current->name, current->password);
        current = current->next;
    }
}
void printContactList()
{
    struct ContactNode *current = Contacthead;
    while (current != NULL)
    {
        printf("Name: %s, phone-number: %s\n", current->name, current->number);
        current = current->next;
    }
}

void loadAccountsCSV()
{
    freeAccountList();
    FILE *file = fopen("accounts.csv", "r");
    if (file == NULL)
    {
        perror("Error opening the file");
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
void loadContactCSV(char *filename)
{
    freeContactList();
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening the file");
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

void unloadAccountCSV()
{
    FILE *fptr = fopen("accounts.csv", "w");
    if (fptr == NULL)
    {
        perror("Error creating the file");
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
void unloadContactCSV(char *filename)
{
    FILE *fptr = fopen(filename, "w");
    if (fptr == NULL)
    {
        perror("Error creating the file");
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
void login(char *name, char *password)
{
    int len1 = strlen(name);
    int len2 = strlen(password);
    char *filename = (char *)malloc(len1 + len2 + 1);
    strcpy(filename, name);
    strcat(filename, password);
    printf("you are logged in!!\n");
}
void newAccount()
{
    char name[15];
    char password[15];
    printf("enter your name\n");
    scanf(" %[^\n]", name);
    printf("enter your password");
    scanf("%s", password);
    loadAccountsCSV();
    appendAccountNode(&Accounthead, name, password);
    unloadAccountCSV(Accounthead);
    int len1 = strlen(name);
    int len2 = strlen(password);
    char *filename = (char *)malloc(len1 + len2 + 5);
    strcpy(filename, name);
    strcat(filename, password);
    strcat(filename, ".csv");
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        perror("Failed to create file");
        return; // Return an error code
    }
    fclose(file);
}
void loggingin()
{
    char name[15];
    char password[15];
    printf("enter you name\n");
    scanf("%s", name);
    printf("enter your password\n");
    scanf("%s", password);
    loadAccountsCSV();
    struct AccountNode *curr = Accounthead;
    while (curr->next != NULL)
    {
        if (strcmp(curr->name, name) && strcmp(curr->password, password))
        {
            login(curr->name, curr->password);
            exit(0);
        }
        else
        {
            curr = curr->next;
        }
    }
}
void deleteAccount()
{
    char name[15];
    char password[15];
    printf("enter you name\n");
    scanf("%s", name);
    printf("enter your password\n");
    scanf("%s", password);
    int len1 = strlen(name);
    int len2 = strlen(password);
    loadAccountsCSV();

    if (Accounthead == NULL)
    {
        return;
    }
    struct AccountNode *curr = Accounthead;
    if (strcmp(curr->name, name) && strcmp(curr->password, password))
    {
        Accounthead = Accounthead->next;
        free(curr);
        char *filename = (char *)malloc(len1 + len2 + 5);
        strcpy(filename, name);
        strcat(filename, password);
        strcat(filename, ".csv");
        remove(filename);
        unloadAccountCSV();
        return;
    }
    while (curr->next != NULL)
    {
        if (strcmp(curr->next->password, password) && strcmp(curr->next->name, name))
        {
            struct AccountNode *temp = curr->next->next;
            free(curr->next);
            curr->next = temp;
            break;
        }
        curr = curr->next;
    }
    char *filename = (char *)malloc(len1 + len2 + 5);
    strcpy(filename, name);
    strcat(filename, password);
    strcat(filename, ".csv");
    remove(filename);
    unloadAccountCSV();
}
void forgetPassword()
{
    int adminPass;
    printf("Enter admin password : ");
    scanf("%d", &adminPass);
    if (adminPass != 123)
    {
        printf("Wrong admin password!!");
        return;
    }
    char name[15];
    printf("Enter your name : ");
    scanf(" %[^\n]", name);
    loadAccountsCSV();
}
void changingPassword()
{
}
int main()
{
    while (1)
    {
        int choice;
        printf("Enter a number (1-6): \n");
        printf("1:new account\n");
        printf("2:login\n");
        printf("3:delete account\n");
        printf("4:Forget password\n");
        printf("5:Changing password\n");
        printf("6:exit\n");
        printf("Enter yourr choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            newAccount();
            printf("your account has been successfully created!");
            break;
        case 2:
            loggingin();
            printf("your account is not found, please create a new account to login\n");
            break;
        case 3:
            deleteAccount();
            break;
        case 4:
            forgetPassword();
            break;
        case 5:
            changingPassword();
            break;
        case 6:
            exit(0);
        default:
            printf("enter a number between 1 to 4");
        }
    }
}