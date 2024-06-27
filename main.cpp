#include<iostream>
#include"./adt/bookADT.h"
#include"./adt/customerADT.h"
using namespace std;

main(){
    int choice;
    cout<<"[1] New Book"<<endl;
    cout<<"[2] Rent a Book"<<endl;
    cout<<"[3] Return a Book"<<endl;
    cout<<"[4] Show Book Details"<<endl;
    cout<<"[5] Display all Books"<<endl;
    cout<<"[6] Check Book Availability"<<endl;
    cout<<"[7] Customer Maintenance"<<endl;
    cout<<"[8] Exit Program"<<endl;
    cout<<"Enter your choice: ";cin>>choice;
    bookADT myBook;
    do
    {
        switch (choice){

        case 1:{
            myBook.newBook();
            break;
        }
        case 2:{
            cout<<"Rent a Book"<<endl;
            break;
        }
        case 3:{
            cout<<"Return a Book"<<endl;
            break;
        }
        case 4:{
            cout<<"Show Book Details"<<endl;
            break;
        }
        case 5:{
            cout<<"Display all Books"<<endl;
            break;
        }
        case 6:{
            cout<<"Check Book Availability"<<endl;
            break;
        }
        case 7:{
            cout<<"Customer Maintenance"<<endl;
            break;
        }
        case 8:{
            cout<<"Exit Program"<<endl;
            break;
        }
        default:{
            cout<<"Invalid input. Please try again."<<endl;
        }
    }
    } while (choice!=8);
}