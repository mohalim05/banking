#include "bank.h"
int account_count=0;
//1- login function
int login(void)
{
    FILE *userptr=fopen("users.txt","r");
    if(userptr==NULL)
    {
        printf("error: users.txt not found!\n");
        return 0;
    }

    char username[40];
    char password[40];
    char fileUSer[40];
    char filePass[40];

    int found=0;
    printf("username: ");
    fgets(username,sizeof(username),stdin);
    username[strcspn(username,"\n")]='\0';
    printf("password: ");
    fgets(password,sizeof(password),stdin);
    password[strcspn(password,"\n")]='\0';
    //read file line by line and search
    while(fscanf(userptr,"%s %s",fileUSer,filePass)!=EOF)
    {
        //compare inputs with file data
        if(strcmp(username,fileUSer)==0&&strcmp(password,filePass)==0)
        {
            found=1;
            break;
        }

    }
    fclose(userptr);
    if(found)
    {
        printf("\nLogin Successful welcome %s\n",username);
        return 1;
    }
    else
    {
        printf("\nInvalid username or password\n");
        return 0;
    }
}
//end of login function

//2-Load function

