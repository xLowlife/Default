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
#ifndef CLASS_DOS_SOULS_H
#define CLASS_DOS_SOULS_H

#include <stdlib.h>
#include <cctype> // isdigit()
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random> // Mersenne Twister
#include <string>
#include <cstring>
#include <vector>
using namespace std;

const int
	hMAX{100},	  // Specify Maximum amount of Health
	hSTEAL{2},	  // Specify Maximum amount of Life Steal
	sMAX{100},	  // Specify Maximum amount of Stamina
	sGAIN{10},	  // Specify Base amount of Stamina Recovery
	sLGAIN{3},	  // Specify Bonus amount of Stamina Recovery for Light Armor
	sMGAIN{2},	  // Specify Bonus amount of Stamina Recovery for Medium Armor
	sHGAIN{1},	  // Specify Bonus amount of Stamina Recovery for Heavy Armor
	aCOST{10},	  // Specify Cost of Attack
	bCOST{25},	  // Specify Cost of Block
	bBUFF{2},	  // Specify Damage Reduction of Block
	dCOST{50},	  // Specify Cost of Dodge
	rngASIZE{10}, // Specify Size of Person Arrays
	rngPSIZE{4},  // Specify Size of Player rngArray
	rngESIZE{3},  // Specify Size of Enemy rngArray
	mMENUS{5},	  // Specify Maximum amount of Menus
	mLINES{12},	  // Specify amount of Menu Lines
	mCOLS{4},	  // Specify amount of Menu Array Columns
	uMENUS{5},	  // Specify Maximum amount of Menus
	uLINES{12},	  // Specify amount of Menu Lines
	uCOLS{4},	  // Specify amount of Menu Array Columns
	wSIZE{4},	  // Specify Size of Weapon Array
	aSIZE{4},	  // Specify Size of Armor Array
	pSIZE{1},	  // Specify Size of Person Array
	fSIZE{10},	  // Specify Size of Floor Array
	fLOOT{500},	  // Specify Minimum amount of Money Player gets for beating Floor
	eLOOT{250};	  // Specify Minimum amount of Money Player gets for killing Enemy

class Game
{
public:
	struct Weapon
	{
		string
			weaponName = "Bare Hands",	   // Specify Name of Weapon
			weaponBuff = "No Weapon Buff"; // Specify Buff of Weapon
		double
			weaponDamage = 20, // Specify Damage of Weapon
			weaponPrice = 0;   // Specify Price of Weapon
		int
			weaponType = 0; // Specify Type of Weapon
	};

	struct Armor
	{
		string
			armorName = "Nothing",		 // Specify Name of Armor
			armorBuff = "No Armor Buff"; // Specify Buff of Armor
		double
			armorDefense = 10, // Specify Defense of Armor
			armorPrice = 0;	   // Specify Price of Armor
		int
			armorType = 0; // Specify Type of Armor
	};

	struct Person
	{
		string
			personName = "Person"; // Specify Name of Person
		double
			personHealth = hMAX,  // Specify Health of Person
			personStamina = sMAX, // Specify Stamina of Person
			personMoney = 0;	  // Specify Money of Person
		int
			personIndex = 0,  // Specify Index of Person
			personNumber = 0, // Specify Number of Person
			personWeapon = 0, // Specify Weapon Equipped to Person
			personArmor = 0;  // Specify Armor Equipped to Person
		bool
			isPlayer = false,	 // Specify if Person is Player
			isRecovering = true, // Specify if Person is Recovering
			isAttacking = false, // Specify if Person is Attacking
			isBlocking = false,	 // Specify if Person is Blocking
			isDodging = false,	 // Specify if Person is Dodging
			isWaiting = false;	 // Specify if Person is Waiting
		int
			//*rngArray = new int[rngASIZE]{},			// Establish Dynamic Array for RNG
			rngArray[rngASIZE]{1}, // Establish an Array for RNG
			//*choiceArray = new int[rngASIZE]{}; 		// Establish Dynamic Array for Random Choices
			choiceArray[rngASIZE]{1}; // Establish Array for Random Choices
		vector<Weapon> Weapons;		  // Initialize Weapon Vector for Weapons
		vector<Armor> Armors;		  // Initialize Armor Vector for Armors

		// Operator Overload Functions
		// Function to Evaluate for Combat Tie
		// Accepts Person parameter
		// Returns void, passes data by member access
		bool operator==(Person &Enemy)
		{
			bool combatTie = false;
			if (isAttacking == true && Enemy.isAttacking == true)
			{
				combatTie = true;
			}
			else if (isBlocking == true && Enemy.isBlocking == true)
			{
				combatTie = true;
			}
			else if (isDodging == true && Enemy.isDodging == true)
			{
				combatTie = true;
			}
			else if (isWaiting == true && Enemy.isWaiting == true)
			{
				combatTie = true;
			}
			else
			{
				combatTie = false;
			}
			return combatTie;
		}

		// Function to Evaluate for Combat Not Tied
		// Accepts Person parameter
		// Returns void, passes data by member access
		bool operator!=(Person &Enemy)
		{
			bool combatNotTie = false;
			if (isAttacking == true && Enemy.isAttacking == false)
			{
				combatNotTie = true;
			}
			else if (isBlocking == true && Enemy.isBlocking == false)
			{
				combatNotTie = true;
			}
			else if (isDodging == true && Enemy.isDodging == false)
			{
				combatNotTie = true;
			}
			else if (isWaiting == true && Enemy.isWaiting == false)
			{
				combatNotTie = true;
			}
			else
			{
				combatNotTie = false;
			}
			return combatNotTie;
		}

		// Function to Evaluate for Combat Player Loss
		// Accepts Person parameter
		// Returns void, passes data by member access
		bool operator<=(Person &Enemy)
		{
			bool combatLoss = false;
			if (isAttacking == true && Enemy.isDodging == true)
			{
				combatLoss = true;
			}
			else if (isBlocking == true && Enemy.isAttacking == true)
			{
				combatLoss = true;
			}
			else if (isDodging == true && Enemy.isBlocking == true)
			{
				combatLoss = true;
			}
			else if (isWaiting == true && Enemy.isAttacking == true)
			{
				combatLoss = true;
			}
			else
			{
				combatLoss = false;
			}
			return combatLoss;
		}

		// Function to Evaluate for Combat Player Win
		// Accepts Person parameter
		// Returns void, passes data by member access
		bool operator>=(Person &Enemy)
		{
			bool combatWin = false;
			if (isAttacking == true)
			{
				if (Enemy.isBlocking == true)
				{
					combatWin = true;
				}
				else if (Enemy.isWaiting == true)
				{
					combatWin = true;
				}
				else
				{
					combatWin = false;
				}
			}
			else if (isBlocking == true && Enemy.isDodging == true)
			{
				combatWin = true;
			}
			else if (isDodging == true && Enemy.isAttacking == true)
			{
				combatWin = true;
			}
			else
			{
				combatWin = false;
			}
			return combatWin;
		}

		// Function to Damage Enemy for Combat Player Win
		// Accepts Person parameter
		// Returns void, passes data by member access
		Person &operator+=(Person &Enemy)
		{
			// Check if Enemy is Blocking
			if (isBlocking == true)
			{
				// If Enemy is Blocking deal Reduced Damage
				(Enemy.personHealth -= (Weapons.at(personWeapon).weaponDamage - Enemy.Armors.at(Enemy.personArmor).armorDefense) / bBUFF);

				// If Blocking the Attack emptys the Enemy's Stamina, gain a free Unblocked Attack
				if ((Enemy.personStamina - bCOST) <= 0)
				{
					Enemy.personHealth -= (Weapons.at(personWeapon).weaponDamage - Enemy.Armors.at(Enemy.personArmor).armorDefense);
				}
			}
			else
			{
				// If Enemy is not Blocking or Dodging, Attack the Enemy
				Enemy.personHealth -= (Weapons.at(personWeapon).weaponDamage - Enemy.Armors.at(Enemy.personArmor).armorDefense);
			}

			return *this;
		}

		// Function to Damage Player for Combat Player Loss
		// Accepts Person parameter
		// Returns void, passes data by member access
		Person &operator-=(Person &Enemy)
		{
			// Check if Player is Blocking
			if (isBlocking == true)
			{
				// If Player is Blocking deal Reduced Damage
				(personHealth -= (Enemy.Weapons.at(Enemy.personWeapon).weaponDamage - Armors.at(personArmor).armorDefense) / bBUFF);
				// If Blocking the Attack emptys the Player's Stamina, gain a free Unblocked Attack
				if ((personStamina - bCOST) <= 0)
				{
					personHealth -= (Enemy.Weapons.at(Enemy.personWeapon).weaponDamage - Armors.at(personArmor).armorDefense);
				}
			}
			else
			{
				// If Player is not Blocking or Dodging, Attack the Player
				personHealth -= (Enemy.Weapons.at(Enemy.personWeapon).weaponDamage - Armors.at(personArmor).armorDefense);
			}
			return *this;
		}

		// Function to Evaluate if Player has less Health than Enemy
		// Accepts Person parameter
		// Returns void, passes data by member access
		Person &operator<(Person &Enemy)
		{
			bool lesser = false;
			if (personHealth < Enemy.personHealth)
			{
				lesser = true;
				return Enemy;
			}
			else
			{
				lesser = false;
				return *this;
			}
		}

		// Function to Evaluate if Player has more Health than Enemy
		// Accepts Person parameter
		// Returns void, passes data by member access
		Person &operator>(Person &Enemy)
		{
			bool greater = false;
			if (personHealth > Enemy.personHealth)
			{
				greater = true;
				return *this;
			}
			else
			{
				greater = false;
				return Enemy;
			}
		}

		// Function to give Player Enemy's Money after Combat Player Win
		// Accepts Person parameter
		// Returns void, passes data by member access
		void operator+(Person &Enemy)
		{
			// Take that Loser's Money
			personHealth = (personHealth + (hMAX / hSTEAL));
			personMoney = (personMoney + Enemy.personMoney);
			return;
		}

		// Function to give Player Enemy's Items after Combat Player Win
		// Accepts Person parameter
		// Returns void, passes data by member access
		void operator-(Person &Enemy)
		{
			// And his Shit too
			Weapons.push_back(Enemy.Weapons.at(Enemy.personWeapon));
			Armors.push_back(Enemy.Armors.at(Enemy.personArmor));
			return;
		}

		void output(ostream &osObj)
		{
			osObj << '(' << personHealth << ')';
		}
	};

	struct Floor
	{
		string
			floorName = "Floor"; // Specify Name of Floor
		double
			floorModifier = 1,	// Specify Modifier of Floor
			floorMoney = fLOOT; // Specify Reward of Floor
		int
			floorIndex = 0,	 // Specify Index of Floor
			floorNumber = 1, // Specify Number of Floor
			floorLevel = 1;	 // Specify Level of Floor
		bool
			isStore = true; // Specify if Store is Available on Floor

		vector<Person> Enemies; // Initialize Person Vector for Enemies
	};

	vector<Floor> Floors;	// Initialize Floor Vector for Floors
	vector<Person> Players; // Initialize Person Vector for Players

	string (*menuLines)[mLINES][mCOLS] = new string[mMENUS][mLINES][mCOLS]{}; // Establish a Dynamic 2D String Array for Menu Lines
	int (*menuLinesNumbers)[mCOLS] = new int[mLINES][mCOLS]{};				  // Establish a Dynamic 2D String Array for Menu Numbers
	bool (*menuLinesSelected)[mCOLS] = new bool[mLINES][mCOLS]{};			  // Establish a Dynamic 2D String Array for Menu Selections
	string (*uiLines)[mLINES][mCOLS] = new string[mMENUS][mLINES][mCOLS]{};	  // Establish a Dynamic 2D String Array for Menu Lines
	int (*uiLinesNumbers)[mCOLS] = new int[mLINES][mCOLS]{};				  // Establish a Dynamic 2D String Array for Menu Numbers
	bool (*uiLinesSelected)[mCOLS] = new bool[mLINES][mCOLS]{};				  // Establish a Dynamic 2D String Array for Menu Selections
	// string *weaponLabels = new string[wSIZE]{};		 // Establish a dynamic array for Weapon Labels
	// string *armorLabels = new string[aSIZE]{};		 // Establish a dynamic array for Armor Labels
	// string *personLabels = new string[pSIZE]{};		 // Establish a dynamic array for Person Labels
	// string *floorNames = new string[fSIZE]{}; // Establish a dynamic array for Floor Labels

	// Constructor with Default Parameters
	Game()
	{
		// Add Game Data to Arrays
		gameAddData();

		// Start Menus
		gameMenus(1);
		gameMenus(2);
		gameMenus(3);
		// gameIntro();
		// gameRules();
		// gameSettings();

		// Build Game
		dsGameNew();

		// Do Combat while Player's Characters are Not all Dead or Player has Not Won
		do
		{
			gameCombat();
		} while (Players.at(-1).personHealth > 0 && Floors.at(-1).Enemies.at(-1).personHealth > 0);

		// Start End Screen
		// gameOutro();
	}

	// Destructor with Default Parameters
	~Game()
	{
		// Wrap Up
		delete[] menuLines;
		menuLines = nullptr;
		//  delete[] weaponLabels;
		//  weaponLabels = nullptr;
		//  delete[] armorLabels;
		//  armorLabels = nullptr;
		//  delete[] personsLabels;
		//  personsLabels = nullptr;
		//  delete[] floorNames;
		//  floorNames = nullptr;
		//  delete[] Players.at(0).rngArray;
		//  Players.at(0).rngArray = nullptr;
		//  delete[] Players.at(0).choiceArray;
		//  Players.at(0).choiceArray = nullptr;
		//  for (int i = 0; Floors.size(); ++i)
		//{
		//	delete[] Floors.at(i).Enemy.rngArray;
		//	Floors.at(i).Enemy.rngArray = nullptr;
		//	delete[] Floors.at(i).Enemy.choiceArray;
		//	Floors.at(i).Enemy.choiceArray = nullptr;
		// }
	}

	// INTERACT FUNCTIONS
	string dsChoiceString();
	double dsChoiceNumber(int = 0, int = 9);

	// MENU FUNCTIONS
	void gameAddData();
	int gameMenu(int, int = 1, int = mLINES, int = 1, int = 0);
	void gameIntro();
	void gameRules();
	void gameSettings();
	void gameFloorIntro();
	void gameOutro();
	void gameMenus(int, int = 1);

	// UI FUNCTIONS
	void gameUi(int, int = 1, int = mLINES, int = 1, int = 0);

	// SYSTEM FUNCTIONS
	int rndInt(int, int = 1);
	bool rng(int = rngPSIZE);
	Floor dsFloorNew(int = -1);
	Person dsEnemyNew(int = -1);
	Person dsPlayerNew(int = -1);
	void dsGameNew();
	void gameCombat();
	void gameStaminaRecovery();
	void gamePlayerTurn(int, int = 1);
	int gameEnemyAi();
	void gameEnemyTurn();

	// GAME FUNCTIONS
	void gameAddItems();
	void gameProgress();
	void gameCombats();
	void turnAttack();
	void turnBlock();
	void turnDodge();
	void turnWait();
	void turnRun();
	void turnExitGame();
	void enemyAttack();
	void enemyBlock();
	void enemyDodge();
	void enemyWait();
	void turnAttackShow();
	void turnBlockShow();
	void turnDodgeShow();
	void turnWaitShow();
	void enemyAttackShow();
	void enemyBlockShow();
	void enemyDodgeShow();
	void enemyWaitShow();

private:
	// Initialize Private Int(s) for Class
	int
		// Game Settings
		floorDifficulty = 3,
		floorTotal = 10,
		enemyTotal = 1,
		playerTotal = 1,

		// Floor/Person Count
		floorCount = 0,
		enemyCount = 0,
		playerCount = 0,

		// Game Progress
		floorCurrent = 0,
		floorRound = 0,
		enemyCurrent = 0,
		playerCurrent = 0,

		// Game Choices
		enemyChoice = 0,
		playerChoice = 0,

		// Game Stats
		playerFloors = 0,
		playerKills = 0,
		playerWealth = 0,

		// User Int
		userInt = 0;
	// Initialize Private String(s) for Class
	string
		// Game Files
		fileMenus = "fileMenus.txt",
		fileUi = "fileUi.txt",
		fileItems = "fileItems.txt",
		fileFloors = "fileFloors.txt",
		fileEnemies = "fileEnemies.txt",
		filePlayers = "filePlayers.txt",

		// User Name
		userName = "Player",

		// User String
		userString = "0";
	// Initialize Private Bool(s) for Class
	bool
		userIntisInt = false,
		userStringisString = false;
};

#endif
