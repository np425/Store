
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

struct Purchase {
    string productName;
    int quantity;
    double totalPrice;
};
void purchaseHistory(const vector<Purchase>& history) {

    cout << "\n========== PURCHASE HISTORY ==========\n";
    if (history.empty()) {
        cout << "History is empty.\n";
        return;
    }
    double grandTotal = 0;
    for (size_t i = 0; i < history.size(); i++) {
        cout << "\nPurchase #" << i + 1 << "\n";
        cout << "Product: " << history[i].productName << "\n";
        cout << "Quantity: " << history[i].quantity << "\n";
        cout << fixed << setprecision(2);
        cout << "Total: " << history[i].totalPrice << " EUR\n";
        grandTotal += history[i].totalPrice;
    }
    cout << "\n--------------------------------------\n";
    cout << "Grand Total: " << grandTotal << " EUR\n";
}


void chooseProduct(vector<Product>& products,
    vector<Purchase>& history) {
    int productChoice;
    int quantity;
    cout << "Enter product number: ";
    cin >> productChoice;
    if (productChoice < 1 || productChoice > products.size()) {
        cout << "Invalid product selection.\n";
        return;
    }
    cout << "Enter quantity: ";
    cin >> quantity;

    if (quantity <= 0) {
        cout << "Invalid quantity.\n";
        return;
    }
    if (quantity > products[productChoice - 1].quantity) {
        cout << "Not enough stock available.\n";
        return;
    }

    // Calculate total price
    double totalPrice =
        products[productChoice - 1].price * quantity;

    // Reduce stock
    products[productChoice - 1].quantity -= quantity;

    // Save purchase in history
    history.push_back({
        products[productChoice - 1].name,
        quantity,
        totalPrice
        });

    cout << "\nPurchase successful!\n";

    cout << "Product: "
        << products[productChoice - 1].name << "\n";

    cout << "Total: " << fixed << setprecision(2)
        << totalPrice << " EUR\n";
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

int main() {

    std::vector<Product> products = {
        { "Milk", 1.20, 30 },
        { "Bread", 0.95, 15 },
        { "Cheese", 4.50, 8 }
    };
    vector<Purchase> history;
    int choice = -1;

    while (choice != 0) {
        std::cout << "\n=== Store ===\n";
        std::cout << "1. Show products\n";
        std::cout << "2. Purchase products\n";
        cout << "3. Purchase history\n";
        std::cout << "4. Change price\n";
        std::cout << "5. Check stock of a product\n";
        std::cout << "6. Buy a product\n";
        std::cout << "7. Show sum of all purchase totals \n";
        std::cout << "8. Cheapest product\n";
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
            break;
        case 2:
            showProducts(products);
            chooseProduct(products, history);
            break;
        case 3:
            purchaseHistory(history);
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