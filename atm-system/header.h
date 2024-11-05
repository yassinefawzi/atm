#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct Date
{
    int month, day, year;
};

// all fields for each record of an account
struct Record
{
    int id;
    int userId;
    char name[100];
    char country[100];
    int phone;
    char accountType[10];
    int accountNbr;
    double amount;
    struct Date deposit;
    struct Date withdraw;
};

struct User
{
    int id;
    char name[50];
    char password[50];
};

// authentication functions
void loginMenu(char a[50], char pass[50]);
void registerMenu(char a[50], char pass[50]);
const char *getPassword(struct User u);
void account_register(char name[50], char password[50]);
void account_update(int type[2], char new[50], char name[50]);
void check_account(char name[50], int id);
void Transaction(struct User u, int trans[2], float amount);
void deleteAccount(struct User u, int id);
void transfer(struct User u, int id, char new[50]);

// system function
void createNewAcc(struct User u);
void mainMenu(struct User u);
void checkAllAccounts(struct User u);
int getAccountFromFile(FILE *ptr, char name[50], struct Record *r);
int get_Id(struct User u);
void success(struct User u);