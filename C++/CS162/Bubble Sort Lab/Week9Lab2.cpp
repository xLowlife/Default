/******************************************************************************
Week 9 Lab 2

Donnie Gilbert
CS162-W1 SP24 Priestley

Specification Summary:


Sources:
Watching Mr.Priestley's labs.

"If you don't specify, I may ask you if I can share it."
*******************************************************************************/

/******************************************************************************
 *                                 Week 9 Lab 2 .cpp                          *
 ******************************************************************************/
/*  	INCLUDE LIBRARIES FOR FILE	-	-	-	-	-	-	-	-	-	-	  */
#include <iostream>
/*  	DEFINE NAMESPACE FOR FILE	-	-	-	-	-	-	-	-	-	-	  */
using namespace std;
/******************************************************************************
 *                               GLOBAL DECLARATIONS                          *
 ******************************************************************************/

/*  	INITIALIZE GLOBAL CONSTS FOR FILE	-	-	-	-	-	-	-	-	  */
/** 	Initialize Const Ints for File	-	-	-	-	-	-	-	-	-	 **/
// const int arraySIZE = 4; // Specify Size of File Array

/*  	INITIALIZE GLOBAL FUNCTIONS FOR FILE	-	-	-	-	-	-	-	  */
/** 	Initialize Array Functions	-	-	-	-	-	-	-	-	-	-	 **/
void Display(int fileArray[], int arraySIZE);
void BubbleSort(int fileArray[], int arraySIZE);

/******************************************************************************
 *                               GLOBAL DECLARATIONS                          *
 ******************************************************************************/

/******************************************************************************
 *                                 Main Function                              *
 ******************************************************************************/

int main()
{
	/*  	INITIALIZE VARIABLES FOR main()	-	-	-	-	-	-	-	-	  */
	/** 	Initialize Arrays for main()	-	-	-	-	-	-	-	-	 **/
	int fileArray[]{7, 6, 2, 9, 5, 3};

	/** 	Initialize Ints for main()	-	-	-	-	-	-	-	-	-	 **/
	int arraySIZE = (sizeof(fileArray) / sizeof(fileArray[0]));

	/*  	BEGIN PROGRAM	-	-	-	-	-	-	-	-	-	-	-	-	  */
	/** 	Program Introduction	-	-	-	-	-	-	-	-	-	-	 **/
	cout
		<< "Bubble Sort Demo" << endl
		<< "We are going to sort the following list: " << endl;

	/** 	Display File Array	-	-	-	-	-	-	-	-	-	-	-	 **/
	Display(fileArray, arraySIZE);

	/** 	Sort File Array	-	-	-	-	-	-	-	-	-	-	-	-	 **/
	BubbleSort(fileArray, arraySIZE);

	/** 	Sorted Message	-	-	-	-	-	-	-	-	-	-	-	-	 **/
	cout << "The final array is as follows: " << endl;

	/** 	Display Sorted File Array	-	-	-	-	-	-	-	-	-	 **/
	Display(fileArray, arraySIZE);

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
/** 	Define Array Functions	-	-	-	-	-	-	-	-	-	-	-	 **/

// Function to Output Array Data
// Accepts 1 Array Parameter, and 1 Int Parameter for Array Size
// Returns Void, Passes Data by Member Access
void Display(int fileArray[], int arraySIZE)
{
	/*  	DISPLAY DATA IN FILE ARRAY	-	-	-	-	-	-	-	-	-	  */
	/** 	Loop through Data in File Array	-	-	-	-	-	-	-	-	 **/
	for (int idx = 0; idx < arraySIZE; ++idx)
	{
		/***	Display fileArray[idx]	-	-	-	-	-	-	-	-	-	***/
		cout << fileArray[idx] << ' ';
	}

	/***	Output New Line	-	-	-	-	-	-	-	-	-	-	-	-	***/
	cout << endl;

	/*  	RETURN VOID	-	-	-	-	-	-	-	-	-	-	-	-	-	  */
	return;
}

// Function to Sort Array Data with Bubble Sort Method
// Accepts 1 Array Parameter, and 1 Int Parameter for Array Size
// Returns Void, Passes Data by Member Access
void BubbleSort(int fileArray[], int arraySIZE)
{
	/*  	INITIALIZE VARIABLES FOR BubbleSort()	-	-	-	-	-	-	  */
	/** 	Initialize Ints for BubbleSort()	-	-	-	-	-	-	-	 **/
	int temp; // Specify Temporary Int for Sorting

	/*  	SORT DATA IN FILE ARRAY	-	-	-	-	-	-	-	-	-	-	  */
	/** 	Loop through Data in File Array	-	-	-	-	-	-	-	-	 **/
	for (int i = 0; i < (arraySIZE - 1); ++i)
	{
		/***	Loop through Data in File Array - j	-	-	-	-	-	-	***/
		for (int j = 0; j < (arraySIZE - 1 - i); ++j)
		{
			/*  	CHECK IF NEXT DATA IS LESS THAN CURRENT DATA	-	-	  */
			/** 	If Next Data is Less Than Current Data, Sort Data	-	 **/
			if (fileArray[j + 1] < fileArray[j])
			{
				/***	Sort Data in File Array	-	-	-	-	-	-	-	***/
				temp = fileArray[j];
				fileArray[j] = fileArray[j + 1];
				fileArray[j + 1] = temp;
			}
		}
	}

	/*  	RETURN VOID	-	-	-	-	-	-	-	-	-	-	-	-	-	  */
	return;
}

/******************************************************************************
 *                               GLOBAL DEFINITIONS                           *
 ******************************************************************************/
