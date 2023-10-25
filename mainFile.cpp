
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip> // Include the iomanip header to use setprecision
#include <iomanip> // Include the iomanip header to use setw, setfill, and setprecision

using namespace std;

// Define the structure for an order
struct Order
{
    int orderNumber;
    string customerName;
    string item;
    int quantity;
    double price;
    string date;
};

// Function to calculate the total cost of an order
double calculateTotalCost(const Order &order)
{
    return order.quantity * order.price;
}

// Function to generate a receipt and write it to a file
void generateReceipt(const Order &order)
{
    string filename = "receipts.txt";
    ofstream outFile(filename, ios::app);

    if (outFile.is_open())
    {
        outFile << "Order Number: " << order.orderNumber << endl;
        outFile << "Customer Name: " << order.customerName << endl;
        outFile << "Item: " << order.item << endl;
        outFile << "Quantity: " << order.quantity << endl;
        outFile << "Price per unit: $" << order.price << endl;
        outFile << "Total Cost: $" << calculateTotalCost(order) << endl;
        outFile << "Date: " << order.date << endl;
        outFile << "---------------------------\n";
        outFile << "***************************\n";
        outFile << "---------------------------\n";

        outFile.close();
    }
    else
    {
        cout << "Error: Unable to open the receipt file." << endl;
    }
}

// Function to update and store the total sales in a file
void updateTotalSales(double totalSales)
{
    string filename = "total_sales.txt";
    ofstream outFile(filename);

    if (outFile.is_open())
    {
        outFile << totalSales;
        outFile.close();
    }
    else
    {
        cout << "Error: Unable to update total sales." << endl;
    }
}

// Function to retrieve and display total sales from a file
double retrieveTotalSales()
{
    string filename = "total_sales.txt";
    ifstream inFile(filename);
    double totalSales = 0.0;

    if (inFile.is_open())
    {
        inFile >> totalSales;
        inFile.close();
    }
    else
    {
        cout << "Error: Unable to retrieve total sales." << endl;
    }

    return totalSales;
}

struct MenuItem
{
    string name;
    double price;
};



void displayMenu(const std::vector<MenuItem> &menu)
{
    // Print the header
    cout << left << setw(30) << "Item"
         << "Price" << endl;
    cout << setfill('-') << setw(40) << "" << setfill(' ') << endl;

    // Print menu items
    for (const MenuItem &item : menu)
    {
        cout << left << setw(30) << item.name << "$" << fixed << setprecision(2) << item.price << endl;
    }
};

int main()
{
    int orderNumber = 1;
    vector<Order> orders;
    double totalSales = retrieveTotalSales(); 
    

    // Define a vector of menu items
    std::vector<MenuItem> menu = {
        {"1)Burger", 10.99},
        {"2)Pizza", 12.49},
        {"3)Pasta", 8.99},
        {"4)Salad", 5.99},
    };

    // Display the menu
    displayMenu(menu);

    while (true)
    {   displayMenu(menu);
        cout << "Enter customer name (or 'q' to quit): \n";
        string customerName;
        cin >> customerName;

        if (customerName == "q")
        {
            break;
        }

        Order order;
        order.orderNumber = orderNumber++;
        order.customerName = customerName;
        cout << "Enter item: ";
        cin >> order.item;
        cout << "Enter quantity: ";
        cin >> order.quantity;
        cout << "Enter price per unit: ";
        cin >> order.price;
        cout << "Date:";
        cin >> order.date;

        // Get the current date (you may need to implement this)
        // order.date = "2023-10-24";  // Change this to the actual date

        generateReceipt(order);
        orders.push_back(order);
        totalSales += calculateTotalCost(order);

        updateTotalSales(totalSales);

        cout << "Total Sales: $" << totalSales << endl;
    }

    return 0;
}
