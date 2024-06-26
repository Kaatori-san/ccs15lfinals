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
    }

    void rentBook() {  
        loadBooks(); 

        char choice;
        string title;
        bool bookFound = false;
        cout << "Rent Book" << endl;
        cout << "Book Title: ";
        cin.ignore();
        getline(cin, title);
        for (auto& book : books) {
            if (book.title == title) {
                bookFound = true;
                cout << "Book Title Found!\nDo you want to rent the book? Y/N: ";
                cin >> choice;
                if (choice == 'Y' || choice == 'y') {
                    if (book.copies > 0) {
                        book.copies--; 
                        saveBooks(); 
                        cout << "Book Rented!" << endl;
                    }
                }
                return;
            } else if (!bookFound){
                cout << "Book Title Not Found!" << endl;
            }
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
                return;
            }
        }
        if (!bookFound){
            cout << "Book Title Not Found!" << endl;
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
                cout << "ID: " << book.id << "\nTitle: " << book.title << "\nGenre: " << book.genre
                     << "\nPublisher: " << book.publisher << "\nCopies: " << book.copies << endl;
                return;
            }
        }
        if (!bookFound){
            cout << "Book Title Not Found!" << endl;
        }
    }

    void displayAllBooks() {   
        loadBooks();  

        for (const auto& book : books) {
            cout << "ID: " << book.id << "\nTitle: " << book.title << "\nGenre: " << book.genre
                 << "\nPublisher: " << book.publisher << "\nCopies: " << book.copies << endl;
        }
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
        if (!file) return; 

        books.clear();
        Book book;
        while (file >> book.id >> ws && getline(file, book.title) && getline(file, book.genre) &&
               getline(file, book.publisher) && file >> book.copies >> ws) {
            books.push_back(book);
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