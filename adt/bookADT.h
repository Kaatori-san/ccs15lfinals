#ifndef BOOKADT_H
#define BOOKADT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#ifdef _WIN32
#include <direct.h>  // For _mkdir on Windows, AYAW GUAMANA SA APPLE WTF
#else
#include <sys/stat.h> // For mkdir on Unix/Linux
#endif

using namespace std;

// Book
struct Book {
    int id;             // identifier for the book, so when user checks the book's availability, the code can track if it's been rented or not
    string title;       // Title of the book
    string genre;       // Genre of the book
    string production;  // Production details of the book, like what studio made them etc
    int copies;         // Number of copies 
};

// Declaration of the BookADT class
class BookADT {
public:
    void newBook();                             // new book 
    void rentBook();                            // Rent a book 
    void returnBook();                          // Return a book 
    void showBookDetails();                     // Showss the details of a specific book
    void displayAllBooks();                     // Displays details of all books that has been inputed by the user
    bool checkBookAvailability(const string& title); // Check if a book is available or not, by asking the user to input the book title

    const vector<Book>& getBooks() const;       // Gets the list of all books

private:
    const char* bookPath = "./data/books.txt";  // file storing books data
    vector<Book> books;                         // Vectors to store all books

    int getNextID();                            
    void loadBooks();                           // Load books data from file
    void saveBooks();                           // Save books data to file
};

// Member function definitions

// Get the next available ID for a new book
int BookADT::getNextID() {
    return books.empty() ? 1 : books.back().id + 1;
}

// Load books data from file into memory / text file
void BookADT::loadBooks() {
    ifstream file(bookPath);
    if (!file) return;  // If file cannot be opened, return without loading

    Book book;
    // Read each book's data from file and store in the books vector
    while (file >> book.id >> ws && getline(file, book.title) && getline(file, book.genre) &&
           getline(file, book.production) && file >> book.copies >> ws) {
        books.push_back(book);
    }
    file.close();
}

// Save current books data from memory to file
void BookADT::saveBooks() {
#ifdef _WIN32
    _mkdir("./data");  // Create directory if not exist (Windows)
#else
    mkdir("./data", 0777);  // Create directory if not exist (Unix/Linux)
#endif

    ofstream file(bookPath);
    // Write each book's data from the books vector to file
    for (const auto& book : books) {
        file << book.id << endl
             << book.title << endl
             << book.genre << endl
             << book.production << endl
             << book.copies << endl;
    }
    file.close();
}

// Adds a new book to the system
void BookADT::newBook() {
    loadBooks();  // Load existing books data

    Book book;
    book.id = getNextID();  // Assign next available ID
    // Prompt user for new book details
    cout << "Add New Book\nBook Title: ";
    cin.ignore();
    getline(cin, book.title);
    cout << "Genre: ";
    getline(cin, book.genre);
    cout << "Production: ";
    getline(cin, book.production);
    cout << "Number of Copies: ";
    cin >> book.copies;

    books.push_back(book);  // Add new book to vector
    saveBooks();  // Save updated books data to file
    cout << "New Book Title Added!" << endl;
}

// Rent a book to a customer
void BookADT::rentBook() {
    loadBooks();  // Load existing books data

    string title;
    cout << "Show Book\nBook Title: ";
    cin.ignore();
    getline(cin, title);
    // Search for the book by title in the books vector
    for (auto& book : books) {
        if (book.title == title) {
            // Prompt user to rent the book if available copies exist
            cout << "Book Title Found! Do you want to rent the book? Y/N: ";
            char choice;
            cin >> choice;
            if (choice == 'Y' || choice == 'y') {
                if (book.copies > 0) {
                    book.copies--;  // Decrease available copies
                    saveBooks();  // Save updated books data to file
                    cout << "Book Rented!" << endl;
                } else {
                    cout << "Book Not Available!" << endl;
                }
            }
            return;
        }
    }
    cout << "Book Title Not Found!" << endl;
}

// Return a book from a customer
void BookADT::returnBook() {
    loadBooks();  // Load existing books data

    string title;
    cout << "Return Book\nBook Title: ";
    cin.ignore();
    getline(cin, title);
    // Search for the book by title in the books vector
    for (auto& book : books) {
        if (book.title == title) {
            book.copies++;  // Increase available copies
            saveBooks();  // Save updated books data to file
            cout << "Book Returned!" << endl;
            return;
        }
    }
    cout << "Book Title Not Found!" << endl;
}

// Show details of a specific book
void BookADT::showBookDetails() {
    loadBooks();  // Load existing books data

    string title;
    cout << "Show Book Details\nBook Title: ";
    cin.ignore();
    getline(cin, title);
    // Search for the book by title in the books vector and display details
    for (const auto& book : books) {
        if (book.title == title) {
            cout << "ID: " << book.id << "\nTitle: " << book.title << "\nGenre: " << book.genre
                 << "\nProduction: " << book.production << "\nCopies: " << book.copies << endl;
            return;
        }
    }
    cout << "Book Title Not Found!" << endl;
}

// Display details of all books in the system
void BookADT::displayAllBooks() {
    loadBooks();  // Load existing books data

    for (const auto& book : books) {
        cout << "ID: " << book.id << "\nTitle: " << book.title << "\nGenre: " << book.genre
             << "\nProduction: " << book.production << "\nCopies: " << book.copies << endl;
    }
}

// Check if a book with a given title is available
bool BookADT::checkBookAvailability(const string& title) {
    loadBooks();  // Load existing books data

    // Search for the book by title in the books vector
    for (const auto& book : books) {
        if (book.title == title && book.copies > 0) {
            return true;  // Book found and available
        }
    }
    return false;  // Book not found or not available
}

// Get the vector of all books in the system
const vector<Book>& BookADT::getBooks() const {
    return books;
}

#endif
