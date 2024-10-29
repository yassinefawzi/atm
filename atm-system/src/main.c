#include "header.h"
volatile int keepRunning = 1; // Define the global variable
int error = 0;


void mainMenu(struct User u)
{
    int option;
    int trans[2];
    int id[2];
    char new[50];
    float amount;
    system("clear");
    printf("\n\n\t\t======= ATM =======\n\n");
    printf("\n\t\t-->> Feel free to choose one of the options below <<--\n");
    printf("\n\t\t[1]- Create a new account\n");
    printf("\n\t\t[2]- Update account information\n");
    printf("\n\t\t[3]- Check accounts\n");
    printf("\n\t\t[4]- Check list of owned account\n");
    printf("\n\t\t[5]- Make Transaction\n");
    printf("\n\t\t[6]- Remove existing account\n");
    printf("\n\t\t[7]- Transfer ownership\n");
    printf("\n\t\t[8]- Exit\n");
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        u.id = get_Id(u);
        createNewAcc(u);
        success(u);
        break;
    case 2:
        system("clear");
        printf("\t\t\t===== Account Update =====\n");
        printf("Enter your account id\n");
        scanf("%d", &id[0]);
        printf("Select 1 for changing your phone number, 2 for changing your country\n");
        scanf("%d", &id[1]);
        if (id[1] != 1 && id[1] != 2) {
            printf("Error. Invalide choice\n");
            exit(-1);
        }
        if (id[1] == 1) {
            printf("please enter your new phone number\n");
        } else if (id[1] == 2) {
            printf("please enter your new country\n");
        }
        scanf("%s", new);
        account_update(id, new, u.name);
        success(u);
        break;
    case 3:
        system("clear");
        printf("\t\t\t===== Check Account For User: %s =====\n", u.name);
        printf("Enter id of the account you want to check\n");
        scanf("%d", &id[0]);
        check_account(u.name, id[0]);
        success(u);
        break;
    case 4:
        system("clear");
        checkAllAccounts(u);
        success(u);
    case 5:
        system("clear");
        printf("\t\t\t===== Transaction =====\n");
        printf("Enter 1 to Withdraw or 2 to Deposit.\n");
        scanf("%d", &trans[0]);
        if (trans[0] == 1) {
            printf("Enter id of the account you want to make the transaction from\n");
            scanf("%d", &trans[1]);
            printf("Enter the ammount you want to Withdraw.\n");
            scanf("%f", &amount);
            if (amount < 0) {
                printf("Enter a positive number next time.\n");
                exit(-1);
            }
        } else if (trans[0] == 2) {
            printf("Enter id of the account you want to make the transaction from\n");
            scanf("%d", &trans[1]);
            printf("Enter the ammount you want to Deposit.\n");
            scanf("%f", &amount);
            if (amount < 0) {
                printf("Enter a positive number next time.\n");
                exit(-1);
            }
        } else {
            printf("Error Please Enter 1 to Withdraw or 2 to Deposit next time.\n");
            exit(-1);
        }
        Transaction(u, trans, amount);
            success(u);
        break;
    case 6:
        system("clear");
        printf("\t\t\t===== Delete Account =====\n");
        printf("Enter ID of the account you want to delete.\n");
        scanf("%d", &id[0]);
        deleteAccount(u, id[0]);
        success(u);
        break;
    case 7:
        system("clear");
        printf("\t\t\t===== Transfer Account =====\n");
        printf("Enter ID of the account you want to transfer.\n");
        scanf("%d", &id[0]);
        printf("Enter name of the account you want to transfer to.\n");
        scanf("%s", new);
        transfer(u, id[0], new);
        success(u);
        break;
    case 8:
        exit(1);
    default:
        printf("Invalid operation!\n");
    }
};

void initMenu(struct User *u)
{
    int r = 0;
    int option;
    system("clear");
    printf("\n\n\t\t======= ATM =======\n");
    printf("\n\t\t-->> Feel free to login / register :\n");
    printf("\n\t\t[1]- login\n");
    printf("\n\t\t[2]- register\n");
    printf("\n\t\t[3]- exit\n");
    while (!r)
    {
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            loginMenu(u->name, u->password);
            if (strcmp(u->password, getPassword(*u)) == 0)
            {
                printf("\n\nPassword Match!");
            }
            else
            {
                printf("\nWrong password!! or User Name\n");
                exit(1);
            }
            r = 1;
            break;
        case 2:
            account_register(u->name, u->password);
            r = 1;
            break;
        case 3:
            exit(1);
            break;
        default:
            printf("Insert a valid operation!\n");
        }
    }
}


int main()
{
    struct User u;
    initMenu(&u);
    mainMenu(u);
    return 0;
}
