#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<ctime>
using namespace std;
class Car_Admin {
public:
	string  Type, Seating, Status, Aut_Man, Car_Name;
	float Rent;
	int Car_Id;
	void input(int l_id) {

		Car_Id = l_id + 1;
		cout << "Enter the car name: " << endl; cin >> Car_Name;
		cout << "Enter the type of the car:(Sedan/SUV) " << endl; cin >> Type;
		cout << "Enter the Seating capacity of the car: " << endl; cin >> Seating;
		cout << "Is it a Manual or an Automatic car: " << endl; cin >> Aut_Man;
		cout << "Enter the rent of the car(per day): " << endl; cin >> Rent;
		Status = "Available";
	}
	void display() {
		cout<<endl<<"|"<<setw(6)<<Car_Id << setw(5) << "|" << setw(20) << Car_Name<<setw(5) << "|" << setw(5) << Type << setw(5) << "|" << setw(10) << Seating << setw(5) << "|" << setw(10) << Aut_Man << setw(5) << "|"<<setw(6)<<Rent << setw(5) << "|"<<setw(10)<<Status << setw(5) << "|";
	}
};
fstream f;
Car_Admin C;
void Add(){
	int l_id=0;
	f.open("Car_Admin.dat", ios::binary | ios::in);
	if (!f)
	{
		l_id = 0;
	}
	else 
	{
		f.read((char*)&C, sizeof(C));
		while (!f.eof()) {
			l_id = C.Car_Id;
			f.read((char*)&C, sizeof(C));
		}
		f.close();
	}
	f.open("Car_Admin.dat", ios::binary | ios::app);
	C.input(l_id);
	f.write((char*)&C, sizeof(C));
	f.close();
	
}

void Display_All() {
	f.open("Car_Admin.dat", ios::binary | ios::in);

	cout << "-------------------------------------------------------------------------------------------------------" << endl;
	cout << "|" << setw(6) << "Car Id" << setw(5) << "|" << setw(20) << "Car Name" << setw(5) << "|" << setw(5) << "Type" << setw(5) << "|" << setw(10) << "Seating" << setw(5) << "|" << setw(10) << "Aut_Man" << setw(5) << "|" << setw(6) << "Rent" << setw(5) << "|" << setw(10) << "Status" << setw(5) << "|" << endl;
	cout << "|-----------------------------------------------------------------------------------------------------|";
	f.read((char*)&C, sizeof(C));
	while (!f.eof()) {
		C.display();
		f.read((char*)&C, sizeof(C));
	}
	f.close();
}


void Available_Car() {
	cout << "-------------------------------------------------------------------------------------------------------" << endl;
	cout << "|" << setw(6) << "Car Id" << setw(5) << "|" << setw(20) << "Car Name" << setw(5) << "|" << setw(5) << "Type" << setw(5) << "|" << setw(10) << "Seating" << setw(5) << "|" << setw(10) << "Aut_Man" << setw(5) << "|" << setw(6) << "Rent" << setw(5) << "|" << setw(10) << "Status" << setw(5) << "|" << endl;
	cout << "|-----------------------------------------------------------------------------------------------------|";
	f.open("Car_Admin.dat", ios::binary | ios::in);
	
	f.read((char*)&C, sizeof(C));

	while (!f.eof()) {
		if (C.Status == "Available")
		{
			C.display();
		}
		
		f.read((char*)&C, sizeof(C));
	}
	f.close();
}
void search() {
	int Sid;
	int flag;
	cout << "Enter the Car id of the car to be searched: " << endl; cin >> Sid;
	f.open("Car_Admin.dat", ios::binary | ios::in);
	cout << "-------------------------------------------------------------------------------------------------------" << endl;
	cout << "|" << setw(6) << "Car Id" << setw(5) << "|" << setw(20) << "Car Name" << setw(5) << "|" << setw(5) << "Type" << setw(5) << "|" << setw(10) << "Seating" << setw(5) << "|" << setw(10) << "Aut_Man" << setw(5) << "|" << setw(6) << "Rent" << setw(5) << "|" << setw(10) << "Status" << setw(5) << "|" << endl;
	cout << "|-----------------------------------------------------------------------------------------------------|";
	f.read((char*)&C, sizeof(C));
	while (!f.eof()) {
		if (Sid == C.Car_Id) {
			C.display(); flag = 0;
		}
		f.read((char*)&C, sizeof(C));
	}
	f.close();
	if (flag == 1) {
		cout << "Car not found" << endl;
	}
}
void Update() {
	int sid;
	float rent;
	f.open("Car_Admin.dat", ios::binary | ios::out|ios::in);
	cout << "Enter the car id: " << endl; cin >> sid;
	f.read((char*)&C, sizeof(C));
	while (!f.eof()) {
		int pos = f.tellp();
		if (sid == C.Car_Id) {
			cout << "Enter the new rent: " << endl;
			cin >> rent;
			C.Rent = rent;
			f.seekp(pos - sizeof(C));
			f.write((char*)&C, sizeof(C));
			break;
		}	
		f.read((char*)&C, sizeof(C));
	}
	f.close();
}
void Status_Update() {
	int sid;
	float Status;
	f.open("Car_Admin.dat", ios::binary | ios::out | ios::in);
	cout << "Enter the car id: " << endl; cin >> sid;
	f.read((char*)&C, sizeof(C));
	while (!f.eof()) {
		int pos = f.tellp();
		if (sid == C.Car_Id) {
			C.Status="Available";
			f.seekp(pos - sizeof(C));
			f.write((char*)&C, sizeof(C));
			break;
		}
		f.read((char*)&C, sizeof(C));
	}
	f.close();
}

fstream ff;
void Delete_Car() {
	int sid;
	cout << "Enter the Car Id: " << endl; cin >> sid;
	f.open("Car_Admin.dat", ios::binary | ios::in);
	ff.open("New.dat", ios::binary | ios::app);
	f.read((char*)&C, sizeof(C));
	while (!f.eof()) {
		if (sid != C.Car_Id) {
			ff.write((char*)&C, sizeof(C));
		}
		f.read((char*)&C, sizeof(C));
	}
	ff.close();
	f.close();
	remove("Car_Admin.dat");
	rename("New.dat", "Car_Admin.dat");
}
class Customer {

	public:
	int Time,No_Day,C_id,ch;
	float Amount,CGST,SGST,Car_Rent,Total;
	string Cus_Nam, Cus_Pass,Name,Adhar_Id, Phone_Num,Car_Name;

	void s_input() {
		cout << "Enter the your Name: " << endl; getline(cin,Cus_Nam);
		cout << "Enter your mobile number: " << endl; cin.ignore(); cin >> Phone_Num;
		cout << "Enter a strong password to be created: " << endl; cin.ignore(); cin >> Cus_Pass;
	}

	void l_input() {
		cout << "Enter your mobile number: " << endl; cin >> Phone_Num;
		cout << "Enter your password: " << endl; cin >> Cus_Pass;
	}

	void display() {
		cout <<endl<< "Customer Name" << Cus_Nam << "Phone number" << Phone_Num << "Customer Passcode" << Cus_Pass;
	}

	void Book_Car(){
		cout << "Enter your name:" << endl; cin >> Name;
		cout << "Enter your adhar id: " << endl; cin >> Adhar_Id;
		cout << "Your contact number is: " << endl << Phone_Num;
		cout << "\nThe number of days for which you want the car: " << endl; cin >> No_Day;

		Available_Car();

		cout << "\nEnter Car id you want to buy: " << endl; cin >> C_id;
		f.open("Car_Admin.dat", ios::binary | ios::in | ios::out);
		f.read((char*)&C, sizeof(C));
		while (!f.eof()) {
			int tell = f.tellp();
			if (C_id == C.Car_Id) {
				Car_Name = C.Car_Name;
				Car_Rent = C.Rent;
				Amount = Car_Rent * No_Day;
				CGST = Amount * 0.08;
				SGST = Amount * 0.08;
				Total = Amount + CGST + SGST;
				cout << "Final total amount for the duration is: " << Total;
				cout << "\nDo you want to book: (Enter 1 for yes or 2 for No)" << endl; cin >> ch;
				if (ch == 1) {
					C.Status = "Booked";
					f.seekp(tell - sizeof(C));
					f.write((char*)&C, sizeof(C));
					system("cls");
					Billgenerate();
					break;
				}
				else {
					break;
				}
			}
			f.read((char*)&C, sizeof(C));
		}
		f.close();

	}
	void Billgenerate() {

		cout << "-----------------------------------------------------------" << endl;
		cout << "|\t\t\t Bill \t\t\t          |" << endl;
		cout << "|---------------------------------------------------------|" << endl;
		cout << "| Name:" << Cus_Nam << endl;
		cout << "| Adhar id: " << Adhar_Id << endl;
		cout << "| Contact number: " << Phone_Num << endl;
		cout << "----------------------------------------------------------|" << endl;

		cout << "|" << "    Car name   " << "   Rent    " << "   No of days    " << "     Amount    " << endl;
		cout << "|" << setw(10) << Car_Name << setw(11) << Car_Rent << setw(16) << No_Day << setw(16) << Amount << setw(5) << "|" << endl;
		cout << "|---------------------------------------------------------|" << endl;
		cout << "|" << "      CGST     " << setw(38) << CGST << setw(5) << "|" << endl;
		cout << "|" << "      SGST     " << setw(38) << SGST << setw(5) << "|" << endl;
		cout << "|---------------------------------------------------------|" << endl;
		cout << "|" << "   Total bill: " << setw(38) << Total << setw(5) << "|" << endl;


		//cout << "Name:" <<Cus_Nam<< endl;
		////cout << "Date " << DD << "/" << MM << "/" << YY << endl;
		//cout << "Contact number: " << Phone_Num << endl;
		//cout << "Adhar id: " << Adhar_Id << endl;
		//cout << "Car name: " << Car_Name<< endl;
		//cout << "Car rent: " << Car_Rent << endl;
		//cout << "No of days " << No_Day << endl;
		//cout << "Amount" << Amount << endl;
		//cout << "SGST " << SGST<<endl;
		//cout << "CGST" << CGST << endl;
		//cout << "Total bill: " << Total << endl;
	}
};
Customer K;
void Signup() {
	f.open("Cus.dat", ios::binary | ios::app);
	K.s_input();
	f.write((char*)&K, sizeof(K));
	f.close();
}

int login() {
	K.l_input();
	string pass = K.Cus_Pass;
	string no = K.Phone_Num;
	int Flag = 0;

	f.open("Cus.dat", ios::binary | ios::in );
	f.read((char*)&K, sizeof(K));
	while (!f.eof())
	{
		if (no == K.Phone_Num && pass==K.Cus_Pass)
		{
			
			Flag = 1;
		}
		f.read((char*)&K, sizeof(K));
	}
	if (Flag == 0)
	{
		cout << "Not successfull";
		return 0;
	}
	else {
		cout << "Login succesfully";
		return 1;
	}

	f.close();

}

int main() {

	while (1)
	{
		int au;
		string Ui, Up;
		l1:
		cout <<endl<< "Menu " << endl;
		cout << "1.Admin \n2.User";
		cout << endl << "Enter Your Choice "; cin >> au;

		if (au == 1)
		{
			cout << "Enter the user id: " << endl; cin >> Ui;
			while (Ui != "SuperAdmin") {
				cout << "Enter the correct user id: " << endl; cin >> Ui;
			}
			cout << "Enter the password: " << endl; cin >> Up;
			while (Up != "SuperPass") {
				cout << "Enter the correct passcode: " << endl; cin >> Up;
			}
			while (1)
			{
				int ach;
				cout << "\nMenu";
				cout << "\n1. Add Car \n2. Display All Car \n3. Search Car \n4. Update Rent \n5. Delete Car \n6. Status Update \n7.MainMenu \n8.Exit"<<endl;
				cout << "Enter Your Choice: "; cin >> ach;

				switch (ach)
				{
				case 1: system("cls"); Add(); break;
				case 2:system("cls");
					Display_All(); break;
				case 3: system("cls"); search(); break;
				case 4: system("cls"); Update(); break;
				case 5: system("cls"); Delete_Car(); break;
				case 6: system("cls"); Status_Update(); break;
				case 7:goto l1; break;
				default:exit(0);
				}
			}
		}
		else if (au == 2)
		{
			while (1)
			{
				int ch, SL, ch1;
				l2:
				cout << "\n\nMenu\n1.signup \n2.Login \n3.Mainmenu \n4.Exit \nEnter choice " << endl;
				cin >> ch;
				switch (ch) {
				case 1:
					system("cls");
					Signup(); break;
				case 2:
					system("cls");
					SL = login();
					break;
				case 3: goto l1; break;
				case 4: exit(0); break;
				default:
					exit(0);
				}

				if (ch == 1 || SL == 1)
				{
					while(1){
					
					cout << "\n\n1. Display available car \n2. Book Car \n3. Signup/Login \n4. Exit \nEnter choice " << endl; cin >> ch1;
					switch (ch1) {
					case 1: system("cls"); Available_Car(); system("cls"); Available_Car(); break;
					case 2: system("cls"); K.Book_Car(); break;
					case 3: goto l2; break;
					default: exit(0);
					}
					}
				}
			}

		}

	}
	
}
