/******************************************************************************
Dos Souls

Donnie Gilbert
CS162-W1 SP24 Priestley

Purpose of the program:
Make a game for weekly homework.

Specification Summary:
A game where 2 opponents fight to the death in a series
of multi-rounded games of Rock, Paper, Scissors matches until 1 person's health
reaches 0. The game is played in the format of Attack, Block, Dodge, and runs on
a system of Stamina which is a resource required to be able to perform an Attack,
Block, or Dodge. If a person does NOT have enough stamina to Attack, Block,
or Dodge, they must "Wait" which is a state of no action leaving them open to
being attacked, but allowed to regain Stamina while spending 0 Stamina.
The player engages in combat 1 stage, named Floor(s), at a time for a
specifed amount of Floors (Default is 10 Floors).
The player enters 1 Floor at a time, and each floor has a
specifed amount of Enemies per Floor (Default is 1 Enemy per Floor).

Game Rules:
Attack	beats	Block	-	Attacker deals Damage to Blocker divided by block strength.
Block	beats	Dodge	-	Blocker deals Damage to Dodger.
Dodge	beats	Attack	-	Dodger deals Damage to Attacker.
If a Blocker Blocks an Attack, and the Blocker's Stamina reaches 0 or Lower,
Blocker gets Stunned, and Attacker deals ANOTHER UNBlocked Damage to Blocker.
Being a Waiter instead of a Blocker is the only way to avoid this.

Game Notes:
Combat is augmented with a system of Items in the form of Weapons and Armor.
Combat Difficulty increases as the player progresses through floors.

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

// Function to take User's Choice with Getline()
// Accepts no Parameters
// Returns User's Choice as String
string Game::gameChoiceString()
{
	// Initialize Variable(s) for gameChoiceString()
	string userString = "0"; // Initialize Strings(s) for storing User String(s)
	bool isAlnums = true;	 // Initialize Bool(s) for storing Bool(s)

	// Take User's Choice with Getline()
	getline(cin, userString);

	// Checks User's Choice for Alnums
	for (int i = 0; isAlnums && i < userString.length(); ++i)
	{
		// If Char in String is NOT an Alnum, Empty Variable(s)
		if (!(isalnum(userString[i])))
		{
			isAlnums = false;
		}
	}

	// If isAlnums == false, Empty Variable(s)
	if (isAlnums == false)
	{
		userString = "0";
	}

	// End gameChoiceString() with a Newline
	cout << endl;

	// Return User's Choice as userString
	return userString;
}

// Function to take User's Choice with Getline()
// Accepts 2 Int Parameters for Minimum Range and Maximum Range of User's Choice
// Returns User's Choice as Double
double Game::gameChoiceInt(int minInt, int maxInt)
{
	// Initialize Variable(s) for gameChoiceInt()
	string userString = "0"; // Initialize Strings(s) for storing User String(s)
	double userDouble = 0;	 // Initialize Double(s) for storing User Double(s)
	bool					 // Initialize Bool(s) for storing Bool(s)
		isInt = true,
		isDigits = true;

	// Take User's Choice with Getline()
	getline(cin, userString);

	// If String is 0, Return 0
	if (userString[0] == '0')
	{
		userString = "0";
		userDouble = 0;
	}

	// If String is Not 0, Check User's Choice
	else
	{
		// If no Minimum Range and Maximum Range, Accept Numbers Larger than 1 Digit
		if (minInt == 0 && maxInt == 0)
		{
			// If Char in userString[0] is Not a Negative Sign or NOT a Digit, Empty Variable(s)
			if (userString[0] != '-' && !(isdigit(userString[0])))
			{
				isDigits = false;
			}

			// If Char in userString[0] is a Negative Sign and no Digits, Empty Variable(s)
			else if (userString[0] == '-' && userString.length() < 2)
			{
				isDigits = false;
			}

			// If Char in userString[0] has a Negative Sign and/or has Digit(s), Continue
			else
			{
				// Checks User's Choice for Digits
				for (int i = 1; isDigits && i < userString.length(); ++i)
				{
					// If Char in String is NOT a Digit, Empty Variable(s)
					if (!(isdigit(userString[i])))
					{
						isDigits = false;
					}
				}
			}

			// If all Char(s) in String is/are Digit(s), Return String as Double
			if (isDigits == true)
			{
				userDouble = stod(userString);
			}

			// If isDigits == false, Empty Variable(s)
			else
			{
				userString = "0";
				userDouble = 0;
			}
		}

		// If Minimum Range or Maximum Range specified, Only accept Numbers with 1 Digit
		else
		{
			// If Char in userString[0] is Not 1 and NOT a Digit, Empty Variable(s)
			if (userString.length() != 1 || !(isdigit(userString[0])))
			{
				isInt = false;
			}

			// If Char in userString[0] < minInt or userString[0] > maxInt, Empty Variable(s)
			else if (stoi(userString) < minInt || stoi(userString) > maxInt)
			{
				isInt = false;
			}

			// If Char in String is an Int, Return String as Double
			if (isInt == true)
			{
				userDouble = stod(userString);
			}

			// If isInt == false, Empty Variable(s)
			else
			{
				userString = "0";
				userDouble = 0;
			}
		}
	}

	// End gameChoiceInt() with a Newline
	cout << endl;

	// Return User's Choice as userDouble
	return userDouble;
}

/******************************************************************************
 *                              INTERACT FUNCTIONS                            *
 ******************************************************************************/

/******************************************************************************
 *                                  MENU FUNCTIONS                            *
 ******************************************************************************/

// Function to Fill Menu Line Array
// Accepts no Parameters
// Returns Void
void Game::gameAddData()
{
	// Initialize Variable(s) for gameAddData()
	ifstream fileGame; // Initialize ifstream(s) for storing ifstream(s)
	string lineNew;	   // Initialize Strings(s) for storing String(s)

	// Open fileMenus
	fileGame.open(fileMenus);
	if (fileGame.is_open())
	{
		// Output fileMenus opened successfully to console
		cout << "File, " << fileMenus << ", opened successfully" << endl
			 << endl;

		// Fill Menu Line Array Pages
		for (int mMENU = 0; mMENU < mMENUS; ++mMENU)
		{
			// Fill Menu Line Array Lines
			for (int mLINE = 0; mLINE < mLINES; ++mLINE)
			{
				// Fill Menu Line Array Columns
				for (int mCOL = 0; mCOL < mCOLS; ++mCOL)
				{
					// Store Menu Line Array Columns at menuLines[mMENU][mLINE][mCOL]
					getline(fileGame, menuLines[mMENU][mLINE][mCOL], ';');
				}

				// Advance to Next Menu Line
				getline(fileGame, lineNew);
			}
		}

		// Close fileMenus
		fileGame.close();
	}

	// Error if fileMenus did Not Open
	else
	{
		// Output fileMenus failed to open to console
		cout << "File, " << fileMenus << ", failed to open" << endl
			 << endl;
	}

	// Open fileUi
	fileGame.open(fileUi);
	if (fileGame.is_open())
	{
		// Output fileUi opened successfully to console
		cout << "File, " << fileUi << ", opened successfully" << endl
			 << endl;

		// Fill Ui Line Array Pages
		for (int uMENU = 0; uMENU < uMENUS; ++uMENU)
		{
			// Fill Ui Line Array Lines
			for (int uLINE = 0; uLINE < uLINES; ++uLINE)
			{
				// Fill Ui Line Array Columns
				for (int uCOL = 0; uCOL < uCOLS; ++uCOL)
				{
					// Store Ui Line Array Columns at uiLines[uMENU][uLINE][uCOL]
					getline(fileGame, uiLines[uMENU][uLINE][uCOL], ';');
				}

				// Advance to Next Ui Line
				getline(fileGame, lineNew);
			}
		}

		// Close fileUi
		fileGame.close();
	}

	// Error if fileUi did Not Open
	else
	{
		// Output fileUi failed to open to console
		cout << "File, " << fileUi << ", failed to open" << endl
			 << endl;
	}

	// Fill menuLinesNumbers Array Lines with (-1)
	for (int mLINE = 0; mLINE < mLINES; ++mLINE)
	{
		// Fill menuLinesNumbers Array Columns with (-1)
		for (int mCOL = 0; mCOL < mCOLS; ++mCOL)
		{
			menuLinesNumbers[mLINE][mCOL] = (-1);
		}
	}

	// Fill uiLinesNumbers Array Lines with (-1)
	for (int uLINE = 0; uLINE < uLINES; ++uLINE)
	{
		// Fill uiLinesNumbers Array Columns with (-1)
		for (int uCOL = 0; uCOL < uCOLS; ++uCOL)
		{
			uiLinesNumbers[uLINE][uCOL] = (-1);
		}
	}

	return;
}

// Function to Display Game Menus
// Accepts 5 Int Parameters for adjusting output of Menu Lines
// Returns Void
int Game::gameMenu(int mMENU, int mPAGE, int mLINETOTAL, int sLINEMIN, int sLINEMAX)
{
	// Initialize Variable(s) for gameMenu()
	int userInt = 0;	   // Initialize Int(s) for storing User Int(s)
	double userDouble = 0; // Initialize Double(s) for storing User Double(s)
	bool				   // Initialize Bool(s) for storing Bool(s)
		isMenu = false,
		isDone = false;

	// Set Any menuLinesSelected[sLINE][0] == true
	for (int sLINE = sLINEMIN; sLINE < (sLINEMIN + sLINEMAX); ++sLINE)
	{
		menuLinesSelected[sLINE][0] = true;
	}

	// Clear Terminal to Display Game Menu
	system("CLS");

	// Display Game Menu
	for (int mLINE = 1; mLINE < mLINETOTAL; ++mLINE)
	{
		// cout menuLines[mMENU][mLINE] lineLeft, then menuLines[mMENU][mLINE] lineRight, Centered to setw(40)
		cout << setw(40) << right << menuLines[mMENU][mLINE][1]
			 << left;

		// If Line Has Value, cout Value Message
		if (menuLinesNumbers[mLINE][0] >= 0)
		{
			cout << menuLinesNumbers[mLINE][0];
		}

		// cout menuLines[mMENU][mLINE] lineRight
		cout << menuLines[mMENU][mLINE][2];

		// If Line is Selected, cout Selected Message
		if (menuLinesSelected[mLINE][0] == true)
		{
			cout << menuLines[mMENU][11][3];
		}

		// cout New Line for All Lines, Except Last Line
		if (mLINE <= (mLINES - 2))
		{
			cout << endl;
		}
	}

	// Take User Choice Specified by Menu
	userInt = gameChoiceInt(menuLines[mMENU][0][1][0], menuLines[mMENU][0][1][1]);

	// Return User Choice as Int
	return userInt;
}

// Function to Display Intro Menu
// Accepts no Parameters
// Returns Void
void Game::gameIntro()
{
	// Initialize Variable(s) for Intro()
	int userInt = 0;	   // Initialize Int(s) for storing User Int(s)
	double userDouble = 0; // Initialize Double(s) for storing User Double(s)
	bool isDone = false;   // Initialize Bool(s) for storing Bool(s)

	// Take User's Choice with gameChoiceInt() while isDone != true;
	do
	{
		// Display Intro Menu
		gameMenu(1);

		// Take User Choice of (1 - 1)
		userInt = gameChoiceInt(1, 1);

		// Check User Choice
		switch (userInt)
		{
		case 1: // If User Choice is 1, Continue
			isDone = true;
			break;
		default: // If User Choice is Not 1, Wait
			isDone = false;
			break;
		}
	} while (isDone != true);

	// Return Void
	return;
}

// Function to Display Rules Menu
// Accepts no Parameters
// Returns Void
void Game::gameRules()
{
	// Initialize Variable(s) for gameRules()
	int userInt = 0;	   // Initialize Int(s) for storing User Int(s)
	double userDouble = 0; // Initialize Double(s) for storing User Double(s)
	bool isDone = false;   // Initialize Bool(s) for storing Bool(s)

	// Take User's Choice with gameChoiceInt() while isDone != true;
	do
	{
		// Display Rules Menu
		gameMenu(2);

		// Take User Choice of (1 - 1)
		userInt = gameChoiceInt(1, 1);

		// Check User Choice
		switch (userInt)
		{
		case 1: // If User Choice is 1, Continue
			isDone = true;
			break;
		default: // If User Choice is Not 1, Wait
			isDone = false;
			break;
		}
	} while (isDone != true);

	// Return Void
	return;
}

// Function to Display Settings Menu
// Accepts no Parameters
// Returns Void
void Game::gameSettings()
{
	// Initialize Variable(s) for gameSettings()
	int userInt = 0;	   // Initialize Int(s) for storing User Int(s)
	double userDouble = 0; // Initialize Double(s) for storing User Double(s)
	bool isDone = false;   // Initialize Bool(s) for storing Bool(s)

	// Set Settings Values
	menuLinesNumbers[4][0] = floorDifficulty;
	menuLinesNumbers[5][0] = floorTotal;
	menuLinesNumbers[6][0] = enemyTotal;
	menuLinesNumbers[7][0] = playerTotal;

	// Take User's Choice with gameChoiceInt() while isDone != true;
	do
	{
		// If User is Editing, Display Settings Menu Page 2
		if (menuLinesSelected[4][0] == true || menuLinesSelected[5][0] == true || menuLinesSelected[6][0] == true || menuLinesSelected[7][0] == true)
		{
			// Display Settings Menu Page 2
			gameMenu(3, 2);
		}

		// If User is Not Editing a Setting, Display Settings Menu Page 1
		else
		{
			// Display Settings Menu Page 1
			gameMenu(3);
		}

		// Check if User is Editing floorDifficulty
		if (menuLinesSelected[4][0] == true)
		{
			// Take User Choice of any Number
			floorDifficulty = gameChoiceInt(1, 9);
			menuLinesNumbers[4][0] = floorDifficulty;
			menuLinesSelected[4][0] = false;
		}

		// Check if User is Editing floorTotal
		else if (menuLinesSelected[5][0] == true)
		{
			// Take User Choice of any Number
			floorTotal = gameChoiceInt(1, 9);
			menuLinesNumbers[5][0] = floorTotal;
			menuLinesSelected[5][0] = false;
		}

		// Check if User is Editing enemyTotal
		else if (menuLinesSelected[6][0] == true)
		{
			// Take User Choice of any Number
			enemyTotal = gameChoiceInt(1, 9);
			menuLinesNumbers[6][0] = enemyTotal;
			menuLinesSelected[6][0] = false;
		}

		// Check if User is Editing playerTotal
		else if (menuLinesSelected[7][0] == true)
		{
			// Take User Choice of any Number
			playerTotal = gameChoiceInt(1, 9);
			menuLinesNumbers[7][0] = playerTotal;
			menuLinesSelected[7][0] = false;
		}

		// If User is Not Editing Settings, Display Settings Menu Page 1
		else
		{
			// Take User Choice of (1 - 5)
			userInt = gameChoiceInt(1, 5);

			// Check User Choice
			switch (userInt)
			{
			case 1: // If User Choice is 1, Continue
				isDone = true;
				break;
			case 2:								// If User Choice is within range, Open Setting
				menuLinesSelected[4][0] = true; // Set Menu Line 4 to Selected
				isDone = false;
				break;
			case 3:								// If User Choice is within range, Open Setting
				menuLinesSelected[5][0] = true; // Set Menu Line 5 to Selected
				isDone = false;
				break;
			case 4:								// If User Choice is within range, Open Setting
				menuLinesSelected[6][0] = true; // Set Menu Line 6 to Selected
				isDone = false;
				break;
			case 5:								// If User Choice is within range, Open Setting
				menuLinesSelected[7][0] = true; // Set Menu Line 7 to Selected
				isDone = false;
				break;
			default: // If User Choice is Not within range, Wait
				isDone = false;
				break;
			}
		}
	} while (isDone != true);

	// Fill menuLinesNumbers Array Lines with (-1)
	for (int mLINE = 0; mLINE < mLINES; ++mLINE)
	{
		// Fill menuLinesNumbers Array Columns with (-1)
		for (int mCOL = 0; mCOL < mCOLS; ++mCOL)
		{
			menuLinesNumbers[mLINE][mCOL] = (-1);
		}
	}

	// Return Void
	return;
}

// Function to Display Floor Intro
// Accepts no Parameters
// Returns Void, passes data by member access
void Game::gameFloorIntro()
{
	// Initialize Variable(s) for gameSettings()
	int userInt = 0;	   // Initialize Int(s) for storing User Int(s)
	double userDouble = 0; // Initialize Double(s) for storing User Double(s)
	bool isDone = false;   // Initialize Bool(s) for storing Bool(s)

	// Set Settings Values
	menuLinesNumbers[5][0] = (floorCurrent + 1);

	// Take User's Choice with gameChoiceInt() while isDone != true;
	do
	{
		// Display Floor Intro
		gameMenu(4);

		// Take User Choice of (1 - 1)
		userInt = gameChoiceInt(1, 1);

		// Check User Choice
		switch (userInt)
		{
		case 1: // If User Choice is 1, Continue
			isDone = true;
			break;
		default: // If User Choice is Not 1, Wait
			isDone = false;
			break;
		}
	} while (isDone != true);

	// Fill menuLinesNumbers Array Lines with (-1)
	for (int mLINE = 0; mLINE < mLINES; ++mLINE)
	{
		// Fill menuLinesNumbers Array Columns with (-1)
		for (int mCOL = 0; mCOL < mCOLS; ++mCOL)
		{
			menuLinesNumbers[mLINE][mCOL] = (-1);
		}
	}

	// Return Void
	return;
}

// Function to Display Outro Menu
// Accepts no Parameters
// Returns Void
void Game::gameOutro()
{
	// Initialize Variable(s) for Outro()
	int userInt = 0;	   // Initialize Int(s) for storing User Int(s)
	double userDouble = 0; // Initialize Double(s) for storing User Double(s)
	bool isDone = false;   // Initialize Bool(s) for storing Bool(s)

	// Take User's Choice with gameChoiceInt() while isDone != true;
	do
	{
		// Display Rules Menu
		gameMenu(1);

		// Take User Choice of (1 - 1)
		userInt = gameChoiceInt(1, 1);

		// Check User Choice
		switch (userInt)
		{
		case 1: // If User Choice is 1, Continue
			isDone = true;
			break;
		default: // If User Choice is Not 1, Wait
			isDone = false;
			break;
		}
	} while (isDone != true);

	// Return Void
	return;
}

// Function to Display Game Menus
// Accepts no Parameters
// Returns Void
void Game::gameMenus(int mMENU, int mPAGE)
{
	// Initialize Variable(s) for gameMenus()
	int userInt = 0;	   // Initialize Int(s) for storing User Int(s)
	double userDouble = 0; // Initialize Double(s) for storing User Double(s)
	bool				   // Initialize Bool(s) for storing Bool(s)
		isMenu = false,
		isIntro = false,
		isRules = false,
		isSettings = false,
		isFloorIntro = false,
		isOutro = false,
		isDone = false,
		isPaused = false,
		isChoice[10];

	// Find mMENU in menuLines[i][0][0]
	for (int i = 0; !(isMenu) && i < mMENUS; ++i)
	{
		// If Menu Index is found, Correct mMENU with Menu Index
		if (stoi(menuLines[i][0][0]) == mMENU)
		{
			// Correct mMENU with Menu Page Index
			mMENU = i + (mPAGE - 1);
			isMenu = true;
		}
	}

	// Fill isChoice[] with false
	for (int i = 0; i < 10; ++i)
	{
		isChoice[i] = false;
	}

	// If mMENU != 0, Open Selected Menu
	if (mMENU != 0)
	{
		if (isSettings == true)
		{
			// Set Settings Values
			menuLinesNumbers[4][0] = floorDifficulty;
			menuLinesNumbers[5][0] = floorTotal;
			menuLinesNumbers[6][0] = enemyTotal;
			menuLinesNumbers[7][0] = playerTotal;
		}

		else if (isFloorIntro == true)
		{
			// Set Settings Values
			menuLinesNumbers[5][0] = (floorCurrent + 1);
		}

		// Take User's Choice with gameChoiceInt() while isDone != true;
		do
		{
			// If User is Editing, Display Settings Menu Page 2
			if (menuLinesSelected[4][0] == true || menuLinesSelected[5][0] == true || menuLinesSelected[6][0] == true || menuLinesSelected[7][0] == true)
			{
				// Display Settings Menu Page 2
				mPAGE = 2;
			}

			// If User is Not Editing a Setting, Display Settings Menu Page 1
			else
			{
				// Display Settings Menu Page 1
				mPAGE = 1;
			}

			// Display Menu and Take User Choice
			userInt = gameMenu(mMENU, mPAGE);

			// Check if User is Editing floorDifficulty
			if (menuLinesSelected[4][0] == true)
			{
				// Take User Choice of any Number
				floorDifficulty = userInt;
				menuLinesNumbers[4][0] = floorDifficulty;
				menuLinesSelected[4][0] = false;
			}

			// Check if User is Editing floorTotal
			else if (menuLinesSelected[5][0] == true)
			{
				// Take User Choice of any Number
				floorTotal = userInt;
				menuLinesNumbers[5][0] = floorTotal;
				menuLinesSelected[5][0] = false;
			}

			// Check if User is Editing enemyTotal
			else if (menuLinesSelected[6][0] == true)
			{
				// Take User Choice of any Number
				enemyTotal = userInt;
				menuLinesNumbers[6][0] = enemyTotal;
				menuLinesSelected[6][0] = false;
			}

			// Check if User is Editing playerTotal
			else if (menuLinesSelected[7][0] == true)
			{
				// Take User Choice of any Number
				playerTotal = userInt;
				menuLinesNumbers[7][0] = playerTotal;
				menuLinesSelected[7][0] = false;
			}

			// If User is Not Editing Settings, Display Settings Menu Page 1
			else
			{
				// Check User Choice
				switch (userInt)
				{
				case 1: // If User Choice is 1, Continue
					// Send Choice 1 to Menu
					isChoice[1] = true;

					// Close the Menus
					isDone = true;
					break;
				case 2: // If User Choice is 2, Continue
					// Send Choice 2 to Menu
					isChoice[2] = true;

					// If Settings
					if (isSettings == true)
					{
						menuLinesSelected[4][0] = true; // Set Menu Line 4 to Selected
					}

					// Keep Menus Running until Closed
					isDone = false;
					break;
				case 3: // If User Choice is 3, Continue
					// Send Choice 3 to Menu
					isChoice[3] = true;

					// If Settings
					if (isSettings == true)
					{
						menuLinesSelected[5][0] = true; // Set Menu Line 5 to Selected
					}

					// Keep Menus Running until Closed
					isDone = false;
					break;
				case 4: // If User Choice is 4, Continue
					// Send Choice 4 to Menu
					isChoice[4] = true;

					// If Settings
					if (isSettings == true)
					{
						menuLinesSelected[6][0] = true; // Set Menu Line 6 to Selected
					}

					// Keep Menus Running until Closed
					isDone = false;
					break;
				case 5: // If User Choice is 5, Continue
					// Send Choice 5 to Menu
					isChoice[5] = true;

					// If Settings
					if (isSettings == true)
					{
						menuLinesSelected[7][0] = true; // Set Menu Line 7 to Selected
					}

					// Keep Menus Running until Closed
					isDone = false;
					break;
				case 6: // If User Choice is 6, Continue
					// Send Choice 6 to Menu
					isChoice[6] = true;

					// Keep Menus Running until Closed
					isDone = false;
					break;
				case 7: // If User Choice is 7, Continue
					// Send Choice 7 to Menu
					isChoice[7] = true;

					// Keep Menus Running until Closed
					isDone = false;
					break;
				case 8: // If User Choice is 8, Continue
					// Send Choice 8 to Menu
					isChoice[8] = true;

					// Keep Menus Running until Closed
					isDone = false;
					break;
				case 9: // If User Choice is 9, Continue
					// Send Choice 9 to Menu
					isChoice[9] = true;

					// Keep Menus Running until Closed
					isDone = false;
					break;
				case 0: // If User Choice is 0, Continue
					// Send Choice 0 to Menu
					isChoice[0] = true;

					// Keep Menus Running until Closed
					isDone = false;
					break;
				default: // If Error, Take Choice Again
					// Keep Menus Running until Closed
					isDone = false;
					break;
				}
			}
		} while (isDone != true);

		// Fill menuLinesNumbers Array Lines with (-1)
		for (int mLINE = 0; mLINE < mLINES; ++mLINE)
		{
			// Fill menuLinesNumbers Array Columns with (-1)
			for (int mCOL = 0; mCOL < mCOLS; ++mCOL)
			{
				menuLinesNumbers[mLINE][mCOL] = (-1);
			}
		}
	}

	// If mMENU == 0, Select Menu
	else
	{
		// Game is Paused
		isPaused = true;

		// Take User's Choice with gameChoiceInt() while isPaused == true;
		do
		{
			// Display Menu and Take User Choice
			userInt = gameMenu(mMENU);

			// Fill isChoice[] with false
			for (int i = 0; i < 10; ++i)
			{
				isChoice[i] = false;
			}

			// Check User Choice
			switch (userInt)
			{
			case 1: // If User Choice is 1, Continue
				// Send Choice 1 to Menu
				isChoice[1] = true;
				isDone = true;

				// Keep Menus Running until Closed
				isPaused = false;
				break;
			case 2: // If User Choice is 2, Continue
				// Send Choice 2 to Menu
				isChoice[2] = true;

				// Keep Menus Running until Closed
				isPaused = false;
				break;
			case 3: // If User Choice is 3, Continue
				// Send Choice 3 to Menu
				isChoice[3] = true;

				// Keep Menus Running until Closed
				isPaused = false;
				break;
			case 4: // If User Choice is 4, Continue
				// Send Choice 4 to Menu
				isChoice[4] = true;

				// Keep Menus Running until Closed
				isPaused = false;
				break;
			case 5: // If User Choice is 5, Continue
				// Send Choice 5 to Menu
				isChoice[5] = true;

				// Keep Menus Running until Closed
				isPaused = false;
				break;
			case 6: // If User Choice is 6, Continue
				// Send Choice 6 to Menu
				isChoice[6] = true;

				// Keep Menus Running until Closed
				isPaused = false;
				break;
			case 7: // If User Choice is 7, Continue
				// Send Choice 7 to Menu
				isChoice[7] = true;

				// Keep Menus Running until Closed
				isPaused = false;
				break;
			case 8: // If User Choice is 8, Continue
				// Send Choice 8 to Menu
				isChoice[8] = true;

				// Keep Menus Running until Closed
				isPaused = false;
				break;
			case 9: // If User Choice is 9, Continue
				// Send Choice 9 to Menu
				isChoice[9] = true;

				// Close the Menus
				isPaused = true;
				break;
			case 0: // If User Choice is 0, Continue
				// Send Choice 0 to Menu
				isChoice[0] = true;

				// Keep Menus Running until Closed
				isPaused = false;
				break;
			default: // If Error, Take Choice Again
				// Keep Menus Running until Closed
				isPaused = false;
				break;
			}
		} while (isPaused == true);
	}

	// Return Void
	return;
}

/******************************************************************************
 *                                  MENU FUNCTIONS                            *
 ******************************************************************************/

/******************************************************************************
 *                                    UI FUNCTIONS                            *
 ******************************************************************************/

/******************************************************************************
 *                                    UI FUNCTIONS                            *
 ******************************************************************************/

/******************************************************************************
 *                                SYSTEM FUNCTIONS                            *
 ******************************************************************************/

// Function to generate a random integer in the range [rndMax, rndMin]
// Accepts integer parameter for max value
// Can accept 2nd integer parameter for min value, Default min value = 1
// Returns an integer from rndMin to rndMax, inclusive
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

	return distribution(generator);
}

// Function to add game RNG
// Accepts integer parameter to determine Maximum numbers to guess from
// Returns bool, passes data by member access
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
	return rngWon;
}

// Function to fill Floor arrays and Floors vectors with Floors data
// Accepts no parameters if called with 0 parameters,
// otherwise, accepts 1 int parameter for total Floor count.
// and accepts 1 string parameter for game Floors file. Format: ("file.txt")
// Returns void, passes data by member access
Game::Floor Game::gameAddFloor(int i)
{
	// Create new Floor with Default items
	Floor newFloor; // Initialize Default Floor

	// Generate Floor data
	newFloor.floorIndex = i;										// Specify Index of Floor
	newFloor.floorNumber = floorCount;								// Specify Number of Floor
	newFloor.floorDescription = ("Floor " + to_string(floorCount)); // Specify Default Description of Floors

	// Generate random Floor data
	newFloor.floorLevel = (i + rndInt((3 + floorDifficulty), (0 + floorDifficulty))); // Specify Level of Floor
	newFloor.floorModifier = (1 + ((newFloor.floorLevel) / 10));					  // Specify Modifier of Floor
	newFloor.floorLoot = (rndInt((fLOOT * 2), fLOOT) * newFloor.floorModifier);		  // Specify Prize for beating Floor
	newFloor.isStore = rng(4);

	return newFloor;
}

// Function to fill Person arrays and Enemies vector with Enemy data
// Accepts no parameters if called with 0 parameters,
// otherwise, accepts 1 int parameter for total Enemy count.
// and accepts 1 string parameter for game Enemies file. Format: ("file.txt")
// Returns void, passes data by member access
Game::Person Game::gameAddEnemy(int i)
{
	// Create new Enemy with Default items
	Weapon noWeapon;					  // Initialize Default Weapon for Enemy
	Armor noArmor;						  // Initialize Default Armor for Enemy
	Person newEnemy;					  // Initialize new Person for storing Enemy data
	newEnemy.Weapons.push_back(noWeapon); // Add noWeapon to Enemy Weapons vector
	newEnemy.Armors.push_back(noArmor);	  // Add noArmor to Enemy Armors vector

	// Generate Enemy data
	newEnemy.personIndex = i;								  // Specify Index of Enemy
	newEnemy.personNumber = enemyCount;						  // Specify Number of Enemy
	newEnemy.personName = ("Enemy " + to_string(enemyCount)); // Specify Default Name of Enemies
	newEnemy.personMoney = rndInt((eLOOT * 2), eLOOT);		  // Specify Prize for killing Enemy

	// Generate random Enemy items
	newEnemy.personWeapon = 0; // Specify Weapon of Enemy
	newEnemy.personArmor = 0;  // Specify Armor of Enemy

	// Fill rngArray for RNG
	for (int i = 0; i < rngASIZE; ++i)
	{
		newEnemy.rngArray[i] = (i + 1);
	}

	// Fill choiceArray for Random Choices
	for (int i = 0; i < rngASIZE; ++i)
	{
		newEnemy.choiceArray[i] = rndInt(rngESIZE);
	}

	return newEnemy;
}

// Function to fill Person arrays and Players vector with Player data
// Accepts no parameters if called with 0 parameters,
// otherwise, accepts 1 int parameter for total player count.
// and accepts 1 string parameter for game Players file. Format: ("file.txt")
// Returns void, passes data by member access
Game::Person Game::gameAddPlayer(int i)
{
	// Create new Player with Default items
	Weapon noWeapon;					   // Initialize Default Weapon for Player
	Armor noArmor;						   // Initialize Default Armor for Player
	Person newPlayer;					   // Initialize new Person for storing Player data
	newPlayer.Weapons.push_back(noWeapon); // Add noWeapon to Player Weapons vector
	newPlayer.Armors.push_back(noArmor);   // Add noArmor to Player Armors vector

	// Generate Player data
	newPlayer.isPlayer = true;									 // Specify Person is Player
	newPlayer.personIndex = i;									 // Specify Index of Player
	newPlayer.personNumber = playerCount;						 // Specify Number of Player
	newPlayer.personName = ("Player " + to_string(playerCount)); // Specify Default Name of Player
	if (playerTotal == -1)										 // -1 For TESTING, Set Back to 1
	{
		cout << "Please Enter a Name: ";
		userString = gameChoiceString();
		cout << endl;
		newPlayer.personName = userString; // Ask Player to enter Name
	}

	// Generate Player items
	newPlayer.personWeapon = 0; // Specify Weapon of Player
	newPlayer.personArmor = 0;	// Specify Armor of Player

	// Fill rngArray for RNG
	for (int i = 0; i < rngASIZE; ++i)
	{
		newPlayer.rngArray[i] = (i + 1);
	}

	// Fill choiceArray for Random Choices
	for (int i = 0; i < rngASIZE; ++i)
	{
		newPlayer.choiceArray[i] = rndInt(rngESIZE);
	}

	return newPlayer;
}

// Function to display game progress
// Accepts no parameters
// Returns void, passes data by member access
void Game::gameProgress()
{
	// Clear terminal to display progress
	// system("CLS");

	// Display Health
	cout << "Player Health: " << Players.at(playerCurrent).personHealth << endl;
	cout << "Enemy Health: " << Floors.at(floorCurrent).Enemies.at(enemyCurrent).personHealth << endl
		 << endl;

	// Excute Combat Turns
	if (Players.at(playerCurrent) >= Floors.at(floorCurrent).Enemies.at(enemyCurrent))
	{
		cout << "Player Wins." << endl
			 << endl;
		Players.at(playerCurrent) += Floors.at(floorCurrent).Enemies.at(enemyCurrent);
	}
	else if (Players.at(playerCurrent) <= Floors.at(floorCurrent).Enemies.at(enemyCurrent))
	{
		cout << "Player Loses." << endl
			 << endl;
		Players.at(playerCurrent) -= Floors.at(floorCurrent).Enemies.at(enemyCurrent);
	}
	else if (Players.at(playerCurrent) == Floors.at(floorCurrent).Enemies.at(enemyCurrent))
	{
		cout << "Round Tie." << endl
			 << endl;
	}
	else
	{
		cout << "Round Failed." << endl
			 << endl;
	}

	// Display Health
	cout << "Player Health: " << Players.at(playerCurrent).personHealth << endl;
	cout << "Enemy Health: " << Floors.at(floorCurrent).Enemies.at(enemyCurrent).personHealth << endl
		 << endl;

	// Display floor progress
	cout << setw(16) << left << "Current Floor:"
		 << setw(5) << left << (floorCurrent + 1)
		 << setw(2) << left << ' '
		 << setw(18) << left << "Floors Remaining:"
		 << setw(5) << left << (floorTotal - (floorCurrent + 1)) << endl;
	for (int i = 0; i < floorCurrent; ++i)
	{
		cout << "[ ] ";
	}
	cout << " [ x ]  ";
	for (int i = 0; i < (floorTotal - (floorCurrent + 1)); ++i)
	{
		cout << "[ ] ";
	}
	cout << endl
		 << endl;

	// Display health and money
	cout << setw(16) << left << "Player Health:"
		 << setw(5) << left << Players.at(playerCurrent).personHealth
		 << setw(2) << left << ' '
		 << setw(17) << left << "Enemy Health:"
		 << setw(5) << left << Floors.at(floorCurrent).Enemies.at(enemyCurrent).personHealth << endl
		 << setw(16) << left << "Player Stamina:"
		 << setw(5) << left << Players.at(playerCurrent).personStamina
		 << setw(2) << left << ' '
		 << setw(17) << left << "Enemy Stamina:"
		 << setw(5) << left << Floors.at(floorCurrent).Enemies.at(enemyCurrent).personStamina << endl
		 << setw(16) << left << "Player Money:"
		 << setw(5) << left << Players.at(playerCurrent).personMoney
		 << setw(2) << left << ' '
		 << setw(17) << left << "Combat Round:"
		 << setw(5) << left << (floorRound + 1) << endl
		 << endl;

	// Display Player and Enemy chosen options
	if (floorRound > 0)
	{
		switch (playerChoice) // Display Players's choice of action for turn
		{
		case 1:
			cout << "Player's Choice: Attack" << endl;
			break;
		case 2:
			cout << "Player's Choice: Block" << endl;
			break;
		case 3:
			cout << "Player's Choice: Dodge" << endl;
			break;
		case 4:
			cout << "Player's Choice: Wait" << endl;
			break;
		default:
			// Error Message
			cout << "Player's Choice: Invalid (gameProgress())" << endl
				 << endl;
			break;
		}

		switch (enemyChoice) // Display Enemy's choice of action for turn
		{
		case 1:
			cout << "Enemy's Choice: Attack" << endl
				 << endl;
			break;
		case 2:
			cout << "Enemy's Choice: Block" << endl
				 << endl;
			break;
		case 3:
			cout << "Enemy's Choice: Dodge" << endl
				 << endl;
			break;
		case 4:
			cout << "Enemy's Choice: Wait" << endl
				 << endl;
			break;
		default:
			// Error Message
			cout << "Enemy's Choice: Invalid" << endl
				 << endl;
			break;
		}
	}

	// Excute Enemy combat turns
	if (Floors.at(floorCurrent).Enemies.at(enemyCurrent).isAttacking == true)
	{
		enemyAttackShow(); // Execute enemy Attack;
	}
	else if (Floors.at(floorCurrent).Enemies.at(enemyCurrent).isBlocking == true)
	{
		enemyBlockShow(); // Execute enemy Block;
	}
	else if (Floors.at(floorCurrent).Enemies.at(enemyCurrent).isDodging == true)
	{
		enemyDodgeShow(); // Execute enemy Dodge;
	}
	else if (Floors.at(floorCurrent).Enemies.at(enemyCurrent).isWaiting == true)
	{
		enemyWaitShow(); // Execute enemy Wait;
	}

	// Excute Player combat turns
	if (Players.at(playerCurrent).isAttacking == true)
	{
		turnAttackShow(); // Execute user Attack;
	}
	else if (Players.at(playerCurrent).isBlocking == true)
	{
		turnBlockShow(); // Execute user Block;
	}
	else if (Players.at(playerCurrent).isDodging == true)
	{
		turnDodgeShow(); // Execute user Dodge;
	}
	else if (Players.at(playerCurrent).isWaiting == true)
	{
		turnWaitShow(); // Execute user Wait;
	}

	return;
}

// Function to Display Game Ui
// Accepts 5 Int Parameters for adjusting output of Ui Lines
// Returns Void
void Game::gameUi(int uMENU, int uPAGE, int uLINETOTAL, int sLINEMIN, int sLINEMAX)
{
	// Initialize Variable(s) for gameUi()
	int // Initialize Int(s) for storing User Int(s)
		userInt = 0,
		uiHud = 4,
		uiChoices = 3,
		uiCombat = 2,
		uiOptions = 2;
	double userDouble = 0; // Initialize Double(s) for storing User Double(s)
	bool				   // Initialize Bool(s) for storing Bool(s)
		isUi = false,
		isDone = false;

	// Set Settings Values
	uiLinesNumbers[1][0] = (floorCurrent + 1);
	uiLinesNumbers[1][1] = (floorRound + 1);
	uiLinesNumbers[2][0] = Players.at(playerCurrent).personHealth;
	uiLinesNumbers[2][1] = Floors.at(floorCurrent).Enemies.at(enemyCurrent).personHealth;
	uiLinesNumbers[3][0] = Players.at(playerCurrent).personStamina;
	uiLinesNumbers[3][1] = Floors.at(floorCurrent).Enemies.at(enemyCurrent).personStamina;
	uiLinesNumbers[4][0] = Players.at(playerCurrent).personMoney;
	uiLinesNumbers[4][1] = (enemyTotal - enemyCurrent);

	// Find uMENU in uiLines[i][0][0]
	for (int i = 0; !(isUi) && i < uMENUS; ++i)
	{
		// If Ui Index is found, Correct uMENU with Ui Index
		if (stoi(uiLines[i][0][0]) == uMENU)
		{
			// Correct uMENU with Ui Page Index
			uMENU = i + (uPAGE - 1);
			isUi = true;
		}
	}

	// Set Any uiLinesSelected[sLINE][0] == true
	for (int sLINE = sLINEMIN; sLINE < (sLINEMIN + sLINEMAX); ++sLINE)
	{
		uiLinesSelected[sLINE][0] = true;
	}

	// Clear Terminal to Display Game Ui
	system("CLS");

	// Display Game Ui HUD Line 1 - 4
	for (int uLINE = 1; uLINE < uiHud; ++uLINE)
	{
		// cout uiLines[uMENU][uLINE] lineLeft, then uiLines[uMENU][uLINE] lineRight, Centered to setw(40)
		cout << left << setw(40) << (uiLines[uMENU][uLINE][1] + to_string(uiLinesNumbers[uLINE][0]))
			 << right << setw(40) << (to_string(uiLinesNumbers[uLINE][1]) + uiLines[uMENU][uLINE][2]);

		// cout New Line
		cout << endl;
	}

	// Display Game Ui Combat Display Line 5 - 7
	for (int uLINE = 5; uLINE < uiChoices; ++uLINE)
	{
		// cout uiLines[uMENU][uLINE] lineLeft, then uiLines[uMENU][uLINE] lineRight, Centered to setw(40)
		cout << right << setw(40) << (uiLines[uMENU][uLINE][1] + to_string(uiLinesNumbers[uLINE][0]))
			 << left << setw(40) << (uiLines[uMENU][uLINE][2] + to_string(uiLinesNumbers[uLINE][1]));

		// If Line Has Value, cout Value Message
		if (uiLinesNumbers[uLINE][0] >= 0)
		{
			cout << uiLinesNumbers[uLINE][0];
		}

		// cout uiLines[uMENU][uLINE] lineRight
		cout << uiLines[uMENU][uLINE][2];

		// If Line is Selected, cout Selected Message
		if (uiLinesSelected[uLINE][0] == true)
		{
			cout << uiLines[uMENU][0][3];
		}

		// cout New Line
		cout << endl;
	}

	// Display Game Ui Recap Line 8 - 9
	for (int uLINE = 8; uLINE < uiCombat; ++uLINE)
	{
		// cout uiLines[uMENU][uLINE] lineLeft, then uiLines[uMENU][uLINE] lineRight, Centered to setw(40)
		cout << right << setw(40) << (uiLines[uMENU][uLINE][1] + to_string(uiLinesNumbers[uLINE][0]))
			 << left << setw(40) << (uiLines[uMENU][uLINE][2] + to_string(uiLinesNumbers[uLINE][1]));

		// cout New Line
		cout << endl;
	}

	// Display Game Ui Choices Line 10 - 11
	for (int uLINE = 10; uLINE < uLINES; ++uLINE)
	{
		// cout uiLines[uMENU][uLINE] lineLeft, then uiLines[uMENU][uLINE] lineRight, Centered to setw(40)
		cout << right << setw(40) << uiLines[uMENU][uLINE][1]
			 << left << uiLines[uMENU][uLINE][2];

		// cout New Line for All Lines, Except Last Line
		if (uLINE <= (uiOptions - 1))
		{
			cout << endl;
		}
	}

	// Return Void
	return;
}

// Function to Engage in Combat
// Accepts no Parameters
// Returns Void
void Game::gameCombat()
{
	// Initialize Variable(s) for gameSettings()
	int userInt = 0;	   // Initialize Int(s) for storing User Int(s)
	double userDouble = 0; // Initialize Double(s) for storing User Double(s)
	bool isDone = false;   // Initialize Bool(s) for storing Bool(s)

	// Display New Floor Intro
	gameFloorIntro();

	// Take User's Choice with gameChoiceInt() while isDone != true;
	do
	{
		// If User is Editing, Display Settings Menu Page 2
		if (uiLinesSelected[4][0] == true || uiLinesSelected[5][0] == true || uiLinesSelected[6][0] == true || uiLinesSelected[7][0] == true)
		{
			// Display Settings Menu Page 2
			gameUi(1);
		}

		// If User is Not Editing a Setting, Display Settings Menu Page 1
		else
		{
			// Display Settings Menu Page 1
			gameUi(1);
		}

		// Check if User is Editing floorDifficulty
		if (uiLinesSelected[4][0] == true)
		{
			// Take User Choice of any Number
			floorDifficulty = gameChoiceInt(1, 4);
			uiLinesNumbers[4][0] = floorDifficulty;
			uiLinesSelected[4][0] = false;
		}

		// Check if User is Editing floorTotal
		else if (uiLinesSelected[5][0] == true)
		{
			// Take User Choice of any Number
			floorTotal = gameChoiceInt(1, 4);
			uiLinesNumbers[5][0] = floorTotal;
			uiLinesSelected[5][0] = false;
		}

		// Check if User is Editing enemyTotal
		else if (uiLinesSelected[6][0] == true)
		{
			// Take User Choice of any Number
			enemyTotal = gameChoiceInt(1, 4);
			uiLinesNumbers[6][0] = enemyTotal;
			uiLinesSelected[6][0] = false;
		}

		// Check if User is Editing playerTotal
		else if (uiLinesSelected[7][0] == true)
		{
			// Take User Choice of any Number
			playerTotal = gameChoiceInt(1, 4);
			uiLinesNumbers[7][0] = playerTotal;
			uiLinesSelected[7][0] = false;
		}

		// If User is Not Editing Settings, Display Ui 1
		else
		{
			// Take User Choice of (1 - 5)
			userInt = gameChoiceInt(1, 5);

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

	// Fill uiLinesNumbers Array Lines with (-1)
	for (int uLINE = 0; uLINE < uLINES; ++uLINE)
	{
		// Fill uiLinesNumbers Array Columns with (-1)
		for (int uCOL = 0; uCOL < uCOLS; ++uCOL)
		{
			uiLinesNumbers[uLINE][uCOL] = (-1);
		}
	}

	// Return Void
	return;
}

// Function to execute Person Attack
// Accepts no parameters
// Returns void, passes data by member access
void Game::gameCombats()
{
	for (int i = 0; i < enemyTotal; ++i)
	{
		do
		{
			// Progress Combat and Excute combat choices
			gamePlayerTurn(playerChoice, enemyChoice);
			gameEnemyTurn();

			// Move to next round
			++floorRound;

			// Stamina Recovery System
			gameStaminaRecovery();
		} while (Floors.at(floorCurrent).Enemies.at(enemyCurrent).personHealth > 0 && Players.at(playerCurrent).personHealth > 0);
		++enemyCurrent;
	}
	// Display Progress after Combat
	// gameProgress();

	if (Players.at(playerCurrent).personHealth > 0)
	{
		bool storeUse = false;
		bool floorNext = false;

		// Victory message
		cout << "You have killed " << Floors.at(floorCurrent).Enemies.at(enemyCurrent).personName << ", congrats." << endl
			 << endl;
		playerWealth += Floors.at(floorCurrent).Enemies.at(enemyCurrent).personMoney;
		Players.at(playerCurrent) += Floors.at(floorCurrent).Enemies.at(enemyCurrent);
		++playerKills;

		// Display Progress after Combat
		// gameProgress();

		// Ask user to use store is present
		if (Floors.at(floorCurrent).isStore == true)
		{
			cout << "Do you want to use the Store to buy and sell items? (0 = No, 1 = Yes): ";
			cin >> storeUse;
			cout << "Player's Choice: " << storeUse << endl
				 << endl;
			if (storeUse == 1)
			{
				// gameStore();
				cout << "gameStore(). (Took Enemy Items)" << endl
					 << endl;
				playerWealth -= Floors.at(floorCurrent).Enemies.at(enemyCurrent).personMoney;
			}
			else
			{
				cout << "You can no longer access the Store. (No Items Taken)" << endl
					 << endl;
			}
		}

		// Ask user to advance to the next floor
		do
		{
			cout << "Are you ready to advance to the next Floor? (1 = Yes): ";
			cin >> floorNext;
			cout << "Player's Choice: " << floorNext << endl
				 << endl;
			if (floorNext == 1)
			{
				Players.at(playerCurrent).personStamina = sMAX;
				playerWealth += Floors.at(floorCurrent).floorLoot;
				Players.at(playerCurrent).personMoney += Floors.at(floorCurrent).floorLoot;
				++floorCurrent;
				floorRound = 0;
				gameFloorIntro();
			}
			else
			{
				cout << "Please press 1 to advance to the next Floor" << endl;
			}
		} while (floorNext != 1);
	}
	else
	{
		cout << "You have died. Thats unfortunate." << endl
			 << endl
			 << "You killed " << playerKills
			 << " enemies and earned a total of " << playerWealth << " money." << endl
			 << endl;
	}
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

// Function to Take Player's Turn
// Accepts no Parameters
// Returns Void, Passes Data by Member Access
void Game::gamePlayerTurn(int uMENU, int uPAGE)
{
	// Initialize Variable(s) for gamePlayerTurn()
	int userInt = 0;	   // Initialize Int(s) for storing User Int(s)
	double userDouble = 0; // Initialize Double(s) for storing User Double(s)
	bool isDone = false;   // Initialize Bool(s) for storing Bool(s)

	// Reset Player
	// playerChoice = 0;
	Players.at(playerCurrent).isRecovering = true;
	Players.at(playerCurrent).isAttacking = false;
	Players.at(playerCurrent).isBlocking = false;
	Players.at(playerCurrent).isDodging = false;
	Players.at(playerCurrent).isWaiting = false;

	// Take User's Choice with gameChoiceInt() while isDone != true;
	do
	{
		// Display Game Ui
		gameUi(1);

		// Take User Choice of (1 - 4)
		userInt = gameChoiceInt(uMENU, uPAGE);

		// Check User Choice
		switch (userInt)
		{
		case 1: // If User Choice is 1, Attack
			// If User has enough Stamina, Attack
			if (Players.at(playerCurrent).personStamina >= aCOST)
			{
				Players.at(playerCurrent).personStamina -= aCOST;
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
				Players.at(playerCurrent).personStamina -= dCOST;
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

	// Return Void
	return;
}

// Function to Take Enemy's Turn
// Accepts no Parameters
// Returns Void, Passes Data by Member Access
void Game::gameEnemyTurn()
{
	// Initialize Variable(s) for gameEnemyTurn()
	int enemyInt = 0;	 // Initialize Int(s) for storing User Int(s)
	bool isDone = false; // Initialize Bool(s) for storing Bool(s)

	// Reset Enemy
	// enemyChoice = 0;
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
				Floors.at(floorCurrent).Enemies.at(enemyCurrent).personStamina -= aCOST;
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
				Floors.at(floorCurrent).Enemies.at(enemyCurrent).personStamina -= dCOST;
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

// Function to Decide Choices for Enemy's Turn
// Accepts no Parameters
// Returns Void, Passes Data by Member Access
int Game::gameEnemyAi()
{
	// Initialize Variable(s) for gameEnemyAi()
	int enemyInt = 0;	 // Initialize Int(s) for storing User Int(s)
	bool isDone = false; // Initialize Bool(s) for storing Bool(s)

	// Take Enemy's Choice while isDone != true;
	do
	{
		//
		if (Floors.at(floorCurrent).Enemies.at(enemyCurrent).personStamina >= dCOST)
		{
			//
			if (Players.at(playerCurrent).personStamina < aCOST)
			{
				enemyInt = 1;
			}

			//
			else if (Players.at(playerCurrent).personStamina <= bCOST)
			{
				bool choice1 = rng(rndInt(4)); // Default 3
				//
				if (choice1 == true)
				{
					enemyInt = 1;
				}

				//
				else
				{
					enemyInt = 3;
				}
			}

			//
			else if (Players.at(playerCurrent).personStamina < dCOST)
			{
				bool choice2 = rng(rndInt(4)); // Default 3
				//
				if (choice2 == true)
				{
					enemyInt = 3;
				}

				//
				else
				{
					enemyInt = 1;
				}
			}

			//
			else
			{
				int choice3 = rndInt((rngASIZE - 1), 0);
				enemyInt = Floors.at(floorCurrent).Enemies.at(enemyCurrent).choiceArray[choice3];
			}
		}

		//
		else if (Floors.at(floorCurrent).Enemies.at(enemyCurrent).personStamina > bCOST)
		{
			//
			if (Players.at(playerCurrent).personStamina < aCOST)
			{
				enemyInt = 1;
			}

			//
			else if (Players.at(playerCurrent).personStamina <= bCOST)
			{
				bool choice4 = rng(rndInt(4)); // Default 3
				//
				if (choice4 == true)
				{
					enemyInt = 1;
				}

				//
				else
				{
					enemyChoice = 2;
				}
			}

			//
			else if (Players.at(playerCurrent).personStamina < dCOST)
			{
				bool choice5 = rng(rndInt(4)); // Default 3
				//
				if (choice5 == true)
				{
					enemyInt = 2;
				}

				//
				else
				{
					enemyInt = 1;
				}
			}

			//
			else
			{
				bool choice6 = rng(rndInt(4)); // Default 3
				//
				if (choice6 == true)
				{
					enemyInt = 1;
				}

				//
				else
				{
					enemyInt = 2;
				}
			}
		}

		//
		else if (Floors.at(floorCurrent).Enemies.at(enemyCurrent).personStamina >= aCOST)
		{
			//
			if (Players.at(playerCurrent).personStamina >= dCOST)
			{
				bool choice7 = rng(rndInt(4)); // Default 3
				//
				if (choice7 == true)
				{
					enemyInt = 2;
				}

				//
				else
				{
					enemyInt = 1;
				}
			}

			//
			else
			{
				enemyInt = 1;
			}
		}

		//
		else
		{
			enemyInt = 4;
		}

		// End for Testing
		isDone = true;
	} while (isDone != true);

	// Return Enemy's Choice as Int
	return enemyInt;
}

//// Function to execute Person Attack
//// Accepts no parameters
//// Returns void, passes data by member access
// void Game::turnAttack()
//{
//	if (Floors.at(floorCurrent).Enemies.at(enemyCurrent).isAttacking == true)
//	{
//		if (Players.at(playerCurrent).personHealth - (Floors.at(floorCurrent).Enemies.at(enemyCurrent).Weapons.at(Floors.at(floorCurrent).Enemies.at(enemyCurrent).personWeapon).weaponDamage - Players.at(playerCurrent).Armors.at(Players.at(playerCurrent).personArmor).armorDefense) <= 0)
//		{
//			Players.at(playerCurrent).personHealth = 0;
//		}
//		else
//		{
//			Players.at(playerCurrent).personHealth -= (Floors.at(floorCurrent).Enemies.at(enemyCurrent).Weapons.at(Floors.at(floorCurrent).Enemies.at(enemyCurrent).personWeapon).weaponDamage - Players.at(playerCurrent).Armors.at(Players.at(playerCurrent).personArmor).armorDefense);
//		}
//	}
//	if (Floors.at(floorCurrent).Enemies.at(enemyCurrent).isDodging == true)
//	{
//		if (Players.at(playerCurrent).personHealth - (Floors.at(floorCurrent).Enemies.at(enemyCurrent).Weapons.at(Floors.at(floorCurrent).Enemies.at(enemyCurrent).personWeapon).weaponDamage - Players.at(playerCurrent).Armors.at(Players.at(playerCurrent).personArmor).armorDefense) <= 0)
//		{
//			Players.at(playerCurrent).personHealth = 0;
//		}
//		else
//		{
//			Players.at(playerCurrent).personHealth -= (Floors.at(floorCurrent).Enemies.at(enemyCurrent).Weapons.at(Floors.at(floorCurrent).Enemies.at(enemyCurrent).personWeapon).weaponDamage - Players.at(playerCurrent).Armors.at(Players.at(playerCurrent).personArmor).armorDefense);
//		}
//	}
//	return;
// }
//
//// Function to execute Person Block
//// Accepts no parameters
//// Returns void, passes data by member access
// void Game::turnBlock()
//{
//	if (Floors.at(floorCurrent).Enemies.at(enemyCurrent).isAttacking == true)
//	{
//		if (Players.at(playerCurrent).personHealth - ((Floors.at(floorCurrent).Enemies.at(enemyCurrent).Weapons.at(Floors.at(floorCurrent).Enemies.at(enemyCurrent).personWeapon).weaponDamage - Players.at(playerCurrent).Armors.at(Players.at(playerCurrent).personArmor).armorDefense) / bBUFF) <= 0)
//		{
//			Players.at(playerCurrent).personHealth = 0;
//		}
//		else
//		{
//			Players.at(playerCurrent).personHealth -= ((Floors.at(floorCurrent).Enemies.at(enemyCurrent).Weapons.at(Floors.at(floorCurrent).Enemies.at(enemyCurrent).personWeapon).weaponDamage - Players.at(playerCurrent).Armors.at(Players.at(playerCurrent).personArmor).armorDefense) / bBUFF);
//			if ((Players.at(playerCurrent).personStamina - bCOST) <= 0)
//			{
//				Players.at(playerCurrent).personStamina = 0;
//				Players.at(playerCurrent).personHealth -= (Floors.at(floorCurrent).Enemies.at(enemyCurrent).Weapons.at(Floors.at(floorCurrent).Enemies.at(enemyCurrent).personWeapon).weaponDamage - Players.at(playerCurrent).Armors.at(Players.at(playerCurrent).personArmor).armorDefense);
//			}
//			else
//			{
//				Players.at(playerCurrent).personStamina -= bCOST;
//			}
//		}
//	}
//	return;
// }
//
//// Function to execute Person Dodge
//// Accepts no parameters
//// Returns void, passes data by member access
// void Game::turnDodge()
//{
//	if (Floors.at(floorCurrent).Enemies.at(enemyCurrent).isBlocking == true)
//	{
//		if (Players.at(playerCurrent).personHealth - (Floors.at(floorCurrent).Enemies.at(enemyCurrent).Weapons.at(Floors.at(floorCurrent).Enemies.at(enemyCurrent).personWeapon).weaponDamage - Players.at(playerCurrent).Armors.at(Players.at(playerCurrent).personArmor).armorDefense) <= 0)
//		{
//			Players.at(playerCurrent).personHealth = 0;
//		}
//		else
//		{
//			Players.at(playerCurrent).personHealth -= (Floors.at(floorCurrent).Enemies.at(enemyCurrent).Weapons.at(Floors.at(floorCurrent).Enemies.at(enemyCurrent).personWeapon).weaponDamage - Players.at(playerCurrent).Armors.at(Players.at(playerCurrent).personArmor).armorDefense);
//		}
//	}
//	return;
// }
//
//// Function to execute Person Wait
//// Accepts no parameters
//// Returns void, passes data by member access
// void Game::turnWait()
//{
//	if (Floors.at(floorCurrent).Enemies.at(enemyCurrent).isAttacking == true)
//	{
//		if (Players.at(playerCurrent).personHealth - (Floors.at(floorCurrent).Enemies.at(enemyCurrent).Weapons.at(Floors.at(floorCurrent).Enemies.at(enemyCurrent).personWeapon).weaponDamage - Players.at(playerCurrent).Armors.at(Players.at(playerCurrent).personArmor).armorDefense) <= 0)
//		{
//			Players.at(playerCurrent).personHealth = 0;
//		}
//		else
//		{
//			Players.at(playerCurrent).personHealth -= (Floors.at(floorCurrent).Enemies.at(enemyCurrent).Weapons.at(Floors.at(floorCurrent).Enemies.at(enemyCurrent).personWeapon).weaponDamage - Players.at(playerCurrent).Armors.at(Players.at(playerCurrent).personArmor).armorDefense);
//		}
//	}
//	return;
// }
//
//// Function to execute Person Attack
// Accepts no parameters
// Returns void, passes data by member access
void Game::turnRun()
{
	if (floorRound == 0)
	{
		// gameNewFloor(); // Execute turnRun
		cout << "gameNewFloor()" << endl
			 << endl;
	}
	else
	{
		cout << "It's too late. You made your choice." << endl
			 << endl;
	}
	return;
}

// Function to execute Person Attack
// Accepts no parameters
// Returns void, passes data by member access
void Game::turnExitGame()
{
	if (Floors.at(floorCurrent).Enemies.at(enemyCurrent).personStamina >= dCOST)
	{
		// turnExitGame(); // Execute turnRun
		cout << "turnExitGame()" << endl
			 << endl;
	}
	else
	{
		cout << "Are you sure you want to exit the game?" << endl
			 << endl;
		cout << "Goodbye" << endl;
	}
	return;
}

//// Function to execute Person Attack
//// Accepts no parameters
//// Returns void, passes data by member access
// void Game::enemyAttack()
//{
//	if (Players.at(playerCurrent).isAttacking == true)
//	{
//		if (Floors.at(floorCurrent).Enemies.at(enemyCurrent).personHealth - (Players.at(playerCurrent).Weapons.at(Players.at(playerCurrent).personWeapon).weaponDamage - Floors.at(floorCurrent).Enemies.at(enemyCurrent).Armors.at(Floors.at(floorCurrent).Enemies.at(enemyCurrent).personArmor).armorDefense) <= 0)
//		{
//			Floors.at(floorCurrent).Enemies.at(enemyCurrent).personHealth = 0;
//		}
//		else
//		{
//			Floors.at(floorCurrent).Enemies.at(enemyCurrent).personHealth -= (Players.at(playerCurrent).Weapons.at(Players.at(playerCurrent).personWeapon).weaponDamage - Floors.at(floorCurrent).Enemies.at(enemyCurrent).Armors.at(Floors.at(floorCurrent).Enemies.at(enemyCurrent).personArmor).armorDefense);
//		}
//	}
//	if (Players.at(playerCurrent).isDodging == true)
//	{
//		if (Floors.at(floorCurrent).Enemies.at(enemyCurrent).personHealth - (Players.at(playerCurrent).Weapons.at(Players.at(playerCurrent).personWeapon).weaponDamage - Floors.at(floorCurrent).Enemies.at(enemyCurrent).Armors.at(Floors.at(floorCurrent).Enemies.at(enemyCurrent).personArmor).armorDefense) <= 0)
//		{
//			Floors.at(floorCurrent).Enemies.at(enemyCurrent).personHealth = 0;
//		}
//		else
//		{
//			Floors.at(floorCurrent).Enemies.at(enemyCurrent).personHealth -= (Players.at(playerCurrent).Weapons.at(Players.at(playerCurrent).personWeapon).weaponDamage - Floors.at(floorCurrent).Enemies.at(enemyCurrent).Armors.at(Floors.at(floorCurrent).Enemies.at(enemyCurrent).personArmor).armorDefense);
//		}
//	}
//	return;
// }
//
//// Function to execute Person Block
//// Accepts no parameters
//// Returns void, passes data by member access
// void Game::enemyBlock()
//{
//	if (Players.at(playerCurrent).isAttacking == true)
//	{
//		if (Floors.at(floorCurrent).Enemies.at(enemyCurrent).personHealth - ((Players.at(playerCurrent).Weapons.at(Players.at(playerCurrent).personWeapon).weaponDamage - Floors.at(floorCurrent).Enemies.at(enemyCurrent).Armors.at(Floors.at(floorCurrent).Enemies.at(enemyCurrent).personArmor).armorDefense) / bBUFF) <= 0)
//		{
//			Floors.at(floorCurrent).Enemies.at(enemyCurrent).personHealth = 0;
//		}
//		else
//		{
//			Floors.at(floorCurrent).Enemies.at(enemyCurrent).personHealth -= ((Players.at(playerCurrent).Weapons.at(Players.at(playerCurrent).personWeapon).weaponDamage - Floors.at(floorCurrent).Enemies.at(enemyCurrent).Armors.at(Floors.at(floorCurrent).Enemies.at(enemyCurrent).personArmor).armorDefense) / bBUFF);
//			if ((Floors.at(floorCurrent).Enemies.at(enemyCurrent).personStamina - bCOST) <= 0)
//			{
//				Floors.at(floorCurrent).Enemies.at(enemyCurrent).personStamina = 0;
//				Floors.at(floorCurrent).Enemies.at(enemyCurrent).personHealth -= (Players.at(playerCurrent).Weapons.at(Players.at(playerCurrent).personWeapon).weaponDamage - Floors.at(floorCurrent).Enemies.at(enemyCurrent).Armors.at(Floors.at(floorCurrent).Enemies.at(enemyCurrent).personArmor).armorDefense);
//			}
//			else
//			{
//				Floors.at(floorCurrent).Enemies.at(enemyCurrent).personStamina -= bCOST;
//			}
//		}
//	}
//	return;
// }
//
//// Function to execute Person Dodge
//// Accepts no parameters
//// Returns void, passes data by member access
// void Game::enemyDodge()
//{
//	if (Players.at(playerCurrent).isBlocking == true)
//	{
//		if (Floors.at(floorCurrent).Enemies.at(enemyCurrent).personHealth - (Players.at(playerCurrent).Weapons.at(Players.at(playerCurrent).personWeapon).weaponDamage - Floors.at(floorCurrent).Enemies.at(enemyCurrent).Armors.at(Floors.at(floorCurrent).Enemies.at(enemyCurrent).personArmor).armorDefense) <= 0)
//		{
//			Floors.at(floorCurrent).Enemies.at(enemyCurrent).personHealth = 0;
//		}
//		else
//		{
//			Floors.at(floorCurrent).Enemies.at(enemyCurrent).personHealth -= (Players.at(playerCurrent).Weapons.at(Players.at(playerCurrent).personWeapon).weaponDamage - Floors.at(floorCurrent).Enemies.at(enemyCurrent).Armors.at(Floors.at(floorCurrent).Enemies.at(enemyCurrent).personArmor).armorDefense);
//		}
//	}
//	return;
// }
//
//// Function to execute Person Wait
//// Accepts no parameters
//// Returns void, passes data by member access
// void Game::enemyWait()
//{
//	if (Players.at(playerCurrent).isAttacking == true)
//	{
//		if (Floors.at(floorCurrent).Enemies.at(enemyCurrent).personHealth - (Players.at(playerCurrent).Weapons.at(Players.at(playerCurrent).personWeapon).weaponDamage - Floors.at(floorCurrent).Enemies.at(enemyCurrent).Armors.at(Floors.at(floorCurrent).Enemies.at(enemyCurrent).personArmor).armorDefense) <= 0)
//		{
//			Floors.at(floorCurrent).Enemies.at(enemyCurrent).personHealth = 0;
//		}
//		else
//		{
//			Floors.at(floorCurrent).Enemies.at(enemyCurrent).personHealth -= (Players.at(playerCurrent).Weapons.at(Players.at(playerCurrent).personWeapon).weaponDamage - Floors.at(floorCurrent).Enemies.at(enemyCurrent).Armors.at(Floors.at(floorCurrent).Enemies.at(enemyCurrent).personArmor).armorDefense);
//		}
//	}
//	return;
// }

void Game::turnAttackShow()
{
	if (Floors.at(floorCurrent).Enemies.at(enemyCurrent).isAttacking == true)
	{
		cout << Floors.at(floorCurrent).Enemies.at(enemyCurrent).personName << " hit "
			 << Players.at(playerCurrent).personName << " at the same time for "
			 << (Floors.at(floorCurrent).Enemies.at(enemyCurrent).Weapons.at(Floors.at(floorCurrent).Enemies.at(enemyCurrent).personWeapon).weaponDamage - Players.at(playerCurrent).Armors.at(Players.at(playerCurrent).personArmor).armorDefense)
			 << " damage." << endl
			 << endl;
	}
	if (Floors.at(floorCurrent).Enemies.at(enemyCurrent).isDodging == true)
	{
		cout << Floors.at(floorCurrent).Enemies.at(enemyCurrent).personName << " dodged "
			 << Players.at(playerCurrent).personName << "'s attack and hit them after for "
			 << (Floors.at(floorCurrent).Enemies.at(enemyCurrent).Weapons.at(Floors.at(floorCurrent).Enemies.at(enemyCurrent).personWeapon).weaponDamage - Players.at(playerCurrent).Armors.at(Players.at(playerCurrent).personArmor).armorDefense)
			 << " damage." << endl
			 << endl;
	}
	return;
}

// Function to execute Person Block
// Accepts no parameters
// Returns void, passes data by member access
void Game::turnBlockShow()
{
	if (Floors.at(floorCurrent).Enemies.at(enemyCurrent).isAttacking == true)
	{
		if (Players.at(playerCurrent).personHealth - ((Floors.at(floorCurrent).Enemies.at(enemyCurrent).Weapons.at(Floors.at(floorCurrent).Enemies.at(enemyCurrent).personWeapon).weaponDamage - Players.at(playerCurrent).Armors.at(Players.at(playerCurrent).personArmor).armorDefense) / bBUFF) <= 0)
		{
			cout << Floors.at(floorCurrent).Enemies.at(enemyCurrent).personName << " hit "
				 << Players.at(playerCurrent).personName << "'s shield and damaged them for "
				 << ((Floors.at(floorCurrent).Enemies.at(enemyCurrent).Weapons.at(Floors.at(floorCurrent).Enemies.at(enemyCurrent).personWeapon).weaponDamage - Players.at(playerCurrent).Armors.at(Players.at(playerCurrent).personArmor).armorDefense) / bBUFF)
				 << " damage." << endl
				 << endl;
		}
		else
		{
			cout << Floors.at(floorCurrent).Enemies.at(enemyCurrent).personName << " hit "
				 << Players.at(playerCurrent).personName << "'s shield and damaged them for "
				 << ((Floors.at(floorCurrent).Enemies.at(enemyCurrent).Weapons.at(Floors.at(floorCurrent).Enemies.at(enemyCurrent).personWeapon).weaponDamage - Players.at(playerCurrent).Armors.at(Players.at(playerCurrent).personArmor).armorDefense) / bBUFF)
				 << " damage." << endl
				 << endl;
			if ((Players.at(playerCurrent).personStamina - bCOST) <= 0)
			{
				cout << Floors.at(floorCurrent).Enemies.at(enemyCurrent).personName << " stunned "
					 << Players.at(playerCurrent).personName << " and hit them again for "
					 << (Floors.at(floorCurrent).Enemies.at(enemyCurrent).Weapons.at(Floors.at(floorCurrent).Enemies.at(enemyCurrent).personWeapon).weaponDamage - Players.at(playerCurrent).Armors.at(Players.at(playerCurrent).personArmor).armorDefense)
					 << " damage." << endl
					 << endl;
			}
			else
			{
			}
		}
	}
	return;
}

// Function to execute Person Dodge
// Accepts no parameters
// Returns void, passes data by member access
void Game::turnDodgeShow()
{
	if (Floors.at(floorCurrent).Enemies.at(enemyCurrent).isBlocking == true)
	{
		cout << Floors.at(floorCurrent).Enemies.at(enemyCurrent).personName << " caught "
			 << Players.at(playerCurrent).personName << "'s dodge and hit them them after for "
			 << (Floors.at(floorCurrent).Enemies.at(enemyCurrent).Weapons.at(Floors.at(floorCurrent).Enemies.at(enemyCurrent).personWeapon).weaponDamage - Players.at(playerCurrent).Armors.at(Players.at(playerCurrent).personArmor).armorDefense)
			 << " damage." << endl
			 << endl;
	}
	return;
}

// Function to execute Person Wait
// Accepts no parameters
// Returns void, passes data by member access
void Game::turnWaitShow()
{
	if (Floors.at(floorCurrent).Enemies.at(enemyCurrent).isAttacking == true)
	{
		cout << Floors.at(floorCurrent).Enemies.at(enemyCurrent).personName << " attacked "
			 << Players.at(playerCurrent).personName << " while they hesitated and hit them for "
			 << (Floors.at(floorCurrent).Enemies.at(enemyCurrent).Weapons.at(Floors.at(floorCurrent).Enemies.at(enemyCurrent).personWeapon).weaponDamage - Players.at(playerCurrent).Armors.at(Players.at(playerCurrent).personArmor).armorDefense)
			 << " damage." << endl
			 << endl;
	}
	return;
}

// Function to execute Person Attack
// Accepts no parameters
// Returns void, passes data by member access
void Game::enemyAttackShow()
{
	if (Players.at(playerCurrent).isAttacking == true)
	{
		cout << Players.at(playerCurrent).personName << " hit "
			 << Floors.at(floorCurrent).Enemies.at(enemyCurrent).personName << " at the same time for "
			 << (Players.at(playerCurrent).Weapons.at(Players.at(playerCurrent).personWeapon).weaponDamage - Floors.at(floorCurrent).Enemies.at(enemyCurrent).Armors.at(Floors.at(floorCurrent).Enemies.at(enemyCurrent).personArmor).armorDefense)
			 << " damage." << endl
			 << endl;
	}
	if (Players.at(playerCurrent).isDodging == true)
	{
		cout << Players.at(playerCurrent).personName << " dodged "
			 << Floors.at(floorCurrent).Enemies.at(enemyCurrent).personName << "'s attack and hit them after for "
			 << (Players.at(playerCurrent).Weapons.at(Players.at(playerCurrent).personWeapon).weaponDamage - Floors.at(floorCurrent).Enemies.at(enemyCurrent).Armors.at(Floors.at(floorCurrent).Enemies.at(enemyCurrent).personArmor).armorDefense)
			 << " damage." << endl
			 << endl;
	}
	return;
}

// Function to execute Person Block
// Accepts no parameters
// Returns void, passes data by member access
void Game::enemyBlockShow()
{
	if (Players.at(playerCurrent).isAttacking == true)
	{
		if (Floors.at(floorCurrent).Enemies.at(enemyCurrent).personHealth - ((Players.at(playerCurrent).Weapons.at(Players.at(playerCurrent).personWeapon).weaponDamage - Floors.at(floorCurrent).Enemies.at(enemyCurrent).Armors.at(Floors.at(floorCurrent).Enemies.at(enemyCurrent).personArmor).armorDefense) / bBUFF) <= 0)
		{
			cout << Players.at(playerCurrent).personName << " hit "
				 << Floors.at(floorCurrent).Enemies.at(enemyCurrent).personName << "'s shield and damaged them for "
				 << ((Players.at(playerCurrent).Weapons.at(Players.at(playerCurrent).personWeapon).weaponDamage - Floors.at(floorCurrent).Enemies.at(enemyCurrent).Armors.at(Floors.at(floorCurrent).Enemies.at(enemyCurrent).personArmor).armorDefense) / bBUFF)
				 << " damage." << endl
				 << endl;
		}
		else
		{
			cout << Players.at(playerCurrent).personName << " hit "
				 << Floors.at(floorCurrent).Enemies.at(enemyCurrent).personName << "'s shield and damaged them for "
				 << ((Players.at(playerCurrent).Weapons.at(Players.at(playerCurrent).personWeapon).weaponDamage - Floors.at(floorCurrent).Enemies.at(enemyCurrent).Armors.at(Floors.at(floorCurrent).Enemies.at(enemyCurrent).personArmor).armorDefense) / bBUFF)
				 << " damage." << endl
				 << endl;
			if ((Floors.at(floorCurrent).Enemies.at(enemyCurrent).personStamina - bCOST) <= 0)
			{
				cout << Players.at(playerCurrent).personName << " stunned "
					 << Floors.at(floorCurrent).Enemies.at(enemyCurrent).personName << " and hit them again for "
					 << (Players.at(playerCurrent).Weapons.at(Players.at(playerCurrent).personWeapon).weaponDamage - Floors.at(floorCurrent).Enemies.at(enemyCurrent).Armors.at(Floors.at(floorCurrent).Enemies.at(enemyCurrent).personArmor).armorDefense)
					 << " damage." << endl
					 << endl;
			}
			else
			{
			}
		}
	}
	return;
}

// Function to execute Person Dodge
// Accepts no parameters
// Returns void, passes data by member access
void Game::enemyDodgeShow()
{
	if (Players.at(playerCurrent).isBlocking == true)
	{
		cout << Players.at(playerCurrent).personName << " caught "
			 << Floors.at(floorCurrent).Enemies.at(enemyCurrent).personName << "'s dodge and hit them them after for "
			 << (Players.at(playerCurrent).Weapons.at(Players.at(playerCurrent).personWeapon).weaponDamage - Floors.at(floorCurrent).Enemies.at(enemyCurrent).Armors.at(Floors.at(floorCurrent).Enemies.at(enemyCurrent).personArmor).armorDefense)
			 << " damage." << endl
			 << endl;
	}
	return;
}

// Function to execute Person Wait
// Accepts no parameters
// Returns void, passes data by member access
void Game::enemyWaitShow()
{
	if (Players.at(playerCurrent).isAttacking == true)
	{
		cout << Players.at(playerCurrent).personName << " attacked "
			 << Floors.at(floorCurrent).Enemies.at(enemyCurrent).personName << " while they hesitated and hit them for "
			 << (Players.at(playerCurrent).Weapons.at(Players.at(playerCurrent).personWeapon).weaponDamage - Floors.at(floorCurrent).Enemies.at(enemyCurrent).Armors.at(Floors.at(floorCurrent).Enemies.at(enemyCurrent).personArmor).armorDefense)
			 << " damage." << endl
			 << endl;
	}
	return;
}

/******************************************************************************
 *                                  GAME FUNCTIONS                            *
 ******************************************************************************/
