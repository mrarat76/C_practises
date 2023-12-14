#include <stdio.h>
#include "flowersales.h"
#include <stdlib.h> // exit ve free işlevlerini kullanmak için
#include <string.h> // strcmp ve strcpy işlevlerini kullanmak için

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
const char* getFlowerTypeName(enum FlowerType type) {
    switch (type) {
        case ROSE:
            return "ROSE";
        case TULIP:
            return "TULIP";
        case LILY:
            return "LILY";
        case DAISY:
            return "DAISY";
        case SUNFLOWER:
            return "SUNFLOWER";
        default:
            return "UNKNOWN";
    }
}



void addFlower(int flowerID, char *name, float price, enum FlowerType type, int stock) {
    // Çiçekleri veritabanına ekleyin
    if (flowerCount < 100) {
        flowerDatabase[flowerCount].flowerID = flowerID;
         strcpy(flowerDatabase[flowerCount].name, name);
        //snprintf(flowerDatabase[flowerCount].name, sizeof(flowerDatabase[flowerCount].name), "%s", name);
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
            printf("Flower ID: %d\n", flowerDatabase[i].flowerID);
            printf("Flower Name: %s\n", flowerDatabase[i].name);
            printf("Flower Price: %.2f\n", flowerDatabase[i].price);
            printf("Flower Type: %d\n", flowerDatabase[i].type);
            printf("Flower Type Name: %s\n", getFlowerTypeName(flowerDatabase[i].type));
            printf("Flower stock quantity: %d\n", flowerDatabase[i].stock);
            return;
        }
    }
    printf("The ID of %d could not found.\n", flowerID);
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



void updateflower(int flowerID, char *newName, float newPrice, enum FlowerType newType, int newStock) {
    // Çiçek verisini güncelleyin
    int i;
    for (i = 0; i < flowerCount; i++) {
        if (flowerDatabase[i].flowerID == flowerID) {
            strcpy(flowerDatabase[i].name, newName);
            flowerDatabase[i].price = newPrice;
            flowerDatabase[i].type = newType;
            flowerDatabase[i].stock = newStock;

            // Düzenlenmiş çiçeği dosyaya kaydet
            if (writeFlowerDataToFile()) {
                printf("The flower with ID %d has been successfully updated.\n", flowerID);
            } else {
                printf("The flower with ID %d could not be updated.\n", flowerID);
            }
            return;
        }
    }
    printf("The flower with ID %d was not found.\n", flowerID);
}


// Function to write users to a file
int writeUsersToFile(struct User users[], int userCount) {
    FILE *file = fopen("users.txt", "w");
    if (file == NULL) {
        return 0;
    }

    for (int i = 0; i < userCount; i++) {
        fprintf(file, "%s %s %d\n", users[i].username, users[i].password, users[i].isAdmin);
    }

    fclose(file);
    return 1;
}

void deleteuser(struct User users[], int *userCount, const char *deleteUsername) {
    int found = 0;
    for (int i = 0; i < *userCount; i++) {
        if (strcmp(deleteUsername, users[i].username) == 0) {
            found = 1;
            for (int j = i; j < *userCount - 1; j++) {
                strcpy(users[j].username, users[j + 1].username);
                strcpy(users[j].password, users[j + 1].password);
                users[j].isAdmin = users[j + 1].isAdmin;
            }
            (*userCount)--;

            if (writeUsersToFile(users, *userCount)) {
                printf("User '%s' has been successfully deleted.\n", deleteUsername);
            } else {
                printf("User '%s' could not be deleted.\n", deleteUsername);
            }
            break;
        }
    }

    if (!found) {
        printf("User '%s' not found.\n", deleteUsername);
    }
}
// Function to read users from a file
int readUsersFromFile(struct User users[], int *userCount) {
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) {
        return 0;
    }

    *userCount = 0;
    while (fscanf(file, "%s %s %d", users[*userCount].username, users[*userCount].password, &users[*userCount].isAdmin) == 3) {
        (*userCount)++;
    }

    fclose(file);
    return 1;
}

void adduser(struct User users[], int *userCount, const char *newUsername, const char *newPassword, int newUserIsAdmin) {
    if (*userCount >= 100) {
        printf("User limit exceeded. Cannot add more users.\n");
        return; // Kullanıcı limiti aşıldı. Daha fazla kullanıcı eklenemez.
    }

    strcpy(users[*userCount].username, newUsername);
    strcpy(users[*userCount].password, newPassword);
    users[*userCount].isAdmin = newUserIsAdmin;
    (*userCount)++;

    if (writeUsersToFile(users, *userCount)) {
        printf("User has been successfully added.\n");
    } else {
        printf("User could not be added.\n");
    }
}

void listFlowers(struct Flower flowerDatabase[], int flowerCount) {
    printf("All Flowers have been listed below:\n");
    for (int i = 0; i < flowerCount; i++) {
        printf("Flower ID: %d\n", flowerDatabase[i].flowerID);
        printf("Flower Name: %s\n", flowerDatabase[i].name);
        printf("Flower Price: %.2f\n", flowerDatabase[i].price);
        printf("Flower Type: %d\n", flowerDatabase[i].type);
        printf("Flower Stock Quantity: %d\n", flowerDatabase[i].stock);
        printf("Flower Type Name: %s\n", getFlowerTypeName(flowerDatabase[i].type));
        printf("\n");
    }
}


void placeOrder(struct Flower flowerDatabase[], int flowerCount) {
    int flowerID;
    int value;
    
    printf("Enter the flower ID to place an order: ");
    scanf("%d", &flowerID);
    printf("Enter the flower stock quantity: ");
    scanf("%d", &value);
    
    int foundIndex = -1;
    for (int i = 0; i < flowerCount; i++) {
        if (flowerDatabase[i].flowerID == flowerID) {
            foundIndex = i;
            break;
        }
    }
    
    if (foundIndex >= 0) {
        if (flowerDatabase[foundIndex].stock > 0) {
            // Sipariş işlemini burada yapabilirsiniz
            printf("Flower has ordered successfully\n");
            flowerDatabase[foundIndex].stock -= value;

            // Dinamik olarak flowerorderdb'yi genişlet
            if (flowerorderdb == NULL) {
                // flowerorderdb henüz boşsa, ilk defa bellek ayırın
                flowerorderdb = (struct Flower *)malloc(sizeof(struct Flower));
            } else {
                // flowerorderdb doluysa, realloc kullanarak belleği genişletin
                flowerorderdb = (struct Flower *)realloc(flowerorderdb, (flowercount + 1) * sizeof(struct Flower));
            }

            if (flowerorderdb == NULL) {
                printf("Error: Couldn't allocate or expand memory.\n");
                exit(1);
            }

            // Yeni çiçeği flowerorderdb'ye ekleyin
            flowerorderdb[flowercount].flowerID = flowerDatabase[foundIndex].flowerID;
            strcpy(flowerorderdb[flowercount].name, flowerDatabase[foundIndex].name);
            flowerorderdb[flowercount].price = flowerDatabase[foundIndex].price;
            flowerorderdb[flowercount].type = flowerDatabase[foundIndex].type;
            flowerorderdb[flowercount].stock = value;
            flowercount++;
            
            if (flowerDatabase[foundIndex].stock == 0) {
                deleteFlowerFromFile(flowerID);
            }
            
            // Sipariş verilen çiçeği silmek için deleteFlower fonksiyonunu çağırın
           
            writeFlowerOrdersToFile(flowerorderdb, flowercount);
        } else {
            printf("Flower out of stock.\n");
        }
    } else {
        printf("Invalid Flower ID.\n");
    }
}

void listOrders() {
    printf("All orders:\n");
    for (int i = 0; i < flowercount; i++) {
        printf("Flower ID: %d\n", flowerorderdb[i].flowerID);
        printf("Flower Name: %s\n", flowerorderdb[i].name);
        printf("Flower Price: %.2f\n", flowerorderdb[i].price);
        printf("Flower Type: %d\n", flowerorderdb[i].type);
        printf("The stock quantity of the ordered flower: %d\n", flowerorderdb[i].stock);
        printf("Flower Type Name: %s\n", getFlowerTypeName(flowerorderdb[i].type));
        printf("\n");
    }
}

