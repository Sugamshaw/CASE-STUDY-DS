#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct AccountNode* head = NULL;
// Define a structure for the linked list node
struct AccountNode {
    char name[100];
    char password[100];
    struct AccountNode* next;
};
void freeAccountList(struct AccountNode* head){
    while (head != NULL) {
        struct AccountNode* temp = head;
        head = head->next;
        free(temp);
    }
}
// Function to create a new node
struct AccountNode* createNode(const char* name, const char* password) {
    struct AccountNode* newNode = (struct AccountNode*)malloc(sizeof(struct AccountNode));
    if (newNode == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }
    strncpy(newNode->name, name, sizeof(newNode->name));
    strncpy(newNode->password, password, sizeof(newNode->password));
    newNode->next = NULL;
    return newNode;
}

// Function to append a node to the linked list
void appendNode(struct AccountNode** head, const char* name, const char* password) {
    struct AccountNode* newNode = createNode(name, password);
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct AccountNode* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Function to print the linked list
void printList(struct AccountNode* head) {
    struct AccountNode* current = head;
    while (current != NULL) {
        printf("Name: %s, Password: %s\n", current->name, current->password);
        current = current->next;
    }
}

int loadAccountsCSV() {
    FILE* file = fopen("accounts.csv", "r"); // Open the CSV file for reading

    if (file == NULL) {
        perror("Error opening the file");
        return 1;
    }

    char line[256]; // Buffer to store a line from the file

     // Initialize the linked list

    // Read and process each line of the CSV file
    while (fgets(line, sizeof(line), file) != NULL) {
        char name[100];
        char password[100];
        if (sscanf(line, " %[^,],%s", name, password) == 2) {
            appendNode(&head, name, password);
        }
    }

    fclose(file); 
    

    return 0;
}
int main(){
    loadAccountsCSV();
    printList(head);
}