#include <stdio.h>

struct Car {
    int speed;
    int price;
    char model[50];
    struct Driver driver;
    
    
};

struct Driver {
    char type[50];
    int unitSalary;
    int duration;
   
};

int CalculateTotalPAYMENT(Car car){
   if(car.driver-> type=='B') {
    return car.driver->unitSalary * car.driver -> duration;
   
   }


   else {
    return 0;

   }




}

int main() {
    struct Car cars[3] = {
        {100, 2400, "Toyota"},
        {150, 2300, "Honda"},
        {200, 2800, "BMW"}
    };

    for (int i = 0; i < 3; i++) {
        printf("Car %d is a %s, its speed is %d km/h, and its price is $%d.\n",
               i + 1, cars[i].model, cars[i].speed, cars[i].price);
    }

    int sum=0;
    for (int i=0; i<3; i++){
    sum=sum+cars[i].price;
    }
    printf("The total price of the cars is $%d.\n", sum);

   struct Driver drivers [3]{
    {"A", 100, 10},
    {"B", 200, 20},
    {"C", 300, 30}
   };

   for (int i = 0; i < 3; i++)
   {
    cars[i].driver=drivers[i];
   }
   
   
    
    
    
  
    return 0;
}
