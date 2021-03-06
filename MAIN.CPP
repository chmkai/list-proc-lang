#include <iostream.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <fstream.h>
#include <string.h>
#include <stdio.h>

//Declarations:
class atom;
class func;
class userdefun;
class heapitem;
class Heap;
class stack;


ifstream File("src.txt");

union atomu // Atom data union for use in atom class
{
	int num;
	char ch;
	int ptr; // integer added to heap.baseaddr() to get pointer to heapitem with pointer to unparsed string....woah, thi is getting meta...
};


class atom
{
	char type;
	atomu val;
public:
	atom() // NOW we need this
	{
		type = 'x'; // Unknown type
	}
	atom(atom &x) // COPY CONSTRUCTOR -- yes, we need this
	{
		type = x.rtype();
		switch (tolower(x.rtype()))
		{
			case 'n':
				setval(x.value(), 'n'); break;
			case 'c':
				setval(char(x.value()), 'c');  break;
			case 'p':
				setval(x.value(), 'p'); break;
		}
	}
	void set(atom x)
	{
		type = x.type;
		switch (tolower(x.rtype()))
		{
			case 'n':
				val.num = x.value(); break;
			case 'c':
				val.ch = x.value();  break;
			case 'p':
				val.ptr = x.value(); break;
		}
	}
	void settype(char t)
	{
		switch (t) {
			case 'n': case 'N':
			case 'c': case 'C':
			case 'p': case 'P':
				type = t; break;
		default:
			cerr<<"[ERROR]Atom conversion -- unknown type"<<t<<" [ERROR]"<<endl;
		}
	}
	char rtype() //returns type
	{return type;}
	int value() // CAUTION : USES INT RETURN, SEE BELOW
	{   if(type == 'x')
			cerr<<"[ERROR] atom of unknown type [ERROR]";
		switch(type)
		{
			case 'n':
			case 'N':
				return val.num; break;
			case 'c':
			case 'C':
				return val.ch; break; // CAUTION: RETURNS CHARACTER AS NUMBER; NEEDS TO BE CONVERTED; SEE ABOVE
			case 'p':
			case 'P':
				return val.ptr; break;
//        default:
//            cerr<<"[ERROR]asked to return unknown type"<<t<<" [ERROR]"<<endl;
		}
	}
	void setval(int v, char t) // explicitly convert to int b4 passing char to v.
	{
		if(tolower(t) == 'c' )
		{ val.ch = char(v); settype(t);}
		else
			if(tolower(t) == 'n')
				{ val.num = v; settype(t);}
			else
				if(tolower(t) == 'p')
					{ val.ptr = v; settype(t);}
				else
					cerr<<"[ERROR] Request to set value of unknown type"<<t<<" [ERROR]";
	}
};

class squarelist
{
	atom list[8];
public:
	void setarg(int i, atom a)
	{list[i].set(a);}
	atom item(int i)
	{return list[i];}
};

class func //Statement functions
{
protected:
	char name[10]; // Function identifier
	atom argv[8]; // argument vector using array of strings
public:
	func()
	{strcpy(name, "lambda");} // Keeps nameless functions as "lambda"
	func(char n[], atom a[]) // Constructor
	{
		strcpy(name,n);
		for(int i = 0; i < 8 ; i++)
			arg(i).setval(a[i].value() , a[i].rtype());
	}
	func(func &x) // Constructor
	{
		strcpy(name,x.name);
		for(int i = 1; i < 9 ; i++)
			arg(i).setval(x.arg(i).value() , x.arg(i).rtype());
	}
	char* getname()
	{return name;}
	atom arg(int index) // ONE-indexed , start from 1 , end with 8
	{
		if(index > 0 && index <=8)
			return argv[index-1];
	}
	void setname(char n[])
	{
		strcpy(name, n);
	}
	void setarg(int n, atom x)
	{
		(argv[n-1]).set(x);
	}
};

class userdefun:public func // User defined function class
{
protected:
	char* list;
public:
	 userdefun() {;} // Does this even work?
	userdefun(char* ptr) {list = ptr;} // Will this work?
	char* retlist()
	{return list;}
	void setexec(char* ptr) //set pointer to string being used as list to parse
	{
		list = ptr;
	}
};


/* PARSER RESOLVE -- KolkonutDev1
class func
{
  public:
  char argv[100][100]

};
void parselist()
{
  char atom[100];
  ifstream fin("llp.txt");
  int i=0,x=0;

  while(fin>>atom)
  {
	if(atom[0]=='(')
	  x+=1;
	if(atom[strlen(atom)]==')')
	  x-=1;

	if(x!=0)
	  strcpy(argv[i],atom);
	i++;
  }

  fin.close();
}


*/ //Keep reference, delete later


class heapitem
{
	void* ptr; // REAL pointer to stored object
	char name[10]; // Identifier for reserved keyword, function,or varaible; in that order
public:
	heapitem()
	{
		strcpy(name,"NIL");
	}
	heapitem(void* p , char* i)
	{
		ptr = p;
		strcpy(name, i);
	}
	void setid(char n[])
	{
		strcpy(name, n);
	}
	void setaddr(void* ad)
	{
		ptr = ad;
	}
	void* addr() // Return pointer
	{return ptr;}

	char* id()  // Return identifier
	{return name;}
};


class Heap
{
public:
	heapitem index[32];
	heapitem* baseaddr() //returns 0-address of heap index
		{return &(index[0]);}
	int _alloc(userdefun f) //Allocates Statement
	{
		userdefun* _f = new userdefun(f);
		(*_f).setexec(f.retlist());
		int i = request();
		index[i].setid(f.getname());
		index[i].setaddr((void *)_f);
		return i;
	}
	int _alloc(atom a, char n[]) //allocates user-defined variables.
	{
		atom* _var = new atom(a);
//        (*_var).setval(a.value(), a.rtype());
		int i = request();
		index[i].setid(n);
		index[i].setaddr((void *)&_var);
		return i;
	}
	char* _alloc(int&heapi, int sz = 32) //returns string address to write in. `&heapi` is the integer to hold the heapaddress
	{
		char* _str = new char[sz];
		int i = request();
		index[i].setid("NA");
		index[i].setaddr((void *)_str);
		heapi = i;
		return _str; // use this return value for local string variable to write through. works as array.
	}
	int request() // Requests free memory space
	{
		for(int i = 0; i < 32; i++)
			if(!strcmpi(index[i].id(),"NIL"))
				return i;
	}
	int search(char idf[])
	{
		for(int i = 0 ; i < 32; i++)
			if(!strcmpi(index[i].id(),idf))
				return i;
	}
} heap;    // THIS DOES NOT WORK BUT IT WORKS

class stack
{
	func fp[8]; // list array
	int top;
public:
//    int fptr; // FILE POINTER VARIABLE
	stack()
	{
		top = -1;
	}
	void push(func f) // Adds function to the top of the stack
	{
		if(top!=7)
		{
			top+=1;
			strcpy(fp[top].getname(),f.getname());
			for(int i = 0; i < 8; i++)
				fp[top].arg(i+1).setval(f.arg(i+1).value() , f.arg(i+1).rtype());
		}
		else
			cerr<<"[ERROR]Stack Overflow[ERROR]"<<endl;
	}
	void pop() // takes out the last element in the stack
	{
		if(top!=-1)
		{
			top-=1;
		}
		else
			cerr<<"[ERROR]Stack underflow[ERROR]"<<endl;
	}
	int l()
	{return top;}
} calls;

void* genaddr(atom x)
{
	if(x.rtype() == 'p')
		return (heap.index[x.value()]).addr();
}

atom parsechar() // Parses single character
{
	char c;
	File.get(c);
	atom x;
	x.setval(int(c), 'c');
	return x;
}

atom parsequotes(char context = 'f') //Parses strings and passes back a ptr-atom
{
	int heapi;
	char c;
	int space = 0;
	char* sptr = heap._alloc(heapi);
	File.get(c);
	while(c != '\"')
	{
		sptr[space] = c;
		space++;
		File.get(c);
	}
	atom x;
	x.setval(heapi, 'p');
	return x;
}
/*
atom parsequotes(char* s_address, char context = 'f')
{
	int heapi;
	char c;
	int space = 0;
	char* sptr = heap._alloc(heapi);
	do
	{
		c = s_address[space];
		sptr[space] = c;
		space++;
	}while(s_address[space+1] != '\"');
	atom x;
	x.setval(heapi, 'p');
	return x;
}
*/
atom parselist(char context = 'f', int tc = 0); // prototype

atom parseblock()
{
	char c;
	atom retom;
	File.get(c);
	while(c != '}')
	{
		switch(c)
		{
			case '(':
				retom.set(parselist('f' , 0));
				break;
			case '{':
				retom.set(parseblock());
				break;
			case '\"':
				retom.set(parsequotes('f'));
				break;
		}
		File.get(c);
	}
}

void readinput() //Base input function
{
	char c;
	File.get(c);
	atom NRTRN;
	NRTRN.set(parseblock()); // ASSUMES FIRST CHARACTER IS '{'
}

atom eval(func f)
{
	if(!strcmpi(f.getname(), "+")) // Thanks, KolkonutDev1 !
	{
		int sum=0;
		for (int i=1;i<9;i++)
			if((f.arg(i)).rtype() == 'n')
				sum+=f.arg(i).value();
		atom x;
		x.setval(sum,'n');
		return x;
	}
	else if(!strcmpi(f.getname(), "-")) // Thanks, KolkonutDev1 !
	{
		int sum=0;
		for (int i=2;i<9;i++)
			if((f.arg(i)).rtype() == 'n')
			sum+=f.arg(i).value();
			atom x;
			x.setval(f.arg(1).value()-sum,'n');
		return x;
	}
	else if(!strcmpi(f.getname(), "*")) //Thanks, KolkonutDev1 !
	{
		int prod=1;
		for (int i=1;i<9;i++)
		if((f.arg(i)).rtype() == 'n')
			prod*=f.arg(i).value();
		atom x;
		x.setval(prod,'n');
		return x;
	}
	else if(!strcmpi(f.getname(), "/")) //Thanks, KolkonutDev1 !
	{
		int quo=0;
		if((f.arg(1)).rtype() == 'n'&&(f.arg(2)).rtype() == 'n')
			quo=f.arg(1).value()/f.arg(2).value();
		atom x;
		x.setval(quo,'n');
		return x;
	}
	else if(!strcmpi(f.getname(), "%")) //Thanks, KolkonutDev1 !
	{
		int quo=0;
		if((f.arg(1)).rtype() == 'n' && (f.arg(2)).rtype() == 'n')
		quo=f.arg(1).value()%f.arg(2).value();
		atom x;
		x.setval(quo,'n');
		return x;
	}
	else if(!strcmpi( f.getname() , "echo"))
	{
		for(int i = 1 ; i < 9 ; i++)
				if((f.arg(i)).rtype()  == 'p')
					  cout<< (heap.index[(f.arg(i)).value()]).addr();
				else
					if((f.arg(i)).rtype() != 'x')
						cout<< f.arg(i).value();
// NOT A TYPO .DO NOT DEREFERENCE  (put *) HERE AS `cout`ING ADDRESS SHOULD PRINT THE WHOLE THING
		cout<<endl;
	}
}

atom parselist(char context, int tc) // context being 'f' means file , 'm' means in memory
{

	char token[8];
	func list;
	calls.push(list);
	char c;
	int wc = 0; //current size of token being read
	int c_arg = 0; //no. of arguments read
	atom retom; // Atom to be returned
	do
	{
		switch(context)
		{
			case 'f':
				if(!File.eof())
					File.get(c);
				cout<<"f";
				break;
			case 'm':
				cout<<"m";
				break;
		default:
			  //	cerr<<"[ERROR]Unknown context[ERROR]";
			  cerr<<"u";
		}
		switch(c)
		{
			case '(':
				atom temp1(parselist(context));
				list.setarg(c_arg, temp1);
				wc = 0;
				c_arg++;
				break;
			case ')':
				break;
			case '\'':
				atom temp2(parsechar());
				list.setarg(c_arg, temp2);
				wc = 0;
				c_arg++;
				break;
			case '\"':
				atom temp3(parsequotes(context));
				list.setarg(c_arg, temp3);
				wc = 0;
				c_arg++;
				break;
			case '{':
				atom temp4(parseblock());
				list.setarg(c_arg, temp4);
				wc = 0;
				c_arg++;
				break;
			case '\n':
			case '\t':
			case 32:
				if(wc > 0)
				{
					if(c_arg > 0)
					{
						int heapi;
						char* stp = heap._alloc(heapi, 8);
						strcpy(stp, token);
						atom temp5; // temporary atom to hold value b4 passing into list
						temp5.setval(heapi, 'p');
						list.setarg(c_arg,temp5);
					}
					else
					if(c_arg == 0)
						list.setname(token);
					else
						cerr<<"[ERROR]Negative Current Argument for list in stack \"calls\"[ERROR]";
					c_arg++;
					wc = 0;
				}
				break;
		default:
			token[wc] = c;
			wc++;
		}
		tc++;
	}while(c!=')');
	retom.set(eval(list));
	calls.pop();
	return retom;
}


/* KolkonutDev1 RESOLVE
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

*/ //Keep as ref , delete later

void main()
{
	clrscr();
	cout<<getch();
	atom test(parselist('f', 0));
	cout<<test.value();
	getch();
	File.close();
}
