#include <iostream>
#include <limits>
#include "adt/bookADT.h"
#include "adt/customerADT.h"
#include "adt/customerRentADT.h"

using namespace std;


// Cleas the console screen
void clrscr() {
    cout << "\033[2J\033[1;1H";
}

// Checks the Book Availability
void checkBook(BookADT& myBook) { 
    cout << "Check Book Availability\nBook Title: ";  // Displays this message to promt the user to enter the book title
    cin.ignore();   // Clears any remaining characters in the input buffers, to ensure that the next input is read correctly
    string title;   // Declares a string variable, stores the book title entered by the user
    getline(cin, title);  // reads the entire line of input and stores it in the 'title'
    if (myBook.checkBookAvailability(title)) {  // calls the function checkBookAvailability from bookADT
        cout << "Book Available!" << endl;   // if the method of checkBookAvailability is true, It prints out this message to the user
    } else {
        cout << "Book Not Available!" << endl;  // if the book is not available, this message is displayed
    }
    cout << "Press enter to continue...";   // Waits for the User To Input
    cin.ignore();        // waits for the user to press enter
}
void waitForUserInput() {
    cout << "Press enter to continue...";
    cin.ignore();
}


bool getCustomerId(int &customerId) {  // customer ID verification
    cout << "Enter Customer ID: ";    // Prompts for the user to enter a Customer ID
    cin >> customerId;    // Reads the input from the user and stores it in the 'customerID' variable
    if (cin.fail() || customerId <= 0) {  // checks if the user entred a non-numeric character, also checks if the entered ID is inavlid
        cin.clear();  // Clear the error flag on cin
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard bad input
        cout << "Invalid Customer ID. Please enter a positive integer." << endl;  // Displays an error message, informing the user that the ID is invalid
        waitForUserInput();  
        return false;   // indicates that the input was inavlid
    }
    cin.ignore();    
    return true;     // indicates that input is valid
}


bool getChoice(int &choice) {
    cout << "\tEnter your choice: ";
    cin >> choice;
    if (cin.fail()) {  // checks if the input is invalid
        cin.clear();  // Clear the error flag on cin
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard bad input
        cout << "Invalid input. Please enter an integer." << endl;
        waitForUserInput();
        return false;
    }
    return true;
}


int main() {
    // declare variables
    int choice, subChoice;  // storage for the user manu selections
    int customerId;       // holds the customer ID entered by the user
    BookADT myBook;        // bookADT for managing the books section of the main menu
    CustomerADT myCustomer;    // customerADT for managing customer maintenance sub menu
    CustomerRentADT myRental;  // customerRentADT manages the rentals made by the user

    myBook.accessBooks();   // Loads book Data
    myCustomer.accessCustomers();   // Loads customer Data

    do {  // Main Menu Loop that continues until the user selects to [8] Exit Program
        clrscr();  // clears console screen for better readability

        // Main Menu Options 
        cout << "\t---- Library Management System ----" << endl;
        cout << "\t[1] New Book" << endl;
        cout << "\t[2] Rent a Book" << endl;
        cout << "\t[3] Return a Book" << endl;
        cout << "\t[4] Show Book Details" << endl;
        cout << "\t[5] Display all Books" << endl;
        cout << "\t[6] Check Book Availability" << endl;
        cout << "\t[7] Customer Maintenance" << endl;
        cout << "\t[8] Exit Program" << endl;

        if (!getChoice(choice)) {  // prompts the user to enter their choice. If input is invalid
            continue;  // it continues to the next iteration of the loop with an error handling message informing the user of It's Invalidity.
        }

        switch (choice) {  // Switch Case is used for the Main Menu Options
            case 1: {
                clrscr();
                myBook.newBook();   // cals the function of newBook from bookADT
                break;
            }
            case 2: {
                clrscr();
                
                string bookTitle;  // string variable for the book title
                if (getCustomerId(customerId)) {  // prompts the user to enter their ID
                    if (myCustomer.isCustomerIDAvailable(customerId)) {  // checks if the ID exists in the system
                        cout << "Enter Book Title: ";   // this message shows when ID is true
                        getline(cin, bookTitle);   // reads the entire line netered by the user and stores it in the 'bookTitle' variable
                        myRental.rentBook(myBook, customerId, bookTitle);   /* rents the book 'bookTitle' to customer with the given 'customerID'.
                        'myBook' is passed to the function to allow it to access and modify the book data */
                    } else {  // if the ID is not found
                        cout << "Customer ID Not Found!" << endl;
                        waitForUserInput();
                    }
                } 
                break;  // Exits case and returns to the main menu loop
            }
            case 3: {
                clrscr();
                if (getCustomerId(customerId)) { // prompts the user to enter their ID
                    if (myCustomer.isCustomerIDAvailable(customerId)) {  // Checks if the entered ID exists in the system
                        myBook.returnBook();  // Calls the function returnBook, handles the process of the customer returning the book that they previously rented
                    } else {  // if false, this prints
                        cout << "Customer ID Not Found!" << endl;
                        waitForUserInput();
                    }
                }   
                break;
            }
            case 4: {
                clrscr();
                myBook.showBookDetails();    // cals the function of showBookDetails from bookADT
                break;
            }
            case 5: {
                clrscr();
                myBook.displayAllBooks();    // cals the function of displayAllBooks from bookADT
                break;
            }
            case 6: {
                clrscr();
                checkBook(myBook);    // cals the function of checkBook from bookADT
                break;
            }
            case 7: {
                clrscr();

                // Sub-Menu options
                cout << "\t---- Customer Maintenance ----" << endl;
                cout << "\t[1] Add Customer" << endl;
                cout << "\t[2] Show Customer Details" << endl;
                cout << "\t[3] Show All Customers" << endl;
                cout << "\t[4] Back to Main Menu" << endl;

                if (!getChoice(subChoice)) {  // calls the getChoice function for the user to enter their choice in the sub menu
                    continue;  // if an invalid integer is inputed, the continue statement prints out an error handling message to the user
                }

                switch (subChoice) {  // Switch Case is used for the Sub Menu Options
                    case 1: {
                        clrscr();
                        myCustomer.addCustomer();   // cals the function of addCustomer from customerADT
                        break;
                    }
                    case 2: {
                        clrscr();
                        myCustomer.showCustomerDetails();    // cals the function of showCustomerDetails from customerADT
                        break;
                    }
                    case 3: {
                        clrscr();
                        myCustomer.printAllCustomers();     // cals the function of printAllCustomers from customerADT
                        break;
                    }
                    case 4: {   // handles the option to go back to the main menu. [4] Back to the Main Menu
                        break;  // Exits the sub menu loop and returns to the main menu
                    }
                    default:   // handles invalid input not matching the defined sub menu options
                        cout << "Invalid input. Please try again." << endl;
                        waitForUserInput();
                        cin.ignore();
                        break;
                }
                break;  // Exits the inner switch statement for the Sub Menu
            }
            case 8: {  // Exiting Program
                clrscr();
                cout << "Exiting Program." << endl;
                break;
            }
            default:  // handles invalid input not matching the defined main menu options
                cout << "Invalid input. Please try again." << endl;
                waitForUserInput();
                cin.ignore();
                break;

        }
    } while (choice != 8);   // loop continues to display the main menu until user chooses to Exit the Program

    return 0;  // indicates that the program is successfull 
}
