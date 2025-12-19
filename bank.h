// Header Guard: Prevents the file from being included multiple times
#ifndef BANK_H
#define BANK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h> // for date operations

// ==========================================
// 1. Structure Definitions
// ==========================================

// Date Structure
typedef struct {
    int year, month, day;
} Date;

// Bank Account Structure
typedef struct {
    char account_number[50]; //stored as a string to handle leading zeros
    char name[100]; //client name
    char mobile[20]; //mobile number
    char email[100]; //client email
    double balance; //Account balance
    Date date_opened; //Date the account was opened
    int status; // Active=1 , Inactive=0
} Account;

// ==========================================
// 2. Global Variables
// ==========================================

// 'extern' allows these variables to be accessed by all files
extern Account *accounts; // Pointer for Dynamic Array to store all accounts
extern int account_count; // Counter for the current number of accounts

// ==========================================
// 3. Function Prototypes
// ==========================================

// Module 1: System Core
int login(void);
void load_accounts(void);
void save_accounts(void);
void quit_system(void);
int validate_number(char *str); // Helper to check if string contains digits only
int validate_email( char *email);
int validate_account_number(char *str);

// Module 2: Account Management
void add_account(void);
void modify_account(void);
void delete_account(void);
void change_status(void);
void delete_multiple_accounts(void); // Bonus Task

// Module 3: Financial Operations
void withdraw(void);
void deposit(void);
void transfer(void);
void print_report(void);
double get_daily_withdrawal_sum(const char *accNum);

// Module 4: Operations & UI
void query_search(void);
void advanced_search(void);
void print_sorted_accounts(void);

// Internal Sorting Helpers
void sortByName(void);
void SortByDate(void);
void SortByBalance(void);
void sortByStatus(void);

#endif // End of Header Guard
