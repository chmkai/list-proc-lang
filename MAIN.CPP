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
        strcpy(name,"NIL");
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

    }
    heapitem* _alloc(atom a) //allocates user-defined variables, strings and arrays, and other really long atoms
    {
// @TODO: Make This
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
};

class atom
{
    char type;
    atomu val;
public:
    atom(){;}
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
                return val.num; break;  // CAUTION : CONVERT TO FLOAT
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
    void setval(int v, int is_ptr) // explicitly convert to int b4 passing char to v.
    {
        if(is_ptr == 0)
        {
            if(v >= 48 && v <= 57) // use char for numbers too...
                val.num = float(v - 48);
            else
                if(v >= 32 && v <= 127)
                    val.ch = char(v);
        }
        else
        {
            val.ptr = v;
        }
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
};

class userdefun:public func // User defined function class
{
protected:
    char* list;
public:
    userdefun(char* ptr) {list = ptr} // Will this work?
    void setexec(char* ptr)
    {
        list = ptr;
    }
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
