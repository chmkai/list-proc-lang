//Line-Processor
//This is where the code for our program will be written.
//This is basic for now.
//Make new issues for each modification. This is the main dev.

#include <iostream.h>
#include <conio.h>
#include <fstream.h>
#include <stdio.h>

//Predefined variables
int v=0,w=0,x=0,y=0,z=0

//Need to make functions.

void readinputandstore()
{
  cout<<"Enter "end" when the code is finished.";
  cout<<endl<<endl;
  
  ofstream fout("lpp.txt");
  
  char word[80];
  
  for(;;)
  {
    gets(word);
    
    if(strcmpi(word,"end")!=0)
        fout<<word;
    else 
        break;
  }
  fout.close();
}

//Treat input as lines. Process accordingly.

void process()
{
    ifstream fin("lpp.txt")
    char st[80];
      
    while(fin.getine(st))
    {
      if (st[0]=='p')
        print(st);
      else if(st[0]=='a')
        add(st);
      else if(st[0]=='s')
        subtract(st);
      else if(st[0]=='m')
        multiply(st);
      else if(st[0]=='d')
        divide(st);
			else if(st[0]=='r')
				read(st);
    }
  
  fin.close();
}

//Prints
void print(char st[])
{
	int textflag=0;
  for (int i=7;i<strlen(st);i++)
	{
		if(st[6]=='"')
		{
     cout<<st[i];
			textflag=1;
		}
		if(st[i]=='"')
			break;
	}
	
	if (textflag==0)
		switch (st[6])
		{
			  case 'v':		cout<<v;break;
				case 'w':		cout<<w;break;
				case 'x':		cout<<x;break;
				case 'y':		cout<<y;break;
				case 'z':		cout<<z;break;
		}
	
	
  cout<<endl;
}

/*Now we have input stored. We need to analyze this input and process it in order to program using this language.*/

void menu()
{
  int op;

  do{
    
  clrscr();
    
  cout<<"Hello and welcome to SLANG2, a student-made programming language! Here, you will learn the basics of programming.\n"
  cout<<"Kindly refer to the chart on your left for further instructions, because Kolko was lazy and forgot to programme this in.\n"
  
  cout<<"\n\nMENU\n\n\n";
  
  cout<<"1.Begin writing code.\n";
  cout<<"2.Run the code.\n";
  cout<<"3.Exit.\n";
  
  cout<<"\n\n\nSelect an option (number please!) :";
  cin>>op;
  
  switch (op)
    {
      case 1: readinputandstore();break;
      
      case 2: processing();break;  
    }
  }while(op!=3);    
}

void main()
{
  cout<<"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Maecenas eget nibh vitae lorem scelerisque aliquam quis a metus. Sed et."
  menu();
  getch();
}
