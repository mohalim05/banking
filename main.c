#include <stdio.h>
#include <stdlib.h>
#include "bank.h"

int main()
{
    int choice;
    while(1)
    {
        printf("\n=========================================\n");
        printf("        WELCOME TO BANK SYSTEM           ");
        printf("\n=========================================\n");
        printf("[1] LOGIN\n");
        printf("[2] QUIT\n");
        printf("=========================================\n");
        printf("Enter your choice: ");

        if(scanf("%d", &choice) != 1) {
            while(getchar() != '\n');
            choice = 0;
        } else {
            getchar();
        }

        switch(choice)
        {
            case 1:
                if(login())
                {
                    load_accounts();
                    menu();
                }
                break;
            case 2:
                exit(0);
                break;
            default:
                printf("Invalid choice! Please select 1 or 2.\n");
        }
    }
    return 0;
}
