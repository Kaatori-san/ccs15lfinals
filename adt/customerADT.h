#ifndef CUSTOMERADT_H
#define CUSTOMERADT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "bookADT.h"         // Include header for BookADT class
#include "customerRentADT.h" // Include header for CustomerRentADT class

#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif

using namespace std;

class CustomerADT {
public:
    void addCustomer();             // Function to add a new customer
    void showCustomerDetails();     // Function to display details of a customer
    void printAllCustomers();       // Function to print details of all customers

    // Check if a customer ID is available
    bool isCustomerIDAvailable(int id);

    void accessCustomers() {        // Function to access customers (loads them)
        loadCustomers();
    }

private:
    struct Customer {               // Structure defining the Customer data
        int id;                     // Customer ID
        string name;                // Customer name
        string address;             // Customer address
    };

    const char* customerPath = "./data/customers.txt"; // Path to customer data file
    vector<Customer> customers;    // Vector to store all customers

    int getNextID();               // Function to get the next available customer ID
    bool loadCustomers();          // Function to load customers from file
    void saveCustomers();          // Function to save customers to file
    void appendCustomer(const Customer& customer); // Function to append a customer to file
    void printError(const string& msg) { // Function to print error messages
        cerr << "Error: " << msg << endl;
    }
    void waitForUserInput() {      // Function to wait for user input (press enter)
        cout << "Press enter to continue...";
        cin.ignore();
    }
};

int CustomerADT::getNextID() {
    return customers.empty() ? 1 : customers.back().id + 1; // Return the next ID (increment last ID if not empty)
}

bool CustomerADT::loadCustomers() {
    ifstream file(customerPath); // Open file for reading
    if (!file) {                 // Check if file open failed
        printError("Failed to open customers file."); // Print error message
        return false;            // Return false indicating failure
    }

    customers.clear();           // Clear the existing customers vector
    Customer customer;           // Temporary variable to store each customer
    string line;                 // String to read each line from file
    while (getline(file, line)) { // Read each line from file
        if (line.find("Customer ID: ") == 0) { // Check if line contains Customer ID
            customer.id = stoi(line.substr(13)); // Extract and convert ID from string
        } else if (line.find("Name: ") == 0) { // Check if line contains Name
            customer.name = line.substr(6);   // Extract name from string
        } else if (line.find("Address: ") == 0) { // Check if line contains Address
            customer.address = line.substr(9);    // Extract address from string
        } else if (line == "---") {       // Check for end of customer record
            customers.push_back(customer); // Add customer to vector
        }
    }
    file.close(); // Close file
    return true;  // Return true indicating success
}

void CustomerADT::appendCustomer(const Customer& customer) {
#ifdef _WIN32
    _mkdir("./data"); // Create directory on Windows
#else
    mkdir("./data", 0777); // Create directory on Unix-like systems
#endif

    ofstream file(customerPath, ios::app); // Open file for appending
    if (!file) { // Check if file open failed
        printError("Unable to open file for writing."); // Print error message
        return;    // Return indicating failure
    }

    // Append customer details to file
    file << "Customer ID: " << customer.id << '\n'
         << "Name: " << customer.name << '\n'
         << "Address: " << customer.address << '\n'
         << "---\n";

    file.close(); // Close file
}

void CustomerADT::addCustomer() {
    if (!loadCustomers()) { // Load customers from file, return if failed
        return;
    }

    Customer customer; // Create new customer object
    customer.id = getNextID(); // Get next available customer ID
    cout << "Add Customer\nName: "; // Prompt user for name
    cin.ignore();  // Ignore any remaining characters in input buffer
    getline(cin, customer.name); // Get customer name
    cout << "Address: "; // Prompt user for address
    getline(cin, customer.address); // Get customer address

    customers.push_back(customer); // Add customer to vector
    appendCustomer(customer);      // Append customer to file
    cout << "New Customer Added!" << endl; // Print success message
    cout << "Customer ID: " << customer.id << endl; // Print customer ID
    waitForUserInput(); // Wait for user input
}

void CustomerADT::showCustomerDetails() {
    if (!loadCustomers()) { // Load customers from file, return if failed
        return;
    }

    int id; // Variable to store customer ID
    cout << "Show Customer Details\nCustomer ID: "; // Prompt for customer ID

    while (!(cin >> id) || cin.peek() != '\n') { // Validate input as integer
        cin.clear();  // Clear error state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
        cout << "Invalid Input. Input a Valid Customer ID number: "; // Prompt for valid ID
    }
    cin.ignore(); // Ignore newline character in input buffer

    bool found = false; // Flag to indicate if customer is found
    for (const auto& customer : customers) { // Iterate through customers vector
        if (customer.id == id) { // Check if customer ID matches
            cout << "\nID: " << customer.id << "\nName: " << customer.name << "\nAddress: " << customer.address << endl; // Display customer details
            found = true; // Set flag to true indicating customer found
            break; // Exit loop since customer is found
        }
    }

    if (!found) { // If customer not found
        cout << "Customer ID Not Found!" << endl; // Print error message
    }
    waitForUserInput(); // Wait for user input
}

void CustomerADT::printAllCustomers() {
    if (!loadCustomers()) { // Load customers from file, return if failed
        return;
    }

    if (customers.empty()) { // Check if customers vector is empty
        cout << "No customers found." << endl; // Print message if no customers found
        return;
    }

    for (const auto& customer : customers) { // Iterate through customers vector
        cout << "ID: " << customer.id << "\nName: " << customer.name << "\nAddress: " << customer.address << "\n-------" << endl; // Display customer details
    }
    waitForUserInput(); // Wait for user input
    cin.ignore();       // Ignore any remaining characters in input buffer
}

void CustomerADT::saveCustomers() {
#ifdef _WIN32
    _mkdir("./data"); // Create directory on Windows
#else
    mkdir("./data", 0777); // Create directory on Unix-like systems
#endif

    ofstream file(customerPath); // Open file for writing
    if (!file) { // Check if file open failed
        printError("Unable to open file for writing."); // Print error message
        return;    // Return indicating failure
    }

    for (const auto& customer : customers) { // Iterate through customers vector
        file << "Customer ID: " << customer.id << '\n'
             << "Name: " << customer.name << '\n'
             << "Address: " << customer.address << '\n'
             << "---\n"; // Write customer details to file
    }

    file.close(); // Close file
}

// Function to check if a customer ID exists
bool CustomerADT::isCustomerIDAvailable(int id) {
    for (const auto& customer : customers) { // Iterate through customers vector
        if (customer.id == id) { // Check if customer ID matches
            return true; // Return true indicating customer ID exists
        }
    }
    return false; // Return false indicating customer ID does not exist
}

#endif // End of CUSTOMERADT_H header guard
