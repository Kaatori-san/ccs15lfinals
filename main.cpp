#include<iostream>
#include"./adt/videoADT.cpp"
#include"./adt/customerADT.cpp"
using namespace std;

main(){
    int choice;
    cout<<"[1] New Video"<<endl;
    cout<<"[2] Rent a Video"<<endl;
    cout<<"[3] Return a Video"<<endl;
    cout<<"[4] Show Video Details"<<endl;
    cout<<"[5] Display all Videos"<<endl;
    cout<<"[6] Check Video Availability"<<endl;
    cout<<"[7] Customer Maintenance"<<endl;
    cout<<"[8] Exit Program"<<endl;
    cout<<"Enter your choice: ";cin>>choice;
    switch (choice){

        case 1:{
            cout<<"[1] New Video"<<endl;
            break;
        }
        case 2:{
            cout<<"[2] Rent a Video"<<endl;
            break;
        }
        case 3:{
            cout<<"[3] Return a Video"<<endl;
            break;
        }
        case 4:{
            cout<<"[4] Show Video Details"<<endl;
            break;
        }
        case 5:{
            cout<<"[5] Display all Videos"<<endl;
            break;
        }
        case 6:{
            cout<<"[6] Check Video Availability"<<endl;
            break;
        }
        case 7:{
            cout<<"[7] Customer Maintenance"<<endl;
            break;
        }
        case 8:{
            cout<<"[8] Exit Program"<<endl;
            break;
        }
        default:{
            return 0;
        }
    }
}