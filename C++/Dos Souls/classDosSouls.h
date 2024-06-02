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
 *                              class Dos Souls .h                            *
 ******************************************************************************/
/*  	DEFINE FILE AS HEADER FILE	-	-	-	-	-	-	-	-	-	-	  */
#ifndef CLASS_DOS_SOULS_H
#define CLASS_DOS_SOULS_H
/*  	INCLUDE LIBRARIES FOR FILE	-	-	-	-	-	-	-	-	-	-	  */
// #include "classDisplayScreen.h"
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

/*  	INITIALIZE GLOBAL CONSTS FOR FILE	-	-	-	-	-	-	-	-	  */
/** 	Initialize Const Strings for File	-	-	-	-	-	-	-	-	 **/
const string
	/***	File Names	-	-	-	-	-	-	-	-	-	-	-	-	-	***/
	fileNew = "fileNew.dat",				 // Specify Name of New File
	fileMenus = "fileMenus.txt",			 // Specify Name of Game Menu Screens File
	fileUi = "fileUis.txt",					 // Specify Name of Game Ui Screens File
	fileUisMessages = "fileUisMessages.txt", // Specify Name of Game Ui Messages File
	fileItems = "fileItems.txt",
	fileFloors = "fileFloors.txt",
	fileEnemies = "fileEnemies.txt",
	filePlayers = "filePlayers.txt";

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
const int screenMenus[] = {0, 1, 2, 3, 4, 5, 6};
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
	COMBAT4, // Specify Chapter of Player Wait Ui Screens
	COMBAT5	 // Specify Chapter of Player Wait Ui Screens
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

class Game /*  	INITIALIZE CLASS FOR DOS SOULS	-	-	-	-	-	-	-	  */
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
		enemyChoice = 1,
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

	/*  	INITIALIZE PRIVATE FUNCTIONS FOR GAME CLASS	-	-	-	-	-	  */
	/** 	Initialize New Private Functions	-	-	-	-	-	-	-	 **/
	//

public: /*  	PUBLIC MEMBER SECTION FOR CLASS	-	-	-	-	-	-	-	  */
	/*  	INITIALIZE PUBLIC STRUCTS FOR CLASS	-	-	-	-	-	-	-	  */
	/** 	Initialize Display Screen Structs	-	-	-	-	-	-	-	 **/
	struct sLineCol;
	struct sLine;
	struct sPage;
	struct sChapter;

	/** 	Initialize Game Item Structs	-	-	-	-	-	-	-	-	 **/
	struct Weapon;
	struct Armor;

	/** 	Initialize Game Character Structs	-	-	-	-	-	-	-	 **/
	struct Person;

	/** 	Initialize Game Level Structs	-	-	-	-	-	-	-	-	 **/
	struct Floor;

	/*  	INITIALIZE PUBLIC VECTORS FOR CLASS	-	-	-	-	-	-	-	  */
	/** 	Initialize Display Screen Vectors	-	-	-	-	-	-	-	 **/
	vector<sChapter> screenMenu;
	vector<sChapter> screenUi;

	/** 	Initialize Game Character Vectors	-	-	-	-	-	-	-	 **/
	vector<Person> Players;

	/** 	Initialize Game Level Vectors	-	-	-	-	-	-	-	-	 **/
	vector<Floor> Floors;

	/*  	INITIALIZE PUBLIC FUNCTIONS FOR CLASS	-	-	-	-	-	-	  */
	/** 	Initialize Class Constructor Functions	-	-	-	-	-	-	 **/
	Game();
	~Game();

	/** 	Initialize User Input Functions	-	-	-	-	-	-	-	-	 **/
	string dsChoiceString();
	double dsChoiceNumber(int = 1, int = 9);

	/** 	Initialize File Read/Write Functions	-	-	-	-	-	-	 **/
	void dsFiles(string);
	void dsFileWrite(int, int = 0, string = fileNew);

	/** 	Initialize Menu Screens Functions	-	-	-	-	-	-	-	 **/
	double dsMenuDisplay(int, int = 0);
	void dsMenus(int, int = 0);

	/** 	Initialize Ui Screens Functions	-	-	-	-	-	-	-	-	 **/
	void dsUisCombat();
	double dsUisDisplay(int, int = 0);
	void dsUis(int, int = 0);

	/** 	Initialize Game Building Functions	-	-	-	-	-	-	-	 **/
	int rndInt(int, int = 1);
	bool rng(int = rngPSIZE);
	Floor &dsFloorNew(int = -1);
	Person &dsEnemyNew(int = -1, int = -1);
	Person &dsPlayerNew(int = -1);
	void dsGameNew();

	/** 	Initialize Game Combat Functions	-	-	-	-	-	-	-	 **/
	void gameCombat();
	void gameStaminaRecovery();
	void gamePlayerTurn(int, int = 0);
	int gameEnemyAi();
	void gameEnemyTurn();

	/** 	Initialize Game Extra Functions	-	-	-	-	-	-	-	-	 **/
	void gameCombats();

	/** 	Initialize Class Friend Functions	-	-	-	-	-	-	-	 **/
	// friend void Screen::fileRead(string);
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
		fileStream.open(fileName, ios::out /*| ios::binary*/);
	}

	/** 	If Opening Fstream in Input Mode, Open File with ios::in	-	 **/
	else
	{
		/***	Open File with ios::in to Read from File	-	-	-	-	***/
		fileStream.open(fileName, ios::in /*| ios::binary*/);
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
