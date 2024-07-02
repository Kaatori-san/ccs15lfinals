#ifndef CUSTOMERCENTADT_H
#define CUSTOMERCENTADT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "bookADT.h" // Including the BookADT header file for book operations

#ifdef _WIN32
#include <direct.h> // for windows
#else
#include <sys/stat.h>  // for unix like systems
#endif

using namespace std;

class CustomerRentADT {
public:
    // Rent a book to a customer
    void rentBook(BookADT& bookADT, int customerId, const string& bookTitle) {
        loadRentals();  // Load existing rental records
        
        // Check if the requested book is available
        if (bookADT.checkBookAvailability(bookTitle)) {
            int bookId = -1;
            const auto& books = bookADT.getBooks();

            // Find the ID of the book by its title
            for (const auto& book : books) {
                if (book.title == bookTitle) {
                    bookId = book.id;
                    break;
                }
            }

            // If the book ID is found
            if (bookId != -1) {
                // Check if the customer already has a rental record
                for (auto& rental : rentals) {
                    if (rental.customerId == customerId) {
                        rental.bookIds.push_back(bookId); // Add the book to the customer's rental
                        bookADT.rentBookByTitle(bookTitle); // Update book availability
                        saveRentals(); // Save the updated rental records
                        cout << "Book Rented!" << endl; // Print confirmation message
                        return;
                    }
                }

                // If no rental record exists for the customer, create a new one
                Rental newRental;
                newRental.customerId = customerId;
                newRental.bookIds.push_back(bookId); // Add the book to the new rental record
                rentals.push_back(newRental); // Add the new rental record to the list
                bookADT.rentBookByTitle(bookTitle); // Update book availability
                saveRentals(); // Save the updated rental records
                cout << "Book Rented!" << endl; // Print confirmation message
            }
        } else {
            cout << "Book Not Available!" << endl; // Print message if book is not available
        }
    }

private:
    struct Rental {
        int customerId; // Customer ID associated with the rental
        vector<int> bookIds; // IDs of books rented by the customer
    };

    const char* rentalPath = "./data/rentals.txt"; // File path for storing rental records
    vector<Rental> rentals; // Vector to store all rental records

    // Load existing rental records from file
    void loadRentals() {
        ifstream file(rentalPath); // Open file for reading
        if (!file) {
            cout << "Unable to open file." << endl; // Print error message if file cannot be opened
            return;
        }

        rentals.clear(); // Clear existing rentals vector
        Rental rental; // Temporary variable to hold rental record
        string line; // String variable to hold each line of the file
        while (getline(file, line)) {
            // Checks if the line contains: Customer ID: 
            if (line.find("Customer ID: ") == 0) {
                // Extract the customer ID from the line starting after "Customer ID: "
                rental.customerId = stoi(line.substr(13));
            }
            //  Checks if the line contains: Book ID:  
            else if (line.find("Book IDs: ") == 0) {
                rental.bookIds.clear(); // Clear existing book IDs

                // Extracts IDs substrings starting right after Book ID:
                string ids = line.substr(10); 
                size_t pos = 0; // Position variable for parsing
                while ((pos = ids.find(",")) != string::npos) {
                    rental.bookIds.push_back(stoi(ids.substr(0, pos))); // Add parsed ID to vector
                    ids.erase(0, pos + 1); // Erase parsed part from substring
                }
                if (!ids.empty()) {
                    rental.bookIds.push_back(stoi(ids)); // Add last ID to vector
                }
            }
            // End of rental record
            else if (line == "---") {
                rentals.push_back(rental); // Add completed rental record to vector
            }
        }
        file.close(); // Close file after reading
    }

    // Save updated rental records to file
    void saveRentals() {
#ifdef _WIN32
        _mkdir("./data"); // Create directory for data storage (Windows)
#else
        mkdir("./data", 0777); // Create directory for data storage (Unix-like systems)
#endif

        ofstream file(rentalPath); // Open file for writing
        if (!file) {  // if the file is not found
            cout << "Unable to open file." << endl; // Print error message if file cannot be opened
            return;
        }

        // Write each rental record to file 
        for (const auto& rental : rentals) {
            file << "Customer ID: " << rental.customerId << '\n'; // Write customer ID to file
            file << "Book IDs: ";
            for (size_t i = 0; i < rental.bookIds.size(); ++i) {
                file << rental.bookIds[i]; // Write each book ID to file
                if (i != rental.bookIds.size() - 1) {
                    file << ","; // Separate book IDs with commas
                }
            }
            file << '\n' << "---\n"; // End of rental record
        }

        file.close(); // Close file after writing
    }
};

#endif
