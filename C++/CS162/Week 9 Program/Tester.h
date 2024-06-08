/******************************************************************************
Week 9 Program

Donnie Gilbert
CS162-W1 SP24 Priestley

Specification Summary:
Part 1
define a class "Tester" that will store a string name and int score
data members should be protected
public accessors (getters) should be provided
public mutators (setters) should be provided
it is okay to use string objects this time,
because we won't be using a random access file
opens a sample sequential text data file to read
uses a loop to read names and ints into array "tester" of type Tester
until it reaches the end of the file OR
reaches the maximum size of the array (const MAX = 100)
data pairs should be counted as they are read in and count should be retained
displays all data on screen, one name and number per line, from the array,
using a function call (e.g., to void DisplayAll(Tester arr[], int size)
demonstrates that it can look up data by name using a linear (sequential) search

Part 2
goes on to sort the array according to the int data member using selection sort,
thereby ordering the data in ascending numeric order by score (see Chapter 8)
displays all data on screen, one name and number per line
demonstrates that it can look up data by score using a binary search
prompts user to enter a score
program finds at least one person with that score and displays their info

Part 3
goes on to sort array according to the string data member using bubble sort,
thereby ordering the data alphabetically by name
demonstrates that it can look up data by name using a binary search
lists the names of the person(s) with the highest score
lists the names of the person(s) with the lowest score

This is my final lab/program submission and I just want to be done.
I feel like I've been staring at this screen for years.

Sources:
Watching Mr.Priestley's labs.

"If you don't specify, I may ask you if I can share it."
*******************************************************************************/

/******************************************************************************
 *                                       Tester .h                            *
 ******************************************************************************/
/*  	DEFINE FILE AS HEADER FILE	-	-	-	-	-	-	-	-	-	-	  */
#ifndef TESTER_H
#define TESTER_H
/*  	INCLUDE LIBRARIES FOR FILE	-	-	-	-	-	-	-	-	-	-	  */
#include <string>
/*  	DEFINE NAMESPACE FOR FILE	-	-	-	-	-	-	-	-	-	-	  */
using namespace std;
/******************************************************************************
 *                               GLOBAL DECLARATIONS                          *
 ******************************************************************************/

/******************************************************************************
 *                               GLOBAL DECLARATIONS                          *
 ******************************************************************************/

/******************************************************************************
 *                                CLASS DEFINITIONS                           *
 ******************************************************************************/

class Tester /*  	INITIALIZE CLASS FOR TESTERS	-	-	-	-	-	-	  */
{
protected: /*  	PROTECTED MEMBER SECTION FOR CLASS	-	-	-	-	-	-	  */
	/*  	INITIALIZE PROTECTED VARIABLES FOR CLASS	-	-	-	-	-	  */
	/** 	Initialize Protected Ints for Class	-	-	-	-	-	-	-	 **/
	int _score{};

	/** 	Initialize Protected Strings for Class	-	-	-	-	-	-	 **/
	string _name{};

public: /*  	PUBLIC MEMBER SECTION FOR CLASS	-	-	-	-	-	-	-	  */
	/*  	INITIALIZE PUBLIC FUNCTIONS FOR CLASS	-	-	-	-	-	-	  */
	/** 	Initialize Class Constructor Functions	-	-	-	-	-	-	 **/
	Tester();
	virtual ~Tester();

	/** 	Initialize Protected Member Get Functions	-	-	-	-	-	 **/
	string get_name();
	int get_score();

	/** 	Initialize Protected Member Set Functions	-	-	-	-	-	 **/
	void set_name(string &a_name);
	void set_score(int a_score);
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

#endif /*  	TESTER_H	-	-	-	-	-	-	-	-	-	-	-	-	-	  */
