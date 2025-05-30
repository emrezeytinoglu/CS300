#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;



//Emre Zeytinoglu




// struct of our matrix
struct cell
{
 char letter; // letter inside the cell
 char color; // color of the cell
};



// this function fills the matrix with letters and colors
void creatingmatrix(vector < vector < cell > > & mat ,int rows, string word, string guess, int & k)
{
	
	
	int wordlen = word.length();
	int a = 0;
	char ourvalue;
	
	
		while (a < wordlen)
		{
			if (guess.at(a) == word.at(a))
			{
				ourvalue = 'G';
				mat[k][a].color = ourvalue;
				mat[k][a].letter = guess.at(a);
				a++;
				 
			}
			else
			{
				if (word.find(guess.at(a)) != string::npos)
				{

					ourvalue = 'Y';
					mat[k][a].color = ourvalue;
					mat[k][a].letter = guess.at(a);
				}
				else
				{
					ourvalue = 'B';
					mat[k][a].color = ourvalue;
					mat[k][a].letter = guess.at(a);
				}
				a++;
			}
				
		}
	
	
	k++;
}


//this function checks inputs 
bool inputchecks(string word, string guess, vector <string> & arr, int attemptint, vector <vector <cell>> & mat)
{
	if (word.length() > guess.length())
	{
		cout << "The word is too short!" << endl;
		return false;
	}
	else if (guess.length() > word.length())
	{
		cout << "The word is too long!" << endl;
		return false;
	}
	
	
	
	else
	{
		
		unsigned int u = 0;
		
		while(u < word.length())
		{
			unsigned int o = 1;
			char firstletter = guess.at(u);
			if(!(firstletter >= 97 && firstletter <= 122))
			{
				cout << "Your input has illegal letters!" << endl;
				return false;
			}
			else
			{
				while( o < word.length())
				{
					char secondletter = guess.at(o);

					 if(firstletter == secondletter && u != o)
					{
						cout << "Your input has a duplicate letter!" << endl;
						return false;
					}
					o++;
				}
				
			}
			u++;
		}


			
		if ( arr.size() != 0)
			{
				int s = 0;
				while (s <= arr.size())
				{
					int q = 0;
					if(guess == arr[q])
					{
						cout << "You've already tried this word!" << endl;
						return false;
					}
					else
					{
						int m = 0;
						while(m < word.length())
						{
							if (mat[arr.size()-1][m].color == 'G' && guess[m] != mat[arr.size()-1][m].letter)
							{
								cout << "You did not use the green letter in your word!" << endl;
								return false;
							}
								m++;
						}
					
					}
					
					q++;
					s++;
				}
			}
		
		
		}
	

	}
			
			



	




//this function prints out our matrix
void printmatrix(vector < vector < cell > > & mat, int rows, int cols)
{
	
	
	int e = 0;
	while (e < rows)
	{
		
		cout << "||";
		int r = 0;
		while (r < cols)
		{
			cout << " " << mat[e][r].letter << " , " << mat[e][r].color << " ||";
			r++;


		}
		cout << endl;
		e++;


	}






}

// this function reports the result of the game
void printresult(string guess, string word)
{
	if (guess == word)
	{
		cout << "You win!" << endl;
	}
	else
	{
		cout << "You lose!" << endl;
	}


}

int main()
{
	ifstream input;
	string filename;
	string guess;
	
	
	cout << "Welcome to SWordle!" << endl;
	// get file input
	cout << "Please enter the file name: ";
	cin >> filename;
	input.open(filename.c_str());
	
	// ask until file opened
	while (input.fail())
	{
		cout << "Couldn't find the file!" << endl;
		cout << "Please enter the file name: ";
		cin >> filename;
		input.open(filename.c_str());
	}

	// reading file for attempt and word
	string line, attempt,word;
	int numlines = 0;
	while (getline(input,line))
	{
		if (numlines == 0)
		{
			
			 attempt = line;
		}
		else
		{
			  word = line;
		}
		numlines++;
	}
	int attemptint;
	stringstream ss;
	ss << attempt;
	ss >> attemptint;
	int rows = attemptint;
	int cols = word.length();
	vector < vector< cell > > mat;
	int i = 0;
	
	// while loop for filling our empty matrix
	while(i < attemptint)
	{
		mat.push_back(vector<cell>());
		int x= 0;
		while(x < cols)
		{
			cell wasd;
			wasd.letter = '-';
			wasd.color = '-';
			mat[i].push_back(wasd);
			x++;
		}

		i++;
	}
	// there is the main part of my code, it includes all functions that were created outside of the main part 
	int v= 0;
	int k = 0;
	vector <string> arr;
	cout << "The word that you will guess has " << cols << " letters and you have "<< attemptint <<" attempts." << endl;
	while(v < attemptint && word != guess)
	{
		
		cout << "What's your guess? ";
		cin >> guess;
		while (inputchecks(word, guess, arr, attemptint, mat) == false)
		{
			cout << "What's your guess? ";
			cin >> guess;
		}
		arr.push_back(guess);
		creatingmatrix(mat,rows,word,guess,k);
		printmatrix(mat, rows, cols);
		v++;
	}
	
	printresult(guess, word);
	


	
	











	return 0;
}