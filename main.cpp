// Elisaveta Peeva 180012881
// Taha Kashaf 180020889
// Laura Hutchison 180017529


#include <iostream>
#include <limits>
#include "methodHeaders.h"
#include <iostream>
#include <cstring>
#include <string.h>
#include <iomanip>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

/* 

1. Get the user to input a rule;
2. Get the binary number for this rule;
3. 

*/

// This method handles the "logic" for the menu.
void menuSwitch(int switcher) {
	switch(switcher) {
		case 1: {
			decToBinaryNoR();
			cout << "\n";
			cout << "=============SUCCESS!=============";
			cout << "\n";
			cout << "Enter Anything To Return to the Menu: ";
			string worthless;
			cin >> worthless;
			menu();
			break;
		}
  		case 2: {
  			binaryToDecimal();
			cout << "\n";
			cout << "=============SUCCESS!=============";
			cout << "\n";
			cout << "Enter Anything To Return to the Menu: ";
			string worthless;
			cin >> worthless;
			menu();
    		break;			
		}
		case 3: {
			int choice = rule();
			bool *p = decToBinary(choice);
			celAutConfig(p);

			cout << "\n";
			cout << "=============SUCCESS!=============";
			cout << "\n";
			cout << "Enter Anything To Return to the Menu: ";
			string worthless;
			cin >> worthless;
			menu();
			break;
		}
		case 4: {
			lifeConfig();
			menu();
			//Option 4
			break;
		}
		case 0: {
			cout << "Bye!\n";
			
			break;
		}
  		default: {
  			cout << "That's not a valid choice. Please try again.\n";
  			menu();
		}
	}
}

// This method just displays the menu.
void menu() {
	int menuChoice;
	cout << "==================Menu Options==================\n";
	cout << "1: Decimal To Binary Converter\n";
	cout << "2: Binary To Decimal Converter\n";
	cout << "3: CA with Custom First Generation\n";
	cout << "4: Play Game of Life with Random Seed\n";
	//cout << "5: Choice 5\n"; 
	cout << "0: Exit\n";
	cout << "================================================\n";
	cout << "Please Enter the Number For Your Choice:\n";
	cout << "Choice: ";
	cin >> menuChoice; 
	while (cin.fail() == true) {
		cin.clear();
		cin.ignore(256, '\n');
		cout << "Please enter an INTEGER that corresponds to a menu choice\n";
		cout << "Choice: ";
		cin >> menuChoice;
	}
	menuSwitch(menuChoice);
}

// This method returns the users chosen "rule number" as an int
int rule() {

	string choice;

	int rule;
	int error;
	do {

		do {
			cout << endl;
			error=0;
			cout << "Enter a rule which you would like to apply (between 0 and 255): ";
			cin >> choice;
			for (int i=0;i<choice.size();i++) if (!isdigit(choice[i])) error++;
			if (error!=0) cout << "Invalid input! Please try again." << endl;	
		}
		while (error!=0);

		rule = stoi(choice);
		cout << "Rule: " << rule << endl;
		if (rule<0 || rule>255) cout << "Invalid input." << endl;
	}
	while (rule<0 || rule>255);
	return rule;


}

// This method returns a pointer to an array that contains the binary equivilant of the decimal rule the user choose.
bool * decToBinary(int choice) {

	bool* pointer;
	static bool binary[8] = {0,0,0,0,0,0,0,0};
	int loop=7;

	//cout << "The binary number for " << choice << " is: ";

	while (choice!=0) {
		binary[loop]=choice%2;
		choice=choice/2;
		loop--;
	}

	// for (int i=0;i<=7;i++) {
	// 	cout << binary[i] ;
	// }


	cout << "\n";

	return binary;
}

// This method allows the user to customize various options for the simple CA.
void celAutConfig(bool *pRule) {

	int error;
	string line;

	cout << "Enter Your Custom First Generation For the Cellular Automaton." << endl;
	cout << "It must be a line of 1s and 0s." << endl;
	cout << "Example: 101010101 " << endl;

	do {
		cout << endl;
		error=0;
		cout << "Custom First Generation:";
		cin >> line;
		for (int i=0;i<line.size();i++) {
			if (line[i]!='0' && line[i]!='1') error++;
		}
		if (error!=0) {
			cout << "Invalid input! Please try again." << endl;
		}
	}
	while (error!=0);

	int sizeOfArray = line.size();
	bool firstLine[sizeOfArray];

	for (int i=0;i<sizeOfArray;i++) {
		string s(1,line[i]);
		firstLine[i]=stoi(s);
	}

	// cout << "Printing the generator: " ;
	// for (int i=0;i<sizeOfArray;i++) {
	// 	cout << firstLine[i] << "  " ;
	// }


	int numberOfGens;
	int errorr;
	string choice;

	do {
		cout << endl;
		errorr=0;
		cout << "How Many Generations Would You Like to Run For: " ;
		cin >> choice;
		for (int i=0;i<choice.size();i++) if (!isdigit(choice[i])) errorr++;
		if (errorr!=0) cout << "Invalid input! Please try again." << endl;	
	}
	while (errorr!=0);


	numberOfGens = stoi(choice);

	bool *pFirstLine = firstLine;
	celAut(pRule, pFirstLine, sizeOfArray, numberOfGens);

}


// This method takes custom user choices from celAutConfig() and uses them to generate a CA. This method will also print the CA to a file.
void celAut(bool *pRule, bool *pUserGen, int size, int gens) {
	
	bool rule[8];
	for (int i = 0; i < 8; i++) {
		rule[i] = *(pRule+i);
	}


	bool oldGen[size];
	for (int i = 0; i < size; i++) {
		oldGen[i] = *(pUserGen+i);
	}

	bool newGen[size];
	//char printGen[size];
	bool left;
	bool mid;
	bool right;

	ofstream myfile;
	myfile.open ("CellularAutomaton.txt");	

	for (int i = 0; i < size; i++) {
		//cout << oldGen[i];
		if (oldGen[i] == 1) {
			cout << "\u25A0 ";
			myfile << "\u25A0 ";
		} else if (oldGen[i] == 0) {
			cout << "\u25A1 ";
			myfile << "\u25A1 ";
		}
	}

	cout << "\n";
	myfile << "\n";

	for(int x = 0; x < gens; x++) {
		
		for(int checkMe = 0; checkMe < size; checkMe++) {
			
			if (checkMe == 0) {
				left = oldGen[size - 1];
				mid = oldGen[checkMe];
				right = oldGen[checkMe + 1];
			} else if (checkMe == size - 1) {
				left = oldGen[checkMe - 1];
				mid = oldGen[checkMe];
				right = oldGen[0];
			} else {
				left = oldGen[checkMe - 1];
				mid = oldGen[checkMe];
				right = oldGen[checkMe + 1];
			}

			if (left == 1 && mid == 1 && right == 1) {
				newGen[checkMe] = rule[0];
			} else if (left == 1 && mid == 1 && right == 0) {
				newGen[checkMe] = rule[1];
			} else if (left == 1 && mid == 0 && right == 1) {
				newGen[checkMe] = rule[2];
			} else if (left == 1 && mid == 0 && right == 0) {
				newGen[checkMe] = rule[3];
			} else if (left == 0 && mid == 1 && right == 1) {
				newGen[checkMe] = rule[4];
			} else if (left == 0 && mid == 1 && right == 0) {
				newGen[checkMe] = rule[5];
			} else if (left == 0 && mid == 0 && right == 1) {
				newGen[checkMe] = rule[6];
			} else if (left == 0 && mid == 0 && right == 0) {
				newGen[checkMe] = rule[7];
			}
		}

	
		for (int i = 0; i < size; i++) {
			
			if (newGen[i] == 1) {
				cout << "\u25A0 ";
				myfile << "\u25A0 ";
			} else if (newGen[i] == 0) {
				cout << "\u25A1 ";
				myfile << "\u25A1 ";
			}
			oldGen[i] = newGen[i];
		}	
		
		cout << "\n";
		myfile<<"\n";
		
	}

	myfile.close();

}

// This method creates a random 15*15 seed for the Game Of Life.
void lifeConfig() {

	int randArray[15][15];
	char lifeArray[15][15];
	srand(time(NULL));
	//int rand();


	cout << "Your Random Seed Is:\n";

	for(int x=0; x<15; x++) {
		for(int y=0; y<15; y++) {
			randArray[x][y] = rand() % 2;
			if (randArray[x][y] == 1) {
				cout << "\u25A0 ";
				lifeArray[x][y] = '1';
			} else if (randArray[x][y] == 0) {
				cout << "\u25A1 ";
				lifeArray[x][y] = '0';
			}
		}
		cout << "\n";
	}

	gameOfLife(lifeArray);
}

// This method "plays" Conways Game Of Life, using the random 15*15 seed from the lifeConfig method.
void gameOfLife(char initialSeed[15][15]) {

	const int rows=15; 
	const int columns=15;

	char seed[rows+2][columns+2];

	// ----------------------- WRAPPING ------------------------

	for (int i=1;i<rows+1;i++){
		for (int j=1;j<columns+1;j++) {
			seed[i][j]=initialSeed[i-1][j-1];
		}
	}

	for (int i=0;i<rows+2;i++) {
		seed[i][0]='X';
		seed[i][columns+1] = 'X';
	}

	for (int j=0;j<columns+2;j++) {
		seed[0][j]='X';
		seed[rows+1][j]='X';
	}


	// for (int i=0;i<rows+2;i++) {
	// 	for (int j=0;j<columns+2;j++) {
	// 		cout << seed[i][j] << " " ;
	// 	}
	// 	cout << endl;2
	// }
	cout<<endl;

	// ----------------------------------------------------------

	int alive;
	int dead;

	char newGen[rows+2][columns+2];

	// Adding the wrapping
	for (int i=0;i<rows+2;i++) {
		newGen[i][0]='X';
		newGen[i][columns+1] = 'X';
	}

	for (int j=0;j<columns+2;j++) {
		newGen[0][j]='X';
		newGen[rows+1][j]='X';
	}

	// ------------------- GAME OF LIFE -------------------------

	int loop=1;
	int error;

	string choice;

	do {
		cout << endl;
		error=0;
		cout << "For how many generations would you like to play the game of life: ";
		cin >> choice;
		for (int i=0;i<choice.size();i++) if (!isdigit(choice[i])) error++;
		if (error!=0) cout << "Invalid input! Please try again." << endl;	
	}
	while (error!=0);


	int usersChoice = stoi(choice);

	// Printing of the seed
		for (int i=0;i<rows+2;i++) {
			for (int j=0;j<columns+2;j++) {
				if (seed[i][j] == '1') {
					cout << "\u25A0 ";
				} else if (seed[i][j] == '0') {
					cout << "\u25A1 ";
				}
			}
			cout << endl;
		}
	
	cout<<endl;

	usleep(2500);
	system("clear");
		
	int counter = 1;

	do {

		cout << "You Are Seeing Generation " << counter << " of " << usersChoice << "\n";
		counter++;

		for (int i=1;i<rows+1;i++) {
			for (int j=1;j<columns+1;j++) {

				alive=0;
				dead=0;

				// Going through the neighbors of the cell

				if (seed[i-1][j-1]=='1') alive++; else dead++;
				if (seed[i][j-1]=='1') alive++; else dead++;
				if (seed[i+1][j-1]=='1') alive++; else dead++;
				if (seed[i+1][j]=='1') alive++; else dead++;
				if (seed[i+1][j+1]=='1') alive++; else dead++;
				if (seed[i][j+1]=='1') alive++; else dead++;
				if (seed[i-1][j+1]=='1') alive++; else dead++;
				if (seed[i-1][j]=='1') alive++; else dead++;

				// Deciding if the cell will live or die
				if (seed[i][j]=='1') {
					if (alive<2) newGen[i][j]='0';
					else if (alive==2 || alive==3) newGen[i][j]='1';
					else if (alive>3) newGen[i][j]='0';
				}
				else if (seed[i][j]=='0') {
					if (alive==3) newGen[i][j]='1';
					else newGen[i][j]='0';
				}
			}
		}

		loop++;

		// Printing of the new Generation
		for (int i=0;i<rows+2;i++) {
			for (int j=0;j<columns+2;j++) {
				if (newGen[i][j] == '1') {
					cout << "\u25A0 ";
				} else if (newGen[i][j] == '0') {
					cout << "\u25A1 ";
				}
			}
			cout << endl;
		}
		cout<<endl;

		usleep(2500000);
		system("clear");

		// Making the new Generation the seed
		for (int i=1;i<rows+1;i++){
			for (int j=1;j<columns+1;j++) {
				seed[i][j]=newGen[i][j];
			}
		}
	}
	while (loop!=usersChoice);

	cout << "Your Final Generation Is: ";
	for (int i=0;i<rows+2;i++) {
		for (int j=0;j<columns+2;j++) {
			if (newGen[i][j] == '1') {
				cout << "\u25A0 ";
			} else if (newGen[i][j] == '0') {
				cout << "\u25A1 ";
			}
		}
		cout << endl;
	}
	cout<<endl;

	cout << "Enter Anything to Return to the Menu:\n";
	string useless;
	cin >> useless;
}


// This method takes a decimal from the user, and converts in into binary, as long as that number is within the constraints of 64 bit binary.
void decToBinaryNoR() {

	int choice=0;

	cout << "Enter A Decimal Number: ";
	cin >> choice ;
	cout << endl;

	int loop=63;

	int binary[64];
	for (int i=0;i<64;i++) {
		binary[i]=2;
	}

	while (choice!=0) {
		binary[loop]=choice%2;
		choice=choice/2;
		loop--;
	}

	cout << "Your Number in Binary Is: \n";

	for (int i=0;i<=63;i++) {
		if (binary[i]==1 || binary[i]==0) cout << binary[i] ;
	}


	cout << "\n";

}

// This method takes binary input from the user, and converts it into a decimal.
int binaryToDecimal() {

	int error;
	string line;


	do {
		cout << endl;
		error=0;
		cout << "Enter a binary number: ";
		cin >> line;
		for (int i=0;i<line.size();i++) {
			if (line[i]!='0' && line[i]!='1') error++;
		}
		if (error!=0) {
			cout << "Invalid input! Please try again." << endl;
		}
	}
	while (error!=0);

	int sizeOfArray = line.size();
	bool firstLine[sizeOfArray];

	for (int i=0;i<sizeOfArray;i++) {
		string s(1,line[i]);
		firstLine[i]=stoi(s);
	}

	// cout << "Printing the number: " ;
	// for (int i=0;i<sizeOfArray;i++) {
	// 	cout << firstLine[i] << "  " ;
	// }

	cout << endl;

	int sum=0;
	int two=1;

	for (int i=0;i<sizeOfArray;i++) {
		two = 1;
		for (int j=0;j<sizeOfArray-i-1;j++) {
			two=two*2;	
		}
		//cout << "Printing the power of 2: " << two << endl;
		two=two*firstLine[i];
		sum = sum + two;

	}

	cout << "The decimal number is: " << sum << endl;
	cout << endl;

	cout << "\n" << endl;

	return sum;

}

// This is our main method
int main() 
{
	menu();
    return 0;
}