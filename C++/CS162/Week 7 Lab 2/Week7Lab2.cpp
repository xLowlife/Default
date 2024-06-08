/******************************************************************************
Week 7 Lab 2

Donnie Gilbert
CS162-W1 SP24 Priestley

Specification Summary:
This program will store a list of products
in a random access file and an array.

Each product will have a SKU (product ID Code),
description, price, and qty.

The lookup feature will allow the user to enter
a SKU. The program will display the related
product from the array, then look it up on the
disk and display it again from the file.

Sources:
Watching Mr.Priestley's labs.

"If you don't specify, I may ask you if I can share it."
*******************************************************************************/

/******************************************************************************
 *                                 Week 7 Lab 2 .cpp                          *
 ******************************************************************************/
/*  	INCLUDE LIBRARIES FOR FILE	-	-	-	-	-	-	-	-	-	-	  */
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <cstring>
/*  	DEFINE NAMESPACE FOR FILE	-	-	-	-	-	-	-	-	-	-	  */
using namespace std;
/******************************************************************************
 *                               GLOBAL DECLARATIONS                          *
 ******************************************************************************/

/*  	INITIALIZE GLOBAL CONSTS FOR FILE	-	-	-	-	-	-	-	-	  */
/** 	Initialize Const Strings for File	-	-	-	-	-	-	-	-	 **/
const string
	fileNew = "fileNew.dat",		   // Specify Name of New File
	fileProducts = "fileProducts.dat"; // Specify Name of Products File

/*  	INITIALIZE GLOBAL FUNCTIONS FOR FILE	-	-	-	-	-	-	-	  */
/** 	Initialize File Read/Write Functions	-	-	-	-	-	-	-	 **/
bool fileOpen(fstream &, string = fileNew, bool = false);

/******************************************************************************
 *                               GLOBAL DECLARATIONS                          *
 ******************************************************************************/

/******************************************************************************
 *                                CLASS DEFINITIONS                           *
 ******************************************************************************/

class Product /*  	INITIALIZE CLASS FOR Products	-	-	-	-	-	-	  */
{
private: /** 	Private Member Section for Product Class	-	-	-	-	 **/
	/*  	INITIALIZE PRIVATE VARIABLES FOR Product CLASS	-	-	-	-	  */
	/** 	Initialize Private Ints for Product Class	-	-	-	-	-	 **/
	static int counter; // Specify Counter of All Products
	int
		serial, // Specify Product's Serial Number
		qty;	// Specify Total Amount of Product

	/** 	Initialize Private Doubles for Product Class	-	-	-	-	 **/
	double price; // Specify Product's Price

	/** 	Initialize Private Char Arrays for Product Class	-	-	-	 **/
	char
		sku[16],  // Specify Product's SKU
		desc[31]; // Specify Product's Description

public: /** 	Public Member Section for Product Class	-	-	-	-	-	 **/
	/*  	INITIALIZE PUBLIC FUNCTIONS FOR Product CLASS	-	-	-	-	  */
	/** 	Initialize Class Constructor Functions	-	-	-	-	-	-	 **/
	Product()
		: serial{++counter}, sku{""}, desc{""}, price{0}, qty{0} {};
	Product(const Product &source);
	Product(const char arg_sku[], const char arg_desc[],
			double arg_price, int arg_qty);
	~Product();

	/** 	Initialize Private Member Get Functions	-	-	-	-	-	-	 **/
	int get_serial() { return serial; }
	char *get_desc() { return desc; }
	operator double() { return price; }

	/** 	Initialize Display Output Functions	-	-	-	-	-	-	-	 **/
	void output(ostream &, char = 'V');
	friend ostream &operator<<(ostream &, Product);
};

/*  	DEFINE PRIVATE VARIABLES FOR Product CLASS	-	-	-	-	-	-	  */
/** 	Define Private Ints for Product Class	-	-	-	-	-	-	-	 **/
int Product::counter = 1000; // Specify Amount in Counter

/*  	DEFINE PUBLIC FUNCTIONS FOR Product CLASS	-	-	-	-	-	-	  */
/** 	Define Class Constructor Functions	-	-	-	-	-	-	-	-	 **/

// Constructor to Copy Private Members to Products
// Accepts 1 Product Parameter
// Returns Void, Passes Data by Member Access
Product::Product(const Product &source)
	: serial{++counter}, price{source.price}, qty{source.qty}
{
	/*  	COPY PRIVATE MEMBERS	-	-	-	-	-	-	-	-	-	-	  */
	/** 	Copy Private Members to Products	-	-	-	-	-	-	-	 **/
	strcpy(sku, source.sku);
	strcpy(desc, source.desc);
}

// Constructor to Copy Private Members to Char Arrays
// Accepts 2 Char Array Parameters, 1 Double Parameter, and 1 Int Parameter
// Returns Void, Passes Data by Member Access
Product::Product(const char arg_sku[], const char arg_desc[],
				 double arg_price, int arg_qty)
	: serial{++counter}, price{arg_price}, qty{arg_qty}
{

	/*  	COPY PRIVATE MEMBERS	-	-	-	-	-	-	-	-	-	-	  */
	/** 	Copy Private Members to Char Arrays	-	-	-	-	-	-	-	 **/
	strcpy(sku, arg_sku);
	strcpy(desc, arg_desc);
}

// Default Deconstructor for Product
// Accepts No Parameters
// Returns Void, Passes Data by Member Access
Product::~Product()
{
}

/** 	Define Display Output Functions	-	-	-	-	-	-	-	-	-	 **/

// Function to Output Products
// Accepts 1 Ostream Parameter, and 1 Char Parameter
// Returns Void, Passes Data by Member Access
void Product::output(ostream &os, char ori)
{
	/*  	INITIALIZE VARIABLES FOR output()	-	-	-	-	-	-	-	  */
	/** 	Initialize Ints for output()	-	-	-	-	-	-	-	-	 **/
	ori = toupper(ori); // Capitalize Char Parameter Before Check

	/*  	CHECK IF ori IS 'V'	-	-	-	-	-	-	-	-	-	-	-	  */
	/** 	If ori is 'V', Display Product Vertically	-	-	-	-	-	 **/
	if (ori == 'V')
	{
		/***	Display Product Vertically	-	-	-	-	-	-	-	-	***/
		os << setw(15) << "Serial #: " << serial << endl
		   << setw(15) << "SKU: " << sku << endl
		   << setw(15) << "Description: " << desc << endl
		   << setw(15) << "Price: " << price << endl
		   << setw(15) << "On Hand: " << qty << endl
		   << endl;
	}

	/** 	Otherwise, Display Product Horizontally	-	-	-	-	-	-	 **/
	else
	{
		/***	Display Product Horizontally	-	-	-	-	-	-	-	***/
		os << setw(10) << serial << ' '
		   << setw(15) << sku << ' '
		   << setw(30) << desc << ' '
		   << setw(9) << setprecision(2) << fixed << price << ' '
		   << setw(9) << qty << endl;
	}
}

// Function to Output Products
// Accepts 1 Ostream Parameter, and 1 Product Parameter
// Returns Void, Passes Data by Member Access
ostream &operator<<(ostream &os, Product p)
{

	/*  	DISPLAY PRODUCTS	-	-	-	-	-	-	-	-	-	-	-	  */
	/** 	Display Products Vertically	-	-	-	-	-	-	-	-	-	 **/
	p.output(os, 'V');

	/*  	RETURN OSTREAM	-	-	-	-	-	-	-	-	-	-	-	-	  */
	return os;
}

/******************************************************************************
 *                                CLASS DEFINITIONS                           *
 ******************************************************************************/

/******************************************************************************
 *                                 Main Function                              *
 ******************************************************************************/

int main()
{
	/*  	INITIALIZE VARIABLES FOR main()	-	-	-	-	-	-	-	-	  */
	/** 	Initialize Doubles for main()	-	-	-	-	-	-	-	-	 **/
	double x = 0.0;

	/** 	Initialize Products for main()	-	-	-	-	-	-	-	-	 **/
	Product p1{"RB", "Raisin Bran", 6.99, 100};
	Product p2{p1};

	/*  	BEGIN PROGRAM	-	-	-	-	-	-	-	-	-	-	-	-	  */
	/** 	Intro Message	-	-	-	-	-	-	-	-	-	-	-	-	 **/
	cout << "Product Lookup Program" << endl
		 << endl;

	/** 	Display Products	-	-	-	-	-	-	-	-	-	-	-	 **/
	/***	Display Products Serials, and Descriptions	-	-	-	-	-	***/
	// cout << p1.get_serial() << " " << p1.get_desc() << endl
	//	 << p2.get_serial() << " " << p2.get_desc() << endl;

	/***	Display Products Vertically	-	-	-	-	-	-	-	-	-	***/
	p1.output(cout);
	p2.output(cout);

	/***	Display Products Horizontally	-	-	-	-	-	-	-	-	***/
	p1.output(cout, 'H');
	p2.output(cout, 'H');

	/***	Display Doubles with Products	-	-	-	-	-	-	-	-	***/
	x = p1;

	cout << endl
		 << "x is " << x << endl
		 << p1;

	/*  	RETURN 0	-	-	-	-	-	-	-	-	-	-	-	-	-	  */
	return 0;
}

/******************************************************************************
 *                                 Main Function                              *
 ******************************************************************************/

/******************************************************************************
 *                               GLOBAL DEFINITIONS                           *
 ******************************************************************************/

/*  	DEFINE GLOBAL FUNCTIONS FOR FILE	-	-	-	-	-	-	-	-	  */
/** 	Define File Read/Write Functions	-	-	-	-	-	-	-	-	 **/

// Function to Open Files in Binary Mode
// Accepts:	1 Fstream Parameter for File Stream,
// 			1 String Parameter for File Name,
// Optional	1 Bool Parameter for true == Outputting to File. (Default: false)
// Returns Bool, true == File is Open, false == File is Not Open
bool FileOpen(fstream &fileStream, string fileName, bool fileIsOut)
{
	/*  	CHECK IF FSTREAM IS INPUT OR OUTPUT	-	-	-	-	-	-	-	  */
	/** 	If Fstream is Output, Open File with ios::out	-	-	-	-	 **/
	if (fileIsOut == true)
	{
		/***	Open File with ios::out	-	-	-	-	-	-	-	-	-	***/
		fileStream.open(fileName, ios::out | ios::binary);
	}

	/** 	If Fstream is Input, Open File with ios::in	-	-	-	-	-	 **/
	else
	{
		/***	Open File with ios::in	-	-	-	-	-	-	-	-	-	***/
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
