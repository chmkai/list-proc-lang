#include <iostream.h>
#include <conio.h>
#include <fstream.h>
#include <strings.h>
#include <stdio.h>

union atomu // Atom data union for use in atom class
{
    float num;
    char ch;
    int ptr; // integer added to heap.baseaddr() to get pointer to heapitem with pointer to unparsed string....woah, thi is getting meta...
};

class heapitem
{
    int* ptr; // REAL pointer to stored object
    char name[10]; // Identifier for reserved keyword, function,or varaible; in that order
public:
    heapitem()
    {
        strcpy(name,"NIL")
    }
    heapitem(int* p , char* i)
    {
        ptr = p;
        strcpy(name, i);
    }
    addr() // Return pointer
    {return ptr;}
    id()  // Return identifier
    {return name;}
};

class heap // Virtual Heap -- Data store for everything
{
    heapitem index[32]; // Array of heapitem pointers. NOT pointer to heapitem array.
public:
    heapitem* baseaddr() //returns 0-address of heap index
        {return &(index[0]);}
    heapitem* _alloc(userdefun f) //Allocates Statement
    {
// @TODO MAKE THIS
    }
    heapitem* _alloc(atom a) //allocates user-defined variables, strings and arrays, and other really long atoms
    {
// @TODO MAKE THIS
    }
    heapitem* request() // Requests free memory space
    {
        for(int i = 0; i < 32; i++)
            if(strcmpi(index[i].retname(),"NIL"))
                return (&(index[0]) + i);
    }
};

class stack //This is the call stack. It acts as a virtual stack machine.
{
    func fp[8]]; // function array
    int top; // The level of meta we're at.
public:
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
            cout<<"[ERROR]Stack Overflow[ERROR]"<<endl;
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
};

class atom
{
    char type;
    atomu val;
public:
    atom(atom x) // COPY CONSTRUCTOR -- yes, we need this
    {
        type = x.type;
        switch (tolower(x.type))
        {
            case 'n':
                val.num = x.val.num; break;
            case 'c':
                val.ch = x.val.ch;
            case 'p':
                val.ptr = x.val.ptr;
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
                return val.num;
            case 'c':
            case 'C':
                return val.ch;  // CAUTION: RETURNS CHARACTER AS NUMBER; NEEDS TO BE CONVERTED; SEE ABOVE
            case 'p':
            case 'P':
                return val.ptr;
        default:
            cerr<<"[ERROR]asked to return unknown type"<<t<<" [ERROR]"<<endl;
        }
    }
    // @TODO -add a set-value-function , checking the type and safely assigning both the `type` and `val` values
};

class func //Statement functions
{
protected:
    char name[10]; // Function identifier
    atom argv[8]; // argument vector using array of strings
public:
    func()
    {name = "lambda";} // Keeps nameless functions as "lambda"
    func(char n[], char* a[][]) // Constructor
    {
        strcpy(name,n);
        for(int i = 0; i < 10 ; i++)
            strcpy(argv[i],a);
    }
    func(func x) // Constructor
    {
        strcpy(name,x.name);
        for(int i = 0; i < 10 ; i++)
            strcpy(argv[i],x.argv[i]);
    }
    char* getname()
    {return name;}
};

class userdefun:public func // User defined function class
{
protected:
    char* list;
};

void readinput(char fname[]) //Base input function
{
    ifstream fin(fname);
    char c;
    stack calls; //creates the call stack for all functions
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
void main
{   // @TODO :
    //Add some way to "include" function definition files?
    //These could contain function definitions created from basic ones
    //Decide if we are going to read directly from a text file
    //If so, how are we going to ignore all whitespace? Figure that out
    //Also, DONT TOUCH THE MAIN JUST YET.
    //Also, decide if we are going to need a menu.
}
