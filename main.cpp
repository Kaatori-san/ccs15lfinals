#include <iostream>
#include <limits>
#include "adt/bookADT.h"
#include "adt/customerADT.h"
#include "adt/customerRentADT.h"

using namespace std;

void clrscr() {
    cout << "\033[2J\033[1;1H";
}

void checkBook(BookADT& myBook) {
    cout << "Check Book Availability\nBook Title: ";
    cin.ignore();   
    string title;
    getline(cin, title);
    if (myBook.checkBookAvailability(title)) {
        cout << "Book Available!" << endl;
    } else {
        cout << "Book Not Available!" << endl;
    }
    cout << "Press enter to continue...";
    cin.ignore();   
}
void waitForUserInput() {
    cout << "Press enter to continue...";
    cin.ignore();
}
bool getCustomerId(int &customerId) {
    cout << "Enter Customer ID: ";
    cin >> customerId;
    if (cin.fail() || customerId <= 0) {
        cin.clear();  // Clear the error flag on cin
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard bad input
        cout << "Invalid Customer ID. Please enter a positive integer." << endl;
        waitForUserInput();
        return false;
    }
    cin.ignore();
    return true;
}
int main() {
    // declare variables
    char choice, subChoice;
    int customerId;
    BookADT myBook;              
    CustomerADT myCustomer;     
    CustomerRentADT myRental;

    myBook.accessBooks();
    myCustomer.accessCustomers();
    do {
        clrscr();  
        cout << "\t---- Library Management System ----" << endl;
        cout << "\t[1] New Book" << endl;
        cout << "\t[2] Rent a Book" << endl;
        cout << "\t[3] Return a Book" << endl;
        cout << "\t[4] Show Book Details" << endl;
        cout << "\t[5] Display all Books" << endl;
        cout << "\t[6] Check Book Availability" << endl;
        cout << "\t[7] Customer Maintenance" << endl;
        cout << "\t[8] Exit Program" << endl;
        cout << "\tEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case '1': {
                clrscr();
                myBook.newBook();   
                break;
            }
            case '2': {
                clrscr();
                
                string bookTitle;
                if (getCustomerId(customerId)) {
                    if (myCustomer.isCustomerIDAvailable(customerId)) {
                        cout << "Enter Book Title: ";
                        getline(cin, bookTitle);
                        myRental.rentBook(myBook, customerId, bookTitle); 
                    } else {
                        cout << "Customer ID Not Found!" << endl;
                        waitForUserInput();
                    }
                } 
                break;
            }
            case '3': {
                clrscr();
                if (getCustomerId(customerId)) {
                    if (myCustomer.isCustomerIDAvailable(customerId)) {
                        myBook.returnBook(); 
                    } else {
                        cout << "Customer ID Not Found!" << endl;
                        waitForUserInput();
                    }
                }   
                break;
            }
            case '4': {
                clrscr();
                myBook.showBookDetails();   
                break;
            }
            case '5': {
                clrscr();
                myBook.displayAllBooks();   
                break;
            }
            case '6': {
                clrscr();
                checkBook(myBook);   
                break;
            }
            case '7': {
                clrscr();
                cout << "\t---- Customer Maintenance ----" << endl;
                cout << "\t[1] Add Customer" << endl;
                cout << "\t[2] Show Customer Details" << endl;
                cout << "\t[3] Show All Customers" << endl;
                cout << "\t[4] Back to Main Menu" << endl;
                cout << "\tEnter your choice: ";
                cin >> subChoice;

                switch (subChoice) {
                    case '1': {
                        clrscr();
                        myCustomer.addCustomer();   
                        break;
                    }
                    case '2': {
                        clrscr();
                        myCustomer.showCustomerDetails();    
                        break;
                    }
                    case '3': {
                        clrscr();
                        myCustomer.printAllCustomers();     
                        break;
                    }
                    case '4': {   
                        break;
                    }
                    default:
                        cout << "Invalid input. Please try again." << endl;
                        waitForUserInput();
                        cin.ignore();
                        break;
                }
                break;
            }
            case '8': {
                clrscr();
                cout << "Exiting Program." << endl;
                break;
            }
            default:
                cout << "Invalid input. Please try again." << endl;
                waitForUserInput();
                cin.ignore();
                break;

        }
    } while (choice != '8');   

    return 0;
}
