/******************************************************************************
Week 8 Lab 1

Donnie Gilbert
CS162-W1 SP24 Priestley

Specification Summary:


Sources:
Watching Mr.Priestley's labs.

"If you don't specify, I may ask you if I can share it."
*******************************************************************************/

/******************************************************************************
 *                                 Week 8 Lab 1 .cpp                          *
 ******************************************************************************/
/*  	INCLUDE LIBRARIES FOR FILE	-	-	-	-	-	-	-	-	-	-	  */
#include <iomanip>
#include <iostream>
#include <cstring>
/*  	DEFINE NAMESPACE FOR FILE	-	-	-	-	-	-	-	-	-	-	  */
using namespace std;
/******************************************************************************
 *                               GLOBAL DECLARATIONS                          *
 ******************************************************************************/

/*  	INITIALIZE GLOBAL CONSTS FOR FILE	-	-	-	-	-	-	-	-	  */
/** 	Initialize Const Ints for File	-	-	-	-	-	-	-	-	-	 **/
const int arraySIZE = 4; // Specify Size of File Array

/******************************************************************************
 *                               GLOBAL DECLARATIONS                          *
 ******************************************************************************/

/******************************************************************************
 *                                CLASS DEFINITIONS                           *
 ******************************************************************************/

/*  	DEFINE GLOBAL CLASSES FOR FILE	-	-	-	-	-	-	-	-	-	  */
/** 	Define Global Class for Firms	-	-	-	-	-	-	-	-	-	 **/

class Firm /*  	INITIALIZE CLASS FOR FIRMS	-	-	-	-	-	-	-	-	  */
{
protected: /*  	PROTECTED MEMBER SECTION FOR CLASS	-	-	-	-	-	-	  */
	/*  	INITIALIZE PROTECTED VARIABLES FOR CLASS	-	-	-	-	-	  */
	/** 	Initialize Protected Char Arrays for Class	-	-	-	-	-	 **/
	char
		Name[30], // Specify Firm's Name
		City[20]; // Specify Firm's City

public: /*  	PUBLIC MEMBER SECTION FOR CLASS	-	-	-	-	-	-	-	  */
	/*  	INITIALIZE PUBLIC FUNCTIONS FOR CLASS	-	-	-	-	-	-	  */
	/** 	Initialize Class Constructor Functions	-	-	-	-	-	-	 **/
	// Firm();
	// Firm(const Firm &f) { strcpy(Name, f.Name); }

	/** 	Initialize Private Member Get Functions	-	-	-	-	-	-	 **/
	char *get_Name() { return Name; }
	char *get_City() { return City; }

	/** 	Initialize Private Member Set Functions	-	-	-	-	-	-	 **/
	void set_Name(const char new_Name[]) { strcpy(Name, new_Name); }
	void set_City(const char new_City[]) { strcpy(City, new_City); }

	/** 	Initialize Display Output Functions	-	-	-	-	-	-	-	 **/
	void output(ostream &, char = 'V');
	friend ostream &operator<<(ostream &, Firm);
};

/*  	DEFINE PUBLIC FUNCTIONS FOR CLASS	-	-	-	-	-	-	-	-	  */
/** 	Define Display Output Functions	-	-	-	-	-	-	-	-	-	 **/

// Function to Output Firms
// Accepts 1 Ostream Parameter, and 1 Char Parameter
// Returns Void, Passes Data by Member Access
void Firm::output(ostream &os, char ori)
{
	/*  	INITIALIZE VARIABLES FOR output()	-	-	-	-	-	-	-	  */
	/** 	Initialize Ints for output()	-	-	-	-	-	-	-	-	 **/
	ori = toupper(ori); // Capitalize Char Parameter Before Check

	/*  	CHECK IF ori IS 'V'	-	-	-	-	-	-	-	-	-	-	-	  */
	/** 	If ori is 'V', Display Firm Vertically	-	-	-	-	-	-	 **/
	if (ori == 'V')
	{
		/***	Display Firm Vertically	-	-	-	-	-	-	-	-	-	***/
		os << setw(15) << "Name: " << Name << endl
		   << setw(15) << "City: " << City << endl
		   << endl;
	}

	/** 	Otherwise, Display Firm Horizontally	-	-	-	-	-	-	 **/
	else
	{
		/***	Display Firm Horizontally	-	-	-	-	-	-	-	-	***/
		os << setw(15) << Name << ' '
		   << setw(15) << City << endl;
	}
}

// Function to Output Firms
// Accepts 1 Ostream Parameter, and 1 Firm Parameter
// Returns Void, Passes Data by Member Access
ostream &operator<<(ostream &os, Firm f)
{

	/*  	DISPLAY FirmS	-	-	-	-	-	-	-	-	-	-	-	-	  */
	/** 	Display Firms Vertically	-	-	-	-	-	-	-	-	-	 **/
	f.output(os, 'V');

	/*  	RETURN OSTREAM	-	-	-	-	-	-	-	-	-	-	-	-	  */
	return os;
}

/** 	Define Global Class for Clients	-	-	-	-	-	-	-	-	-	 **/

class Client /*  	INITIALIZE CLASS FOR CLIENTS	-	-	-	-	-	-	  */
	: public Firm
{
protected: /*  	PROTECTED MEMBER SECTION FOR CLASS	-	-	-	-	-	-	  */
	/*  	INITIALIZE PROTECTED VARIABLES FOR CLASS	-	-	-	-	-	  */
	/** 	Initialize Protected Chars for Class	-	-	-	-	-	-	 **/
	char Region; // Specify Client's Region

public: /*  	PUBLIC MEMBER SECTION FOR CLASS	-	-	-	-	-	-	-	  */
	/*  	INITIALIZE PUBLIC FUNCTIONS FOR CLASS	-	-	-	-	-	-	  */
	char get_Region() { return Region; }

	/** 	Initialize Private Member Set Functions	-	-	-	-	-	-	 **/
	void set_Region(const char new_Region) { Region = new_Region; }

	/** 	Initialize Display Output Functions	-	-	-	-	-	-	-	 **/
	void output(ostream &, char = 'V');
	friend ostream &operator<<(ostream &, Client);
};

/*  	DEFINE PUBLIC FUNCTIONS FOR CLASS	-	-	-	-	-	-	-	-	  */
/** 	Define Display Output Functions	-	-	-	-	-	-	-	-	-	 **/

// Function to Output Clients
// Accepts 1 Ostream Parameter, and 1 Char Parameter
// Returns Void, Passes Data by Member Access
void Client::output(ostream &os, char ori)
{
	/*  	INITIALIZE VARIABLES FOR output()	-	-	-	-	-	-	-	  */
	/** 	Initialize Ints for output()	-	-	-	-	-	-	-	-	 **/
	ori = toupper(ori); // Capitalize Char Parameter Before Check

	/*  	CHECK IF ori IS 'V'	-	-	-	-	-	-	-	-	-	-	-	  */
	/** 	If ori is 'V', Display Client Vertically	-	-	-	-	-	 **/
	if (ori == 'V')
	{
		/***	Display Client Vertically	-	-	-	-	-	-	-	-	***/
		os << setw(15) << "Name: " << Name << endl
		   << setw(15) << "City: " << City << endl
		   << setw(15) << "Region: " << Region << endl
		   << endl;
	}

	/** 	Otherwise, Display Client Horizontally	-	-	-	-	-	-	 **/
	else
	{
		/***	Display Client Horizontally	-	-	-	-	-	-	-	-	***/
		os << setw(15) << Name << ' '
		   << setw(15) << City << ' '
		   << setw(15) << Region << endl;
	}
}

// Function to Output Clients
// Accepts 1 Ostream Parameter, and 1 Client Parameter
// Returns Void, Passes Data by Member Access
ostream &operator<<(ostream &os, Client c)
{

	/*  	DISPLAY CLIENTS	-	-	-	-	-	-	-	-	-	-	-	-	  */
	/** 	Display Clients Vertically	-	-	-	-	-	-	-	-	-	 **/
	c.output(os, 'V');

	/*  	RETURN OSTREAM	-	-	-	-	-	-	-	-	-	-	-	-	  */
	return os;
}

/** 	Define Global Class for Vendors	-	-	-	-	-	-	-	-	-	 **/

class Vendor /*  	INITIALIZE CLASS FOR VENDORS	-	-	-	-	-	-	  */
	: public Firm
{
protected: /*  	PROTECTED MEMBER SECTION FOR CLASS	-	-	-	-	-	-	  */
	/*  	INITIALIZE PROTECTED VARIABLES FOR CLASS	-	-	-	-	-	  */
	/** 	Initialize Protected Ints for Class	-	-	-	-	-	-	-	 **/
	int Quality; // Specify Vendor's Quality

public: /*  	PUBLIC MEMBER SECTION FOR CLASS	-	-	-	-	-	-	-	  */
		/*  	INITIALIZE PUBLIC FUNCTIONS FOR CLASS	-	-	-	-	-	-	  */
		/** 	Initialize Class Constructor Functions	-	-	-	-	-	-	 **/
		// Vendor();
};

/******************************************************************************
 *                                CLASS DEFINITIONS                           *
 ******************************************************************************/

/******************************************************************************
 *                                 Main Function                              *
 ******************************************************************************/

int main()
{
	/*  	INITIALIZE VARIABLES FOR main()	-	-	-	-	-	-	-	-	  */
	/** 	Initialize Arrays for main()	-	-	-	-	-	-	-	-	 **/
	char Choice[30];
	Client Clients[arraySIZE];

	/***	Define Clients in Clients Array	-	-	-	-	-	-	-	-	***/
	Clients[0].set_Name("Nike");
	Clients[0].set_City("Beaverton");
	Clients[0].set_Region('W');

	Clients[1].set_Name("Adidas");
	Clients[1].set_City("Portland");
	Clients[1].set_Region('W');

	Clients[2].set_Name("Daimler");
	Clients[2].set_City("Portland");
	Clients[2].set_Region('W');

	Clients[3].set_Name("Patagonia");
	Clients[3].set_City("Portland");
	Clients[3].set_Region('W');

	/*  	BEGIN PROGRAM	-	-	-	-	-	-	-	-	-	-	-	-	  */
	/** 	Program Introduction	-	-	-	-	-	-	-	-	-	-	 **/
	cout << "Inheritance Program" << endl
		 << endl
		 << "Choose one of the following client firms: " << endl;

	/** 	Loop through Clients Array	-	-	-	-	-	-	-	-	-	 **/
	for (Client c : Clients)
	{
		/** 	Display Clients	-	-	-	-	-	-	-	-	-	-	-	 **/
		cout << c.get_Name() << ' ';
	}

	/** 	Take User Input	-	-	-	-	-	-	-	-	-	-	-	-	 **/
	cout << endl
		 << "Your choice: " << endl;
	cin >> setw(30) >> Choice;

	/** 	Loop through Clients Array	-	-	-	-	-	-	-	-	-	 **/
	for (Client c : Clients)
	{
		if (strcmp(c.get_Name(), Choice) == 0)
		{
			/** 	Display Clients	-	-	-	-	-	-	-	-	-	-	 **/
			c.output(cout, 'V');
		}
	}

	/*  	RETURN 0	-	-	-	-	-	-	-	-	-	-	-	-	-	  */
	return 0;
}

/******************************************************************************
 *                                 Main Function                              *
 ******************************************************************************/

/******************************************************************************
 *                               GLOBAL DEFINITIONS                           *
 ******************************************************************************/

/******************************************************************************
 *                               GLOBAL DEFINITIONS                           *
 ******************************************************************************/
