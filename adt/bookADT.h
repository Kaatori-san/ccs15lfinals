#ifndef BOOKADT_H
#define BOOKADT_H

#include <iostream>  // Handling input and output operations in the console log
#include <fstream>  // used for reading and writing files. 
#include <string>   // used for handling string data, such as storing book details etc 
#include <vector>   // used to store nad manage the collections of Book in a resizable array-like structure

#ifdef _WIN32
#include <direct.h> // mkdir() on Windows
#else
#include <sys/stat.h> // mkdir() on Unix/Linux
#endif

using namespace std;

// Book structure for storing book details
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
    void waitForUserInput() {
        cout << "Press enter to continue...";  
        cin.ignore(); // waits for the user to press the 'Enter' key
    }
    void newBook() {  // Adds a new book to the file
        loadBooks();  // Loads existing books from file
        Book book;
        book.id = getNextID();  // Generate new ID for the book
        // Asks the user for book details
        cout << "Add New Book\nBook Title: ";
        cin.ignore();
        getline(cin, book.title);
        cout << "Genre: ";
        getline(cin, book.genre);
        cout << "Publisher: ";
        getline(cin, book.publisher);
        cout << "Number of Copies: ";
        cin >> book.copies;
        books.push_back(book);  // adds the new book to the vector
        saveBooks();            // save updated book list to file
        cout << "New Book Added!" << endl;
        waitForUserInput();
    }

    void rentBookByTitle(const string& title) {  // rents a book by decreasing It's available copies. 
        loadBooks();    // Load existing books from file

        for (auto& book : books) {
            if (book.title == title) {
                if (book.copies > 0) {
                    book.copies--;  // decreases available copies, if the user inputs more than 1 copies of a book
                    saveBooks();    // saves updated book list to file
                    return;
                }
            }
        }
    }

    void returnBook() {  // Returns a book by increasing It's available copies
        loadBooks();     // Load existing books from file

        string title;  // character inputs
        bool bookFound = false;  // declares bookFound if the book is found
        cout << "Return Book\nBook Title: ";
        cin.ignore();    // Ignores any newline characters
        getline(cin, title);

        // Searches for the book ttile in the vector file
        for (auto& book : books) {  // repeats over each book in the 'books' vector. 
            if (book.title == title) {  // checks if the book title matches the title entered by the user
                bookFound = true;  // book has beend found
                book.copies++;  // Increases available copies
                saveBooks();   // function to save the updated book list to the file
                cout << "Book Returned!" << endl;
                return;
            }
        }
        if (!bookFound){  // checks bookFound is still flase, if no matching book was found, this section is showed to the user
            cout << "Book Title Not Found!" << endl;
        }
        waitForUserInput();
    }

    void showBookDetails() {
        loadBooks();  // loads the current list of books from a file into the 'books' vector. 

        string title;  // character input
        cout << "Show Book Details\nBook Title: ";
        cin.ignore();  // ignores any newline characters in the input buffer from previous inputs. This also ensures that 'getline' reads the title correctly
        getline(cin, title);  // reads the full line of input from the user and store it in the 'title' variable
        bool bookFound = false;  // bookFound to false, if a book entered by the user is found in the 'books' vector

        // Search for the book by title in the evctor
        for (const auto& book : books) {  // repeats through each book in the 'books' vector
            if (book.title == title) {  // checks if the current book matches the title entered by the user
                bookFound = true;  // if match is found, it is true

                // This displays the book details if found. 
                cout << endl << "ID: " << book.id << "\nTitle: " << book.title << "\nGenre: " << book.genre << "\nPublisher: " << book.publisher << "\nCopies: " << book.copies << endl;
                waitForUserInput();
                return;
            }
        }
    
        if (!bookFound){ // if not found, this shows
            cout << "Book Title Not Found!" << endl;
            waitForUserInput();
        }
    }

    // Displays all the books inside th evector
    void displayAllBooks() {   
        loadBooks();  

        for (const auto& book : books) {  // repeats through each book in the 'books' vector

            // Displayment details of every book
            cout << "ID: " << book.id << "\nTitle: " << book.title << "\nGenre: " << book.genre
                 << "\nPublisher: " << book.publisher << "\nCopies: " << book.copies << endl << "--------------" << endl;
        }
        waitForUserInput();
        cin.ignore();
    }

    // Checks if a specific book is available for rent. If the user enters more than 1 copies, it will say available for rent until that 1 other copy is rented.
    bool checkBookAvailability(const string& title) {   
        loadBooks();  

        for (const auto& book : books) {
            if (book.title == title && book.copies > 0) {
                return true;   // command if the book is found and available
            }
        }
        return false;  
    }

    // Returns the vector of Books
    const vector<Book>& getBooks() const {
        return books;
    }

private:
    const char* bookPath = "./data/books.txt";  // This is the path for storing books data file. This declares a constant character pointer named bookPath
    vector<Book> books;        // We use vector to store books                 

    int getNextID() {   // This generate the next ID available for the upcoming or new book inputed by the user
        return books.empty()? 1 : books.back().id + 1;  // checks if the 'books' vector is empty, if empty returns 1 as the next ID. If not, retrieves and continue the ID of the last book
    }

    // Load books data from file into the vector
    void loadBooks() {
        ifstream file(bookPath);  // creates an input file stream object named file and to open the file specified by the 'bookPath'
        if (!file) {  // checks if the file is opened
            cout << "Unable to open file." << endl;
            return;  // returns if file cannot be found
        }

        books.clear();  // clears existing books vector
        Book book;  // declares any variable 'book' of type 'Book'. This is used to temporarily store data for each book read from the file
        string line;  // variable 'line' to store each line of text read from the file
        while (getline(file, line)) {  // reads each line of the file until there are no more lines

            // Each line of the file to extract book details
            if (line.find("ID: ") == 0) {  // checks each line to determine its content and assign values
                book.id = stoi(line.substr(4));
            } else if (line.find("Title: ") == 0) {
                book.title = line.substr(7);
            } else if (line.find("Genre: ") == 0) {
                book.genre = line.substr(7);
            } else if (line.find("Publisher: ") == 0) {
                book.publisher = line.substr(11);
            } else if (line.find("Copies: ") == 0) {
                book.copies = stoi(line.substr(8));
            } else if (line == "---") {
                books.push_back(book);  // Add the book to the vector
            }
        }
        file.close();
    }

    // Saves books data from vector to file
    void saveBooks() {
    #ifdef _WIN32
    _mkdir("./data");   // Creates directory for data files fro Windows
    #else
    mkdir("./data", 0777);  // Same but for Unix/Linux
    #endif

    ofstream file(bookPath);  // This opens the file for writing
    if (!file) {
        cout << "Unable to open file." << endl;
        return;   // Again, return if the file data cannot be found
    }

    // Write each book's details to the file. Be much more readable and understandable if labeled and seperated from each other.
    for (const auto& book : books) {
        file << "ID: " << book.id << '\n'
             << "Title: " << book.title << '\n'
             << "Genre: " << book.genre << '\n'
             << "Publisher: " << book.publisher << '\n'
             << "Copies: " << book.copies << '\n'
             << "---\n";  // Separator between books
    }

    file.close();  // Closes the file stream
}

};

#endif
