\
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

struct Book {
    int id;
    string title;
    string genre;
    string publisher;
    int copies;
};

class BookADT {
public:
    void accessBooks() {
        loadBooks();
    }
    void waitForUserInput() {
        cout << "Press enter to continue...";
        cin.ignore();
    }

    void newBook() {
        loadBooks();
        Book book;
        book.id = getNextID();
        cout << "Adding New Book\n\nBook Title: ";
        cin.ignore();
        getline(cin, book.title);
        cout << "Genre: ";
        getline(cin, book.genre);
        cout << "Publisher: ";
        getline(cin, book.publisher);
        cout << "Number of Copies: ";
        cin >> book.copies;
        cin.ignore();
        books.push_back(book);
        saveBooks();
        cout << "\n---------------" << endl;
        cout << "New Book Added!" << endl;
        waitForUserInput();
    }

 void rentBookByTitle(const string& title) {
    loadBooks();

    bool bookFound = false;
    for (auto& book : books) {
        if (book.title == title) {
            bookFound = true;
            if (book.copies > 0) {
                char choice;
                cout << "Book Found!\nDo You Want to Rent the book? Y/N: ";
                cin >> choice;
                cin.ignore(); 

                if (toupper(choice) == 'Y') {
                    book.copies--;
                    saveBooks();
                    cout << "Book has been rented successfully!" << endl;
                } else {
                    cout << "Book rental cancelled." << endl;
                }
                waitForUserInput();
                return;
            } else {
                cout << "Book Not Available!" << endl;
                waitForUserInput();
                cin.ignore();
                return;
            }
        }
    }

    if (!bookFound) {
        cout << "Book Not Found!" << endl;
        waitForUserInput();
    }
}

    void returnBook() {
        loadBooks();
        int customerId;
        string title;
        bool bookFound = false;

        cout << "Book Title: ";
        getline(cin, title);

        for (auto& book : books) {
            if (book.title == title) {
                bookFound = true;
                book.copies++;
                saveBooks();
                cout << "Book Returned!" << endl;
                waitForUserInput();
                return;
            }
        }

        if (!bookFound) {
            cout << "Book Title Not Found!" << endl;
            waitForUserInput();
        }
    }

    void showBookDetails() {
        loadBooks();
        string title;
        cout << "Show Book Details\n\nBook Title: ";
        cin.ignore();
        getline(cin, title);
        bool bookFound = false;

        for (const auto& book : books) {
            if (book.title == title) {
                bookFound = true;
                cout << endl << "ID: " << book.id << "\nTitle: " << book.title << "\nGenre: " << book.genre << "\nPublisher: " << book.publisher << "\nCopies: " << book.copies << "\n------" << endl;
                waitForUserInput();
                return;
            }
        }

        if (!bookFound) {
            cout << "Book Title Not Found!" << endl;
            waitForUserInput();
        }
    }

    void displayAllBooks() {
        loadBooks();

        for (const auto& book : books) {
            cout << "ID: " << book.id << "\nTitle: " << book.title << "\nGenre: " << book.genre
                 << "\nPublisher: " << book.publisher << "\nCopies: " << book.copies << endl << "--------------" << endl;
        }
        waitForUserInput();
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
        return books.empty() ? 1 : books.back().id + 1;
    }

    void loadBooks() {
        ifstream file(bookPath);
        if (!file) {
            cout << "Unable to open file." << endl;
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
                books.push_back(book);
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
            cout << "Unable to open file." << endl;
            return;
        }

        for (const auto& book : books) {
            file << "ID: " << book.id << '\n'
                 << "Title: " << book.title << '\n'
                 << "Genre: " << book.genre << '\n'
                 << "Publisher: " << book.publisher << '\n'
                 << "Copies: " << book.copies << '\n'
                 << "---\n";
        }

        file.close();
    }
};

#endif
