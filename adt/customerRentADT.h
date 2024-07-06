
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
    void waitForUserInput() {
        cout << "Press enter to continue...";
        cin.ignore();
    }
    void rentBook(BookADT& bookADT, int customerId, const string& bookTitle) {
        loadRentals();

        if (bookADT.checkBookAvailability(bookTitle)) {
            int bookId = -1;
            const auto& books = bookADT.getBooks();

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
                        bookADT.rentBookByTitle(bookTitle);
                        saveRentals();
                        return;
                    }
                }

                Rental newRental;
                newRental.customerId = customerId;
                newRental.bookIds.push_back(bookId);
                rentals.push_back(newRental);
                bookADT.rentBookByTitle(bookTitle);
                saveRentals();
            }
        } else {
            cout << "Book Not Available!" << endl;
            waitForUserInput();
        }
    }

private:
    struct Rental {
        int customerId;
        vector<int> bookIds;
    };

    const char* rentalPath = "./data/rentals.txt";
    vector<Rental> rentals;

    void loadRentals() {
        ifstream file(rentalPath);
        if (!file) {
            cout << "Unable to open file." << endl;
            return;
        }

        rentals.clear();
        Rental rental;
        string line;
        while (getline(file, line)) {
            if (line.find("Customer ID: ") == 0) {
                rental.customerId = stoi(line.substr(13));
            } else if (line.find("Book IDs: ") == 0) {
                rental.bookIds.clear();
                string ids = line.substr(10);
                size_t pos = 0;
                while ((pos = ids.find(",")) != string::npos) {
                    rental.bookIds.push_back(stoi(ids.substr(0, pos)));
                    ids.erase(0, pos + 1);
                }
                if (!ids.empty()) {
                    rental.bookIds.push_back(stoi(ids));
                }
            } else if (line == "---") {
                rentals.push_back(rental);
            }
        }
        file.close();
    }

    void saveRentals() {
#ifdef _WIN32
        _mkdir("./data");
#else
        mkdir("./data", 0777);
#endif

        ofstream file(rentalPath);
        if (!file) {
            cout << "Unable to open file." << endl;
            return;
        }

        for (const auto& rental : rentals) {
            file << "Customer ID: " << rental.customerId << '\n';
            file << "Book IDs: ";
            for (size_t i = 0; i < rental.bookIds.size(); ++i) {
                file << rental.bookIds[i];
                if (i != rental.bookIds.size() - 1) {
                    file << ",";
                }
            }
            file << '\n' << "---\n";
        }

        file.close();
    }
};

#endif
