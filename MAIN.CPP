#include <iostream.h>
#include <conio.h>
#include <fstream.h>
#include <stdio.h>
#include <stdio.h>

union atomu
{
    float num;
    char ch;
    int ptr;
};

class heapitem
{
    int* ptr; // REAL pointer to stored object
    char name[10]; // Identifier for reserved keyword, function,or varaible; in that order
public:
    heapitem(int* p , char * i)
    {
        ptr = p;
        strcpy(name, i);
    }
    addr()
    {return ptr;}
    id()
    {return name;}
}

class heap // Virtual Heap
{
    heapitem* index[256]; // Array of heapitem pointers. NOT pointer to heapitem array.
public:
    baseaddr() //returns 0-address of heap index
        {return &(index[0]);}
    falloc() //Allocates Statement
    {

    }
    valloc() //allocates user-defined varaibles, strings and arrays, and other really long atoms
    {

    }
}

class stack //This is the call stack. It acts as a virtual stack machine..
{
    func fp[8]]; // function array
    int top; // The level of meta we're at.
public:
    stack()
    {
        top = -1; // UNLIMITED META
    }
    push(func f) // Adds function to the top of the stack
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
    pop(func f) // takes out the last element in the stack
    {
        if(top!=-1) // More than technically physically limited meta!
        {
            top-=1;
        }
        else
            cerr<<"[ERROR]Stack underflow[ERROR]"<<endl;
    }
    top() // Returns to Ravenholm... We don't go there anymore....
    {return top;}
};

class atom
{
    char type;
    atomu val;
public:
    settype(char t)
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

};

class func //Statement functions
{
    char name[10]; // Function identifier
    char argv[8][8]; // argument vector using array of strings
public:
    func()
    {name = "lambda";} // Keeps nameless functions as "lambda"
    func(char n[], char* a[][]) // Copy Constructor // Do we need this?
    {
        strcpy(name,n);
        for(int i = 0; i < 10 ; i++)
            strcpy(argv[i],a)
    }
    char* getname()
    {return name;}
}

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
{
    //Add some way to "include" function definition files?
    //These could contain function definitions created from basic ones
    //Decide if we are going to read directly from a text file
    //If so, how are we going to ignore all whitespace? Figure that out
    //Also, DONT TOUCH THE MAIN JUST YET.
    //Also, decide if we are going to need a menu.
}
