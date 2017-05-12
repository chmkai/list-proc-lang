
//List-Processor
//This is where the code for our program will be written.
//This is basic for now.
//Make new issues for each modification. This is the main dev.

#include <iostream.h>
#include <conio.h>
#include <fstream.h>
#include <stdio.h>

//Need to make functions.

void readinputandstore()
{
  cout<<"Enter "end" when the code is finished.";
  cout<<endl<<endl;
  
  ifstream fin("lpp.txt");
  
  char word[80];
  
  do
  {
    gets(word);
    fin>>word;
   
  }
  while(strcmpi("end",word)!=0);
  
  fin.close();
}

//swuareds












void main()
{
  cout<<"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Maecenas eget nibh vitae lorem scelerisque aliquam quis a metus. Sed et."
  getch();
}
