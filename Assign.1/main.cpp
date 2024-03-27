/*
================================================================================
* Lani Do
* CIS22B
* Assignment #1
* 01/18/23
*/

#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
using namespace std;
const int LENGTH = 4;

// Function prototypes
void InitializeCards(int cards[][LENGTH]);
void ShowCards(int cards[][LENGTH], bool faceup[][LENGTH]);

// ======================
//     main function
// ======================
int main()
{
	// 1) Welcome the user and ask their full name.

        string firstname;
		string lastname;

        int attempts = 0;
        cout << "Welcome to a memory game! \nPlease enter your full name: ";
        cin >> firstname >> lastname;

		//getline(cin, name); so name can have many words
        
		cout << "Find all the matching pairs on the board!" << endl;

	// 2) Create 2D array holding the number of each card. Pass it to InitializeCards function. 

        int cards[4][4];
        InitializeCards(cards);

	// 3) Create 2D array of Booleans that represents whether or not the card is matched. 

	    bool match[4][4]={false};

	// 4) while the game is not over :
	
	while(true){
		
		// 	Display the current state of the game board. non-matched pairs should be "facedown" and matched pairs should be "faceup"
		
		ShowCards(cards,match);

		// 	Prompt the user to enter the coordinates of two cards
		// 	Note: user can choose to quit 
		
		int x1, x2, y1, y2;
		while (true)
		{
			cout << "\nEnter x and y position of the 1st card:";
			cin >> x1 >> y1;
			cout << "Enter x and y position of the 2nd card:";
			cin >> x2 >> y2;

			//check if coordinates are valid
			if (x1<0 || x2<0 ||y1<0 ||y2<0 || x1>=LENGTH || x2>=LENGTH || y1>=LENGTH || y2>=LENGTH)
				cout << "Invalid coordinated detected! Please enter another coordinate number between 0 and " << LENGTH-1 << endl;
			//check if the cards have already been matched & flipped
			else if (match[x1][y1]==true || match[x2][y2]==true)
				cout << "You've already flipped this card. Please choose another one\n";
			else
				break;
		}

		char c; 
		match[x1][y1]=true; 
		match[x2][y2]=true;
		ShowCards(cards,match);

		// 	If the values of the two coordinates match : flip the cards over forever
		// 	else : temporarily flip over the cards to show the user the values, then flip them over again.
		if (cards[x1][y1]==cards[x2][y2])
			cout << "You've found a match!\n" << endl;
		else
		{
			match[x1][y1]=false; 
			match[x2][y2]=false;
			cout << "No match\n" << endl;
			cout << "Flipping cards over again... \nEnter 'q' to quit or press any key to continue... ";
			cin >> c; 
			//cin.get(c) so 'Enter' key will be included
		}
		attempts++;
		
		// check if user want to continue/quit
		if (c == 'q')
			break;
	}
	// 5) Save the user’s name and how many turns it took to win the game into an output text file. If he quits
	// before winning save “Don’t give up” message in the file.

		ofstream myfile;
		myfile.open("numberOfAttempts.txt"); 

		//no need to check if file exists for output b/c u just created it above??
		//don't include "Dont give up" if user WINS the game
			//check for c=='q' again to print that....

		myfile << firstname << " " << lastname;
		myfile <<"\nNumber of attempts: " << attempts << "\nDon’t give up!";
		myfile.close();		
		
}
// InitializeCards
// Places pairs of numbers in the 2D array and then
// randomly shuffles them.
// ======================
//Notice that when you pass a 2D-array to a function, you MUST specify the number of columns
void InitializeCards(int cards[][LENGTH])
{
	//seed rand() - remember to always do this before using rand()
	srand(time(0));
	int x1, y1, x2, y2;
	int i;
	int temp;

	// Place pairs in known locations -   this is how our array looks like after
	cards[0][0] = 1; cards[0][1] = 1;//   1  1  2  2
	cards[0][2] = 2; cards[0][3] = 2;
	cards[1][0] = 3; cards[1][1] = 3;//   3  3  4  4
	cards[1][2] = 4; cards[1][3] = 4;
	cards[2][0] = 5; cards[2][1] = 5;//   5  5  6   6
	cards[2][2] = 6; cards[2][3] = 6;
	cards[3][0] = 7; cards[3][1] = 7;//   7  7  8   8
	cards[3][2] = 8; cards[3][3] = 8;

	// Now that 2D has been initialized with 8 pairs, we want to shuffle the board so
	// that the pairs aren't right next to each other
	for (int i = 0; i < 30; i++) {
		//Get set of random coordinates and swap
		//First random coordinate on our 2d "grid"
		y1 = rand() % LENGTH;
		x1 = rand() % LENGTH;
		//Second random coordinate of our 2d "grid"
		y2 = rand() % LENGTH;
		x2 = rand() % LENGTH;

		//Now we swap value at (x1, y1) with value at(x2, y2)
		temp = cards[x1][y1];
		cards[x1][y1] = cards[x2][y2];
		cards[x2][y2] = temp;
		//Note: just like with 1D arrays, modifying an n-dimensional array inside
		// a function will change the array itself
	}
}
// ======================
// ShowCards
// Generates a display on the screen.  If faceup=false,
// an * is output, otherwise the card in that slot is output.
// ======================
void ShowCards(int cards[][LENGTH], bool faceup[][LENGTH]) {

	cout << "\n     0 1 2 3 " << endl;
	cout << "    ========= " << endl;
	for (int i = 0; i < LENGTH; ++i){
		cout << i << "  | ";
		for (int j = 0; j < LENGTH; j++){
			if (faceup[i][j] == true)
				cout << cards[i][j] << " ";
			else
				cout << "* ";
		}
		cout << "|" << endl;
	}
	cout << "    ========= "  << endl;
}
