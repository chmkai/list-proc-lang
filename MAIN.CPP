#include <iostream.h>
#include <conio.h>
#include <fstream.h>
#include <stdio.h>

class stack //This is the call stack. It acts as a virtual stack machine..
{
    func fp[8]]; // function array
    int top;
public:
    stack()
    {
        top = -1;
    }
    push(func f) //adds function to the top of the stack
    {
        if(top!=7)
        {
            top+=1;
            strcpy(fp[top].name,f.name);
            for(int i = 0; i < 8; i++)
                strcpy(fp[top].argv[i],f.argv[i]);
        }
        else
            cout<<"[ERROR]Stack Overflow[ERROR]";
    }
    pop(func f) // takes out the last element in the stack
    {
        if(top!=-1)
        {
            top-=1;
        }
        else
            cout<<"[ERROR]Stack underflow[ERROR]";
    }
    top()
    {return top;}
};

class func //Statement functions
{
    char name[10]; // Function identifier
    char argv[8][8]; // argument vector using array of strings
public:
    func()
    {name = "lambda";} // Keeps nameless functions as "lambda"
    func(char n[], char* a[][]) // Copy Constructor
    {
        strcpy(name,n);
        for(int i = 0; i < 10 ; i++)
            strcpy(argv[i],a)
    }
}

void readinput(char fname[]) //Base input function
{
    ifstream fin(fname);
    char c;
    stack calls; //creates the call stack for all functions
}

void parselist(stack &calls, ifstream &fin) // For parsing individual lists - recursively passes all of them
{

}

void main
{
    //Add some way to "include" function definition files?
}
