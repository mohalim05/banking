#include "bank.h"

void modify_account(void){
    printf("\n=============================\n");
    printf("      MODIFY ACCOUNT DATA        ");
    printf("\n=============================\n");
    char id[50];
    int index=-1;

printf("Enter account number: ");
scanf("%49s",id);
int i;
for(i=0;i<account_count;i++){

    if(strcmp(accounts[i].account_number,id)==0){
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
if(flag=='y'||flag=='Y'){
    printf("enter new name: ");
    getchar();
    fgets(temp_name,100,stdin);
    temp_name[strcspn(temp_name,"\n")]='\0';
}


printf("\ncurrent email: %s\n",temp_email);
printf("do you want to change email? (y/n): ");
scanf(" %c",&flag);

if(flag=='y'||flag=='Y'){
    printf("enter new email: ");
    getchar();
    fgets(temp_email,100,stdin);
    temp_email[strcspn(temp_email,"\n")]='\0';
}

printf("\ncurrent mobile number: %s\n",temp_mobile);
printf("do you want to change mobile number? (y/n): ");
scanf(" %c",&flag);

if(flag=='y'||flag=='Y'){
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
if(flag=='y'||flag=='Y'){
strcpy(accounts[index].name,temp_name);
strcpy(accounts[index].mobile,temp_mobile);
strcpy(accounts[index].email,temp_email);
save_accounts();
printf("\nData saved successfully\n");
}
else{
    printf("\nCancelled operation\n");}

printf("=================================\n");
}


void change_status(void){
    printf("\n=============================\n");
    printf("      MODIFY ACCOUNT STATUS        ");
    printf("\n=============================\n");
int temp_status;
 int ind=-1;
char id[50];
printf("Enter account number: ");
scanf("%49s",id);
int i;
for(i=0;i<account_count;i++){

    if(strcmp(accounts[i].account_number,id)==0){
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
if(accounts[ind].status==1){
    strcpy(status,"active");
}else {
strcpy(status,"inactive");

}
printf("\n=============================\n");
printf("      CURRENT STATUS  [%s]      ",status);
printf("\n=============================\n");
printf("choose new status:\n[1]Activate\n[2]Deactivate\n");
int choice;

printf("Enter your choice: ");
scanf(" %d",&choice);
while(choice!=1&&choice!=2){

printf("\nPlease Enter [1] or [2]: ");
scanf(" %d",&choice);

}
if(accounts[ind].status==1&&choice==1||accounts[ind].status==0&&choice==2){
    printf("The account is already in this status!\n");
    return;
}
if(choice==1){
    temp_status=1;

}
else if(choice==2){
    temp_status=0;
}
printf("Are you sure you want to save changes (y/n)?: ");
char flag;
scanf(" %c",&flag);
if(flag=='y'||flag=='Y'){
   accounts[ind].status=temp_status;
   save_accounts();
    printf("\nStatus updated: %s --> %s \n",status,(choice==1)?"active":"inactive");

}
else{
    printf("\nCancelled operation\n");
}
printf("=================================\n");
}
