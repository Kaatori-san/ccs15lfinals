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
    void loadCustomers();     
    void saveCustomers();    
    void appendCustomer(const Customer& customer); // Function to append a new customer to the file
};

int CustomerADT::getNextID() {
    return customers.empty() ? 1 : customers.back().id + 1;
}

void CustomerADT::loadCustomers() {
    ifstream file(customerPath);
    if (!file) return;  

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
            customers.push_back(customer); // Add the customer to the vector
        }
    }
    file.close();
}

void CustomerADT::addCustomer() {   // [1] Add Customer content
    loadCustomers();   

    Customer customer;
    customer.id = getNextID();  
    cout << "Add Customer\nName: ";
    cin.ignore();
    getline(cin, customer.name);
    cout << "Address: ";
    getline(cin, customer.address);

    customers.push_back(customer); 
    appendCustomer(customer); // Append the new customer to the file
    cout << "New Customer Added!" << endl;
}

void CustomerADT::showCustomerDetails() {    // [2]  Show Customer Details content
    loadCustomers();  
    
    int id;
    cout << "Show Customer Details\nCustomer ID: ";
    cin >> id;
    cin.ignore();
    // Search for the customer by ID in the customers vector and display details
    for (const auto& customer : customers) {
        if (customer.id == id) {
            cout << "ID: " << customer.id << "\nName: " << customer.name << "\nAddress: " << customer.address << endl;
            return;
        }
    }
    cout << "Customer ID Not Found!" << endl;
}

void CustomerADT::printAllCustomers() {     // [3] Print All Customers content
    loadCustomers();  

    for (const auto& customer : customers) {
        cout << "ID: " << customer.id << "\nName: " << customer.name << "\nAddress: " << customer.address << endl;
    }
}

void CustomerADT::saveCustomers() {
#ifdef _WIN32
    _mkdir("./data");    // DIRECTORY
#else
    mkdir("./data", 0777);  
#endif

    ofstream file(customerPath);
    for (const auto& customer : customers) {
        file << "Customer ID: " << customer.id << '\n'
             << "Name: " << customer.name << '\n'
             << "Address: " << customer.address << '\n'
             << "---\n";  // Separator between customers
    }
    file.close();
}

#endif
