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
    enum FlowerType type;
    int stock; // Stok miktarı
};

int flowerCount;

// Function prototypes
void initializeFlowerDatabase();
void addFlower(int flowerID, char *name, float price, enum FlowerType type, int stock);
void findFlower(int flowerID);
void updateFlower(int flowerID, char *newName, float newPrice, enum FlowerType newType);
void deleteFlower(int flowerID);
void summarizeFlowerSales();
struct Flower flowerDatabase[100]; // Maksimum 100 çiçek varsayımı

#endif
