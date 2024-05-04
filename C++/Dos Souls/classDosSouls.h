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

// Initialize Const Variable(s) for Game
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
	mLINES{12},	  // Specify Maximum amount of Menu Lines
	mCOLS{4},	  // Specify Maximum amount of Menu Line Columns
	mLABELS{4},	  // Specify Maximum amount of Menu Labels
	mLCOLS{3},	  // Specify Maximum amount of Menu Label Columns
	uMENUS{5},	  // Specify Maximum amount of Ui Screens
	uLINES{12},	  // Specify Maximum amount of Ui Screen Lines
	uCOLS{4},	  // Specify Maximum amount of Ui Screen Line Columns
	uLABELS{2},	  // Specify Maximum amount of Ui Screen Labels
	uLCOLS{3},	  // Specify Maximum amount of Ui Screen Label Columns
	wSIZE{4},	  // Specify Size of Weapon Array
	aSIZE{4},	  // Specify Size of Armor Array
	pSIZE{1},	  // Specify Size of Person Array
	fSIZE{10},	  // Specify Size of Floor Array
	fLOOT{500},	  // Specify Minimum amount of Money Player gets for beating Floor
	eLOOT{250};	  // Specify Minimum amount of Money Player gets for killing Enemy

// Initialize Class for Game
class Game
{
public:
	// Initialize Structs(s) for Game
	struct Weapon
	{
		// Initialize Variable(s) for Weapon
		string							   // Initialize String(s) for storing String(s)
			weaponName = "Bare Hands",	   // Specify Name of Weapon
			weaponBuff = "No Weapon Buff"; // Specify Buff of Weapon
		double							   // Initialize Double(s) for storing Double(s)
			weaponDamage = 20,			   // Specify Damage of Weapon
			weaponPrice = 0;			   // Specify Price of Weapon
		int								   // Initialize Int(s) for storing Int(s)
			weaponType = 0;				   // Specify Type of Weapon
	};

	struct Armor
	{
		// Initialize Variable(s) for Armor
		string							 // Initialize String(s) for storing String(s)
			armorName = "Nothing",		 // Specify Name of Armor
			armorBuff = "No Armor Buff"; // Specify Buff of Armor
		double							 // Initialize Double(s) for storing Double(s)
			armorDefense = 10,			 // Specify Defense of Armor
			armorPrice = 0;				 // Specify Price of Armor
		int								 // Initialize Int(s) for storing Int(s)
			armorType = 0;				 // Specify Type of Armor
	};

	struct Person
	{
		// Initialize Variable(s) for Person
		string					   // Initialize String(s) for storing String(s)
			personName = "Person"; // Specify Name of Person
		double					   // Initialize Double(s) for storing Double(s)
			personHealth = hMAX,   // Specify Health of Person
			personStamina = sMAX,  // Specify Stamina of Person
			personMoney = 0;	   // Specify Money of Person
		int						   // Initialize Int(s) for storing Int(s)
			personIndex = 0,	   // Specify Index of Person
			personNumber = 0,	   // Specify Number of Person
			personWeapon = 0,	   // Specify Weapon Equipped to Person
			personArmor = 0;	   // Specify Armor Equipped to Person
		bool					   // Initialize Bool(s) for storing Bool(s)
			isPlayer = false,	   // Specify if Person is Player
			isRecovering = true,   // Specify if Person is Recovering
			isAttacking = false,   // Specify if Person is Attacking
			isBlocking = false,	   // Specify if Person is Blocking
			isDodging = false,	   // Specify if Person is Dodging
			isWaiting = false;	   // Specify if Person is Waiting

		// Initialize Array(s) for Person
		int
			//*rngArray = new int[rngASIZE]{},			// Establish Dynamic Array for RNG
			rngArray[rngASIZE]{1}, // Establish an Array for RNG
			//*choiceArray = new int[rngASIZE]{}; 		// Establish Dynamic Array for Random Choices
			choiceArray[rngASIZE]{1}; // Establish Array for Random Choices

		// Initialize Vector(s) for Person
		vector<Weapon> Weapons; // Initialize Weapon Vector for Weapons
		vector<Armor> Armors;	// Initialize Armor Vector for Armors

		// OVERLOAD FUNCTIONS
		// Function to Overload Operator '==' for Person to Evaluate for Combat Tie
		// Accepts 1 Person Parameter
		// Returns Bool, passes Data by Member Access
		bool operator==(Person &Person2)
		{
			// Initialize Variable(s) for Person's operator==()
			bool combatTie = false; // Initialize Bool(s) for storing Bool Data

			// If Person 1 and Person 2 are Attacking, Combat is Tied
			if (this->isAttacking == true && Person2.isAttacking == true)
			{
				combatTie = true;
			}

			// If Person 1 and Person 2 are Blocking, Combat is Tied
			else if (this->isBlocking == true && Person2.isBlocking == true)
			{
				combatTie = true;
			}

			// If Person 1 and Person 2 are Dodging, Combat is Tied
			else if (this->isDodging == true && Person2.isDodging == true)
			{
				combatTie = true;
			}

			// If Person 1 and Person 2 are Waiting, Combat is Tied
			else if (this->isWaiting == true && Person2.isWaiting == true)
			{
				combatTie = true;
			}

			// If Person 1 and Person 2 are Not doing Same Action, Combat is Not Tied
			else
			{
				combatTie = false;
			}

			// Return Combat Tie as Bool
			return combatTie;
		}

		// Function to Overload Operator '!=' for Person to Evaluate for Combat Not Tie
		// Accepts 1 Person Parameter
		// Returns Bool, passes Data by Member Access
		bool operator!=(Person &Person2)
		{
			// Initialize Variable(s) for Person's operator!=()
			bool combatNotTie = false; // Initialize Bool(s) for storing Bool Data

			// If Person 1 is Attacking and Person 2 is Not, Combat is Not Tied
			if (this->isAttacking == true && Person2.isAttacking == false)
			{
				combatNotTie = true;
			}

			// If Person 1 is Blocking and Person 2 is Not, Combat is Not Tied
			else if (this->isBlocking == true && Person2.isBlocking == false)
			{
				combatNotTie = true;
			}

			// If Person 1 is Dodging and Person 2 is Not, Combat is Not Tied
			else if (this->isDodging == true && Person2.isDodging == false)
			{
				combatNotTie = true;
			}

			// If Person 1 is Waiting and Person 2 is Not, Combat is Not Tied
			else if (this->isWaiting == true && Person2.isWaiting == false)
			{
				combatNotTie = true;
			}

			// If Person 1 and Person 2 are doing Same Action, Combat is Tied
			else
			{
				combatNotTie = false;
			}

			// Return Combat Not Tie as Bool
			return combatNotTie;
		}

		// Function to Overload Operator '<=' for Person to Evaluate for Combat Loss
		// Accepts 1 Person Parameter
		// Returns Bool, passes Data by Member Access
		bool operator<=(Person &Person2)
		{
			// Initialize Variable(s) for Person's operator<=()
			bool combatLoss = false; // Initialize Bool(s) for storing Bool Data

			// If Person 1 is Attacking and Person 2 is Dodging, Combat is Loss
			if (this->isAttacking == true && Person2.isDodging == true)
			{
				combatLoss = true;
			}

			// If Person 1 is Blocking and Person 2 is Attacking, Combat is Loss
			else if (this->isBlocking == true && Person2.isAttacking == true)
			{
				combatLoss = true;
			}

			// If Person 1 is Dodging and Person 2 is Blocking, Combat is Loss
			else if (this->isDodging == true && Person2.isBlocking == true)
			{
				combatLoss = true;
			}

			// If Person 1 is Waiting and Person 2 is Attacking, Combat is Loss
			else if (this->isWaiting == true && Person2.isAttacking == true)
			{
				combatLoss = true;
			}

			// If Person 1 is Not doing Losing Action against Person 2, Combat is Not Loss
			else
			{
				combatLoss = false;
			}

			// Return Combat Loss as Bool
			return combatLoss;
		}

		// Function to Overload Operator '>=' for Person to Evaluate for Combat Win
		// Accepts 1 Person Parameter
		// Returns Bool, passes Data by Member Access
		bool operator>=(Person &Person2)
		{
			// Initialize Variable(s) for Person's operator>=()
			bool combatWin = false; // Initialize Bool(s) for storing Bool Data

			// If Person 1 is Attacking and Person 2 is Blocking, Combat is Win
			if (this->isAttacking == true && Person2.isBlocking == true)
			{
				combatWin = true;
			}

			// If Person 1 is Blocking and Person 2 is Dodging, Combat is Win
			else if (this->isBlocking == true && Person2.isDodging == true)
			{
				combatWin = true;
			}

			// If Person 1 is Dodging and Person 2 is Attacking, Combat is Win
			else if (this->isDodging == true && Person2.isAttacking == true)
			{
				combatWin = true;
			}

			// If Person 1 is Attacking and Person 2 is Waiting, Combat is Win
			else if (this->isAttacking == true && Person2.isWaiting == true)
			{
				combatWin = true;
			}

			// If Person 1 is Not doing Winning Action against Person 2, Combat is Not Win
			else
			{
				combatWin = false;
			}

			// Return Combat Win as Bool
			return combatWin;
		}

		// Function to Overload Operator '+=' for Person to Deal Damage to Person 2
		// Accepts 1 Person Parameter
		// Returns Void, passes Data by Member Access
		void operator+=(Person &Person2)
		{
			// Check if Person 2 is Blocking
			if (Person2.isBlocking == true)
			{
				// If Person 2 is Blocking, Deal Full Damage divided by bBUFF
				Person2.personHealth -= ((this->Weapons.at(this->personWeapon).weaponDamage - Person2.Armors.at(Person2.personArmor).armorDefense) / bBUFF);

				// If Person 2 Blocks the Attack, Take Stamina Cost of Blocking from Person 2
				Person2.personStamina -= bCOST;

				// If Person 2 Blocks the Attack and Person 2's Stamina Drops to 0, Person 1 Attacks Person 2 again, Deal Full Damage
				if (Person2.personStamina <= 0)
				{
					Person2.personStamina = 0; // Don't let Person 2's Stamina go Below 0
					Person2.personHealth -= (this->Weapons.at(this->personWeapon).weaponDamage - Person2.Armors.at(Person2.personArmor).armorDefense);
				}
			}

			// If Person 2 is Not Blocking, Deal Full Damage
			else
			{
				Person2.personHealth -= (this->Weapons.at(this->personWeapon).weaponDamage - Person2.Armors.at(Person2.personArmor).armorDefense);
			}

			// Return Void
			return;
		}

		// Function to Overload Operator '-=' for Person to Take Damage from Person 2
		// Accepts 1 Person Parameter
		// Returns Void, passes Data by Member Access
		void operator-=(Person &Person2)
		{
			// Check if Person 1 is Blocking
			if (this->isBlocking == true)
			{
				// If Person 1 is Blocking, Deal Full Damage divided by bBUFF
				this->personHealth -= ((Person2.Weapons.at(Person2.personWeapon).weaponDamage - this->Armors.at(this->personArmor).armorDefense) / bBUFF);

				// If Person 1 Blocks the Attack, Take Stamina Cost of Blocking from Person 1
				this->personStamina -= bCOST;

				// If Person 1 Blocks the Attack and Person 1's Stamina Drops to 0, Person 2 Attacks Person 1 again, Deal Full Damage
				if (this->personStamina <= 0)
				{
					this->personStamina = 0; // Don't let Person 1's Stamina go Below 0
					this->personHealth -= (Person2.Weapons.at(Person2.personWeapon).weaponDamage - this->Armors.at(this->personArmor).armorDefense);
				}
			}

			// If Person 1 is Not Blocking, Deal Full Damage
			else
			{
				this->personHealth -= (Person2.Weapons.at(Person2.personWeapon).weaponDamage - this->Armors.at(this->personArmor).armorDefense);
			}

			// Return Void
			return;
		}

		// Function to Overload Operator '<' for Person to Evaluate if Health is Less than Person 2
		// Accepts 1 Person Parameter
		// Returns Bool, passes Data by Member Access
		bool operator<(Person &Person2)
		{
			// Initialize Variable(s) for Person's operator<()
			bool healthLess = false; // Initialize Bool(s) for storing Bool Data

			// If Person 1's Health is Less than Person 2's Health, Health is Less
			if (this->personHealth < Person2.personHealth)
			{
				healthLess = true;
			}

			// If Person 1's Health is Not Less than Person 2's Health, Health is Not Less
			else
			{
				healthLess = false;
			}

			// Return Health is Less as Bool
			return healthLess;
		}

		// Function to Overload Operator '>' for Person to Evaluate if Health is More than Person 2
		// Accepts 1 Person Parameter
		// Returns Bool, passes Data by Member Access
		bool operator>(Person &Person2)
		{
			// Initialize Variable(s) for Person's operator>()
			bool healthMore = false; // Initialize Bool(s) for storing Bool Data

			// If Person 1's Health is More than Person 2's Health, Health is More
			if (this->personHealth > Person2.personHealth)
			{
				healthMore = true;
			}

			// If Person 1's Health is Not More than Person 2's Health, Health is Not More
			else
			{
				healthMore = false;
			}

			// Return Health is More as Bool
			return healthMore;
		}

		// Function to Overload Operator '+' for Person to Give Person 1 Person 2's Loot after Kill
		// Accepts 1 Person Parameter
		// Returns Void, passes Data by Member Access
		void operator+(Person &Person2)
		{
			// Recover Person 1's Health and Stamina after Kill
			this->personHealth += (hMAX / hSTEAL);
			if (this->personHealth >= hMAX)
			{
				this->personHealth = hMAX; // Don't let Person 1's Health go Above hMAX
			}
			this->personStamina = sMAX;

			// Take that Loser's Money
			this->personMoney += Person2.personMoney;

			// Return Void
			return;
		}

		// Function to Overload Operator '-' for Person to Give Person 1 Person 2's Items after Kill
		// Accepts 1 Person Parameter
		// Returns Void, passes Data by Member Access
		void operator-(Person &Person2)
		{
			// And his Shit too
			this->Weapons.push_back(Person2.Weapons.at(Person2.personWeapon));
			this->Armors.push_back(Person2.Armors.at(Person2.personArmor));

			// Return Void
			return;
		}

		// Function to Overload Operator '=' for Person
		// Accepts 1 Person Parameter
		// Returns Void, passes Data by Member Access
		void operator=(Person &Person2)
		{
			// Fill Person 1 with Person 2's Data
			this->personName = Person2.personName; // Specify Name of Person
			// this->personHealth = Person2.personHealth;	 // Specify Health of Person
			// this->personStamina = Person2.personStamina; // Specify Stamina of Person
			this->personMoney = Person2.personMoney;   // Specify Money of Person
			this->personIndex = Person2.personIndex;   // Specify Index of Person
			this->personNumber = Person2.personNumber; // Specify Number of Person
			this->personWeapon = Person2.personWeapon; // Specify Weapon Equipped to Person
			this->personArmor = Person2.personArmor;   // Specify Armor Equipped to Person
			this->isPlayer = Person2.isPlayer;		   // Specify if Person is Player

			// Return Void
			return;
		}
	};

	struct Floor
	{
		// Initialize Variable(s) for Floor
		string					 // Initialize String(s) for storing String(s)
			floorName = "Floor"; // Specify Name of Floor
		double					 // Initialize Double(s) for storing Double(s)
			floorModifier = 1,	 // Specify Modifier of Floor
			floorMoney = fLOOT;	 // Specify Reward of Floor
		int						 // Initialize Int(s) for storing Int(s)
			floorIndex = 0,		 // Specify Index of Floor
			floorNumber = 1,	 // Specify Number of Floor
			floorLevel = 1;		 // Specify Level of Floor
		bool					 // Initialize Bool(s) for storing Bool(s)
			isStore = true;		 // Specify if Store is Available on Floor

		// Initialize Vector(s) for Floor
		vector<Person> Enemies; // Initialize Person Vector for Floor Enemies

		// OVERLOAD FUNCTIONS
		// Function to Overload Operator '=' for Floor
		// Accepts 1 Floor Parameter
		// Returns Void, passes Data by Member Access
		void operator=(Floor &Floor2)
		{
			// Fill Floor 1 with Floor 2's Data
			this->floorName = Floor2.floorName;			// Specify Name of Floor
			this->floorModifier = Floor2.floorModifier; // Specify Modifier of Floor
			this->floorMoney = Floor2.floorMoney;		// Specify Reward of Floor
			this->floorIndex = Floor2.floorIndex;		// Specify Index of Floor
			this->floorNumber = Floor2.floorNumber;		// Specify Number of Floor
			this->floorLevel = Floor2.floorLevel;		// Specify Level of Floor
			this->isStore = Floor2.isStore;				// Specify if Store is Available on Floor

			// Return Void
			return;
		}
	};

	// Initialize Vector(s) for Game
	vector<Floor> Floors;	// Initialize Floor Vector for Floors
	vector<Person> Players; // Initialize Person Vector for Players

	// Initialize Array(s) for Menus
	string (*menuLabels)[mLCOLS] = new string[mLABELS][mLCOLS]{};			   // Establish a Dynamic 2D String Array for Menu Labels
	string (*menuLines)[mLINES][mCOLS] = new string[mMENUS][mLINES][mCOLS]{};  // Establish a Dynamic 2D String Array for Menu Lines
	int (*menuLinesNumbers)[mLINES][mCOLS] = new int[mMENUS][mLINES][mCOLS]{}; // Establish a Dynamic 2D String Array for Menu Numbers
	bool (*menuLinesSelected)[mCOLS] = new bool[mLINES][mCOLS]{};			   // Establish a Dynamic 2D String Array for Menu Selections

	// Initialize Array(s) for Ui
	string (*uiLabels)[uLCOLS] = new string[uLABELS][uLCOLS]{};				 // Establish a Dynamic 2D String Array for Menu Labels
	string (*uiLines)[uLINES][uCOLS] = new string[uMENUS][uLINES][uCOLS]{};	 // Establish a Dynamic 2D String Array for Menu Lines
	int (*uiLinesNumbers)[uLINES][uCOLS] = new int[uMENUS][uLINES][uCOLS]{}; // Establish a Dynamic 2D String Array for Menu Numbers
	bool (*uiLinesSelected)[uCOLS] = new bool[uLINES][uCOLS]{};				 // Establish a Dynamic 2D String Array for Menu Numbers

	// Initialize Array(s) for Items
	// string *weaponLabels = new string[wSIZE]{};		 // Establish a dynamic array for Weapon Labels
	// string *armorLabels = new string[aSIZE]{};		 // Establish a dynamic array for Armor Labels
	// string *personLabels = new string[pSIZE]{};		 // Establish a dynamic array for Person Labels
	// string *floorNames = new string[fSIZE]{}; // Establish a dynamic array for Floor Labels

	// Constructor with Default Parameters
	Game()
	{
		// Add Game Data to Arrays
		dsFiles();

		// Start Menus
		dsMenus(1);
		dsMenus(2);
		dsMenus(3);
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
		delete[] menuLabels;
		menuLabels = nullptr;
		delete[] menuLines;
		menuLines = nullptr;
		delete[] menuLinesNumbers;
		menuLinesNumbers = nullptr;
		delete[] menuLinesSelected;
		menuLinesSelected = nullptr;
		delete[] uiLabels;
		uiLabels = nullptr;
		delete[] uiLines;
		uiLines = nullptr;
		delete[] uiLinesNumbers;
		uiLinesNumbers = nullptr;
		delete[] uiLinesSelected;
		uiLinesSelected = nullptr;
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

	// FILE FUNCTIONS
	void dsFiles();

	// MENU FUNCTIONS
	int dsMenuDisplay(int, int = 1, int = mLINES, int = 1, int = 0);
	void gameIntro();
	void gameRules();
	void gameSettings();
	void gameFloorIntro();
	void gameOutro();
	void dsMenus(int, int = 1);

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
	// Initialize Private Int(s) for Game
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
	// Initialize Private String(s) for Game
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
	// Initialize Private Bool(s) for Game
	bool
		userIntisInt = false,
		userStringisString = false;
};

#endif
