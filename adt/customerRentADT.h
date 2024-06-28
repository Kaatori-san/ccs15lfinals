#ifndef CUSTOMERCENTADT_H
#define CUSTOMERCENTADT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "bookADT.h"
#include "customerADT.h"
using namespace std;

class CustomerRentADT {
public:
    void rentBook(BookADT& bookADT);
    void returnBook(BookADT& bookADT);
    void printCustomerRentals();

private:
    struct Rental {
        int customerId;
        vector<int> bookIds;
    };

    const char* rentalPath = "./data/rentals.txt";
    vector<Rental> rentals;
    void loadRentals();
    void saveRentals();
};

void CustomerRentADT::loadRentals() {
    ifstream file(rentalPath);
    if (!file) return;

    Rental rental;
    while (file >> rental.customerId) {
        int bookId;
        while (file >> bookId) {
            rental.bookIds.push_back(bookId);
        }
        rentals.push_back(rental);
    }
    file.close();
}

void CustomerRentADT::saveRentals() {
    ofstream file(rentalPath);
    for (const auto& rental : rentals) {
        file << rental.customerId;
        for (const auto& bookId : rental.bookIds) {
            file << " " << bookId;
        }
        file << endl;
    }
    file.close();
}

void CustomerRentADT::rentBook(BookADT& bookADT) {
    loadRentals();
    
    int customerId;
    string bookTitle;
    cout << "Rent Book\nCustomer ID: ";
    cin >> customerId;
    cout << "Book Title: ";
    cin.ignore();
    getline(cin, bookTitle);

    if (bookADT.checkBookAvailability(bookTitle)) {
        int bookId = -1;
        const auto& books = bookADT.getBooks(); // Use the new getter method
        for (const auto& book : books) {
            if (book.title == bookTitle) {
                bookId = book.id;
                break;
            }
        }

        if (bookId != -1) {
            for (auto& rental : rentals) {
                if (rental.customerId == customerId) {
                    rental.bookIds.push_back(bookId);
                    bookADT.rentBook();
                    saveRentals();
                    cout << "Book Rented!" << endl;
                    return;
                }
            }

            Rental newRental;
            newRental.customerId = customerId;
            newRental.bookIds.push_back(bookId);
            rentals.push_back(newRental);
            bookADT.rentBook();
            saveRentals();
            cout << "Book Rented!" << endl;
        }
    } else {
        cout << "Book Not Available!" << endl;
    }
}

void CustomerRentADT::returnBook(BookADT& bookADT) {
    loadRentals();
    
    int customerId;
    string bookTitle;
    cout << "Return Book\nCustomer ID: ";
    cin >> customerId;
    cout << "Book Title: ";
    cin.ignore();
    getline(cin, bookTitle);

    const auto& books = bookADT.getBooks(); // Use the new getter method
    for (auto& rental : rentals) {
        if (rental.customerId == customerId) {
            for (auto it = rental.bookIds.begin(); it != rental.bookIds.end(); ++it) {
                for (const auto& book : books) {
                    if (*it == book.id && book.title == bookTitle) {
                        rental.bookIds.erase(it);
                        bookADT.returnBook();
                        saveRentals();
                        cout << "Book Returned!" << endl;
                        return;
                    }
                }
            }
        }
    }
    cout << "Book Title Not Found in Customer's Rentals!" << endl;
}

void CustomerRentADT::printCustomerRentals() {
    loadRentals();
    int customerId;
    cout << "Print Customer Rentals\nCustomer ID: ";
    cin >> customerId;
    for (const auto& rental : rentals) {
        if (rental.customerId == customerId) {
            cout << "Customer ID: " << rental.customerId << endl;
            for (const auto& bookId : rental.bookIds) {
                cout << "Book ID: " << bookId << endl;
            }
            return;
        }
    }
    cout << "Customer ID Not Found!" << endl;
}

#endif
