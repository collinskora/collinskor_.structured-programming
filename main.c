

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static double g_balance = 1000.00; /* starting balance */
static int g_pin = 1234;           /* stored PIN */

/* Function prototypes */
bool login(void);
void showMenu(void);
void handleChoice(void);
void checkBalance(void);
void deposit(double amount);
void withdraw(double amount);

/* Helper to safely read a line from stdin */
static bool readline(char *buf, size_t size) {
    if (!fgets(buf, (int)size, stdin)) return false;
    /* strip newline if present */
    buf[strcspn(buf, "\n")] = '\0';
    return true;
}

/* Helper to read a positive double amount from user,
   returns true and sets *out if successful, false on failure */
static bool readPositiveAmount(double *out) {
    char buf[64];
    if (!readline(buf, sizeof(buf))) return false;
    char *endptr = NULL;
    double val = strtod(buf, &endptr);
    /* basic validation: something parsed and no extra junk (allow trailing spaces) */
    while (*endptr == ' ' || *endptr == '\t') endptr++;
    if (buf[0] == '\0' || endptr[0] != '\0') {
        return false;
    }
    if (val <= 0.0) return false;
    *out = val;
    return true;
}

/* 1. Login / PIN Verification Function */
bool login(void) {
    const int max_attempts = 3;
    char buf[32];

    for (int attempt = 1; attempt <= max_attempts; ++attempt) {
        printf("Enter your 4-digit PIN: ");
        if (!readline(buf, sizeof(buf))) return false;
        int entered = atoi(buf);
        if (entered == g_pin) {
            printf("Login successful. Welcome!\n\n");
            return true;
        } else {
            int remaining = max_attempts - attempt;
            if (remaining > 0) {
                printf("Incorrect PIN. Attempts remaining: %d\n", remaining);
            } else {
                printf("Incorrect PIN. Maximum attempts exceeded. Access denied.\n");
            }
        }
    }
    return false;
}

/* 2. Show ATM Menu */
void showMenu(void) {
    puts("===== ATM Menu =====");
    puts("1) Balance Inquiry");
    puts("2) Deposit");
    puts("3) Withdraw");
    puts("4) Exit");
    puts("====================");
    printf("Choose an option (1-4): ");
}

/* 3. Handle User Choice - reads choice and calls functions */
void handleChoice(void) {
    char buf[32];
    while (true) {
        showMenu();
        if (!readline(buf, sizeof(buf))) {
            puts("\nInput error; exiting.");
            return;
        }
        int choice = atoi(buf);
        switch (choice) {
            case 1:
                checkBalance();
                break;
            case 2: {
                printf("Enter amount to deposit: ");
                double amt;
                if (!readPositiveAmount(&amt)) {
                    printf("Invalid amount. Please enter a positive number.\n\n");
                } else {
                    deposit(amt);
                }
                break;
            }
            case 3: {
                printf("Enter amount to withdraw: ");
                double amt;
                if (!readPositiveAmount(&amt)) {
                    printf("Invalid amount. Please enter a positive number.\n\n");
                } else {
                    withdraw(amt);
                }
                break;
            }
            case 4:
                printf("Thank you. Ending session.\n");
                return;
            default:
                printf("Invalid choice. Please enter a number between 1 and 4.\n\n");
        }
    }
}

/* 1) Balance Inquiry */
void checkBalance(void) {
    printf("Current balance: $%.2f\n\n", g_balance);
}

/* 3) Deposit */
void deposit(double amount) {
    /* Validation for positive amount is expected to be done before calling,
       but double-check here for safety. */
    if (amount <= 0.0) {
        printf("Deposit amount must be positive.\n\n");
        return;
    }
    g_balance += amount;
    printf("Deposited: $%.2f\n", amount);
    printf("New balance: $%.2f\n\n", g_balance);
}

/* 3) Withdraw */
void withdraw(double amount) {
    if (amount <= 0.0) {
        printf("Withdrawal amount must be positive.\n\n");
        return;
    }
    if (amount > g_balance) {
        printf("Insufficient funds. Available balance: $%.2f\n\n", g_balance);
        return;
    }
    g_balance -= amount;
    printf("Please take your cash: $%.2f\n", amount);
    printf("New balance: $%.2f\n\n", g_balance);
}

/* Main: perform login, then allow repeated transactions until Exit */
int main(void) {
    printf("Welcome to the ATM Simulator\n\n");
    if (!login()) {
        return 0;
    }
    handleChoice();
    return 0;
}
