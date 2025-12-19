#include "bank.h"
Account *accounts=NULL;
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

void quit_system(void)
{
    printf("\nSaving...\n");

    save_accounts();

    if (accounts != NULL)
    {
        free(accounts);
        accounts = NULL;
    }


    account_count = 0;

    printf("logged out\n");
    exit(0);
}
//2-Load function
void load_accounts(void)
{
    FILE *loadptr=fopen("accounts.txt","r");
    if(loadptr==NULL)
    {
        printf("error: accounts.txt not found!\n");
        return ;
    }

    char*token;
    char information[300];
    account_count=0;
    while(fgets(information,300,loadptr)!=NULL)
    {
        if(strcmp(information,"\n")==0){
            continue;
        }
        Account *temp =(Account*)realloc(accounts,(account_count+1)*sizeof(Account));
        if(temp==NULL)
        {
            printf("Memory Allocation failed\n");
            exit(1);
        }
        accounts=temp;

        //account number
        token=strtok(information,",");
        if(token!=NULL)strcpy(accounts[account_count].account_number,token);
        else continue;

        //name
        token=strtok(NULL,",");
        if(token!=NULL)strcpy(accounts[account_count].name,token);

        //Email
        token=strtok(NULL,",");
        if(token!=NULL)strcpy(accounts[account_count].email,token);

        //Balance
        token=strtok(NULL,",");
        if(token!=NULL)accounts[account_count].balance=atof(token);

        //Mobile
        token=strtok(NULL,",");
        if(token!=NULL)strcpy(accounts[account_count].mobile,token);

        //month
        token=strtok(NULL,"-");
        if(token!=NULL)accounts[account_count].date_opened.month=atoi(token);

        //year
        token=strtok(NULL,",");
        if(token!=NULL)accounts[account_count].date_opened.year=atoi(token);

        //status
        token=strtok(NULL,",");
        if(token!=NULL && strstr(token,"inactive")!=NULL)
        {
            accounts[account_count].status=0;
        }
        else
        {
            accounts[account_count].status=1;
        }
        account_count++;
    }

    fclose(loadptr);
    printf("System loaded %d accounts successfully\n",account_count);
}

//save accounts

#include <stdio.h>
#include <stdlib.h>
void save_accounts(void)
{
    FILE *saveptr = fopen("accounts.txt", "w");
    if (saveptr == NULL)
    {
        printf("error: cannot open accounts.txt for writing!\n");
        return;
    }

    for (int i = 0; i < account_count; i++)
    {
        fprintf(saveptr,
                "%s,%s,%s,%.2f,%s,%02d-%d, %s\n",
                accounts[i].account_number,
                accounts[i].name,
                accounts[i].email,
                accounts[i].balance,
                accounts[i].mobile,
                accounts[i].date_opened.month,
                accounts[i].date_opened.year,
                accounts[i].status ? "active" : "inactive");
    }

    fclose(saveptr);
    printf("Accounts saved successfully\n");
}
