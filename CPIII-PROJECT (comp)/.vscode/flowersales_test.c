#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flowersales.h"
#include "flowersales_imp.c"



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
        printf("User's data cannot be detected..\n");
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
            printf("Default admin has been generated. \n");
        } else {
            printf("Attention! Default admin has not been generated.\n");
            return 1;
        }
    }

    int isLoggedIn = 0;
    char username[50];

    while (1) {
        if (!isLoggedIn) {
            // Kullanıcı girişi yapılmamışsa, kullanıcı adı ve şifre istenilmesi
            char password[50];
            
             printf("\033[37;1mProvided by AraTech Autonomous Systems\033[0m\n");
    
           
            printf("=== FLOWER SALES SYSTEM ===\n");
            printf("Welcome\n");
            printf("===     LOGIN PAGE    ===\n");
            printf("Username: ");
            scanf("%s", username);
            printf("Password: ");
            scanf("%s", password);

            // Kullanıcı adı ve şifreyi kontrol edin ve giriş yapmalarına izin verilmesi
            int userIndex = -1;
            for (int i = 0; i < userCount; i++) {
                if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
                    isLoggedIn = 1; // Kullanıcı giriş yaptı
                    break;
                }
            }

            if (!isLoggedIn) {
                printf("Invalid username or password.\n");
                continue; // Kullanıcı giriş yapamazsa tekrar kullanıcı adı ve şifre isteyin
            }
        }

        if (isLoggedIn) {
            // Kullanıcı giriş yaptıysa bu blok içinde işlemleri yapabilirsiniz
            int isAdmin = 0;

            for (int i = 0; i < userCount; i++) {
                if (strcmp(username, users[i].username) == 0) {
                    isAdmin = users[i].isAdmin;
                    break;
                }
            }

            if (isAdmin) {
                int choice;
                while (1) {
                    printf("Administrator Panel\n");
                    printf("1. Add User\n");
                    printf("2. Delete User\n");
                    printf("3. Order a flower\n");
                    printf("4. List all flowers\n");
                    printf("5. Exit\n");
                    printf("6. Add flower\n");
                    printf("7. Edit flower\n");
                    printf("8. Find flower by ID\n");
                    printf("Enter your precious choice: ");
                    scanf("%d", &choice);

                    switch (choice) {
                        case 1: {
                            char newUsername[50];
                            char newPassword[50];
                            int newUserIsAdmin;

                            printf("Enter new username: ");
                            scanf("%s", newUsername);
                            printf("Enter new password: ");
                            scanf("%s", newPassword);
                            printf("Specify whether the new user is an administrator (1) or a regular user (0): ");
                            scanf("%d", &newUserIsAdmin);

                            strcpy(users[userCount].username, newUsername);
                            strcpy(users[userCount].password, newPassword);
                            users[userCount].isAdmin = newUserIsAdmin;
                            userCount++;

                            if (writeUsersToFile(users, userCount)) {
                                printf("User has been successfully added.\n");
                            } else {
                                printf("User could not be added.\n");
                            }
                            break;
                        }
                        case 2: {
                            char deleteUser[50];
                            printf("Enter the username to delete: ");
                            scanf("%s", deleteUser);

                            int found = 0;
                            for (int i = 0; i < userCount; i++) {
                                if (strcmp(deleteUser, users[i].username) == 0) {
                                    found = 1;
                                    for (int j = i; j < userCount - 1; j++) {
                                        strcpy(users[j].username, users[j + 1].username);
                                        strcpy(users[j].password, users[j + 1].password);
                                        users[j].isAdmin = users[j + 1].isAdmin;
                                    }
                                    userCount--;

                                    if (writeUsersToFile(users, userCount)) {
                                        printf("User has been successfully deleted.\n");
                                    } else {
                                        printf("User could not be deleted.\n");
                                    }
                                    break;
                                }
                            }

                            if (!found) {
                                printf("User not found.\n");
                            } 
                            break;
                        }
                        case 3: {
                            int flowerID;
                            printf("Enter the flower ID to place an order: ");
                            scanf("%d", &flowerID);

                            if (flowerID >= 0 && flowerID < flowerCount) {
                                if (flowerDatabase[flowerID].stock > 0) {
                                    // Sipariş işlemini burada yapabilirsiniz
                                    printf("Flower successfully ordered.\n");
                                    flowerDatabase[flowerID].stock--;
                                } else {
                                    printf("Flower out of stock.\n");
                                }
                            } else {
                                printf("Invalid Flower ID.\n");
                            }
                            break;
                        }
                        case 4: {
                            printf("All Flowers has been listed below:\n");
                            for (int i = 0; i < flowerCount; i++) {
                                printf("Flower ID: %d\n", flowerDatabase[i].flowerID);
                                printf("Flower Name: %s\n", flowerDatabase[i].name);
                                printf("Flower Price: %.2f\n", flowerDatabase[i].price);
                                printf("Flower Type: %d\n", flowerDatabase[i].type);
                                printf("Flower stock value: %d\n", flowerDatabase[i].stock);
                                printf("\n");
                            }
                            break;
                        }
                        case 5: {
                           printf("Exiting...\n");
                           fflush(stdout); // Tamponu temizle
                           system("cls");  // Konsolu temizle (Windows için)
                           return main();
                        }

                        case 6: {
                                // Çiçek Ekle
                                char flowerName[50];
                                float flowerPrice;
                                int flowerType;
                                int flowerStock;
                                int id;
                                printf("To add, enter the flower ID: ");
                                scanf("%d", &id);
                                // Çiçek ID'sine sahip çiçek zaten varsa ekleme yapma
                                
                                 int isAlreadyExist = 0;
                                    for (int i = 0; i < flowerCount; i++) {
                                    if (flowerDatabase[i].flowerID == id) {
                                     isAlreadyExist = 1;
                                     break;
                                      }
                                 }

                                if (isAlreadyExist) {
                                 printf("A flower with this ID already exists. The addition couldn't be completed.\n");
                                 break;
                                  }
                               
                                printf("The names are as follows: ROSE, TULIP, LILY, DAISY, SUNFLOWER.\n");
                                printf("Enter the flower name to add.: ");
                                scanf("%s", flowerName);
                                printf("Enter the flower price: ");
                                scanf("%f", &flowerPrice);
                                printf("Specify the flower type: {ROSE -> 0, TULIP->1, LILY->2, DAISY->3, SUNFLOWER->4} ");
                                scanf("%d", &flowerType);
                                printf("Enter the flower stock quantity:");
                                scanf("%d", &flowerStock);
                                
                                // Yeni çiçeği flowerDatabase'e ekleyin
                                flowerDatabase[flowerCount].flowerID = id; // Yeni çiçeğin ID'si
                                strcpy(flowerDatabase[flowerCount].name, flowerName);
                                flowerDatabase[flowerCount].price = flowerPrice;
                                flowerDatabase[flowerCount].type = flowerType;
                                flowerDatabase[flowerCount].stock = flowerStock;
                                flowerCount++;

                                // Çiçeği dosyaya kaydet
                                if (writeFlowerDataToFile()) {
                                    printf("The flower has been successfully added.\n");
                                } else {
                                    printf("The flower could not be added.\n");
                                }
                                break;
                            }

                        case 7: {
                                // Çiçek Düzenle
                                int editFlowerID;

                                printf("Enter the flower ID to edit:");
                                scanf("%d", &editFlowerID);

                                // Belirtilen çiçek ID'sine sahip çiçeklerin zaten ekli olup olmadığını kontrol et
                                int found = 0;
                                for (int i = 0; i < flowerCount; i++) {
                                    if (flowerDatabase[i].flowerID == editFlowerID) {
                                        found = 1;
                                        break;
                                    }
                                }

                                if (!found) {
                                    printf("The flower with this ID could not be found.\n");
                                    break;
                                }

                                char newFlowerName[50];
                                float newFlowerPrice;
                                int newFlowerType;
                                int newFlowerStock;

                                printf("Enter the new flower name:");
                                scanf("%s", newFlowerName);
                                printf("Enter the new flower price: ");
                                scanf("%f", &newFlowerPrice);
                                printf("Specify the new flower type: ");
                                scanf("%d", &newFlowerType);
                                printf("Enter the new flower stock quantity: ");
                                scanf("%d", &newFlowerStock);

                                // Çiçeği düzenleyin
                                for (int i = 0; i < flowerCount; i++) {
                                    if (flowerDatabase[i].flowerID == editFlowerID) {
                                        strcpy(flowerDatabase[i].name, newFlowerName);
                                        flowerDatabase[i].price = newFlowerPrice;
                                        flowerDatabase[i].type = newFlowerType;
                                        flowerDatabase[i].stock = newFlowerStock;

                                        // Düzenlenmiş çiçeği dosyaya kaydet
                                        if (writeFlowerDataToFile()) {
                                            printf("The flower has been successfully edited.\n");
                                        } else {
                                            printf("The flower could not be edited.\n");
                                        }

                                        break; // Çiçeği bulduk ve düzenledik, döngüyü sonlandırın.
                                    }
                }

                                break;
                  }
                        case 8: {
                            int flowerID;
                            printf("To find, enter the flower ID: ");
                            scanf("%d", &flowerID);
                            findFlower(flowerID);
                            break;
                        }

                        default:
                            printf("Invalid selection. Please choose a valid option.\n");
                    }
                }
            } else {
                int choice;
                while (1) {
                    printf("User Panel\n");
                    printf("1. Order a flower\n");
                    printf("2. List all flowers\n");
                    printf("3. Show order\n");
                    printf("4. Exit\n");
                    printf("5. Find flower by ID\n");
                    printf("Enter your precious choice: ");
                    scanf("%d", &choice);

                    switch (choice) {
                       case 1: {
                    int flowerID;
                    int value;
                    printf("Enter the flower ID to place an order: ");
                    scanf("%d", &flowerID);
                    printf("Enter the flower stock quantity: ");
                    scanf("%d", &value);
                     
                     // Çiçeği bul ve düzenle
                     int foundIndex = -1;
                        for (int i = 0; i < flowerCount; i++) {
                      if (flowerDatabase[i].flowerID == flowerID) {
                         foundIndex = i;
                      break;
                          }
                         }
                    if (flowerID >= 0 && flowerID < flowerCount) {
                        if (flowerDatabase[flowerID].stock > 0) {
                            // Sipariş işlemini burada yapabilirsiniz
                            printf("Flower has ordered successfully\n");
                            flowerDatabase[foundIndex].stock=flowerDatabase[foundIndex].stock-value;

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
                            if(flowerDatabase[foundIndex].stock == 0){
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
                    break;
                }
                        case 2: {
                            printf("All Flowers has been listed below:\n");
                            for (int i = 0; i < flowerCount; i++) {
                                printf("Flower ID: %d\n", flowerDatabase[i].flowerID);
                                printf("Flower Name: %s\n", flowerDatabase[i].name);
                                printf("Flower Price: %.2f\n", flowerDatabase[i].price);
                                printf("Flower Type: %d\n", flowerDatabase[i].type);
                                printf("Flower Stock Quantity: %d\n", flowerDatabase[i].stock);
                                printf("\n");
                            }
                            break;
                        }
                        case 3: {
                            printf("All orders:\n");
                            for (int i = 0; i < flowercount; i++) {
                                printf("Flower ID: %d\n", flowerorderdb[i].flowerID);
                                printf("Flower Name: %s\n", flowerorderdb[i].name);
                                printf("Flower Price: %.2f\n", flowerorderdb[i].price);
                                printf("Flower Type: %d\n", flowerorderdb[i].type);
                                printf("The stock quantity of the ordered flower: %d\n", flowerorderdb[i].stock);
                                printf("\n");
                            }
                            break;
                        }
                        case 4: {
                            // Çıkış yap ve kullanıcı girişine geri dön
                             printf("Exiting...\n");
                           fflush(stdout); // Tamponu temizle
                           system("cls");  // Konsolu temizle (Windows için)
                           return main();
                        }
                        case 5: {
                            int flowerID;
                            printf("To find, enter the flower ID:");
                            scanf("%d", &flowerID);
                            findFlower(flowerID);
                            break;
                        }
                        default:
                            printf("Invalid selection. Please choose a valid option.\n");
                    }
                }
            }
        }
    }

    return 0;
}








/*

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
   while (1){
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
        printf("4. Sipariş Görüntüle\n");
        printf("Seçiminizi Girin: ");
        scanf("%d", &choice);
        int ID;
        switch (choice) {
            case 1: {
                
                printf("Sipariş vermek için çiçek ID'sini girin: ");
                scanf("%d", &ID);
                findFlower(ID);
                deleteFlower(ID);
               // Dinamik olarak flowerorderdb'yi genişlet
            if (flowerCount == 0) {
    // flowerorderdb henüz boşsa, ilk defa bellek ayırın
    flowerorderdb = (struct Flower *)malloc(sizeof(struct Flower));
                    } else {
    // flowerorderdb doluysa, realloc kullanarak belleği genişletin
    flowerorderdb = (struct Flower *)realloc(flowerorderdb, (flowercount + 1) * sizeof(struct Flower));
                    }

                    if (flowerorderdb == NULL) {
        printf("Hata: Bellek ayıramadı veya genişletilemedi.\n");
                exit(1);
                }

// Yeni çiçeği flowerorderdb'ye ekleyin
                flowerorderdb[flowercount].flowerID = flowerDatabase[ID].flowerID;
                strcpy(flowerorderdb[flowerCount].name, flowerDatabase[ID].name);
                flowerorderdb[flowercount].price = flowerDatabase[ID].price;
                flowerorderdb[flowercount].type = flowerDatabase[ID].type;
                flowerorderdb[flowercount].stock = 1;
                flowercount++;

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
                return 0 ;
            case 4:
                printf("Siparişler:\n");
                for (int i = 0; i <flowercount; i++) {

                    if(ID ==flowerorderdb[i].flowerID){
                    printf("Çiçek ID: %d\n", flowerorderdb[i].flowerID);
                    printf("Çiçek Adı: %s\n", flowerorderdb[i].name);
                    printf("Çiçek Fiyatı: %.2f\n", flowerorderdb[i].price);
                    printf("Çiçek Türü: %d\n", flowerorderdb[i].type);
                    printf("Çiçek Stok Miktarı: %d\n", flowerorderdb[i].stock);
                    printf("\n");
                    }
                    
                }
                break;
            default:
                printf("Geçersiz seçim. Lütfen geçerli bir seçenek seçin.\n");
        }
    


}
} }
    
    
    
    
    
    
    
    return 0;
}


/*

       /* // Normal kullanıcının işlevselliği burada
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
    }
    */