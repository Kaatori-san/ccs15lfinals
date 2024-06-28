#ifndef CUSTOMERADT_H
#define CUSTOMERADT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#ifdef _WIN32
#include <direct.h>  // For _mkdir on Windows
#else
#include <sys/stat.h> // For mkdir on Unix/Linux
#endif

using namespace std;

// Declaration of the CustomerADT class
class CustomerADT {
public:
    void addCustomer();             // Add a new customer 
    void showCustomerDetails();     // Show details of a specific customer
    void printAllCustomers();       // Print details of all customers inputed in the text file

private:
    // Define a struct to represent a Customer
    struct Customer {
        int id;          // Unique identifier for the customer, starts from 1 to idk
        string name;     // Name of the customer
        string address;  // Address of the customer
    };

    const char* customerPath = "./data/customers.txt";   // Path to the file storing customer data
    vector<Customer> customers;                         // Vector to store all customers

    int getNextID();          // Get the next available ID for a new customer, if 1 is taken, 2 will be given etc
    void loadCustomers();     // Load customers data from file
    void saveCustomers();     // Save customers data to file
};

// Member function definitions

// Get the next available ID for a new customer, 1 taken, 2 given
int CustomerADT::getNextID() {
    return customers.empty() ? 1 : customers.back().id + 1;
}

// Load customers data from file into memory
void CustomerADT::loadCustomers() {
    ifstream file(customerPath);
    if (!file) return;  // If file cannot be opened, return without loading

    Customer customer;
    // Read each customer's data from file and store in the customers vector
    while (file >> customer.id >> ws && getline(file, customer.name) && getline(file, customer.address)) {
        customers.push_back(customer);
    }
    file.close();
}

// Save current customers data from memory to file
void CustomerADT::saveCustomers() {
#ifdef _WIN32
    _mkdir("./data");  // Create directory if not exist (Windows)
#else
    mkdir("./data", 0777);  // Create directory if not exist (Unix/Linux)
#endif

    ofstream file(customerPath);
    // Write each customer's data from the customers vector to file
    for (const auto& customer : customers) {
        file << customer.id << endl
             << customer.name << endl
             << customer.address << endl;
    }
    file.close();
}

// Add a new customer to the system
void CustomerADT::addCustomer() {
    loadCustomers();  // Load existing customers data

    Customer customer;
    customer.id = getNextID();  // Assign next available ID
    // Prompt user for new customer details
    cout << "Add Customer\nName: ";
    cin.ignore();
    getline(cin, customer.name);
    cout << "Address: ";
    getline(cin, customer.address);

    customers.push_back(customer);  // Add new customer to vector
    saveCustomers();  // Save updated customers data to file
    cout << "New Customer Added!" << endl;
}

// Show details of a specific customer
void CustomerADT::showCustomerDetails() {
    loadCustomers();  // Load existing customers data

    int id;
    cout << "Show Customer Details\nCustomer ID: ";
    cin >> id;
    // Search for the customer by ID in the customers vector and display details
    for (const auto& customer : customers) {
        if (customer.id == id) {
            cout << "ID: " << customer.id << "\nName: " << customer.name << "\nAddress: " << customer.address << endl;
            return;
        }
    }
    cout << "Customer ID Not Found!" << endl;
}

// Print details of all customers in the system
void CustomerADT::printAllCustomers() {
    loadCustomers();  // Load existing customers data

    for (const auto& customer : customers) {
        cout << "ID: " << customer.id << "\nName: " << customer.name << "\nAddress: " << customer.address << endl;
    }
}

#endif
