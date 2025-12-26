#include "bank.h"

void modify_account(void)
{
    printf("\n=============================\n");
    printf("      MODIFY ACCOUNT DATA        ");
    printf("\n=============================\n");
    char id[50];
    int index=-1;

    printf("Enter account number: ");
    scanf("%49s",id);
    int i;
    for(i=0; i<account_count; i++)
    {

        if(strcmp(accounts[i].account_number,id)==0)
        {
            index=i;
            break;
        }

    }
    if(index==-1)
    {
        printf("Account number %s not found\n",id);
        return;

    }
    char temp_name[100],temp_mobile[20],temp_email[100];
    strcpy(temp_name,accounts[index].name);
    strcpy(temp_mobile,accounts[index].mobile);
    strcpy(temp_email,accounts[index].email);
    printf("current name: %s\n",temp_name);
    printf("do you want to change name? (y/n): ");
    char flag;
    scanf(" %c",&flag);
    if(flag=='y'||flag=='Y')
    {
        printf("enter new name: ");
        getchar();
        fgets(temp_name,100,stdin);
        temp_name[strcspn(temp_name,"\n")]='\0';
    }


    printf("\ncurrent email: %s\n",temp_email);
    printf("do you want to change email? (y/n): ");
    scanf(" %c",&flag);

    if(flag=='y'||flag=='Y')
    {
        printf("enter new email: ");
        getchar();
        fgets(temp_email,100,stdin);
        temp_email[strcspn(temp_email,"\n")]='\0';
    }

    printf("\ncurrent mobile number: %s\n",temp_mobile);
    printf("do you want to change mobile number? (y/n): ");
    scanf(" %c",&flag);

    if(flag=='y'||flag=='Y')
    {
        printf("enter new mobile number: ");
        getchar();
        fgets(temp_mobile,20,stdin);
        temp_mobile[strcspn(temp_mobile,"\n")]='\0';
    }


    printf("\n======updated information=======\n");
    printf("name: %s --> %s\n",accounts[index].name,temp_name);
    printf("email: %s --> %s\n",accounts[index].email,temp_email);
    printf("mobile: %s --> %s\n",accounts[index].mobile,temp_mobile);
    printf("=================================\n");

    printf("Are you sure you want to save changes (y/n)?: ");
    scanf(" %c",&flag);
    if(flag=='y'||flag=='Y')
    {
        strcpy(accounts[index].name,temp_name);
        strcpy(accounts[index].mobile,temp_mobile);
        strcpy(accounts[index].email,temp_email);
        save_accounts();
        printf("\nData saved successfully\n");
    }
    else
    {
        printf("\nCancelled operation\n");
    }

    printf("=================================\n");
}


void change_status(void)
{
    printf("\n=============================\n");
    printf("      MODIFY ACCOUNT STATUS        ");
    printf("\n=============================\n");
    int temp_status;
    int ind=-1;
    char id[50];
    printf("Enter account number: ");
    scanf("%49s",id);
    int i;
    for(i=0; i<account_count; i++)
    {

        if(strcmp(accounts[i].account_number,id)==0)
        {
            ind=i;
            break;
        }

    }
    if(ind==-1)
    {
        printf("Error: Account number %s not found\n",id);
        return;

    }
    char status[10];
    if(accounts[ind].status==1)
    {
        strcpy(status,"active");
    }
    else
    {
        strcpy(status,"inactive");

    }
    printf("\n=============================\n");
    printf("      CURRENT STATUS  [%s]      ",status);
    printf("\n=============================\n");
    printf("choose new status:\n[1]Activate\n[2]Deactivate\n");
    int choice;

    printf("Enter your choice: ");
    while(1) {
        if(scanf("%d",&choice)!=1) {

            while(getchar()!='\n');
            printf("Invalid input! Please Enter [1] or [2]: ");
        } else {
            getchar();
            if(choice==1||choice==2) {
                break;
            } else{
                printf("Please Enter [1] or [2]: ");
            }
        }
    }
    if(accounts[ind].status==1&&choice==1||accounts[ind].status==0&&choice==2)
    {
        printf("The account is already in this status!\n");
        return;
    }
    if(choice==1)
    {
        temp_status=1;

    }
    else if(choice==2)
    {
        temp_status=0;
    }
    printf("Are you sure you want to save changes (y/n)?: ");
    char flag;
    scanf(" %c",&flag);
    if(flag=='y'||flag=='Y')
    {
        accounts[ind].status=temp_status;
        save_accounts();
        printf("\nStatus updated: %s --> %s \n",status,(choice==1)?"active":"inactive");

    }
    else
    {
        printf("\nCancelled operation\n");
    }
    printf("=================================\n");
}

///////////////////////////////////////////
void delete_account()
{
    printf("\n=============================\n");
    printf("      DELETE ACCOUNT             ");
    printf("\n=============================\n");
    int dt_ind=-1;
    char id[50];
    printf("Enter account number to delete: ");
    scanf("%49s",id);
    int i;
    for(i=0; i<account_count; i++)
    {

        if(strcmp(accounts[i].account_number,id)==0)
        {
            dt_ind=i;
            break;
        }

    }
    if(dt_ind==-1)
    {
        printf("Error: Account number %s not found\n",id);
        return;

    }
    if(accounts[dt_ind].balance>0.0)
    {
        printf("error : Account has balance :%.2f $\n",accounts[dt_ind].balance);
        printf("only Accounts with 0.00 balance can be deleted\n");
        return;
    }
    printf("Account found : [name: %s]",accounts[dt_ind].name);
    printf("\nAre you sure you want to delete this account? (y/n): ");
    char inputchoice;
    scanf(" %c",&inputchoice);
    if(inputchoice=='y'||inputchoice=='Y')
    {

        for(i=dt_ind; i<account_count-1; i++)
        {
            accounts[i]=accounts[i+1];
        }
        account_count--;
        Account *tempdata=realloc(accounts,account_count*sizeof(Account));
        if(tempdata!=NULL||account_count==0)
        {
            accounts=tempdata;

        }
        save_accounts();
        printf("\nAccount deleted successfully\n");
    }
    else
    {
        printf("\nCancelled operation\n");
    }
    printf("=================================\n");
}




void advanced_search(void)
{
    printf("\n=============================\n");
    printf("      ADVANCED SEARCH             ");
    printf("\n=============================\n");
    printf("Enter keyword to search: ");
    char keyword[50];
    fgets(keyword,50,stdin);
    keyword[strcspn(keyword,"\n")]='\0';
    int search_count=0;
    char *month[]= {"","January","February","March"
                    ,"April","May","June"
                    ,"July","August","September"
                    ,"October","November","December"
                   };
    int i;
    printf("\n=============================\n");
    printf("\n       Search results        \n");
    printf("\n=============================\n");
    for(i=0; i<account_count; i++)
    {
        if(strstr(accounts[i].name,keyword)!=NULL)
        {
            search_count++;
            printf("Account number: %s\n",accounts[i].account_number);
            printf("Name: %s\n",accounts[i].name);
            printf("E-mail: %s\n",accounts[i].email);
            printf("Balance: %.2f $\n",accounts[i].balance);
            printf("Mobile: %s\n",accounts[i].mobile);
            printf("Date opened: %s %d\n",month[accounts[i].date_opened.month],accounts[i].date_opened.year);
            printf("Status: %s\n",(accounts[i].status==1)?"active":"inactive");
            printf("\n");
        }
    }
    if(search_count==0)
    {
        printf("no matches found for key word %s\n",keyword);
    }
    printf("=================================\n");
}


Date getCurrentDate(void)
{
    Date d;
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    d.year = tm_info->tm_year + 1900;
    d.month = tm_info->tm_mon + 1;
    d.day = tm_info->tm_mday;
    return d;
}

void query_search(void)
{
    char *month[] = {"", "January", "February", "March", "April", "May", "June",
                     "July", "August", "September", "October", "November", "December"
                    };
    char Acnum[100];
    int i, flag = 1;

    printf("\n=============================\n");
    printf("        QUERY ACCOUNT        ");
    printf("\n=============================\n");
    printf("Please enter an account number: ");

    while (1)
    {
        if (!fgets(Acnum, sizeof(Acnum), stdin)) return;
        Acnum[strcspn(Acnum, "\n")] = '\0';
        if (validate_account_number(Acnum)) break;
        printf("\033[31m[ERROR] Account number must be exactly 10 digits!\033[0m\n");
        printf("Try again: ");
    }

    printf("\nChecking account number...\n");

    for (i = 0; i < account_count; i++)
    {
        if (strcmp(Acnum, accounts[i].account_number) == 0)
        {
            flag = 0;
            printf("\n=============================\n");
            printf("      Bank account found!    ");
            printf("\n=============================\n");
            printf("Account Number: %s\n", accounts[i].account_number);
            printf("Name: %s\n", accounts[i].name);
            printf("E-mail: %s\n", accounts[i].email);
            printf("Balance: %.2f $\n", accounts[i].balance);
            printf("Mobile: %s\n", accounts[i].mobile);
            printf("Date opened: %s %d\n", month[accounts[i].date_opened.month], accounts[i].date_opened.year);
            printf("Status: %s\n", (accounts[i].status == 1) ? "Active" : "Inactive");
            printf("\n");
            break;
        }
    }

    if (flag)
    {
        printf("\033[31mThis account number does not exist in our database\033[0m\n");
    }
    printf("=================================\n");
}

void add_account(void)
{
    printf("\n=============================\n");
    printf("       ADD NEW ACCOUNT       ");
    printf("\n=============================\n");

    printf("Please enter account name: ");
    char acname[100];
    fgets(acname, sizeof(acname), stdin);
    acname[strcspn(acname, "\n")] = '\0';

    char acnum[100];
    while (1)
    {
        printf("Please enter account number: ");
        if (!fgets(acnum, sizeof(acnum), stdin)) return;
        acnum[strcspn(acnum, "\n")] = '\0';

        if (!validate_account_number(acnum))
        {
            printf("\033[31m[ERROR] Account number must be 10 digits. Try again.\033[0m\n");
            continue;
        }

        int exists = 0;
        for (int i = 0; i < account_count; i++)
        {
            if (strcmp(accounts[i].account_number, acnum) == 0)
            {
                exists = 1;
                break;
            }
        }

        if (exists)
        {
            printf("\033[31m[ERROR] This number already exists. Try another.\033[0m\n");
            continue;
        }
        break;
    }

    char mail[100];
    while (1)
    {
        printf("Please enter email: ");
        if (!fgets(mail, sizeof(mail), stdin)) return;
        mail[strcspn(mail, "\n")] = '\0';
        if (validate_email(mail)) break;
        printf("\033[31mEmail entered is incorrect try again.\033[0m\n");
    }

    char phonenum[100];
    while (1)
    {
        printf("Please enter mobile number: ");
        if (!fgets(phonenum, sizeof(phonenum), stdin)) return;
        phonenum[strcspn(phonenum, "\n")] = '\0';
        if (validate_number(phonenum)) break;
        printf("\033[31mPhone number is digits only try again.\033[0m\n");
    }

    ++account_count;
    Account *tempdata = realloc(accounts, account_count * sizeof(Account));
    if (!tempdata)
    {
        printf("Memory allocation failed\n");
        --account_count;
        return;
    }
    accounts = tempdata;

    int index = account_count - 1;
    strcpy(accounts[index].name, acname);
    strcpy(accounts[index].account_number, acnum);
    strcpy(accounts[index].email, mail);
    strcpy(accounts[index].mobile, phonenum);
    accounts[index].date_opened = getCurrentDate();
    accounts[index].status = 1;
    accounts[index].balance = 0.0;

    printf("\nAre you sure you want to save? (yes/no): ");
    char save[100];
    fgets(save, 99, stdin);
    save[strcspn(save, "\n")] = '\0';

    if (save[0] == 'y' || save[0] == 'Y')
    {
        save_accounts();
        printf("\n\033[32mData saved successfully.\033[0m\n");
    }
    else
    {
        printf("\n\033[31mOperation cancelled. Changes were not saved.\033[0m\n");
        account_count--;
        Account *tempdata = realloc(accounts, account_count * sizeof(Account));
        if (tempdata != NULL || account_count == 0)
        {
            accounts = tempdata;
        }
    }
    printf("=================================\n");
}


void sortByName(void) {
    int i, j;
    Account temp;
    for (i = 0; i < account_count - 1; i++) {
        for (j = 0; j < account_count - i - 1; j++) {
            if (strcmp(accounts[j].name, accounts[j + 1].name) > 0) {
                temp = accounts[j];
                accounts[j] = accounts[j + 1];
                accounts[j + 1] = temp;
            }
        }
    }
    printf("\nAccounts sorted by Name (A-Z).\n");
}

void sortByBalance(void) {
    int i, j;
    Account temp;
    for (i = 0; i < account_count - 1; i++) {
        for (j = 0; j < account_count - i - 1; j++) {
            if (accounts[j].balance < accounts[j + 1].balance) {
                temp = accounts[j];
                accounts[j] = accounts[j + 1];
                accounts[j + 1] = temp;
            }
        }
    }
    printf("\nAccounts sorted by Balance (Highest First).\n");
}

void sortByDate(void) {
    int i, j;
    Account temp;
    for (i = 0; i < account_count - 1; i++) {
        for (j = 0; j < account_count - i - 1; j++) {
            int swap_needed = 0;
            if (accounts[j].date_opened.year < accounts[j + 1].date_opened.year) {
                swap_needed = 1;
            } else if (accounts[j].date_opened.year == accounts[j + 1].date_opened.year) {
                if (accounts[j].date_opened.month < accounts[j + 1].date_opened.month) {
                    swap_needed = 1;
                }
            }
            if (swap_needed) {
                temp = accounts[j];
                accounts[j] = accounts[j + 1];
                accounts[j + 1] = temp;
            }
        }
    }
    printf("\nAccounts sorted by Date (Newest First).\n");
}

void sortByStatus(void) {
    int i, j;
    Account temp;
    for (i = 0; i < account_count - 1; i++) {
        for (j = 0; j < account_count - i - 1; j++) {
            if (accounts[j].status < accounts[j + 1].status) {
                temp = accounts[j];
                accounts[j] = accounts[j + 1];
                accounts[j + 1] = temp;
            }
        }
    }
    printf("Accounts sorted by status (Active first).\n");
}

void print_sorted_accounts(void) {
    if (account_count == 0) {
        printf("\nNo accounts available to sort or print.\n");
        return;
    }

    printf("\n=============================\n");
    printf("      PRINT SORTED DATA      ");
    printf("\n=============================\n");
    printf("Choose sort criteria:\n");
    printf("[1] Name\n");
    printf("[2] Balance\n");
    printf("[3] Date Opened\n");
    printf("[4] Status\n");
    printf("Enter your choice: ");

    int choice;
    scanf("%d", &choice);
    getchar();

    while (choice < 1 || choice > 4) {
        printf("Invalid choice. Please enter 1, 2, 3, or 4: ");
        scanf("%d", &choice);
        getchar();
    }

    if (choice == 1) {
        sortByName();
    } else if (choice == 2) {
        sortByBalance();
    } else if (choice == 3) {
        sortByDate();
    } else if (choice == 4) {
        sortByStatus();
    }

    printf("\n=============================\n");
    printf("     SORTED ACCOUNT LIST     ");
    printf("\n=============================");

    print();

    printf("=================================\n");
}


void delete_multiple_accounts(void){

printf("3la 7sb\n");
}
