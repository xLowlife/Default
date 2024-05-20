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
/*  	INCLUDE LIBRARIES FOR FILE	-	-	-	-	-	-	-	-	-	-	  */
#include "classDosSouls.h"
/*  	DEFINE NAMESPACE FOR FILE	-	-	-	-	-	-	-	-	-	-	  */
using namespace std;
/******************************************************************************
 *                               STRUCT DEFINITIONS                           *
 ******************************************************************************/

/*  	DEFINE PUBLIC STRUCTS FOR GAME CLASS	-	-	-	-	-	-	-	  */
/** 	Define Display Screen Structs	-	-	-	-	-	-	-	-	-	 **/
// Struct that stores Line Columns for Display Screen Pages
// Contains Ints, Int Pointers, Doubles, Strings, and Bools
// Defines Struct, passes Data by Member Access
struct Game::sLineCol
{
	/*  	INITIALIZE VARIABLES FOR sLineCol	-	-	-	-	-	-	-	  */
	/** 	Initialize Ints for sLineCol	-	-	-	-	-	-	-	-	 **/
	int
		lcolIndex = (-1),	// Specify sLineCol's Line Column Index
		*lNumPtr = nullptr; // Specify sLineCol's Pointer to Variable Numbers

	/** 	Initialize Doubles for sLineCol	-	-	-	-	-	-	-	-	 **/
	double
		lNum = (-1),		 // Specify sLineCol's Variable Number
		*lDoubPtr = nullptr; // Specify sLineCol's Pointer to Variable Doubles

	/** 	Initialize Strings for sLineCol	-	-	-	-	-	-	-	-	 **/
	string lStr = " "; // Specify sLineCol's Variable String

	/** 	Initialize Bools for sLineCol	-	-	-	-	-	-	-	-	 **/
	bool
		lInfo = false, // Specify sLineCol's Variable State
		lSel = false;  // Specify sLineCol's Selected State
};

// Struct that stores Line Rows for Display Screen Pages
// Contains Ints, Strings, Vectors, and Functions
// Defines Struct, passes Data by Member Access
struct Game::sLine
{
	/*  	INITIALIZE VARIABLES FOR sLine	-	-	-	-	-	-	-	-	  */
	/** 	Initialize Ints for sLine	-	-	-	-	-	-	-	-	-	 **/
	int
		lineIndex = (-1),	 // Specify sLine's Line Index
		lineEmptyNum = (-1); // Specify sLine's Empty Number Value

	/** 	Initialize Strings for sLine	-	-	-	-	-	-	-	-	 **/
	string
		lineName = "Line ", // Specify sLine's Name
		lineEmptyStr = " "; // Specify sLine's Empty String Value

	/*  	INITIALIZE VECTORS FOR sLine	-	-	-	-	-	-	-	-	  */
	vector<sLineCol> sLineCols; // sLineCol Vector for sLine's Line Columns

	/*  	DEFINE FUNCTIONS FOR sLine	-	-	-	-	-	-	-	-	-	  */
	/** 	Define Struct Constructor Functions	-	-	-	-	-	-	-	 **/
	// Default Constructor for sLine
	// Create New Line Column at sLineCols.at(0) to Reserve for Line Data,
	// and Allow me to Access sLineCols with Line Column 1 starting at Index 1
	sLine() { sLineNew(); }

	/** 	Define Struct Vector Functions	-	-	-	-	-	-	-	-	 **/
	// Function to Create New Line Column, and Add to this->sLineCols
	// Accepts No Parameters
	// Returns Void, passes Data by Member Access
	void sLineNew()
	{
		/*  	INITIALIZE VARIABLES FOR sLineNew()	-	-	-	-	-	-	  */
		/** 	Initialize sLineCols for sLineNew()	-	-	-	-	-	-	 **/
		sLineCol newLineCol;
		/***	Push Back sLineCols to this->sLineCols Vector	-	-	-	***/
		this->sLineCols.push_back(newLineCol);

		/*  	RETURN VOID	-	-	-	-	-	-	-	-	-	-	-	-	  */
		return;
	}

	/** 	Define Struct Overload Functions	-	-	-	-	-	-	-	 **/
	// Function to Overload Operator '/' for sLine to Split Strings in Half
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
			/** 	Add 1st Half to Old this->sLineCols.at(-1).lStr	-	-	 **/
			this->sLineCols.at(this->sLineCols.size() - 1).lStr =
				oldString.substr(0, stringHalf);
			/***	Create New Line Column	-	-	-	-	-	-	-	-	***/
			this->sLineNew();

			/** 	Add 2nd Half to New this->sLineCols.at(-1).lStr	-	-	 **/
			this->sLineCols.at(this->sLineCols.size() - 1).lStr =
				oldString.substr(stringHalf);
		}

		/** 	If oldString Length is Odd, Subtract oldString Length by 1	 **/
		else if (oldString.length() >= 3 && (oldString.length() % 2) != 0)
		{
			/*  	SUBTRACT LENGTH OF oldString BY 1, THEN DIVIDE IN HALF	  */
			stringHalf = ((oldString.length() - 1) / 2);
			/** 	Add 1st Half to Old this->sLineCols.at(-1).lStr	-	-	 **/
			this->sLineCols.at(this->sLineCols.size() - 1).lStr =
				oldString.substr(0, stringHalf);
			/***	Create New Line Column	-	-	-	-	-	-	-	-	***/
			this->sLineNew();

			/** 	Add 2nd Half to New this->sLineCols.at(-1).lStr	-	-	 **/
			this->sLineCols.at(this->sLineCols.size() - 1).lStr =
				oldString.substr(stringHalf);
		}

		/** 	If oldString Length is Invalid, Error Without .push_back()	 **/
		else
		{
			cout << "Function: sLine.operator/() Failed" << endl;
		}

		/*  	RETURN VOID	-	-	-	-	-	-	-	-	-	-	-	-	  */
		return;
	}
};

// Struct that stores Pages for Display Screen Chapters
// Contains Ints, Strings, and Vectors
// Defines Struct, passes Data by Member Access
struct Game::sPage
{
	/*  	INITIALIZE VARIABLES FOR sPage	-	-	-	-	-	-	-	-	  */
	/** 	Initialize Ints for sPage	-	-	-	-	-	-	-	-	-	 **/
	int
		pageIndex = (-1), // Specify sPage's Page Index
		pageRows = (-1),  // Specify sPage's Line Row Amount
		pageCols = (-1),  // Specify sPage's Line Column Amount
		pageMin = (-1),	  // Specify sPage's Min Choice
		pageMax = (-1);	  // Specify sPage's Max Choice

	/** 	Initialize Strings for sPage	-	-	-	-	-	-	-	-	 **/
	string
		pageName = "New Page",	 // Specify sPage's Name
		pageSel = " [SELECTED]"; // Specify sPage's Selected Message

	/*  	INITIALIZE VECTORS FOR sPage	-	-	-	-	-	-	-	-	  */
	vector<sLine> sLines; // sLine Vector for sPage's Line Rows
};

// Struct that stores Chapters for Display Screens
// Contains Ints, Strings, Vectors, and Vectors of Pointers
// Defines Struct, passes Data by Member Access
struct Game::sChapter
{
	/*  	INITIALIZE VARIABLES FOR sChapter	-	-	-	-	-	-	-	  */
	/** 	Initialize Ints for sChapter	-	-	-	-	-	-	-	-	 **/
	int chapIndex = (-1); // Specify sChapter's Chapter Index

	/** 	Initialize Strings for sChapter	-	-	-	-	-	-	-	-	 **/
	string chapName = "New Chapter"; // Specify sChapter's Name

	/*  	INITIALIZE VECTORS FOR sChapter	-	-	-	-	-	-	-	-	  */
	vector<sPage> sPages;	   // sPage Vector for sChapter's Pages
	vector<int *> chapPtrs;	   // Int Pointer Vector for sChapter's Variable Data
	vector<double *> doubPtrs; // Int Pointer Vector for sChapter's Variable Data
};

/** 	Define Game Item Structs	-	-	-	-	-	-	-	-	-	-	 **/
// Struct that stores Weapons for for Game Characters
// Contains Ints, Doubles, and Strings
// Defines Struct, passes Data by Member Access
struct Game::Weapon
{
	/*  	INITIALIZE VARIABLES FOR Weapon	-	-	-	-	-	-	-	-	  */
	/** 	Initialize Ints for Weapon	-	-	-	-	-	-	-	-	-	 **/
	int weaponType = 0; // Specify Type of Weapon

	/** 	Initialize Doubles for Weapon	-	-	-	-	-	-	-	-	 **/
	double
		weaponDamage = 20, // Specify Damage of Weapon
		weaponPrice = 0;   // Specify Price of Weapon

	/** 	Initialize Strings for Weapon	-	-	-	-	-	-	-	-	 **/
	string
		weaponName = "Bare Hands",	   // Specify Name of Weapon
		weaponBuff = "No Weapon Buff"; // Specify Buff of Weapon
};

// Struct that stores Armors for Game Characters
// Contains Ints, Doubles, and Strings
// Defines Struct, passes Data by Member Access
struct Game::Armor
{
	/*  	INITIALIZE VARIABLES FOR Armor	-	-	-	-	-	-	-	-	  */
	/** 	Initialize Ints for Armor	-	-	-	-	-	-	-	-	-	 **/
	int armorType = 0; // Specify Type of Armor

	/** 	Initialize Doubles for Armor	-	-	-	-	-	-	-	-	 **/
	double
		armorDefense = 10, // Specify Defense of Armor
		armorPrice = 0;	   // Specify Price of Armor

	/** 	Initialize Strings for Armor	-	-	-	-	-	-	-	-	 **/
	string
		armorName = "Nothing",		 // Specify Name of Armor
		armorBuff = "No Armor Buff"; // Specify Buff of Armor
};

/** 	Define Game Character Structs	-	-	-	-	-	-	-	-	-	 **/
// Struct that stores Game Characters for Game Class
// Contains Ints, Doubles, Strings, Bools, Arrays, Vectors, and Functions
// Defines Struct, passes Data by Member Access
struct Game::Person
{
	/*  	INITIALIZE VARIABLES FOR Person	-	-	-	-	-	-	-	-	  */
	/** 	Initialize Ints for Person	-	-	-	-	-	-	-	-	-	 **/
	int
		personIndex = 0,  // Specify Index of Person
		personNumber = 0, // Specify Number of Current Person
		personWeapon = 0, // Specify Weapon Equipped to Person
		personArmor = 0;  // Specify Armor Equipped to Person

	/** 	Initialize Doubles for Person	-	-	-	-	-	-	-	-	 **/
	double
		personhMAX = gameConsts[hMAX],	  // Specify Health Maximum of Person
		personHealth = gameConsts[hMAX],  // Specify Health of Person
		personStamina = gameConsts[sMAX], // Specify Stamina of Person
		personMoney = 0;				  // Specify Money of Person

	/** 	Initialize Strings for Person	-	-	-	-	-	-	-	-	 **/
	string personName = "Person"; // Specify Name of Person

	/** 	Initialize Bools for Person	-	-	-	-	-	-	-	-	-	 **/
	bool
		isPlayer = false,	 // Specify if Person is Player
		isRecovering = true, // Specify if Person is Recovering
		isAttacking = false, // Specify if Person is Attacking
		isBlocking = false,	 // Specify if Person is Blocking
		isDodging = false,	 // Specify if Person is Dodging
		isWaiting = false;	 // Specify if Person is Waiting

	/*  	INITIALIZE ARRAYS FOR Person	-	-	-	-	-	-	-	-	  */
	int
		rngArray[3]{},	  // Initialize Int Array for RNG
		choiceArray[4]{}; // Initialize Int Array for Random Choices

	/*  	INITIALIZE VECTORS FOR Person	-	-	-	-	-	-	-	-	  */
	vector<Weapon> Weapons; // Initialize Weapon Vector for Weapons
	vector<Armor> Armors;	// Initialize Armor Vector for Armors

	/*  	DEFINE FUNCTIONS FOR Person	-	-	-	-	-	-	-	-	-	  */
	/** 	Define Struct Overload Functions	-	-	-	-	-	-	-	 **/
	// Function to Evaluate for Combat Tie
	// Accepts 1 Person Parameter for Comparing
	// Returns Bool, passes Data by Member Access
	bool operator==(Person &Person2)
	{
		/*  	INITIALIZE VARIABLES FOR operator==()	-	-	-	-	-	  */
		/** 	Initialize Bools for operator==()	-	-	-	-	-	-	 **/
		bool combatTie = false; // Specify if Combat is Tied

		/*  	CHECK STATE OF COMBAT	-	-	-	-	-	-	-	-	-	  */
		/** 	If Person 1 and Person 2 Attacks, Combat is Tied	-	-	 **/
		if (this->isAttacking == true && Person2.isAttacking == true)
		{
			combatTie = true;
		}

		/** 	If Person 1 and Person 2 Blocks, Combat is Tied	-	-	-	 **/
		else if (this->isBlocking == true && Person2.isBlocking == true)
		{
			combatTie = true;
		}

		/** 	If Person 1 and Person 2 Dodges, Combat is Tied	-	-	-	 **/
		else if (this->isDodging == true && Person2.isDodging == true)
		{
			combatTie = true;
		}

		/** 	If Person 1 and Person 2 Waits, Combat is Tied	-	-	-	 **/
		else if (this->isWaiting == true && Person2.isWaiting == true)
		{
			combatTie = true;
		}

		/** 	Else, Combat is Not Tied	-	-	-	-	-	-	-	-	 **/
		else
		{
			combatTie = false;
		}

		/*  	RETURN BOOL	-	-	-	-	-	-	-	-	-	-	-	-	  */
		return combatTie;
	}

	// Function to Evaluate for Combat Not Tie
	// Accepts 1 Person Parameter for Comparing
	// Returns Bool, passes Data by Member Access
	bool operator!=(Person &Person2)
	{
		/*  	INITIALIZE VARIABLES FOR operator!=()	-	-	-	-	-	  */
		/** 	Initialize Bools for operator!=()	-	-	-	-	-	-	 **/
		bool combatNotTie = false; // Specify if Combat is Not Tied

		/*  	CHECK STATE OF COMBAT	-	-	-	-	-	-	-	-	-	  */
		/** 	If Person 1 Attacks and Person 2 Doesn't, Combat is Not Tied **/
		if (this->isAttacking == true && Person2.isAttacking == false)
		{
			combatNotTie = true;
		}

		/** 	If Person 1 Blocks and Person 2 Doesn't, Combat is Not Tied	 **/
		else if (this->isBlocking == true && Person2.isBlocking == false)
		{
			combatNotTie = true;
		}

		/** 	If Person 1 Dodges and Person 2 Doesn't, Combat is Not Tied	 **/
		else if (this->isDodging == true && Person2.isDodging == false)
		{
			combatNotTie = true;
		}

		/** 	If Person 1 Waits and Person 2 Doesn't, Combat is Not Tied	 **/
		else if (this->isWaiting == true && Person2.isWaiting == false)
		{
			combatNotTie = true;
		}

		/** 	Else, Combat is Tied	-	-	-	-	-	-	-	-	-	 **/
		else
		{
			combatNotTie = false;
		}

		/*  	RETURN BOOL	-	-	-	-	-	-	-	-	-	-	-	-	  */
		return combatNotTie;
	}

	// Function to Evaluate for Combat Loss
	// Accepts 1 Person Parameter for Comparing
	// Returns Bool, passes Data by Member Access
	bool operator<=(Person &Person2)
	{
		/*  	INITIALIZE VARIABLES FOR operator<=()	-	-	-	-	-	  */
		/** 	Initialize Bools for operator<=()	-	-	-	-	-	-	 **/
		bool combatLoss = false; // Specify if Combat is Lost

		/*  	CHECK STATE OF COMBAT	-	-	-	-	-	-	-	-	-	  */
		/** 	If Person 1 Attacks and Person 2 Dodges, Combat is Lost	-	 **/
		if (this->isAttacking == true && Person2.isDodging == true)
		{
			combatLoss = true;
		}

		/** 	If Person 1 Blocks and Person 2 Attacks, Combat is Lost	-	 **/
		else if (this->isBlocking == true && Person2.isAttacking == true)
		{
			combatLoss = true;
		}

		/** 	If Person 1 Dodges and Person 2 Blocks, Combat is Lost	-	 **/
		else if (this->isDodging == true && Person2.isBlocking == true)
		{
			combatLoss = true;
		}

		/** 	If Person 1 Waits and Person 2 Attacks, Combat is Lost	-	 **/
		else if (this->isWaiting == true && Person2.isAttacking == true)
		{
			combatLoss = true;
		}

		/** 	Else, Combat is Won	-	-	-	-	-	-	-	-	-	-	 **/
		else
		{
			combatLoss = false;
		}

		/*  	RETURN BOOL	-	-	-	-	-	-	-	-	-	-	-	-	  */
		return combatLoss;
	}

	// Function to Evaluate for Combat Win
	// Accepts 1 Person Parameter for Comparing
	// Returns Bool, passes Data by Member Access
	bool operator>=(Person &Person2)
	{
		/*  	INITIALIZE VARIABLES FOR operator>=()	-	-	-	-	-	  */
		/** 	Initialize Bools for operator>=()	-	-	-	-	-	-	 **/
		bool combatWin = false; // Specify if Combat is Won

		/*  	CHECK STATE OF COMBAT	-	-	-	-	-	-	-	-	-	  */
		/** 	If Person 1 Attacks and Person 2 Blocks, Combat is Won	-	 **/
		if (this->isAttacking == true && Person2.isBlocking == true)
		{
			combatWin = true;
		}

		/** 	If Person 1 Blocks and Person 2 Dodges, Combat is Won	-	 **/
		else if (this->isBlocking == true && Person2.isDodging == true)
		{
			combatWin = true;
		}

		/** 	If Person 1 Dodges and Person 2 Attacks, Combat is Won	-	 **/
		else if (this->isDodging == true && Person2.isAttacking == true)
		{
			combatWin = true;
		}

		/** 	If Person 1 Attacks and Person 2 Waits, Combat is Won	-	 **/
		else if (this->isAttacking == true && Person2.isWaiting == true)
		{
			combatWin = true;
		}

		/** 	Else, Combat is Lost	-	-	-	-	-	-	-	-	-	 **/
		else
		{
			combatWin = false;
		}

		/*  	RETURN BOOL	-	-	-	-	-	-	-	-	-	-	-	-	  */
		return combatWin;
	}

	// Function to Damage Person 2's Health in Combat
	// Accepts 1 Person Parameter for Fighting
	// Returns Void, passes Data by Member Access
	void operator+=(Person &Person2)
	{
		/*  	CHECK STATE OF COMBAT	-	-	-	-	-	-	-	-	-	  */
		/** 	If Person 1 Wins Combat, Check if Person 2 is Blocking	-	 **/
		if (*this >= Person2)
		{
			/*  	CHECK IF PERSON 2 IS BLOCKING	-	-	-	-	-	-	  */
			/** 	If Person 2 is Blocking, Deal Reduced Damage to Person 2 **/
			if (Person2.isBlocking == true)
			{
				/***	Deal Reduced Damage to Person 2 based on bBUFF		***/
				Person2.personHealth -=
					((this->Weapons
						  .at(this->personWeapon)
						  .weaponDamage -
					  Person2.Armors
						  .at(Person2.personArmor)
						  .armorDefense) /
					 gameConsts[bBUFF]);

				/***	Take Stamina Cost of Blocking from Person 2			***/
				Person2.personStamina -= gameConsts[bCOST];

				/*  	CHECK IF PERSON 2 IS EXHAUSTED	-	-	-	-	-	  */
				/** 	If Person 2 is Exhausted, Gain Free Unblocked Attack **/
				if (Person2.personStamina <= 0)
				{
					/***	Prevent Person 2's Stamina from going Below 0	***/
					Person2.personStamina = 0;

					/***	Gain a Free Unblocked Attack on Person 2		***/
					Person2.personHealth -=
						(this->Weapons
							 .at(this->personWeapon)
							 .weaponDamage -
						 Person2.Armors
							 .at(Person2.personArmor)
							 .armorDefense);
				}
			}

			/** 	If Person 2 is Not Blocking, Deal Full Damage			 **/
			else
			{
				/***	Deal Full Damage to Person 2 						***/
				Person2.personHealth -=
					(this->Weapons
						 .at(this->personWeapon)
						 .weaponDamage -
					 Person2.Armors
						 .at(Person2.personArmor)
						 .armorDefense);
			}
		}

		/** 	If Person 2 Wins Combat, Check if Person 1 is Blocking	-	 **/
		else if (*this <= Person2)
		{
			/*  	CHECK IF PERSON 1 IS BLOCKING	-	-	-	-	-	-	  */
			/** 	If Person 1 is Blocking, Deal Reduced Damage to Person 1 **/
			if (this->isBlocking == true)
			{
				/***	Deal Reduced Damage to Person 1 based on bBUFF		***/
				this->personHealth -=
					((Person2.Weapons
						  .at(Person2.personWeapon)
						  .weaponDamage -
					  this->Armors
						  .at(this->personArmor)
						  .armorDefense) /
					 gameConsts[bBUFF]);

				/***	Take Stamina Cost of Blocking from Person 1			***/
				this->personStamina -= gameConsts[bCOST];

				/*  	CHECK IF PERSON 1 IS EXHAUSTED	-	-	-	-	-	  */
				/** 	If Person 1 is Exhausted, Gain Free Unblocked Attack **/
				if (this->personStamina <= 0)
				{
					/***	Prevent Person 1's Stamina from going Below 0	***/
					this->personStamina = 0;

					/***	Gain a Free Unblocked Attack on Person 1		***/
					this->personHealth -=
						(Person2.Weapons
							 .at(Person2.personWeapon)
							 .weaponDamage -
						 this->Armors
							 .at(this->personArmor)
							 .armorDefense);
				}
			}

			/** 	If Person 1 is Not Blocking, Deal Full Damage			 **/
			else
			{
				/***	Deal Full Damage to Person 1 						***/
				this->personHealth -=
					(Person2.Weapons
						 .at(Person2.personWeapon)
						 .weaponDamage -
					 this->Armors
						 .at(this->personArmor)
						 .armorDefense);
			}
		}

		/*  	RETURN VOID	-	-	-	-	-	-	-	-	-	-	-	-	  */
		return;
	}

	// Function to Consume Stamina During Combat
	// Accepts 1 Person Parameter for Fighting
	// Returns Void, passes Data by Member Access
	void operator-=(Person &Person2)
	{
		/*  	CHECK STATE OF COMBAT	-	-	-	-	-	-	-	-	-	  */
		/** 	If Person 1 Attacks, Take Stamina Cost of Attacking	-	-	 **/
		if (this->isAttacking == true)
		{
			this->personStamina -= gameConsts[aCOST];
		}

		/** 	If Person 1 Dodges, Take Stamina Cost of Dodging	-	-	 **/
		else if (this->isDodging == true)
		{
			this->personStamina -= gameConsts[dCOST];
		}

		/*  	CHECK IF PERSON 1 IS EXHAUSTED	-	-	-	-	-	-	-	  */
		/** 	If Person 1 is Exhausted, Prevent Person 1's Stamina < 0	 **/
		if (this->personStamina <= 0)
		{
			this->personStamina = 0;
		}

		/*  	CHECK STATE OF COMBAT	-	-	-	-	-	-	-	-	-	  */
		/** 	If Person 2 Attacks, Take Stamina Cost of Attacking	-	-	 **/
		if (Person2.isAttacking == true)
		{
			Person2.personStamina -= gameConsts[aCOST];
		}

		/** 	If Person 2 Dodges, Take Stamina Cost of Dodging	-	-	 **/
		else if (Person2.isDodging == true)
		{
			Person2.personStamina -= gameConsts[dCOST];
		}

		/*  	CHECK IF PERSON 2 IS EXHAUSTED	-	-	-	-	-	-	-	  */
		/** 	If Person 2 is Exhausted, Prevent Person 2's Stamina < 0	 **/
		if (Person2.personStamina <= 0)
		{
			Person2.personStamina = 0;
		}

		/*  	RETURN VOID	-	-	-	-	-	-	-	-	-	-	-	-	  */
		return;
	}

	// Function to Evaluate if Health is Less than Person 2
	// Accepts 1 Person Parameter for Comparing
	// Returns Bool, passes Data by Member Access
	bool operator<(Person &Person2)
	{
		/*  	INITIALIZE VARIABLES FOR operator<()	-	-	-	-	-	  */
		/** 	Initialize Bools for operator<()	-	-	-	-	-	-	 **/
		bool healthLess = false; // Specify if Person 1's Health is Less

		/*  	CHECK STATE OF COMBAT	-	-	-	-	-	-	-	-	-	  */
		/** 	If Person 1's Health is Less than Person 2, Health is Less	 **/
		if (this->personHealth < Person2.personHealth)
		{
			healthLess = true;
		}

		/** 	Else, Health is Not Less	-	-	-	-	-	-	-	-	 **/
		else
		{
			healthLess = false;
		}

		/*  	RETURN BOOL	-	-	-	-	-	-	-	-	-	-	-	-	  */
		return healthLess;
	}

	// Function to Evaluate if Health is More than Person 2
	// Accepts 1 Person Parameter for Comparing
	// Returns Bool, passes Data by Member Access
	bool operator>(Person &Person2)
	{
		/*  	INITIALIZE VARIABLES FOR operator>()	-	-	-	-	-	  */
		/** 	Initialize Bools for operator>()	-	-	-	-	-	-	 **/
		bool healthMore = false; // Specify if Person 1's Health is More

		/*  	CHECK STATE OF COMBAT	-	-	-	-	-	-	-	-	-	  */
		/** 	If Person 1's Health is More than Person 2, Health is More	 **/
		if (this->personHealth > Person2.personHealth)
		{
			healthMore = true;
		}

		/** 	Else, Health is Not More	-	-	-	-	-	-	-	-	 **/
		else
		{
			healthMore = false;
		}

		/*  	RETURN BOOL	-	-	-	-	-	-	-	-	-	-	-	-	  */
		return healthMore;
	}

	// Function to Recover Person 1's Resources After Kill
	// Accepts 1 Person Parameter for Looting
	// Returns Void, passes Data by Member Access
	void operator+(Person &Person2)
	{
		/*  	RECOVER RESOURCES AFTER KILL	-	-	-	-	-	-	-	  */
		/** 	Heal Person 1 by hSTEAL Amount After Killing Person 2	-	 **/
		this->personHealth += (Person2.personhMAX / gameConsts[hSTEAL]);

		/***	If Person 1's Health > 0, Prevent Person 1's Health > 0	-	***/
		if (this->personHealth >= gameConsts[hMAX])
		{
			this->personHealth = gameConsts[hMAX];
		}

		/** 	Recover Person 1's Stamina to Full	-	-	-	-	-	-	 **/
		this->personStamina = gameConsts[sMAX];

		/** 	Give Person 2's Money to Person 1	-	-	-	-	-	-	 **/
		this->personMoney += Person2.personMoney;

		/*  	RETURN VOID	-	-	-	-	-	-	-	-	-	-	-	-	  */
		return;
	}

	// Function to Give Allow Person 1 to Take Person 2's Items
	// Accepts 1 Person Parameter for Looting
	// Returns Void, passes Data by Member Access
	void operator-(Person &Person2)
	{
		/*  	TAKE PERSON 2'S ITEMS	-	-	-	-	-	-	-	-	-	  */
		/** 	Give Person 2's Current Weapon to Person 1	-	-	-	-	 **/
		this->Weapons.push_back(Person2.Weapons
									.at(Person2.personWeapon));

		/** 	Give Person 2's Current Armor to Person 1	-	-	-	-	 **/
		this->Armors.push_back(Person2.Armors
								   .at(Person2.personArmor));

		/*  	RETURN VOID	-	-	-	-	-	-	-	-	-	-	-	-	  */
		return;
	}

	// Function to Copy Person 2 to Person 1
	// Accepts 1 Person Parameter for Copying
	// Returns Void, passes Data by Member Access
	void operator=(Person &Person2)
	{
		/*  	COPY PERSON 2 TO PERSON 1	-	-	-	-	-	-	-	-	  */
		/** 	Copy Person 2's Name to Person 1	-	-	-	-	-	-	 **/
		this->personName = Person2.personName;

		/** 	Copy Person 2's Health to Person 1	-	-	-	-	-	-	 **/
		// this->personHealth = Person2.personHealth;

		/** 	Copy Person 2's Stamina to Person 1	-	-	-	-	-	-	 **/
		// this->personStamina = Person2.personStamina;

		/** 	Copy Person 2's Money to Person 1	-	-	-	-	-	-	 **/
		this->personMoney = Person2.personMoney;

		/** 	Copy Person 2's Index to Person 1	-	-	-	-	-	-	 **/
		this->personIndex = Person2.personIndex;

		/** 	Copy Person 2's Number to Person 1	-	-	-	-	-	-	 **/
		this->personNumber = Person2.personNumber;

		/** 	Copy Person 2's Equipped Weapon Slot to Person 1	-	-	 **/
		this->personWeapon = Person2.personWeapon;

		/** 	Copy Person 2's Equipped Armor Slot to Person 1	-	-	-	 **/
		this->personArmor = Person2.personArmor;

		/** 	Copy if Person 2 is Player Character to Person 1	-	-	 **/
		this->isPlayer = Person2.isPlayer;

		/*  	RETURN VOID	-	-	-	-	-	-	-	-	-	-	-	-	  */
		return;
	}
};

/** 	Define Game Level Structs	-	-	-	-	-	-	-	-	-	-	 **/
// Struct that stores Game Levels for Game Class
// Contains Ints, Doubles, Strings, Bools, Vectors, and Functions
// Defines Struct, passes Data by Member Access
struct Game::Floor
{
	/*  	INITIALIZE VARIABLES FOR Floor	-	-	-	-	-	-	-	-	  */
	/** 	Initialize Ints for Floor	-	-	-	-	-	-	-	-	-	 **/
	int
		floorIndex = 0,	 // Specify Index of Floor
		floorNumber = 1; // Specify Number of Floor

	/** 	Initialize Doubles for Floor	-	-	-	-	-	-	-	-	 **/
	double
		floorLevel = 1,					// Specify Level of Floor
		floorModifier = 1,				// Specify Modifier of Floor
		floorMoney = gameConsts[fLOOT]; // Specify Reward of Floor

	/** 	Initialize Strings for Floor	-	-	-	-	-	-	-	-	 **/
	string floorName = "Floor"; // Specify Name of Floor

	/** 	Initialize Bools for Floor	-	-	-	-	-	-	-	-	-	 **/
	bool isStore = true; // Specify if Store is Available on Floor

	/*  	INITIALIZE VECTORS FOR Floor	-	-	-	-	-	-	-	-	  */
	vector<Person> Enemies; // Initialize Person Vector for Floor Enemies

	/*  	DEFINE FUNCTIONS FOR Floor	-	-	-	-	-	-	-	-	-	  */
	/** 	Define Struct Overload Functions	-	-	-	-	-	-	-	 **/
	// Function to Copy Floor 2 to Floor 1
	// Accepts 1 Floor Parameter for Copying
	// Returns Void, passes Data by Member Access
	void operator=(Floor &Floor2)
	{
		/*  	COPY FLOOR 2 TO FLOOR 1	-	-	-	-	-	-	-	-	-	  */
		/** 	Copy Floor 2's Name to Floor 1	-	-	-	-	-	-	-	 **/
		this->floorName = Floor2.floorName;

		/** 	Copy Floor 2's Modifier to Floor 1	-	-	-	-	-	-	 **/
		this->floorModifier = Floor2.floorModifier;

		/** 	Copy Floor 2's Money Prize to Floor 1	-	-	-	-	-	 **/
		this->floorMoney = Floor2.floorMoney;

		/** 	Copy Floor 2's Index to Floor 1	-	-	-	-	-	-	-	 **/
		this->floorIndex = Floor2.floorIndex;

		/** 	Copy Floor 2's Number to Floor 1	-	-	-	-	-	-	 **/
		this->floorNumber = Floor2.floorNumber;

		/** 	Copy Floor 2's Level to Floor 1	-	-	-	-	-	-	-	 **/
		this->floorLevel = Floor2.floorLevel;

		/** 	Copy if Floor 2 has Store to Floor 1	-	-	-	-	-	 **/
		this->isStore = Floor2.isStore;

		/*  	RETURN VOID	-	-	-	-	-	-	-	-	-	-	-	-	  */
		return;
	}
};

/******************************************************************************
 *                               STRUCT DEFINITIONS                           *
 ******************************************************************************/

/******************************************************************************
 *                             FUNCTION DEFINITIONS                           *
 ******************************************************************************/
/** 	Initialize Class Deconstructor Functions	-	-	-	-	-	 **/
/***	Define Default Class Constructor	-	-	-	-	-	-	***/
Game::Game()

{
	/*  	GATHER MENU DATA FROM GAME FILES	-	-	-	-	-	-	  */
	dsFiles(fileMenus);

	/*  	OPEN MENU SCREENS TO BEGIN GAME	-	-	-	-	-	-	-	  */
	dsMenus(INTRO);
	dsMenus(RULES);
	dsMenus(SETTINGS);

	/*  	BUILD NEW GAME LEVELS AND CHARACTERS	-	-	-	-	-	  */
	dsGameNew();

	/*  	GATHER UI DATA FROM GAME FILES	-	-	-	-	-	-	-	  */
	dsFiles(fileUi);

	/*  	ENGAGE IN COMBAT UNTIL VICTORY OR GAME OVER	-	-	-	-	  */
	dsUis(COMBAT1, (1 - 1));
	dsUis(COMBAT1, (2 - 1));
	dsUis(COMBAT1, (3 - 1));
	dsUis(COMBAT1, (4 - 1));

	// do
	//{
	/** 	Play Until All Levels Done or All Player Characters Dead	 **/
	// gameCombat();
	//} while (Floors.at(Floors.size() - 1)
	//				 .Enemies
	//				 .at(Floors.at(Floors.size() - 1).Enemies.size() - 1)
	//				 .personHealth > 0 &&
	//		 Players.at(Players.size() - 1).personHealth > 0);

	/*  	OPEN OUTRO MENU SCREENS AFTER GAME COMPLETE	-	-	-	-	  */
	dsMenus(FLOORINTRO);
}

/***	Define Default Class Deconstructor	-	-	-	-	-	***/
Game::~Game()
{
	/*  	ERASE screenMenu VECTOR	-	-	-	-	-	-	-	-	-	  */
	screenMenu.erase(screenMenu.begin(), screenMenu.end());

	/*  	ERASE screenUi VECTOR	-	-	-	-	-	-	-	-	-	  */
	screenUi.erase(screenUi.begin(), screenUi.end());

	/*  	ERASE Floors VECTOR	-	-	-	-	-	-	-	-	-	-	  */
	Floors.erase(Floors.begin(), Floors.end());

	/*  	ERASE Players VECTOR	-	-	-	-	-	-	-	-	-	  */
	Players.erase(Players.begin(), Players.end());
}

/******************************************************************************
 *                           User Input Functions                             *
 ******************************************************************************/

// Function to Take User's Input as String
// Accepts No Parameters
// Returns String, passes Data by Member Access
string Game::dsChoiceString()
{
	/*  	INITIALIZE VARIABLES FOR dsChoiceString()	-	-	-	-	-	  */
	/** 	Initialize Strings for dsChoiceString()	-	-	-	-	-	-	 **/
	string userString = "-1";

	/** 	Initialize Bools for dsChoiceString()	-	-	-	-	-	-	 **/
	bool isChoice = true;

	/*  	TAKE USER INPUT	-	-	-	-	-	-	-	-	-	-	-	-	  */
	getline(cin, userString);

	/*  	CHECK USER INPUT FOR ALNUMS	-	-	-	-	-	-	-	-	-	  */
	/** 	Loop through User's Input, Checking for Alnums	-	-	-	-	 **/
	for (int i = 0; isChoice && i < userString.length(); ++i)
	{
		/***	If Char in String is NOT an Alnum, Empty Variables	-	-	***/
		if (!(isalnum(userString[i])))
		{
			isChoice = false;
		}
	}

	/*  	CHECK IF USER INPUT IS VALID	-	-	-	-	-	-	-	-	  */
	/** 	If User's Input is NOT Valid, Completely Empty Variables	-	 **/
	if (isChoice == false)
	{
		userString = "-1";
	}

	/*  	OUTPUT NEWLINE	-	-	-	-	-	-	-	-	-	-	-	-	  */
	cout << endl;

	/*  	RETURN STRING	-	-	-	-	-	-	-	-	-	-	-	-	  */
	return userString;
}

// Function to Take User's Input as Double
// Requires 2 Int Parameter(s) for Min Value and Max Value of User Input
// Returns Double, passes Data by Member Access
double Game::dsChoiceNumber(int choiceMin, int choiceMax)
{
	/*  	INITIALIZE VARIABLES FOR dsChoiceNumber()	-	-	-	-	-	  */
	/** 	Initialize Doubles for dsChoiceNumber()	-	-	-	-	-	-	 **/
	double userDouble = (-1);

	/** 	Initialize Strings for dsChoiceNumber()	-	-	-	-	-	-	 **/
	string userString = "-1";

	/** 	Initialize Bools for dsChoiceNumber()	-	-	-	-	-	-	 **/
	bool isChoice = true;

	/*  	TAKE USER INPUT	-	-	-	-	-	-	-	-	-	-	-	-	  */
	getline(cin, userString);

	/*  	CHECK FOR MIN/MAX USER INPUT	-	-	-	-	-	-	-	-	  */
	/** 	If Min >= 0 and Max <= 9, Only Accept Single Digit Numbers	-	 **/
	if (choiceMin >= 0 && choiceMax <= 9)
	{
		/*  	CHECK USER INPUT FOR SINGLE DIGIT NUMBERS	-	-	-	-	  */
		/** 	If User Inupt has More than 1 Digit, Empty Variables	-	 **/
		if (userString.length() != 1 || !(isdigit(userString[0])))
		{
			isChoice = false;
		}
	}

	/** 	If Min >= 0 and Max > 9, Only Accept Positive Numbers	-	-	 **/
	else if (choiceMin >= 0 && choiceMax > 9)
	{
		/*  	CHECK USER INPUT FOR POSITIVE NUMBERS	-	-	-	-	-	  */
		/** 	Loop through User's Input, Checking for Digits	-	-	-	 **/
		for (int i = 0; isChoice && i < userString.length(); ++i)
		{
			/***	If Char in String is Not a Digit, Empty Variables		***/
			if (!(isdigit(userString[i])))
			{
				isChoice = false;
			}
		}
	}

	/** 	If Min >= 0 and Max > 9, Only Accept Negative Numbers	-	-	 **/
	else if (choiceMin < 0 && choiceMax <= 0)
	{
		/*  	CHECK USER INPUT FOR NEGATIVE NUMBERS	-	-	-	-	-	  */
		/** 	If userString[0] is Not a Negative Sign, Empty Variables	 **/
		if (userString[0] != '-')
		{
			isChoice = false;
		}

		/** 	Loop through User's Input, Checking for Digits	-	-	-	 **/
		for (int i = 1; isChoice && i < userString.length(); ++i)
		{
			/***	If Char in String is Not a Digit, Empty Variables		***/
			if (!(isdigit(userString[i])))
			{
				isChoice = false;
			}
		}
	}

	/** 	Else, Accept Any Numbers	-	-	-	-	-	-	-	-	-	 **/
	else
	{
		/*  	CHECK USER INPUT FOR ANY NUMBER	-	-	-	-	-	-	-	  */
		/** 	If userString[0] is Not '-' or a Digit, Empty Variables	-	 **/
		if (userString[0] != '-' && !(isdigit(userString[0])))
		{
			isChoice = false;
		}

		/** 	If userString[0] is '-' and Length < 2, Empty Variables	-	 **/
		else if (userString[0] == '-' && userString.length() < 2)
		{
			isChoice = false;
		}

		/** 	If userString[0] is '-' and Length >= 2, CHECK FOR DIGITS	 **/
		else
		{
			/*  	CHECK USER INPUT FOR DIGITS	-	-	-	-	-	-	-	  */
			/** 	Loop through User's Input, Checking for Digits	-	-	 **/
			for (int i = 1; isChoice && i < userString.length(); ++i)
			{
				/***	If Char in String is Not a Digit, Empty Variables	***/
				if (!(isdigit(userString[i])))
				{
					isChoice = false;
				}
			}
		}
	}

	/*  	VALIDATE USER INPUT	-	-	-	-	-	-	-	-	-	-	-	  */
	/** 	If User Input is Valid, Check User Input Final Time	-	-	-	 **/
	if (isChoice == true)
	{
		/*  	CHECK IF USER INPUT IS EMPTY	-	-	-	-	-	-	-	  */
		/** 	If User Input is Not Empty, Check if User Input is in Range	 **/
		if (userString.length() >= 1)
		{
			/***	If User Input is Out of Range, Empty Variables	-	-	***/
			if (stod(userString) < choiceMin ||
				stod(userString) > choiceMax)
			{
				isChoice = false;
			}

			/***	If User Input is in Range, Validate User Input	-	-	***/
			else
			{
				userDouble = stod(userString);
			}
		}

		/** 	If User Input is Empty, Empty Variables	-	-	-	-	-	 **/
		else
		{
			isChoice = false;
		}
	}

	/** 	If User Input is Not Valid, Completely Empty Both Variables	-	 **/
	if (isChoice != true)
	{
		userString = "-1";
		userDouble = (-1);
	}

	/*  	OUTPUT NEWLINE	-	-	-	-	-	-	-	-	-	-	-	-	  */
	cout << endl;

	/*  	RETURN DOUBLE	-	-	-	-	-	-	-	-	-	-	-	-	  */
	return userDouble;
}

/******************************************************************************
 *                           User Input Functions                             *
 ******************************************************************************/

/******************************************************************************
 *                      File Read/Write Functions                             *
 ******************************************************************************/

// Function to Access Game Files for Game Data
// Accepts No Parameter(s)
// Returns Void, passes Data by Member Access
void Game::dsFiles(string dsFileName)
{
	// Initialize Variable(s) for dsFiles()
	ifstream dsFile; // Initialize ifstream(s) for storing ifstream(s)

	// Open dsFileName
	dsFile.open(dsFileName);
	// If dsFileName did Open, Continue
	if (dsFile.is_open())
	{
		// Output dsFileName opened successfully to console
		cout << "File, " << dsFileName << ", opened successfully" << endl
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

			// If File is Menu File, Add to screenMenu
			if (dsFileName == fileMenus)
			{
				// Add New Chapter to screenMenu Vector
				screenMenu.push_back(newChapter);
			}
			// If File is Ui File, Add to screenUi
			else if (dsFileName == fileUi)
			{
				// Add New Chapter to screenMenu Vector
				screenUi.push_back(newChapter);
			}

		} while (isLastChap[0] == '+');
		// Close dsFileName
		dsFile.close();

		// If File is Menu File, Add to screenMenu
		if (dsFileName == fileMenus)
		{
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
		// If File is Ui File, Add to screenUi
		else if (dsFileName == fileUi)
		{
			// Add Ui's Combat Screen Pointers for Line Column Pointers to Follow
			screenUi.at(COMBAT1).chapPtrs.push_back(&floorCurrent);
			screenUi.at(COMBAT1).chapPtrs.push_back(&floorRound);
			screenUi.at(COMBAT1).doubPtrs.push_back(&Players.at(playerCurrent).personHealth);
			screenUi.at(COMBAT1).doubPtrs.push_back(&Floors.at(floorCurrent).Enemies.at(enemyCurrent).personHealth);
			screenUi.at(COMBAT1).doubPtrs.push_back(&Players.at(playerCurrent).personStamina);
			screenUi.at(COMBAT1).doubPtrs.push_back(&Floors.at(floorCurrent).Enemies.at(enemyCurrent).personStamina);
			screenUi.at(COMBAT1).doubPtrs.push_back(&Players.at(playerCurrent).personMoney);
			screenUi.at(COMBAT1).chapPtrs.push_back(&enemyCount);

			// Make Ui Screen Page's Line Column Pointers Follow Pointers in Ui Screen's chapPtrs Vector
			for (int uiScreen = 0; uiScreen < screenUi.size(); ++uiScreen)
			{ // Loop through Ui Screens
				for (int screenPage = 0; screenPage < screenUi.at(uiScreen).sPages.size(); ++screenPage)
				{ // Loop through Ui Screen's Pages
					// Track which chapPtr in screenUi.at(uiScreen).chapPtrs to Point to
					int chapPtrsAmount = 0;
					for (int pageLine = 1; chapPtrsAmount < screenUi.at(uiScreen).chapPtrs.size() && pageLine < 2 /*screenUi.at(uiScreen).sPages.at(screenPage).sLines.size()*/; ++pageLine)
					{ // Loop through Ui Screen Page's Line Rows While chapPtrsAmount < screenUi.at(uiScreen).chapPtrs.size()
						for (int LineCol = 1; LineCol < screenUi.at(uiScreen).sPages.at(screenPage).sLines.at(pageLine).sLineCols.size(); ++LineCol)
						{ // Loop through Ui Screen Page's Line Columns
							// If Ui Screen Page's Line Column needs chapPtr, Point to it's chapPtr in screenUi.at(uiScreen).chapPtrs
							if (screenUi.at(uiScreen).sPages.at(screenPage).sLines.at(pageLine).sLineCols.at(LineCol).lInfo == true)
							{
								// Point to chapPtr in screenUi.at(uiScreen).chapPtrs.at(chapPtrsAmount)
								screenUi.at(uiScreen).sPages.at(screenPage).sLines.at(pageLine).sLineCols.at(LineCol).lNumPtr = screenUi.at(uiScreen).chapPtrs.at(chapPtrsAmount);
								// Specify Next chapPtr in screenUi.at(uiScreen).chapPtrs to Point to
								++chapPtrsAmount;
							}
						}
					}
				}
			}

			// Make Ui Screen Page's Line Column Pointers Follow Pointers in Ui Screen's doubPtrs Vector
			for (int uiScreen = 0; uiScreen < screenUi.size(); ++uiScreen)
			{ // Loop through Ui Screens
				for (int screenPage = 0; screenPage < screenUi.at(uiScreen).sPages.size(); ++screenPage)
				{ // Loop through Ui Screen's Pages
					// Track which chapPtr in screenUi.at(uiScreen).doubPtrs to Point to
					int doubPtrsAmount = 0;
					for (int pageLine = 2; doubPtrsAmount < screenUi.at(uiScreen).doubPtrs.size() && pageLine < 5 /*screenUi.at(uiScreen).sPages.at(screenPage).sLines.size()*/; ++pageLine)
					{ // Loop through Ui Screen Page's Line Rows While doubPtrsAmount < screenUi.at(uiScreen).doubPtrs.size()
						for (int LineCol = 1; LineCol < 2 /*screenUi.at(uiScreen).sPages.at(screenPage).sLines.at(pageLine).sLineCols.size()*/; ++LineCol)
						{ // Loop through Ui Screen Page's Line Columns
							// If Ui Screen Page's Line Column needs chapPtr, Point to it's chapPtr in screenUi.at(uiScreen).doubPtrs
							if (screenUi.at(uiScreen).sPages.at(screenPage).sLines.at(pageLine).sLineCols.at(LineCol).lInfo == true)
							{
								// Point to chapPtr in screenUi.at(uiScreen).doubPtrs.at(doubPtrsAmount)
								screenUi.at(uiScreen).sPages.at(screenPage).sLines.at(pageLine).sLineCols.at(LineCol).lDoubPtr = screenUi.at(uiScreen).doubPtrs.at(doubPtrsAmount);
								// Specify Next chapPtr in screenUi.at(uiScreen).doubPtrs to Point to
								++doubPtrsAmount;
							}
						}
					}
				}
			}
		}
	}

	// If dsFileName did Not Open, Error
	else
	{
		// Output dsFileName failed to open to console
		cout << "File, " << dsFileName << ", failed to open" << endl
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
	std::ofstream dsWriteFile; // Initialize ofstream(s) for storing ofstream(s)
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
 *                      File Read/Write Functions                             *
 ******************************************************************************/

/******************************************************************************
 *                       Display Screen Functions (Menu)                      *
 ******************************************************************************/

// Function to Display Game Menus
// Accepts 2 Int Parameters, 1 for Menu Chapter, and 1 for Menu Page
// Returns Double, passes Data by Member Access
double Game::dsMenuDisplay(int chapIndex, int pageIndex)
{
	/*  	INITIALIZE VARIABLES FOR dsMenuDisplay()	-	-	-	-	-	  */
	/** 	Initialize Doubles for dsMenuDisplay()	-	-	-	-	-	-	 **/
	double userDouble = (-1);

	/** 	Initialize Strings for dsMenuDisplay()	-	-	-	-	-	-	 **/
	string lineString = " ";

	/*  	OUTPUT DISPLAY SCREEN TO CONSOLE	-	-	-	-	-	-	-	  */
	/** 	Clear Console to Refresh Display Screen	-	-	-	-	-	-	 **/
	system("CLS");

	/** 	Display Top Border, Each Corner Spaced by setw(40)	-	-	-	 **/
	cout << setw(40) << left << "+ - - - - - - - - - - - - - - - - - - -"
		 << setw(40) << right << "- - - - - - - - - - - - - - - - - - - - +"
		 << endl;

	/** 	Loop through Page's Line Rows, Checking for Line Columns	-	 **/
	for (int pageLine = 1;
		 pageLine < screenMenu.at(chapIndex)
						.sPages.at(pageIndex)
						.sLines.size();
		 ++pageLine)
	{
		/*  	INITIALIZE VECTORS FOR dsMenuDisplay()	-	-	-	-	-	-	  */
		vector<string> lineStrings;

		/*  	CHECK FOR LINE COLUMNS	-	-	-	-	-	-	-	-	-	  */
		/** 	Loop through Page's Line Colums, Checking for Line Data	-	 **/
		for (int LineCol = 1;
			 LineCol < screenMenu.at(chapIndex)
						   .sPages.at(pageIndex)
						   .sLines.at(pageLine)
						   .sLineCols.size();
			 ++LineCol)
		{
			/***	Specify lineString is Page's Line Column String	-	-	***/
			lineString = screenMenu.at(chapIndex)
							 .sPages.at(pageIndex)
							 .sLines.at(pageLine)
							 .sLineCols.at(LineCol)
							 .lStr;

			/***	If Page's Line Column Pointer Points to Value, Swap "~"	***/
			if (screenMenu.at(chapIndex)
					.sPages.at(pageIndex)
					.sLines.at(pageLine)
					.sLineCols.at(LineCol)
					.lInfo == true)
			{
				lineString.replace(
					lineString.find_first_of("~"),
					1,
					to_string(*screenMenu.at(chapIndex)
								   .sPages.at(pageIndex)
								   .sLines.at(pageLine)
								   .sLineCols.at(LineCol)
								   .lNumPtr));
			}

			/***	Add lineString to lineStrings Vector	-	-	-	-	***/
			lineStrings.push_back(lineString);
		}

		/** 	If Page Line is Selected, Append Page's Selected Message	 **/
		if (screenMenu.at(chapIndex)
				.sPages.at(pageIndex)
				.sLines.at(pageLine)
				.sLineCols.at(0)
				.lSel == true)
		{
			/***	Append Page's Selected Message							***/
			lineStrings.at(lineStrings.size() - 1)
				.append(screenMenu.at(chapIndex)
							.sPages.at(pageIndex)
							.pageSel);
		}

		/** 	Display Left Line String, Centered by setw(40)			-	 **/
		cout << setw(40) << right << lineStrings.at(0);

		/** 	Display Right Line String, Centered by setw(40)			-	 **/
		cout << setw(40) << left << lineStrings.at(1);

		/*  	OUTPUT NEWLINE	-	-	-	-	-	-	-	-	-	-	-	  */
		cout << endl;
	}

	/** 	Display Bottom Border, Each Corner Spaced by setw(40)	-	-	 **/
	cout << setw(40) << left << "+ - - - - - - - - - - - - - - - - - - -"
		 << setw(40) << right << "- - - - - - - - - - - - - - - - - - - - +"
		 << endl;

	/** 	Display Final Line, Centered by setw(40)			-	-	-	 **/
	cout << setw(40) << right
		 << screenMenu.at(chapIndex)
				.sPages.at(pageIndex)
				.sLines.at(0)
				.sLineCols.at(1)
				.lStr
		 << left
		 << screenMenu.at(chapIndex)
				.sPages.at(pageIndex)
				.sLines.at(0)
				.sLineCols.at(2)
				.lStr;

	/** 	Take User Input, Min/Max Specified by Display Screen	-	-	 **/
	userDouble = dsChoiceNumber(
		screenMenu.at(chapIndex)
			.sPages.at(pageIndex)
			.pageMin,
		screenMenu.at(chapIndex)
			.sPages.at(pageIndex)
			.pageMax);

	/*  	RETURN DOUBLE	-	-	-	-	-	-	-	-	-	-	-	-	  */
	return userDouble;
}

// Function to Access Game Menus
// Accepts 2 Int Parameter(s)
// Returns Void, passes Data by Member Access
void Game::dsMenus(int chapIndex, int pageIndex)
{
	/*  	INITIALIZE VARIABLES FOR dsMenus()	-	-	-	-	-	-	-	  */
	/** 	Initialize Doubles for dsMenus()	-	-	-	-	-	-	-	 **/
	int userInt = (-1);

	/** 	Initialize Doubles for dsMenus()	-	-	-	-	-	-	-	 **/
	double userDouble = (-1);

	/** 	Initialize Bools for dsMenus()	-	-	-	-	-	-	-	-	 **/
	bool isDone = false;

	/*  	CHECK USER INPUT	-	-	-	-	-	-	-	-	-	-	-	  */
	/** 	Do this While isDone != true	-	-	-	-	-	-	-	-	 **/
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
				for (int pageLine = 1;
					 !(isLine) && pageLine < screenMenu.at(chapIndex)
												 .sPages.at(pageIndex)
												 .sLines.size();
					 ++pageLine)
				{ // Loop through Menu Screen Page's Line Rows
					// If User Selected Page's Line Row, Mark Page's Line Row as Selected
					if (userInt == screenMenu.at(chapIndex)
									   .sPages.at(pageIndex)
									   .sLines.at(pageLine)
									   .sLineCols.at(0)
									   .lNum)
					{
						// Change Menu Page to Page 2
						++pageIndex;

						// Mark Page's Line Row as Selected
						screenMenu.at(chapIndex)
							.sPages.at(pageIndex)
							.sLines.at(pageLine)
							.sLineCols.at(0)
							.lSel = true;

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
				for (int pageLine = 1;
					 !(isLine) && pageLine < screenMenu.at(chapIndex)
												 .sPages.at(pageIndex)
												 .sLines.size();
					 ++pageLine)
				{ // Loop through Menu Screen Page's Line Rows
					// If User Selected Page's Line Row, Check Page's Line Columns
					if (screenMenu.at(chapIndex)
							.sPages.at(pageIndex)
							.sLines.at(pageLine)
							.sLineCols.at(0)
							.lSel == true)
					{
						// Check Page's Line Columns for Selected Pointer
						for (int LineCol = 1;
							 LineCol < screenMenu.at(chapIndex)
										   .sPages.at(pageIndex)
										   .sLines.at(pageLine)
										   .sLineCols.size();
							 ++LineCol)
						{ // Loop through Menu Screen Page's Line Columns
						  // If User Selected Page's Line Row, Check Page's Line Columns
							if (screenMenu.at(chapIndex)
									.sPages.at(pageIndex)
									.sLines.at(pageLine)
									.sLineCols.at(LineCol)
									.lInfo == true)
							{
								// Edit Value that Line Column's Selected Pointer Points to
								*screenMenu.at(chapIndex)
									 .sPages.at(pageIndex)
									 .sLines.at(pageLine)
									 .sLineCols.at(LineCol)
									 .lNumPtr = userInt;

								// Mark Page's Line Row as Unselected
								screenMenu.at(chapIndex)
									.sPages.at(pageIndex)
									.sLines.at(pageLine)
									.sLineCols.at(0)
									.lSel = false;

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
 *                       Display Screen Functions (Menu)                      *
 ******************************************************************************/

/******************************************************************************
 *                       Display Screen Functions (Ui)                        *
 ******************************************************************************/

// Function to Display Game Menus
// Accepts 2 Int Parameters, 1 for Menu Chapter, and 1 for Menu Page
// Returns Double, passes Data by Member Access
double Game::dsUiDisplay(int chapIndex, int pageIndex)
{
	/*  	INITIALIZE VARIABLES FOR dsMenuDisplay()	-	-	-	-	-	  */
	/** 	Initialize Doubles for dsMenuDisplay()	-	-	-	-	-	-	 **/
	double userDouble = (-1);

	/** 	Initialize Strings for dsMenuDisplay()	-	-	-	-	-	-	 **/
	string lineString = " ";

	/*  	OUTPUT DISPLAY SCREEN TO CONSOLE	-	-	-	-	-	-	-	  */
	/** 	Clear Console to Refresh Display Screen	-	-	-	-	-	-	 **/
	system("CLS");

	/** 	Display Top Border, Each Corner Spaced by setw(40)	-	-	-	 **/
	cout << setw(40) << left << "+ - - - - - - - - - - - - - - - - - - -"
		 << setw(40) << right << "- - - - - - - - - - - - - - - - - - - - +"
		 << endl;

	/** 	Loop through Page's Line Rows, Checking for Line Columns	-	 **/
	for (int pageLine = 1;
		 pageLine < screenMenu.at(chapIndex)
						.sPages.at(pageIndex)
						.sLines.size();
		 ++pageLine)
	{
		/*  	INITIALIZE VECTORS FOR dsMenuDisplay()	-	-	-	-	-	-	  */
		vector<string> lineStrings;

		/*  	CHECK FOR LINE COLUMNS	-	-	-	-	-	-	-	-	-	  */
		/** 	Loop through Page's Line Colums, Checking for Line Data	-	 **/
		for (int LineCol = 1;
			 LineCol < screenMenu.at(chapIndex)
						   .sPages.at(pageIndex)
						   .sLines.at(pageLine)
						   .sLineCols.size();
			 ++LineCol)
		{
			/***	Specify lineString is Page's Line Column String	-	-	***/
			lineString = screenMenu.at(chapIndex)
							 .sPages.at(pageIndex)
							 .sLines.at(pageLine)
							 .sLineCols.at(LineCol)
							 .lStr;

			/***	If Page's Line Column Pointer Points to Value, Swap "~"	***/
			if (screenMenu.at(chapIndex)
					.sPages.at(pageIndex)
					.sLines.at(pageLine)
					.sLineCols.at(LineCol)
					.lInfo == true)
			{
				lineString.replace(
					lineString.find_first_of("~"),
					1,
					to_string(*screenMenu.at(chapIndex)
								   .sPages.at(pageIndex)
								   .sLines.at(pageLine)
								   .sLineCols.at(LineCol)
								   .lNumPtr));
			}

			/***	Add lineString to lineStrings Vector	-	-	-	-	***/
			lineStrings.push_back(lineString);
		}

		/** 	If Page Line is Selected, Append Page's Selected Message	 **/
		if (screenMenu.at(chapIndex)
				.sPages.at(pageIndex)
				.sLines.at(pageLine)
				.sLineCols.at(0)
				.lSel == true)
		{
			/***	Append Page's Selected Message							***/
			lineStrings.at(lineStrings.size() - 1)
				.append(screenMenu.at(chapIndex)
							.sPages.at(pageIndex)
							.pageSel);
		}

		/** 	Display Left Line String, Centered by setw(40)			-	 **/
		cout << setw(40) << right << lineStrings.at(0);

		/** 	Display Right Line String, Centered by setw(40)			-	 **/
		cout << setw(40) << left << lineStrings.at(1);

		/*  	OUTPUT NEWLINE	-	-	-	-	-	-	-	-	-	-	-	  */
		cout << endl;
	}

	/** 	Display Bottom Border, Each Corner Spaced by setw(40)	-	-	 **/
	cout << setw(40) << left << "+ - - - - - - - - - - - - - - - - - - -"
		 << setw(40) << right << "- - - - - - - - - - - - - - - - - - - - +"
		 << endl;

	/** 	Display Final Line, Centered by setw(40)			-	-	-	 **/
	cout << setw(40) << right
		 << screenMenu.at(chapIndex)
				.sPages.at(pageIndex)
				.sLines.at(0)
				.sLineCols.at(1)
				.lStr
		 << left
		 << screenMenu.at(chapIndex)
				.sPages.at(pageIndex)
				.sLines.at(0)
				.sLineCols.at(2)
				.lStr;

	/** 	Take User Input, Min/Max Specified by Display Screen	-	-	 **/
	userDouble = dsChoiceNumber(
		screenMenu.at(chapIndex)
			.sPages.at(pageIndex)
			.pageMin,
		screenMenu.at(chapIndex)
			.sPages.at(pageIndex)
			.pageMax);

	/*  	RETURN DOUBLE	-	-	-	-	-	-	-	-	-	-	-	-	  */
	return userDouble;
}

// Function to Access Game Menus
// Accepts 2 Int Parameter(s)
// Returns Void, passes Data by Member Access
void Game::dsUis(int chapIndex, int pageIndex)
{
	/*  	INITIALIZE VARIABLES FOR dsMenus()	-	-	-	-	-	-	-	  */
	/** 	Initialize Doubles for dsMenus()	-	-	-	-	-	-	-	 **/
	int userInt = (-1);

	/** 	Initialize Doubles for dsMenus()	-	-	-	-	-	-	-	 **/
	double userDouble = (-1);

	/** 	Initialize Bools for dsMenus()	-	-	-	-	-	-	-	-	 **/
	bool isDone = false;

	/*  	CHECK USER INPUT	-	-	-	-	-	-	-	-	-	-	-	  */
	/** 	Do this While isDone != true	-	-	-	-	-	-	-	-	 **/
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
				for (int pageLine = 1;
					 !(isLine) && pageLine < screenMenu.at(chapIndex)
												 .sPages.at(pageIndex)
												 .sLines.size();
					 ++pageLine)
				{ // Loop through Menu Screen Page's Line Rows
					// If User Selected Page's Line Row, Mark Page's Line Row as Selected
					if (userInt == screenMenu.at(chapIndex)
									   .sPages.at(pageIndex)
									   .sLines.at(pageLine)
									   .sLineCols.at(0)
									   .lNum)
					{
						// Change Menu Page to Page 2
						++pageIndex;

						// Mark Page's Line Row as Selected
						screenMenu.at(chapIndex)
							.sPages.at(pageIndex)
							.sLines.at(pageLine)
							.sLineCols.at(0)
							.lSel = true;

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
				for (int pageLine = 1;
					 !(isLine) && pageLine < screenMenu.at(chapIndex)
												 .sPages.at(pageIndex)
												 .sLines.size();
					 ++pageLine)
				{ // Loop through Menu Screen Page's Line Rows
					// If User Selected Page's Line Row, Check Page's Line Columns
					if (screenMenu.at(chapIndex)
							.sPages.at(pageIndex)
							.sLines.at(pageLine)
							.sLineCols.at(0)
							.lSel == true)
					{
						// Check Page's Line Columns for Selected Pointer
						for (int LineCol = 1;
							 LineCol < screenMenu.at(chapIndex)
										   .sPages.at(pageIndex)
										   .sLines.at(pageLine)
										   .sLineCols.size();
							 ++LineCol)
						{ // Loop through Menu Screen Page's Line Columns
						  // If User Selected Page's Line Row, Check Page's Line Columns
							if (screenMenu.at(chapIndex)
									.sPages.at(pageIndex)
									.sLines.at(pageLine)
									.sLineCols.at(LineCol)
									.lInfo == true)
							{
								// Edit Value that Line Column's Selected Pointer Points to
								*screenMenu.at(chapIndex)
									 .sPages.at(pageIndex)
									 .sLines.at(pageLine)
									 .sLineCols.at(LineCol)
									 .lNumPtr = userInt;

								// Mark Page's Line Row as Unselected
								screenMenu.at(chapIndex)
									.sPages.at(pageIndex)
									.sLines.at(pageLine)
									.sLineCols.at(0)
									.lSel = false;

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
 *                       Display Screen Functions (Ui)                        *
 ******************************************************************************/

/******************************************************************************
 *                           Game Build Functions                             *
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
	newFloor.floorLevel = (floorIndex + rndInt((3 + floorDifficulty), 0));								 // Specify Level of Floor
	newFloor.floorModifier = (1.0 + ((newFloor.floorLevel) / 10.0));									 // Specify Modifier of Floor
	newFloor.floorMoney = (rndInt((gameConsts[fLOOT] * 2), gameConsts[fLOOT]) * newFloor.floorModifier); // Specify Reward of Floor
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
	// Specify Maximum amount of Health of Enemy, gameConsts[hBUFF] used to create an upper limit in the future
	newEnemy.personhMAX = (newEnemy.personHealth * (Floors.at(floorIndex).floorModifier / gameConsts[hBUFF]));
	newEnemy.personHealth = newEnemy.personhMAX; // Specify Health of Enemy
	newEnemy.personIndex = enemyIndex;			 // Specify Index of Enemy
	newEnemy.personNumber = enemyCount;			 // Specify Number of Enemy

	// If dsEnemyNew() is Called with No Parameter, Specify Index of Enemy as Next Index
	if (enemyIndex == (-1))
	{
		newEnemy.personIndex = (enemyTotal - 1); // Specify Index of Enemy as Next Index
	}

	// Fill New Enemy with Random Enemy Data
	newEnemy.personMoney = (rndInt((gameConsts[eLOOT] * 2), gameConsts[eLOOT]) * Floors.at(floorIndex).floorModifier); // Specify Reward of Enemy

	// Fill New Enemy with Random Weapon and Armor
	// Weapon newWeapon;					   // Initialize Weapon(s) for storing Weapon Data
	// Armor newArmor;						   // Initialize Armor(s) for storing Armor Data
	// newEnemy.Weapons.push_back(newWeapon); // push_back() New Weapon to New Enemy's Weapon Vector
	// newEnemy.Armors.push_back(newArmor);   // push_back() New Armor to New Enemy's Armor Vector
	// newEnemy.personWeapon = 1;			   // Specify Weapon Equipped to Enemy
	// newEnemy.personArmor = 1;			   // Specify Armor Equipped to Enemy

	// Fill New Enemy's rngArray for RNG
	for (int i = 0; i < gameConsts[rngASIZE]; ++i)
	{
		newEnemy.rngArray[i] = (i + 1);
	}

	// Fill New Enemy's choiceArray for Random Choices
	for (int i = 0; i < gameConsts[rngASIZE]; ++i)
	{
		newEnemy.choiceArray[i] = rndInt(gameConsts[rngESIZE]);
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
	for (int i = 0; i < gameConsts[rngASIZE]; ++i)
	{
		newPlayer.rngArray[i] = (i + 1);
	}

	// Fill New Player's choiceArray for Random Choices
	for (int i = 0; i < gameConsts[rngASIZE]; ++i)
	{
		newPlayer.choiceArray[i] = rndInt(gameConsts[rngESIZE]);
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
 *                           Game Build Functions                             *
 ******************************************************************************/

/******************************************************************************
 *                          Game Combat Functions                             *
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
// for (int uMENU = 0; uMENU < gameConsts[uMENUS]; ++uMENU)
//{
//	// Fill uiLinesNumbers Array Lines
//	for (int uLINE = 0; uLINE < gameConsts[uLINES]; ++uLINE)
//	{
//		// Fill uiLinesNumbers Array Columns
//		for (int uCOL = 0; uCOL < gameConsts[uCOLS]; ++uCOL)
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
//				Players.at(playerCurrent).personStamina = gameConsts[sMAX];
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
			if ((Players.at(playerCurrent).personStamina + gameConsts[sGAIN]) > gameConsts[sMAX])
			{
				Players.at(playerCurrent).personStamina = gameConsts[sMAX];
			}
			else
			{
				Players.at(playerCurrent).personStamina += gameConsts[sGAIN];
			}
		}

		// Recover Enemy's Stamina if allowed to
		if (Floors.at(floorCurrent).Enemies.at(enemyCurrent).isRecovering == true)
		{
			// Recover Enemy's Stamina
			if ((Floors.at(floorCurrent).Enemies.at(enemyCurrent).personStamina + gameConsts[sGAIN]) > gameConsts[sMAX])
			{
				Floors.at(floorCurrent).Enemies.at(enemyCurrent).personStamina = gameConsts[sMAX];
			}
			else
			{
				Floors.at(floorCurrent).Enemies.at(enemyCurrent).personStamina += gameConsts[sGAIN];
			}
		}
	}
	return;
}

/******************************************************************************
 *                          Game Combat Functions                             *
 ******************************************************************************/

/******************************************************************************
 *                           Game Extra Functions                             *
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
//			if (Players.at(playerCurrent).personStamina >= gameConsts[aCOST])
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
//			if (Players.at(playerCurrent).personStamina >= gameConsts[dCOST])
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
			if (Floors.at(floorCurrent).Enemies.at(enemyCurrent).personStamina >= gameConsts[aCOST])
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
			if (Floors.at(floorCurrent).Enemies.at(enemyCurrent).personStamina >= gameConsts[dCOST])
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
	if (Floors.at(floorCurrent).Enemies.at(enemyCurrent).personStamina >= gameConsts[dCOST])
	{
		// If Player's Stamina is too Low to Act, Decide Attack
		if (Players.at(playerCurrent).personStamina < gameConsts[aCOST])
		{
			enemyInt = 1;
		}

		// If Player has too Little Stamina to Block Safely, Decide Dodge or Attack
		else if (Players.at(playerCurrent).personStamina <= gameConsts[bCOST])
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
		else if (Players.at(playerCurrent).personStamina < gameConsts[dCOST])
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
			int choice3 = rndInt((gameConsts[rngASIZE] - 1), 0);
			enemyInt = Floors.at(floorCurrent).Enemies.at(enemyCurrent).choiceArray[choice3];
		}
	}

	// If Enemy has enough Stamina to Block Safely, Decide
	else if (Floors.at(floorCurrent).Enemies.at(enemyCurrent).personStamina > gameConsts[bCOST])
	{
		// If Player has too Little Stamina to Act, Decide Attack
		if (Players.at(playerCurrent).personStamina < gameConsts[aCOST])
		{
			enemyInt = 1;
		}

		// If Player has too Little Stamina to Block Safely, Decide Block or Attack
		else if (Players.at(playerCurrent).personStamina <= gameConsts[bCOST])
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
		else if (Players.at(playerCurrent).personStamina < gameConsts[dCOST])
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
	else if (Floors.at(floorCurrent).Enemies.at(enemyCurrent).personStamina >= gameConsts[aCOST])
	{
		// If Player has enough Stamina to Dodge, Decide Attack or Block
		if (Players.at(playerCurrent).personStamina >= gameConsts[dCOST])
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
 *                           Game Extra Functions                             *
 ******************************************************************************/

/******************************************************************************
 *                             FUNCTION DEFINITIONS                           *
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
		if (Players.at(playerCurrent).personHealth - ((Floors.at(floorCurrent).Enemies.at(enemyCurrent).Weapons.at(Floors.at(floorCurrent).Enemies.at(enemyCurrent).personWeapon).weaponDamage - Players.at(playerCurrent).Armors.at(Players.at(playerCurrent).personArmor).armorDefense) / gameConsts[bBUFF]) <= 0)
		{
			cout << Floors.at(floorCurrent).Enemies.at(enemyCurrent).personName << " hit "
				 << Players.at(playerCurrent).personName << "'s shield and damaged them for "
				 << ((Floors.at(floorCurrent).Enemies.at(enemyCurrent).Weapons.at(Floors.at(floorCurrent).Enemies.at(enemyCurrent).personWeapon).weaponDamage - Players.at(playerCurrent).Armors.at(Players.at(playerCurrent).personArmor).armorDefense) / gameConsts[bBUFF])
				 << " damage." << endl
				 << endl;
		}
		else
		{
			cout << Floors.at(floorCurrent).Enemies.at(enemyCurrent).personName << " hit "
				 << Players.at(playerCurrent).personName << "'s shield and damaged them for "
				 << ((Floors.at(floorCurrent).Enemies.at(enemyCurrent).Weapons.at(Floors.at(floorCurrent).Enemies.at(enemyCurrent).personWeapon).weaponDamage - Players.at(playerCurrent).Armors.at(Players.at(playerCurrent).personArmor).armorDefense) / gameConsts[bBUFF])
				 << " damage." << endl
				 << endl;
			if ((Players.at(playerCurrent).personStamina - gameConsts[bCOST]) <= 0)
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
		if (Floors.at(floorCurrent).Enemies.at(enemyCurrent).personHealth - ((Players.at(playerCurrent).Weapons.at(Players.at(playerCurrent).personWeapon).weaponDamage - Floors.at(floorCurrent).Enemies.at(enemyCurrent).Armors.at(Floors.at(floorCurrent).Enemies.at(enemyCurrent).personArmor).armorDefense) / gameConsts[bBUFF]) <= 0)
		{
			cout << Players.at(playerCurrent).personName << " hit "
				 << Floors.at(floorCurrent).Enemies.at(enemyCurrent).personName << "'s shield and damaged them for "
				 << ((Players.at(playerCurrent).Weapons.at(Players.at(playerCurrent).personWeapon).weaponDamage - Floors.at(floorCurrent).Enemies.at(enemyCurrent).Armors.at(Floors.at(floorCurrent).Enemies.at(enemyCurrent).personArmor).armorDefense) / gameConsts[bBUFF])
				 << " damage." << endl
				 << endl;
		}
		else
		{
			cout << Players.at(playerCurrent).personName << " hit "
				 << Floors.at(floorCurrent).Enemies.at(enemyCurrent).personName << "'s shield and damaged them for "
				 << ((Players.at(playerCurrent).Weapons.at(Players.at(playerCurrent).personWeapon).weaponDamage - Floors.at(floorCurrent).Enemies.at(enemyCurrent).Armors.at(Floors.at(floorCurrent).Enemies.at(enemyCurrent).personArmor).armorDefense) / gameConsts[bBUFF])
				 << " damage." << endl
				 << endl;
			if ((Floors.at(floorCurrent).Enemies.at(enemyCurrent).personStamina - gameConsts[bCOST]) <= 0)
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
