#ifndef BOOKADT_H
#define BOOKADT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#ifdef _WIN32
#include <direct.h> // Header for Windows-specific directory creation
#else
#include <sys/stat.h> // Header for POSIX directory creation
#endif

using namespace std;

// Structure to represent a Book
struct Book {
    int id;           // Unique identifier for the book
    string title;     // Title of the book
    string genre;     // Genre of the book
    string publisher; // Publisher of the book
    int copies;       // Number of available copies of the book
};

// Class for Book
class BookADT {
public:
    // Function to initialize and load books from file
    void accessBooks() {
        loadBooks();
    }

    // Function to wait for user input (press enter to continue)
    void waitForUserInput() {
        cout << "Press enter to continue...";
        cin.ignore(); // Ignores any remaining characters in input buffer
    }

    // Function to add a new book to the library
    void newBook() {
        loadBooks(); // Load existing books from file
        Book book;
        book.id = getNextID(); // Assign a new ID to the new book

        // Prompt user for book details
        cout << "Adding New Book\n\nBook Title: ";
        cin.ignore(); // Ignore any newline characters
        getline(cin, book.title);
        cout << "Genre: ";
        getline(cin, book.genre);
        cout << "Publisher: ";
        getline(cin, book.publisher);
        cout << "Number of Copies: ";
        cin >> book.copies;
        cin.ignore(); // Ignore any remaining characters in input buffer

        books.push_back(book); // Add the new book to the vector
        saveBooks();           // Save updated book list to file
        cout << "\n---------------" << endl;
        cout << "New Book Added!" << endl;
        waitForUserInput(); // Wait for user to press enter
    }

    // Function to rent a book by its title
    void rentBookByTitle(const string& title) {
        loadBooks(); // Load existing books from file

        bool bookFound = false;  // starts from false before it tracks whether a spepcific book has been found in the 'book' vector.
        for (auto& book : books) {  // 
            if (book.title == title) {  // checks if the title matches any of the titles in 'books' vector
                bookFound = true;  // if true
                if (book.copies > 0) {  // checks if there are any available copies of the book
                    char choice;  // vairable to store user input
                    cout << "Book Found!\nDo You Want to Rent the book? Y/N: ";
                    cin >> choice;  // reads the user choice, whether they want to rent a book
                    cin.ignore(); // Ignore any remaining characters in input buffer

                    if (toupper(choice) == 'Y') { // if Y (yes)
                        book.copies--; // Decrement available copies
                        saveBooks();   // Save updated book list to file
                        cout << "Book has been rented successfully!" << endl;
                    } else {  // if N (no)
                        cout << "Book rental cancelled." << endl;
                    }
                    waitForUserInput(); // Wait for user to press enter
                    return;
                } else {
                    cout << "Book Not Available!" << endl;  // book is found but there are no available copies, it informs the user
                    waitForUserInput(); // Wait for user to press enter
                    cin.ignore();       // Ignore any remaining characters in input buffer
                    return;
                }
            }
        }

        if (!bookFound) {  // after for loop, checks the value of 'bookFound'
            cout << "Book Not Found!" << endl;  // if false, it prints this message
            waitForUserInput(); // Wait for user to press enter
        }
    }

    // Function to return a rented book
    void returnBook() {
        loadBooks(); // Load existing books from file
        string title;  // characters
        bool bookFound = false;  // starts from false

        cout << "Book Title: ";
        getline(cin, title); // Prompt user to enter title of book to return

        for (auto& book : books) { // 'book' vector is checked to see if it's 'title' matches 
            if (book.title == title) {  // if found
                bookFound = true;
                book.copies++;   // Increment available copies
                saveBooks();     // Save updated book list to file
                cout << "Book Returned!" << endl;
                waitForUserInput(); // Wait for user to press enter
                return;
            }
        }

        if (!bookFound) {  // if not found
            cout << "Book Title Not Found!" << endl;
            waitForUserInput(); // Wait for user to press enter
        }
    }

    // Function to display details of a specific book
    void showBookDetails() {
        loadBooks(); // Load existing books from file
        string title;
        cout << "Show Book Details\n\nBook Title: ";
        cin.ignore(); // Ignore any newline characters
        getline(cin, title); // Prompt user to enter title of book to show details

        bool bookFound = false;
        for (const auto& book : books) {
            if (book.title == title) {
                bookFound = true;
                // Display book details
                cout << endl << "ID: " << book.id << "\nTitle: " << book.title << "\nGenre: " << book.genre << "\nPublisher: " << book.publisher << "\nCopies: " << book.copies << "\n------" << endl;
                waitForUserInput(); // Wait for user to press enter
                return;
            }
        }

        if (!bookFound) {
            cout << "Book Title Not Found!" << endl;
            waitForUserInput(); // Wait for user to press enter
        }
    }

    // Function to display all books in the library
    void displayAllBooks() {
        loadBooks(); // Load existing books from file

        for (const auto& book : books) {  // performs through the 'books' vector
            // Display details of each book
            cout << "ID: " << book.id << "\nTitle: " << book.title << "\nGenre: " << book.genre
                 << "\nPublisher: " << book.publisher << "\nCopies: " << book.copies << endl << "--------------" << endl;
        }
        waitForUserInput(); // Wait for user to press enter
        cin.ignore();       // Ignore any remaining characters in input buffer
    }

    // Function to check availability of a book by its title
    bool checkBookAvailability(const string& title) {
        loadBooks(); // Load existing books from file

        for (const auto& book : books) {
            if (book.title == title && book.copies > 0) {
                return true; // Book is available
            }
        }
        return false; // Book not found or not available
    }

    // Function to get the vector of all books
    const vector<Book>& getBooks() const { // allows the program to have a read-only view of all the books within the bookADT 
        return books; // Return vector of books
    }

private:
    const char* bookPath = "./data/books.txt"; // File path to store book information
    vector<Book> books; // Vector to store all books

    // Function to get the next available ID for a new book
    int getNextID() {
        return books.empty() ? 1 : books.back().id + 1; // Return next ID based on existing books
    }

    // Function to load books from file
    void loadBooks() {
        ifstream file(bookPath); // Open file for reading
        if (!file) {
            cout << "Unable to open file." << endl; // Error if file cannot be opened
            return;
        }

        books.clear(); // Clear existing books vector
        Book book; // Temporary variable to store book data
        string line; // String to store each line of file content
        while (getline(file, line)) {
            if (line.find("ID: ") == 0) {
                book.id = stoi(line.substr(4)); // Extract and parse book ID
            } else if (line.find("Title: ") == 0) {
                book.title = line.substr(7); // Extract book title
            } else if (line.find("Genre: ") == 0) {
                book.genre = line.substr(7); // Extract book genre
            } else if (line.find("Publisher: ") == 0) {
                book.publisher = line.substr(11); // Extract book publisher
            } else if (line.find("Copies: ") == 0) {
                book.copies = stoi(line.substr(8)); // Extract and parse number of copies
            } else if (line == "---") {
                books.push_back(book); // Add completed book to vector when end of book entry is reached
            }
        }
        file.close(); // Close file after reading
    }

    // Function to save books to file
    void saveBooks() {
#ifdef _WIN32
        _mkdir("./data"); // Create directory for storing data on Windows
#else
        mkdir("./data", 0777); // Create directory for storing data on POSIX systems
#endif

        ofstream file(bookPath); // Open file for writing
        if (!file) {
            cout << "Unable to open file." << endl; // Error if file cannot be opened
            return;
        }

        for (const auto& book : books) {
            // Write each book's details to file
            file << "ID: " << book.id << '\n'
                 << "Title: " << book.title << '\n'
                 << "Genre: " << book.genre << '\n'
                 << "Publisher: " << book.publisher << '\n'
                 << "Copies: " << book.copies << '\n'
                 << "---\n";
        }

        file.close(); // Close file after writing
    }
};

#endif // End of BOOKADT_H
