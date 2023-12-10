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
void initializeFlowerOrderDatabase(int initialSize) {
    flowerorderdb = (struct Flower *)malloc(initialSize * sizeof(struct Flower));
    if (flowerorderdb == NULL) {
        printf("Hata: Çiçek siparişi veritabanı oluşturulamadı.\n");
        exit(1);
    }
    flowercount = 0;
}

// Çiçek siparişleri veritabanını temizlemek için aşağıdaki gibi bir işlev oluşturabilirsiniz
void cleanUpFlowerOrderDatabase() {
    free(flowerorderdb);
    flowerorderdb = NULL;
    flowercount = 0;
}


void deleteFlowerFromFile(int flowerID) {
    // Geçici bir dosya oluşturun
    FILE *tempFile = fopen("temp_flower.txt", "w");
    if (tempFile == NULL) {
        printf("Geçici dosya oluşturulamadı.\n");
        return;
    }

    // Eski verileri yeni dosyaya kopyala ve silinmesi gereken çiçeği atla
    for (int i = 0; i < flowerCount; i++) {
        if (flowerDatabase[i].flowerID == flowerID) {
            continue; // Silinmesi gereken çiçeği atla
        }
        fprintf(tempFile, "%d %s %.2f %d %d\n", flowerDatabase[i].flowerID, flowerDatabase[i].name, flowerDatabase[i].price, flowerDatabase[i].type, flowerDatabase[i].stock);
    }

    // Geçici dosyayı kapatın ve orijinal dosyayı silin
    fclose(tempFile);
    remove("flowers.txt");

    // Geçici dosyayı orijinal dosya adıyla yeniden adlandırın
    rename("temp_flower.txt", "flowers.txt");

    printf("ID'si %d olan çiçek başarıyla silindi.\n", flowerID);

    // Veritabanını güncelleyin
    loadFlowerDataFromFile();
}
int userLogin(struct User users[], int userCount, char *username, char *password) {
    int isLoggedIn = 0;

    char inputUsername[50];
    char inputPassword[50];

    printf("Giriş\n");
    printf("Kullanıcı Adı: ");
    scanf("%s", inputUsername);
    printf("Şifre: ");
    scanf("%s", inputPassword);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(inputUsername, users[i].username) == 0 && strcmp(inputPassword, users[i].password) == 0) {
            isLoggedIn = 1; // Kullanıcı giriş yaptı
            strcpy(username, inputUsername);
            strcpy(password, inputPassword);
            break;
        }
    }

    return isLoggedIn;
}
int writeFlowerOrdersToFile(struct Flower *orders, int count) {
    FILE *file = fopen("flowerorder.txt", "a"); // "a" dosyayı eklemek için açar

    if (file == NULL) {
        printf("Dosya açma hatası\n");
        return 0;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d %s %.2f %d %d\n", orders[i].flowerID, orders[i].name, orders[i].price, orders[i].type, orders[i].stock);
    }

    fclose(file);
    return 1;
}


// Function to write flower data to a file
int writeFlowerDataToFile() {
    FILE *file = fopen("flowers.txt", "w");
    if (file == NULL) {
        return 0; // Dosya açılamadı
    }

    for (int i = 0; i < flowerCount; i++) {
        fprintf(file, "%d %s %.2f %d %d\n", flowerDatabase[i].flowerID, flowerDatabase[i].name, flowerDatabase[i].price, flowerDatabase[i].type, flowerDatabase[i].stock);
    }

    fclose(file);
    return 1; // Başarıyla yazıldı
}



