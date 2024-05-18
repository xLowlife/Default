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
		// If userString.length() >= 1, Continue to Final Check
		if (userString.length() >= 1)
		{
			// If userString < choiceMin or userString > choiceMax, Final Check to Empty Variable(s)
			if (stod(userString) < choiceMin || stod(userString) > choiceMax)
			{
				isChoice = false;
			}
			// If userString is in Range, Return String as Double
			else
			{
				userDouble = stod(userString);
			}
		}
		// If userString.length() < 1, Empty Variable(s)
		else
		{
			isChoice = false;
		}
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

	// Open fileMenus
	dsFile.open(fileMenus);
	// If fileMenus did Open, Continue
	if (dsFile.is_open())
	{
		// Output fileMenus opened successfully to console
		cout << "File, " << fileMenus << ", opened successfully" << endl
			 << endl;

		// Initialize Strings(s) for storing String(s), In Order of getline Use Order
		string
			pageRows,	 // Specify sPage's Line Rows
			pageCols,	 // Specify sPage's Line Columns
			chapIndex,	 // Specify sChapter's Chapter Index
			pageIndex,	 // Specify sPage's Page Index
			pageMin,	 // Specify sPage's Min Choice
			pageMax,	 // Specify sPage's Max Choice
			isLastChap,	 // Specify if sChapter is Last in Screen
			isLastPage,	 // Specify if sPage is Last in Screen
			isLineEmpty, // Specify sLine's Empty State
			lineIndex,	 // Specify sLine's Line Index
			lineSel,	 // Specify sLine's Selection Number if sLine is Selectable
			lineInfo,	 // Specify sLine's Variable States
			lineString,	 // Specify sLine's Variable String
			lineTrash;	 // Specify Trash Variable

		// Fill New Chapter's Data and Vectors
		do
		{
			// Initialize New sChapter(s) for storing New Chapter Data
			sChapter newChapter;

			// Fill New Pages's Data and Vectors
			do
			{
				// Initialize New sPage(s) for storing New Page Data
				sPage newPage;

				// PAGE DIMENSIONS
				// Store New Page's Line Row Amount in pageRows
				getline(dsFile, pageRows, '-');
				// Specify New Page's Line Row Amount
				newPage.pageRows = stoi(pageRows);
				// Store New Page's Line Column Amount in pageCols
				getline(dsFile, pageCols, '-');
				// Specify New Page's Line Column Amount
				newPage.pageCols = stoi(pageCols);
				// Advance to Next Line in dsFile
				getline(dsFile, lineTrash);

				// PAGE INDEXES
				// Store New Chapter's Chapter Index in chapIndex
				getline(dsFile, chapIndex, ';');
				// Specify New Chapter's Chapter Index
				newChapter.chapIndex = stoi(chapIndex);
				// Store New Page's Page Index in chapIndex
				getline(dsFile, pageIndex, ';');
				// Specify New Page's Page Index
				newPage.pageIndex = stoi(pageIndex);

				// PAGE MIN CHOICES
				// Store New Page's Minimum User Choice in pageMin
				getline(dsFile, pageMin, ';');
				// If pageMin[0] == '+', Specify "Infinite" Positive Minimum User Choice
				if (pageMin[0] == '+')
				{
					newPage.pageMin = ((100 * 100) * (100 * 100));
				}
				// If pageMin[0] == '-', Specify "Infinite" Negative Minimum User Choice
				else if (pageMin[0] == '-')
				{
					newPage.pageMin = (((-100 * 100)) * (100 * 100));
				}
				// If pageMin == Number, Specify Minimum User Choice
				else
				{
					// Specify New Page's Minimum User Choice
					newPage.pageMin = stoi(pageMin);
				}

				// PAGE MAX CHOICES
				// Store New Page's Maximum User Choice in pageMax
				getline(dsFile, pageMax, ';');
				// If pageMax[0] == '+', Specify "Infinite" Positive Maximum User Choice
				if (pageMax[0] == '+')
				{
					newPage.pageMax = (1000 * 1000);
				}
				// If pageMax[0] == '-', Specify "Infinite" Negative Maximum User Choice
				else if (pageMax[0] == '-')
				{
					newPage.pageMax = ((-1000) * 1000);
				}
				// If pageMax[0] == Number, Specify Maximum User Choice
				else
				{
					// Specify New Page's Maximum User Choice
					newPage.pageMax = stoi(pageMax);
				}

				// PAGE INFO
				// Store Note of if New Chapter is Last in Screen
				getline(dsFile, isLastChap, ';');
				// Store Note of if New Page is Last in Screen
				getline(dsFile, isLastPage, ';');
				// Store New Chapter's Name in newChapter.chapName
				getline(dsFile, newChapter.chapName, ';');
				// Store New Page's Name in newPage.pageName
				getline(dsFile, newPage.pageName, ';');
				// Advance to Next Line in dsFile
				getline(dsFile, lineTrash);

				// PAGE LINES
				// Fill New Lines's Data and Vectors
				for (int pageRow = 0; pageRow < newPage.pageRows; ++pageRow)
				{
					// Initialize New sLine(s) for storing New Line Data
					sLine newLine;

					// LINE INFO
					// Store Note of if New Line is Empty
					getline(dsFile, isLineEmpty, ';');
					// Store New Line's Line Index in lineIndex
					getline(dsFile, lineIndex, ';');
					// Specify New Line's Line Index
					newLine.lineIndex = stoi(lineIndex);
					// Specify New Line's Name
					newLine.lineName.append(lineIndex);

					// LINE SELECTION
					// Store Note of if New Line can be Selected
					getline(dsFile, lineInfo, ';');
					// Specify New Line Column 0's Line Column Index
					newLine.sLineCols.at(0).lcolIndex = 0;
					// Specify New Line Column 0's String
					newLine.sLineCols.at(0).lStr = "Column 0";
					// If New Line CAN be Selected, Add Data on How to New Line's Vectors
					if (lineInfo[0] == '+')
					{
						// Specify New Line Column 0's Required User Choice as true
						newLine.sLineCols.at(0).lInfo = true;
						// Store New Line's Required Choice for Select in lineSel
						getline(dsFile, lineSel, ';');
						// Specify New Line Column 0's Required User Choice
						newLine.sLineCols.at(0).lNum = stoi(lineSel);
					}
					// If New Line CANNOT be Selected, Advance to Next Line Column
					else
					{
						// Advance to Next Line Column in dsFile
						getline(dsFile, lineTrash, ';');
						// If New Line is Line 0, Do NOT Trash String
						if (pageRow == 0)
						{
							// Specify New Page's Selected Message
							newPage.pageSel = lineTrash;
						}
					}

					// LINE COLUMNS
					// Fill New Lines's lSTRS Vector with String(s)
					for (int pageCol = 1; pageCol < (newPage.pageCols + 1); ++pageCol)
					{
						// Create New Line Column
						newLine.sLineNew();

						// Store Note of if New Lines's Line Column needs Input
						getline(dsFile, lineInfo, ';');
						// Specify New Line Column's Line Column Index
						newLine.sLineCols.at(newLine.sLineCols.size() - 1).lcolIndex = stoi(lineInfo.substr(1));
						// If New Lines's Line Column needs Input, Add true to newLine.sLineCols.at(-1).lInfo
						if (lineInfo[0] == '+')
						{
							// Specify New Line Column's Required User Choice as true
							newLine.sLineCols.at(newLine.sLineCols.size() - 1).lInfo = true;
						}

						// If New Line is NOT Marked Empty, Add String to newLine.lSTRS
						if (isLineEmpty[0] == '+')
						{
							// Store New Line's Line Column String in lineString
							getline(dsFile, lineString, ';');
							// If New Line's Line Column String is "sLine/", Split Next Line in Half
							if (lineString == "sLine/")
							{
								// Advance to Next Line Column in Loop
								++pageCol;
								// Store Note of if Next Line's Line Column needs Input
								getline(dsFile, lineInfo, ';');
								// Store Next Line's Line Column String in lineString
								getline(dsFile, lineString, ';');
								// Split Next Line in Half, and Add Both Halves to newLine.lSTRS
								(newLine / lineString);
								// Specify Next Line Column's Line Column Index
								newLine.sLineCols.at(newLine.sLineCols.size() - 1).lcolIndex = stoi(lineInfo.substr(1));
								// If Next Lines's Line Column needs Input, Add true to newLine.lINFO.at(pageCol)
								if (lineInfo[0] == '+')
								{
									// Specify New Line Column's Required User Choice as true
									newLine.sLineCols.at(newLine.sLineCols.size() - 1).lInfo = true;
								}
							}
							// If New Line's Line Column String is NOT "sLine/", Add Line Column String
							else
							{
								// Add New Line Column's String to newLine.sLineCols.at(-1).lStr
								newLine.sLineCols.at(newLine.sLineCols.size() - 1).lStr = lineString;
							}
						}
						// If New Line is Marked Empty, Trash All Strings
						else
						{
							// Advance to Next Line Column in dsFile
							getline(dsFile, lineTrash, ';');
						}
					}
					// Add New Line to New Page's newPage.sLines
					newPage.sLines.push_back(newLine);
					// Advance to Next Line in dsFile
					getline(dsFile, lineTrash);
				}
				// Add New Page to New Chapter's newChapter.sPages
				newChapter.sPages.push_back(newPage);
			} while (isLastPage[0] == '+');
			// Add New Chapter to screenMenu Vector
			screenMenu.push_back(newChapter);
		} while (isLastChap[0] == '+');
		// Close fileMenus
		dsFile.close();

		// Add Menu's Setting Screen Pointers for Line Column Pointers to Follow
		screenMenu.at(SETTINGS).chapPtrs.push_back(&floorDifficulty);
		screenMenu.at(SETTINGS).chapPtrs.push_back(&floorTotal);
		screenMenu.at(SETTINGS).chapPtrs.push_back(&enemyTotal);
		screenMenu.at(SETTINGS).chapPtrs.push_back(&playerTotal);

		// Add Menu's FLOOR INTRO Screen Pointers for Line Column Pointers to Follow
		screenMenu.at(FLOORINTRO).chapPtrs.push_back(&floorCurrent);

		// Make Menu Screen Page's Line Column Pointers Follow Pointers in Menu Screen's chapPtrs Vector
		for (int menuScreen = 0; menuScreen < screenMenu.size(); ++menuScreen)
		{ // Loop through Menu Screens
			for (int screenPage = 0; screenPage < screenMenu.at(menuScreen).sPages.size(); ++screenPage)
			{ // Loop through Menu Screen's Pages
				// Track which chapPtr in screenMenu.at(menuScreen).chapPtrs to Point to
				int chapPtrsAmount = 0;
				for (int pageLine = 1; chapPtrsAmount < screenMenu.at(menuScreen).chapPtrs.size() && pageLine < screenMenu.at(menuScreen).sPages.at(screenPage).sLines.size(); ++pageLine)
				{ // Loop through Menu Screen Page's Line Rows While chapPtrsAmount < screenMenu.at(menuScreen).chapPtrs.size()
					for (int LineCol = 1; LineCol < screenMenu.at(menuScreen).sPages.at(screenPage).sLines.at(pageLine).sLineCols.size(); ++LineCol)
					{ // Loop through Menu Screen Page's Line Columns
						// If Menu Screen Page's Line Column needs chapPtr, Point to it's chapPtr in screenMenu.at(menuScreen).chapPtrs
						if (screenMenu.at(menuScreen).sPages.at(screenPage).sLines.at(pageLine).sLineCols.at(LineCol).lInfo == true)
						{
							// Point to chapPtr in screenMenu.at(menuScreen).chapPtrs.at(chapPtrsAmount)
							screenMenu.at(menuScreen).sPages.at(screenPage).sLines.at(pageLine).sLineCols.at(LineCol).lNumPtr = screenMenu.at(menuScreen).chapPtrs.at(chapPtrsAmount);
							// Specify Next chapPtr in screenMenu.at(menuScreen).chapPtrs to Point to
							++chapPtrsAmount;
						}
					}
				}
			}
		}
	}

	// If fileMenus did Not Open, Error
	else
	{
		// Output fileMenus failed to open to console
		cout << "File, " << fileMenus << ", failed to open" << endl
			 << endl;
	}
	// Return Void
	return;
}

// Function to Write Game Files for Game Data
// Accepts 1 Parameter for File Name ("fileNew.txt")
// Returns Void, passes Data by Member Access
void Game::dsFileWrite(int chapIndex, int pageIndex, string dsWriteFileName)
{
	// Initialize Variable(s) for dsFileWrite()
	std::ofstream dsWriteFile(dsWriteFileName, std::ofstream::out); // Initialize ofstream(s) for storing ofstream(s)
	// Initialize String Vector for Menu Screen Page's Line Strings
	vector<string> lineStrings;

	// Open dsWriteFileName
	dsWriteFile.open(dsWriteFileName);
	// If dsWriteFileName did Open, Continue
	if (dsWriteFile.is_open())
	{
		// Output dsWriteFileName opened successfully to console
		cout << "File, " << dsWriteFileName << ", opened successfully" << endl
			 << endl;

		// Initialize Strings(s) for storing String(s), In Order of getline Use Order
		string
			lineHeader = " ", // Specify String for Header Line
			lineData = " ";	  // Specify String for Data Line

		// Fill Header Line (Line -2)
		// Append Menu Screen Page's Total Line Rows to lineHeader
		lineHeader = to_string(screenMenu.at(chapIndex).sPages.at(pageIndex).pageRows);
		lineHeader.append("-");
		// Append Menu Screen Page's Total Line Columns to lineHeader
		lineHeader.append(to_string(screenMenu.at(chapIndex).sPages.at(pageIndex).pageCols));
		lineHeader.append("---------------------");
		// Append Menu Screen Chapter's Name to lineHeader
		lineHeader.append(screenMenu.at(chapIndex).chapName);
		lineHeader.append("-");
		// Append Menu Screen Page's Name to lineHeader
		lineHeader.append(screenMenu.at(chapIndex).sPages.at(pageIndex).pageName);
		lineHeader.append("---------------------;");

		// Fill Data Line (Line -1)
		// Append Menu Screen Chapter's Index to lineData
		lineData = to_string(screenMenu.at(chapIndex).chapIndex);
		lineData.append(";");
		// Append Menu Screen Page's Index to lineData
		lineData.append(to_string(screenMenu.at(chapIndex).sPages.at(pageIndex).pageIndex));
		lineData.append(";");
		// Append Menu Screen Page's Min User Choice to lineData
		lineData.append(to_string(screenMenu.at(chapIndex).sPages.at(pageIndex).pageMin));
		lineData.append(";");
		// Append Menu Screen Page's Max User Choice to lineData
		lineData.append(to_string(screenMenu.at(chapIndex).sPages.at(pageIndex).pageMax));
		lineData.append(";");
		// If Menu Screen Chapter is Not Last Chapter, Append "+;"
		if (screenMenu.at(chapIndex).chapIndex < (screenMenu.size() - 1))
		{
			lineData.append("+;");
		}
		// If Menu Screen Chapter is Last Chapter, Append "-;"
		else
		{
			lineData.append("-;");
		}
		// If Menu Screen Page is Not Last Page, Append "+;"
		if (screenMenu.at(chapIndex).sPages.at(pageIndex).pageIndex < (screenMenu.at(chapIndex).sPages.size() - 1))
		{
			lineData.append("+;");
		}
		// If Menu Screen Page is Last Page, Append "-;"
		else
		{
			lineData.append("-;");
		}
		// Append Menu Screen Chapter's Name to lineData
		lineData.append(screenMenu.at(chapIndex).chapName);
		lineData.append(";");
		// Append Menu Screen Page's Name to lineData
		lineData.append(screenMenu.at(chapIndex).sPages.at(pageIndex).pageName);
		lineData.append(";");

		// Add lineHeader to lineStrings Vector
		lineStrings.push_back(lineHeader);
		// Add lineData to lineStrings Vector
		lineStrings.push_back(lineData);

		// Fill String Lines (Line 0 - lineStrings.size())
		for (int pageLine = 0; pageLine < screenMenu.at(chapIndex).sPages.at(pageIndex).sLines.size(); ++pageLine)
		{ // Loop through Menu Screen Page's Line Rows
			// Initialize String for storing Menu Screen Page's Line Column String
			string lineString = " ";

			// Temporarily Append Line Index to lineString
			lineString = "-;";

			// Append Line Index to lineString
			lineString.append(to_string(screenMenu.at(chapIndex).sPages.at(pageIndex).sLines.at(pageLine).lineIndex));

			// If Line is Line 0, Append Selected Message to lineString
			if (screenMenu.at(chapIndex).sPages.at(pageIndex).sLines.at(pageLine).lineIndex == 0)
			{
				lineString.append(";-;");
				lineString.append(screenMenu.at(chapIndex).sPages.at(pageIndex).pageSel);
			}
			// If Line Can be Selected, Append ";+;" and Required Choice to Select Line to lineString
			else if (screenMenu.at(chapIndex).sPages.at(pageIndex).sLines.at(pageLine).sLineCols.at(0).lInfo == true)
			{
				lineString.append(";+;");
				// Prevents Decimals from being Appended to lineString
				int doubleTOint = (-1);
				doubleTOint = screenMenu.at(chapIndex).sPages.at(pageIndex).sLines.at(pageLine).sLineCols.at(0).lNum;
				lineString.append(to_string(doubleTOint));
			}
			// If Line Can NOT be Selected, Append ";-; ;" to lineString
			else
			{
				lineString.append(";-; ");
			}

			// Write Lines to File
			for (int LineCol = 1; LineCol < screenMenu.at(chapIndex).sPages.at(pageIndex).sLines.at(pageLine).sLineCols.size(); ++LineCol)
			{ // Loop through Menu Screen Page's Line Columns

				// If Line Column Requires Data, Append ";+;" and Required Choice to Select Line to lineString
				if (screenMenu.at(chapIndex).sPages.at(pageIndex).sLines.at(pageLine).sLineCols.at(LineCol).lInfo == true)
				{
					lineString.append(";+");
				}
				// If Line Can NOT be Selected, Append ";-; ;" to lineString
				else
				{
					lineString.append(";-");
				}
				// Append Line Column Index to lineString
				lineString.append(to_string(screenMenu.at(chapIndex).sPages.at(pageIndex).sLines.at(pageLine).sLineCols.at(LineCol).lcolIndex));
				lineString.append(";");

				// Append Line Column String to lineString
				lineString.append(screenMenu.at(chapIndex).sPages.at(pageIndex).sLines.at(pageLine).sLineCols.at(LineCol).lStr);
			}
			lineString.append(";");

			// Check if Menu Screen Page's Line Columns are Not Empty
			bool isEmpty = true;
			for (int LineCol = 1; isEmpty && LineCol < screenMenu.at(chapIndex).sPages.at(pageIndex).sLines.at(pageLine).sLineCols.size(); ++LineCol)
			{ // Loop through Menu Screen Page's Line Columns
				// If Menu Screen Page's Line Column is Not Empty, Replace "-" and Beginning of lineString with "+"
				if (screenMenu.at(chapIndex).sPages.at(pageIndex).sLines.at(pageLine).sLineCols.at(LineCol).lStr.length() >= 1)
				{
					// If Menu Screen Page's Line Column is Not " ", Replace "-" and Beginning of lineString with "+"
					if (screenMenu.at(chapIndex).sPages.at(pageIndex).sLines.at(pageLine).sLineCols.at(LineCol).lStr != " ")
					{
						// Replace "-" and Beginning of lineString with "+"
						lineString.replace(0, 1, "+");
						isEmpty = false;
					}
				}
			}

			// Add lineString to lineStrings Vector
			lineStrings.push_back(lineString);
		}

		// Write lineStrings to dsWriteFile
		char lineChar;
		for (int pageLine = 0; pageLine < lineStrings.size(); ++pageLine)
		{ // Loop through lineStrings's Lines
			dsWriteFile << lineStrings.at(pageLine);
		}

		// Close dsWriteFileName
		dsWriteFile.close();
	}
	// If dsWriteFileName did Not Open, Error
	else
	{
		// Output dsWriteFileName failed to open to console
		cout << "File, " << dsWriteFileName << ", failed to open" << endl
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
double Game::dsMenuDisplay(int chapIndex, int pageIndex)
{
	// Initialize Variable(s) for dsMenuDisplay()
	double userDouble = (-1); // Initialize Double(s) for storing User Double(s)

	// Clear Terminal to Display Game Screen
	system("CLS");

	// Display Top Border, Each Corner Spaced by setw(40)
	cout << setw(40) << left << "+ - - - - - - - - - - - - - - - - - - -"
		 << setw(40) << right << "- - - - - - - - - - - - - - - - - - - - +"
		 << endl;

	// Display Game Screen
	for (int pageLine = 1; pageLine < screenMenu.at(chapIndex).sPages.at(pageIndex).sLines.size(); ++pageLine)
	{ // Loop through Menu Screen Page's Line Rows
		// Initialize String Vector for Menu Screen Page's Line Column Strings
		vector<string> lineStrings;

		// Fill Game Screen's lineStrings Vector
		for (int LineCol = 1; LineCol < screenMenu.at(chapIndex).sPages.at(pageIndex).sLines.at(pageLine).sLineCols.size(); ++LineCol)
		{ // Loop through Menu Screen Page's Line Columns
			// Initialize String for storing Menu Screen Page's Line Column String
			string lineString = " ";
			// Specify lineString is Menu Screen Page's Line Column String
			lineString = screenMenu.at(chapIndex).sPages.at(pageIndex).sLines.at(pageLine).sLineCols.at(LineCol).lStr;

			// If Menu Screen Page's Line Column Pointer Points to Value, Replace "~" in lineString with Value Pointed to
			if (screenMenu.at(chapIndex).sPages.at(pageIndex).sLines.at(pageLine).sLineCols.at(LineCol).lInfo == true)
			{
				// Replace "~" in lineString with Value Pointed to by Menu Screen Page's Line Column Pointer
				lineString.replace(lineString.find_first_of("~"), 1, to_string(*screenMenu.at(chapIndex).sPages.at(pageIndex).sLines.at(pageLine).sLineCols.at(LineCol).lNumPtr));
			}

			// Add lineString to lineStrings Vector
			lineStrings.push_back(lineString);
		}

		// If Menu Screen Page's Line is Selected, Append Menu Screen Page's Selected Message
		if (screenMenu.at(chapIndex).sPages.at(pageIndex).sLines.at(pageLine).sLineCols.at(0).lSel == true)
		{
			// Append Menu Screen Page's Selected Message to Last lineString
			lineStrings.at(lineStrings.size() - 1).append(screenMenu.at(chapIndex).sPages.at(pageIndex).pageSel);
		}

		// Display Left String of Menu Screen Page's Line Row, Centered to setw(40)
		cout << setw(40) << right << lineStrings.at(0);
		// Display Right String of Menu Screen Page's Line Row, Centered to setw(40)
		cout << setw(40) << left << lineStrings.at(1);

		// Display New Line After Menu Screen Page's Line Row
		cout << endl;
	}

	// Display Bottom Border, Each Corner Spaced by setw(40)
	cout << setw(40) << left << "+ - - - - - - - - - - - - - - - - - - -"
		 << setw(40) << right << "- - - - - - - - - - - - - - - - - - - - +"
		 << endl;

	// Display Final Line After All of Menu Screen Page's Line Rows
	cout << setw(40) << right << screenMenu.at(chapIndex).sPages.at(pageIndex).sLines.at(0).sLineCols.at(1).lStr
		 << left << screenMenu.at(chapIndex).sPages.at(pageIndex).sLines.at(0).sLineCols.at(2).lStr;

	// Take User Choice Specified by Menu Screen's Page
	userDouble = dsChoiceNumber(screenMenu.at(chapIndex).sPages.at(pageIndex).pageMin, screenMenu.at(chapIndex).sPages.at(pageIndex).pageMax);

	// Return User Choice as Double
	return userDouble;
}

// Function to Access Game Menus
// Accepts 2 Int Parameter(s)
// Returns Void, passes Data by Member Access
void Game::dsMenus(int chapIndex, int pageIndex)
{
	// Initialize Variable(s) for dsMenus()
	int userInt = (-1);		  // Initialize Int(s) for storing User Int(s)
	double userDouble = (-1); // Initialize Double(s) for storing User Double(s)
	bool isDone = false;	  // Initialize Bool(s) for storing Bool(s)

	// Take User's Choice with dsChoiceNumber() while isDone != true;
	do
	{
		// Display Menu and Take User Choice
		userDouble = dsMenuDisplay(chapIndex, pageIndex);
		userInt = userDouble;

		// If pageIndex == 0, Display Menu Page 1
		if (pageIndex == 0)
		{
			// If userInt is (-1), Keep Menu Running
			if (userInt == (-1))
			{
				// Keep Menu Page at Page 1
				pageIndex = 0;

				// Keep Menu Running until Closed
				isDone = false;
			}

			// If userInt is 1, Close the Menu
			else if (userInt == 1)
			{
				// Keep Menu Page at Page 1
				pageIndex = 0;

				// Close the Menu
				isDone = true;
			}

			// If User Chose a Line, Mark Line as Selected
			else
			{
				// Initialize Bool(s) for storing Bool(s)
				bool isLine = false;

				// Check Menu Screen Page's Line Rows for Selected Line Row
				for (int pageLine = 1; !(isLine) && pageLine < screenMenu.at(chapIndex).sPages.at(pageIndex).sLines.size(); ++pageLine)
				{ // Loop through Menu Screen Page's Line Rows
					// If User Selected Page's Line Row, Mark Page's Line Row as Selected
					if (userInt == screenMenu.at(chapIndex).sPages.at(pageIndex).sLines.at(pageLine).sLineCols.at(0).lNum)
					{
						// Change Menu Page to Page 2
						++pageIndex;

						// Mark Page's Line Row as Selected
						screenMenu.at(chapIndex).sPages.at(pageIndex).sLines.at(pageLine).sLineCols.at(0).lSel = true;

						// End Checking Menu Screen Page's Line Rows for Selected Line Row
						isLine = true;
					}

					// If Not Selected Page's Line Row, Keep Looking
					else
					{
						isLine = false;
					}
				}

				// Keep Menu Running until Closed
				isDone = false;
			}
		}

		// If pageIndex == 1, Display Menu Page 2
		else if (pageIndex == 1)
		{
			// If userInt is (-1), Keep Menu Running
			if (userInt == (-1))
			{
				// Keep Menu Page at Page 2
				pageIndex = 1;

				// Keep Menu Running until Closed
				isDone = false;
			}

			// If User Choice is Valid, Edit Selected Line
			else
			{
				// Initialize Bool(s) for storing Bool(s)
				bool isLine = false;

				// Check Menu Screen Page's Line Rows for Selected Line Row
				for (int pageLine = 1; !(isLine) && pageLine < screenMenu.at(chapIndex).sPages.at(pageIndex).sLines.size(); ++pageLine)
				{ // Loop through Menu Screen Page's Line Rows
					// If User Selected Page's Line Row, Check Page's Line Columns
					if (screenMenu.at(chapIndex).sPages.at(pageIndex).sLines.at(pageLine).sLineCols.at(0).lSel == true)
					{
						// Check Page's Line Columns for Selected Pointer
						for (int LineCol = 1; LineCol < screenMenu.at(chapIndex).sPages.at(pageIndex).sLines.at(pageLine).sLineCols.size(); ++LineCol)
						{ // Loop through Menu Screen Page's Line Columns
						  // If User Selected Page's Line Row, Check Page's Line Columns
							if (screenMenu.at(chapIndex).sPages.at(pageIndex).sLines.at(pageLine).sLineCols.at(LineCol).lInfo == true)
							{
								// Edit Value that Line Column's Selected Pointer Points to
								*screenMenu.at(chapIndex).sPages.at(pageIndex).sLines.at(pageLine).sLineCols.at(LineCol).lNumPtr = userInt;

								// Mark Page's Line Row as Unselected
								screenMenu.at(chapIndex).sPages.at(pageIndex).sLines.at(pageLine).sLineCols.at(0).lSel = false;

								// Change Menu Page to Page 1
								--pageIndex;

								// End Checking Menu Screen Page's Line Rows for Selected Line Row
								isLine = true;
							}
						}
					}

					// If Not Selected Page's Line Row, Keep Looking
					else
					{
						isLine = false;
					}
				}

				// Keep Menu Running until Closed
				isDone = false;
			}
		}
	} while (isDone != true);

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
// double Game::gameUi(int uMENU, int uPAGE)
//{
//	// Initialize Variable(s) for gameUi()
//	int // Initialize Int(s) for storing Int(s)
//		uiHud = 5,
//		uiChoices = 8,
//		uiCombat = 10,
//		dsChoiceMin = 1,
//		dsChoiceMax = 4;
//	double userDouble = (-1); // Initialize Double(s) for storing User Double(s)
//	bool isDone = false;	  // Initialize Bool(s) for storing Bool(s)
//
//	// Clear Terminal to Display Game Ui
//	system("CLS");
//
//	// cout Top Border, Each Corner Spaced by setw(40)
//	cout << setw(40) << left << "+- - - - - - - - - - - - -"
//		 << setw(40) << right << "- - - - - - - - - - - - -+"
//		 << endl
//		 << endl;
//
//	// Display Game Ui HUD Line 1 - 4
//	for (int uLINE = 1; uLINE < uiHud; ++uLINE)
//	{
//		// cout uiLines[uMENU][uLINE] lineLeft, then uiLines[uMENU][uLINE] lineRight, Centered to setw(40)
//		cout << setw(40) << left << (uiLines[(stoi(uiLabels[uMENU][0]) + uPAGE)][uLINE][1] + to_string(uiLinesNumbers[0][uLINE][0]))
//			 << setw(40) << right << (to_string(uiLinesNumbers[0][uLINE][1]) + uiLines[(stoi(uiLabels[uMENU][0]) + uPAGE)][uLINE][2]);
//
//		// cout New Line
//		cout << endl;
//	}
//
//	// Display Game Ui Combat Display Line 5 - 7
//	for (int uLINE = 5; uLINE < uiChoices; ++uLINE)
//	{
//		// cout uiLines[uMENU][uLINE] lineLeft, then uiLines[uMENU][uLINE] lineRight, Centered to setw(40)
//		cout << setw(40) << right << (uiLines[(stoi(uiLabels[uMENU][0]) + uPAGE)][uLINE][1] + to_string(uiLinesNumbers[0][uLINE][0]))
//			 << setw(40) << left << (uiLines[(stoi(uiLabels[uMENU][0]) + uPAGE)][uLINE][2] + to_string(uiLinesNumbers[0][uLINE][1]));
//
//		// If Line Has Value, cout Value Message
//		if (uiLines[(stoi(uiLabels[uMENU][0]) + uPAGE)][uLINE][3] != "-1")
//		{
//			cout << uiLinesNumbers[uMENU][uLINE][2];
//		}
//
//		// cout uiLines[uMENU][uLINE] lineRight
//		cout << uiLines[(stoi(uiLabels[uMENU][0]) + uPAGE)][uLINE][2];
//
//		// If Line is Selected, cout Selected Message
//		if (uiLinesNumbers[uMENU][uLINE][3] == 1)
//		{
//			cout << uiLines[(stoi(uiLabels[uMENU][0]) + uPAGE)][11][3];
//		}
//
//		// cout New Line
//		cout << endl;
//	}
//
//	// Display Game Ui Recap Line 8 - 9
//	for (int uLINE = 8; uLINE < uiCombat; ++uLINE)
//	{
//		// cout uiLines[uMENU][uLINE] lineLeft, then uiLines[uMENU][uLINE] lineRight, Centered to setw(40)
//		cout << setw(40) << right << (uiLines[(stoi(uiLabels[uMENU][0]) + uPAGE)][uLINE][1] + to_string(Players.at(playerCurrent).personHealth))
//			 << setw(40) << left << (uiLines[(stoi(uiLabels[uMENU][0]) + uPAGE)][uLINE][2] + to_string(Players.at(playerCurrent).personHealth));
//
//		// cout New Line
//		cout << endl;
//	}
//
//	// Display Game Ui Choices Line 10 - 11
//	for (int uLINE = 10; uLINE < uLINES; ++uLINE)
//	{
//		// cout uiLines[uMENU][uLINE] lineLeft, then uiLines[uMENU][uLINE] lineRight, Centered to setw(40)
//		cout << setw(40) << right << uiLines[(stoi(uiLabels[uMENU][0]) + uPAGE)][uLINE][1]
//			 << left << uiLines[(stoi(uiLabels[uMENU][0]) + uPAGE)][uLINE][2];
//
//		// cout New Line for All Lines, Except Last Line
//		if (uLINE <= (uLINES - 2))
//		{
//			cout << endl;
//		}
//	}
//
//	// Correct choiceMin
//	if (uiLines[(stoi(uiLabels[uMENU][0]) + uPAGE)][0][3].substr(0, 1) == "+")
//	{
//		dsChoiceMin = (1000 * 1000);
//	}
//	else if (uiLines[(stoi(uiLabels[uMENU][0]) + uPAGE)][0][3].substr(0, 1) == "-")
//	{
//		dsChoiceMin = ((-1000) * (1000));
//	}
//	else
//	{
//		dsChoiceMin = stoi(uiLines[(stoi(uiLabels[uMENU][0]) + uPAGE)][0][3].substr(0, 1));
//	}
//
//	// Correct choiceMax
//	if (uiLines[(stoi(uiLabels[uMENU][0]) + uPAGE)][0][3].substr(1, 1) == "+")
//	{
//		dsChoiceMax = (1000 * 1000);
//	}
//	else if (uiLines[(stoi(uiLabels[uMENU][0]) + uPAGE)][0][3].substr(1, 1) == "-")
//	{
//		dsChoiceMax = ((-1000) * (1000));
//	}
//	else
//	{
//		dsChoiceMax = stoi(uiLines[(stoi(uiLabels[uMENU][0]) + uPAGE)][0][3].substr(1, 1));
//	}
//
//	// Take User Choice Specified by Ui
//	userDouble = dsChoiceNumber(dsChoiceMin, dsChoiceMax);
//
//	// Return User Choice as Double
//	return userDouble;
//}

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

	// Return New Floor
	return newFloor;
}

// Function to Create New Enemy
// Accepts No Parameter(s) by Default
// If Entered, also Accepts 1 Int Parameter to Specify Enemy Index
// Returns Person, passes Data by Member Access
Game::Person Game::dsEnemyNew(int floorIndex, int enemyIndex)
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
	// Specify Maximum amount of Health of Enemy, hBUFF used to create an upper limit in the future
	newEnemy.personhMAX = (newEnemy.personHealth * (Floors.at(floorIndex).floorModifier / hBUFF));
	newEnemy.personHealth = newEnemy.personhMAX; // Specify Health of Enemy
	newEnemy.personIndex = enemyIndex;			 // Specify Index of Enemy
	newEnemy.personNumber = enemyCount;			 // Specify Number of Enemy

	// If dsEnemyNew() is Called with No Parameter, Specify Index of Enemy as Next Index
	if (enemyIndex == (-1))
	{
		newEnemy.personIndex = (enemyTotal - 1); // Specify Index of Enemy as Next Index
	}

	// Fill New Enemy with Random Enemy Data
	newEnemy.personMoney = (rndInt((eLOOT * 2), eLOOT) * Floors.at(floorIndex).floorModifier); // Specify Reward of Enemy

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
	newPlayer.isPlayer = true;									 // Specify Person is Player
	newPlayer.personName = ("Player " + to_string(playerCount)); // Specify Name of Player
	newPlayer.personIndex = playerIndex;						 // Specify Index of Player
	newPlayer.personNumber = playerCount;						 // Specify Number of Player

	// If dsPlayerNew() is Called with No Parameter, Specify Index of Player as Next Index
	if (playerIndex == (-1))
	{
		newPlayer.personIndex = (playerCount - 1); // Specify Index of Player as Next Index
	}

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
			Floors.at(i).Enemies.push_back(dsEnemyNew(i, j));
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
// void Game::gameCombat()
//{
//	// Initialize Variable(s) for gameSettings()
//	int userInt = 0;	   // Initialize Int(s) for storing User Int(s)
//	double userDouble = 0; // Initialize Double(s) for storing User Double(s)
//	bool isDone = false;   // Initialize Bool(s) for storing Bool(s)
//
//	for (int i = 0; i < floorTotal; ++i)
//	{
//		// Display New Floor Intro
//		dsMenus(3);
//
//		for (int j = 0; j < enemyTotal; ++j)
//		{
//			do
//			{
//				// Move to Next Round
//				++floorRound;
//
//				// Take Player's Combat Choice
//				gamePlayerTurn(playerChoice, (enemyChoice - 1));
//
//				// Take Enemy's Combat Choice
//				gameEnemyTurn();
//
//				// Consume Stamina for Actions in Combat
//				Players.at(playerCurrent) -= Floors.at(floorCurrent).Enemies.at(enemyCurrent);
//
//				// Deal Damage to Loser in Combat
//				Players.at(playerCurrent) += Floors.at(floorCurrent).Enemies.at(enemyCurrent);
//
//				// Stamina Recovery System
//				gameStaminaRecovery();
//			} while (Floors.at(floorCurrent).Enemies.at(enemyCurrent).personHealth > 0 && Players.at(playerCurrent).personHealth > 0);
//			// Move to Next Enemy
//			++enemyCurrent;
//		}
//		// Move to Next Floor
//		++floorCurrent;
//	}

// Take User Choice of (1 - 5)
// userInt = dsChoiceNumber(1, 5);

// Check User Choice
// switch (userInt)
//{
// case 1: // If User Choice is 1, Continue
//	isDone = true;
//	break;
// case 2: // If User Choice is within range, Continue
//	// uiLinesNumbers[uMENU][uLINE][3] = 1; // Set Menu Line 4 to Selected
//	isDone = false;
//	break;
// case 3: // If User Choice is within range, Continue
//	// uiLinesNumbers[uMENU][uLINE][3] = 1; // Set Menu Line 5 to Selected
//	isDone = false;
//	break;
// case 4: // If User Choice is within range, Continue
//	// uiLinesNumbers[uMENU][uLINE][3] = 1; // Set Menu Line 6 to Selected
//	isDone = false;
//	break;
// case 5: // If User Choice is within range, Continue
//	// uiLinesNumbers[uMENU][uLINE][3] = 1; // Set Menu Line 7 to Selected
//	isDone = false;
//	break;
// default: // If User Choice is Not within range, Wait
//	isDone = false;
//	break;
//}

// Fill uiLinesNumbers Array
// for (int uMENU = 0; uMENU < uMENUS; ++uMENU)
//{
//	// Fill uiLinesNumbers Array Lines
//	for (int uLINE = 0; uLINE < uLINES; ++uLINE)
//	{
//		// Fill uiLinesNumbers Array Columns
//		for (int uCOL = 0; uCOL < uCOLS; ++uCOL)
//		{
//			// Fill uiLinesNumbers Array Columns with (-1)
//			uiLinesNumbers[uMENU][uLINE][uCOL] = (-1);
//		}
//	}
//}

// Return Void
// return;
//}

// Function to execute Person Attack
// Accepts no parameters
// Returns void, passes data by member access
// void Game::gameCombats()
//{
//	for (int i = 0; i < enemyTotal; ++i)
//	{
//		do
//		{
//			// Progress Combat and Excute combat choices
//			gamePlayerTurn(playerChoice);
//			gameEnemyTurn();
//
//			// Move to next round
//			++floorRound;
//
//			// Stamina Recovery System
//			gameStaminaRecovery();
//		} while (Floors.at(floorCurrent).Enemies.at(enemyCurrent).personHealth > 0 && Players.at(playerCurrent).personHealth > 0);
//		++enemyCurrent;
//	}
//	// Display Progress after Combat
//	// gameProgress();
//
//	if (Players.at(playerCurrent).personHealth > 0)
//	{
//		bool storeUse = false;
//		bool floorNext = false;
//
//		// Victory message
//		cout << "You have killed " << Floors.at(floorCurrent).Enemies.at(enemyCurrent).personName << ", congrats." << endl
//			 << endl;
//		playerWealth += Floors.at(floorCurrent).Enemies.at(enemyCurrent).personMoney;
//		Players.at(playerCurrent) += Floors.at(floorCurrent).Enemies.at(enemyCurrent);
//		++playerKills;
//
//		// Display Progress after Combat
//		// gameProgress();
//
//		// Ask user to use store is present
//		if (Floors.at(floorCurrent).isStore == true)
//		{
//			cout << "Do you want to use the Store to buy and sell items? (0 = No, 1 = Yes): ";
//			cin >> storeUse;
//			cout << "Player's Choice: " << storeUse << endl
//				 << endl;
//			if (storeUse == 1)
//			{
//				// gameStore();
//				cout << "gameStore(). (Took Enemy Items)" << endl
//					 << endl;
//				playerWealth -= Floors.at(floorCurrent).Enemies.at(enemyCurrent).personMoney;
//			}
//			else
//			{
//				cout << "You can no longer access the Store. (No Items Taken)" << endl
//					 << endl;
//			}
//		}
//
//		// Ask user to advance to the next floor
//		do
//		{
//			cout << "Are you ready to advance to the next Floor? (1 = Yes): ";
//			cin >> floorNext;
//			cout << "Player's Choice: " << floorNext << endl
//				 << endl;
//			if (floorNext == 1)
//			{
//				Players.at(playerCurrent).personStamina = sMAX;
//				playerWealth += Floors.at(floorCurrent).floorMoney;
//				Players.at(playerCurrent).personMoney += Floors.at(floorCurrent).floorMoney;
//				++floorCurrent;
//				floorRound = 0;
//			}
//			else
//			{
//				cout << "Please press 1 to advance to the next Floor" << endl;
//			}
//		} while (floorNext != 1);
//	}
//	else
//	{
//		cout << "You have died. Thats unfortunate." << endl
//			 << endl
//			 << "You killed " << playerKills
//			 << " enemies and earned a total of " << playerWealth << " money." << endl
//			 << endl;
//	}
//	return;
//}

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
// void Game::gamePlayerTurn(int uMENU, int uPAGE)
//{
//	// Initialize Variable(s) for gamePlayerTurn()
//	int userInt = (-1);		  // Initialize Int(s) for storing User Int(s)
//	double userDouble = (-1); // Initialize Double(s) for storing User Double(s)
//	bool isDone = false;	  // Initialize Bool(s) for storing Bool(s)
//
//	// Reset Player
//	// playerChoice = (-1);
//	Players.at(playerCurrent).isRecovering = true;
//	Players.at(playerCurrent).isAttacking = false;
//	Players.at(playerCurrent).isBlocking = false;
//	Players.at(playerCurrent).isDodging = false;
//	Players.at(playerCurrent).isWaiting = false;
//
//	// Set Ui Values
//	// uiLinesNumbers[0][0][0] = Players.at(playerCurrent).personHealth;
//	// uiLinesNumbers[0][0][1] = Floors.at(floorCurrent).Enemies.at(enemyCurrent).personHealth;
//	// uiLinesNumbers[0][1][0] = Players.at(playerCurrent).personStamina;
//	// uiLinesNumbers[0][1][1] = Floors.at(floorCurrent).Enemies.at(enemyCurrent).personStamina;
//	// uiLinesNumbers[0][2][0] = Players.at(playerCurrent).personMoney;
//	// uiLinesNumbers[0][2][1] = (enemyTotal - enemyCurrent);
//
//	// Take User's Choice with dsChoiceNumber() while isDone != true;
//	do
//	{
//		// Display Game Ui with Correct Ui Index
//		userDouble = gameUi(uMENU, uPAGE);
//		userInt = userDouble;
//
//		// Check User Choice
//		switch (userInt)
//		{
//		case 1: // If User Choice is 1, Attack
//			// If User has enough Stamina, Attack
//			if (Players.at(playerCurrent).personStamina >= aCOST)
//			{
//				Players.at(playerCurrent).isAttacking = true;
//				isDone = true;
//			}
//			// If User does Not have enough Stamina, Take Choice Again
//			else
//			{
//				isDone = false;
//			}
//			break;
//		case 2: // If User Choice is 2, Block
//			// Disable Stamina Recovery, Block
//			Players.at(playerCurrent).isRecovering = false;
//			Players.at(playerCurrent).isBlocking = true;
//			isDone = true;
//			break;
//		case 3: // If User Choice is 3, Dodge
//			// If User has enough Stamina, Dodge
//			if (Players.at(playerCurrent).personStamina >= dCOST)
//			{
//				Players.at(playerCurrent).isDodging = true;
//				isDone = true;
//			}
//			// If User does Not have enough Stamina, Take Choice Again
//			else
//			{
//				isDone = false;
//			}
//			break;
//		case 4: // If User Choice is 4, Wait
//			// Enable Stamina Recovery, Wait
//			Players.at(playerCurrent).isRecovering = true;
//			Players.at(playerCurrent).isWaiting = true;
//			isDone = true;
//			break;
//		case 9: // If User Choice is 9, Exit
//			isDone = true;
//			break;
//		default: // If User Choice is Not within range, Wait
//			isDone = false;
//			break;
//		}
//	} while (isDone != true);
//
//	// playerChoice = userInt
//	playerChoice = userInt;
//
//	// Return Void
//	return;
//}

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

// Function to execute Person Attack
// Accepts no parameters
// Returns void, passes data by member access
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
