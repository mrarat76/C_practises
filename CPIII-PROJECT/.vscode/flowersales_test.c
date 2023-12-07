#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flowersales.h"
#include "flowersales_imp.c"
// Struct to represent user information
struct User {
    char username[50];
    char password[50];
    int isAdmin; // Kullanıcının yönetici olup olmadığını belirtmek için eklenen alan
};

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

int main() {
    // Initialize the flower database
    initializeFlowerDatabase();
    loadFlowerDataFromFile();
    struct User users[100]; // Maksimum 100 kullanıcı varsayımı
    int userCount = 0;

    // Read users from a file
    if (!readUsersFromFile(users, &userCount)) {
        printf("Kullanıcı verileri okunamadı.\n");
        return 1;
    }

    // Varsayılan admin kullanıcısı kontrolü
    if (userCount == 0) {
        // Eğer kullanıcı verileri boşsa, varsayılan bir admin kullanıcısını ekleyin.
        strcpy(users[0].username, "admin");
        strcpy(users[0].password, "admin123");
        users[0].isAdmin = 1; // Bu kullanıcıyı admin olarak işaretleyin
        userCount = 1;
        if (writeUsersToFile(users, userCount)) {
            printf("Varsayılan admin kullanıcısı başarıyla oluşturuldu.\n");
        } else {
            printf("Varsayılan admin kullanıcısı oluşturulamadı.\n");
            return 1;
        }
    }

    int isAdmin = 0;
    char username[50];
    char password[50];

    printf("Giriş\n");
    printf("Kullanıcı Adı: ");
    scanf("%s", username);
    printf("Şifre: ");
    scanf("%s", password);

    int userIndex = -1;
    // Kullanıcının yönetici olup olmadığını ve hangi kullanıcı olduğunu kontrol edin
    for (int i = 0; i < userCount; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            isAdmin = users[i].isAdmin;
            userIndex = i;
            break;
        }
    }

    if (userIndex == -1) {
        printf("Geçersiz kullanıcı adı veya şifre.\n");
        return 1;
    }

    if (isAdmin) {
        int choice;
        while (1) {
            printf("Yönetici Paneli\n");
            printf("1. Kullanıcı Ekle\n");
            printf("2. Kullanıcı Sil\n");
            printf("3. Çıkış\n");
            printf("Seçiminizi Girin: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    printf("Yeni kullanıcı için kullanıcı adını girin: ");
                    scanf("%s", username);
                    printf("Yeni kullanıcı için şifreyi girin: ");
                    scanf("%s", password);
                    printf("Yeni kullanıcı için yönetici mi (1) yoksa normal kullanıcı mı (0) olduğunu belirtin: ");
                    int newUserIsAdmin;
                    scanf("%d", &newUserIsAdmin);
                    strcpy(users[userCount].username, username);
                    strcpy(users[userCount].password, password);
                    users[userCount].isAdmin = newUserIsAdmin;
                    userCount++;
                    if (writeUsersToFile(users, userCount)) {
                        printf("Kullanıcı başarıyla eklendi.\n");
                    } else {
                        printf("Kullanıcı eklenemedi.\n");
                    }
                    break;
                case 2:
                    printf("Silmek için kullanıcı adını girin: ");
                    scanf("%s", username);
                    int found = 0;
                    for (int i = 0; i < userCount; i++) {
                        if (strcmp(username, users[i].username) == 0) {
                            found = 1;
                            for (int j = i; j < userCount - 1; j++) {
                                strcpy(users[j].username, users[j + 1].username);
                                strcpy(users[j].password, users[j + 1].password);
                                users[j].isAdmin = users[j + 1].isAdmin;
                            }
                            userCount--;
                            if (writeUsersToFile(users, userCount)) {
                                printf("Kullanıcı başarıyla silindi.\n");
                            } else {
                                printf("Kullanıcı silinemedi.\n");
                            }
                            break;
                        }
                    }
                    if (!found) {
                        printf("Kullanıcı bulunamadı.\n");
                    }
                    break;
                case 3:
                    printf("Yönetici panelinden çıkılıyor.\n");
                    return 0;
                default:
                    printf("Geçersiz seçim. Lütfen geçerli bir seçenek seçin.\n");
            }
        }
    } else {

 int choice;
    while (1) {
        printf("Kullanıcı Paneli\n");
        printf("1. Çiçek Siparişi Ver\n");
        printf("2. Tüm Çiçekleri Görüntüle\n");
        printf("3. Çıkış\n");
        printf("Seçiminizi Girin: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int ID;
                printf("Sipariş vermek için çiçek ID'sini girin: ");
                scanf("%d", &ID);
                findFlower(ID);

                // Çiçeğin mevcut olup olmadığını kontrol edin
                if (ID >= 0 && ID < flowerCount) {
                    // Sipariş işlemini yönetmek için buraya kod ekleyebilirsiniz.
                    if (flowerDatabase[ID].stock > 0) {
                        printf("Çiçek başarıyla sipariş edildi.\n");
                        flowerDatabase[ID].stock--; // Stoku azalt
                    } else {
                        printf("Çiçek stokta yok.\n");
                    }
                } else {
                    printf("Geçersiz Çiçek ID'si.\n");
                }
                break;
            }
            case 2:
                  printf("Tüm Çiçekler:\n");
                for (int i = 0; i < flowerCount; i++) {
                    printf("Çiçek ID: %d\n", flowerDatabase[i].flowerID);
                    printf("Çiçek Adı: %s\n", flowerDatabase[i].name);
                    printf("Çiçek Fiyatı: %.2f\n", flowerDatabase[i].price);
                    printf("Çiçek Türü: %d\n", flowerDatabase[i].type);
                    printf("Çiçek Stok Miktarı: %d\n", flowerDatabase[i].stock);
                    printf("\n");
                }
                break;
            case 3:
                printf("Kullanıcı panelinden çıkılıyor.\n");
                return 0;
            default:
                printf("Geçersiz seçim. Lütfen geçerli bir seçenek seçin.\n");
        }
    


       /*/ // Normal kullanıcının işlevselliği burada
        int choice;
        while (1) {
            printf("Kullanıcı Paneli\n");
            printf("1. Çiçek Siparişi Ver\n");
            printf("2. Çıkış\n");
            printf("Seçiminizi Girin: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:{

                
                    int ID;
                    printf("Sipariş vermek için çiçek ID'sini girin: ");
                    scanf("%d", &ID);
                    findFlower(ID);

                    // Çiçeğin mevcut olup olmadığını kontrol edin
                    if (ID >= 0 && ID < flowerCount) {
                        // Sipariş işlemini yönetmek için buraya kod ekleyebilirsiniz.
                        if (flowerDatabase[ID].stock > 0) {
                            printf("Çiçek başarıyla sipariş edildi.\n");
                            flowerDatabase[ID].stock--; // Stoku azalt
                        } else {
                            printf("Çiçek stokta yok.\n");
                        }
                    } else {
                        printf("Geçersiz Çiçek ID'si.\n");
                    }
                    break;
                }
                case 2:
                    printf("Kullanıcı panelinden çıkılıyor.\n");
                    return 0;
                default:
                    printf("Geçersiz seçim. Lütfen geçerli bir seçenek seçin.\n");
            }
        }
    }*/

    return 0;
}}}
