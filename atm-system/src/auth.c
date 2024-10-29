#include <termios.h>
#include "header.h"

char *USERS = "./data/users.txt";

void loginMenu(char a[50], char pass[50])
{
    struct termios oflags, nflags;

    system("clear");
    printf("\n\n\n\t\t\t\t   Bank Management System\n\t\t\t\t\t User Login:");
    scanf("%s", a);

    // disabling echo
    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0)
    {
        perror("tcsetattr");
        exit(-1);
    }
    printf("\n\n\n\n\n\t\t\t\tEnter the password to login:");
    scanf("%s", pass);

    // restore terminal
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
    {
        perror("tcsetattr");
        exit(-1);
    }
};

const char *getPassword(struct User u)
{
    FILE *fp;
    struct User userChecker;

    if ((fp = fopen("./data/users.txt", "r")) == NULL)
    {
        printf("Error! opening file\n");
        exit(-1);
    }
    while (fscanf(fp, "%*d %s %s", userChecker.name, userChecker.password) != EOF)
    {

        if (strcmp(userChecker.name, u.name) == 0)
        {
            fclose(fp);
            char *buff = userChecker.password;
            return buff;
        }
    }

    fclose(fp);
    return "no user found";
}

int get_Id(struct User u) {
    FILE *fd = fopen("./data/users.txt", "r");
    int found = 0;
    int id = 0;
    char name[50];
    while (fscanf(fd, "%d %s %*s", &id, name) != EOF) {
        if (strcmp(name, u.name) == 0) {
            fclose(fd);
            return id;
        }
    }
    fclose(fd);
    printf("Error in User Id not found.\n");
    exit(-1);
}

void account_register(char name[50], char password[50]) {
    FILE *fp;
    struct User userChecker;
    if ((fp = fopen("./data/users.txt", "a+")) == NULL)
    {
        printf("Error! opening file\n");
        exit(-1);
    }
    system("clear");
    printf("\n\n\n\t\t\t\t   Bank Management System\n\t\t\t\t\t Enter Your User Login:");
    scanf("%s", name);
    while (fscanf(fp, "%d %s %*s", &userChecker.id, userChecker.name) != EOF)
    {
        if (strcmp(userChecker.name, name) == 0)
        {
            printf("user: %s is Already taken taken Please select another One\n", name);
            fclose(fp);
            exit(-1);
        }
    }
    printf("\n\n\n\n\n\t\t\t\t Enter Your Login password:");
    scanf("%s", password);
    fprintf(fp, "%d %s %s\n", userChecker.id+1, name, password);
    if (fclose(fp) != 0) {
        perror("Error closing the file");
    }
    printf("User %s registered successfully!\n", name);
    return ;
}

void account_update(int type[2], char new[50], char name[50]) {
    char date[20];
    float balance;
    char line[256];
    int found;
    FILE *fd = fopen("./data/records.txt", "r");
    if (fd == NULL) {
        perror("Error opening file");
        exit(-1);
    }
    FILE *tempFile = fopen("./data/temp_records.txt", "w");
    if (tempFile == NULL) {
        perror("Error opening temporary file");
        fclose(fd);
        exit(-1);
    }
    struct Record r;
    while (fgets(line, sizeof(line), fd) != NULL) {
        sscanf(line, "%d %d %s %d %s %s %d %f %s", &r.id, &r.userId, r.name, &r.accountNbr, date, r.country, &r.phone, &balance, r.accountType);
        if (r.accountNbr == type[0] && found == 0) {
            if (strcmp(r.name, name) != 0) {
                printf("You don't have access to this account\n");
                fclose(fd);
                fclose(tempFile);
                if (remove("./data/temp_records.txt") != 0) {
                    perror("Error deleting the temporary file");
                }
                exit(-1);
            } else if (type[1] == 1) {
                fprintf(tempFile, "%d %d %s %d %s %s %s %lf %s\n", r.id, r.userId, r.name, r.accountNbr, date, r.country, new, balance, r.accountType);
            } else {
                fprintf(tempFile, "%d %d %s %d %s %s %d %lf %s\n", r.id, r.userId, r.name, r.accountNbr, date, new, r.phone, balance, r.accountType);
            }
            found = 1;
        } else {
            fputs(line, tempFile);
        }
    }
    fclose(fd);
    fclose(tempFile);
    if (remove("./data/records.txt") != 0) {
        perror("Error deleting the original file");
        exit(-1);
    }
    if (rename("./data/temp_records.txt", "./data/records.txt") != 0) {
        perror("Error renaming the temporary file");
        exit(-1);
    }
    if (found) {
        printf("Account information updated successfully.\n");
    } else {
        printf("Account number not found.\n");
    }
}

void Transaction(struct User u, int trans[2], float amount) {
    struct Record r;
    float balance;
    char date[20];
    char line[256];
    int found = 0;
    float value;

    FILE *fd = fopen("./data/records.txt", "r");
    if (fd == NULL) {
        perror("Error opening file");
        exit(-1);
    }
    FILE *tempFile = fopen("./data/temp_records.txt", "w");
    if (tempFile == NULL) {
        perror("Error opening temporary file");
        fclose(fd);
        exit(-1);
    }
    while (fgets(line, sizeof(line), fd) != NULL) {
        sscanf(line, "%d %d %s %d %s %s %d %f %s", &r.id, &r.userId, r.name, &r.accountNbr, date, r.country, &r.phone, &balance, r.accountType);
        if (r.accountNbr == trans[1] && found == 0) {
            if (strcmp(r.name, u.name) != 0) {
                printf("You don't have access to this account\n");
                fclose(fd);
                fclose(tempFile);
                if (remove("./data/temp_records.txt") != 0) {
                    perror("Error deleting the temporary file");
                }
                exit(-1);
        return;
            } else if (trans[0] == 1) {
                value = balance - amount;
                if (value < 0) {
                    fputs(line, tempFile);
                } else {
                    fprintf(tempFile, "%d %d %s %d %s %s %d %.2f %s\n", r.id, r.userId, r.name, r.accountNbr, date, r.country, r.phone, value, r.accountType);
                }
            } else if (trans[0] == 2) {
                value = balance + amount;
                fprintf(tempFile, "%d %d %s %d %s %s %d %.2f %s\n", r.id, r.userId, r.name, r.accountNbr, date, r.country, r.phone, value, r.accountType);
            }
            found = 1;
        } else {
            fputs(line, tempFile);
        }
    }
    fclose(fd);
    fclose(tempFile);
    if (remove("./data/records.txt") != 0) {
        perror("Error deleting the original file");
        exit(-1);
    }
    if (rename("./data/temp_records.txt", "./data/records.txt") != 0) {
        perror("Error renaming the temporary file");
        exit(-1);
    }
    if (found) {
        printf("Account information updated successfully.\n");
    } else {
        printf("Account number not found.\n");
    }
}

void check_account(char name[50], int id) {
    int intrest;
    float value;
    struct Record r;
    char date[20];
    float balance;
    char line[256];
    int found = 0;
    FILE *fd = fopen("./data/records.txt", "r");
    while (fgets(line, sizeof(line), fd) != NULL) {
        sscanf(line, "%*d %*d %s %d %s %s %d %f %s", r.name, &r.accountNbr, date, r.country, &r.phone, &balance, r.accountType);
        if (id == r.accountNbr) {
            if (strcmp(r.name, name) != 0) {
                printf("Error You don't have access to this account.\n");
                exit(-1);
            } else {
                printf("Account Number: %d\n", r.accountNbr);
                printf("Deposit Date: %s\n", date);
                printf("Country: %s\n", r.country);
                printf("Phone Number: %d\n", r.phone);
                printf("Ammount Deposited: %.2f\n", balance);
                printf("Type Of Acciount: %s\n", r.accountType);
                found = 1;
            }
        }
    }
    fclose(fd);
    if (found == 1) {
        if (strcmp(r.accountType, "savings")) {
            value = (0.07 / 12 ) * balance;
            printf("You will get %.2f as interest on day %.2s of every month\n", value, date);
        } else if (strcmp(r.accountType, "fixed01")) {
            value = (0.04 / 12 ) * balance;
            printf("You will get %.2f as interest on day %.2s of every month\n", value, date);
        } else if (strcmp(r.accountType, "fixed02")) {
            value = (0.05 / 12 ) * balance;
            printf("You will get %.2f as interest on day %.2s of every month\n", value, date);
        } else if (strcmp(r.accountType, "fixed03")) {
            value = (0.87 / 12 ) * balance;
            printf("You will get %.2f as interest on day %.2s of every month\n", value, date);
        } else if (strcmp(r.accountType, "current")) {
            printf("You will not get interests because the account is of type current\n");
        } else {
            printf("Error Account type not found.");
            exit(-1);;
        }
    } else {
        printf("Account number not found\n");
        exit(-1);
    }
}

void    deleteAccount(struct User u, int id) {
    struct Record r;
    char line[256];
    char date[100];
    float balance;
    int found = 0;

    FILE *fd = fopen("./data/records.txt", "r");
    if (fd == NULL) {
        perror("Error opening file");
        exit(-1);
    }
    FILE *tempFile = fopen("./data/temp_records.txt", "w");
    if (tempFile == NULL) {
        perror("Error opening temporary file");
        fclose(fd);
        exit(-1);
    }
    while (fgets(line, sizeof(line), fd) != NULL) {
        sscanf(line, "%d %d %s %d %s %s %d %f %s", &r.id, &r.userId, r.name, &r.accountNbr, date, r.country, &r.phone, &balance, r.accountType);
        if (r.accountNbr == id && found == 0) {
            if (strcmp(r.name, u.name)) {
                printf("You don't have access to this account\n");
                fclose(fd);
                fclose(tempFile);
                if (remove("./data/temp_records.txt") != 0) {
                    perror("Error deleting the temporary file");
                }
                exit(-1);
            } else {
                printf("Account Number: %d\n", r.accountNbr);
                printf("Deposit Date: %s\n", date);
                printf("Country: %s\n", r.country);
                printf("Phone Number: %d\n", r.phone);
                printf("Ammount Deposited: %.2f\n", balance);
                printf("Type Of Acciount: %s\n", r.accountType);
                found = 1;
            }
        } else {
            fputs(line, tempFile);
        }
    }
    fclose(fd);
    fclose(tempFile);
    if (remove("./data/records.txt") != 0) {
        perror("Error deleting the original file");
        exit(-1);
    }
    if (rename("./data/temp_records.txt", "./data/records.txt") != 0) {
        perror("Error renaming the temporary file");
        exit(-1);
    }
    if (found) {
        printf("Account information updated successfully.\n");
    } else {
        printf("Account number not found.\n");
    }
}

void transfer(struct User u, int id, char new[50]) {
    struct Record r;
    char line[256];
    char date[100];
    float balance;
    int found = 0;

    FILE *fd = fopen("./data/records.txt", "r");
    if (fd == NULL) {
        perror("Error opening file");
        exit(-1);
    }
    FILE *tempFile = fopen("./data/temp_records.txt", "w");
    if (tempFile == NULL) {
        perror("Error opening temporary file");
        fclose(fd);
        exit(-1);
    }
    while (fgets(line, sizeof(line), fd) != NULL) {
        sscanf(line, "%d %d %s %d %s %s %d %f %s", &r.id, &r.userId, r.name, &r.accountNbr, date, r.country, &r.phone, &balance, r.accountType);
        if (r.accountNbr == id && found == 0) {
            if (strcmp(r.name, u.name) != 0) {
                printf("You don't have access to this account\n");
                fclose(fd);
                fclose(tempFile);
                if (remove("./data/temp_records.txt") != 0) {
                    perror("Error deleting the temporary file");
                }
                exit(-1);
            } else {
                fprintf(tempFile, "%d %d %s %d %s %s %d %.2f %s\n", r.id, r.userId, new, r.accountNbr, date, r.country, r.phone, balance, r.accountType);
                found = 1;
            }
        } else {
            fputs(line, tempFile);
        }
    }
    fclose(fd);
    fclose(tempFile);
    if (remove("./data/records.txt") != 0) {
        perror("Error deleting the original file");
        exit(-1);
    }
    if (rename("./data/temp_records.txt", "./data/records.txt") != 0) {
        perror("Error renaming the temporary file");
        exit(-1);
    }
    if (found) {
        printf("Account information updated Transfered.\n");
    } else {
        printf("Account number not found.\n");
    }
}