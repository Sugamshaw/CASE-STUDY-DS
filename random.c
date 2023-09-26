/*
Text Formatting:

You can use escape codes to change text formatting in the terminal.
Here are a few common ANSI escape codes:

Reset formatting: \033[0m
Bold text: \033[1m
Underline text: \033[4m
Blinking text: \033[5m
Text color: \033[38;5;<color_code>m (replace <color_code> with the desired color code)


Text Color:

You can change the text color using ANSI escape codes. Different escape codes correspond to different colors. For example:

Red: \033[31m
Green: \033[32m
Blue: \033[34m

Background Color:

You can also change the background color of the text:

Red background: \033[41m
Green background: \033[42m
Blue background: \033[44m


Cursor Manipulation:

You can move the cursor to specific positions, clear the screen, and more using ANSI escape codes. For example:

Move cursor to row 10, column 20: \033[10;20H
Clear the screen: \033[2J


*/
#include <stdio.h>
#include <stdbool.h>
int main()
{
    int choice;

    printf("\t\t\t \033[1;31m------------------------------------------\t\t\t \033[0m\n");
    printf("\t\t\t\033[1;31m|\033[0m \033[1;31;43mWELCOME TO OUR CONTACT BOOK APPLICATIONS\033[0m \033[1;31m|\033[0m\n");
    printf("\t\t\t \033[1;31m------------------------------------------\033[0m\n");

    while (true)
    {

        printf("\t\t\t \033[1;31m1. LOGIN/SIGNIN\033[0m\n");
        printf("\t\t\t \033[1;32m2. NEW USER RESIGTRATION\033[0m\n");
        printf("\t\t\t \033[1;33m3. FORGOT PASSWORD\033[0m\n");
        printf("\t\t\t \033[1;34m4. CHANGING PASSWORD\033[0m\n");
        printf("\t\t\t \033[1;35m5. DELETION ACCOUNT\033[0m\n");
        printf("\t\t\t \033[1;36m6. EXIT\033[0m\n");
        printf("\t\t\t \033[1;37mENTER YOUR CHOICE: \033[0m\033[1;32m\n");
        printf("\t\t\t \033[1;38mENTER YOUR CHOICE: \033[0m\033[1;32m\n");
        printf("\t\t\t \033[1;39mENTER YOUR CHOICE: \033[0m\033[1;32m\n");
        printf("\t\t\t \033[1;40mENTER YOUR CHOICE: \033[0m\033[1;32m\n");

        scanf("%d", &choice);
        printf("\033[0m\n");
        switch (choice)
        {
        case 1:
            int choice2;
            printf("Hi!!");
            printf("WELCOME TO YOUR CONTACT DIRECTORY ");
            printf("\t\t\t \033[1;31m1. INSERTING NEW CONTACT DETAIL\033[0m\n");
            printf("\t\t\t \033[1;31m2. DELETION OF CONTACT DETAIL\033[0m\n");
            printf("\t\t\t \033[1;31m3. CHANGING NAME \033[0m\n");
            printf("\t\t\t \033[1;31m4. CHANGING NUMBER\033[0m\n");
            printf("\t\t\t \033[1;31m5. MERGING OF NEW NUMBER\033[0m\n");
            printf("\t\t\t \033[1;31m6. SEARCHING A CONTACT\033[0m\n");
            printf("\t\t\t \033[1;31m7. EXIT\033[0m\n");
            printf("\t\t\t \033[1;31mENTER YOUR CHOICE: \033[0m");
            scanf("%d", &choice2);
            printf("\033[0m\n");
            switch (choice2)
            {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                return 0;
                break;

            default:
                break;
            }
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            //green
            printf("\t\t\t \033[1;32mEnter your name : \033[0m\033[1;33m");
            printf("\033[0m");
            //red
            printf("\t\t\t \033[1;31mNo contacts found.\033[0m");
            //blue
            printf("\t\t\t \033[1;34mYour account is not found\033[0m\n");
            break;
        case 5:
            break;
        case 6:
            return 0;
            break;
        default:
            printf("\t\t\t \033[1;32mWRONG CHOICE\033[0m \n\n");
        }
    }
    // Change text color to red and make it bold
    // printf("\033[1;31mBold Red Text\033[0m\n");
    // Change text color to red
    // printf("\033[31mRed Text\033[0m\n");
    // Red text on a yellow background
    // printf("\033[1;31;43mRed Text on Yellow Background\033[0m\n");

    // printf("\033[1;34;41m Blinking Text\033[0m\n");

    return 0;
}
