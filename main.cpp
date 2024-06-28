#include <iostream>
#include "adt/bookADT.h"
#include "adt/customerADT.h"
#include "adt/customerRentADT.h"
using namespace std;

int main() {
    int choice;
    BookADT myBook;                  // BookADT to manage books
    CustomerADT myCustomer;          // CustomerADT to manage customers
    CustomerRentADT myRental;        // CustomerRentADT to manage rentals

    // Main menu loop
    do {
        // Display main menu options
        cout << "[1] New Book" << endl;
        cout << "[2] Rent a Book" << endl;
        cout << "[3] Return a Book" << endl;
        cout << "[4] Show Book Details" << endl;
        cout << "[5] Display all Books" << endl;
        cout << "[6] Check Book Availability" << endl;
        cout << "[7] Customer Maintenance" << endl;
        cout << "[8] Exit Program" << endl;
        cout << "Enter your choice: ";
        cin >> choice;  // Input user choice

        // Process user choice using switch statement
        switch (choice) {
            case 1: {
                // Add a new book
                myBook.newBook();
                break;
            }
            case 2: {
                // Rent a book
                myRental.rentBook(myBook);
                break;
            }
            case 3: {
                // Return a rented book
                myRental.returnBook(myBook);
                break;
            }
            case 4: {
                // Show details of a specific book
                myBook.showBookDetails();
                break;
            }
            case 5: {
                // Display details of all books
                myBook.displayAllBooks();
                break;
            }
            case 6: {
                // Check availability of a book 
                cout << "Check Book Availability\nBook Title: ";
                cin.ignore();
                string title;
                getline(cin, title);
                if (myBook.checkBookAvailability(title)) {
                    cout << "Book Available!" << endl;
                } else {
                    cout << "Book Not Available!" << endl;
                }
                break;
            }
            case 7: {
                // Customer maintenance submenu
                cout << "[1] Add Customer" << endl;
                cout << "[2] Show Customer Details" << endl;
                cout << "[3] Print All Customers" << endl;
                cout << "Enter your choice: ";
                int subChoice;
                cin >> subChoice;
                switch (subChoice) {
                    case 1: {
                        // Add a new customer
                        myCustomer.addCustomer();
                        break;
                    }
                    case 2: {
                        // Show details of a specific customer
                        myCustomer.showCustomerDetails();
                        break;
                    }
                    case 3: {
                        // Print details of all customers
                        myCustomer.printAllCustomers();
                        break;
                    }
                    default:
                        cout << "Invalid input. Please try again." << endl;
                }
                break;
            }
            case 8:
                // Exit the program
                cout << "Exit Program" << endl;
                break;
            default:
                // Handle invalid input
                cout << "Invalid input. Please try again." << endl;
        }
    } while (choice != 8);  // Repeat until user chooses to exit

    return 0;
}
