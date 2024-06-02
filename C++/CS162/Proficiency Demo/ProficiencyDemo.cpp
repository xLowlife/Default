/******************************************************************************
Proficiency Demo

Donnie Gilbert
CS162-W1 SP24 Priestley

Purpose of the Program:
Make a Program that can find all of the Prime Numbers between 1 and 1000.

Specification Summary:
Uses Loops, Conditional Statements, and Vectors.

Sources:
Watching Mr.Priestley's labs.

"If you don't specify, I may ask you if I can share it."
*******************************************************************************/

/******************************************************************************
 *                             Proficiency Demo .cpp                          *
 ******************************************************************************/
/*  	INCLUDE LIBRARIES FOR FILE	-	-	-	-	-	-	-	-	-	-	  */
#include <iostream>
#include <vector>
/*  	DEFINE NAMESPACE FOR FILE	-	-	-	-	-	-	-	-	-	-	  */
using namespace std;
/******************************************************************************
 *                               GLOBAL DECLARATIONS                          *
 ******************************************************************************/

/*  	INITIALIZE GLOBAL CONSTS FOR FILE	-	-	-	-	-	-	-	-	  */
/** 	Initialize Const Ints for File	-	-	-	-	-	-	-	-	-	 **/
const int isPrimeMax = 1000; // Specify Max Number for isPrime to Loop through

/** 	Initialize Vectors for File	-	-	-	-	-	-	-	-	-	-	 **/
vector<int> Primes;

/*  	INITIALIZE GLOBAL FUNCTIONS FOR FILE	-	-	-	-	-	-	-	  */
/** 	Initialize Prime Checking Functions	-	-	-	-	-	-	-	-	 **/
void isPrime();
void isPrimeDisplay();

/******************************************************************************
 *                               GLOBAL DECLARATIONS                          *
 ******************************************************************************/

/******************************************************************************
 *                                 Main Function                              *
 ******************************************************************************/

int main()
{
	/*  	BEGIN PROGRAM	-	-	-	-	-	-	-	-	-	-	-	-	  */
	/** 	Intro Message	-	-	-	-	-	-	-	-	-	-	-	-	 **/
	cout << "Prime Numbers Between 1 and " << isPrimeMax << ':' << endl
		 << endl;

	/** 	Check for Prime Numbers	-	-	-	-	-	-	-	-	-	-	 **/
	isPrime();

	/***	Display Prime Numbers	-	-	-	-	-	-	-	-	-	-	***/
	isPrimeDisplay();

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
/** 	Define Prime Checking Functions	-	-	-	-	-	-	-	-	-	 **/

// Function to Check if Numbers are Prime
// Accepts No Parameters
// Returns Void
void isPrime()
{
	/*  	CHECK FOR PRIME NUMBERS	-	-	-	-	-	-	-	-	-	-	  */
	/** 	Loop through Numbers from 2 to (isPrimeMax + 1)	-	-	-	-	 **/
	for (int Number = 2; Number < (isPrimeMax + 1); ++Number)
	{
		/***	Initialize Bools for Checking for Prime Numbers	-	-	-	***/
		bool isPrime = true;

		/*  	CHECK FOR PRIME NUMBERS	-	-	-	-	-	-	-	-	-	  */
		/** 	Loop through Divisors from 2 to Number	-	-	-	-	-	 **/
		for (int Divisor = 2; isPrime && Divisor < Number; ++Divisor)
		{
			/*  	CHECK NUMBER IS PRIME	-	-	-	-	-	-	-	-	  */
			/** 	If Number is Not Prime, Specify Number is Not Prime	-	 **/
			if (Number % Divisor == 0)
			{
				/***	Specify Number is Not Prime	-	-	-	-	-	-	***/
				isPrime = false;
			}
		}

		/*  	CHECK NUMBER IS PRIME	-	-	-	-	-	-	-	-	-	  */
		/** 	If Number is Prime, Add to Primes Vector	-	-	-	-	 **/
		if (isPrime == true)
		{
			/***	Add to Primes Vector	-	-	-	-	-	-	-	-	***/
			Primes.push_back(Number);
		}
	}

	/*  	RETURN VOID	-	-	-	-	-	-	-	-	-	-	-	-	-	  */
	return;
}

// Function to Display Prime Numbers from isPrime()
// Accepts No Parameters
// Returns Void
void isPrimeDisplay()
{
	/*  	DISPLAY PRIME NUMBERS	-	-	-	-	-	-	-	-	-	-	  */
	/** 	Loop through Prime Numbers in Primes Vector	-	-	-	-	-	 **/
	for (int Prime = 0; Prime < Primes.size(); ++Prime)
	{
		/***	Display Prime Numbers Seperated by Commas	-	-	-	-	***/
		cout << Primes.at(Prime) << ",\t";

		/*  	CHECK HOW MANY PRIMES DISPLAYED	-	-	-	-	-	-	-	  */
		/** 	If Number of Displayed Primes is 10, Output Newline	-	-	 **/
		if ((Prime + 1) % 10 == 0)
		{
			/***	Output Newline for More Primes	-	-	-	-	-	-	***/
			cout << endl;
		}
	}

	/*  	RETURN VOID	-	-	-	-	-	-	-	-	-	-	-	-	-	  */
	return;
}

/******************************************************************************
 *                               GLOBAL DEFINITIONS                           *
 ******************************************************************************/
