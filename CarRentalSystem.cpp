//============================================================================
// Name        : CarRentalSystem.cpp
// Author      : Dhruv
// ============================================================================

//*************************************************************
//                   HEADER FILE USED IN PROJECT
//*************************************************************

#include<fstream>
#include<stdio.h>
#include <iostream>
using namespace std;

//*************************************************************
//                   CLASS USED IN PROJECT
//*************************************************************

class car
{	char car_name[20];
	int car_num;
	char status[10];
	char car_type[10];
public:
	void getdata();   //function to accept data from user
	void showdata();  //function to show data on screen
	int ret_car_num(); //returns car number
};   //class ends here.

void car::getdata()
{
	cout<<"Enter car number:";
	cin>>car_num;
	cout<<"\nEnter car name:" ;
	cin>>car_name;
	cout<<"\nEnter car type(SUV/SEDAN/HATCHBACK):" ;
	cin>>car_type;
	cout<<"\nEnter status of the car:";
	cin>>status;
}
void car::showdata()
{
	cout<<"\n\nCAR NUMBER:"<<car_num;
	cout<<"\n\nCAR NAME:"<<car_name;
	cout<<"\n\nCAR TYPE:"<<car_type;
	cout<<"\n\nCAR STATUS:" <<status;
}
int car::ret_car_num()
{
	return car_num;
}

//*************************************************************
//    	           FUNCTION DECLARATION
//*************************************************************

void intro();    	//display welcome screen
void car_menu();	//display car registration menu
void car_register();	//register a car in binary file//
void display_all_cars();//read all cars record from binary file
void search_car(int);	//accept car number and search record from binary file
void modify_car(int);	//accept car number and modify record of binary file
void delete_car(int);	//accept car number and delete selected records from binary file

//*************************************************************
//    	           INTRODUCTION FUNCTION
//*************************************************************
void intro()
{

	cout<<"\n\n\n\t\t\t      DHRUV AGGARWAL";
	cout<<"\n\n\n\t\t\t           FROM" ;
	cout<<"\n\n\n\t\t\t AHLCON INTERNATIONAL SCHOOL";
	cout<<"\n\n\n\t\t\t          PRESENTS";
	cout<<"\n\n\n\t\t\t   CAR REGISTRATION SYSTEM";

}
//*************************************************************
//    	FUNCTION TO DISPLAY CAR REGISTRATION MENU
//*************************************************************

void car_menu()
{
	char ch;
	int cno;
	cout<<"\n\n\n\tCAR REGISTRATION MENU";
	cout<<"\n\n\t1. Register a new car";
	cout<<"\n\n\t2. Display all cars";
	cout<<"\n\n\t3. Search a car";
	cout<<"\n\n\t4. Modify a car";
	cout<<"\n\n\t5. Delete a car";
	cout<<"\n\n\t6. Back to main menu";
	cout<<"\n\n\n\tEnter Choice (1/2/3/4/5/6)? ";
	cin>>ch;

	switch(ch)
	{
	case '1' :	car_register(); break;

	case '2' :cout<<"Record is:"<<endl;
			display_all_cars(); break;

case '3' :	cout<<"\n\n\tEnter Car Number To Search: ";      cin>>cno;
			search_car(cno); break;

	case '4' :cout<<"\n\n Enter car number to Modify:";
			cin>>cno;
			modify_car(cno); break;

	case '5' :cout<<"\n\nEnter Car Number to Delete:";
			cin>>cno;
			delete_car(cno);       break;

	case '6' :	break;
			default:	cout<<"\a";
	}
}

//*************************************************************
//    	     FUNCTION TO REGISTER A CAR RECORD
//*************************************************************
void car_register()
{
	car c;
	char ch='y';
	ofstream fout("NEW_CAR.DAT",ios::binary|ios::app);
	do
	{	c.getdata();
		fout.write((char*)&c,sizeof(c));
		cout<<"\n\nDo you want to enter more(Y/N):";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
	fout.close();
	cout<<"\n\nRECORD HAS BEEN CREATED.";

}
//*************************************************************
//    	FUNCTION TO READ ALL CAR RECORDS FROM FILE
//*************************************************************

void display_all_cars()
{
	car c;
	ifstream fin("NEW_CAR.DAT",ios::binary);
	if(!fin)
	{
		cout<<"FILE COULD NOT BE OPENED! PRESS ANY KEY TO CONTINUE.";

		return;
	}
	cout<<"\n\n\n\t\tDISPLAY ALL RECORDS!\n\n";
	while(fin.read((char *) &c, sizeof(c)))
	{
		c.showdata();
		cout<<"\n\n====================================\n";
	}
	fin.close();

}

//*************************************************************
//    	FUNCTION TO SEARCH SPECIFIC RECORD FROM FILE
//*************************************************************
void search_car(int n)
{	car c;
	ifstream fin("NEW_CAR.DAT",ios::binary);
	if(!fin)
	{
		cout<<"FILE COULD NOT BE OPENED! PRESS ANY KEY TO CONTINUE." ;

		return;
	}
	int flag=0;
	while (!fin.eof())
	{  fin.read((char*)&c,sizeof(c));
		if(c.ret_car_num()==n)
		     {	c.showdata();
			flag=1;
		     }
	}
	fin.close();
	if(flag==0)
		cout<<"\n\nRECORD DOES NOT EXIST.";

}
//*************************************************************
//    	     FUNCTION TO MODIFY RECORD FROM FILE
//*************************************************************

void modify_car(int n)
{
	int found=0;
	car c;
	fstream File;
	File.open("NEW_CAR.DAT",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"FILE COULD NOT BE OPENED! PRESS ANY KEY TO CONTINUE.";


		return;
	}

	while(File.read((char *) &c, sizeof(c)) && found==0)
	{
		if(c.ret_car_num()==n)
		{
			c.showdata();
			cout<<"\n\nPlease enter new details of the CAR"<<endl;
			c.getdata();
		int pos=(-1)*sizeof(c);
		File.seekp(pos,ios::cur);
		File.write((char *) &c, sizeof(c));
		cout<<"\n\n\t RECORD UPDATED";
		    found=1;
		}
	}
	File.close();
	if(found==0)
		cout<<"\n\nRECORD NOT FOUND! ";

}

//*************************************************************
//    	      FUNCTION TO DELETE RECORD OF FILE
//*************************************************************

void delete_car(int n)
{
	car c;
	ifstream fin;
	fin.open("NEW_CAR.DAT",ios::binary);
	if(!fin)
	{
		cout<<"FILE COULD NOT BE OPNEND! PRESS ANY KEY TO CONTINUE.";

		return;
	}
	ofstream fout;
	fout.open("TEMP.DAT",ios::out);
	fin.seekg(0,ios::beg);
	while(fin.read((char *) &c, sizeof(c)))
	{
		if(c.ret_car_num()!=n)
		{
			fout.write((char *) &c, sizeof(c));
		}
	}
	fout.close();
	fin.close();
	remove("NEW_CAR.DAT");
	rename("TEMP.DAT","NEW_CAR.DAT");
	cout<<"\n\n\tRecord Deleted";

}

//*************************************************************
//    	       THE MAIN FUNCTION OF PROGRAM
//*************************************************************

int main()
{

	 char ch;
	intro();
      do
	{
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. CAR REGISTER SYSTEM";
		cout<<"\n\n\t02. EXIT";
		cout<<"\n\n\tPlease Select Your Option (1-2) ";
		cin>>ch;

		switch(ch)
		{
			case '1': car_menu();
				break;
			case '2':
				break;
			default :cout<<"\a";
		}
}while(ch!='2');
}
