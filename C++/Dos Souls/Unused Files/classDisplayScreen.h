/******************************************************************************
Display Screens Class

Donnie Gilbert
CS162-W1 SP24 Priestley

Purpose of the program:
A Class for Display Screens that Output to the Console,
and Refreshes the Console in Regular Intervals with Uniformly Formatted Text,
which Emulates Navigating Menus and Displaying Ui Elements in Video Games.

Specification Summary:
Lots of Structs and Vectors for Display Screens.

Sources:
Watching Mr.Priestley's labs and stuff I learned failing other classes.

"If you don't specify, I may ask you if I can share it."
*******************************************************************************/

/******************************************************************************
 *                        class Display Screens .h                            *
 ******************************************************************************/
/*  	DEFINE FILE AS HEADER FILE	-	-	-	-	-	-	-	-	-	-	  */
#ifndef CLASS_DISPLAY_SCREENS_H
#define CLASS_DISPLAY_SCREENS_H
/*  	INCLUDE LIBRARIES FOR FILE	-	-	-	-	-	-	-	-	-	-	  */
#include <stdlib.h>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <cstring>
#include <vector>
/*  	DEFINE NAMESPACE FOR FILE	-	-	-	-	-	-	-	-	-	-	  */
using namespace std;
/******************************************************************************
 *                               GLOBAL DECLARATIONS                          *
 ******************************************************************************/
class Game; // Forward declaration of Game class

/*  	INITIALIZE GLOBAL CONSTS FOR FILE	-	-	-	-	-	-	-	-	  */
/** 	Initialize Const Strings for File	-	-	-	-	-	-	-	-	 **/
const string
	/***	File Names	-	-	-	-	-	-	-	-	-	-	-	-	-	***/
	fileNew = "fileNew.dat",		// Specify Name of New File
	fileMenus = "fileMenus.dat",	// Specify Name of Menu Screens File
	fileUis = "fileUis.dat",		// Specify Name of Ui Screens File
	fileMenusTxt = "fileMenus.txt", // Specify Name of Menu Screens .txt File
	fileUisTxt = "fileUis.txt";		// Specify Name of Ui Screens .txt File

/** 	Initialize Const Int Array for Game Consts	-	-	-	-	-	-	 **/
const int gameConsts[] =
	{100, 1, 2, 100, 10, 3, 2, 1, 10, 25, 2, 50, 10, 4, 3, 500, 250};
/***	Initialize Enums for Game Consts	-	-	-	-	-	-	-	-	***/
enum gameConstNames
{
	hMAX,	  // Specify Maximum amount of Health
	hBUFF,	  // Specify Maximum Health Multiplier of Enemies
	hSTEAL,	  // Specify Maximum amount of Life Steal
	sMAX,	  // Specify Maximum amount of Stamina
	sGAIN,	  // Specify Base amount of Stamina Recovery
	sLGAIN,	  // Specify Bonus amount of Stamina Recovery for Light Armor
	sMGAIN,	  // Specify Bonus amount of Stamina Recovery for Medium Armor
	sHGAIN,	  // Specify Bonus amount of Stamina Recovery for Heavy Armor
	aCOST,	  // Specify Cost of Attack
	bCOST,	  // Specify Cost of Block
	bBUFF,	  // Specify Damage Reduction of Block
	dCOST,	  // Specify Cost of Dodge
	rngASIZE, // Specify Size of Person Arrays
	rngPSIZE, // Specify Size of Player rngArray
	rngESIZE, // Specify Size of Enemy rngArray
	fLOOT,	  // Specify Minimum amount of Money Player gets for beating Floor
	eLOOT	  // Specify Minimum amount of Money Player gets for killing Enemy
};

/** 	Initialize Const Int Array for Menu Screens	-	-	-	-	-	-	 **/
const int screenMenus[] = {0, 1, 2, 3, 4, 5};
/***	Initialize Enums for Menu Screens	-	-	-	-	-	-	-	-	***/
enum screenMenuNames
{
	INTRO,		// Specify Chapter of Intro Menu Screens
	RULES,		// Specify Chapter of Rules Menu Screens
	SETTINGS,	// Specify Chapter of Settings Menu Screens
	FLOORINTRO, // Specify Chapter of Floor Intro Menu Screens
	STORE,		// Specify Chapter of Store Menu Screens
	OUTRO		// Specify Chapter of Outro Menu Screens
};

/** 	Initialize Const Int Array for Ui Screens	-	-	-	-	-	-	 **/
const int screenUis[] = {0, 1, 2, 3, 4};
/***	Initialize Enums for Ui Screens	-	-	-	-	-	-	-	-	-	***/
enum screenUiNames
{
	COMBAT0, // Specify Chapter of Player Neutral Ui Screens
	COMBAT1, // Specify Chapter of Player Attack Ui Screens
	COMBAT2, // Specify Chapter of Player Block Ui Screens
	COMBAT3, // Specify Chapter of Player Dodge Ui Screens
	COMBAT4	 // Specify Chapter of Player Wait Ui Screens
};

/*  	INITIALIZE GLOBAL FUNCTIONS FOR FILE	-	-	-	-	-	-	-	  */
/** 	Initialize File Read/Write Functions	-	-	-	-	-	-	-	 **/
bool fileOpen(fstream &, string &, bool fileIsWriting = false);

/******************************************************************************
 *                               GLOBAL DECLARATIONS                          *
 ******************************************************************************/

/******************************************************************************
 *                                CLASS DEFINITIONS                           *
 ******************************************************************************/

class Screen /*  	INITIALIZE CLASS FOR DISPLAY SCREENS	-	-	-	-	  */
{
private: /*  	PRIVATE MEMBER SECTION FOR CLASS	-	-	-	-	-	-	  */
	/*  	INITIALIZE PRIVATE VARIABLES FOR CLASS	-	-	-	-	-	-	  */
	/** 	Initialize Private Ints for Class	-	-	-	-	-	-	-	 **/
	int
		/***	Display Screen Ints	-	-	-	-	-	-	-	-	-	-	***/
		menuCount = 0,
		screenCount = 0,
		pageCount = 0,
		lineCount = 0,

		/***	Game Settings Ints	-	-	-	-	-	-	-	-	-	-	***/
		floorDifficulty = 3,
		floorTotal = 10,
		enemyTotal = 1,
		playerTotal = 1,

		/***	Game Character/Level Ints	-	-	-	-	-	-	-	-	***/
		floorCount = 0,
		enemyCount = 0,
		playerCount = 0,

		/***	Game Progress Ints	-	-	-	-	-	-	-	-	-	-	***/
		floorCurrent = 0,
		floorRound = 0,
		enemyCurrent = 0,
		playerCurrent = 0,

		/***	Combat Choice Ints	-	-	-	-	-	-	-	-	-	-	***/
		enemyChoice = 0,
		playerChoice = 0,

		/***	Game Statistics Ints	-	-	-	-	-	-	-	-	-	***/
		playerFloors = 0,
		playerKills = 0,
		playerWealth = 0,

		/***	User Input Ints	-	-	-	-	-	-	-	-	-	-	-	***/
		userInt = 0;

	/** 	Initialize Private Strings for Class	-	-	-	-	-	-	 **/
	string
		/***	User Input Strings	-	-	-	-	-	-	-	-	-	-	***/
		userName = "Player",
		userString = "0";

	/** 	Initialize Private Bools for Class	-	-	-	-	-	-	-	 **/
	bool
		/***	Game Value Bools	-	-	-	-	-	-	-	-	-	-	***/
		userIntisInt = false,
		userStringisString = false;

public: /*  	PUBLIC MEMBER SECTION FOR CLASS	-	-	-	-	-	-	-	  */
	/*  	INITIALIZE PUBLIC STRUCTS FOR CLASS	-	-	-	-	-	-	-	  */
	/** 	Initialize Display Screen Structs	-	-	-	-	-	-	-	 **/
	struct LCPs;
	struct LCol;
	struct Line;
	struct Page;
	struct Chap;

	/** 	Initialize Game Item Structs	-	-	-	-	-	-	-	-	 **/
	struct Weapon;
	struct Armor;

	/** 	Initialize Game Character Structs	-	-	-	-	-	-	-	 **/
	struct Person;

	/** 	Initialize Game Level Structs	-	-	-	-	-	-	-	-	 **/
	struct Floor;

	/*  	INITIALIZE PUBLIC VECTORS FOR CLASS	-	-	-	-	-	-	-	  */
	/** 	Initialize Display Screen Vectors	-	-	-	-	-	-	-	 **/
	vector<Chap> screenMenus;
	vector<Chap> screenUis;

	/** 	Initialize Game Character Vectors	-	-	-	-	-	-	-	 **/
	vector<Person> Players;

	/** 	Initialize Game Level Vectors	-	-	-	-	-	-	-	-	 **/
	vector<Floor> Floors;

	/*  	INITIALIZE PUBLIC FUNCTIONS FOR CLASS	-	-	-	-	-	-	  */
	/** 	Initialize Class Constructor Functions	-	-	-	-	-	-	 **/
	Screen();
	~Screen();

	/** 	Initialize User Input Functions	-	-	-	-	-	-	-	-	 **/
	string inputString();
	double inputNumber(int = 1, int = 9);

	/** 	Initialize File Read/Write Functions	-	-	-	-	-	-	 **/
	void fileRead(string);
	void fileWrite(int, int = 0, string = fileNew);

	/** 	Initialize Menu Screens Functions	-	-	-	-	-	-	-	 **/
	double menuDisplay(int, int = 0);
	void menuOpen(int, int = 0);

	/** 	Initialize Ui Screens Functions	-	-	-	-	-	-	-	-	 **/
	double uiDisplay(int, int = 0);
	void uiOpen(int, int = 0);

	/** 	Initialize Random Variable Functions	-	-	-	-	-	-	 **/
	int randomInt(int, int = 1);
};

/*  	DEFINE PUBLIC STRUCTS FOR CLASS	-	-	-	-	-	-	-	-	-	  */
/** 	Define Display Screen Structs	-	-	-	-	-	-	-	-	-	 **/

// Struct that Stores Pointers for Page's Line Columns
// Contains:	Pointers to Ints, Doubles, Chars, Strings, and Bools
// Defines Struct, Passes Data by Member Access
struct Screen::LCPs
{
	/*  	INITIALIZE VARIABLES FOR Ptrs	-	-	-	-	-	-	-	-	  */
	/** 	Initialize Pointers for Ptrs	-	-	-	-	-	-	-	-	 **/
	int *LColInt = nullptr;		  // Specify LCol's Pointer to Ints
	double *LColDouble = nullptr; // Specify LCol's Pointer to Doubles
	char *LColChar = nullptr;	  // Specify LCol's Pointer to Chars
	string *LColString = nullptr; // Specify LCol's Pointer to Strings
	bool *LColBool = nullptr;	  // Specify LCol's Pointer to Bools
};

// Struct that Stores Line Columns for Page's Lines
// Contains:	Ints, Doubles, Strings, Bools, and Ptrs
// Defines Struct, Passes Data by Member Access
struct Screen::LCol
{
	/*  	INITIALIZE VARIABLES FOR LCol	-	-	-	-	-	-	-	-	  */
	/** 	Initialize Ints for LCol	-	-	-	-	-	-	-	-	-	 **/
	int lcolIndex = (-1); // Specify LCol's Index

	/** 	Initialize Doubles for LCol	-	-	-	-	-	-	-	-	-	 **/
	double lNum = (-1); // Specify LCol's Variable Number;

	/** 	Initialize Strings for LCol	-	-	-	-	-	-	-	-	-	 **/
	string
		lStr = " ",	 // Specify LCol's Variable String
		lType = " "; // Specify LCol's Pointer Type

	/** 	Initialize Bools for LCol	-	-	-	-	-	-	-	-	-	 **/
	bool
		lInfo = false, // Specify LCol's Variable State
		lSel = false;  // Specify LCol's Selected State

	/** 	Initialize Pointers for Ptrs	-	-	-	-	-	-	-	-	 **/
	LCPs Ptrs; // Specify LCol's Pointers to Variable Data
};

// Struct that stores Line Rows for Display Screen Pages
// Contains Ints, Strings, Vectors, and Functions
// Defines Struct, passes Data by Member Access
struct Screen::Line
{
	/*  	INITIALIZE VARIABLES FOR Line	-	-	-	-	-	-	-	-	  */
	/** 	Initialize Ints for Line	-	-	-	-	-	-	-	-	-	 **/
	int
		lineIndex = (-1),	 // Specify Line's Line Index
		lineEmptyNum = (-1); // Specify Line's Empty Number Value

	/** 	Initialize Strings for Line	-	-	-	-	-	-	-	-	-	 **/
	string
		lineName = "Line ", // Specify Line's Name
		lineEmptyStr = " "; // Specify Line's Empty String Value

	/*  	INITIALIZE VECTORS FOR Line	-	-	-	-	-	-	-	-	-	  */
	vector<LCol> LCols; // LCol Vector for Line's Line Columns

	/*  	DEFINE FUNCTIONS FOR Line	-	-	-	-	-	-	-	-	-	  */
	/** 	Define Struct Constructor Functions	-	-	-	-	-	-	-	 **/
	// Default Constructor for Line
	// Create New Line Column at LCols.at(0) to Reserve for Line Data,
	// and Allow me to Access LCols with Line Column 1 starting at Index 1
	Line() { LineNew(); }

	/** 	Define Struct Vector Functions	-	-	-	-	-	-	-	-	 **/
	// Function to Create New Line Column, and Add to this->LCols
	// Accepts No Parameters
	// Returns Void, passes Data by Member Access
	void LineNew()
	{
		/*  	INITIALIZE VARIABLES FOR LineNew()	-	-	-	-	-	-	  */
		/** 	Initialize LCols for LineNew()	-	-	-	-	-	-	-	 **/
		LCol newLCol;
		/***	Push Back LCols to this->LCols Vector	-	-	-	-	-	***/
		this->LCols.push_back(newLCol);

		/*  	RETURN VOID	-	-	-	-	-	-	-	-	-	-	-	-	  */
		return;
	}

	/** 	Define Struct Overload Functions	-	-	-	-	-	-	-	 **/
	// Function to Overload Operator '/' for Line to Split Strings in Half
	// Requires 1 String Parameter to Split
	// Returns Void, passes Data by Member Access
	void operator/(string &oldString)
	{
		/*  	INITIALIZE VARIABLES FOR operator/()	-	-	-	-	-	  */
		/** 	Initialize Ints for operator/()	-	-	-	-	-	-	-	 **/
		int stringHalf = (-1); // Specify Line Half Way Point

		/*  	CHECK LENGTH OF oldString	-	-	-	-	-	-	-	-	  */
		/** 	If oldString Length is Even, Continue Normally	-	-	-	 **/
		if (oldString.length() >= 2 && (oldString.length() % 2) == 0)
		{
			/*  	DIVIDE LENGTH OF oldString IN HALF	-	-	-	-	-	  */
			stringHalf = (oldString.length() / 2);
			/** 	Add 1st Half to Old this->LCols.at(-1).lStr	-	-	-	 **/
			this->LCols.at(this->LCols.size() - 1).lStr =
				oldString.substr(0, stringHalf);
			/***	Create New Line Column	-	-	-	-	-	-	-	-	***/
			this->LineNew();

			/** 	Add 2nd Half to New this->LCols.at(-1).lStr	-	-	-	 **/
			this->LCols.at(this->LCols.size() - 1).lStr =
				oldString.substr(stringHalf);
		}

		/** 	If oldString Length is Odd, Subtract oldString Length by 1	 **/
		else if (oldString.length() >= 3 && (oldString.length() % 2) != 0)
		{
			/*  	SUBTRACT LENGTH OF oldString BY 1, THEN DIVIDE IN HALF	  */
			stringHalf = ((oldString.length() - 1) / 2);
			/** 	Add 1st Half to Old this->LCols.at(-1).lStr	-	-	-	 **/
			this->LCols.at(this->LCols.size() - 1).lStr =
				oldString.substr(0, stringHalf);
			/***	Create New Line Column	-	-	-	-	-	-	-	-	***/
			this->LineNew();

			/** 	Add 2nd Half to New this->LCols.at(-1).lStr	-	-	-	 **/
			this->LCols.at(this->LCols.size() - 1).lStr =
				oldString.substr(stringHalf);
		}

		/** 	If oldString Length is Invalid, Error Without .push_back()	 **/
		else
		{
			cout << "Function: Line.operator/() Failed" << endl;
		}

		/*  	RETURN VOID	-	-	-	-	-	-	-	-	-	-	-	-	  */
		return;
	}
};

// Struct that stores Pages for Display Screen Chapters
// Contains Ints, Strings, and Vectors
// Defines Struct, passes Data by Member Access
struct Screen::Page
{
	/*  	INITIALIZE VARIABLES FOR Page	-	-	-	-	-	-	-	-	  */
	/** 	Initialize Ints for Page	-	-	-	-	-	-	-	-	-	 **/
	int
		pageIndex = (-1), // Specify Page's Page Index
		pageRows = (-1),  // Specify Page's Line Row Amount
		pageCols = (-1),  // Specify Page's Line Column Amount
		pageMin = (-1),	  // Specify Page's Min Choice
		pageMax = (-1);	  // Specify Page's Max Choice

	/** 	Initialize Strings for Page	-	-	-	-	-	-	-	-	-	 **/
	string
		pageName = "New Page",	 // Specify Page's Name
		pageSel = " [SELECTED]"; // Specify Page's Selected Message

	/*  	INITIALIZE VECTORS FOR Page	-	-	-	-	-	-	-	-	-	  */
	vector<Line> Lines; // Line Vector for Page's Line Rows
};

// Struct that stores Chapters for Display Screens
// Contains Ints, Strings, Vectors, and Vectors of Pointers
// Defines Struct, passes Data by Member Access
struct Screen::Chap
{
	/*  	INITIALIZE VARIABLES FOR Chap	-	-	-	-	-	-	-	-	  */
	/** 	Initialize Ints for Chap	-	-	-	-	-	-	-	-	-	 **/
	int chapIndex = (-1); // Specify Chap's Chapter Index

	/** 	Initialize Strings for Chap	-	-	-	-	-	-	-	-	-	 **/
	string chapName = "New Chapter"; // Specify Chap's Name

	/*  	INITIALIZE VECTORS FOR Chap	-	-	-	-	-	-	-	-	-	  */
	vector<Page> Pages;		   // Page Vector for Chap's Pages
	vector<int *> chapPtrs;	   // Int Pointer Vector for Chap's Variable Data
	vector<double *> doubPtrs; // Int Pointer Vector for Chap's Variable Data
};

/******************************************************************************
 *                                CLASS DEFINITIONS                           *
 ******************************************************************************/

/******************************************************************************
 *                               GLOBAL DEFINITIONS                           *
 ******************************************************************************/

/*  	DEFINE GLOBAL FUNCTIONS FOR FILE	-	-	-	-	-	-	-	-	  */
/** 	Define File Read/Write Functions	-	-	-	-	-	-	-	-	 **/

// Function to Open Files in Binary Mode
// Accepts:	1 Fstream Parameter for File Stream,
// 			1 String Parameter for File Name,
// Optional	1 Bool Parameter for true == Writing to File. (Default: false)
// Returns Bool, true == File is Open, false == File is Not Open
bool fileOpen(fstream &fileStream, string &fileName, bool fileIsWriting)
{
	/*  	CHECK IF OPENING FSTREAM IN INPUT OR OUTPUT MODE	-	-	-	  */
	/** 	If Opening Fstream in Output Mode, Open File with ios::out	-	 **/
	if (fileIsWriting == true)
	{
		/***	Open File with ios::out to Write to File	-	-	-	-	***/
		fileStream.open(fileName, ios::out | ios::binary);
	}

	/** 	If Opening Fstream in Input Mode, Open File with ios::in	-	 **/
	else
	{
		/***	Open File with ios::in to Read from File	-	-	-	-	***/
		fileStream.open(fileName, ios::in | ios::binary);
	}

	/*  	CHECK IF FILE IS OPEN	-	-	-	-	-	-	-	-	-	-	  */
	/** 	If File Fails to Open Correctly, Return File is Not Open	-	 **/
	if (fileStream.fail())
	{
		/***	Output Error Message	-	-	-	-	-	-	-	-	-	***/
		cout << "File, " << fileName << ", failed to open" << endl
			 << endl;

		/***	Return File is Not Open	-	-	-	-	-	-	-	-	-	***/
		return false; // false == File is Not Open
	}

	/** 	If File Opens Correctly, Return File is Open	-	-	-	-	 **/
	else
	{
		/***	Output Success Message	-	-	-	-	-	-	-	-	-	***/
		cout << "File, " << fileName << ", opened successfully" << endl
			 << endl;

		/***	Return File is Open	-	-	-	-	-	-	-	-	-	-	***/
		return true; // true == File is Open
	}
}

/******************************************************************************
 *                               GLOBAL DEFINITIONS                           *
 ******************************************************************************/

#endif
