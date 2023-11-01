#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

#define NAMELENGTH 30
#define NUMBERLENGTH 15
#define N 26 * 26 * 26 * 26
#define DIGITS 4
#define NUMS 5
#define M 10 * 10 * 10 * 10 * 10
#define MAXCONTACTS 100

int load_name(void);
int load_number(void);

typedef struct Node
{
    char name[NAMELENGTH + 1];
    char number[NUMBERLENGTH + 1];
    struct Node *next;
} Node;
Node *nameTable[N];
Node *numberTable[M];
char *removeSpaces(char *input)
{
    int input_length = strlen(input);
    char *output = (char *)malloc(input_length + 1);
    int j = 0;

    for (int i = 0; i < input_length; i++)
    {
        if (input[i] != ' ')
        {
            output[j++] = input[i];
        }
    }
    output[j] = '\0';
    return output;
}
void loadTables()
{
    load_name();
    load_number();
}
void printnameTable()
{
    for (int i = 0; i < N; i++)
    {
        Node *curr = nameTable[i];
        while (curr != NULL)
        {
            printf("%s, %s\n", curr->name, curr->number);
            curr = curr->next;
        }
    }
}
void printnumberTable()
{
    for (int i = 0; i < M; i++)
    {
        Node *curr = numberTable[i];
        while (curr != NULL)
        {
            printf("%s, %s\n", curr->name, curr->number);
            curr = curr->next;
        }
    }
}
void freeTables()
{
    printnameTable();
    printnumberTable();
    FILE *fp = fopen("contacts.csv", "w");
    for (int i = 0; i < N; i++)
    {
        Node *curr = nameTable[i];
        while (curr != NULL)
        {
            fprintf(fp, "%s, %s\n", curr->name, curr->number);
            curr = curr->next;
        }
    }
    fclose(fp);
    for (int i = 0; i < M; i++)
    {
        Node *curr = numberTable[i];
        while (curr != NULL)
        {
            Node *temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    for (int i = 0; i < N; i++)
    {
        Node *curr = nameTable[i];
        while (curr != NULL)
        {
            Node *temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
}

int namehash(char *input)
{
    char *word = removeSpaces(input);
    int n = strlen(word);
    int h = 0;
    if (n == 1)
    {
        h = (toupper(word[0]) - 'A') * 26 * 26 * 26;
    }
    else if (n == 2)
    {
        h = (toupper(word[0]) - 'A') * 26 * 26 * 26 + (toupper(word[1]) - 'A') * 26 * 26;
    }
    else if (n == 3)
    {
        h = (toupper(word[0]) - 'A') * 26 * 26 * 26 + (toupper(word[1]) - 'A') * 26 * 26 + (toupper(word[2]) - 'A') * 26;
    }
    else if (n >= 4)
    {
        h = (toupper(word[0]) - 'A') * 26 * 26 * 26 + (toupper(word[1]) - 'A') * 26 * 26 + (toupper(word[2]) - 'A') * 26 + (toupper(word[3]) - 'A');
    }
    return h;
}
int numberhash(char *number)
{
    int n = strlen(number);
    int h = 0;
    if (n == 1)
    {
        h = (number[0] - '0') * 10 * 10 * 10 * 10;
    }
    else if (n == 2)
    {
        h = (number[0] - '0') * 10 * 10 * 10 * 10 + (number[1] - '0') * 10 * 10 * 10;
    }
    else if (n == 3)
    {
        h = (number[0] - '0') * 10 * 10 * 10 * 10 + (number[1] - '0') * 10 * 10 * 10 + (number[0] - '0') * 10 * 10;
    }
    else if (n == 4)
    {
        h = (number[0] - '0') * 10 * 10 * 10 * 10 + (number[1] - '0') * 10 * 10 * 10 + (number[0] - '0') * 10 * 10 + (number[0] - '0') * 10;
    }
    else if (n >= 5)
    {
        h = (number[0] - '0') * 10 * 10 * 10 * 10 + (number[1] - '0') * 10 * 10 * 10 + (number[0] - '0') * 10 * 10 + (number[0] - '0') * 10 + (number[0] - '0');
    }
    return h;
}
int load_name(void)
{
    for (int i = 0; i < N; i++)
    {
        nameTable[i] = NULL;
    }
    FILE *fp = fopen("contacts.csv", "r");
    if (fp == NULL)
    {
        printf("unable to create a file\n");
        return 1;
    }
    char line[NAMELENGTH + NUMBERLENGTH];
    char name_buffer[NAMELENGTH];
    char number_buffer[NUMBERLENGTH];
    while (fgets(line, sizeof(line), fp) != NULL)
    {

        sscanf(line, "%30[^,],%10s", name_buffer, number_buffer);
        Node *new = (Node *)malloc(sizeof(Node));
        strcpy(new->name, name_buffer);
        strcpy(new->number, number_buffer);
        new->next = NULL;
        int hashvalue = namehash(name_buffer);

        if (nameTable[hashvalue] == NULL)
        {
            nameTable[hashvalue] = new;
        }
        else
        {
            new->next = nameTable[hashvalue];
            nameTable[hashvalue] = new;
        }
        // i++;
    }
    fclose(fp);
    return 0;
}
int load_number(void)
{
    for (int i = 0; i < M; i++)
    {
        numberTable[i] = NULL;
    }
    FILE *fp = fopen("contacts.csv", "r");
    if (fp == NULL)
    {
        printf("unable to create a file\n");
        return 1;
    }
    char line[NAMELENGTH + NUMBERLENGTH];
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        char name_buffer[NAMELENGTH];
        char number_buffer[NUMBERLENGTH];
        sscanf(line, "%19[^,],%10s", name_buffer, number_buffer);
        Node *new = (Node *)malloc(sizeof(Node));
        strcpy(new->name, name_buffer);
        strcpy(new->number, number_buffer);
        new->next = NULL;
        int hashvalue = numberhash(number_buffer);
        if (numberTable[hashvalue] == NULL)
        {
            numberTable[hashvalue] = new;
        }
        else
        {
            new->next = numberTable[hashvalue];
            numberTable[hashvalue] = new;
        }
    }
    fclose(fp);
    return 0;
}
int nameSearch(char *name)
{
    clock_t start, end;
    double cpu_time_used;
    const double CLOCKS_PER_MILLISEC = CLOCKS_PER_SEC / 1000.0;
    int digits = strlen(name);
    FILE *fp = fopen("result.csv", "w");
    if (fp == NULL)
    {
        perror("ERROR!!!");
        return 1;
    }
    start = clock();
    int hashvalue = namehash(name);
    if (digits >= DIGITS)
    {
        Node *curr = nameTable[hashvalue];
        while (curr != NULL)
        {
            fprintf(fp, "%s, %s\n", curr->name, curr->number);
            curr = curr->next;
        }
    }
    else
    {
        int current_index = hashvalue;
        int limit = pow(26, DIGITS - digits);
        do
        {
            Node *curr = nameTable[current_index];
            while (curr != NULL)
            {
                fprintf(fp, "%s, %s\n", curr->name, curr->number);
                curr = curr->next;
            }
            current_index++;
        } while ((current_index) % limit != 0);
    }
    end = clock();
    cpu_time_used = (double)(end - start) / CLOCKS_PER_MILLISEC;
    fprintf(fp, "Time taken: %lf milliseconds", cpu_time_used);
    fclose(fp);
    return 0;
}
int numberSearch(char *number)
{
    clock_t start, end;
    double cpu_time_used;
    const double CLOCKS_PER_MILLISEC = CLOCKS_PER_SEC / 1000.0;
    int nums = strlen(number);
    FILE *fp = fopen("result.csv", "w");
    if (fp == NULL)
    {
        perror("ERROR!!!");
        return 1;
    }
    start = clock();
    int hashvalue = numberhash(number);
    if (nums >= NUMS)
    {
        Node *curr = numberTable[hashvalue];
        while (curr != NULL)
        {
            fprintf(fp, "%s, %s\n", curr->name, curr->number);
            curr = curr->next;
        }
    }
    else
    {
        int current_index = hashvalue;
        int limit = pow(10, NUMS - nums);
        do
        {
            Node *curr = numberTable[current_index];
            while (curr != NULL)
            {
                fprintf(fp, "%s, %s\n", curr->name, curr->number);
                curr = curr->next;
            }
            current_index++;
        } while ((current_index) % limit != 0);
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_MILLISEC;
    fprintf(fp, "Time taken: %lf milliseconds", cpu_time_used);
    fclose(fp);
    return 0;
}
void add_contact(void)
{
    char name[NAMELENGTH];
    char number[NUMBERLENGTH];
    printf("enter the name: ");
    scanf(" %19[^\n]", name);
    printf("\n");
    printf("enter the number: ");
    scanf(" %14[^\n]", number);
    printf("\n");
    Node *new = (Node *)malloc(sizeof(Node));
    strcpy(new->name, name);
    strcpy(new->number, number);
    new->next = NULL;
    int hashvalue = namehash(name);
    if (nameTable[hashvalue] == NULL)
    {
        nameTable[hashvalue] = new;
    }
    else
    {
        new->next = nameTable[hashvalue];
        nameTable[hashvalue] = new;
    }
    hashvalue = numberhash(number);
    new = (Node *)malloc(sizeof(Node));
    strcpy(new->name, name);
    strcpy(new->number, number);
    new->next = NULL;
    if (numberTable[hashvalue] == NULL)
    {
        numberTable[hashvalue] = new;
    }
    else
    {
        new->next = numberTable[hashvalue];
        numberTable[hashvalue] = new;
    }
}

void deleteByNumber(char *number)
{
    char name[NAMELENGTH];
    int hashvalue = numberSearch(number);
    Node *curr = numberTable[hashvalue];
    if (curr == NULL)
    {
        return;
    }
    else if (strcmp(curr->number, number) == 0)
    {
        strcpy(name, curr->name);
        numberTable[hashvalue] = curr->next;
        free(curr);
        curr = NULL;
    }
    while (curr != NULL)
    {
        if (strcmp(curr->next->number, number) == 0)
        {
            Node *temp = curr->next;
            strcpy(name, curr->next->name);
            curr->next = curr->next->next;
            free(temp);
            break;
        }
        curr = curr->next;
    }
    hashvalue = namehash(name);
    curr = nameTable[hashvalue];
    if (strcmp(curr->name, name) == 0)
    {
        nameTable[hashvalue] = curr->next;
        free(curr);
        curr = NULL;
    }
    while (curr != NULL)
    {
        if (strcmp(curr->next->name, name) == 0)
        {
            Node *temp = curr->next;
            curr->next = curr->next->next;
            free(temp);
            break;
        }
        curr = curr->next;
    }
    return;
}

// void deleteByName(char *name)
// {
//     char number[NUMBERLENGTH];
//     int nameHashValue = nameSearch(name);
//     Node *curr = nameTable[nameHashValue];
//     Node *prev = NULL;
//     if (curr == NULL)
//     {
//         // Node with the given name not found
//         return;
//     }
//     while (curr != NULL)
//     {
//         if (strcmp(curr->name, name) == 0)
//         {
//             // Node with the given name found, delete it
//             if (prev == NULL)
//             {
//                 nameTable[nameHashValue] = curr->next;
//             }
//             else
//             {
//                 prev->next = curr->next;
//             }
//             strcpy(number, curr->number);
//             free(curr);
//             break;
//         }
//         prev = curr;
//         curr = curr->next;
//     }
//     printf("%s\n", number);
//     int numberHashValue = numberSearch(number);
//     curr = numberTable[numberHashValue];
//     prev = NULL;
//     if (curr == NULL)
//     {
//         // Node with the given number not found
//         return;
//     }
//     while (curr != NULL)
//     {
//         if (strcmp(curr->number, number) == 0)
//         {
//             // Node with the given number found, delete it
//             if (prev == NULL)
//             {
//                 numberTable[numberHashValue] = curr->next;
//             }
//             else
//             {
//                 prev->next = curr->next;
//             }
//             free(curr);
//             break;
//         }
//         prev = curr;
//         curr = curr->next;
//     }
// }

void deleteByName(char *name)
{
    char number[NUMBERLENGTH];
    int hashvalue = nameSearch(name);
    Node *curr = nameTable[hashvalue];
    if (curr == NULL)
    {
        printf("Contact not found\n");
        return;
    }
    else if (strcmp(curr->name, name) == 0)
    {
        strcpy(number, curr->number);
        nameTable[hashvalue] = curr->next;
        free(curr);
        curr = NULL;
    }
    while (curr->next != NULL)
    {
        if (strcmp(curr->next->name, name) == 0)
        {
            Node *temp = curr->next;
            strcpy(number, curr->next->number);
            curr->next = curr->next->next;
            free(temp);
            break;
        }
        curr = curr->next;
    }
    hashvalue = numberhash(number);
    curr = numberTable[hashvalue];
    if (strcmp(curr->number, number) == 0)
    {
        numberTable[hashvalue] = curr->next;
        free(curr);
        curr = NULL;
    }
    while (curr->next != NULL)
    {
        if (strcmp(curr->next->number, number) == 0)
        {
            Node *temp = curr->next;
            curr->next = curr->next->next;
            free(temp);
            break;
        }
        curr = curr->next;
    }
    return;
}
void edit(void)
{
    system("cls");
    char name[NAMELENGTH];
    char number[NUMBERLENGTH];
    printf("enter the name and number of the contact you want to edit.\n");
    printf("name: ");
    scanf("%s", name);
    printf("\n");
    printf("number: ");
    scanf("%s", number);
    printf("\n");
    deleteByName(name);
    printf("give the new name and number of the contact\n");
    add_contact();
}

void delete(void)
{
    int choice;
    system("cls");
    printf("1.delete by name\n");
    printf("2.delete by number\n");
    printf("enter your choice: ");
    scanf("%d", &choice);
    printf("\n");
    if (choice == 1)
    {
        char *name = (char *)malloc(NAMELENGTH);
        printf("Enter the name: ");
        scanf("%s", name);
        printf("\n");
        deleteByName(name);
    }
    else if (choice == 2)
    {
        char *number = (char *)malloc(NUMBERLENGTH);
        printf("Enter the number: ");
        scanf("%s", number);
        printf("\n");
        deleteByNumber(number);
    }
    return;
}
void search(void)
{
    int choice;
    printf("1.search by number\n");
    printf("2.search by name\n");
    scanf("%d", &choice);
    if (choice == 1)
    {
        printf("Enter the number\n");
        char *number = (char *)malloc(NUMBERLENGTH);
        scanf("%s", number);
        printf("\n");
        numberSearch(number);
    }
    else if (choice == 2)
    {
        printf("Enter the name\n");
        char *name = (char *)malloc(NAMELENGTH);
        scanf("%s", name);
        printf("\n");
        nameSearch(name);
    }
    printf("Check result.csv\n");
    return;
}
int main(void)
{
    clock_t start, end;
    start = clock();
    loadTables();
    end = clock();
    double time = (double)(end - start) / (CLOCKS_PER_SEC / 1000.0);
    printf("time to load tables: %lf\n", time);
    while (1)
    {
        int choice;
        printf("enter a number.\n");
        printf("1.Add contact\n");
        printf("2.delete contact\n");
        printf("3.Edit contact\n");
        printf("4.search contact\n");
        printf("5.print name table\n");
        printf("6.print number table\n");
        printf("7.exit\n");
        printf("choice: ");
        scanf("%d", &choice);
        printf("\n");
        switch (choice)
        {
        case 1:
            add_contact();
            break;
        case 2:
            delete ();
            break;
        case 3:
            edit();
            break;
        case 4:
            search();
            break;
        case 5:
            printnameTable();
            break;
        case 6:
            printnumberTable();
            break;
        case 7:
            freeTables();
            return 0;
        default:
            printf("please enter a valid a choice\n");
            break;
        }
    }
}