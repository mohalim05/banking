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

///////////////////////////////////////////
void delete_account(){
printf("\n=============================\n");
printf("      DELETE ACCOUNT             ");
printf("\n=============================\n");
 int dt_ind=-1;
char id[50];
printf("Enter account number to delete: ");
scanf("%49s",id);
int i;
for(i=0;i<account_count;i++){

    if(strcmp(accounts[i].account_number,id)==0){
        dt_ind=i;
        break;
    }

}
if(dt_ind==-1)
{
    printf("Error: Account number %s not found\n",id);
    return;

}
if(accounts[dt_ind].balance>0.0){
    printf("error : Account has balance :%.2f $\n",accounts[dt_ind].balance);
    printf("only Accounts with 0.00 balance can be deleted\n");
return;
}
printf("Account found : [name: %s]",accounts[dt_ind].name);
printf("\nAre you sure you want to delete this account? (y/n): ");
char inputchoice;
scanf(" %c",&inputchoice);
if(inputchoice=='y'||inputchoice=='Y'){

    for(i=dt_ind;i<account_count-1;i++){
        accounts[i]=accounts[i+1];
    }
    account_count--;
   Account *tempdata=realloc(accounts,account_count*sizeof(Account));
   if(tempdata!=NULL||account_count==0){
    accounts=tempdata;

    }
    save_accounts();
    printf("\nAccount deleted successfully\n");
}
else{
   printf("\nCancelled operation\n");
}
printf("=================================\n");
}




void advanced_search(void){
printf("\n=============================\n");
printf("      ADVANCED SEARCH             ");
printf("\n=============================\n");
printf("Enter keyword to search: ");
char keyword[50];
getchar();
fgets(keyword,50,stdin);
keyword[strcspn(keyword,"\n")]='\0';
int search_count=0;
char *month[]={"","January","February","March"
,"April","May","June"
,"July","August","September"
,"October","November","December"};
int i;
printf("\n=============================\n");
printf("\n       Search results        \n");
printf("\n=============================\n");
for(i=0;i<account_count;i++){
    if(strstr(accounts[i].name,keyword)!=NULL){
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
if(search_count==0){
    printf("no matches found for key word %s\n",keyword);
}
printf("=================================\n");
}

