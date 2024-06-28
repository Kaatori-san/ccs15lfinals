#ifndef CUSTOMERADT_H
#define CUSTOMERADT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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
};

int CustomerADT::getNextID() {
    return customers.empty() ? 1 : customers.back().id + 1;
}

void CustomerADT::loadCustomers() {
    ifstream file(customerPath);
    if (!file) return;

    Customer customer;
    while (file >> customer.id >> ws && getline(file, customer.name) && getline(file, customer.address)) {
        customers.push_back(customer);
    }
    file.close();
}

void CustomerADT::saveCustomers() {
    ofstream file(customerPath);
    for (const auto& customer : customers) {
        file << customer.id << endl
             << customer.name << endl
             << customer.address << endl;
    }
    file.close();
}

void CustomerADT::addCustomer() {
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

void CustomerADT::showCustomerDetails() {
    loadCustomers();
    int id;
    cout << "Show Customer Details\nCustomer ID: ";
    cin >> id;
    for (const auto& customer : customers) {
        if (customer.id == id) {
            cout << "ID: " << customer.id << "\nName: " << customer.name << "\nAddress: " << customer.address << endl;
            return;
        }
    }
    cout << "Customer ID Not Found!" << endl;
}

void CustomerADT::printAllCustomers() {
    loadCustomers();
    for (const auto& customer : customers) {
        cout << "ID: " << customer.id << "\nName: " << customer.name << "\nAddress: " << customer.address << endl;
    }
}

#endif
