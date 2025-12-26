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
    while(fscanf(userptr,"%s %s",fileUSer,filePass)!=EOF)
    {
        if(strcmp(username,fileUSer)==0&&strcmp(password,filePass)==0)
        {
            found=1;
            break;
        }

    }
    fclose(userptr);
    if(found)
    {
        printf("\nLogin Successfully welcome %s\n",username);
        return 1;
    }
    else
    {
        printf("\nInvalid username or password\n");
        return 0;
    }
}

void menu(void) {
    void (*options[])(void) = {
        NULL,
        add_account,
        delete_account,
        modify_account,
        query_search,
        advanced_search,
        change_status,
        withdraw,
        deposit,
        transfer,
        print_report,
        print_sorted_accounts,
        quit_system,
        delete_multiple_accounts
    };

    int choice;
    char go_back;

    while (1) {
        printf("\n=========================================\n");
        printf("       BANK MANAGEMENT SYSTEM\n");
        printf("=========================================\n");
        printf("[1] ADD New Account\n");
        printf("[2] DELETE Account\n");
        printf("[3] MODIFY Account\n");
        printf("[4] SEARCH (Query)\n");
        printf("[5] ADVANCED SEARCH\n");
        printf("[6] CHANGE STATUS\n");
        printf("[7] WITHDRAW\n");
        printf("[8] DEPOSIT\n");
        printf("[9] TRANSFER\n");
        printf("[10] REPORT\n");
        printf("[11] PRINT Sorted Accounts\n");
        printf("[12] QUIT\n");
        printf("[13] Delete Multiple\n");
        printf("=========================================\n");
        printf("Enter your choice: ");

        if (scanf("%d",&choice)!=1) {
            while(getchar()!='\n');
            choice=0;
        } else {
            getchar();
        }

        if (choice>=1&&choice<=13) {
            (*options[choice])();
            if (choice!=12) {
                printf("\n-----------------------------------------\n");
                printf("Do you want to go back to the menu or exit? (y: Menu / n: Exit): ");
                scanf(" %c",&go_back);
                while(getchar()!='\n');

                if (go_back=='n' || go_back=='N') {
                    quit_system();
                }
            }
        } else {
            printf("Invalid choice! Please select 1-13\n");
        }
    }
}
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
        accounts[account_count].date_opened.day = 1;

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

int validate_account_number(char *str)
{
    if(str==NULL||*str=='\0'||strlen(str)!=10)
        return 0;

    while(*str)
    {
        if(*str<'0'||*str>'9')
            return 0;
        str++;
    }

    return 1;
}
int validate_number(char *str)
{
    if(str==NULL||*str=='\0')
        return 0;

    while(*str)
    {
        if(*str<'0'||*str>'9')
            return 0;
        str++;
    }

    return 1;
}
int validate_email(char *email)
{
    char *at;
    char *dot;

    if(email==NULL||*email=='\0')
    {
        return 0;
    }

    if(strchr(email,' ')!=NULL)
    {
        return 0;
    }

    at=strchr(email,'@');
    if(at==NULL||at==email)
    {
        return 0;
    }

    dot=strchr(at+1,'.');
    if(dot==NULL||*(dot+1)=='\0')
    {
        return 0;
    }

    return 1;
}


void print(void) {
    char *month[] = {"", "January", "February", "March", "April", "May", "June",
                     "July", "August", "September", "October", "November", "December"};
    int i;

    if (account_count == 0) {
        printf("\nNo accounts to display.\n");
        return;
    }

    for (i = 0; i < account_count; i++) {
        printf("\n---------------------------------\n");
        printf("Account Number: %s\n", accounts[i].account_number);
        printf("Name: %s\n", accounts[i].name);
        printf("E-mail: %s\n", accounts[i].email);
        printf("Balance: %.2f $\n", accounts[i].balance);
        printf("Mobile: %s\n", accounts[i].mobile);
        printf("Date Opened: %s %d\n", month[accounts[i].date_opened.month], accounts[i].date_opened.year);
        printf("Status: %s\n", (accounts[i].status == 1) ? "Active" : "Inactive");
    }
    printf("---------------------------------\n");
}
