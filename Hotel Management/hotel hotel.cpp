#include<iostream>
#include<fstream>
#include<conio.h>
#include<windows.h>
using namespace std;

class Hotel 
{
	private:
		int room_no;
		char Name[30];
		char Address[50];
		char Phone_num[20]; 
	public: 
	void booking();
	int check(int);
	void show();
	void rooms();
	void edit();
	void modify(int);
	void delete_rec(int);
};

void Hotel::booking() 
{
	int r, flag;
	ofstream fout("hotel_management.dat",ios::app);
	cout<<"\n Enter Customer Details";
	cout<<"\n --------------------------------------";
	cout<<"\n Please enter the room number: ";
	cin>>r;
	cin.ignore(100, '\n');	
	flag=check(r);
	if (flag == 1)
	{	
		cout<<"\n Sorry, the room is booked!"<<"\n";
 	}
 	else 
	{
		room_no = r;
		cout<<"Name: "<<"\n";
		cin.getline(Name,30);
		cout<<"Address: "<<"\n";
		cin.getline(Address,50);
		cout<<"Phone Number: "<<"\n";
		cin.getline(Phone_num,20);
		fout.write((char*)this,sizeof(Hotel));
		cout<<"Room is booked."<<endl;
	}
	cout<<"\n Press any key to continue...!";
	getch();
	fout.close();
}

void Hotel::show()
{
	ifstream fin("hotel_management.dat", ios::in);
	int r, flag;
	cout<<"Please enter your room number: "<<endl;
	cin>>r;
	while (!fin.eof())  // if not end of file, continue reading data
	{
		fin.read((char*)this,sizeof(Hotel));	
		if (room_no == r)
		{
			cout<<"\n Customer Details: "<<endl;
			cout<<"\n ------------------------"<<endl;
			cout<<"\n Your room number is: "<<r<<endl;
			cout<<"\n Name: "<<Name<<endl;
			cout<<"\n Address: "<<Address<<endl;
			cout<<"\n Phone Number: "<<Phone_num<<endl;
			flag = 1;
			break;
		}
	}
		if (flag == 0)
		{
			cout<<"Oops sorry, room number not found or occupied. Please try again."<<endl;
		}	
		getch();
	fin.close();	
}

void Hotel::rooms()
{
	ifstream fin("hotel_management.dat",ios::in);
	cout<<"\n Lists of Room Vacant";
	cout<<"\n Room No. \t\t\tName\t\t\tAddress\t\t\tPhone Num";
	while (!fin.eof())
	{
		fin.read((char*)this,sizeof(Hotel));
		cout<<"\n"<<room_no<<"\t\t\t"<<Name;
		cout<<"\t\t\t"<<Address<<"\t\t\t\t\t"<<Phone_num<<endl;
	}
	fin.close();
}

void Hotel::edit()
{
	int choice,r;
	cout<<"EDIT MENU"<<endl;
	cout<<"-------------------"<<endl;
	cout<<"1.Modify Customer Record"<<endl;
	cout<<"2.Delete Customer Record"<<endl;
	cin>>choice;
	cout<<"Please enter your room number: "<<endl;
	cin>>r;
	switch (choice)
	{
		case 1: 
			modify(r);
		break;
		case 2:
			delete_rec(r);
		break;
		default: 
		cout<<"Wrong choice. Please choose again."<<endl;
		break;
	}	
	getch();
}

void Hotel::modify(int r)
{
	long get_pointer_position, flag = 0;
	fstream file("hotel_management.dat",ios::in|ios::out|ios::binary);
	while(!file.eof())
	{
		get_pointer_position = file.tellg();
		file.read((char*)this,sizeof(Hotel));		
		if (room_no == r)
		{
 			cout<<"Please enter your name: "<<endl;
			cin.getline(Name,50);
			cin.ignore(100, '\n');
			cout<<"Please enter your address: "<<"\n";
			cin.getline(Address,50);
			cout<<"Please enter your phone number: "<<"\n";
			cin.getline(Phone_num,20);
			file.seekg(get_pointer_position);
			file.write((char*)this,sizeof(Hotel));
			cout<<"Record is modified"<<endl;
			flag = 1;
			break;		
		}
	}
		if(flag==0)
		{
			cout<<"\n Sorry room number not found or vacant!";
			file.close();
		}		
}

void Hotel::delete_rec(int r)
{
	int flag = 0;
	char ch; 
	ifstream fin("hotel_management.dat, ios::in");
	ofstream fout("temp.dat, ios::out");
	while (!fin.eof())
	{
		fin.read((char*)this,sizeof(Hotel));
		if (room_no == r)
		{
			cout<<"Name: "<<Name<<endl;
			cout<<"Address: "<<Address<<endl;
			cout<<"Phone number: "<<Phone_num<<endl;
			cout<<"Do you want to delete this record (Y/N)? ";
			cin>>ch;
			if(ch=='n')
			fout.write((char*)this,sizeof(Hotel));
			flag = 1;				
		}
		else
		fout.write((char*)this,sizeof(Hotel));
	}
	fin.close();
	fout.close();
	if(flag==0)
	{
		cout<<"Sorry room no ot found or vacant"<<endl;
	}
	else
	{
		remove("hotel_management.dat");
		rename("temp.dat","hotel_management.dat");
	}
}

int Hotel::check(int r)
{
	int flag=0;
	ifstream fin("hotel_management.dat", ios::in);
	while (!fin.eof())
	{
		fin.read((char*)this,sizeof(Hotel));
		if(room_no == r)
		{
			flag = 1;
			break;
		}	
	}	
	fin.close();
	return(flag);
}

int main () {
	int choice;
	Hotel data;
	cout<<endl;
	cout<<"\t\t-----------------------------------------"<<"\n";
	cout<<"\t\t\t* Welcome to Jamie Hotel *"<<"\n";
	cout<<"\t\t-----------------------------------------"<<"\n";
	cout<<"\t\t\tPlease enter your choice"<<endl;	
	cout<<"\t\t\t1. Book a room?"<<endl;
	cout<<"\n\t\t\t2. Customer Record"<<endl;
	cout<<"\n\t\t\t3. Rooms Allotted"<<endl;
	cout<<"\n\t\t\t4. Edit Record"<<endl;
	cout<<"\n\t\t\t5. Exit"<<endl;
	cout<<"\n\t\t\tYour choice: ";
	cin>>choice;
	switch(choice) 
	{
		case 1:
			data.booking();
			break;
		case 2:
			data.show();
			break;
		case 3:
			data.rooms();
			break;
		case 4: 
			data.edit();
			break;
		case 5: break;
		default:
			cout<<"Please enter a valid choice."<<"\n";			
		return 0;		
	}
}
