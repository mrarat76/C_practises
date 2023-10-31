#include <stdio.h>
#include "flowersales.h"

// Define a struct array to store flower data
extern struct Flower flowerDatabase[100]; // Assuming a maximum of 100 flowers


// Function implementations
void initializeFlowerDatabase() {
    flowerCount = 0;
}

void addFlower(int flowerID, char *name, float price, enum FlowerType type) {
    // Add a flower to the database
    if (flowerCount < 100) {
        flowerDatabase[flowerCount].flowerID = flowerID;
        snprintf(flowerDatabase[flowerCount].name, sizeof(flowerDatabase[flowerCount].name), "%s", name);
        flowerDatabase[flowerCount].price = price;
        flowerDatabase[flowerCount].type = type;
        flowerCount++;
    }
}

void findFlower(int flowerID) {
    // Find and display a flower by ID
    int i;
    for (i = 0; i < flowerCount; i++) {
        if (flowerDatabase[i].flowerID == flowerID) {
            printf("Flower ID: %d\n", flowerDatabase[i].flowerID);
            printf("Flower Name: %s\n", flowerDatabase[i].name);
            printf("Flower Price: %.2f\n", flowerDatabase[i].price);
            printf("Flower Type: %d\n", flowerDatabase[i].type);
            return;
        }
    }
    printf("Flower with ID %d not found.\n", flowerID);
}

void updateFlower(int flowerID, char *newName, float newPrice, enum FlowerType newType) {
    // Update flower data
    int i;
    for (i = 0; i < flowerCount; i++) {
        if (flowerDatabase[i].flowerID == flowerID) {
            snprintf(flowerDatabase[i].name, sizeof(flowerDatabase[i].name), "%s", newName);
            flowerDatabase[i].price = newPrice;
            flowerDatabase[i].type = newType;
            printf("Flower with ID %d updated.\n", flowerID);
            return;
        }
    }
    printf("Flower with ID %d not found.\n", flowerID);
}

void deleteFlower(int flowerID) {
    // Delete a flower from the database
    int i;
    for (i = 0; i < flowerCount; i++) {
        if (flowerDatabase[i].flowerID == flowerID) {
            // Shift remaining elements to fill the gap
            for (int j = i; j < flowerCount - 1; j++) {
                flowerDatabase[j] = flowerDatabase[j + 1];
            }
            flowerCount--;
            printf("Flower with ID %d deleted.\n", flowerID);
            return;
        }
    }
    printf("Flower with ID %d not found.\n", flowerID);
}

void summarizeFlowerSales() {
    // Summarize flower sales and display the result
    float totalSales = 0;
    for (int i = 0; i < flowerCount; i++) {
        totalSales += flowerDatabase[i].price;
    }
    printf("Total Sales: %.2f\n", totalSales);
}

