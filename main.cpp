#include <iostream>
#include "adt/bookADT.h"
#include "adt/customerADT.h"
#include "adt/customerRentADT.h"
using namespace std;

void clrscr() { 
    cout << "\033[2J\033[1;1H";
    }

int main() {
    int choice;
    BookADT myBook; 
    CustomerADT myCustomer;
    CustomerRentADT myRental;

    do {
        clrscr();
        cout << "[1] New Book" << endl;
        cout << "[2] Rent a Book" << endl;
        cout << "[3] Return a Book" << endl;
        cout << "[4] Show Book Details" << endl;
        cout << "[5] Display all Books" << endl;
        cout << "[6] Check Book Availability" << endl;
        cout << "[7] Customer Maintenance" << endl;
        cout << "[8] Exit Program" << endl;
        cout << "Enter your choice: ";
        cin >> choice; 

        switch (choice) {
            case 1:{
                clrscr();
                myBook.newBook();
                break;
            }
            case 2:{
                clrscr();
                myBook.rentBook();
                break;
            }
            case 3:{
                clrscr();
                myBook.returnBook();
                break;
            }
            case 4:{
                clrscr();
                myBook.showBookDetails();
                break;   
            }
            case 5:{
                clrscr();
                myBook.displayAllBooks();
                break;
            }
            case 6: {
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
                cout << "[1] Add Customer" << endl;
                cout << "[2] Show Customer Details" << endl;
                cout << "[3] Print All Customers" << endl;
                cout << "Enter your choice: ";
                int subChoice;
                cin >> subChoice;
                switch (subChoice) {
                    case 1:
                        myCustomer.addCustomer();
                        break;
                    case 2:
                        myCustomer.showCustomerDetails();
                        break;
                    case 3:
                        myCustomer.printAllCustomers();
                        break;
                    default:
                        cout << "Invalid input. Please try again." << endl;
                }
                break;
            }
            case 8:{
                clrscr();
                cout << "Exiting Program." << endl;
                break;
            }
            default:
                cout << "Invalid input. Please try again." << endl;
        }
    } while (choice != 8);

    return 0;
}
