#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account {
    int accNo;
    char name[50];
    float balance;
};

void createAccount() {
    struct Account a;
    FILE *fp = fopen("accounts.txt", "a");

    printf("\nEnter Account Number: ");
    scanf("%d", &a.accNo);
    printf("Enter Name: ");
    scanf(" %[^\n]", a.name);
    printf("Enter Initial Balance: ");
    scanf("%f", &a.balance);

    fwrite(&a, sizeof(a), 1, fp);
    fclose(fp);
    printf("✅ Account created successfully!\n");
}

void viewAccounts() {
    struct Account a;
    FILE *fp = fopen("accounts.txt", "r");

    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }

    printf("\nAll Accounts:\n");
    while (fread(&a, sizeof(a), 1, fp)) {
        printf("\nAcc No: %d\nName: %s\nBalance: %.2f\n", a.accNo, a.name, a.balance);
    }
    fclose(fp);
}

void depositMoney() {
    struct Account a;
    int accNo, found = 0;
    float amount;
    FILE *fp = fopen("accounts.txt", "r+");

    printf("Enter Account Number: ");
    scanf("%d", &accNo);
    while (fread(&a, sizeof(a), 1, fp)) {
        if (a.accNo == accNo) {
            found = 1;
            printf("Enter amount to deposit: ");
            scanf("%f", &amount);
            a.balance += amount;
            fseek(fp, -sizeof(a), SEEK_CUR);
            fwrite(&a, sizeof(a), 1, fp);
            printf("✅ Amount deposited!\n");
            break;
        }
    }
    if (!found) printf("❌ Account not found.\n");
    fclose(fp);
}

void withdrawMoney() {
    struct Account a;
    int accNo, found = 0;
    float amount;
    FILE *fp = fopen("accounts.txt", "r+");

    printf("Enter Account Number: ");
    scanf("%d", &accNo);
    while (fread(&a, sizeof(a), 1, fp)) {
        if (a.accNo == accNo) {
            found = 1;
            printf("Enter amount to withdraw: ");
            scanf("%f", &amount);
            if (amount <= a.balance) {
                a.balance -= amount;
                fseek(fp, -sizeof(a), SEEK_CUR);
                fwrite(&a, sizeof(a), 1, fp);
                printf("✅ Amount withdrawn!\n");
            } else {
                printf("❌ Insufficient balance.\n");
            }
            break;
        }
    }
    if (!found) printf("❌ Account not found.\n");
    fclose(fp);
}

void searchAccount() {
    struct Account a;
    int accNo, found = 0;
    FILE *fp = fopen("accounts.txt", "r");

    printf("Enter Account Number to search: ");
    scanf("%d", &accNo);
    while (fread(&a, sizeof(a), 1, fp)) {
        if (a.accNo == accNo) {
            found = 1;
            printf("\nAccount Found:\n");
            printf("Acc No: %d\nName: %s\nBalance: %.2f\n", a.accNo, a.name, a.balance);
            break;
        }
    }
    if (!found) printf("❌ Account not found.\n");
    fclose(fp);
}

int main() {
    int choice;

    do {
        printf("\n==== BANKING SYSTEM ====\n");
        printf("1. Create Account\n");
        printf("2. View All Accounts\n");
        printf("3. Deposit Money\n");
        printf("4. Withdraw Money\n");
        printf("5. Search Account\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createAccount(); break;
            case 2: viewAccounts(); break;
            case 3: depositMoney(); break;
            case 4: withdrawMoney(); break;
            case 5: searchAccount(); break;
            case 0: printf("Exiting...\n"); break;
            default: printf("❌ Invalid choice.\n");
        }
    } while (choice != 0);

    return 0;
}
