#include<iostream.h>
#include<conio.h>
#include<string.h>
#include<stdio.h>
#include<dos.h>

class question
{
	char question[100],op1[20],op2[20],op3[20];
	int ans;
	public:void addquestion()
	{
		cout<<"\nENTER YOUR QUESTION:";
		gets(question);
		cout<<"ENTER OPTION 1:";
		gets(op1);
		cout<<"ENTER OPTION 2:";
		gets(op2);
		cout<<"ENTER OPTION 3:";
		gets(op3);
		cout<<"ENTER ANSWER OPTION:";
		cin>>ans;
		}
		void show()
		{
			cout<<endl;
			puts(question);
			cout<<"\n1.\t"<<op1<<"\n2.\t"<<op2<<"\n3.\t"<<op3<<endl;
		}
		int returnanswer()
		{
			return ans;
		}
}quest;
class player
{
	char name[25];
	int score,idno;
	public:
		void getname()
		{
			cout<<"\nEnter Your Name:";
			gets(name);
			cout<<"\nEnter your Id number:";
			cin>>idno;
			score=0;
		}
		char*returnname()
		{
			return name;
		}
		void getscore(int temp)
		{
			score=temp;
		}
		void show()
		{
			cout<<endl<<idno<<"\t"<<name<<"\t\t"<<score;
		}
		int returnidno()
		{
			return idno;
		}
}s;
void menu()
{
	cout<<"===========================================================================";
	cout<<"\n||								  	||";
	cout<<"\n||								  	||";
	cout<<"\n||		 QQQQQQ	   U	  U   IIIII   ZZZZZZZZ			||";
	cout<<"\n||		QQ     Q   U	  U	I 	    Z	  		||";
	cout<<"\n||		Q Q    Q   U	  U	I	   Z 	  		||";
	cout<<"\n||		Q  Q   Q   U	  U	I	  Z	  		||";
	cout<<"\n||		Q   Q  Q   U	  U	I	 Z	  		||";
	cout<<"\n||		Q    Q Q   U	  U	I	Z		  	||";
	cout<<"\n||		Q     QQ   U	  U	I      Z      	  		||";
	cout<<"\n||		 QQQQQQQ    UUUUUU    IIIII   ZZZZZZZ	  		||";
	cout<<"\n||		       QQ				  		||";
	cout<<"\n||								  	||";
	cout<<"\n||								  	||";
	cout<<"\n||								  	||";
	cout<<"\n||			press any key to continue			||";
	cout<<"\n=========================================================================";
	getch();
}
int menu2()
{
	int choice;
	clrscr();
	cout<<"\n\t\tMENU\n\t1.Play Mode\n\t2.Devloper Mode";
	cout<<"\nENTER YOUR CHOICE :=> ";
	cin>>choice;
	return choice;
}
int menu3()
{
	int choice;
	clrscr();
	cout<<"====================================================================";
	cout<<"\n||								  ||";
	cout<<"\n||			     MENU				  ||";
	cout<<"\n||								  ||";
	cout<<"\n||	     	1	Play					  ||";
	cout<<"\n||								  ||";
	cout<<"\n||		2	Show Previous Records			  ||";
	cout<<"\n||								  ||";
	cout<<"\n||								  ||";
	cout<<"\n||		  	ENTER YOUR OPTION			  ||";
	cout<<"\n||								  ||";
	cout<<"\n||								  ||";
	cout<<"\n||                                                                ||";
	cout<<"\n====================================================================\n";
	cin>>choice;
	return choice;
}
void menu4()
{
	clrscr();
	ofstream kvout;
	ifstream kvin;
	kvout.open("quiznew.dat",ios::binary||ios::out);
	int n,pin,i;
	cout<<"\t\t\tWelcome To Devloper Mode";
	cout<<"\n\n\t\tEnter Pin to access developer mode:";
	cin>>pin;
	if(pin==1234)
	{
		cout<<"\n\nHow many questions you want to enter:";
		cin>>n;
		for(int i=0;i<n;i++)
		{
			quest.addquestion();
			kvout.write((char*)&quest,sizeof(quest));
		}
		cout<<"\nSaving changes";
		for(i=0;i<30;i++)
		{
			delay(30);
			cout<<".";
		}
		cout<<"!!Done!!\n";
		kvout.close();
	}
	else
	{
		cout<<"\nAccess denied";
	}
}
void play()
{
	clrscr();
	int temp,score,n=0,correct=0;
	s.getname();
	ifstream kvin;
	ofstream kvout;
	kvin.open("quiznew.dat",ios::binary|ios::in);
	while(kvin.read((char*)&quest,sizeof(quest)))
	{
		quest.show();
		cout<<"\nEnter your option(ans):";
		cin>>temp;
		if(temp==quest.returnanswer())
		{
			correct++;
			cout<<"\nRight answer!!";
		}
		else
		{
			cout<<"\nWrong Answer!!";
		}
		n++;
	}
	cout<<"\nYour Score is:"<<correct*10<<"/"<<10*n;
	kvout.open("record.dat",ios::binary|ios::ate);
	score=correct*10;
	s.getscore(score);
	kvout.write((char*)&s,sizeof(s));
	kvout.close();
	kvin.close();
}
void showrecord()
{
	ifstream kvin;
	ofstream kvout;
	int ans;
	kvin.open("record.dat",ios::binary|ios::in);
	cout<<"\nId\tName\t\tScore";
	while(kvin.read((char*)&s,sizeof(s)))
	{
		s.show();
	}
	kvin.close();
	cout<<"\nWould you like to delete any record:";
	cout<<"\n1\t Yes\n2\t No\n";
	cin>>ans;
	if(ans==1)
	{
		clrscr();
		cout<<"Now Showing Records Once Again\n";
		cout<<"Id\tName\t\tScore\n";
		kvin.open("record.dat",ios::binary|ios::in);
		while(kvin.read((char*)&s,sizeof(s)))
		{
			s.show();
		}
		kvin.close();
		cout<<"\nEnter the Id number of player whose record is to be deleted :=> ";
		int temp;
		cin>>temp;
		kvin.open("record.dat",ios::binary|ios::in);
		kvout.open("temp.dat",ios::binary|ios::out);
		while(kvin.read((char*)&s,sizeof(s)))
		{
			if(temp!=s.returnidno())
			{
				kvout.write((char*)&s,sizeof(s));
			}
		}
		kvin.close();
		kvout.close();
		remove("record.dat");
		rename("temp.dat","record.dat");
		cout<<"\nNow deleting if found";
		for(int i=0;i<30;i++)
		{
			delay(30);
			cout<<".";
		}
		cout<<"!!!Done!!!";
	}
}
void main()
{
	clrscr();
	menu();
	int ans,ans1,choice=0;
	do
	{
		ans=menu2();
		if(ans==1)
		{
			ans1=menu3();
			if(ans1==1)
			{
				play();
			}
			else if(ans1==2)
			{
				showrecord();
			}
		}
		else if(ans==2)
		{
			menu4();
		}
		cout<<"\n\nBack to Menu(press 1)\n\n\nTo Exit(Press 0)\n";
		cin>>choice;
	}while(choice==1);
}