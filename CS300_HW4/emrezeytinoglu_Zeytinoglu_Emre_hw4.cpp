#include <iostream>
#include <fstream>
#include <string>
#include "emrezeytinoglu_Zeytinoglu_Emre_hw4_DynStackHW4.h"
using namespace std;

//controling line number
int linecounter(ifstream & input,string line,int &linec){
    
    while(getline(input,line)){
        linec++;
    }
    return linec;
}

//controling stack
void controlcheck(DynStack & check, ifstream & input, int linenum, int k, string line, bool &control,int linec)
{
    
    char ch;
    int numofline;
    char charof = line.at(k);
	//push if open
    if((charof == '{') || (charof == '(') || (charof == '['))
    {
        check.push(charof, linenum);
        cout << "Found the opening symbol " << charof << " at line " << linenum << endl;
        control=true;
                
    }
	//pop if close
	else if((charof == '}') || (charof == ')') || (charof == ']'))
    {
        if (!check.isEmpty()){
            check.pop(ch,numofline);
        
            
            if(charof==')')
            {
            
                if(ch == '(')
                {

                    cout << "Found the closing symbol ) at line " << linenum << " which closes the opening symbol ( at line " << numofline << endl;
                    control=true;
                }
            }
            
            else if (charof == ']')
            {
            
                if(ch == '[')
                {
                    cout << "Found the closing symbol ] at line " << linenum << " which closes the opening symbol [ at line " << numofline << endl;
                    control=true;
                }
                        
            }
            else if (charof == '}')
            {
                if(ch == '{')
                {
                    cout << "Found the closing symbol } at line " << linenum << " which closes the opening symbol { at line " << numofline << endl;
                    control=true;
                }

            }
        }
        }
    //error check but i could not be successful
    else if ((charof == ')' && ch!='(')||(charof == ']' && ch!='[')||(charof == '}' && ch!='{'))
            {
                if(check.isEmpty())
                {
                    cout << "ERROR!!! Found the closing symbol "<< charof <<" but there are no unclosed opening symbols!" << endl;
                    control=false;
                }
                else
                {
                     cout << "ERROR!!! Found the closing symbol "<< charof <<" at line "<< linenum <<" but the last unclosed opening symbol is "<< ch <<" at line "<< numofline << endl;
                    control=false;
                }
            }
                    
                
        
    if(check.isEmpty() && linenum==linec)
        {
            cout << "File processed successfully. No errors were found." << endl;
            control=false;
         }
    }
                    
    
    
            
            





int main()
{
    int linec=0;
    ifstream input;
    string filename,line;
    DynStack check;
    cout << "Please enter the file name: ";
    cin >> filename;
    input.open(filename.c_str());
    //file control
	while(input.fail())
    {
        cout << "File not found." << endl;
        cout << "Please enter the file name: ";
        cin >> filename;
        input.open(filename.c_str());
    }
    int linect=linecounter(input,line,linec)-1;
    bool control=true;
    int k=0;
    input.clear();
    input.seekg(0);
	//getline and use function for checks
	for(int linenum = 1; getline(input,line) ;linenum++)
    {
        k=0;
        while(k < line.length()-1&&control == true)
        {
            
            controlcheck(check,input,linenum,k,line,control,linect);
            k++;
        }
        
    }
    return 0;
}