
#include <iostream>
#include <vector>
#include <iomanip>
#include "product.h"
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

void changePrice(std::vector<Product>& products) {
    showProducts(products);

    int number;
    double newPrice;

    std::cout << "Choose product number: ";
    std::cin >> number;

    if (number < 1 || number > products.size()) {
        std::cout << "Invalid product number!\n";
        return;
    }

    std::cout << "Enter new price: ";
    std::cin >> newPrice;

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
            << std::fixed << std::setprecision(2) << products[cheapestNumber].price << " EUR\n";
    }
}

bool readInt(int& value) {
    if (std::cin >> value) return true;
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    return false;
}

void showStock(const std::vector<Product>& products) {
    showProducts(products);
    std::cout << "Choose product number: ";
    int n;
    if (!readInt(n) || n < 1 || n >(int)products.size()) {
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
    if (!readInt(n) || n < 1 || n >(int)products.size()) {
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
        std::cout << "7. Increase a products quantity\n";
        std::cout << "2. Show sum of all purchase totals \n";
        std::cout << "3. Cheapest product\n";
        std::cout << "4. Change price\n";
        std::cout << "5. Check stock of a product\n";
        std::cout << "6. Buy a product\n";
        std::cout << "0. Exit\n";
        std::cout << "Choice: ";

        if (!readInt(choice)) {
            std::cout << "Please enter a number.\n";
            choice = -1;
            continue;
        }

        switch (choice) {
        case 1:
            showProducts(products);
            chooseProduct(products);
            break;
        case 2:
            changePrice(products);
            break;
        case 3:
            cheapestProduct(products);
            break;
          case 4:
            changePrice(products);
            break;
        case 3:
            increaseQuantity(products);
            break;
        case 0:
            std::cout << "Bye!\n";
            break;
        case 5: showStock(products); break;
        case 6: buyProduct(products); break;
        default:
            std::cout << "Unknown option.\n";
        }
    }

    return 0;
}