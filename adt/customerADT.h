\
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

    // Check if a customer ID is available
    bool isCustomerIDAvailable(int id);

    void accessCustomers() {
        loadCustomers();
    }
private:
    struct Customer {
        int id;
        string name;
        string address;
    };

    const char* customerPath = "./data/customers.txt";
    vector<Customer> customers;

    int getNextID();

    bool loadCustomers();

    void saveCustomers();

    void appendCustomer(const Customer& customer);

    void printError(const string& msg) {
        cerr << "Error: " << msg << endl;
    }

    void waitForUserInput() {
        cout << "Press enter to continue...";
        cin.ignore();
    }
};

int CustomerADT::getNextID() {
    return customers.empty() ? 1 : customers.back().id + 1;
}

bool CustomerADT::loadCustomers() {
    ifstream file(customerPath);
    if (!file) {
        printError("Failed to open customers file.");
        return false;
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
    return true;
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
        return;
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
    cout <<  "Customer  ID: " << customer.id << endl;
    waitForUserInput();
}

void CustomerADT::showCustomerDetails() {
    if (!loadCustomers()) {
        return;
    }

    int id;
    cout << "Show Customer Details\nCustomer ID: ";

    while (!(cin >> id) || cin.peek() != '\n') {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout << "Invalid Input. Input a Valid Customer ID number: ";
    }
    cin.ignore();

    bool found = false;
    for (const auto& customer : customers) {
        if (customer.id == id) {
            cout << "\n" << "ID: " << customer.id << "\nName: " << customer.name << "\nAddress: " << customer.address << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Customer ID Not Found!" << endl;
    }
    waitForUserInput();
}

void CustomerADT::printAllCustomers() {
    if (!loadCustomers()) {
        return;
    }

    if (customers.empty()) {
        cout << "No customers found." << endl;
        return;
    }

    for (const auto& customer : customers) {
        cout << "ID: " << customer.id << "\nName: " << customer.name << "\nAddress: " << customer.address << "\n-------" << endl;
    }
    waitForUserInput();
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

// Function to check if a customer ID exists
bool CustomerADT::isCustomerIDAvailable(int id) {
    for (const auto& customer : customers) {
        if (customer.id == id) {
            return true;
        }
    }
    return false;
}


#endif
