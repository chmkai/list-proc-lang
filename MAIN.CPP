#include <iostream.h>
#include <conio.h>
#include <fstream.h>
#include <strings.h>
#include <stdio.h>

ifstream FILE("src.txt");

union atomu // Atom data union for use in atom class
{
    int num;
    char ch;
    int ptr; // integer added to heap.baseaddr() to get pointer to heapitem with pointer to unparsed string....woah, thi is getting meta...
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
    int* ptr; // REAL pointer to stored object
    char name[10]; // Identifier for reserved keyword, function,or varaible; in that order
public:
    heapitem()
    {
        strcpy(name,"NIL");
    }
    heapitem(int* p , char* i)
    {
        ptr = p;
        strcpy(name, i);
    }
    void setid(char n[])
    {
        strcpy(name, n);
    }
    void setaddr(int* ad)
    {
        ptr = ad;
    }
    int* addr() // Return pointer
    {return ptr;}

    char* id()  // Return identifier
    {return name;}
};


class Heap // Virtual Heap -- Data store for everything
{
public:
    heapitem index[32]; // Array of heapitem pointers. NOT pointer to heapitem array.
    heapitem* baseaddr() //returns 0-address of heap index
        {return &(index[0]);}
    int _alloc(userdefun f) //Allocates Statement
    {
        userdefun* _f = new userdefun(f); // 3 dereference levels for exec
        (*_f).setexec(f.retlist());
        int i = request();
        index[i].setid(f.getname());
        index[i].setaddr(_f);
        return i;
    }
    int _alloc(atom a, char n[]) //allocates user-defined variables.
    {
        atom* _var = new atom(a);
//        (*_var).setval(a.value(), a.rtype()); // Is this how it's done? I'm not sure. not sure if `->` works.
        int i = request();
        index[i].setid(n);
        index[i].setaddr(_var);
        return i;
    }
    char* _alloc(int&heapi, int sz = 32) //returns string address to write in. `&heapi` is the integer to hold the heapaddress
    {
        char* _str = new str[sz];
        int i = request();
        index[i].setid("NA");
        index[i].setaddr(_str);
        heapi = i;
        return _str; // use this return value for local string variable to write through. works as array.
    }
    int request() // Requests free memory space
    {
        for(int i = 0; i < 32; i++)
            if(!strcmpi(index[i].retname(),"NIL"))
                return i;
    }
    int search(char idf[])
    {
        for(int i = 0 ; i < 32; i++)
            if(!strcmpi(index[i].name,idf))
                return i;
    }
} heap;

class stack //This is the call stack. It acts as a virtual stack machine.
{
    func fp[8]; // function array
    int top; // The level of meta we're at.
public:
//    int fptr; // FILE POINTER VARIABLE
    stack()
    {
        top = -1; // UNLIMITED META
    }
    void push(func f) // Adds function to the top of the stack
    {
        if(top!=7) // Limited Meta?
        {
            top+=1;
            strcpy(fp[top].name,f.name);
            for(int i = 0; i < 8; i++)
                strcpy(fp[top].argv[i],f.argv[i]);
        }
        else
            cerr<<"[ERROR]Stack Overflow[ERROR]"<<endl;
    }
    void pop(func f) // takes out the last element in the stack
    {
        if(top!=-1) // More than technically limited meta!
        {
            top-=1;
        }
        else
            cerr<<"[ERROR]Stack underflow[ERROR]"<<endl;
    }
    int l() // Returns to Ravenholm... We don't go there anymore....
    {return top;}
} calls;

class atom
{
    char type;
    atomu val;
public:
    atom(){;} // Do we need this?
    atom(atom x) // COPY CONSTRUCTOR -- yes, we need this
    {
        type = x.type;
        switch (tolower(x.type))
            case 'n':
                val.num = x.val.num; break;
            case 'c':
                val.ch = x.val.ch;  break;
            case 'p':
                val.ptr = x.val.ptr; break;
        }
    }
    void set(atom x)
    {
        type = x.type;
        switch (tolower(x.type))
        {
            case 'n':
                val.num = x.val.num; break;
            case 'c':
                val.ch = x.val.ch;  break;
            case 'p':
                val.ptr = x.val.ptr; break;
        }
    }
    void settype(char t)
    {
        switch (t) {
            case 'n': case 'N':
            case 'c': case 'C':
            case 'p': case 'P':
                val.type = t; break;
        default:
            cerr<<"[ERROR]Atom conversion -- unknown type"<<t<<" [ERROR]"<<endl;
        }
    }
    char rtype() //returns type
    {return type;}
    int value() // CAUTION : USES INT RETURN, SEE BELOW
    {
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

class func //Statement functions
{
protected:
    char name[10]; // Function identifier
    atom argv[8]; // argument vector using array of strings
public:
    func()
    {name = "lambda";} // Keeps nameless functions as "lambda"
    func(char n[], atom a[]) // Constructor
    {
        strcpy(name,n);
        for(int i = 0; i < 8 ; i++)
            argv[i] = a[i];
    }
    func(func x) // Constructor
    {
        strcpy(name,x.name);
        for(int i = 0; i < 10 ; i++)
            strcpy(argv[i],x.argv[i]);
    }
    char* getname()
    {return name;}
    atom arg(int index) // ONE-indexed , start from 1 , end with 8
    {
        if(index > 0 && index <=8)
            return (index-1);
    }
    void setname(char n[])
    {
        strcpy(name, n);
    }
    void setarg(int n, atom x)
    {
        (f.arg[n-1]).set(x);
    }
};

class userdefun:public func // User defined function class
{
protected:
    char* list;
public:
    userdefun(char* ptr) {list = ptr} // Will this work?
    char* retlist()
    {return list;}
    void setexec(char* ptr) //set pointer to string being used as list to parse
    {
        list = ptr;
    }
};

char* genaddr(atom x)
{
    if(x.rtype = 'p')
        return (heap.index[x.value()]).addr();
}


atom parsechar() // Parses character -- Does not need to have another quote after
{
    char c;
    FILE.get(c);
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
    FILE.get(c);
    while(c != '\"')
    {
        sptr[space] = c;
        space++;
        FILE.get(c);
    }
    atom x;
    atom.set(heapi, 'p');
    return x;
}

atom parsequotes(char context = 'm',char* s_address)
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
    atom.set(heapi, 'p');
    return x;
}

atom parselist(char context = 'f', int tc = 0); // prototype

atom parseblock()
{
    char c;
    atom retom;
    FILE.get(c);
    while(c != '}')
    {
        switch(c)
        {
            case '(':
                retom.set(parselist());
                break;
            case '{':
                retom.set(parseblock());
                break;
            case '\"':
                retom set(parsequotes());
                break;
        }
    }
}

void readinput() //Base input function
{
    char c;
    FILE.get(c);
    atom NRTRN;
    NRTRN.set(parseblock()); // ASSUMES FIRST CHARACTER IS '{'
}

atom eval()
{

}

atom parselist(char context = 'f', int tc = 0) // context being 'f' means file , 'm' means in memory
{

    char token[8];
    func list;
    calls.push(list);

    int wc = 0; //current size of token being read
    int c_arg = 0; //no. of arguments read
    atom retom; // Atom to be returned
    do
    {
        char c;
        switch(context)
        {
            case 'f':
                FILE.get(c);
                break;
            case 'm':
                break;
        default:
                cerr<<"[ERROR]Unknown context[ERROR]";
        }
        switch(token)
        {
            case '(':
                retom.set(parselist(context, tc)); // HOLY META-RECUR-WHAT?
                list.setarg(c_arg, temp;)
                wc = 0;
                c_arg++;
                break;
            case ')':
                break;
            case '\'':
                atom temp(parsechar()); //constructor through parsechar() -- will it work?
                list.setarg(c_arg, temp;)
                wc = 0;
                c_arg++;
                break;
            case '\"':
                atom temp(parsequotes(context));
                list.setarg(c_arg, temp;)
                wc = 0;
                c_arg++;
                break;
            case '{':
                atom temp(parseblock());
            case 32:
                if(wc > 0)
                {
                    if(c_arg > 0)
                    {
                        int heapi;
                        char* stp = heap._alloc(heapi, 8);
                        strcpy(stp, token);
                        atom temp; // temporary atom to hold value b4 passing into list
                        temp.setval(heapi, 'p');
                        list.setarg(c_arg,temp);
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
    }while(token!=')');
    retom.set(/* eval() called here */);
}

/*
char* parselist(stack &calls, ifstream &fin) // For parsing individual lists - recursively passes all of them
{
   char token[8]; //Hold token for parsing

    while(fin.get(a))  // eval() somewhere inside here
    {
        if(a == '(')
        {
            calls.push(f)
            token = parselist(calls , fin); //Meta
        }
        if(a == ')')
        {
            return token;

        }
    }

}
*/
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

void main
{
     // @TODO :
    //Add some way to "include" function definition files?
    //These could contain function definitions created from basic ones
    //Decide if we are going to read directly from a text file
    //If so, how are we going to ignore all whitespace? Figure that out
    //Also, DONT TOUCH THE MAIN JUST YET.
    //Also, decide if we are going to need a menu.
    FILE.close();
}
