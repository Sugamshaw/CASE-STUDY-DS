#include <stdio.h>

int main() {
    char name[100]; // Declare a character array to store the name

    printf("Enter your name: ");
    scanf("%99s", name); // Read the name as a string (up to 99 characters)

    printf("Hello, %s!\n", name); // Print the name

    return 0;
}
