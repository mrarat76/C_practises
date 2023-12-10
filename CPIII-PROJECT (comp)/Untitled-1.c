#include <stdio.h>
#include <stdlib.h>

int main() {
    // Initialize the flower database
    initializeFlowerDatabase();

    // Add some flowers
    addFlower(1, "Red Rose", 2.99, ROSE);
    addFlower(2, "Tulip", 1.99, TULIP);
    addFlower(3, "White Lily", 3.49, LILY);

    // Test various operations
    findFlower(2);
    updateFlower(2, "Yellow Tulip", 1.49, TULIP);
    deleteFlower(1);

    // Summarize flower sales
    summarizeFlowerSales();

    return 0;
}
