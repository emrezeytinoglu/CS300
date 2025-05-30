#include <iostream>
#include <string>
#include <fstream>
using namespace std;




struct node
{
    char ch;
    node * next;
    node()
        :next(NULL)
    {}
    
};

void printnode1(node*head1)
{
    node * temp = head1;
    while(temp!=NULL)
    {
        cout << temp ->ch;
        temp=temp -> next;
    }


}
void printnode2(node*head2)
{
    node * temp = head2;
    while(temp!=NULL)
    {
        cout << temp ->ch;
        temp=temp -> next;
    }


}

 /* Begin: code taken from linkedlist.cpp */

void ClearList1(node * head1)
{
    node *ptr1=head1;
    while(head1!=NULL)
    {
        ptr1=head1;
        head1=head1->next;
        delete ptr1;
    }
}
 /* End: code taken from linkedlist.cpp */
void simcommand(node * head1, node * head2, int & similarity)
{
    node * temp1 = head1;
    node * temp2 = head2;
	similarity = 0;
    while(temp1!= NULL && temp2!=NULL)
    {
       
        if (temp1->ch == temp2->ch)
        {
            temp1 = temp1->next;
            temp2 = temp2->next;
            similarity++;
        }
        else
        {
            temp1 = temp1->next;
            temp2 = temp2->next;

        }
    }
    

}

// deleting chars 
void del1command(node * &head1,char key, int & k)
{
    node * temp1 = head1;
    k = 0;
    if(head1 == NULL)
    {
        cout << "No deletion as the value " << key <<" was not found in the list.";

    }
    else 
	{	
		if(head1 -> ch == key)
		{
			 head1 = head1->next;
			 if(head1->ch==key)
			 {
				 head1=head1->next;
			 }
			k++;
		}
		while(temp1 -> next != NULL)
        {
           
            if (temp1->next-> ch == key)
            {
                k++;
                node * ptr = temp1 -> next;
                temp1->next = temp1->next->next;
                delete ptr;
            }
            temp1 = temp1->next;
        }
        
    }
    
    
}




// inserting chars
node * insertcommand(node * head2, char key, char afterkey)
{
    node * temp2 = head2;
    
    while(temp2 != NULL && temp2 -> ch != key)
    {
        temp2 = temp2->next;
    }
    if (temp2!= NULL)
    {
            
            node * ptr2 = new node();
            ptr2->ch = afterkey;
            ptr2-> next = temp2->next;
            temp2->next = ptr2;
            cout << "Inserting " << afterkey << " after " << key << " in List1."<<endl;
            
    }
    else
    {
        cout << "Inserting " << afterkey << " after " << key << " in List1."<<endl;
        cout << "The node with " << key << " value does not exist. Therefore, Inserting " << afterkey << " at the beginning of the list." << endl;
        node * ptr2 = new node();
        ptr2 -> ch = afterkey;
        ptr2 -> next = head2;
        return ptr2;

    }
    return head2;
}



int main()
{
    string filename1,filename2;
    ifstream input1,input2;
    node * head1 = NULL;
    node * head2 = NULL;
    node * temp1 = head1;
    node * temp2 = head2;
    int k = 0 ,similarity = 0;
    char character1,character2;
    //opening file
	cout << "Please enter the file 1 name: ";
    cin >> filename1;
    input1.open(filename1.c_str());
    while (input1.fail())
    {
        cout << "Please enter the file 1 name: ";
        cin >> filename1;
        input1.open(filename1.c_str());
    }
    cout << "Please enter the file 2 name: ";
    cin >> filename2;
    input2.open(filename2.c_str());
    while (input2.fail())
    {
        cout << "Please enter the file 2 name : ";
        cin >> filename2;
        input2.open(filename2.c_str());
    }
	// filling linked list
    while (input1 >> character1)
    {
        
        node * ptr = new node();
        ptr -> ch = character1;
        ptr -> next = NULL;
        if (head1 == NULL)
        {
            head1 = ptr;
            temp1 = head1;
        }
        else
        {
            temp1 ->next=ptr;
            temp1 = temp1->next;
        }
        
    }
    
    while (input2 >> character2)
    {
        
        node * ptr2 = new node();
        ptr2 -> ch = character2;
        ptr2 -> next = NULL;
        if (head2 == NULL)
        {
            head2 = ptr2;
            temp2 = head2;
        }
        else
        {
            temp2 ->next=ptr2;
            temp2 = temp2->next;
        }
        
    }
    cout << "List1: ";
    printnode1(head1);
    cout << endl;
    cout << "List2: ";
    printnode2(head2);
    cout << endl;
	cout << endl;
    string commands;
    char argument1, argument2;
    cout << "Enter a command and its corresponding argument(s), if any: ";
    cin >> commands;
	//checking commands and using functions
	while(commands != "exit")
    {
        
        if(commands == "sim")
        {
            cout << "Displaying the contents of the two lists:" << endl;
            cout << "List1: ";
            printnode1(head1);
            cout << endl;
            cout << "List2: ";
            printnode2(head2);
            cout << endl;
            simcommand(head1, head2, similarity);
            cout << "There is/are "<< similarity << " letter(s) matched in the same positions in both lists." << endl;
        }
    
        else if(commands == "del1" )
        {
            cin >> argument1;
            if ((argument1 >= 'a') && (argument1 <= 'z'))
            {
                del1command(head1,argument1, k);
                if(k== 0)
                {
                    cout << "No deletion as the value " << argument1 <<" was not found in the list.";
                    cout << endl;
                }
                else
                {
                    cout << "Deleting all occurrences of " << argument1 << " in List1." << endl << "The current content of List1 is: ";
                    printnode1(head1);
                }
            }
            else
            {
                cout << "Invalid arguments." << endl;
            }

        }
        else if(commands == "del2" )
        {
            cin >> argument1;
            if ((argument1 >= 'a') && (argument1 <= 'z'))
            {
                del1command(head2,argument1, k);
                if(k==0)
                {
					cout << "No deletion as the value " << argument1 <<" was not found in the list.";
                    cout << endl;
                }
				 else
                {
                    cout << "Deleting all occurrences of " << argument1 << " in List1." << endl << "The current content of List1 is: ";
                    printnode2(head2);
                }
            }
            else
            {
                cout << "Invalid arguments." << endl;
            }
        }
        else if(commands == "insert1" )
        {
            cin >> argument1 >> argument2;
            if ((argument1 >= 'a' && argument1 <= 'z')&&((argument2 >= 'a' && argument2 <= 'z')))
            {
            
                head1 = insertcommand(head1, argument2 , argument1);
                cout << "The current content of List1 is: ";
                printnode1(head1);
                cout << endl;
            }
            else
            {
                cout << "Invalid arguments." << endl;
            }
        }
        else if(commands == "insert2" )
        {
            cin >> argument1 >> argument2;
            if ((argument1 >= 'a' && argument1 <= 'z')&&(argument2 >= 'a' && argument2<= 'z'))
            {
                
                head2 = insertcommand(head2, argument2 , argument1);
                cout << "The current content of List2 is: ";
                printnode2(head2);
                cout << endl;
            }
            else
            {
                cout << "Invalid arguments." << endl;
            }
        }
        else
        {
            cout << "Invalid command." << endl;
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }

        cout << endl;
        cout << "Enter a command and its corresponding argument(s), if any: ";
        cin >> commands;
        
    }
     cout << "Clearing the two lists and saying Goodbye!" << endl;
     ClearList1(head1);
     ClearList1(head2);


    return 0;
}