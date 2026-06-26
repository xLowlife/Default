/******************************************************************************
Ticket Noter

Donnie Gilbert
TEKsystems

Purpose of the program:
Generate notes to use for work tickets.

Specification Summary:
Read input from a .txt file,
Generate notes to use for work tickets in seperate .txt files.
*******************************************************************************/

/******************************************************************************
 *                           class Ticket Noter .cxx                          *
 ******************************************************************************/
#include "classTicketNoter.h"

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

	// Return Void
	return;
}

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

// Function to Display Game Menus
// Accepts 5 Int Parameters for adjusting output of Menu Lines
// Returns Void
void Game::gameMenu(int mMENU, int mPAGE, int mLINETOTAL, int sLINEMIN, int sLINEMAX)
{
	// Initialize Variable(s) for gameMenu()
	int userInt = 0;	   // Initialize Int(s) for storing User Int(s)
	double userDouble = 0; // Initialize Double(s) for storing User Double(s)
	bool				   // Initialize Bool(s) for storing Bool(s)
		isMenu = false,
		isDone = false;

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
			cout << menuLines[mMENU][0][3];
		}

		// cout New Line for All Lines, Except Last Line
		if (mLINE <= (mLINES - 2))
		{
			cout << endl;
		}
	}

	// Return Void
	return;
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
	// Open the file
	ifstream fileGame;
	fileGame.open(fileFloors);
	if (fileGame.is_open())
	{
		// Output File opened successfully to console
		cout << "File, " << fileFloors << ", opened successfully" << endl
			 << endl;

		//// Read the file and fill Floors label array
		// for (int i = 0; i < (gameITEMS - 1); ++i)
		//{
		//	getline(fileGame, weaponLabels[i], ',');
		// }
		// getline(fileGame, weaponLabels[-1]);

		// Close the file
		fileGame.close();

		// Create new Floor with Default items
		Floor newFloor; // Initialize Default Floor

		// Generate Floor data
		newFloor.floorDescription = ("Floor " + to_string(i + 1)); // Specify Default Description of Floors
		newFloor.floorNumber = i;								   // Specify Number of Floor

		// Generate random Floor data
		newFloor.floorLevel = (i + rndInt((3 + floorDifficulty), (0 + floorDifficulty))); // Specify Level of Floor
		newFloor.floorModifier = (1 + ((newFloor.floorLevel) / 10));					  // Specify Modifier of Floor
		newFloor.floorLoot = (rndInt((fLOOT * 2), fLOOT) * newFloor.floorModifier);		  // Specify Prize for beating Floor
		newFloor.isStore = rng(4);

		return newFloor;
	}
	else
	{
		// Output File failed to open to console
		cout
			<< "File, " << fileFloors << ", failed to open" << endl
			<< endl;

		// Return empty Floor
		Floor noFloor;
		return noFloor;
	}
}

// Function to fill Person arrays and Enemies vector with Enemy data
// Accepts no parameters if called with 0 parameters,
// otherwise, accepts 1 int parameter for total Enemy count.
// and accepts 1 string parameter for game Enemies file. Format: ("file.txt")
// Returns void, passes data by member access
Game::Person Game::gameAddEnemy(int i)
{
	// Open the file
	ifstream fileGame;
	fileGame.open(fileEnemies);
	if (fileGame.is_open())
	{
		// Output File opened successfully to console
		cout << "File, " << fileEnemies << ", opened successfully" << endl
			 << endl;

		// Close the file
		fileGame.close();

		// Create new Enemy with Default items
		Weapon noWeapon;					  // Initialize Default Weapon for Enemy
		Armor noArmor;						  // Initialize Default Armor for Enemy
		Person newEnemy;					  // Initialize new Person for storing Enemy data
		newEnemy.Weapons.push_back(noWeapon); // Add noWeapon to Enemy Weapons vector
		newEnemy.Armors.push_back(noArmor);	  // Add noArmor to Enemy Armors vector

		// Generate Enemy data
		newEnemy.personName = ("Enemy " + to_string(i + 1)); // Specify Default Name of Enemies
		newEnemy.personMoney = rndInt((eLOOT * 2), eLOOT);	 // Specify Prize for killing Enemy

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
	else
	{
		// Output File failed to open to console
		cout << "File, " << fileEnemies << ", failed to open" << endl
			 << endl;

		// Return empty Person
		Person noPerson;
		return noPerson;
	}
}

// Function to fill Person arrays and Players vector with Player data
// Accepts no parameters if called with 0 parameters,
// otherwise, accepts 1 int parameter for total player count.
// and accepts 1 string parameter for game Players file. Format: ("file.txt")
// Returns void, passes data by member access
Game::Person Game::gameAddPlayer(int i)
{
	// Open the file
	ifstream fileGame;
	fileGame.open(filePlayers);
	if (fileGame.is_open())
	{
		// Output File opened successfully to console
		cout << "File, " << filePlayers << ", opened successfully" << endl
			 << endl;

		// Close the file
		fileGame.close();

		// Create new Player with Default items
		Weapon noWeapon;					   // Initialize Default Weapon for Player
		Armor noArmor;						   // Initialize Default Armor for Player
		Person newPlayer;					   // Initialize new Person for storing Player data
		newPlayer.Weapons.push_back(noWeapon); // Add noWeapon to Player Weapons vector
		newPlayer.Armors.push_back(noArmor);   // Add noArmor to Player Armors vector

		// Generate Player data
		newPlayer.isPlayer = true;
		newPlayer.personName = ("Player " + to_string(i + 1)); // Specify Default Name of Player
		if (playerTotal == 1)
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
	else
	{
		// Output File failed to open to console
		cout << "File, " << filePlayers << ", failed to open" << endl
			 << endl;

		// Return empty Person
		Person noPerson;
		return noPerson;
	}
}

// Function to display Floor Intro
// Accepts no parameters
// Returns void, passes data by member access
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
		// Display Rules Menu
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
