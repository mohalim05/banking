#include "bank.h"


void get_today(Date *d){
    time_t t=time(NULL);
    struct tm *tm_info=localtime(&t);

    d->year =tm_info->tm_year + 1900;
    d->month=tm_info->tm_mon + 1;
    d->day  =tm_info->tm_mday;
}

double get_daily_withdrawal_sum(const char *accNum){
    FILE *f;
    char name_file[100];
    sprintf(name_file,"%s.txt",accNum);

    f=fopen(name_file,"r");

    if(f==NULL)
        return 0;

    char operation[50];
    double amount,sum=0;
    int y,m,d;

    Date today;
    get_today(&today);

    while(fscanf(f,"%[^,],%lf,%d-%d-%d\n",operation,&amount,&y,&m,&d)!= EOF){
        if(strcmp(operation,"withdraw")==0 &&y==today.year&&m==today.month&&d==today.day)
            sum=sum+amount;
    }
    fclose(f);
    return sum;
}

void withdraw(void){
    printf("\n=============================\n");
    printf("           WITHDRAW           ");
    printf("\n=============================\n");

    char acc_x[50];
    int i;

    printf("Enter Account Number: ");
    scanf("%49s",acc_x);
    getchar();

    for(i=0;i<account_count;i++){
        if(strcmp(acc_x,accounts[i].account_number)==0)
            break;
    }

    if(i==account_count){
        printf("Error: Account not found.\n");
        return;
    }

    if(accounts[i].status==0){
        printf("Warning: inactive account.\ntransaction cannot be completed\n");
        return;
    }

    double amount;
    double sum_today=get_daily_withdrawal_sum(accounts[i].account_number);
    while (1) {
        printf("<<<Enter amount>>>\n");
        if (scanf("%lf", &amount) != 1) {
            while (getchar() != '\n');
            printf("Error: Invalid input. Please enter numbers only.\n");
        } else {
            getchar();
            if (amount > 10000)
                printf("Note: Maximum withdrawal limit is 10,000$ per transaction.\n");
            else if (amount <= 0)
                printf("Error: Amount must be positive.\n");
            else
                break;
        }
    }
    if(sum_today+amount>50000){
        printf("Daily withdrawal limit reached (50,000$).\n");
        return;
    }

    if(accounts[i].balance<amount){
        printf("Insufficient balance.\n");
        return;
    }

    char save;
    do{
        printf("Do you want to save this transaction? (y/n): \n");
        scanf("%c",&save);
        getchar();
        if(save!='y'&&save!='Y'&&save!='n'&&save!='N')
            printf("Invalid input! Please enter 'y' or 'n'.\n");
    } while(save!='y'&&save!='Y'&&save!='n'&&save!='N');

    if(save=='y'||save=='Y'){
        accounts[i].balance-=amount;
        save_accounts();

        Date today;
        get_today(&today);

        FILE *f;
        char name_file[100];
        char *accNum=accounts[i].account_number;

        sprintf(name_file,"%s.txt",accNum);
        f=fopen(name_file,"a");
        if(f!=NULL){
            fprintf(f,"withdraw,%.2f,%04d-%02d-%02d\n",amount,today.year,today.month,today.day);
            fclose(f);
        }
        printf("\n");
        printf("\033[32m");
        printf("=========================================\n");
        printf("      TRANSACTION SUCCESSFUL!            \n");
        printf("=========================================\n");
        printf("\033[0m");
        printf("Amount       : %.2f $\n",amount);
        printf("New Balance  : %.2f $\n",accounts[i].balance);
        printf("=========================================\n");
    } else {
        printf("Transaction cancelled.\n");
    }
}

void deposit(void){
    printf("\n=============================\n");
    printf("            DEPOSIT           ");
    printf("\n=============================\n");

    char acc_x[50];
    int i;

    printf("Enter Account Number: ");
    scanf("%49s",acc_x);
    getchar();

    for(i=0;i<account_count;i++){
        if(strcmp(acc_x,accounts[i].account_number)==0)
            break;
    }

    if(i==account_count){
        printf("Error: Account not found.\n");
        return;
    }

    if(accounts[i].status==0){
        printf("Warning: inactive account.\ntransaction cannot be completed\n");
        return;
    }

    double amount=0;
    while (1) {
        printf("<<<Enter amount>>>\n");
        if (scanf("%lf", &amount) != 1) {
            while (getchar() != '\n');
            printf("Error: Invalid input. Please enter numbers only.\n");
        } else {
            getchar();
            if (amount > 10000)
                printf("Note: Maximum deposit limit is 10,000$ per transaction.\n");
            else if (amount <= 0)
                printf("Error: Amount must be positive.\n");
            else
                break;
        }
    }

    char save;
    do{
        printf("Do you want to save this transaction? (y/n): \n");
        scanf("%c",&save);
        getchar();
        if(save!='y'&&save!='Y'&&save!='n'&&save!='N')
            printf("Invalid input! Please enter 'y' or 'n'.\n");
    } while(save!='y'&&save!='Y'&&save!='n'&&save!='N');

    if(save=='y'||save=='Y'){
        accounts[i].balance+=amount;
        save_accounts();

        Date today;
        get_today(&today);

        FILE *f;
        char name_file[100];
        char *accNum=accounts[i].account_number;
        sprintf(name_file,"%s.txt",accNum);
        f=fopen(name_file,"a");
        if(f!=NULL){
            fprintf(f,"deposit,%.2f,%04d-%02d-%02d\n",amount,today.year,today.month,today.day);
            fclose(f);
        }
        printf("\n");
        printf("\033[32m");
        printf("=========================================\n");
        printf("      TRANSACTION SUCCESSFUL!            \n");
        printf("=========================================\n");
        printf("\033[0m");
        printf("Amount       : %.2f $\n",amount);
        printf("New Balance  : %.2f $\n",accounts[i].balance);
        printf("=========================================\n");
    } else {
        printf("Transaction cancelled.\n");
    }
}

void transfer(void){
    printf("\n=============================\n");
    printf("           TRANSFER           ");
    printf("\n=============================\n");

    char acc_x[50];
    int i;

    printf("Enter Sender Account Number: ");
    scanf("%49s",acc_x);
    getchar();

    for(i=0;i<account_count;i++){
        if(strcmp(acc_x,accounts[i].account_number)==0)
            break;
    }

    if(i==account_count){
        printf("Error: Sender Account not found.\n");
        return;
    }

    char acc_y[50];
    int j;

    printf("Enter Recipient Account Number: ");
    scanf("%s",acc_y);
    getchar();

    for(j=0;j<account_count;j++){
        if(strcmp(acc_y,accounts[j].account_number)==0)
            break;
    }

    if(j==account_count){
        printf("Error: Recipient Account not found.\n");
        return;
    }

    if(i == j) {
        printf("Error: Cannot transfer to the same account.\n");
        return;
    }

    if(accounts[i].status==0||accounts[j].status==0){
        printf("Warning: One of the accounts is inactive.\ntransaction cannot be completed\n");
        return;
    }

    double amount;
    printf("<<<Enter amount>>>\n");

    while (1) {
        if (scanf("%lf", &amount) != 1) {
            while (getchar() != '\n');
            printf("Invalid input. Please enter a valid amount: ");
        } else {
            getchar();
            if (amount <= 0) {
                printf("Error: Amount must be positive Enter again: ");
            } else {
                break;
            }
        }
    }
    if(accounts[i].balance<amount){
        printf("Your balance is insufficient to complete the transfer.\n");
        return;
    }

    char save;
    do{
        printf("Do you want to save this transaction? (y/n): \n");
        scanf("%c",&save);
        getchar();
        if(save!='y'&&save!='Y'&&save!='n'&&save!='N')
            printf("Invalid input! Please enter 'y' or 'n'.\n");
    } while(save!='y'&&save!='Y'&&save!='n'&&save!='N');

    if(save=='y'||save=='Y'){
        accounts[i].balance-=amount;
        accounts[j].balance+=amount;
        save_accounts();

        Date today;
        get_today(&today);

        FILE *f1;
        FILE *f2;

        char name_file1[100];
        char name_file2[100];
        char *accNum1=accounts[i].account_number;
        char *accNum2=accounts[j].account_number;

        sprintf(name_file1,"%s.txt",accNum1);
        sprintf(name_file2,"%s.txt",accNum2);

        f1=fopen(name_file1,"a");
        f2=fopen(name_file2,"a");

        if(f1!=NULL){
            fprintf(f1,"transfer_out,%.2f,%04d-%02d-%02d\n",amount,today.year,today.month,today.day);
            fclose(f1);
        }

        if(f2!=NULL){
            fprintf(f2,"transfer_in,%.2f,%04d-%02d-%02d\n",amount,today.year,today.month,today.day);
            fclose(f2);
        }

        printf("\033[32m");
        printf("Transaction completed successfully.\n");
        printf("\033[0m");
    } else {
        printf("Transaction cancelled.\n");
    }
}

void print_report(void){
    printf("\n=============================\n");
    printf("            REPORT            ");
    printf("\n=============================\n");

    char acc_x[50];
    int i;

    printf("Enter Account Number: ");
    scanf("%49s",acc_x);
    getchar();

    for(i=0;i<account_count;i++){
        if(strcmp(acc_x,accounts[i].account_number)==0)
            break;
    }

    if(i==account_count){
        printf("Error: Account not found.\n");
        return;
    }

    FILE *f;
    char name_file[100];
    char *accNum=accounts[i].account_number;
    sprintf(name_file,"%s.txt",accNum);
    f=fopen(name_file,"r");

    if(f==NULL){
        printf("No transactions found for this account.\n");
        return;
    }

    char lines[200][200];
    int count=0;

    while(count < 200 && fgets(lines[count],sizeof(lines[count]),f)){
        lines[count][strcspn(lines[count], "\n")] = '\0';
        count++;
    }
    fclose(f);

    printf("Last transactions:\n");
    if(count<=5){
        for(int k=0;k<count;k++)
            printf("%s\n",lines[k]);
    } else {
        for(int j=count-5;j<count;j++)
            printf("%s\n",lines[j]);
    }
}
