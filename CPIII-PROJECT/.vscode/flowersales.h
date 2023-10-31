#ifndef FLOWER_SALES_H
#define FLOWER_SALES_H

// Define an enum
enum FlowerType {
    ROSE,
    TULIP,
    LILY,
    DAISY,
    SUNFLOWER
};

// Define structs
struct Flower {
    int flowerID;
    char name[50];
    float price;
    enum FlowerType type; // Enum type field
};

int flowerCount;

// Function prototypes
void initializeFlowerDatabase();
void addFlower(int id, char *name, float price, enum FlowerType type);
void findFlower(int id);
void updateFlower(int id, char *newName, float newPrice, enum FlowerType newType);
void deleteFlower(int id);
void summarizeFlowerSales();

#endif
