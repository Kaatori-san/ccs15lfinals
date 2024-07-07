#ifndef CUSTOMERCENTADT_H
#define CUSTOMERCENTADT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "bookADT.h"

#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif

using namespace std;

class CustomerRentADT {
public:
    // Function to wait for user input (press enter)
    void waitForUserInput() {
        cout << "Press enter to continue...";
        cin.ignore();
    }

    // Function to rent a book for a customer
    void rentBook(BookADT& bookADT, int customerId, const string& bookTitle) {
        loadRentals(); // Load existing rental data

        // Check if the book is available
        if (bookADT.checkBookAvailability(bookTitle)) {
            int bookId = -1;
            const auto& books = bookADT.getBooks();

            // Find the ID of the book with the specified title
            for (const auto& book : books) {
                if (book.title == bookTitle) {
                    bookId = book.id;
                    break;
                }
            }

            // If the book ID is found, proceed to rental operations
            if (bookId != -1) {
                // Check if customer already has rentals
                for (auto& rental : rentals) {
                    if (rental.customerId == customerId) {
                        rental.bookIds.push_back(bookId); // Add book ID to existing rental
                        bookADT.rentBookByTitle(bookTitle); // Rent the book in BookADT
                        saveRentals(); // Save updated rentals to file
                        return;
                    }
                }

                // If customer has no rentals yet, create a new rental entry
                Rental newRental;
                newRental.customerId = customerId;
                newRental.bookIds.push_back(bookId); // Add book ID to new rental
                rentals.push_back(newRental); // Add new rental to rentals vector
                bookADT.rentBookByTitle(bookTitle); // Rent the book in BookADT
                saveRentals(); // Save updated rentals to file
            }
        } else {
            cout << "Book Not Available!" << endl;
            waitForUserInput(); // Wait for user to press enter
        }
    }

private:
    // Struct to represent a rental transaction
    struct Rental {
        int customerId; // Customer ID associated with the rental
        vector<int> bookIds; // Vector of book IDs rented by the customer
    };

    const char* rentalPath = "./data/rentals.txt"; // Path to rental data file
    vector<Rental> rentals; // Vector to store all rental transactions

    // Function to load existing rental data from file
    void loadRentals() {
        ifstream file(rentalPath); // Open file for reading
        if (!file) {
            cout << "Unable to open file." << endl;
            return;
        }

        rentals.clear(); // Clear existing rentals vector
        Rental rental; // Temporary storage for reading each rental entry
        string line;
        while (getline(file, line)) {
            if (line.find("Customer ID: ") == 0) {
                rental.customerId = stoi(line.substr(13)); // Extract customer ID
            } else if (line.find("Book IDs: ") == 0) {
                rental.bookIds.clear(); // Clear existing book IDs
                string ids = line.substr(10);
                size_t pos = 0;
                // Parse book IDs separated by commas
                while ((pos = ids.find(",")) != string::npos) {
                    rental.bookIds.push_back(stoi(ids.substr(0, pos)));
                    ids.erase(0, pos + 1);
                }
                // Add last book ID
                if (!ids.empty()) {
                    rental.bookIds.push_back(stoi(ids));
                }
            } else if (line == "---") {
                rentals.push_back(rental); // Add completed rental to rentals vector
            }
        }
        file.close(); // Close file
    }

    // Function to save current rentals to file
    void saveRentals() {
#ifdef _WIN32
        _mkdir("./data"); // Create directory if it doesn't exist (Windows)
#else
        mkdir("./data", 0777); // Create directory if it doesn't exist (Unix-like)
#endif

        ofstream file(rentalPath); // Open file for writing
        if (!file) {
            cout << "Unable to open file." << endl;
            return;
        }

        // Write each rental entry to file
        for (const auto& rental : rentals) {
            file << "Customer ID: " << rental.customerId << '\n'; // Write customer ID
            file << "Book IDs: ";
            for (size_t i = 0; i < rental.bookIds.size(); ++i) {
                file << rental.bookIds[i]; // Write each book ID
                if (i != rental.bookIds.size() - 1) {
                    file << ",";
                }
            }
            file << '\n' << "---\n"; // Mark end of rental entry
        }

        file.close(); // Close file
    }
};

#endif
