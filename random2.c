#include <stdio.h>

int main() {
    char name[100]; // Assuming a maximum length for the name
    char password[100]; // Assuming a maximum length for the password

    printf("Enter your name: ");
    scanf(" %[^\n]", name); // Note the space before %[^\n]

    printf("Enter your password: ");
    scanf(" %[^\n]", password); // Note the space before %[^\n]

    printf("Name: %s\n", name);
    printf("Password: %s\n", password);

    return 0;
}
