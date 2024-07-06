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

int main() {
    char subChoice, choice;
    BookADT myBook;              
    CustomerADT myCustomer;     
    CustomerRentADT myRental;   

    do {
        clrscr();  
        cout << "\n-----------------------------------------------------" << endl;
        cout << "\t[1] New Book" << endl;
        cout << "\t[2] Rent a Book" << endl;
        cout << "\t[3] Return a Book" << endl;
        cout << "\t[4] Show Book Details" << endl;
        cout << "\t[5] Display all Books" << endl;
        cout << "\t[6] Check Book Availability" << endl;
        cout << "\t[7] Customer Maintenance" << endl;
        cout << "\t[8] Exit Program" << endl;
        cout << "\tEnter your choice: ";

        while (!(cin >> choice) || choice < 1 || choice > 8 || cin.peek() != '\n') {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n-----------------------------------------------------" << endl;
            cout << "Invalid input. Please enter a single digit number between (1-8): ";
        }

        switch (choice) {
            case '1': {
                clrscr();
                myBook.newBook();   
                break;
            }
            case '2': {
                clrscr();
                int customerId;
                string bookTitle;
                cout << "Enter Customer ID: ";

                while (!(cin >> customerId) || cin.peek() != '\n') {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid Input. Input a Valid Customer ID number: ";
                }
                cin.ignore();

                cout << "Enter Book Title: ";
                getline(cin, bookTitle);
                myRental.rentBook(myBook, customerId, bookTitle);  
                break;
            }
            case '3': {
                clrscr();
                myBook.returnBook();   
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
                cout << "\n-----------------------------------------------------" << endl;
                cout << "\t[1] Add Customer" << endl;
                cout << "\t[2] Show Customer Details" << endl;
                cout << "\t[3] Print All Customers" << endl;
                cout << "\t[4] Back to Main Menu" << endl;
                cout << "\tEnter your choice: ";
                
                while (!(cin >> subChoice) || subChoice < 1 || subChoice > 4 || cin.peek() != '\n') {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\n-----------------------------------------------------" << endl;
                    cout << "Invalid input. Please enter a single digit number between (1-4): ";
                }

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
        }
    } while (choice != '8');   

    return 0;
}
