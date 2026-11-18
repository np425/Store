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
void calculateSum(const std::vector<Product>& products) {
    float sum = 0;
    for (size_t i = 0; i < products.size(); i++) {
        sum += products[i].price * products[i].quantity;
    }
    std::cout << "the sum of all purchases is: " << sum;
}
void increaseQuantity(std::vector<Product>& products) {
    int increaseAmount;
    int product;
    showProducts(products);
    std::cout << "--------------------- pick the product(via its associated number):  --------------------\n";
    std::cin >> product;
    if (product > 0 && product <= products.size()) {
        std::cout << "enter the quantity you want to add: ";
        std::cin >> increaseAmount;
        if (increaseAmount > 0) {
            products[product - 1].quantity += increaseAmount;
        }
        else {
            std::cout << "not a possible quantity" << std::endl;
        }
    }
    else {
        std::cout << "enter the correct product" << std::endl;
    }
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
        std::cout << "2. Show sum of all purchase totals\n";
        std::cout << "3. Increase a products quantity\n";
        std::cout << "0. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            showProducts(products);
            break;
        case 2:
            calculateSum(products);
            break;
        case 3:
            increaseQuantity(products);
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
