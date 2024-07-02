#include <iostream>
#include "adt/bookADT.h"
#include "adt/customerADT.h"
#include "adt/customerRentADT.h"

using namespace std;

// Function to clear the console screen
void clrscr() {
    cout << "\033[2J\033[1;1H";
}

int main() {
    int choice;
    BookADT myBook;              // BookADT class
    CustomerADT myCustomer;      // CustomerADT class
    CustomerRentADT myRental;    // CustomerRentADT class

    do {
        clrscr();   // Clear the console screen
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
        cin >> choice;  // Read user's choice

        switch (choice) {
            case 1: {
                clrscr();
                myBook.newBook();   // Call function to add a new book
                break;
            }
            case 2: {
                clrscr();
                int customerId;
                string bookTitle;
                cout << "Enter Customer ID: ";
                cin >> customerId;
                cout << "Enter Book Title: ";
                cin.ignore();   // Ignore any leftover newline characters
                getline(cin, bookTitle);
                myRental.rentBook(myBook, customerId, bookTitle);  // Rent a book for a customer
                break;
            }
            case 3: {
                clrscr();
                myBook.returnBook();   // Call function to return a book
                break;
            }
            case 4: {
                clrscr();
                myBook.showBookDetails();   // Call function to show details of a book
                break;
            }
            case 5: {
                clrscr();
                myBook.displayAllBooks();   // Call function to display all books
                break;
            }
            case 6: {
                clrscr();
                cout << "Check Book Availability\nBook Title: ";
                cin.ignore();   // Ignore any leftover newline characters
                string title;
                getline(cin, title);
                if (myBook.checkBookAvailability(title)) {
                    cout << "Book Available!" << endl;   // Check if a book is available for rent
                } else {
                    cout << "Book Not Available!" << endl;
                }
                cout << "Press enter to continue...";
                cin.ignore();   // Wait for user to press enter before returning to menu
                break;
            }
            case 7: {
                clrscr();
                // Sub-menu for customer maintenance options
                cout << "[1] Add Customer" << endl;
                cout << "[2] Show Customer Details" << endl;
                cout << "[3] Print All Customers" << endl;
                cout << "Enter your choice: ";
                int subChoice;
                cin >> subChoice;
                switch (subChoice) {
                    case 1:
                        myCustomer.addCustomer();    // Call function to add a new customer
                        break;
                    case 2:
                        myCustomer.showCustomerDetails();    // Call function to show details of a customer
                        break;
                    case 3:
                        myCustomer.printAllCustomers();     // Call function to print all customers
                        break;
                    default:
                        cout << "Invalid input. Please try again." << endl;
                }
                break;
            }
            case 8: {
                clrscr();
                cout << "Exiting Program." << endl;
                break;
            }
            default:
                cout << "Invalid input. Please try again." << endl;
        }
    } while (choice != 8);   // Repeat until the user chooses to exit

    return 0;
}
