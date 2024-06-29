#ifndef CUSTOMERADT_H
#define CUSTOMERADT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#ifdef _WIN32
#include <direct.h>  
#else
#include <sys/stat.h> 
#endif

using namespace std;



// [7] Customer Maintenance
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

    const char* customerPath = "./data/customers.txt";   // Text File for Customers
    vector<Customer> customers;                        

    int getNextID();          // Get the next available ID for a new customer
    void loadCustomers();     // Load customers data from file
    void saveCustomers();     // Save customers data to file
};



int CustomerADT::getNextID() {
    return customers.empty() ? 1 : customers.back().id + 1;
}

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



void CustomerADT::saveCustomers() {
#ifdef _WIN32
    _mkdir("./data");    // DIRECTORY
#else
    mkdir("./data", 0777);  
#endif

    ofstream file(customerPath);
    for (const auto& customer : customers) {
        file << customer.id << endl
             << customer.name << endl
             << customer.address << endl;
    }
    file.close();
}



void CustomerADT::addCustomer() {   // [1] Add Customer content
    customers.clear(); 
    loadCustomers();   

    Customer customer;
    customer.id = getNextID();  
    cout << "Add Customer\nName: ";
    cin.ignore();
    getline(cin, customer.name);
    cout << "Address: ";
    getline(cin, customer.address);

    customers.push_back(customer); 
    saveCustomers();  
    cout << "New Customer Added!" << endl;
}



void CustomerADT::showCustomerDetails() {    // [2]  Show Customer Details content
    customers.clear();
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
    customers.clear();
    loadCustomers();  

    for (const auto& customer : customers) {
        cout << "ID: " << customer.id << "\nName: " << customer.name << "\nAddress: " << customer.address << endl;
    }
}

#endif
