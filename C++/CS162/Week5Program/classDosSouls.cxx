/******************************************************************************
Business Program for Customer Data that is Not a Game

Donnie Gilbert
CS162-W1 SP24 Priestley


Purpose of the program:
Make a Program to search for Clients in an Array for weekly homework.
A lot of this code is a continuation of the game from Week 3 of CS162-W1 SP24.
I am mostly just using this as an opportunity to seek feedback on the progress of
its' development so that I may further my desire of working on the game from week 3.
Currently, this program only demonstrates the Game's Menu/Ui functions, the Data Filling
functions, and the Level Building, Player Character Generating functions.
The Fighting functions are functional, but not ready for demonstration.


Specification Summary:
Define a struct to store a customer record in a file.
	- (ID, company name, city, state, customer type)
Populate an array of clients with at least three clients' information.
	- (can be hard-coded or retrieved from a file, your choice)
Allow the user to type a client ID and see all the corresponding customer data.
	- Your program searches the array for the ID entered by the user.
You are encouraged to store the information on disk,
either in a sequential or random-access file, but that is optional this week.


Notes:
I wish I could also display the "Business" and "Employee" data, but I have
already run out of time. It is currently 1:01 AM, and this assignment was due
about an hour ago at 11:59AM. Sorry for any sloppy code, or poor implentations.
I am currently devoting all of my time in to furthering the game, even if it
may be costing me grade wise unfortunately. I've just never had a project I've
enjoyed this much before, and I apologize in advance to you and myself I suppose.
There are a lot of left over functions from my game, but all of the irrelevant
function calls have been removed. I wouldn't suggest trying to call any
function the I have explicitly called in this demonstration, but feel
free to look. ...and technically I know, I'm not actually searching an array,
but theres no way you would think that should be difficult for me to implement.

Sources:
Watching Mr.Priestley's labs and stuff I learned failing other classes.

"If you don't specify, I may ask you if I can share it."
*******************************************************************************/

/******************************************************************************
 *                              class Dos Souls .cxx                          *
 ******************************************************************************/
#include "classDosSouls.h"
/******************************************************************************
 *                              INTERACT FUNCTIONS                            *
 ******************************************************************************/

// Function to Take User's Choice as String
// Accepts No Parameter(s)
// Returns String, passes Data by Member Access
string Game::dsChoiceString()
{
	// Initialize Variable(s) for dsChoiceString()
	string userString = "-1"; // Initialize Strings(s) for storing User String(s)
	bool isChoice = true;	  // Initialize Bool(s) for storing Bool(s)

	// Take User's Choice with Getline()
	getline(cin, userString);

	// Checks User's Choice for Alnums
	for (int i = 0; isChoice && i < userString.length(); ++i)
	{
		// If Char in String is NOT an Alnum, Empty Variable(s)
		if (!(isalnum(userString[i])))
		{
			isChoice = false;
		}
	}

	// If isChoice == false, Empty Variable(s)
	if (isChoice == false)
	{
		userString = "-1";
	}

	// End dsChoiceString() with a Newline
	cout << endl;

	// Return User's Choice as String
	return userString;
}

// Function to Take User's Choice as Double
// Requires 2 Int Parameter(s) for Min Value and Max Value of Choice
// Returns Double, passes Data by Member Access
double Game::dsChoiceNumber(int choiceMin, int choiceMax)
{
	// Initialize Variable(s) for dsChoiceNumber()
	string userString = "-1"; // Initialize Strings(s) for storing User String(s)
	double userDouble = (-1); // Initialize Double(s) for storing User Double(s)
	bool isChoice = true;	  // Initialize Bool(s) for storing Bool(s)

	// Take User's Choice with Getline()
	getline(cin, userString);

	// If choiceMin >= 0 and choiceMax <= 9, Only Accept Single Digit Numbers
	if (choiceMin >= 0 && choiceMax <= 9)
	{
		// If is Not Single Char or Not a Digit, Empty Variable(s)
		if (userString.length() != 1 || !(isdigit(userString[0])))
		{
			isChoice = false;
		}

		// If Char in userString[0] < choiceMin or userString[0] > choiceMax, Empty Variable(s)
		else if (stoi(userString) < choiceMin || stoi(userString) > choiceMax)
		{
			isChoice = false;
		}
	}

	// If choiceMin >= 0 and choiceMax > 9, Only Accept Positive Multi Digit Numbers
	else if (choiceMin >= 0 && choiceMax > 9)
	{
		// Checks User's Choice for Digits
		for (int i = 0; isChoice && i < userString.length(); ++i)
		{
			// If Char in String is NOT a Digit, Empty Variable(s)
			if (!(isdigit(userString[i])))
			{
				isChoice = false;
			}
		}
	}

	// If choiceMin < 0 and choiceMax <= 0, Only Accept Negative Multi Digit Numbers
	else if (choiceMin < 0 && choiceMax <= 0)
	{
		// If Char in userString[0] is Not a Negative Sign, Empty Variable(s)
		if (userString[0] != '-')
		{
			isChoice = false;
		}

		// Checks User's Choice for Digits
		for (int i = 1; isChoice && i < userString.length(); ++i)
		{
			// If Char in String is NOT a Digit, Empty Variable(s)
			if (!(isdigit(userString[i])))
			{
				isChoice = false;
			}
		}
	}

	// Else, Accept any Multi Digit Number
	else
	{
		// If Char in userString[0] is Not a Negative Sign and Not a Digit, Empty Variable(s)
		if (userString[0] != '-' && !(isdigit(userString[0])))
		{
			isChoice = false;
		}

		// If Char in userString[0] is a Negative Sign and Length Less than 2, Empty Variable(s)
		else if (userString[0] == '-' && userString.length() < 2)
		{
			isChoice = false;
		}

		// If Char in userString[0] has a Negative Sign and/or has Digit(s), Check the rest
		else
		{
			// Checks User's Choice for Digits
			for (int i = 1; isChoice && i < userString.length(); ++i)
			{
				// If Char in String is NOT a Digit, Empty Variable(s)
				if (!(isdigit(userString[i])))
				{
					isChoice = false;
				}
			}
		}
	}

	// If all Char(s) in String is/are Valid, Return String as Double
	if (isChoice == true)
	{
		userDouble = stod(userString);
	}

	// If isChoice == false, Empty Variable(s)
	else
	{
		userString = "-1";
		userDouble = (-1);
	}

	// End dsChoiceNumber() with a Newline
	cout << endl;

	// Return User's Choice as Double
	return userDouble;
}

/******************************************************************************
 *                              INTERACT FUNCTIONS                            *
 ******************************************************************************/

/******************************************************************************
 *                                  FILE FUNCTIONS                            *
 ******************************************************************************/

// Function to Access Game Files for Game Data
// Accepts No Parameter(s)
// Returns Void, passes Data by Member Access
void Game::dsFiles()
{
	// Initialize Variable(s) for dsFiles()
	ifstream dsFile; // Initialize ifstream(s) for storing ifstream(s)
	string			 // Initialize Strings(s) for storing String(s)
		lineTrash,
		labelName,
		labelPage;

	// Open fileMenus
	dsFile.open(fileMenus);
	// If fileMenus did Open, Continue
	if (dsFile.is_open())
	{
		// Output fileMenus opened successfully to console
		cout << "File, " << fileMenus << ", opened successfully" << endl
			 << endl;

		// Fill menuLinesNumbers Array
		for (int mMENU = 0; mMENU < mMENUS; ++mMENU)
		{
			// Fill menuLinesNumbers Array Lines
			for (int mLINE = 0; mLINE < mLINES; ++mLINE)
			{
				// Fill menuLinesNumbers Array Columns
				for (int mCOL = 0; mCOL < mCOLS; ++mCOL)
				{
					// Fill menuLinesNumbers Array Columns with (-1)
					menuLinesNumbers[mMENU][mLINE][mCOL] = (-1);
				}
			}
		}

		// Fill menuLines Array
		for (int mMENU = 0; mMENU < mMENUS; ++mMENU)
		{
			// Advance to Next Menu Label Column
			getline(dsFile, lineTrash, ';');
			// Store Menu Name in labelName
			getline(dsFile, labelName, ';');
			// Store Menu Page in labelPage
			getline(dsFile, labelPage, ';');
			// Advance to Next Menu Line
			getline(dsFile, lineTrash);

			// Fill menuLines Array Lines
			for (int mLINE = 0; mLINE < mLINES; ++mLINE)
			{
				// Fill menuLines Array Columns
				for (int mCOL = 0; mCOL < mCOLS; ++mCOL)
				{
					// Store Menu Line Column at menuLines[mMENU][mLINE][mCOL]
					getline(dsFile, menuLines[mMENU][mLINE][mCOL], ';');
				}

				// Advance to Next Menu Line
				getline(dsFile, lineTrash);
			}

			// Fill menuLabels Array, If Menu Page == Page 1
			if (menuLines[mMENU][0][1] == "0")
			{
				// Specify Index of menuLabels is menuLines[mMENU][0][0]
				int mLABEL = stoi(menuLines[mMENU][0][0]);

				// Store menuLines Index at menuLabels[mLABEL][0]
				menuLabels[mLABEL][0] = to_string(mMENU);

				// Store Menu Name at menuLabels[mLABEL][1]
				menuLabels[mLABEL][1] = labelName;

				// Store Menu Page at menuLabels[mLABEL][2]
				menuLabels[mLABEL][2] = labelPage;
			}
		}

		// Close fileMenus
		dsFile.close();
	}
	// If fileMenus did Not Open, Error
	else
	{
		// Output fileMenus failed to open to console
		cout << "File, " << fileMenus << ", failed to open" << endl
			 << endl;
	}

	// Open fileUi
	dsFile.open(fileCustomers);
	// If fileUi did Open, Continue
	if (dsFile.is_open())
	{
		// Output fileUi opened successfully to console
		cout << "File, " << fileCustomers << ", opened successfully" << endl
			 << endl;

		// Fill uiLinesNumbers Array
		for (int uMENU = 0; uMENU < uMENUS; ++uMENU)
		{
			// Fill uiLinesNumbers Array Lines
			for (int uLINE = 0; uLINE < uLINES; ++uLINE)
			{
				// Fill uiLinesNumbers Array Columns
				for (int uCOL = 0; uCOL < uCOLS; ++uCOL)
				{
					// Fill uiLinesNumbers Array Columns with (-1)
					uiLinesNumbers[uMENU][uLINE][uCOL] = (-1);
				}
			}
		}

		// Fill Ui Arrays
		for (int uMENU = 0; uMENU < uMENUS; ++uMENU)
		{
			// Advance to Next Ui Label Column
			getline(dsFile, lineTrash, ';');
			// Store Ui Name in labelName
			getline(dsFile, labelName, ';');
			// Store Ui Page in labelPage
			getline(dsFile, labelPage, ';');
			// Advance to Next Ui Line
			getline(dsFile, lineTrash);

			// Fill uiLines Array Lines
			for (int uLINE = 0; uLINE < uLINES; ++uLINE)
			{
				// Fill uiLines Array Columns
				for (int uCOL = 0; uCOL < uCOLS; ++uCOL)
				{
					// Store Ui Line Column at uiLines[uMENU][uLINE][uCOL]
					getline(dsFile, uiLines[uMENU][uLINE][uCOL], ';');
				}

				// Advance to Next Ui Line
				getline(dsFile, lineTrash);
			}

			// Fill uiLabels Array, If Ui Page == Page 1
			if (uiLines[uMENU][0][1] == "0")
			{
				// Specify Index of uiLabels is uiLines[uMENU][0][0]
				int mLABEL = stoi(uiLines[uMENU][0][0]);

				// Store uiLines Index at uiLabels[mLABEL][0]
				uiLabels[mLABEL][0] = to_string(uMENU);

				// Store Ui Name at uiLabels[mLABEL][1]
				uiLabels[mLABEL][1] = labelName;

				// Store Ui Page at uiLabels[mLABEL][2]
				uiLabels[mLABEL][2] = labelPage;
			}
		}

		// Close fileUi
		dsFile.close();
	}
	// If fileUi did Not Open, Error
	else
	{
		// Output fileUi failed to open to console
		cout << "File, " << fileCustomers << ", failed to open" << endl
			 << endl;
	}

	// Return Void
	return;
}

/******************************************************************************
 *                                  FILE FUNCTIONS                            *
 ******************************************************************************/

/******************************************************************************
 *                                  MENU FUNCTIONS                            *
 ******************************************************************************/

// Function to Display Game Menus
// Accepts 2 Int Parameter(s) for Adjusting Menus
// Returns Double, passes Data by Member Access
double Game::dsMenuDisplay(int mMENU, int mPAGE)
{
	// Initialize Variable(s) for dsMenuDisplay()
	int // Initialize Int(s) for storing Int(s)
		dsChoiceMin = 1,
		dsChoiceMax = 1;
	double userDouble = (-1); // Initialize Double(s) for storing User Double(s)
	bool isDone = false;	  // Initialize Bool(s) for storing Bool(s)

	// Clear Terminal to Display Game Menu
	system("CLS");

	// cout Top Border, Each Corner Spaced by setw(40)
	cout << setw(40) << left << "+ - - - - - - - - - - - - - - - - - - -"
		 << setw(40) << right << "- - - - - - - - - - - - - - - - - - - - +"
		 << endl;

	// Display Game Menu
	for (int mLINE = 1; mLINE < (mLINES - 1); ++mLINE)
	{
		// cout menuLines[mMENU][mLINE] lineLeft, then menuLines[mMENU][mLINE] lineRight, Centered to setw(40)
		cout << setw(40) << right << menuLines[(stoi(menuLabels[mMENU][0]) + mPAGE)][mLINE][1];

		// If Line Has Value, cout Value Message
		if (menuLines[(stoi(menuLabels[mMENU][0]) + mPAGE)][mLINE][3] != "-1")
		{
			cout << right << ' ' << menuLinesNumbers[mMENU][mLINE][2];
		}

		// cout menuLines[mMENU][mLINE] lineRight
		cout << left << menuLines[(stoi(menuLabels[mMENU][0]) + mPAGE)][mLINE][2];

		// If Line is Selected, cout Selected Message
		if (menuLinesNumbers[mMENU][mLINE][3] != (-1))
		{
			cout << menuLines[(stoi(menuLabels[mMENU][0]) + mPAGE)][11][3];
		}

		// cout New Line
		cout << endl;
	}

	// cout Bottom Border, Each Corner Spaced by setw(40)
	cout << setw(40) << left << "+ - - - - - - - - - - - - - - - - - - -"
		 << setw(40) << right << "- - - - - - - - - - - - - - - - - - - - +"
		 << endl;

	// cout Last menuLines[mMENU][-1] lineLeft, then menuLines[mMENU][-1] lineRight, Left Centered to setw(40)
	cout << setw(40) << right << menuLines[(stoi(menuLabels[mMENU][0]) + mPAGE)][11][1]
		 << left << menuLines[(stoi(menuLabels[mMENU][0]) + mPAGE)][11][2];

	// Correct choiceMin
	if (menuLines[(stoi(menuLabels[mMENU][0]) + mPAGE)][0][3].substr(0, 1) == "+")
	{
		dsChoiceMin = (1000 * 1000);
	}
	else if (menuLines[(stoi(menuLabels[mMENU][0]) + mPAGE)][0][3].substr(0, 1) == "-")
	{
		dsChoiceMin = ((-1000) * (1000));
	}
	else
	{
		dsChoiceMin = stoi(menuLines[(stoi(menuLabels[mMENU][0]) + mPAGE)][0][3].substr(0, 1));
	}

	// Correct choiceMax
	if (menuLines[(stoi(menuLabels[mMENU][0]) + mPAGE)][0][3].substr(1, 1) == "+")
	{
		dsChoiceMax = (1000 * 1000);
	}
	else if (menuLines[(stoi(menuLabels[mMENU][0]) + mPAGE)][0][3].substr(1, 1) == "-")
	{
		dsChoiceMax = ((-1000) * (1000));
	}
	else
	{
		dsChoiceMax = stoi(menuLines[(stoi(menuLabels[mMENU][0]) + mPAGE)][0][3].substr(1, 1));
	}

	// Take User Choice Specified by Menu
	userDouble = dsChoiceNumber(dsChoiceMin, dsChoiceMax);

	// Return User Choice as Double
	return userDouble;
}

// Function to Access Game Menus
// Accepts 2 Int Parameter(s)
// Returns Void, passes Data by Member Access
void Game::dsMenus(int mMENU, int mPAGE)
{
	// Initialize Variable(s) for dsMenus()
	int userInt = (-1);		  // Initialize Int(s) for storing User Int(s)
	double userDouble = (-1); // Initialize Double(s) for storing User Double(s)
	bool isDone = false;	  // Initialize Bool(s) for storing Bool(s)

	// Set Settings Values
	menuLinesNumbers[2][4][2] = floorDifficulty;
	menuLinesNumbers[2][5][2] = floorTotal;
	menuLinesNumbers[2][6][2] = enemyTotal;
	menuLinesNumbers[2][7][2] = playerTotal;
	for (int i = 3; i < 6; ++i)
	{
		menuLinesNumbers[i][4][2] = rndInt(99999, 10000);
		menuLinesNumbers[i][5][2] = rndInt(99999, 10000);
		menuLinesNumbers[i][6][2] = rndInt(99999, 10000);
		menuLinesNumbers[i][7][2] = rndInt(99999, 10000);
		menuLinesNumbers[i][4][1] = 4;
		menuLinesNumbers[i][5][1] = 5;
		menuLinesNumbers[i][6][1] = 6;
		menuLinesNumbers[i][7][1] = 7;
	}

	// Take User's Choice with dsChoiceNumber() while isDone != true;
	do
	{
		// Display Menu and Take User Choice
		userDouble = dsMenuDisplay(mMENU, mPAGE);
		userInt = userDouble;

		// If mPAGE == 0, Display Menu Page 1
		if (mPAGE == 0)
		{
			// If userInt is (-1), Keep Menu Running
			if (userInt == (-1))
			{
				// Keep Menu Page at Page 1
				mPAGE = 0;

				// Keep Menu Running until Closed
				isDone = false;
			}

			// If userInt is 1, Close the Menu
			else if (userInt == 1)
			{
				// Keep Menu Page at Page 1
				mPAGE = 0;

				// Close the Menu
				isDone = true;
			}

			// If userInt is 0, Go Back 1 Menu
			else if (userInt == 0)
			{
				// Go Back 1 Menu
				mMENU = 3;

				// Keep Menu Page at Page 1
				mPAGE = 0;

				// Keep Menu Running until Closed
				isDone = false;
			}

			// If User Chose a Line, Mark Line as Selected
			else
			{
				// Initialize Bool(s) for storing Bool(s)
				bool isLine = false;

				// Check Lines for Selected Line
				for (int mLINE = 1; !(isLine) && mLINE < mLINES; ++mLINE)
				{
					// If User Selected mLINE, Mark mLINE as Selected
					if (userInt == stoi(menuLines[mMENU][mLINE][3]))
					{
						// Mark mLINE as Selected
						menuLinesNumbers[mMENU][stoi(menuLines[mMENU][mLINE][0])][3] = 1;

						// Change Menu Page to Page 2
						mPAGE = 1;

						// End Checking Lines for Selected Line
						isLine = true;
					}

					// If Not Line, Keep Looking
					else
					{
						isLine = false;
					}
				}

				// Keep Menu Running until Closed
				isDone = false;
			}
		}

		// If mPAGE == 1, Display Menu Page 2
		else if (mPAGE == 1)
		{
			// If userInt is (-1), Keep Menu Running
			if (userInt == (-1))
			{
				// Keep Menu Page at Page 2
				mPAGE = 1;

				// Keep Menu Running until Closed
				isDone = false;
			}

			// If User Choice is Valid, Edit Selected Line
			else
			{
				// Settings Menu
				if (mMENU == 2)
				{
					// Initialize Bool(s) for storing Bool(s)
					bool isLine = false;

					// Check Lines for Selected Line
					for (int mLINE = 1; !(isLine) && mLINE < mLINES; ++mLINE)
					{
						// If User Selected mLINE, Edit Selected mLINE
						if (menuLinesNumbers[mMENU][mLINE][3] == 1)
						{
							// Edit Selected mLINE
							menuLinesNumbers[mMENU][mLINE][2] = userInt;

							// Mark mLINE as UnSelected
							menuLinesNumbers[mMENU][mLINE][3] = (-1);

							// Change Menu Page to Page 1
							mPAGE = 0;

							// End Checking Lines for Selected Line
							isLine = true;
						}

						// If Not Line, Keep Looking
						else
						{
							isLine = false;
						}
					}

					// Keep Menu Running until Closed
					isDone = false;
				}

				// Customer Select Menu
				else if (mMENU == 3)
				{
					// Initialize Bool(s) for storing Bool(s)
					bool isLine = false;

					// Check Lines for Selected Line
					for (int mLINE = 1; !(isLine) && mLINE < mLINES; ++mLINE)
					{
						// If User Selected mLINE, Verify
						if (menuLinesNumbers[mMENU][mLINE][3] == 1)
						{
							// If User Confirms, Continue
							if (userInt == 1)
							{
								// Mark mLINE as UnSelected
								menuLinesNumbers[mMENU][mLINE][3] = (-1);

								// Change Menu Page to Selected Customer
								mPAGE = 0;
								mMENU = menuLinesNumbers[mMENU][mLINE][1];

								// End Checking Lines for Selected Line
								isLine = true;
							}

							// If User Denys, Go Back
							else if (userInt == 2)
							{
								// Mark mLINE as UnSelected
								menuLinesNumbers[mMENU][mLINE][3] = (-1);

								// Change Menu Page to Page 1
								mPAGE = 0;

								// End Checking Lines for Selected Line
								isLine = true;
							}

							// If User Invalid Choice, Take Choice Again
							else
							{
								// Keep Menu Page at Page 2
								mPAGE = 1;
							}
						}

						// If Not Line, Keep Looking
						else
						{
							isLine = false;
						}
					}

					// Keep Menu Running until Closed
					isDone = false;
				}
			}
		}
	} while (isDone != true);

	// Set Settings Values
	floorDifficulty = menuLinesNumbers[2][4][2];
	floorTotal = menuLinesNumbers[2][5][2];
	enemyTotal = menuLinesNumbers[2][6][2];
	playerTotal = menuLinesNumbers[2][7][2];

	// Return Void
	return;
}

/******************************************************************************
 *                                  MENU FUNCTIONS                            *
 ******************************************************************************/

/******************************************************************************
 *                                    UI FUNCTIONS                            *
 ******************************************************************************/

// Function to Display Game Ui
// Accepts 2 Int Parameter(s) for Adjusting Ui
// Returns Double, passes Data by Member Access
double Game::gameUi(int uMENU, int uPAGE)
{
	// Initialize Variable(s) for gameUi()
	int // Initialize Int(s) for storing Int(s)
		uiHud = 5,
		uiChoices = 8,
		uiCombat = 10,
		dsChoiceMin = 1,
		dsChoiceMax = 4;
	double userDouble = (-1); // Initialize Double(s) for storing User Double(s)
	bool isDone = false;	  // Initialize Bool(s) for storing Bool(s)

	// Clear Terminal to Display Game Ui
	system("CLS");

	// cout Top Border, Each Corner Spaced by setw(40)
	cout << setw(40) << left << "+- - - - - - - - - - - - -"
		 << setw(40) << right << "- - - - - - - - - - - - -+"
		 << endl
		 << endl;

	// Display Game Ui HUD Line 1 - 4
	for (int uLINE = 1; uLINE < uiHud; ++uLINE)
	{
		// cout uiLines[uMENU][uLINE] lineLeft, then uiLines[uMENU][uLINE] lineRight, Centered to setw(40)
		cout << setw(40) << left << (uiLines[(stoi(uiLabels[uMENU][0]) + uPAGE)][uLINE][1] + to_string(uiLinesNumbers[0][uLINE][0]))
			 << setw(40) << right << (to_string(uiLinesNumbers[0][uLINE][1]) + uiLines[(stoi(uiLabels[uMENU][0]) + uPAGE)][uLINE][2]);

		// cout New Line
		cout << endl;
	}

	// Display Game Ui Combat Display Line 5 - 7
	for (int uLINE = 5; uLINE < uiChoices; ++uLINE)
	{
		// cout uiLines[uMENU][uLINE] lineLeft, then uiLines[uMENU][uLINE] lineRight, Centered to setw(40)
		cout << setw(40) << right << (uiLines[(stoi(uiLabels[uMENU][0]) + uPAGE)][uLINE][1] + to_string(uiLinesNumbers[0][uLINE][0]))
			 << setw(40) << left << (uiLines[(stoi(uiLabels[uMENU][0]) + uPAGE)][uLINE][2] + to_string(uiLinesNumbers[0][uLINE][1]));

		// If Line Has Value, cout Value Message
		if (uiLinesNumbers[0][uLINE][0] >= 0)
		{
			cout << uiLinesNumbers[0][uLINE][0];
		}

		// cout uiLines[uMENU][uLINE] lineRight
		cout << uiLines[(stoi(uiLabels[uMENU][0]) + uPAGE)][uLINE][2];

		// If Line is Selected, cout Selected Message
		if (uiLinesSelected[uLINE][0] == true)
		{
			cout << uiLines[(stoi(uiLabels[uMENU][0]) + uPAGE)][11][3];
		}

		// cout New Line
		cout << endl;
	}

	// Display Game Ui Recap Line 8 - 9
	for (int uLINE = 8; uLINE < uiCombat; ++uLINE)
	{
		// cout uiLines[uMENU][uLINE] lineLeft, then uiLines[uMENU][uLINE] lineRight, Centered to setw(40)
		cout << setw(40) << right << (uiLines[(stoi(uiLabels[uMENU][0]) + uPAGE)][uLINE][1] + to_string(uiLinesNumbers[0][uLINE][0]))
			 << setw(40) << left << (uiLines[(stoi(uiLabels[uMENU][0]) + uPAGE)][uLINE][2] + to_string(uiLinesNumbers[0][uLINE][1]));

		// cout New Line
		cout << endl;
	}

	// Display Game Ui Choices Line 10 - 11
	for (int uLINE = 10; uLINE < uLINES; ++uLINE)
	{
		// cout uiLines[uMENU][uLINE] lineLeft, then uiLines[uMENU][uLINE] lineRight, Centered to setw(40)
		cout << setw(40) << right << uiLines[(stoi(uiLabels[uMENU][0]) + uPAGE)][uLINE][1]
			 << left << uiLines[(stoi(uiLabels[uMENU][0]) + uPAGE)][uLINE][2];

		// cout New Line for All Lines, Except Last Line
		if (uLINE <= (uLINES - 2))
		{
			cout << endl;
		}
	}

	// Correct choiceMin
	if (uiLines[(stoi(uiLabels[uMENU][0]) + uPAGE)][0][3].substr(0, 1) == "+")
	{
		dsChoiceMin = (1000 * 1000);
	}
	else if (uiLines[(stoi(uiLabels[uMENU][0]) + uPAGE)][0][3].substr(0, 1) == "-")
	{
		dsChoiceMin = ((-1000) * (1000));
	}
	else
	{
		dsChoiceMin = stoi(uiLines[(stoi(uiLabels[uMENU][0]) + uPAGE)][0][3].substr(0, 1));
	}

	// Correct choiceMax
	if (uiLines[(stoi(uiLabels[uMENU][0]) + uPAGE)][0][3].substr(1, 1) == "+")
	{
		dsChoiceMax = (1000 * 1000);
	}
	else if (uiLines[(stoi(uiLabels[uMENU][0]) + uPAGE)][0][3].substr(1, 1) == "-")
	{
		dsChoiceMax = ((-1000) * (1000));
	}
	else
	{
		dsChoiceMax = stoi(uiLines[(stoi(uiLabels[uMENU][0]) + uPAGE)][0][3].substr(1, 1));
	}

	// Take User Choice Specified by Ui
	userDouble = dsChoiceNumber(dsChoiceMin, dsChoiceMax);

	// Return User Choice as Double
	return userDouble;
}

/******************************************************************************
 *                                    UI FUNCTIONS                            *
 ******************************************************************************/

/******************************************************************************
 *                                  CORE FUNCTIONS                            *
 ******************************************************************************/

// Function to Generate Random Number
// Requires 1 Int Parameter to Specify Max Value of Number by Default
// If Entered, also Accepts 1 Int Parameter to Specify Min Value of Number
// Returns Int, passes Data by Member Access
int Game::rndInt(int rndMax, int rndMin)
{
	static bool initialized{false};
	static mt19937 generator; // Mersenne Twister

	// Initialize the random engine if not already done
	if (!initialized)
	{
		// Use a random device to seed the generator
		random_device rd;
		generator.seed(rd());
		initialized = true;
	}

	uniform_int_distribution<int> distribution(rndMin, rndMax);

	// Return Random Number as Int
	return distribution(generator);
}

// Function to Generate Game RNG
// Requires 1 Int Parameter to Specify Odds of RNG Win
// Returns Bool, passes Data by Member Access
bool Game::rng(int rngChance)
{
	// Initialize an int Vector for RNG
	vector<int> rngArray;
	// Fill rngArray for RNG
	for (int i = 0; i < rngChance; ++i)
	{
		rngArray.push_back((i + 1));
	}

	// Initialize Variables for RNG
	bool rngWon = false;
	int rngWin = rndInt(rngChance);
	int rngIndex = rndInt((rngChance - 1), 0);
	cout << "rngWin: " << rngWin << '\t'
		 << "rngIndex: " << rngArray.at(rngIndex) << endl;

	// Return true if RNG Chance succeeded
	if (rngArray.at(rngIndex) == rngWin)
	{
		rngWon = true;
		cout << "- RNG Chance Succeeded -" << endl;
	}
	else
	{
		rngWon = false;
		cout << "- RNG Chance Failed -" << endl;
	}

	// Return RNG Win or Loss as Bool
	return rngWon;
}

// Function to Create New Floor
// Accepts No Parameter(s) by Default
// If Entered, also Accepts 1 Int Parameter to Specify Floor Index
// Returns Floor, passes Data by Member Access
Game::Floor Game::dsFloorNew(int floorIndex)
{
	// Initialize Variable(s) for dsFloorNew()
	Floor newFloor; // Initialize Floor(s) for storing Floor Data

	// Fill New Floor with Default Floor Data
	newFloor.floorName = ("Floor " + to_string(floorCount)); // Specify Name of Floor
	newFloor.floorIndex = floorIndex;						 // Specify Index of Floor
	newFloor.floorNumber = floorCount;						 // Specify Number of Floor

	// If dsFloorNew() is Called with No Parameter, Specify Index of Floor as Next Index
	if (floorIndex == (-1))
	{
		newFloor.floorIndex = (floorCount - 1); // Specify Index of Floor as Next Index
	}

	// Fill New Floor with Random Floor Data
	newFloor.floorLevel = (floorIndex + rndInt((3 + floorDifficulty), 0));		 // Specify Level of Floor
	newFloor.floorModifier = (1.0 + ((newFloor.floorLevel) / 10.0));			 // Specify Modifier of Floor
	newFloor.floorMoney = (rndInt((fLOOT * 2), fLOOT) * newFloor.floorModifier); // Specify Reward of Floor
	newFloor.isStore = rng(2);

	// Fill New Floor's Enemy Vector with New Enemies
	dsEnemyNew(newFloor.floorIndex);

	// Return New Floor
	return newFloor;
}

// Function to Create New Enemy
// Accepts No Parameter(s) by Default
// If Entered, also Accepts 1 Int Parameter to Specify Enemy Index
// Returns Person, passes Data by Member Access
Game::Person Game::dsEnemyNew(int enemyIndex)
{
	// Initialize Variable(s) for dsEnemyNew()
	Weapon noWeapon;					  // Initialize Weapon(s) for storing Weapon Data
	Armor noArmor;						  // Initialize Armor(s) for storing Armor Data
	Person newEnemy;					  // Initialize Person(s) for storing Person Data
	newEnemy.Weapons.push_back(noWeapon); // push_back() noWeapon to New Enemy's Weapon Vector
	newEnemy.Armors.push_back(noArmor);	  // push_back() noArmor to New Enemy's Armor Vector

	// Fill New Enemy with Default Enemy Data
	newEnemy.isPlayer = false;								  // Specify Person is Enemy
	newEnemy.personName = ("Enemy " + to_string(enemyCount)); // Specify Name of Enemy
	newEnemy.personIndex = enemyIndex;						  // Specify Index of Enemy
	newEnemy.personNumber = enemyCount;						  // Specify Number of Enemy

	// If dsEnemyNew() is Called with No Parameter, Specify Index of Enemy as Next Index
	if (enemyIndex == (-1))
	{
		newEnemy.personIndex = (enemyCount - 1); // Specify Index of Enemy as Next Index
	}

	// Fill New Enemy with Random Enemy Data
	newEnemy.personMoney = rndInt((eLOOT * 2), eLOOT); // Specify Reward of Enemy

	// Fill New Enemy with Random Weapon and Armor
	// Weapon newWeapon;					   // Initialize Weapon(s) for storing Weapon Data
	// Armor newArmor;						   // Initialize Armor(s) for storing Armor Data
	// newEnemy.Weapons.push_back(newWeapon); // push_back() New Weapon to New Enemy's Weapon Vector
	// newEnemy.Armors.push_back(newArmor);   // push_back() New Armor to New Enemy's Armor Vector
	// newEnemy.personWeapon = 1;			   // Specify Weapon Equipped to Enemy
	// newEnemy.personArmor = 1;			   // Specify Armor Equipped to Enemy

	// Fill New Enemy's rngArray for RNG
	for (int i = 0; i < rngASIZE; ++i)
	{
		newEnemy.rngArray[i] = (i + 1);
	}

	// Fill New Enemy's choiceArray for Random Choices
	for (int i = 0; i < rngASIZE; ++i)
	{
		newEnemy.choiceArray[i] = rndInt(rngESIZE);
	}

	// Return New Enemy
	return newEnemy;
}

// Function to Create New Player
// Accepts No Parameter(s) by Default
// If Entered, Accepts 1 Int Parameter to Specify Player Index
// Returns Person, passes Data by Member Access
Game::Person Game::dsPlayerNew(int playerIndex)
{
	// Initialize Variable(s) for dsPlayerNew()
	Weapon noWeapon;					   // Initialize Weapon(s) for storing Weapon Data
	Armor noArmor;						   // Initialize Armor(s) for storing Armor Data
	Person newPlayer;					   // Initialize Person(s) for storing Person Data
	newPlayer.Weapons.push_back(noWeapon); // push_back() noWeapon to New Player's Weapon Vector
	newPlayer.Armors.push_back(noArmor);   // push_back() noArmor to New Player's Armor Vector

	// Fill New Player with Default Player Data
	newPlayer.isPlayer = true;									  // Specify Person is Player
	newPlayer.personName = uiLines[playerIndex][3][2];			  // Specify Name of Player
	newPlayer.personCompany = uiLines[playerIndex][4][2];		  // Specify Name of Player
	newPlayer.personState = uiLines[playerIndex][5][2];			  // Specify Name of Player
	newPlayer.personCity = uiLines[playerIndex][6][2];			  // Specify Name of Player
	newPlayer.personType = uiLines[playerIndex][7][2];			  // Specify Name of Player
	newPlayer.personID = menuLinesNumbers[3][playerIndex + 4][2]; // Specify Name of Player
	newPlayer.personIndex = playerIndex;						  // Specify Index of Player
	newPlayer.personNumber = playerCount;						  // Specify Number of Player

	// If dsPlayerNew() is Called with No Parameter, Specify Index of Player as Next Index
	if (playerIndex == (-1))
	{
		newPlayer.personIndex = (playerCount - 1); // Specify Index of Player as Next Index
	}

	;

	// Fill New Player's Name with User Entered Name
	if (playerCount == -1) // -1 For TESTING, Set Back to 1
	{
		// Ask User to Enter Name
		cout << "Please Enter a Name: ";
		// Take User's Name with dsChoiceString()
		userName = dsChoiceString();
		cout << endl;
	}

	// Fill New Player with Random Weapon and Armor
	// Weapon newWeapon;						// Initialize Weapon(s) for storing Weapon Data
	// Armor newArmor;							// Initialize Armor(s) for storing Armor Data
	// newPlayer.Weapons.push_back(newWeapon); // push_back() New Weapon to New Player's Weapon Vector
	// newPlayer.Armors.push_back(newArmor);	// push_back() New Armor to New Player's Armor Vector
	// newPlayer.personWeapon = 1;				// Specify Weapon Equipped to Player
	// newPlayer.personArmor = 1;				// Specify Armor Equipped to Player

	// Fill New Player's rngArray for RNG
	for (int i = 0; i < rngASIZE; ++i)
	{
		newPlayer.rngArray[i] = (i + 1);
	}

	// Fill New Player's choiceArray for Random Choices
	for (int i = 0; i < rngASIZE; ++i)
	{
		newPlayer.choiceArray[i] = rndInt(rngESIZE);
	}

	// Return New Player
	return newPlayer;
}

// Function to Create New Game
// Accepts No Parameter(s)
// Returns Void, passes Data by Member Access
void Game::dsGameNew()
{
	// Fill Floor Vector with New Floors
	for (int i = 0; i < floorTotal; ++i)
	{
		// Specify Number of Floors Created
		++floorCount;
		// push_back() New Floor to Floors Vector
		Floors.push_back(dsFloorNew(i));

		// Fill New Floor's Enemy Vector with New Enemies
		for (int j = 0; j < enemyTotal; ++j)
		{
			// Specify Number of Enemies Created
			++enemyCount;
			// push_back() New Enemy to Enemies Vector
			Floors.at(i).Enemies.push_back(dsEnemyNew(j));
		}
	}

	// Fill Player Vector with New Players
	for (int i = 0; i < playerTotal; ++i)
	{
		// Specify Number of Players Created
		++playerCount;
		// push_back() New Player to Players Vector
		Players.push_back(dsPlayerNew(i));
	}

	// Set Customer Values
	menuLinesNumbers[3][4][2] = Players.at(0).personID;
	menuLinesNumbers[3][5][2] = Players.at(1).personID;
	menuLinesNumbers[3][6][2] = Players.at(2).personID;
	menuLinesNumbers[3][7][2] = Players.at(3).personID;

	// Return Void
	return;
}

/******************************************************************************
 *                                  CORE FUNCTIONS                            *
 ******************************************************************************/

/******************************************************************************
 *                                SYSTEM FUNCTIONS                            *
 ******************************************************************************/

// Function to Engage in Combat
// Accepts no Parameters
// Returns Void
void Game::gameCombat()
{
	// Initialize Variable(s) for gameSettings()
	int userInt = 0;	   // Initialize Int(s) for storing User Int(s)
	double userDouble = 0; // Initialize Double(s) for storing User Double(s)
	bool isDone = false;   // Initialize Bool(s) for storing Bool(s)

	for (int i = 0; i < floorTotal; ++i)
	{
		// Display New Floor Intro
		dsMenus(3);

		for (int j = 0; j < enemyTotal; ++j)
		{
			do
			{
				// Move to Next Round
				++floorRound;

				// Take Player's Combat Choice
				gamePlayerTurn(playerChoice, (enemyChoice - 1));

				// Take Enemy's Combat Choice
				gameEnemyTurn();

				// Consume Stamina for Actions in Combat
				Players.at(playerCurrent) -= Floors.at(floorCurrent).Enemies.at(enemyCurrent);

				// Deal Damage to Loser in Combat
				Players.at(playerCurrent) += Floors.at(floorCurrent).Enemies.at(enemyCurrent);

				// Stamina Recovery System
				gameStaminaRecovery();
			} while (Floors.at(floorCurrent).Enemies.at(enemyCurrent).personHealth > 0 && Players.at(playerCurrent).personHealth > 0);
			// Move to Next Enemy
			++enemyCurrent;
		}
		// Move to Next Floor
		++floorCurrent;
	}

	// Take User's Choice with dsChoiceNumber() while isDone != true;
	do
	{
		// If User is Editing, Display Settings Menu Page 2
		if (uiLinesSelected[4][0] == true || uiLinesSelected[5][0] == true || uiLinesSelected[6][0] == true || uiLinesSelected[7][0] == true)
		{
			// Display Settings Menu Page 2
			// gameUi(1);
		}

		// If User is Not Editing a Setting, Display Settings Menu Page 1
		else
		{
			// Display Settings Menu Page 1
			// gameUi(1);
		}

		// Check if User is Editing floorDifficulty
		if (uiLinesSelected[4][0] == true)
		{
			// Take User Choice of any Number
			floorDifficulty = dsChoiceNumber(1, 4);
			uiLinesNumbers[2][4][0] = floorDifficulty;
			uiLinesSelected[4][0] = false;
		}

		// Check if User is Editing floorTotal
		else if (uiLinesSelected[5][0] == true)
		{
			// Take User Choice of any Number
			floorTotal = dsChoiceNumber(1, 4);
			uiLinesNumbers[2][5][0] = floorTotal;
			uiLinesSelected[5][0] = false;
		}

		// Check if User is Editing enemyTotal
		else if (uiLinesSelected[6][0] == true)
		{
			// Take User Choice of any Number
			enemyTotal = dsChoiceNumber(1, 4);
			uiLinesNumbers[2][6][0] = enemyTotal;
			uiLinesSelected[6][0] = false;
		}

		// Check if User is Editing playerTotal
		else if (uiLinesSelected[7][0] == true)
		{
			// Take User Choice of any Number
			playerTotal = dsChoiceNumber(1, 4);
			uiLinesNumbers[2][7][0] = playerTotal;
			uiLinesSelected[7][0] = false;
		}

		// If User is Not Editing Settings, Display Ui 1
		else
		{
			// Take User Choice of (1 - 5)
			userInt = dsChoiceNumber(1, 5);

			// Check User Choice
			switch (userInt)
			{
			case 1: // If User Choice is 1, Continue
				isDone = true;
				break;
			case 2:							  // If User Choice is within range, Continue
				uiLinesSelected[4][0] = true; // Set Menu Line 4 to Selected
				isDone = false;
				break;
			case 3:							  // If User Choice is within range, Continue
				uiLinesSelected[5][0] = true; // Set Menu Line 5 to Selected
				isDone = false;
				break;
			case 4:							  // If User Choice is within range, Continue
				uiLinesSelected[6][0] = true; // Set Menu Line 6 to Selected
				isDone = false;
				break;
			case 5:							  // If User Choice is within range, Continue
				uiLinesSelected[7][0] = true; // Set Menu Line 7 to Selected
				isDone = false;
				break;
			default: // If User Choice is Not within range, Wait
				isDone = false;
				break;
			}
		}
	} while (isDone != true);

	// Fill menuLinesNumbers Array
	for (int uMENU = 0; uMENU < uMENUS; ++uMENU)
	{
		// Fill uiLinesNumbers Array Lines
		for (int uLINE = 0; uLINE < uLINES; ++uLINE)
		{
			// Fill uiLinesNumbers Array Columns
			for (int uCOL = 0; uCOL < uCOLS; ++uCOL)
			{
				// Fill uiLinesNumbers Array Columns with (-1)
				uiLinesNumbers[uMENU][uLINE][uCOL] = (-1);
			}
		}
	}

	// Return Void
	return;
}

// Function for Stamina Recovery System
// Accepts no parameters
// Returns void, passes data by member access
void Game::gameStaminaRecovery()
{
	// Stamina Recovery system
	if (((floorRound + 1) % 2) == 0)
	{
		// Recover Player's Stamina if allowed to
		if (Players.at(playerCurrent).isRecovering == true)
		{
			// Recover Player's Stamina
			if ((Players.at(playerCurrent).personStamina + sGAIN) > sMAX)
			{
				Players.at(playerCurrent).personStamina = sMAX;
			}
			else
			{
				Players.at(playerCurrent).personStamina += sGAIN;
			}
		}

		// Recover Enemy's Stamina if allowed to
		if (Floors.at(floorCurrent).Enemies.at(enemyCurrent).isRecovering == true)
		{
			// Recover Enemy's Stamina
			if ((Floors.at(floorCurrent).Enemies.at(enemyCurrent).personStamina + sGAIN) > sMAX)
			{
				Floors.at(floorCurrent).Enemies.at(enemyCurrent).personStamina = sMAX;
			}
			else
			{
				Floors.at(floorCurrent).Enemies.at(enemyCurrent).personStamina += sGAIN;
			}
		}
	}
	return;
}

/******************************************************************************
 *                                SYSTEM FUNCTIONS                            *
 ******************************************************************************/

/******************************************************************************
 *                                  GAME FUNCTIONS                            *
 ******************************************************************************/

// Function to Take User's Choice in Combat
// Requires 1 Int Parameter(s) for Current Ui Index
// Returns Void, passes Data by Member Access
void Game::gamePlayerTurn(int uMENU, int uPAGE)
{
	// Initialize Variable(s) for gamePlayerTurn()
	int userInt = (-1);		  // Initialize Int(s) for storing User Int(s)
	double userDouble = (-1); // Initialize Double(s) for storing User Double(s)
	bool isDone = false;	  // Initialize Bool(s) for storing Bool(s)

	// Reset Player
	// playerChoice = (-1);
	Players.at(playerCurrent).isRecovering = true;
	Players.at(playerCurrent).isAttacking = false;
	Players.at(playerCurrent).isBlocking = false;
	Players.at(playerCurrent).isDodging = false;
	Players.at(playerCurrent).isWaiting = false;

	// Set Ui Values
	uiLinesNumbers[0][0][0] = Players.at(playerCurrent).personHealth;
	uiLinesNumbers[0][0][1] = Floors.at(floorCurrent).Enemies.at(enemyCurrent).personHealth;
	uiLinesNumbers[0][1][0] = Players.at(playerCurrent).personStamina;
	uiLinesNumbers[0][1][1] = Floors.at(floorCurrent).Enemies.at(enemyCurrent).personStamina;
	uiLinesNumbers[0][2][0] = Players.at(playerCurrent).personMoney;
	uiLinesNumbers[0][2][1] = (enemyTotal - enemyCurrent);

	// Take User's Choice with dsChoiceNumber() while isDone != true;
	do
	{
		// Display Game Ui with Correct Ui Index
		userDouble = gameUi(uMENU, uPAGE);
		userInt = userDouble;

		// Check User Choice
		switch (userInt)
		{
		case 1: // If User Choice is 1, Attack
			// If User has enough Stamina, Attack
			if (Players.at(playerCurrent).personStamina >= aCOST)
			{
				Players.at(playerCurrent).isAttacking = true;
				isDone = true;
			}
			// If User does Not have enough Stamina, Take Choice Again
			else
			{
				isDone = false;
			}
			break;
		case 2: // If User Choice is 2, Block
			// Disable Stamina Recovery, Block
			Players.at(playerCurrent).isRecovering = false;
			Players.at(playerCurrent).isBlocking = true;
			isDone = true;
			break;
		case 3: // If User Choice is 3, Dodge
			// If User has enough Stamina, Dodge
			if (Players.at(playerCurrent).personStamina >= dCOST)
			{
				Players.at(playerCurrent).isDodging = true;
				isDone = true;
			}
			// If User does Not have enough Stamina, Take Choice Again
			else
			{
				isDone = false;
			}
			break;
		case 4: // If User Choice is 4, Wait
			// Enable Stamina Recovery, Wait
			Players.at(playerCurrent).isRecovering = true;
			Players.at(playerCurrent).isWaiting = true;
			isDone = true;
			break;
		case 9: // If User Choice is 9, Exit
			isDone = true;
			break;
		default: // If User Choice is Not within range, Wait
			isDone = false;
			break;
		}
	} while (isDone != true);

	// playerChoice = userInt
	playerChoice = userInt;

	// Return Void
	return;
}

// Function to Take Enemy's Choice in Combat
// Accepts No Parameter(s)
// Returns Void, passes Data by Member Access
void Game::gameEnemyTurn()
{
	// Initialize Variable(s) for gameEnemyTurn()
	int enemyInt = (-1); // Initialize Int(s) for storing Enemy Int(s)
	bool isDone = false; // Initialize Bool(s) for storing Bool(s)

	// Reset Enemy
	// enemyChoice = (-1);
	Floors.at(floorCurrent).Enemies.at(enemyCurrent).isRecovering = true;
	Floors.at(floorCurrent).Enemies.at(enemyCurrent).isAttacking = false;
	Floors.at(floorCurrent).Enemies.at(enemyCurrent).isBlocking = false;
	Floors.at(floorCurrent).Enemies.at(enemyCurrent).isDodging = false;
	Floors.at(floorCurrent).Enemies.at(enemyCurrent).isWaiting = false;

	// Take Enemy's Choice while isDone != true;
	do
	{
		// Take Enemy's Choice of (1 - 4)
		enemyInt = gameEnemyAi();

		// Check Enemy's Choice
		switch (enemyInt)
		{
		case 1: // If Enemy's Choice is 1, Attack
			// If Enemy has enough Stamina, Attack
			if (Floors.at(floorCurrent).Enemies.at(enemyCurrent).personStamina >= aCOST)
			{
				Floors.at(floorCurrent).Enemies.at(enemyCurrent).isAttacking = true;
				isDone = true;
			}
			// If Enemy does Not have enough Stamina, Take Choice Again
			else
			{
				isDone = false;
			}
			break;
		case 2: // If Enemy's Choice is 2, Block
			// Disable Stamina Recovery, Block
			Floors.at(floorCurrent).Enemies.at(enemyCurrent).isRecovering = false;
			Floors.at(floorCurrent).Enemies.at(enemyCurrent).isBlocking = true;
			isDone = true;
			break;
		case 3: // If Enemy's Choice is 3, Dodge
			// If Enemy has enough Stamina, Dodge
			if (Floors.at(floorCurrent).Enemies.at(enemyCurrent).personStamina >= dCOST)
			{
				Floors.at(floorCurrent).Enemies.at(enemyCurrent).isDodging = true;
				isDone = true;
			}
			// If Enemy does Not have enough Stamina, Take Choice Again
			else
			{
				isDone = false;
			}
			break;
		case 4: // If Enemy's Choice is 4, Wait
			// Enable Stamina Recovery, Wait
			Floors.at(floorCurrent).Enemies.at(enemyCurrent).isRecovering = true;
			Floors.at(floorCurrent).Enemies.at(enemyCurrent).isWaiting = true;
			isDone = true;
			break;
		default: // If Enemy's Choice is Not within range, Wait
			isDone = false;
			break;
		}
	} while (isDone != true);

	// enemyChoice = enemyInt
	enemyChoice = enemyInt;

	// Return Void
	return;
}

// Function to Decide Enemy's Choice in Combat
// Accepts No Parameter(s)
// Returns Void, passes Data by Member Access
int Game::gameEnemyAi()
{
	// Initialize Variable(s) for gameEnemyAi()
	int enemyInt = (-1); // Initialize Int(s) for storing Enemy Int(s)

	// If Enemy has enough Stamina to Dodge, Decide
	if (Floors.at(floorCurrent).Enemies.at(enemyCurrent).personStamina >= dCOST)
	{
		// If Player's Stamina is too Low to Act, Decide Attack
		if (Players.at(playerCurrent).personStamina < aCOST)
		{
			enemyInt = 1;
		}

		// If Player has too Little Stamina to Block Safely, Decide Dodge or Attack
		else if (Players.at(playerCurrent).personStamina <= bCOST)
		{
			bool choice1 = rng(rndInt(4)); // Default 3

			// Chance of Attack
			if (choice1 == true)
			{
				enemyInt = 1;
			}

			// Prefer Dodge
			else
			{
				enemyInt = 3;
			}
		}

		// If Player has too Little Stamina to Dodge, Decide Attack or Dodge
		else if (Players.at(playerCurrent).personStamina < dCOST)
		{
			bool choice2 = rng(rndInt(4)); // Default 3
			// Chance of Dodge
			if (choice2 == true)
			{
				enemyInt = 3;
			}

			// Prefer Attack
			else
			{
				enemyInt = 1;
			}
		}

		// If Player has enough Stamina to Dodge, Decide Attack Block or Dodge
		else
		{
			int choice3 = rndInt((rngASIZE - 1), 0);
			enemyInt = Floors.at(floorCurrent).Enemies.at(enemyCurrent).choiceArray[choice3];
		}
	}

	// If Enemy has enough Stamina to Block Safely, Decide
	else if (Floors.at(floorCurrent).Enemies.at(enemyCurrent).personStamina > bCOST)
	{
		// If Player has too Little Stamina to Act, Decide Attack
		if (Players.at(playerCurrent).personStamina < aCOST)
		{
			enemyInt = 1;
		}

		// If Player has too Little Stamina to Block Safely, Decide Block or Attack
		else if (Players.at(playerCurrent).personStamina <= bCOST)
		{
			bool choice4 = rng(rndInt(4)); // Default 3
			// Chance of Attack
			if (choice4 == true)
			{
				enemyInt = 1;
			}

			// Prefer Block
			else
			{
				enemyChoice = 2;
			}
		}

		// If Player has too Little Stamina to Dodge, Decide Attack or Block
		else if (Players.at(playerCurrent).personStamina < dCOST)
		{
			bool choice5 = rng(rndInt(4)); // Default 3
			// Chance of Block
			if (choice5 == true)
			{
				enemyInt = 2;
			}

			// Prefer Attack
			else
			{
				enemyInt = 1;
			}
		}

		// If Player has enough Stamina to Dodge, Decide Block or Attack
		else
		{
			bool choice6 = rng(rndInt(4)); // Default 3
			// Chance of Attack
			if (choice6 == true)
			{
				enemyInt = 1;
			}

			// Prefer Block
			else
			{
				enemyInt = 2;
			}
		}
	}

	// If Enemy only has enough Stamina to Attack, Decide Attack or Block
	else if (Floors.at(floorCurrent).Enemies.at(enemyCurrent).personStamina >= aCOST)
	{
		// If Player has enough Stamina to Dodge, Decide Attack or Block
		if (Players.at(playerCurrent).personStamina >= dCOST)
		{
			bool choice7 = rng(rndInt(4));
			// Chance of Block
			if (choice7 == true)
			{
				enemyInt = 2;
			}

			// Prefer Attack
			else
			{
				enemyInt = 1;
			}
		}

		// If Player has too Little Stamina to Dodge, Decide Attack
		else
		{
			enemyInt = 1;
		}
	}

	// If Enemy has too Little Stamina to Act, Wait
	else
	{
		enemyInt = 4;
	}

	// Return Enemy's Decision as Int
	return enemyInt;
}

/******************************************************************************
 *                                  GAME FUNCTIONS                            *
 ******************************************************************************/
