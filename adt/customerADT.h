#ifndef CUSTOMERADT_H
#define CUSTOMERADT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "bookADT.h"
#include "customerRentADT.h"

#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif

using namespace std;

class CustomerADT {
public:
    void addCustomer();
    void showCustomerDetails();
    void printAllCustomers();

private:
    struct Customer {
        int id;
        string name;
        string address;
    };

    const char* customerPath = "./data/customers.txt";
    vector<Customer> customers;

    int getNextID();
    bool loadCustomers();  // Updated to return bool for error handling
    void saveCustomers();
    void appendCustomer(const Customer& customer);

    // Helper function for error messages
    void printError(const string& msg) {
        cerr << "Error: " << msg << endl;
    }
};

int CustomerADT::getNextID() {
    return customers.empty() ? 1 : customers.back().id + 1;
}

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

void CustomerADT::appendCustomer(const Customer& customer) {
#ifdef _WIN32
    _mkdir("./data");
#else
    mkdir("./data", 0777);
#endif

    ofstream file(customerPath, ios::app);
    if (!file) {
        printError("Unable to open file for writing.");
        return;
    }

    file << "Customer ID: " << customer.id << '\n'
         << "Name: " << customer.name << '\n'
         << "Address: " << customer.address << '\n'
         << "---\n";

    file.close();
}

void CustomerADT::addCustomer() {
    if (!loadCustomers()) {
        return;  // Exit if loading customers fails
    }

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
}

void CustomerADT::showCustomerDetails() {
    if (!loadCustomers()) {
        return;  // Exit if loading customers fails
    }

    int id;
    cout << "Show Customer Details\nCustomer ID: ";
    cin >> id;
    cin.ignore();

    bool found = false;
    for (const auto& customer : customers) {
        if (customer.id == id) {
            cout << "ID: " << customer.id << "\nName: " << customer.name << "\nAddress: " << customer.address << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Customer ID Not Found!" << endl;
    }

    cout << "Press enter to continue...";
    cin.ignore();
}

void CustomerADT::printAllCustomers() {
    if (!loadCustomers()) {
        return;  // Exit if loading customers fails
    }

    if (customers.empty()) {
        cout << "No customers found." << endl;
        return;
    }

    for (const auto& customer : customers) {
        cout << "ID: " << customer.id << "\nName: " << customer.name << "\nAddress: " << customer.address << endl;
    }

    cout << "Press enter to continue...";
    cin.ignore();
}

void CustomerADT::saveCustomers() {
#ifdef _WIN32
    _mkdir("./data");
#else
    mkdir("./data", 0777);
#endif

    ofstream file(customerPath);
    if (!file) {
        printError("Unable to open file for writing.");
        return;
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
