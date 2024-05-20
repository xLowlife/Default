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
/*  	DEFINE HEADER FILE FOR CLASSES	-	-	-	-	-	-	-	-	-	  */
#ifndef CLASS_DOS_SOULS_H
#define CLASS_DOS_SOULS_H
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

/*  	INITIALIZE GLOBAL CONSTS FOR FILE	-	-	-	-	-	-	-	-	  */
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

/** 	Initialize Const Int Array for Display Screens (Menus)	-	-	-	 **/
const int screenMenus[] = {0, 1, 2, 3, 4, 5, 6};
/***	Initialize Enums for Display Screens (Menus)	-	-	-	-	-	***/
enum screenMenuNames
{
	INTRO,		// Specify Game's Intro Menu Screen
	RULES,		// Specify Game's Rules Menu Screen
	SETTINGS,	// Specify Game's Settings Menu Screen
	FLOORINTRO, // Specify Game's Floor Intro Menu Screen
	STORE,		// Specify Game's Store Menu Screen
	OUTRO		// Specify Game's Outro Menu Screen
};

/** 	Initialize Const Int Array for Display Screens (Uis)	-	-	-	 **/
const int screenUis[] = {0, 1, 2, 3, 4};
/***	Initialize Enums for Display Screens (Uis)	-	-	-	-	-	-	***/
enum screenUiNames
{
	COMBAT0, // Specify Game's Player Neutral Combat Ui Screen
	COMBAT1, // Specify Game's Player Attack Combat Ui Screen
	COMBAT2, // Specify Game's Player Block Combat Ui Screen
	COMBAT3, // Specify Game's Player Dodge Combat Ui Screen
	COMBAT4	 // Specify Game's Player Wait Combat Ui Screen
};

/*  	INITIALIZE GLOBAL FUNCTIONS FOR FILE	-	-	-	-	-	-	-	  */
/** 	Initialize New Global Functions	-	-	-	-	-	-	-	-	-	 **/
//

/******************************************************************************
 *                               GLOBAL DECLARATIONS                          *
 ******************************************************************************/

/******************************************************************************
 *                                CLASS DEFINITIONS                           *
 ******************************************************************************/

class Game /*  	INITIALIZE CLASS FOR GAME	-	-	-	-	-	-	-	-	  */
{
public: /** 	Public Member Section for Game Class	-	-	-	-	-	 **/
	/*  	INITIALIZE PUBLIC STRUCTS FOR GAME CLASS	-	-	-	-	-	  */
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

	/*  	INITIALIZE PUBLIC VECTORS FOR GAME CLASS	-	-	-	-	-	  */
	/** 	Initialize Display Screen Vectors	-	-	-	-	-	-	-	 **/
	vector<sChapter> screenMenu;
	vector<sChapter> screenUi;

	/** 	Initialize Game Character Vectors	-	-	-	-	-	-	-	 **/
	vector<Person> Players;

	/** 	Initialize Game Level Vectors	-	-	-	-	-	-	-	-	 **/
	vector<Floor> Floors;

	/*  	INITIALIZE PUBLIC FUNCTIONS FOR GAME CLASS	-	-	-	-	-	  */
	/** 	Initialize Class Constructor Functions	-	-	-	-	-	-	 **/
	Game();
	~Game();

	/** 	Initialize User Input Functions	-	-	-	-	-	-	-	-	 **/
	string dsChoiceString();
	double dsChoiceNumber(int = 1, int = 9);

	/** 	Initialize File Read/Write Functions	-	-	-	-	-	-	 **/
	void dsFiles(string);
	void dsFileWrite(int, int = 0, string = "fileNew.txt");

	/** 	Initialize Display Screen (Menus) Functions	-	-	-	-	-	 **/
	double dsMenuDisplay(int, int = 0);
	void dsMenus(int, int = 0);

	/** 	Initialize Display Screen (Uis) Functions	-	-	-	-	-	 **/
	double dsUiDisplay(int, int = 0);
	void dsUis(int, int = 0);

	/** 	Initialize Game Build Functions	-	-	-	-	-	-	-	-	 **/
	int rndInt(int, int = 1);
	bool rng(int = rngPSIZE);
	Floor dsFloorNew(int = -1);
	Person dsEnemyNew(int = -1, int = -1);
	Person dsPlayerNew(int = -1);
	void dsGameNew();

	/** 	Initialize Game Combat Functions	-	-	-	-	-	-	-	 **/
	void gameCombat();
	void gameStaminaRecovery();
	void gamePlayerTurn(int, int = 0);
	int gameEnemyAi();
	void gameEnemyTurn();

	/** 	Initialize Game Extra Functions	-	-	-	-	-	-	-	-	 **/
	void gameAddItems();
	void gameProgress();
	void gameCombats();

	/** 	Initialize Game Trash Functions	-	-	-	-	-	-	-	-	 **/
	void turnAttackShow();
	void turnBlockShow();
	void turnDodgeShow();
	void turnWaitShow();
	void enemyAttackShow();
	void enemyBlockShow();
	void enemyDodgeShow();
	void enemyWaitShow();

private: /** 	Private Member Section for Game Class	-	-	-	-	-	 **/
	/*  	INITIALIZE PRIVATE VARIABLES FOR GAME CLASS	-	-	-	-	-	  */
	/** 	Initialize Private Ints for Game Class	-	-	-	-	-	-	 **/
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

	/** 	Initialize Private Strings for Game Class	-	-	-	-	-	 **/
	string
		/***	Game Files Strings	-	-	-	-	-	-	-	-	-	-	***/
		fileMenus = "fileMenus.txt",
		fileUi = "fileUi.txt",
		fileItems = "fileItems.txt",
		fileFloors = "fileFloors.txt",
		fileEnemies = "fileEnemies.txt",
		filePlayers = "filePlayers.txt",
		fileNew = "fileNew.txt",

		/***	User Input Strings	-	-	-	-	-	-	-	-	-	-	***/
		userName = "Player",
		userString = "0";

	/** 	Initialize Private Bools for Game Class	-	-	-	-	-	-	 **/
	bool
		/***	Game Value Bools	-	-	-	-	-	-	-	-	-	-	***/
		userIntisInt = false,
		userStringisString = false;

	/*  	INITIALIZE PRIVATE FUNCTIONS FOR GAME CLASS	-	-	-	-	-	  */
	/** 	Initialize New Private Functions	-	-	-	-	-	-	-	 **/
	//
};

/******************************************************************************
 *                                CLASS DEFINITIONS                           *
 ******************************************************************************/

/******************************************************************************
 *                               GLOBAL DEFINITIONS                           *
 ******************************************************************************/

/******************************************************************************
 *                               GLOBAL DEFINITIONS                           *
 ******************************************************************************/

#endif
