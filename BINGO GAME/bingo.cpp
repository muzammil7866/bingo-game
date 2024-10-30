#include<iostream> //for inputs and outputs

#include<cstdlib> //random numbers

#include<ctime> //for new random numbers each time

#include<fstream> //for file handling

#include<string> //for string operations

#include<windows.h> //for colors

#include<iomanip> //for presenting output neatly 

using namespace std;

bool signup(); 

bool login(); 

void mainMenu();

int gameID();

void generateBoard(int board1[][5]);

void displayBoard(int board1[][5], string p, int id);

int toss(string p1, string p2); 

void playGame(int board1[][5], int board[][5], int start, string p1, string p2, int id);

bool winCheck(int board[][5], string p, int id);

int main() //would provide the options to user for either signing up for an account or logging in through existing one
{
	system("color 3");
	bool validInput = false;
	char choice;

	while (validInput != true)
	{
		cout << "\t\t LOGIN MENU " << endl<<endl<<endl;
		cout << "\tPRESS 1 TO LOGIN" << endl;
		cout << "\tpress 2 TO SIGNUP" << endl;

		cout << "\nENTER HERE: ";

		cin >> choice;

		if (choice == '1')
		{
			validInput = true;
			bool found = false;

			while(found != true)
			{
				found = login();
				system("pause");
			}

			mainMenu();
		}

		else if (choice == '2')
		{
			validInput = true;

			bool valid = false;

			while (valid != true)
			{
				valid = signup();
				system("pause");
			}

			mainMenu();
		}

		else
		{
			cout << "\nINVALID INPUT!\n\n";
			system("pause");
			validInput = false;
			system("cls");
		}
	}
	
}

bool signup() //Player would sign up using this function
{
	system("cls");
	string name, pw;
	cout << "\tEnter your name : ";
	cin >> name;
	cout << endl;
	cout << "\tEnter your password : ";
	cin >> pw;
	cout << endl;

	fstream fHand;
	fHand.open("login.txt");

	if (!fHand.is_open())
	{
		cout << "\nUNABLE TO CREATE ACCOUNT, TRY AGAIN!";
	}

	else
	{
		string namef, pwf;
		bool valid = true;
		while (!fHand.eof() and valid != false)
		{
			getline(fHand, namef);
			getline(fHand, pwf);

			if (namef == name)
			{
				cout << "USERNAME ALREADY TAKEN, CHOOSE SOME OTHER!" << endl;
				valid = false;
				return valid;
			}
		}
		fHand.close();

		if (valid)
		{
			fHand.open("login.txt", ios::app);

			if (fHand.is_open())
			{
				fHand << endl<<name<<endl<<pw;

				cout << "\nACCOUNT CREATED SUCCESSFULLY, WELCOME " << name << "!" << endl;
			}

			fHand.close();
		}
		return valid;
	}
}

bool login() //Player would log in using this function
{
	system("cls");

	string name, pw;
	cout << "\tEnter your name : ";
	cin >> name;
	cout << endl;
	cout << "\tEnter your password : ";
	cin >> pw;


	fstream fHand;
	fHand.open("login.txt");

	if (!fHand.is_open())
	{
		cout << "\nUNABLE TO RETRIEVE LOGIN INFO FROM DATABASE!";
	}

	else 
	{
		string namef, pwf;
		bool found = false;
		while (!fHand.eof() and found != true)
		{
			getline(fHand, namef);
			getline(fHand, pwf);

			if (namef == name && pw == pwf)
			{
				cout << "\nLOGGED IN SUCCESSFULLY, WELCOME " << name << "!"<<endl<<endl;
				found = true;
			}
		}

		if (!found)
		{
			cout << "\nINVALID USERNAME OR PASSWORD, TRY AGAIN!"<<endl<<endl;
		}

		fHand.close();
		return found;


	}
	


}

int gameID() //Random ID would be assigned to this game
{
	srand(time(0));
	int thisGameID = rand() % 10000 + 1;
	system("cls");
	cout << "YOUR GAME ID IS: " << thisGameID << endl;

	return thisGameID;
	
}

void generateBoard(int board1[][5]) //Enters the player 1 name and randomly generates its bingo grid numbers
{
	

	int temp = 0;
	bool newRandom = true;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			temp = 1 + rand() % 25;
			for (int k = 0; k < 5; k++)
			{
				for (int l = 0; l < 5; l++)
				{
					if (board1[k][l] == temp)
					{
						newRandom = false;
						break;
					}

					else
					{
						newRandom = true;
					}

				}

				if (!newRandom)
				{
					break;
				}
			}

			if (!newRandom)
			{
				--j;
			}

			else
			{
				board1[i][j] = temp;
			}
		}
	}
}

void displayBoard(int board1[][5], string p, int id)
{
	system("cls");
	cout << "YOUR GAME ID IS: " << id << endl<<endl;
	cout << "HERE IS YOUR BOARD " << p <<"!"<< endl << endl << endl;

	cout << "|";
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cout <<setw(3) << board1[i][j] << setw(3) << "|";
		}
		if (i != 4)
			cout << endl << endl << "|";
	}

	cout<< endl << endl;
}

int toss(string p1, string p2) //would randomly toss b/w the both players
{
	system("cls");
	int num=0;
	num = rand() % 2 + 1;

	cout << "'";
	if (num == 1)
	{
		cout << p1;
	}

	else
	{
		cout << p2;
	}

	cout<<"' WINS THE TOSS\n" << endl;
	cout << "TAKE YOUR FIRST TURN!\n\n";
	system("pause");
	return num;
}

void playGame(int board1[][5], int board2[][5], int start, string p1, string p2, int id) //the proper function that would assign 0 to the number choosen by the either player and also switch their turns
{
	bool valid = false;
	bool found = false;

	int num = 0;
	
	bool endGame = false;
	

	while (!(winCheck(board1, p1, id)||winCheck(board2, p2, id)))
	{
		if (start == 1)
			displayBoard(board1, p1, id);

		else
			displayBoard(board2, p2, id);
		
		cout << "\nCHOOSE YOUR NUMBER (ENTER NUMBERS ONLY B/W 1 TO 25): ";
		cin >> num;

		for (int i = 1; i <= 25; i++)
		{
			if (i == num)
				valid = true;
		}

		if (!valid)
		{
			cout << "\n\nINVALID INPUT, CHOOSE AGAIN!"<<endl<<endl;
			system("pause");
			break;
		}

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (num == board1[i][j])
				{
					found = true;
					board1[i][j] = 0;
				}

				if (num == board2[i][j])
				{
					board2[i][j] = 0;
				}
				
			}
		}

		if (found)
		{
			if (start == 1)
			{
				start = 2;
				displayBoard(board1, p1, id);
				system("pause");
			}
			else if (start == 2)
			{
				start = 1;
				displayBoard(board2, p2, id);
				system("pause");
			}
		}

		if (!found)
		{
			cout << "\n\nSPACE ALREADY OCCUPIED, CHOOSE ANOTHER!\n\n";
			system("pause");
		}
	}

}

bool winCheck(int board1[][5], string p, int id) //would check if the conditions meet for player 1 to win
{
	
	
	int count = 0;
	int lines = 0;
	int score = 0;

	//vertical
	for (int i = 0;i < 5;i++)
	{
		count = 0;

		for (int j = 0;j < 5;j++)
		{
			if (board1[j][i] == 0)
				count++;

		}
		if (count == 5)
			lines++;

	}


	//horizontal
	for (int i = 0;i < 5;i++)
	{
		count = 0;
		for (int j = 0;j < 5;j++)
		{
			if (board1[i][j] == 0)
				count++;

		}

		if (count == 5)
			lines++;
		

	}

	//diagnol
	count = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0;j < 5;j++)
		{
			if (i == j)
				if (board1[i][j] == 0)
					count++;

		}
	}

	if (count == 5)
		lines++;

	count = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0;j < 5;j++)
		{
			if (i + j == 4)
				if (board1[i][j] == 0)
					count++;

		}
	}
	if (count == 5)
		lines++;

	score = lines * 100;

	if (lines >= 5)
	{
		ofstream fHand;
		fHand.open("playersHistory.txt",ios::app);
		if (!fHand.is_open())
		{
			cout << "\n\nUNFORTUNATELY COULD NOT UPDATE THE SCORES BOARD!";
		}
		else
		{
			fHand<<id<<endl<< p <<endl << score<<endl;
			cout << "\n\nCONGRATULATIONS AND BINGO, " << p << " WON!";
			cout << "\n\nYOU HAVE BEEN ADDED TO THE SCORES BOARD! :)"<<endl<<endl;
		}

		fHand.close();
		return true;
		
	}
	return false;
}

void mainMenu() //would allow the user to choose between the menu options and process accoring to that selection
{
	system("cls");

	bool endGame = false;
	bool endGame1 = false;

	int mainChoice = 0;

	cout << "......................................" << endl;
	cout << "\t      B I N G O" << endl;
	cout << "......................................" << endl;
	cout << endl << endl;

	cout << "\tPress (1) to Play Game" << endl<<endl;
	cout << "\tPress (2) to display Game History" << endl << endl;
	cout << "\tPress (3) to How to Play ?" << endl << endl;
	cout << "\tPress (4) to Exit: " << endl << endl;
	cout << "Choose your option: ";
	cin >> mainChoice;

	while (endGame != true)
	{
		if (mainChoice == 1) //main gameplay
		{
			int id = gameID();

			string p1;
			string p2;

			cout << "\nENTER THE NAME OF PLAYER 1: ";
			cin >> p1;

			cout << "\nENTER THE NAME OF PLAYER 2: ";
			cin >> p2;

			int board1[5][5] = { 0 };
			int board2[5][5] = { 0 };

			srand(time(0));
			generateBoard(board1);
			generateBoard(board2);
			
	
			displayBoard(board1, p1, id);
			system("pause");
			displayBoard(board2, p2, id);
			system("pause");

			int start = toss(p1,p2);

			playGame(board1, board2, start, p1, p2, id);

			break;
		}

		else if (mainChoice == 2) //players history file would be called
		{
			fstream fHand;
			fHand.open("playersHistory.txt"); //only names of the winners will be stored

			if (!fHand.is_open())
			{
				cout << "NO PLAYER HISTORY AVAILABLE!"<<endl;
			}

			string id, name, score;
			cout << endl;

			while (!fHand.eof())
			{
				getline(fHand, id);
				getline(fHand, name);
				getline(fHand, score);

				cout<<"\t"<<setw(5) << "("<<id <<") "<< setw(10) << name << " --> " << score << endl << endl;

			}

			fHand.close();
			system("pause");
			mainMenu();
		}

		else if (mainChoice == 3) //Instructions of the game would be displayed
		{
			system("cls");
			cout << endl;
			cout << "\t      INSTRUCTIONS" << endl << endl << endl;

			cout << "1. There are corresponding cards to each player." << endl << endl;
			cout << "2. Each player chooses a number in his turn from the card." << endl << endl;
			cout << "3. Selected number will be replaced by 0 on the cards of both players." << endl << endl;
			cout << "4. For a winner there should be five combinations that can be possible in the following ways:" << endl << endl;

			cout << "\t a) 5 numbers in a column " << endl << endl;
			cout << "\t b) 5 numbers in a row " << endl << endl;
			cout << "\t c) 5 numbers in a diagonal " << endl << endl;

			cout << "5. There will be no scenario of a draw game." << endl << endl;

			cout << "\t      GOOD LUCK! " << endl << endl;

			system("pause");
				
			mainMenu();
			break;
		}

		else if (mainChoice == 4) //Game would end with this option
		{

			endGame = true;
		}

	}
}