#ifndef BOOKADT_H
#define BOOKADT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#ifdef _WIN32
#include <direct.h>  // For _mkdir on Windows
#else
#include <sys/stat.h> // For mkdir on Unix/Linux
#endif

using namespace std;

// Book structure
struct Book {
    int id;
    string title;
    string genre;
    string publisher;
    int copies;
};

// BookADT class declaration
class BookADT {
public:
    void newBook() {
        loadBooks();  // Load existing books data

        Book book;
        book.id = getNextID();  // Assign next available ID
        // Prompt user for new book details
        cout << "Add New Book\nBook Title: ";
        cin.ignore();
        getline(cin, book.title);
        cout << "Genre: ";
        getline(cin, book.genre);
        cout << "Publisher: ";
        getline(cin, book.publisher);
        cout << "Number of Copies: ";
        cin >> book.copies;

        books.push_back(book);  // Add new book to vector
        saveBooks();  // Save updated books data to file
        cout << "New Book Added!" << endl;
    }

    void rentBook() {
        loadBooks();  // Load existing books data

        string title;
        cout << "Rent Book\nBook Title: ";
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

    void returnBook() {
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

    void showBookDetails() {
        loadBooks();  // Load existing books data

        string title;
        cout << "Show Book Details\nBook Title: ";
        cin.ignore();
        getline(cin, title);
        // Search for the book by title in the books vector and display details
        for (const auto& book : books) {
            if (book.title == title) {
                cout << "ID: " << book.id << "\nTitle: " << book.title << "\nGenre: " << book.genre
                     << "\nPublisher: " << book.publisher << "\nCopies: " << book.copies << endl;
                return;
            }
        }
        cout << "Book Title Not Found!" << endl;
    }

    void displayAllBooks() {
        loadBooks();  // Load existing books data

        for (const auto& book : books) {
            cout << "ID: " << book.id << "\nTitle: " << book.title << "\nGenre: " << book.genre
                 << "\nPublisher: " << book.publisher << "\nCopies: " << book.copies << endl;
        }
    }

    bool checkBookAvailability(const string& title) {
        loadBooks();  // Load existing books data

        // Search for the book by title in the books vector
        for (const auto& book : books) {
            if (book.title == title && book.copies > 0) {
                return true;  // Book found and available
            }
        }
        return false;  // Book not found or not available
    }

    const vector<Book>& getBooks() const {
        return books;
    }

private:
    const char* bookPath = "./data/books.txt";  // File storing books data
    vector<Book> books;                         // Vector to store all books

    int getNextID() {
        return books.empty() ? 1 : books.back().id + 1;
    }

    void loadBooks() {
        ifstream file(bookPath);
        if (!file) return;  // If file cannot be opened, return without loading

        books.clear();  // Clear existing books
        Book book;
        // Read each book's data from file and store in the books vector
        while (file >> book.id >> ws && getline(file, book.title) && getline(file, book.genre) &&
               getline(file, book.publisher) && file >> book.copies >> ws) {
            books.push_back(book);
        }
        file.close();
    }

    void saveBooks() {
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
                 << book.publisher << endl
                 << book.copies << endl;
        }
        file.close();
    }
};

#endif
