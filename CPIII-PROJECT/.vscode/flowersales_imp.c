#include <stdio.h>
#include "flowersales.h"

// Define a struct array to store flower data

// Function implementations
void initializeFlowerDatabase() {
    flowerCount = 0;
}
void loadFlowerDataFromFile() {
    FILE *file = fopen("flowers.txt", "r");
    if (file == NULL) {
        printf("Çiçek verileri okunamadı.\n");
        return;
    }

    // Dosyadan çiçek verilerini okuyun ve çiçek veritabanına ekleyin
    while (fscanf(file, "%d %s %f %d %d", &flowerDatabase[flowerCount].flowerID, flowerDatabase[flowerCount].name, &flowerDatabase[flowerCount].price, (int *)&flowerDatabase[flowerCount].type, &flowerDatabase[flowerCount].stock) == 5) {
        flowerCount++;
    }

    fclose(file);
}


void addFlower(int flowerID, char *name, float price, enum FlowerType type, int stock) {
    // Çiçekleri veritabanına ekleyin
    if (flowerCount < 100) {
        flowerDatabase[flowerCount].flowerID = flowerID;
        snprintf(flowerDatabase[flowerCount].name, sizeof(flowerDatabase[flowerCount].name), "%s", name);
        flowerDatabase[flowerCount].price = price;
        flowerDatabase[flowerCount].type = type;
        flowerDatabase[flowerCount].stock = stock;
        flowerCount++;
    }
}

void findFlower(int flowerID) {
    // ID'ye göre çiçeği bulun ve görüntüleyin
    int i;
    for (i = 0; i < flowerCount; i++) {
        if (flowerDatabase[i].flowerID == flowerID) {
            printf("Çiçek ID: %d\n", flowerDatabase[i].flowerID);
            printf("Çiçek Adı: %s\n", flowerDatabase[i].name);
            printf("Çiçek Fiyatı: %.2f\n", flowerDatabase[i].price);
            printf("Çiçek Türü: %d\n", flowerDatabase[i].type);
            printf("Çiçek Stok Miktarı: %d\n", flowerDatabase[i].stock);
            return;
        }
    }
    printf("ID'si %d olan çiçek bulunamadı.\n", flowerID);
}

void updateFlower(int flowerID, char *newName, float newPrice, enum FlowerType newType) {
    // Çiçek verisini güncelleyin
    int i;
    for (i = 0; i < flowerCount; i++) {
        if (flowerDatabase[i].flowerID == flowerID) {
            snprintf(flowerDatabase[i].name, sizeof(flowerDatabase[i].name), "%s", newName);
            flowerDatabase[i].price = newPrice;
            flowerDatabase[i].type = newType;
            printf("ID'si %d olan çiçek güncellendi.\n", flowerID);
            return;
        }
    }
    printf("ID'si %d olan çiçek bulunamadı.\n", flowerID);
}

void deleteFlower(int flowerID) {
    // Veritabanından bir çiçeği silin
    int i;
    for (i = 0; i < flowerCount; i++) {
        if (flowerDatabase[i].flowerID == flowerID) {
            // Boşluğu doldurmak için kalan elemanları kaydırın
            for (int j = i; j < flowerCount - 1; j++) {
                flowerDatabase[j] = flowerDatabase[j + 1];
            }
            flowerCount--;
            printf("ID'si %d olan çiçek silindi.\n", flowerID);
            return;
        }
    }
    printf("ID'si %d olan çiçek bulunamadı.\n", flowerID);
}

void summarizeFlowerSales() {
    // Çiçek satışlarını özetleyin ve sonucu görüntüleyin
    float totalSales = 0;
    for (int i = 0; i < flowerCount; i++) {
        totalSales += flowerDatabase[i].price;
    }
    printf("Toplam Satış: %.2f\n", totalSales);
}
