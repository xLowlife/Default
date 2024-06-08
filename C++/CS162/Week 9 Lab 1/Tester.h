/******************************************************************************
Week 9 Lab 1

Donnie Gilbert
CS162-W1 SP24 Priestley

Specification Summary:


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
