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
 *                                 Week 9 Lab 1 .cpp                          *
 ******************************************************************************/
/*  	INCLUDE LIBRARIES FOR FILE	-	-	-	-	-	-	-	-	-	-	  */
#include <fstream>
#include <iostream>
#include <string>
#include "Tester.h"
#include "Tester.cxx"
/*  	DEFINE NAMESPACE FOR FILE	-	-	-	-	-	-	-	-	-	-	  */
using namespace std;
/******************************************************************************
 *                               GLOBAL DECLARATIONS                          *
 ******************************************************************************/

/*  	INITIALIZE GLOBAL CONSTS FOR FILE	-	-	-	-	-	-	-	-	  */
/** 	Initialize Const Ints for File	-	-	-	-	-	-	-	-	-	 **/
const int arraySIZE = 100; // Specify Maximum Size of File Array

/** 	Initialize Const Strings for File	-	-	-	-	-	-	-	-	 **/
const string
	fileNew = "fileNew.txt",   // Specify Name of New File
	fileScores = "scores.txt"; // Specify Name of Scores File

/*  	INITIALIZE GLOBAL FUNCTIONS FOR FILE	-	-	-	-	-	-	-	  */
/** 	Initialize File Read/Write Functions	-	-	-	-	-	-	-	 **/
bool fileOpen(fstream &fileStream,
			  const string &fileName = fileNew,
			  bool fileIsWriting = false,
			  bool fileIsBinary = false);

/** 	Initialize Array Functions	-	-	-	-	-	-	-	-	-	-	 **/
int loadData(Tester Testers[]);

/******************************************************************************
 *                               GLOBAL DECLARATIONS                          *
 ******************************************************************************/

/******************************************************************************
 *                                 Main Function                              *
 ******************************************************************************/

int main()
{
	/*  	INITIALIZE VARIABLES FOR main()	-	-	-	-	-	-	-	-	  */
	/** 	Initialize Ints for main()	-	-	-	-	-	-	-	-	-	 **/
	int testerSIZE{};

	/** 	Initialize Arrays for main()	-	-	-	-	-	-	-	-	 **/
	Tester Testers[arraySIZE]{};

	/*  	BEGIN PROGRAM	-	-	-	-	-	-	-	-	-	-	-	-	  */
	/** 	Program Introduction	-	-	-	-	-	-	-	-	-	-	 **/
	cout << "Welcome to the Tester Program" << endl;

	/** 	Display File Array	-	-	-	-	-	-	-	-	-	-	-	 **/
	testerSIZE = loadData(Testers);

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

// Function to Open Files
// Accepts:	1 Fstream Parameter for File Stream,
// 			1 String Parameter for File Name,
// Optional	1 Bool Parameter for true == Writing to File. (Default: false)
// Optional	1 Bool Parameter for true == File is Binary. (Default: false)
// Returns Bool, true == File is Open, false == File is Not Open
bool fileOpen(fstream &fileStream, const string &fileName,
			  bool fileIsWriting, bool fileIsBinary)
{
	/*  	CHECK IF OPENING FILE IN BINARY MODE	-	-	-	-	-	-	  */
	/** 	If Opening File in Binary Mode, Open File with ios::binary	-	 **/
	if (fileIsBinary == true)
	{
		/*  	CHECK IF OPENING FSTREAM IN INPUT OR OUTPUT MODE	-	-	  */
		/** 	If Opening Fstream in Output Mode, Open File with ios::out	 **/
		if (fileIsWriting == true)
		{
			/***	Open File with ios::out to Write to File	-	-	-	***/
			fileStream.open(fileName, ios::out | ios::binary);
		}

		/** 	If Opening Fstream in Input Mode, Open File with ios::in	 **/
		else
		{
			/***	Open File with ios::in to Read from File	-	-	-	***/
			fileStream.open(fileName, ios::in | ios::binary);
		}
	}

	/** 	If Opening File in Normal Mode, Open File without ios::binary	 **/
	else
	{
		/*  	CHECK IF OPENING FSTREAM IN INPUT OR OUTPUT MODE	-	-	  */
		/** 	If Opening Fstream in Output Mode, Open File with ios::out	 **/
		if (fileIsWriting == true)
		{
			/***	Open File with ios::out to Write to File	-	-	-	***/
			fileStream.open(fileName, ios::out);
		}

		/** 	If Opening Fstream in Input Mode, Open File with ios::in	 **/
		else
		{
			/***	Open File with ios::in to Read from File	-	-	-	***/
			fileStream.open(fileName, ios::in);
		}
	}

	/*  	CHECK IF FILE IS OPEN	-	-	-	-	-	-	-	-	-	-	  */
	/** 	If File Fails to Open Correctly, Return File is Not Open	-	 **/
	if (!fileStream.is_open())
	{
		/*  	CHECK IF OPENING FSTREAM IN INPUT OR OUTPUT MODE	-	-	  */
		/** 	If Opening Fstream in Output Mode, Output Write Message	-	 **/
		if (fileIsWriting == true)
		{
			/***	Output Write Error Message	-	-	-	-	-	-	-	***/
			cout << "File, " << fileName
				 << ", failed to open in Write Mode" << endl
				 << endl;
		}

		/** 	If Opening Fstream in Input Mode, Output Read Message	-	 **/
		else
		{
			/***	Output Read Error Message	-	-	-	-	-	-	-	***/
			cout << "File, " << fileName
				 << ", failed to open in Read Mode" << endl
				 << endl;
		}

		/***	Return File is Not Open	-	-	-	-	-	-	-	-	-	***/
		return false; // false == File is Not Open
	}

	/** 	If File Opens Correctly, Return File is Open	-	-	-	-	 **/
	else
	{
		/*  	CHECK IF OPENING FSTREAM IN INPUT OR OUTPUT MODE	-	-	  */
		/** 	If Opening Fstream in Output Mode, Output Write Message	-	 **/
		if (fileIsWriting == true)
		{
			/***	Output Write Success Message	-	-	-	-	-	-	***/
			cout << "File, " << fileName
				 << ", opened in Write Mode successfully" << endl
				 << endl;
		}

		/** 	If Opening Fstream in Input Mode, Output Read Message	-	 **/
		else
		{
			/***	Output Read Success Message	-	-	-	-	-	-	-	***/
			cout << "File, " << fileName
				 << ", opened in Read Mode successfully" << endl
				 << endl;
		}

		/***	Return File is Open	-	-	-	-	-	-	-	-	-	-	***/
		return true; // true == File is Open
	}
}

/** 	Define Array Functions	-	-	-	-	-	-	-	-	-	-	-	 **/

// Function to Load Array Data from Files
// Accepts 1 Array Parameter
// Returns Int
int loadData(Tester Testers[])
{
	/*  	INITIALIZE VARIABLES FOR loadData()	-	-	-	-	-	-	-	  */
	/** 	Initialize Ints for loadData()	-	-	-	-	-	-	-	-	 **/
	int dataCount{}; // Specify Int to Count Data

	/** 	Initialize Fstreams for loadData()	-	-	-	-	-	-	-	 **/
	fstream readStream;

	/*  	OPEN FILE IN READ MODE WITH fileOpen()	-	-	-	-	-	-	  */
	/** 	If File Opens Correctly, Read Data from File	-	-	-	-	 **/
	if (fileOpen(readStream, fileScores, false, false))
	{
		/***	Initialize Ints for Reading Data from File	-	-	-	-	***/
		int score; // Specify Int for Scores from File

		/***	Initialize Strings for Reading Data from File	-	-	-	***/
		string name; // Specify String for Names from File

		/*  	READ DATA FROM FILE	-	-	-	-	-	-	-	-	-	-	  */
		/** 	Read Data from File Until End of File or Array Full	-	-	 **/
		do
		{
			/***	Read Name and Score from File	-	-	-	-	-	-	***/
			readStream >> name >> score >> ws; // Use ws for White Space

			/***	Debug Data from File	-	-	-	-	-	-	-	-	***/
			cerr << name << score << endl; // For Debugging

			/*  	FILL ARRAY WITH DATA FROM FILE	-	-	-	-	-	-	  */
			/** 	If readStream is true, Fill Array with Data	-	-	-	 **/
			if (readStream)
			{
				/***	Fill Array with Data	-	-	-	-	-	-	-	***/
				Testers[dataCount].set_name(name);
				Testers[dataCount].set_score(score);
				++dataCount; // Increment Data Counter
			}

		} while (dataCount < arraySIZE && !readStream.eof()); /*  	END LOOP  */
	}

	/** 	If File Fails to Open Correctly, Exit Program	-	-	-	-	 **/
	else
	{
		/*  	EXIT PROGRAM ON ERROR	-	-	-	-	-	-	-	-	-	  */
		exit(1);
	}

	/*  	RETURN INT	-	-	-	-	-	-	-	-	-	-	-	-	-	  */
	return dataCount;
}

/******************************************************************************
 *                               GLOBAL DEFINITIONS                           *
 ******************************************************************************/
