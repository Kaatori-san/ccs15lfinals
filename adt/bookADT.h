#ifndef BOOKADT_H
#define BOOKADT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Book {
    int id;
    string title;
    string genre;
    string production;
    int copies;
    string imageFile;
};

class BookADT {
public:
    void newBook();
    void rentBook();
    void returnBook();
    void showBookDetails();
    void displayAllBooks();
    bool checkBookAvailability(const string& title);

    const vector<Book>& getBooks() const;

private:
    vector<Book> books;
    int getNextID();
    void loadBooks();
    void saveBooks();
};

// Member function definitions

int BookADT::getNextID() {
    return books.empty() ? 1 : books.back().id + 1;
}

void BookADT::loadBooks() {
    ifstream file("books.txt");
    if (!file) return;

    Book book;
    while (file >> book.id >> ws && getline(file, book.title) && getline(file, book.genre) &&
           getline(file, book.production) && file >> book.copies >> ws && getline(file, book.imageFile)) {
        books.push_back(book);
    }
    file.close();
}

void BookADT::saveBooks() {
    ofstream file("books.txt");
    for (const auto& book : books) {
        file << book.id << endl
             << book.title << endl
             << book.genre << endl
             << book.production << endl
             << book.copies << endl
             << book.imageFile << endl;
    }
    file.close();
}

void BookADT::newBook() {
    loadBooks();
    Book book;
    book.id = getNextID();
    cout << "Add New Book\nBook Title: ";
    cin.ignore();
    getline(cin, book.title);
    cout << "Genre: ";
    getline(cin, book.genre);
    cout << "Production: ";
    getline(cin, book.production);
    cout << "Number of Copies: ";
    cin >> book.copies;
    cout << "Image File: ";
    cin.ignore();
    getline(cin, book.imageFile);

    books.push_back(book);
    saveBooks();
    cout << "New Book Title Added!" << endl;
}

void BookADT::rentBook() {
    loadBooks();
    string title;
    cout << "Show Book\nBook Title: ";
    cin.ignore();
    getline(cin, title);
    for (auto& book : books) {
        if (book.title == title) {
            cout << "Book Title Found! Do you want to rent the book? Y/N: ";
            char choice;
            cin >> choice;
            if (choice == 'Y' || choice == 'y') {
                if (book.copies > 0) {
                    book.copies--;
                    saveBooks();
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

void BookADT::returnBook() {
    loadBooks();
    string title;
    cout << "Return Book\nBook Title: ";
    cin.ignore();
    getline(cin, title);
    for (auto& book : books) {
        if (book.title == title) {
            book.copies++;
            saveBooks();
            cout << "Book Returned!" << endl;
            return;
        }
    }
    cout << "Book Title Not Found!" << endl;
}

void BookADT::showBookDetails() {
    loadBooks();
    string title;
    cout << "Show Book Details\nBook Title: ";
    cin.ignore();
    getline(cin, title);
    for (const auto& book : books) {
        if (book.title == title) {
            cout << "ID: " << book.id << "\nTitle: " << book.title << "\nGenre: " << book.genre
                 << "\nProduction: " << book.production << "\nCopies: " << book.copies << "\nImage File: " << book.imageFile << endl;
            return;
        }
    }
    cout << "Book Title Not Found!" << endl;
}

void BookADT::displayAllBooks() {
    loadBooks();
    for (const auto& book : books) {
        cout << "ID: " << book.id << "\nTitle: " << book.title << "\nGenre: " << book.genre
             << "\nProduction: " << book.production << "\nCopies: " << book.copies << "\nImage File: " << book.imageFile << endl;
    }
}

bool BookADT::checkBookAvailability(const string& title) {
    loadBooks();
    for (const auto& book : books) {
        if (book.title == title && book.copies > 0) {
            return true;
        }
    }
    return false;
}

const vector<Book>& BookADT::getBooks() const {
    return books;
}

#endif
