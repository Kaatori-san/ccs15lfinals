#include<iostream>
using namespace std;
class bookADT
{
private:
    int bookID;
    char bookTitle;
    int bookGenre;
    int bookProduction;
    int bookNumCopies;
    int bookIMGFileName;
public:
    void newBook();
    void showBook();
};
void bookADT::newBook(){
    cout<<"add new book"<<endl;
    cout<<"Book Title: ";cin>>bookTitle;
}
void bookADT::showBook(){
    cout<<"show book"<<endl;
    cout<<"Book Title: ";
    cout<<bookTitle;
    return;
}

