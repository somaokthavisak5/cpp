#include <iostream>
#include <vector>
#include <map>
#include <string>

// Define a Product struct
struct Product {
    std::string icon;
    std::string name;
    double price;
};

// Define a Supermarket class
class Supermarket {
public:
    // Constructor
    Supermarket() : dayTotal(0.0) {}

    // ShowMenu displays the supermarket menu
    void showMenu() {
        std::cout << "\nWelcome to supermarket! 👋" << std::endl;
        std::cout << "1. View the products" << std::endl;
        std::cout << "2. Show menu to add to cart" << std::endl;
        std::cout << "3. Add to the cart" << std::endl;
        std::cout << "4. Remove product from cart" << std::endl;
        std::cout << "5. View cart" << std::endl;
        std::cout << "6. Checkout" << std::endl;
        std::cout << "7. Account" << std::endl;
        std::cout << "8. Exit" << std::endl;
    }

    // ViewProducts displays the available products
    void viewProducts() {
        std::cout << "\nAvailable products:" << std::endl;
        int id = 1;
        for (const auto& product : products) {
            std::cout << "Press: " << id << ", Product: " << product.name << ", Price: $" << product.price << std::endl;
            id++;
        }
    }

    // ShowMenuToAdd displays products to add to cart
    void showMenuToAdd() {
        int id = 1;
        for (const auto& product : products) {
            std::cout << "Press: " << id << " to add, Product: " << product.name << ", Price: $" << product.price << " to cart" << std::endl;
            id++;
        }
    }

    // AddToCart adds a product to the cart based on user input
    void addToCart() {
        showMenuToAdd();
        std::cout << "\nEnter the product number to add to cart: ";
        int productID;
        std::cin >> productID;

        if (productID > 0 && productID <= products.size()) {
            cart.push_back(products[productID - 1]);
            std::cout << products[productID - 1].icon << " " << products[productID - 1].name << " has been added to cart" << std::endl;
        } else {
            std::cout << "❌Invalid product number" << std::endl;
        }
    }

    // RemoveFromCart removes a product from the cart based on user input
    void removeFromCart() {
        viewCart();
        std::cout << "Enter the item number to remove from cart: ";
        int itemNum;
        std::cin >> itemNum;

        if (itemNum > 0 && itemNum <= cart.size()) {
            Product removedItem = cart[itemNum - 1];
            cart.erase(cart.begin() + itemNum - 1);
            std::cout << removedItem.icon << " " << removedItem.name << " has been removed from the cart." << std::endl;
        } else {
            std::cout << "❌Invalid item number" << std::endl;
        }
    }

    // ViewCart displays the items in the cart and the total price
    void viewCart() {
        if (cart.empty()) {
            std::cout << "\nYour cart is empty." << std::endl;
            return;
        }

        std::cout << "\nItems in your cart:" << std::endl;
        double total = 0.0;
        for (int idx = 0; idx < cart.size(); idx++) {
            std::cout << idx + 1 << ": " << cart[idx].icon << " " << cart[idx].name << " - $" << cart[idx].price << std::endl;
            total += cart[idx].price;
        }
        std::cout << "\nTotal: $" << total << std::endl;
    }

    // Checkout calculates the total price, clears the cart, and updates the day's total
    void checkout() {
        if (cart.empty()) {
            std::cout << "\nYour cart is empty. Nothing to checkout" << std::endl;
            return;
        }

        double total = 0.0;
        for (const auto& item : cart) {
            total += item.price;
        }

        dayTotal += total;
        std::cout << "\nYour total is $" << total << ". Processing to checkout ..." << std::endl;
        cart.clear();
        std::cout << "\nThank you for shopping with us!" << std::endl;
    }

    // Account displays the total money made today
    void account() {
        std::cout << "Money made today: $" << dayTotal << std::endl;
    }
    // Add a product to the products list
    void addProduct(const Product& product) {
        products.push_back(product);
    }

private:
    std::vector<Product> products;
    std::vector<Product> cart;
    double dayTotal;
};

int main() {
    Supermarket supermarket;

    // Example products
    Product product1 = {"🍎", "Apple", 1.99};
    Product product2 = {"🥛", "Milk", 2.49};
    Product product3 = {"🍞", "Bread", 1.29};

    supermarket.addProduct(product1);
    supermarket.addProduct(product2);
    supermarket.addProduct(product3);

    int choice;
    do {
        supermarket.showMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                supermarket.viewProducts();
                break;
            case 2:
                supermarket.showMenuToAdd();
                break;
            case 3:
                supermarket.addToCart();
                break;
            case 4:
                supermarket.removeFromCart();
                break;
            case 5:
                supermarket.viewCart();
                break;
            case 6:
                supermarket.checkout();
                break;
            case 7:
                supermarket.account();
                break;
            case 8:
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please choose again." << std::endl;
        }
    } while (choice != 8);

    return 0;
}