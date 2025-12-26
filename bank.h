#ifndef BANK_H
#define BANK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


typedef struct {
    int year, month, day;
} Date;


typedef struct {
    char account_number[50];
    char name[100];
    char mobile[20];
    char email[100];
    double balance;
    Date date_opened;
    int status;
} Account;


extern Account *accounts;
extern int account_count;


// Function Prototypes


//System
int login(void);
void menu(void);
void load_accounts(void);
void save_accounts(void);
void quit_system(void);
int validate_number(char *str);
int validate_email( char *email);
int validate_account_number(char *str);

//Account Management
void add_account(void);
void modify_account(void);
void delete_account(void);
void change_status(void);
Date getCurrentDate(void);
void delete_multiple_accounts(void);

//Financial
void withdraw(void);
void deposit(void);
void transfer(void);
void print_report(void);
double get_daily_withdrawal_sum(const char *accNum);
void get_today(Date *d);

//Operations
void query_search(void);
void advanced_search(void);
void print_sorted_accounts(void);

//sort functions
void sortByName(void);
void sortByDate(void);
void sortByBalance(void);
void sortByStatus(void);

#endif
