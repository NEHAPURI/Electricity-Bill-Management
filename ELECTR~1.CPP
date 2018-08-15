#include<iostream.h>
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<fstream.h>

class customer
{
    protected:
	char id;
	char name[50];
	char f_name[50];
	char hno[10];
	char area[50];
	char state[50];
	char pin[7];
	char contact[11];

    public:
	void get_detail();
	void put_detail();

}c;

class payment : public customer
{
    protected:
	int units;
	int OMR,NMR;
	float amount;
	int fine,days,due;
    public:
	void get_units();
	int amt();
	void admin_menu();
	void put_units();
	void login();
	void report();
	char set_id()
	{
		return id;
	}
	void find();
	void del();
	int ret_amt();
	void modify_member();
	void modify_custmor();
	void allm();
}p;

void payment::report()
{
    cout<<"\n\n\t\t\t\t"<<name<<"\t\t\t\t"<<p.amt()<<"\t\t\t\t"<<contact<<"\t\t\t\t";
}

void payment::allm()
{
    // display the record
    int j,i;
    fstream fp1;
    clrscr();
    fp1.open("bill.dat",ios::in);
    if(!fp1)
    {
	gotoxy(20,35);
	cout<<"ERROR!!FILE NOT FOUND";
	getch();
	return;
    }
    else
    {
	gotoxy(20,5);
	cout<<"^ ^ ^ ^ DETAILS OF ALL CUSUMER ^ ^ ^ ^";
	gotoxy(20,7);

	for(i = 0; i < 40; i++)
	{

	}
	gotoxy(1,14);

	for(i = 0; i < 8; i++)
	{
	    cout<<"-";
	}

	gotoxy(3,15);
	cout<<"CUST. ID ";
	gotoxy(18,15);
	cout<<"CUSTOMER NAME ";
	gotoxy(45,15);
	cout<<"AMOUNT ";
	gotoxy(63,15);
	cout<<"CONTACT NO. ";


	gotoxy(1,16);

	for(i = 0; i < 80;i++)
	{
	    cout<<"-";

	}

	while(fp1.read((char*)&p,sizeof(p)))
	{
	    p.report();
	}
	fp1.close();
	getch();
    }
}

void customer::get_detail()
{
    cout<<"\n\n\t\t - - - - DETAILS - - - -\n";
    cout<<"\n\t\tC_id : \t ";
    cin>>id;
   // gets(id);
    cout<<"\n\t\tName : \t";
    gets(name);
    cout<<"\n\t\tFather's Name : \t";
    gets(f_name);
    cout<<"\n\t\tContact Number : \t";
    cin>>contact;
    while(1)
    {
	if(strlen(contact)!= 10)
	{
	    cout<<"\n\t\t\t\nEnter Contact again it must be of 10 digits\t : ";
	    gets(contact);
	}
	else
	    break;
    }
    cout<<"\n\t\tAddress ";
    cout<<"\n\t\tHouse no. ";
    gets(hno);
    cout<<"\n\t\tArea ";
    gets(area);
    cout<<"\n\t\tState ";
    gets(state);
    cout<<"\n\t\tPincode ";
    gets(pin);

    while(1){
	if (strlen(pin)!=6)
	{
	    cout<<"\n\n\t\t\t Pin must be of 6 digit ";
	    cout<<"\n\t\t\tEnter pin Again : ";
	    gets(pin);
	}
	else
	    break;
    }
}

void customer::put_detail()
{
    cout<<"\n\n\t\tC_id : \t ";
    cout<<id;
    //puts(id);
    cout<<"\n\t\tName : \t";
    puts(name);
    cout<<"\n\t\tFather's Name : \t";
    puts(f_name);
    cout<<"\n\n\t\tContact Number : \t";
    cout<<contact;
    cout<<"\n\t\tAddress ";
    cout<<"\t\t\t\t ";
    puts(hno);
    cout<<"\t\t\t\t ";
    puts(area);
    cout<<"\t\t\t\t ";
    puts(state);
    cout<<"\t\t\t\t ";
    puts(pin);

}

void payment::get_units()
{
    clrscr();
    get_detail();
    cout<<"\n\t\tOLD meter reading \t";
    cin>>OMR;
    cout<<"\n\t\tNEW meter reading \t";
    cin>>NMR;
    cout<<"\n\t\tlast due amount \t";
    cin>>due;
    cout<<"\n\t\tDays exceeded \t";
    cin>>days;
    units = NMR - OMR;
}

int payment::amt()
{
    if(units > 0 && units <= 350)
	amount = units*2.5;
    else
	if(units > 350 && units <= 700)
	    amount = ((350*2.5)+(units-350)*3.5);
	if(units>700 && units <= 1000)
	    amount = ((350*2.5)+(350*3.5)+(units-700)*4);
	else
	    if(units>1000)
		((350*2.5)+(350*3.5)+(700*4)+(units-700)*5);

    if(days>0)
	{
	    fine = days*5;
	    amount = (amount+fine)-due;
	}
    else
	amount = (amount-150)+due;

    cout<<"\n\n\t\tFine\t\t: "<<fine;
    cout<<"\n\n\t\tDue amount \t: "<<due;

    return amount;
}


void payment::put_units()
{
    cout<<"\n\n\t\tOld Meter Reading "<<OMR;
    cout<<"\n\n\t\tNew Meter Reading "<<NMR;
    cout<<"\n\n\t\tYour billing amount is "<<amt()<<"\n";
}

void payment::del()
{
    fstream fp;
    char n[6];
    clrscr();
    cout<<"\n\n\t\t^ ^ ^ ^Delete Record^ ^ ^ ^";
    cin>>n;
    fp.open("bills.dat",ios::in|ios::out);
    fstream fp2;
    fp2.open("temp.dat",ios::out);
    fp.seekg(0,ios::beg);

    while(fp.read((char*)&p,sizeof(p)));
    {
	if((p.set_id(),n)!=0)
	{
	    fp2.write((char*)&p,sizeof(p));
	}
    }
    fp2.close();
    fp.close();
    remove("bills.dat");
    rename("temp.dat","bill.dat");
    cout<<"\n\n\n\t\tRecord Deleted";
    getch();
}

void payment::modify_member()
{
    fstream fp1;
    int i = 0,x2;
    char n[6];
    int found = 0;
    clrscr();
    cout<<"\n\tModify Member Record\n";
    cout<<"\n\t\tID to be Modified\t";
    gets(n);
    fp1.open("bills.dat",ios::in|ios::out|ios::binary);

    while(fp1.read((char*)&p,sizeof(p)) && found == 0){
	if((p.set_id(),n)==0)
	{
	    cout<<"\n\n\n\t\t\t* * * * OLD DATA* * * * *";
	    p.put_units();
	    getch();
	    clrscr();
	    cout<<"\n\n\t\t\t( ( ( (NEW DETAILS ) ) ) )\n"<<endl;
	    p.modify_custmor();
	    x2 = (fp1.tellp()-sizeof(p));
	    cout<<"\n\n\n\t\t\t^ ^ ^ ^ Record Update ^ ^ ^ ^";
	    found = 1;
	    p.put_units();
	}
	i++;
    }
    fp1.close();
    if(found == 0)
    {
	cout<<"\n\n\n\t\t\t! ! ! Record Not Found ! ! !\n";
    }
    getch();
}

void payment::modify_custmor()
{
    cout<<"ID No YOU Want To Modify\t"<<id;
    cout<<"\n\n\t\t\tNew Name \t";
    gets(name);
    cout<<"\n\n\t\t\tModify Father's Name\t";
    gets(f_name);
    cout<<"\n\n\t\t\tNew Contact No\t";
    cin>>contact;

    while(1){
	if(strlen(contact)!=0)
	{
	    cout<<"\n\t\tContact must be of 10 digits";
	    cout<<"\n\t\t\tEnter Contact Again\t";
	    gets(contact);
	}
	else
	    break;
    }
    cout<<"\n\n\t\t\taddress\n";
    cout<<"\t\t\tNew House No\t";
    gets(hno);
    cout<<"\n\t\tNew Area \t:";
    gets(area);
    cout<<"\n\t\t\tNew State\t";
    gets(state);
    cout<<"\n\t\t\tNew Pincode\t";
    cin>>pin;
    while(1)
    {
	if(strlen(pin)!=6)
	{
	    cout<<"\n\nPin must be of 6 digit, Enter Pin again\t";
	    gets(pin);
	}
	else
	    break;
    }
}

void payment::login()
{
    char ch,user_id[30],user_pass[15],c,a,enter;
    char original_id[30]="neha",pass[15]="neha";
    int i = 0;
    int j;

    do
    {
	a:
	clrscr();
	gotoxy(30,20);
	cout<<"USER NAME:: ";
	cin>>user_id;
	if((strcmp(original_id,user_id))!=0)
	{
	    cout<<"\n\n\n\n\n\t\t\t\t\t!Sorry!\n\t\t\t\tIncorrect User Name  !!";
	    getch();
	    goto a;
	}
	else
	    {
		gotoxy(30,22);
		cout<<"PASSWORD :";

		while(1){
		    fflush(stdin);
		    ch = getch();
		    if(ch == 13)
			break;
		    else{
			cout<<"*";
			user_pass[i]=ch;
			i++;
		}
	    }
	    user_pass[i]='\0';
	    if((strcmp(pass,user_pass))!=0)
	    {
		gotoxy(41,28);
		cout<<"!SORRY!";
		gotoxy(31,30);
		cout<<"!! Wrong password entered!!";
		gotoxy(30,44);
		cout<<"Do you want to try again?.. ";
		cin>>c;
	    }
		else
		    break;
	}
    } while ((c=='y')||(c=='Y'));
    if(strcmp(pass,user_pass)==0)
    {
	gotoxy(31,40);
	cout<<"!!Password Accepted!!";
	getch();
	clrscr();
	p.admin_menu();
    }
}

void payment::admin_menu()
{
    int chh;
    char c2;
    fstream outfile,outfile1;
    clrscr();
    do{
	clrscr();
	cout<<"\n\n\t\t\t\t@ @ @ @ ADMIN MENU @ @ @ @\n";
	cout<<"\n\t\t\t1. Enter Details\n ";
	cout<<"\n\t\t\t2. Display Details All The Consumer \n ";
	cout<<"\n\t\t\t3. Display the details of Particular Record \n ";
	cout<<"\n\t\t\t4. Modify the record of Cosumer\n ";
	cout<<"\n\t\t\t5. Delete A Record\n ";
	cout<<"\n\t\t\t6. Back to main menu\n ";
	cout<<"\n\t\t\t0. Exit\n ";
	cout<<"\n\t\t\tEnter your choice\t";
	cin>>chh;
	switch(chh)
	{
	    case 0:
		exit(0);

	    case 1:
	    {
		outfile.open("bills.dat",ios::out|ios::app|ios::binary);

		if (!outfile)
		{
		    cout<<"Cant Open\n";
		    exit(0);
		}

		do
		{
		    cout<<"\n\t\t\t\tEnter the Details ";
		    p.get_units();
		    char y1;
		    cout<<"\n\t\tDo you want to save record press 's' for yess \t";
		    cin>>y1;
		    {
			if(y1=='s')
			{
			    outfile.write((char*)&p,sizeof(p));
			    cout<<"\n\n\t\t_ _ _ Record Saved _ _ _";
			}
			else
			    cout<<"\n\n\t\t_ _ _ (Record Not Saved) _ _ _";
		    }
		    cout<<"\n\n\n\n\n\t\t\tPress Y if you want to enter more records :";
		    cin>>c2;
		}while (c2=='y'||c2=='Y');

		outfile.close();
		break;
	    }
	    case 2:
	    {
		p.allm();
		getch();
		break;
	    }
	    case 3:
	    {
		p.find();
		getch();
		break;
	    }
	    case 4:
	    {
		p.modify_member();
		getch();
		break;
	    }
	    case 5:
	    {
		p.del();
		break;
	    }
	}
    }while(chh!=6);
    clrscr();
}


void payment::find()
{
     char n[10];
     int flag = 0;
     cout<<"Enter id :";
     gets(n);
     fstream file1;
     file1.open("bills.dat",ios::in|ios::binary);
     file1.seekg(0);

    while(file1.read((char*)&p,sizeof(p)));
    if((p.set_id(),n)==0)
    {
	flag = 1;
	p.put_units();
    }
    if(flag == 0)
    cout<<"File not found";
    file1.close();
}

void main()
{
    payment p;
    fstream outfile,outfile1;
    clrscr();
    int ch,c1,s;
    cout<<"\t\t********* PROJECT NAME : POWER CORPORATION *********"<<"\n\n\n\n";
    gotoxy(25,25);
    cout<<"\n SUMITTED BY";
    gotoxy(25,26);
    cout<<"\n NAME";
    gotoxy(25,27);
    cout<<"\n ROLL NO";
    gotoxy(25,28);
    cout<<"\n Class XII Science";
    gotoxy(25,29);
    cout<<"\n Session 2018-2019";
    gotoxy(25,30);
    cout<<"\n SCHOOL";
    gotoxy(25,31);
    cout<<"";

    do
    {
	cout<<"\n\n\n\t\t\t\t^^^^ MENU ^^^^\n\n";
	cout<<"\t\t\t1. ADMIN\n\n";
	cout<<"\t\t\t2. USER\n\n";
	cout<<"\t\t\t3. EXIT\n\n";
	cout<<"\n\t\t Enter Your Choice\t";
	cin>>ch;

	switch (ch)
	{
	    case 1:
		{
		    p.login();
		    break;
		}
	    case 2:

	    do
	    {
		clrscr();
		cout<<"\n\t\t\t1. Display your Details\n\n";
		cout<<"\n\t\t\t2. Check by Calculation\n\n";
		cout<<"\n\t\t\t0. Exit\n\n";
		cout<<"\t\t\t Enter your choice : \t";
		cin>>c1;

		switch (c1)
		{
		    case 1:
			p.find();
			getch();
			break;
		    case 2:
		    {
			int omr, nmr,unit,amtt,dueamt;
			cout<<"\n\t\t\told meter  reading\t";
			cin>>omr;
			cout<<"\n\t\t\tnew meter  reading\t";
			cin>>nmr;
			unit = nmr-omr;
			cout<<"\n\t\t\t\tLast due amount \t :";
			cin>>dueamt;

			if (unit>0 && unit <= 350)
			{
			    amtt = unit *2.5;
			}
			else
			    if(unit > 350 && unit <= 700)
				amtt = ((350*2.5)+(unit-350)*3.5);
			    if(unit > 700 && unit <= 1000)
				amtt = ((350*2.5)+(350*3.5)+(unit-700)*4);
			    else
				if(unit > 1000)
				amtt = ((350*2.5)+(350*3.5)+(700*4)+(unit-700)*5);
			cout<<"Billing amount = "<<amtt+dueamt<<"\n";
			cout<<"\n\n\tYou will get a discount of 150 if bill is paid before due date \n";
			cout<<"\n\n\t\tYour amount will be : "<<(amtt+dueamt)-150;
			getch();
			break;
			}
		    case 0:
			exit(0);

		    default:
			cout<<"! ! Entered wrong choice ! !";
			break;
		}
	    } while (c1!=3);
	case 3:
	    exit(0);

	    default:
		cout<<"! ! Entered wrong choice ! !";
	}
    }while (c1!=4);
}