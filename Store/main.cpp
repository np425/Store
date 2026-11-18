 #include <iostream>
#include <vector>
#include <iomanip>
#include "product.h"

void showProducts(const std::vector<Product>& products) {
    for (size_t i = 0; i < products.size(); i++) {
        std::cout << i + 1 << ". "
            << std::left << std::setw(10) << products[i].name
            << std::fixed << std::setprecision(2) << products[i].price << " EUR"
            << "   quantity: " << products[i].quantity << "\n";
    }
}
void removeProduct(std::vector<Product>& products) {
    showProducts(products);

    int num;
    std::cout << "Enter product number to remove: ";
    std::cin >> num;
    if (num < 1 || num >(int)products.size()) {
        std::cout << "No product with that number.\n";
        return;
    }
    products.erase(products.begin() + (num - 1));
    std::cout << "Product removed.\n";
}

int main() {
    std::vector<Product> products = {
        { "Milk", 1.20, 30 },
        { "Bread", 0.95, 15 },
        { "Cheese", 4.50, 8 }
    };

    int choice = -1;
    while (choice != 0) {
        std::cout << "\n=== Store ===\n";
        std::cout << "1. Show products\n";
        std::cout << "2. Remove product\n";
        std::cout << "0. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            showProducts(products);
            break;
        case 2:
            removeProduct(products);
            break;
        case 0:
            std::cout << "Bye!\n";
            break;
        default:
            std::cout << "Unknown option.\n";
        }
    }
    return 0;
}
