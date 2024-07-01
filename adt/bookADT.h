#ifndef BOOKADT_H
#define BOOKADT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#ifdef _WIN32
#include <direct.h> 
#else
#include <sys/stat.h> 
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
        loadBooks();  

        Book book;
        book.id = getNextID(); 
        cout << "Add New Book\nBook Title: ";
        cin.ignore();
        getline(cin, book.title);
        cout << "Genre: ";
        getline(cin, book.genre);
        cout << "Publisher: ";
        getline(cin, book.publisher);
        cout << "Number of Copies: ";
        cin >> book.copies;

        books.push_back(book);  
        saveBooks(); 
        cout << "New Book Added!" << endl;

        cout << "Wait for user input..." << endl;
        cin.ignore();
    }

    void rentBook() {
    loadBooks(); 

    string title;
    bool bookFound = false;
    cout << "Rent Book" << endl;
    cout << "Book Title: ";
    cin.ignore();  // Ignore the newline character left in the input buffer
    getline(cin, title);
    for (auto& book : books) {
        if (book.title == title) {
            bookFound = true;
            char choice;
            cout << "Book Title Found!\nDo you want to rent the book? Y/N: ";
            cin >> choice;
            if (choice == 'Y' || choice == 'y') {
                if (book.copies > 0) {
                    book.copies--; 
                    saveBooks(); 
                    cout << "Book Rented!" << endl;

                    cout << "Wait for user input..." << endl;
                    cin.ignore();
                } else {
                    cout << "No copies available for rent." << endl;

                    cout << "Wait for user input..." << endl;
                    cin.ignore();
                }
            }
            break;
        }
    }
    if (!bookFound) {
        cout << "Book Title Not Found!" << endl;

        cout << "Wait for user input..." << endl;
        cin.ignore();
    }
}

 
    void returnBook() {  
        loadBooks();  

        string title;
        bool bookFound = false;
        cout << "Return Book\nBook Title: ";
        cin.ignore();
        getline(cin, title);
        for (auto& book : books) {
            if (book.title == title) {
                bookFound = true;
                book.copies++;  
                saveBooks();  
                cout << "Book Returned!" << endl;
                cout << "Wait for user input..." << endl;
                cin.ignore();
                return;
            }
        }
        if (!bookFound){
            cout << "Book Title Not Found!" << endl;
            cout << "Wait for user input..." << endl;
            cin.ignore();
        }
    }

    void showBookDetails() {
        loadBooks(); 

        string title;
        cout << "Show Book Details\nBook Title: ";
        cin.ignore();
        getline(cin, title);
        bool bookFound = false;
        for (const auto& book : books) {
            if (book.title == title) {
                bookFound = true;
                cout << "ID: " << book.id << "\nTitle: " << book.title << "\nGenre: " << book.genre << "\nPublisher: " << book.publisher << "\nCopies: " << book.copies << endl;
                cout << "Wait for user input..." << endl;
                cin.ignore();
                return;
            }
        }
        if (!bookFound){
            cout << "Book Title Not Found!" << endl;
            cout << "Wait for user input..." << endl;
            cin.ignore();
        }
    }

    void displayAllBooks() {   
        loadBooks();  

        for (const auto& book : books) {
            cout << "ID: " << book.id << "\nTitle: " << book.title << "\nGenre: " << book.genre
                 << "\nPublisher: " << book.publisher << "\nCopies: " << book.copies << endl;
        }
        cout << "Wait for user input..." << endl;
        cin.ignore();
    }

    bool checkBookAvailability(const string& title) {   
        loadBooks();  

        for (const auto& book : books) {
            if (book.title == title && book.copies > 0) {
                return true;  
            }
        }
        return false;  
    }

    const vector<Book>& getBooks() const {
        return books;
    }

private:
    const char* bookPath = "./data/books.txt";  
    vector<Book> books;                        

    int getNextID() {
        return books.empty()? 1 : books.back().id + 1;
    }

    void loadBooks() {
        ifstream file(bookPath);
        if (!file) {
            cout << "Unable to open file for reading." << endl;
            return; 
        }

        books.clear();
        Book book;
        string line;
        while (getline(file, line)) {
            if (line.find("ID: ") == 0) {
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

    void saveBooks() {
    #ifdef _WIN32
    _mkdir("./data"); 
    #else
    mkdir("./data", 0777);  
    #endif

    ofstream file(bookPath);
    if (!file) {
        cout << "Unable to open file for writing." << endl;
        return;
    }

    for (const auto& book : books) {
        file << "ID: " << book.id << '\n'
             << "Title: " << book.title << '\n'
             << "Genre: " << book.genre << '\n'
             << "Publisher: " << book.publisher << '\n'
             << "Copies: " << book.copies << '\n'
             << "---\n";  // Separator between books
    }

    file.close();
}

};

#endif