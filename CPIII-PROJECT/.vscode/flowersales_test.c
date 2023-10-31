#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flowersales.h"

// Struct to represent user information
struct User {
    char username[50];
    char password[50];
};

// Function to read users from a file
int readUsersFromFile(struct User users[], int *userCount) {
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) {
        return 0;
    }

    *userCount = 0;
    while (fscanf(file, "%s %s", users[*userCount].username, users[*userCount].password) == 2) {
        (*userCount)++;
    }

    fclose(file);
    return 1;
}

// Function to write users to a file
int writeUsersToFile(struct User users[], int userCount) {
    FILE *file = fopen("users.txt", "w");
    if (file == NULL) {
        return 0;
    }

    for (int i = 0; i < userCount; i++) {
        fprintf(file, "%s %s\n", users[i].username, users[i].password);
    }

    fclose(file);
    return 1;
}

int main() {
    // Initialize the flower database
    initializeFlowerDatabase();

    struct User users[100]; // Assuming a maximum of 100 users
    int userCount = 0;

    // Read users from a file
    if (!readUsersFromFile(users, &userCount)) {
        printf("Failed to read user data.\n");
        return 1;
    }

    int isAdmin = 0;
    char username[50];
    char password[50];

    printf("Login\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    // Check if the user is an admin
    if (strcmp(username, "admin") == 0 && strcmp(password, "adminpassword") == 0) {
        isAdmin = 1;
    } else {
        int validUser = 0;
        // Check if the user is in the user database
        for (int i = 0; i < userCount; i++) {
            if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
                validUser = 1;
                break;
            }
        }

        if (!validUser) {
            printf("Invalid username or password.\n");
            return 1;
        }
    }

    if (isAdmin) {
        int choice;
        while (1) {
            printf("Admin Panel\n");
            printf("1. Add User\n");
            printf("2. Delete User\n");
            printf("3. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    printf("Enter username for the new user: ");
                    scanf("%s", username);
                    printf("Enter password for the new user: ");
                    scanf("%s", password);
                    strcpy(users[userCount].username, username);
                    strcpy(users[userCount].password, password);
                    userCount++;
                    if (writeUsersToFile(users, userCount)) {
                        printf("User added successfully.\n");
                    } else {
                        printf("Failed to add user.\n");
                    }
                    break;
                case 2:
                    printf("Enter username to delete: ");
                    scanf("%s", username);
                    int found = 0;
                    for (int i = 0; i < userCount; i++) {
                        if (strcmp(username, users[i].username) == 0) {
                            found = 1;
                            for (int j = i; j < userCount - 1; j++) {
                                strcpy(users[j].username, users[j + 1].username);
                                strcpy(users[j].password, users[j + 1].password);
                            }
                            userCount--;
                            if (writeUsersToFile(users, userCount)) {
                                printf("User deleted successfully.\n");
                            } else {
                                printf("Failed to delete user.\n");
                            }
                            break;
                        }
                    }
                    if (!found) {
                        printf("User not found.\n");
                    }
                    break;
                case 3:
                    printf("Exiting the admin panel.\n");
                    return 0;
                default:
                    printf("Invalid choice. Please select a valid option.\n");
            }
        }
    } else {
        // Normal user's functionality here
         int choice;
        while (1) {
            printf("User Panel\n");
            printf("1. Order Flower\n");
            printf("2. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    int flowerID;
                    printf("Enter Flower ID to order: ");
                    scanf("%d", &flowerID);
                    findFlower(flowerID);

                    // Check if the flower is available
                    if (flowerID >= 0 && flowerID < flowerCount) {
                        // You can add code here to handle the order process.
                        if (flowerDatabase[flowerID].stock > 0) {
                            printf("Flower ordered successfully.\n");
                            flowerDatabase[flowerID].stock--; // Decrease the stock
                        } else {
                            printf("Flower is out of stock.\n");
                        }
                    } else {
                        printf("Invalid Flower ID.\n");
                    }
                    break;
                case 2:
                    printf("Exiting the user panel.\n");
                    return 0;
                default:
                    printf("Invalid choice. Please select a valid option.\n");
            }
    }

    return 0;
}











/*
int main() {
    // Initialize the flower database
    initializeFlowerDatabase();

    // Add some flowers
    addFlower(1, "Red Rose", 2.99, ROSE);
    addFlower(2, "Tulip", 1.99, TULIP);
    addFlower(3, "White Lily", 3.49, LILY);

    // Test various operations
    findFlower(2);
    updateFlower(2, "Yellow Tulip", 1.49, TULIP);
    deleteFlower(1);

    // Summarize flower sales
    summarizeFlowerSales();

    return 0;
}
*/ 