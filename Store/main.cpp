#include <iostream>
#include <vector>
#include <iomanip>
#include "product.h"
#include <limits>
using namespace std;    

void showProducts(const std::vector<Product>& products) {
    for (size_t i = 0; i < products.size(); i++) {
        std::cout << i + 1 << ". "
            << std::left << std::setw(10) << products[i].name
            << std::fixed << std::setprecision(2) << products[i].price << " EUR"
            << "   quantity: " << products[i].quantity << "\n";
    }
  
}

void chooseProduct(const std::vector<Product>& products) {

    int productChoice;
    int quantity;


    cout << "Enter product number: " <<endl;
    cin >> productChoice;

    if (productChoice < 1 || productChoice > products.size()) {
        cout << "Invalid product selection.\n";
        return;
    }

    cout << "Enter the quantity you want to buy: ";
    cin >> quantity;

    if (quantity <= 0) {
        cout << "Invalid quantity. Please enter a positive number.\n";
        return;
    }

    if (quantity > products[productChoice - 1].quantity) {
        cout << "Not enough stock available.\n";
        return;
    }

    cout << "You have chosen to buy "
        << quantity << " of "
        << products[productChoice - 1].name << ".\n";
}
void calculateSum(const std::vector<Product>& products) {
    float sum = 0;
    for (size_t i = 0; i < products.size(); i++) {
        sum += products[i].price * products[i].quantity;
    }
    std::cout << "the sum of all purchases is: " << sum;
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
        std::cout << "0. Exit\n";
        std::cout << "Choice: ";

        if (!(std::cin >> choice)) {
            std::cout << "Enter a number.\n";

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            choice = -1;
            continue;
        }

        switch (choice) {
        case 1:
            showProducts(products);
            chooseProduct(products);
            break;
        case 2:
            calculateSum(products);
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
