// customerADT

#ifndef CUSTOMERADT_H
#define CUSTOMERADT_H

#include <iostream>  // Handling input and output operations in the console log
#include <fstream>  // used for reading and writing files. 
#include <string>   // used for handling string data, such as storing book details etc 
#include <vector>   // used to store nad manage the collections of Book in a resizable array-like structure
#include "bookADT.h"  // connects to other ADT files
#include "customerRentADT.h"

#ifdef _WIN32
#include <direct.h> // for windows systems
#else
#include <sys/stat.h>  // for other systems
#endif

using namespace std;

class CustomerADT {
public:
    // add a new customer
    void addCustomer();

    // shows specific details of a customer by their ID
    void showCustomerDetails();

    // Prints every details of all customers in the customers.txt file
    void printAllCustomers();

private:
    // Structure defining a Customer
    struct Customer {
        int id;
        string name;
        string address;
    };

    const char* customerPath = "./data/customers.txt";  // Path to the customer data file
    vector<Customer> customers;  // Vector to store customer records

    // Function to get the next available customer ID
    int getNextID();

    // Function to load customers from file into memory
    bool loadCustomers();

    // Function to save customers from memory to file
    void saveCustomers();

    // Function to append a new customer record to the file
    void appendCustomer(const Customer& customer);

    // Helper function to print error messages
    void printError(const string& msg) {
        cerr << "Error: " << msg << endl;
    }

    // Helper function to wait for user input
    void waitForUserInput() {
        cout << "Press enter to continue...";
        cin.ignore();
    }
};

//  getNextID function
int CustomerADT::getNextID() {
    return customers.empty() ? 1 : customers.back().id + 1;
}

//  loadCustomers function
bool CustomerADT::loadCustomers() {
    ifstream file(customerPath);
    if (!file) {
        printError("Failed to open customers file.");
        return false;  // Return false if file cannot be opened
    }

    customers.clear();
    Customer customer;
    string line;
    while (getline(file, line)) {
        if (line.find("Customer ID: ") == 0) {
            customer.id = stoi(line.substr(13));
        } else if (line.find("Name: ") == 0) {
            customer.name = line.substr(6);
        } else if (line.find("Address: ") == 0) {
            customer.address = line.substr(9);
        } else if (line == "---") {
            customers.push_back(customer);
        }
    }
    file.close();
    return true;  // Return true if customers are loaded successfully
}

//  appendCustomer function - responsible for putting new customer data in the customers.txt
void CustomerADT::appendCustomer(const Customer& customer) {
#ifdef _WIN32
    _mkdir("./data");
#else
    mkdir("./data", 0777);
#endif

    ofstream file(customerPath, ios::app);  // if customer.txt file cannot be opened this is the error message
    if (!file) {
        printError("Unable to open file for writing.");
        return;
    }

    file << "Customer ID: " << customer.id << '\n'    // if file is succesfully read, this shows
         << "Name: " << customer.name << '\n'
         << "Address: " << customer.address << '\n'
         << "---\n";

    file.close();
}

// addCustomer function
void CustomerADT::addCustomer() {
    if (!loadCustomers()) {
        return;  // Exit if loading customers fails
    }

    // Customer Details
    Customer customer;
    customer.id = getNextID();
    cout << "Add Customer\nName: ";
    cin.ignore();
    getline(cin, customer.name);
    cout << "Address: ";
    getline(cin, customer.address);

    customers.push_back(customer);
    appendCustomer(customer);
    cout << "New Customer Added!" << endl;
    waitForUserInput();   // waits for the user to click on the "enter" key.
}

// I showCustomerDetails function
void CustomerADT::showCustomerDetails() {
    if (!loadCustomers()) {
        return;  // Exit if loading customers fails
    }

    int id;
    cout << "Show Customer Details\nCustomer ID: ";
    cin >> id;
    cin.ignore();

    bool found = false;  // tracked whether the user entered an ID that's inside the file
    for (const auto& customer : customers) {  // repeats over each customer in the customers vector
        if (customer.id == id) {   // checks the  customer's ID
            cout << "ID: " << customer.id << "\nName: " << customer.name << "\nAddress: " << customer.address << endl;  // Prints the customer details
            found = true;  // true is to indicate that the ID was found inside the file
            break;
        }
    }

    if (!found) { // checks if the found variable is false. if It's true then the customer ID was found and this section will be skipped.
    // if not, this section will be executed
        cout << "Customer ID Not Found!" << endl;
    }
    waitForUserInput();
}

// printAllCustomers function
void CustomerADT::printAllCustomers() {
    if (!loadCustomers()) {
        return;  // Exit if loading customers fails
    }

    if (customers.empty()) {  // Checks if the 'customers' vector is empty, if it's empty then this print will be shown. 
        cout << "No customers found." << endl;
        return;
    }

    for (const auto& customer : customers) {  // This loop repeats itself over each cusyomer in the 'customers' vector
        cout << "ID: " << customer.id << "\nName: " << customer.name << "\nAddress: " << customer.address << endl;
    }
    waitForUserInput();
    cin.ignore();  // ignores any remaining characters in the input buffer. Ensures that the input operations will work correctly
}

// Implementation of saveCustomers function
void CustomerADT::saveCustomers() {
#ifdef _WIN32   // directory for windows system
    _mkdir("./data");
#else
    mkdir("./data", 0777);    // other operating systems
#endif

    ofstream file(customerPath);  // write to the file that directs to customers.txt
    if (!file) {  // checks if the file stream was successfully opened.
        printError("Unable to open file for writing.");  // if the file could not be opened this prints
        return;  // exits the saveCustomers function
    }

    for (const auto& customer : customers) {
        file << "Customer ID: " << customer.id << '\n'
             << "Name: " << customer.name << '\n'
             << "Address: " << customer.address << '\n'
             << "---\n";
    }

    file.close();
}

#endif
