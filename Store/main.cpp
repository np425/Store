
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
            << std::fixed << std::setprecision(2)
            << products[i].price << " EUR"
            << "   quantity: " << products[i].quantity << "\n";
    }
}

bool readInt(int& value) {
    if (std::cin >> value) {
        return true;
    }

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return false;
}

bool readDouble(double& value) {
    if (std::cin >> value) {
        return true;
    }

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return false;
}

void chooseProduct(const std::vector<Product>& products) {
    int productChoice;
    int quantity;

    cout << "Enter product number: " << endl;

    if (!readInt(productChoice)) {
        cout << "Enter a number.\n";
        return;
    }

    if (productChoice < 1 || productChoice > products.size()) {
        cout << "Invalid product selection.\n";
        return;
    }

    cout << "Enter the quantity you want to buy: ";

    if (!readInt(quantity)) {
        cout << "Enter a number.\n";
        return;
    }

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

void changePrice(std::vector<Product>& products) {
    showProducts(products);

    int number;
    double newPrice;

    std::cout << "Choose product number: ";

    if (!readInt(number)) {
        std::cout << "Enter a number.\n";
        return;
    }

    if (number < 1 || number > products.size()) {
        std::cout << "Invalid product number!\n";
        return;
    }

    std::cout << "Enter new price: ";

    if (!readDouble(newPrice)) {
        std::cout << "Enter a number.\n";
        return;
    }

    if (newPrice < 0) {
        std::cout << "Price cannot be negative!\n";
        return;
    }

    products[number - 1].price = newPrice;

    std::cout << "Price updated successfully!\n";
}

void cheapestProduct(const std::vector<Product>& products) {
    if (products.size() == 0) std::cout << "No products\n";
    else {
        double cheapestPrice = products[0].price;
        int cheapestNumber = 0;

        for (size_t i = 1; i < products.size(); i++) {
            if (products[i].price < cheapestPrice) {
                cheapestPrice = products[i].price;
                cheapestNumber = i;
            }
        }

        std::cout << "The cheapest product is " << cheapestNumber + 1 << ". "
            << std::left << std::setw(10) << products[cheapestNumber].name
            << std::fixed << std::setprecision(2)
            << products[cheapestNumber].price << " EUR\n";
    }
}

void showStock(const std::vector<Product>& products) {
    showProducts(products);

    std::cout << "Choose product number: ";

    int n;

    if (!readInt(n) || n < 1 || n > (int)products.size()) {
        std::cout << "Invalid product.\n";
        return;
    }

    const Product& p = products[n - 1];

    std::cout << p.name << ": " << p.quantity << " left in stock.\n";
}

void buyProduct(std::vector<Product>& products) {
    showProducts(products);

    std::cout << "Choose product number: ";

    int n;

    if (!readInt(n) || n < 1 || n > (int)products.size()) {
        std::cout << "Invalid product.\n";
        return;
    }

    Product& p = products[n - 1];

    std::cout << "How many " << p.name << " do you want to buy? ";

    int amount;

    if (!readInt(amount) || amount <= 0) {
        std::cout << "Invalid amount.\n";
        return;
    }

    if (amount > p.quantity) {
        std::cout << "Not enough stock. Only " << p.quantity << " left.\n";
        return;
    }

    p.quantity -= amount;

    std::cout << "Bought " << amount << " x " << p.name
        << " for " << std::fixed << std::setprecision(2)
        << amount * p.price << " EUR.\n";

    std::cout << p.name << " left: " << p.quantity << "\n";
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
        std::cout << "2. Show sum of all purchase totals \n";
        std::cout << "3. Cheapest product\n";
        std::cout << "4. Change price\n";
        std::cout << "5. Check stock of a product\n";
        std::cout << "6. Buy a product\n";
        std::cout << "0. Exit\n";
        std::cout << "Choice: ";

        if (!readInt(choice)) {
            std::cout << "Enter a number.\n";
            choice = -1;
            continue;
        }

        switch (choice) {
        case 1:
            showProducts(products);
            chooseProduct(products);
            break;

        case 2:
            std::cout << "Sum of all purchase totals is: ";
            {
                double sum = 0;
                for (size_t i = 0; i < products.size(); i++) {
                    sum += products[i].price * products[i].quantity;
                }
                std::cout << std::fixed << std::setprecision(2) << sum << " EUR\n";
            }
            break;

        case 3:
            cheapestProduct(products);
            break;

        case 4:
            changePrice(products);
            break;

        case 5:
            showStock(products);
            break;

        case 6:
            buyProduct(products);
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