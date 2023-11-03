#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>

using namespace std;

class MenuItem {
public:
    string name;
    double price;

    MenuItem(string _name, double _price) : name(_name), price(_price) {}
};

class Menu {
public:
    vector<MenuItem> items;

    void addMenuItems(const vector<MenuItem>& additionalItems) {
        // Add additional menu items to the common menu
        items.insert(items.end(), additionalItems.begin(), additionalItems.end());
    }

    void display() {
        cout << left << setw(30) << "Item" << "Price" << endl;
        cout << setfill('-') << setw(40) << "" << setfill(' ') << endl;
        for (int i = 0; i < items.size(); ++i) {
            cout << i + 1 << ") " << left << setw(27) << items[i].name << "Rs. " << fixed << setprecision(2) << items[i].price << endl;
        }
    }

    int size() {
        return items.size();
    }

    MenuItem& getItem(int index) {
        return items[index];
    }
};

class Order {
public:
    int orderNumber;
    string customerName;
    vector<MenuItem> items;
    string date;

    Order(int _orderNumber, string _customerName) : orderNumber(_orderNumber), customerName(_customerName) {
        // Get the current date and time
        std::time_t currentTime = std::time(0);
        std::tm* now = std::localtime(&currentTime);
        char buffer[80];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", now);
        date = buffer;
    }

    void addItem(const MenuItem& item) {
        items.push_back(item);
    }

    double calculateTotalCost() const {
        double totalCost = 0.0;
        for (const MenuItem& item : items) {
            totalCost += item.price;
        }
        return totalCost;
    }

    void display() const {
        cout << "Order Number: " << orderNumber << endl;
        cout << "Customer Name: " << customerName << endl;
        cout << "Items in Order:" << endl;
        for (int i = 0; i < items.size(); ++i) {
            cout << i + 1 << ") " << items[i].name << " - Rs. " << fixed << setprecision(2) << items[i].price << endl;
        }
        cout << "Total Cost: Rs. " << fixed << setprecision(2) << calculateTotalCost() << endl;
        cout << "Date: " << date << endl;
    }
};

void generateReceipt(const Order& order) {
    string filename = "receipts.txt";
    ofstream outFile(filename, ios::app);

    if (outFile.is_open()) {
        outFile << "Order Number: " << order.orderNumber << endl;
        outFile << "Customer Name: " << order.customerName << endl;
        outFile << "Items in Order:" << endl;
        for (int i = 0; i < order.items.size(); ++i) {
            outFile << i + 1 << ") " << order.items[i].name << " - Rs. " << fixed << setprecision(2) << order.items[i].price << endl;
        }
        outFile << "Total Cost: Rs. " << fixed << setprecision(2) << order.calculateTotalCost() << endl;
        outFile << "Date: " << order.date << endl;
        outFile << "---------------------------\n";
        outFile << "***************************\n";
        outFile << "---------------------------\n";
        outFile.close();
    } else {
        cout << "Error: Unable to open the receipt file." << endl;
    }
}

int loadOrderNumber() {
    string filename = "order_number.txt";
    ifstream inFile(filename);
    int orderNumber = 1;

    if (inFile.is_open()) {
        inFile >> orderNumber;
        inFile.close();
    }

    return orderNumber;
}

void saveOrderNumber(int orderNumber) {
    string filename = "order_number.txt";
    ofstream outFile(filename);

    if (outFile.is_open()) {
        outFile << orderNumber;
        outFile.close();
    } else {
        cout << "Error: Unable to save order number." << endl;
    }
}

// Define separate sections for menu items
vector<MenuItem> starters = {
    {"Paneer Tikka", 150},
    {"Veg Spring Rolls", 100},
    {"Hara Bhara Kabab", 120},
    // Add more starters
};

vector<MenuItem> mainCourse = {
    {"Paneer Butter Masala", 200},
    {"Veg Biryani", 180},
    {"Dal Makhani", 150},
    // Add more main course items
};

vector<MenuItem> soups = {
    {"Tomato Soup", 80},
    {"Sweet Corn Soup", 90},
    {"Hot and Sour Soup", 100},
    // Add more soups
};

vector<MenuItem> desserts = {
    {"Gulab Jamun", 60},
    {"Rasgulla", 50},
    {"Ice Cream", 70},
    // Add more desserts
};

void displayStarters() {
    cout << "Starters Menu:" << endl;
    for (int i = 0; i < starters.size(); ++i) {
        cout << i + 1 << ") " << starters[i].name << " - Rs. " << fixed << setprecision(2) << starters[i].price << endl;
    }
}

void displayMainCourse() {
    cout << "Main Course Menu:" << endl;
    for (int i = 0; i < mainCourse.size(); ++i) {
        cout << i + 1 << ") " << mainCourse[i].name << " - Rs. " << fixed << setprecision(2) << mainCourse[i].price << endl;
    }
}

void displaySoups() {
    cout << "Soups Menu:" << endl;
    for (int i = 0; i < soups.size(); ++i) {
        cout << i + 1 << ") " << soups[i].name << " - Rs. " << fixed << setprecision(2) << soups[i].price << endl;
    }
}

void displayDesserts() {
    cout << "Desserts Menu:" << endl;
    for (int i = 0; i < desserts.size(); ++i) {
        cout << i + 1 << ") " << desserts[i].name << " - Rs. " << fixed << setprecision(2) << desserts[i].price << endl;
    }
}

int main() {
    vector<Order> orders;
    int orderNumber = loadOrderNumber(); // Load the order number from a file
    double totalSales = 0.0;
    Menu menu;

    // Additional menu items from the second code
    vector<MenuItem> additionalMenuItems;

    // Add the menu items to the corresponding sections
    starters.push_back({"Paneer Tikka", 150});
    mainCourse.push_back({"Paneer Butter Masala", 200});
    soups.push_back({"Tomato Soup", 80});
    desserts.push_back({"Gulab Jamun", 60});

    // Add the menu items to the common menu
    additionalMenuItems.insert(additionalMenuItems.end(), starters.begin(), starters.end());
    additionalMenuItems.insert(additionalMenuItems.end(), mainCourse.begin(), mainCourse.end());
    additionalMenuItems.insert(additionalMenuItems.end(), soups.begin(), soups.end());
    additionalMenuItems.insert(additionalMenuItems.end(), desserts.begin(), desserts.end());

    menu.addMenuItems(additionalMenuItems);

    while (true) {
        cout << "\nRestaurant Management System Menu:\n";
        cout << "1. Display Menu\n";
        cout << "2. Create New Order\n";
        cout << "3. Quit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            displayStarters();
            displayMainCourse();
            displaySoups();
            displayDesserts();
        } else if (choice == 2) {
            cout << "Enter customer name (or 'q' to quit): ";
            string customerName;
            cin >> customerName;

            if (customerName == "q") {
                break;
            }

            Order order(orderNumber++, customerName);
            cout << "Add items to the order (enter section and item number, 0 to finish):\n";
            cout << "Enter the section (1 - Starters, 2 - Main Course, 3 - Soups, 4 - Desserts): ";
            int section;
            while (true) {
                cin >> section;
                if (section == 0) {
                    break;
                } else if (section < 1 || section > 4) {
                    cout << "Invalid section. Please choose a valid section.\n";
                } else {
                    switch (section) {
                        case 1: // Starters
                            displayStarters();
                            break;
                        case 2: // Main Course
                            displayMainCourse();
                            break;
                        case 3: // Soups
                            displaySoups();
                            break;
                        case 4: // Desserts
                            displayDesserts();
                            break;
                    }
                    int itemChoice;
                    cin >> itemChoice;
                    if (itemChoice == 0) {
                        break;
                    }
                    if (itemChoice >= 1 && itemChoice <= additionalMenuItems.size()) {
                        order.addItem(additionalMenuItems[itemChoice - 1]);
                    } else {
                        cout << "Invalid item choice. Please choose a valid item.\n";
                    }
                }
            }

            order.display();
            generateReceipt(order);
            orders.push_back(order);
            totalSales += order.calculateTotalCost();
            saveOrderNumber(orderNumber); // Save the updated order number to a file
        } else if (choice == 3) {
            cout << "Total Sales: Rs. " << fixed << setprecision(2) << totalSales << endl;
            break;
        } else {
            cout << "Invalid choice. Please choose a valid option.\n";
        }
    }

    return 0;
}

