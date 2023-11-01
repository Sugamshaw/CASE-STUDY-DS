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

int load_name(void);

typedef struct Node
{
    char name[NAMELENGTH + 1];
    char number[NUMBERLENGTH + 1];
    struct Node *next;
} Node;
Node *nameTable[N];

char *removeSpaces(char *input)
{
    char *output = (char *)malloc(100);
    int j = 0;

    for (int i = 0; i < strlen(input); i++)
    {
        if (input[i] != ' ')
        {
            output[j++] = input[i];
        }
    }
    output[j] = '\0';
    return output;
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
        }while ((current_index) % limit != 0);
    }
    end = clock();
    cpu_time_used = (double)(end - start) / CLOCKS_PER_MILLISEC;
    fprintf(fp, "Time taken: %lf milliseconds", cpu_time_used);
    fclose(fp);
    return 0;
}

int main()
{
    load_name();
    printf("Enter the name\n");
    char *name = (char *)malloc(NAMELENGTH);
    scanf("%s", name);
    printf("\n");
    nameSearch(name);
}
