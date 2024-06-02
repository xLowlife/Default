/******************************************************************************
Week 6 Lab 1

Donnie Gilbert
CS162-W1 SP24 Priestley

Specification Summary:
Prep for Upcoming Program for Week 6

Sources:
Watching Mr.Priestley's labs.

"If you don't specify, I may ask you if I can share it."
*******************************************************************************/

/******************************************************************************
 *                                 Week 6 Lab 1 .cpp                          *
 ******************************************************************************/
/*  	INCLUDE LIBRARIES FOR FILE	-	-	-	-	-	-	-	-	-	-	  */
#include <fstream>
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
const string fileNew = "fileNew.dat"; // Specify Name of New File

/*  	INITIALIZE GLOBAL FUNCTIONS FOR FILE	-	-	-	-	-	-	-	  */
/** 	Initialize File Read/Write Functions	-	-	-	-	-	-	-	 **/
bool fileOpen(fstream &, string = fileNew, bool = false);

/******************************************************************************
 *                               GLOBAL DECLARATIONS                          *
 ******************************************************************************/

/******************************************************************************
 *                                CLASS DEFINITIONS                           *
 ******************************************************************************/

class Point /*  	INITIALIZE CLASS FOR Points	-	-	-	-	-	-	-	  */
{
private: /** 	Private Member Section for Point Class	-	-	-	-	-	 **/
	/*  	INITIALIZE PRIVATE VARIABLES FOR POINT CLASS	-	-	-	-	  */
	/** 	Initialize Private Doubles for Point Class	-	-	-	-	-	 **/
	double x;
	double y;

public: /** 	Public Member Section for Point Class	-	-	-	-	-	 **/
	/*  	INITIALIZE PUBLIC FUNCTIONS FOR POINT CLASS	-	-	-	-	-	  */
	/** 	Initialize Class Constructor Functions	-	-	-	-	-	-	 **/
	Point();
	Point(double, double);
	~Point();

	/** 	Initialize Display Output Functions	-	-	-	-	-	-	-	 **/
	void output(ostream &);
	friend ostream &operator<<(ostream &os, Point p);
};

/*  	DEFINE PUBLIC FUNCTIONS FOR POINT CLASS	-	-	-	-	-	-	-	  */
/** 	Define Class Constructor Functions	-	-	-	-	-	-	-	-	 **/
Point::Point()
{
	x = 0.0;
	y = 0.0;
}

Point::Point(double arg_x, double arg_y)
{
	x = arg_x;
	y = arg_y;
}

Point::~Point()
{
	x = 0.0;
	y = 0.0;
}

/** 	Define Display Output Functions	-	-	-	-	-	-	-	-	-	 **/
void Point::output(ostream &os)
{
	os << '(' << x << ", " << y << ')';
};

ostream &operator<<(ostream &os, Point p)
{
	// os << '(' << x << ", " << y << ')';
	p.output(os);
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
	/** 	Initialize Points for main()	-	-	-	-	-	-	-	-	 **/
	Point a;
	Point b(5.0, 10.0);

	/*  	BEGIN PROGRAM	-	-	-	-	-	-	-	-	-	-	-	-	  */
	cout << "Hello World\n";

	cout << "Point B is ";
	b.output(cout);
	cout << endl;

	cout << "Point A is " << a << " and Point B is " << b << '.' << endl;

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
// Optional	1 Bool Parameter for True == Outputting to File. (Default: false)
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
