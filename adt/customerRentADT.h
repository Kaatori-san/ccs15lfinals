#ifndef CUSTOMERCENTADT_H
#define CUSTOMERCENTADT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "bookADT.h"     // Include BookADT header for book operations
#include "customerADT.h" // Include CustomerADT header for customer operations

#ifdef _WIN32
#include <direct.h>  // For _mkdir on Windows
#else
#include <sys/stat.h> // For mkdir on Unix/Linux
#endif

using namespace std;

// Declaration of the CustomerRentADT class
class CustomerRentADT {
public:
    void rentBook(BookADT& bookADT);       // Rent a book for a customer
    void returnBook(BookADT& bookADT);     // Return a book from a customer
    void printCustomerRentals();           // Print all rentals of a specific customer

private:
    // Define a struct to represent a Rental
    struct Rental {
        int customerId;         // ID of the customer
        vector<int> bookIds;    // IDs of books rented by the customer
    };

    const char* rentalPath = "./data/rentals.txt";   // Path to the file storing rental data
    vector<Rental> rentals;                         // Vector to store all rentals

    void loadRentals();     // Load rentals data from file
    void saveRentals();     // Save rentals data to file
};

// Member function definitions

// Load rentals data from file into memory
void CustomerRentADT::loadRentals() {
    ifstream file(rentalPath);
    if (!file) return;  // If file cannot be opened, return without loading

    Rental rental;
    // Read each rental's data from file and store in the rentals vector
    while (file >> rental.customerId) {
        int bookId;
        while (file >> bookId) {
            rental.bookIds.push_back(bookId);
        }
        rentals.push_back(rental);
    }
    file.close();
}

// Save current rentals data from memory to file
void CustomerRentADT::saveRentals() {
#ifdef _WIN32
    _mkdir("./data");  // Create directory if not exist (Windows)
#else
    mkdir("./data", 0777);  // Create directory if not exist (Unix/Linux)
#endif

    ofstream file(rentalPath);
    // Write each rental's data from the rentals vector to file
    for (const auto& rental : rentals) {
        file << rental.customerId;
        for (const auto& bookId : rental.bookIds) {
            file << " " << bookId;
        }
        file << endl;
    }
    file.close();
}

// Rent a book for a customer
void CustomerRentADT::rentBook(BookADT& bookADT) {
    loadRentals();  // Load existing rentals data

    int customerId;
    string bookTitle;
    cout << "Rent Book\nCustomer ID: ";
    cin >> customerId;
    cout << "Book Title: ";
    cin.ignore();
    getline(cin, bookTitle);

    // Check if the book is available and get its ID
    if (bookADT.checkBookAvailability(bookTitle)) {
        int bookId = -1;
        const auto& books = bookADT.getBooks();
        for (const auto& book : books) {
            if (book.title == bookTitle) {
                bookId = book.id;
                break;
            }
        }

        // If book found, update rentals and save data
        if (bookId != -1) {
            for (auto& rental : rentals) {
                if (rental.customerId == customerId) {
                    rental.bookIds.push_back(bookId);
                    bookADT.rentBook();  // Update book availability
                    saveRentals();  // Save updated rentals to file
                    cout << "Book Rented!" << endl;
                    return;
                }
            }

            // If customer has no rentals yet, create new rental entry
            Rental newRental;
            newRental.customerId = customerId;
            newRental.bookIds.push_back(bookId);
            rentals.push_back(newRental);
            bookADT.rentBook();  // Update book availability
            saveRentals();  // Save updated rentals to file
            cout << "Book Rented!" << endl;
        }
    } else {
        cout << "Book Not Available!" << endl;
    }
}

// Return a book from a customer
void CustomerRentADT::returnBook(BookADT& bookADT) {
    loadRentals();  // Load existing rentals data

    int customerId;
    string bookTitle;
    cout << "Return Book\nCustomer ID: ";
    cin >> customerId;
    cout << "Book Title: ";
    cin.ignore();
    getline(cin, bookTitle);

    const auto& books = bookADT.getBooks();
    // Search for customer's rentals and return the book
    for (auto& rental : rentals) {
        if (rental.customerId == customerId) {
            for (auto it = rental.bookIds.begin(); it != rental.bookIds.end(); ++it) {
                for (const auto& book : books) {
                    if (*it == book.id && book.title == bookTitle) {
                        rental.bookIds.erase(it);  // Remove book from rentals
                        bookADT.returnBook();  // Update book availability
                        saveRentals();  // Save updated rentals to file
                        cout << "Book Returned!" << endl;
                        return;
                    }
                }
            }
        }
    }
    cout << "Book Title Not Found in Customer's Rentals!" << endl;
}

// Print all rentals of a specific customer
void CustomerRentADT::printCustomerRentals() {
    loadRentals();  // Load existing rentals data

    int customerId;
    cout << "Print Customer Rentals\nCustomer ID: ";
    cin >> customerId;
    // Search for customer's rentals and print all rented book IDs
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
