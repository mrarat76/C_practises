#include <stdio.h>
#include "flowersales.h"

// Define a struct array to store flower data
struct Flower flowerDatabase[100]; // Assuming a maximum of 100 flowers
int flowerCount = 0;

// Function implementations
void initializeFlowerDatabase() {
    flowerCount = 0;
}

void addFlower(int id, char *name, float price, enum FlowerType type) {
    // Add a flower to the database
    if (flowerCount < 100) {
        flowerDatabase[flowerCount].id = id;
        snprintf(flowerDatabase[flowerCount].name, sizeof(flowerDatabase[flowerCount].name), "%s", name);
        flowerDatabase[flowerCount].price = price;
        flowerDatabase[flowerCount].type = type;
        flowerCount++;
    }
}

void findFlower(int id) {
    // Find and display a flower by ID
    int i;
    for (i = 0; i < flowerCount; i++) {
        if (flowerDatabase[i].id == id) {
            printf("Flower ID: %d\n", flowerDatabase[i].id);
            printf("Flower Name: %s\n", flowerDatabase[i].name);
            printf("Flower Price: %.2f\n", flowerDatabase[i].price);
            printf("Flower Type: %d\n", flowerDatabase[i].type);
            return;
        }
    }
    printf("Flower with ID %d not found.\n", id);
}

void updateFlower(int id, char *newName, float newPrice, enum FlowerType newType) {
    // Update flower data
    int i;
    for (i = 0; i < flowerCount; i++) {
        if (flowerDatabase[i].id == id) {
            snprintf(flowerDatabase[i].name, sizeof(flowerDatabase[i].name), "%s", newName);
            flowerDatabase[i].price = newPrice;
            flowerDatabase[i].type = newType;
            printf("Flower with ID %d updated.\n", id);
            return;
        }
    }
    printf("Flower with ID %d not found.\n", id);
}

void deleteFlower(int id) {
    // Delete a flower from the database
    int i;
    for (i = 0; i < flowerCount; i++) {
        if (flowerDatabase[i].id == id) {
            // Shift remaining elements to fill the gap
            for (int j = i; j < flowerCount - 1; j++) {
                flowerDatabase[j] = flowerDatabase[j + 1];
            }
            flowerCount--;
            printf("Flower with ID %d deleted.\n", id);
            return;
        }
    }
    printf("Flower with ID %d not found.\n", id);
}

void summarizeFlowerSales() {
    // Summarize flower sales and display the result
    float totalSales = 0;
    for (int i = 0; i < flowerCount; i++) {
        totalSales += flowerDatabase[i].price;
    }
    printf("Total Sales: %.2f\n", totalSales);
}

