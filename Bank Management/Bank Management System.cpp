#include<iostream>
#include<string>
#include<fstream>
using namespace std;
using std::cout;
using std::cin;
using std::endl;
using std::fstream;
using std::ofstream;
using std::ifstream;
using std::ios;

class BankManagementSystem 
{
	private:
		char FirstName[20];
		char LastName[20];
		char accountNumber[20];
		float balance;
	public:
		void getData();
		void writeToFile();
		void readFromFile();
		void showData();
		void searchFromFile();
		void updateRecord();
};
void BankManagementSystem::getData() 
{
	cout<<"Enter Account Number:";
	cin>>accountNumber;
	//cin.ignore(100, '\n');	
	cout<<"\nFirst Name: ";
	cin.getline(FirstName,20);
	cout<<"\nLast Name: ";
	cin.getline(LastName,20);
	cout<<"\nEnter balance: ";
	cin>>balance;
}
void BankManagementSystem::writeToFile()
{
	ofstream outfile;
	outfile.open("CustomerRecord.dat", ios::binary|ios::app);
	getData();	
 	outfile.write(reinterpret_cast<char *>(this), sizeof(*this));
	outfile.close();
}
void BankManagementSystem::showData()
{
	cout<<"Account Number: "<<accountNumber<<"\n";
	cout<<"First Name: "<<FirstName<<"\n";
	cout<<"Last Name: "<<LastName<<"\n";
	cout<<"Balance: "<<balance<<"\n"; 
}
void BankManagementSystem::readFromFile()
{
	std::ifstream infile;
	infile.open("CustomerRecord.dat", ios::binary);
	while (!infile.eof())
	{
		if(infile.read(reinterpret_cast<char*>(this), sizeof(*this))>0)
        {
            showData();
        }
	}
	infile.close();
}
void BankManagementSystem::searchFromFile()
{
	int n;
	std::ifstream infile;
	infile.open("CustomerRecord.dat", ios::binary);
	if (!infile) 
	{
		cout<<"\n Error in opening file" <<endl;
		return;
	}
	infile.seekg(0,ios::end);
	int count = infile.tellg()/sizeof(*this);
	cout<<"\n There are "<<count<<" record in the file";
    cout<<"\n Enter Record Number to Search: ";
    cin>>n;
    infile.seekg((n-1)*sizeof(*this));
    showData();
}
void BankManagementSystem::updateRecord()
{
	int n;
    fstream iofile;
    iofile.open("record.bank", ios::in|ios::binary);
    if(!iofile)
    {
        cout<<"\nError in opening! File Not Found!!"<<endl;
        return;
    }
    iofile.seekg(0, ios::end);
    int count = iofile.tellg()/sizeof(*this);
    cout<<"\n There are "<<count<<" record in the file";
    cout<<"\n Enter Record Number to edit: ";
    cin>>n;
    iofile.seekg((n-1)*sizeof(*this));
    iofile.read(reinterpret_cast<char*>(this), sizeof(*this));
    cout<<"Record "<<n<<" has following data"<<endl;
    showData();
    iofile.close();
    iofile.open("record.bank", ios::out|ios::in|ios::binary);
    iofile.seekp((n-1)*sizeof(*this));
    cout<<"\nEnter data to Modify "<<endl;
    getData();
    iofile.write(reinterpret_cast<char*>(this), sizeof(*this));
}


int main () 
{	
	int option;
	BankManagementSystem data;
	cout<<"***Banking Information System***"<<"\n";
	cout<<"Select 1 option from below: \n";
	cout<<"1. Add Record \n";
	cout<<"2. Show Record \n";
	cout<<"3. Search Record \n";
	cout<<"4. Update Record \n";
	cout<<"5. Delete Record \n";
	cout<<"6. Quit \n";
	cin>>option;
		switch (option) 
		{	
			case 1:	
			data.writeToFile();
			break;	
			case 2:
			data.readFromFile();
			break;
			case 3: 
			data.searchFromFile();
			break;
			case 4:
			data.updateRecord();
			break;	
			default:
			cout<<"Please enter the correct option \n";										
		}
	system("pause");
	return 0;
}
