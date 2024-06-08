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
 *                                       Tester .cxx                          *
 ******************************************************************************/
/*  	INCLUDE LIBRARIES FOR FILE	-	-	-	-	-	-	-	-	-	-	  */
#include "Tester.h"
/*  	DEFINE NAMESPACE FOR FILE	-	-	-	-	-	-	-	-	-	-	  */
using namespace std;
/******************************************************************************
 *                             FUNCTION DEFINITIONS                           *
 ******************************************************************************/

/*  	DEFINE PUBLIC FUNCTIONS FOR CLASS	-	-	-	-	-	-	-	-	  */
/** 	Define Class Constructor Functions	-	-	-	-	-	-	-	-	 **/

Tester::Tester()
{
	/*  	ZERO OUT INT DATA MEMBER	-	-	-	-	-	-	-	-	-	  */
	_score = 0;
}

Tester::~Tester()
{
	/*  	OVERWRITE DATA WITH NULL CHARACTERS	-	-	-	-	-	-	-	  */
	_name = string(_name.length(), 0);

	/*  	ZERO OUT INT DATA MEMBER	-	-	-	-	-	-	-	-	-	  */
	_score = 0;
}

/** 	Define Protected Member Get Functions	-	-	-	-	-	-	-	 **/

string Tester::get_name()
{
	/*  	RETURN STRING	-	-	-	-	-	-	-	-	-	-	-	-	  */
	return _name;
}

int Tester::get_score()
{
	/*  	RETURN INT	-	-	-	-	-	-	-	-	-	-	-	-	-	  */
	return _score;
}

/** 	Define Protected Member Set Functions	-	-	-	-	-	-	-	 **/

void Tester::set_name(string &a_name)
{
	/*  	SET NAME VARIABLE	-	-	-	-	-	-	-	-	-	-	-	  */
	_name = a_name;
}

void Tester::set_score(int a_score)
{
	/*  	SET SCORE VARIABLE	-	-	-	-	-	-	-	-	-	-	-	  */
	_score = a_score;
}

/******************************************************************************
 *                             FUNCTION DEFINITIONS                           *
 ******************************************************************************/
