/******************************************************************************
Week 6 Lab 2

Donnie Gilbert
CS162-W1 SP24 Priestley

Specification Summary:
Implement a member function that returns a bool,
true if the argument matches the Point object's x value and false otherwise.
Implement a member function that overloads the + operator to add two points.
Implement a member function that overloads the * operator
to multiply a Point left operand by a double right operand.
Implement a friend function that overloads the * operator
to multiply a double left operand by a Point right operand.
Implement a non-member friend function called Square
that returns the square of a Point by squaring each of its operands,
but does not modify the argument passed to it.
Implement a non-member non-friend function called DispPair
that displays a pair of Points with the word " and " between them
(all to the console).

Sources:
Watching Mr.Priestley's labs.

"If you don't specify, I may ask you if I can share it."
*******************************************************************************/

/******************************************************************************
 *                                 Week 6 Lab 2 .cpp                          *
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

	/** 	Initialize Operator Overload Functions	-	-	-	-	-	-	 **/
	bool match(double value);
	Point operator+(const Point other);
	Point operator*(double d);

	/** 	Initialize Class Friend Functions	-	-	-	-	-	-	-	 **/
	friend Point operator*(double d, const Point &p);
	friend Point Square(const Point &p);
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
	return;
};

ostream &operator<<(ostream &os, Point p)
{
	// os << '(' << x << ", " << y << ')';
	p.output(os);
	return os;
}

/** 	Define Operator Overload Functions	-	-	-	-	-	-	-	-	 **/
bool Point::match(double value)
{
	return x == value;
}

Point Point::operator+(const Point other)
{
	return Point(x + other.x, y + other.y);
}

Point Point::operator*(double d)
{
	return Point(x * d, y * d);
}

/** 	Define Class Friend Functions	-	-	-	-	-	-	-	-	-	 **/
Point operator*(double d, Point &p)
{
	return p * d;
}

Point Square(const Point &p)
{
	return Point(p.x * p.x, p.y * p.y);
}

void outputPoint(const Point &p1, const Point &p2);

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

	cout << "The two points are ";
	outputPoint(a, b);
	cout << '.' << endl;

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

/** 	Define Display Output Functions	-	-	-	-	-	-	-	-	-	 **/

// Function to Output Points
// Accepts 2 Point Parameters
// Returns Void
void outputPoint(Point &p1, Point &p2)
{
	p1.output(cout);
	cout << " and ";
	p2.output(cout);

	/*  	RETURN VOID	-	-	-	-	-	-	-	-	-	-	-	-	-	  */
	return;
}

/******************************************************************************
 *                               GLOBAL DEFINITIONS                           *
 ******************************************************************************/
