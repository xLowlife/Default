/******************************************************************************
Week 5 Lab 1

Donnie Gilbert
CS162-W1 SP24 Priestley

Specification Summary:
Define a Student struct that has a fixed size.
Fields (data members) are last, first, and age.
Make sure your program declares an array,
assigns values to the array,
writes the array to a file and then reads the file into a second array.
Also make sure that you can seek to a specific student in the file,
and read in just that student to a standalone struct variable.

Sources:
Watching Mr.Priestley's labs.

"If you don't specify, I may ask you if I can share it."
*******************************************************************************/

/******************************************************************************
 *                                 Week 5 Lab 2 .cpp                          *
 ******************************************************************************/
/*  	INCLUDE LIBRARIES FOR FILE	-	-	-	-	-	-	-	-	-	-	  */
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <cstring>
/*  	DEFINE NAMESPACE FOR FILE	-	-	-	-	-	-	-	-	-	-	  */
using namespace std;
/******************************************************************************
 *                               GLOBAL DECLARATIONS                          *
 ******************************************************************************/

/*  	INITIALIZE GLOBAL CONSTS FOR FILE	-	-	-	-	-	-	-	-	  */
/** 	Initialize Const Ints for File	-	-	-	-	-	-	-	-	-	 **/
const int
	fieldsSIZE = 3,	  // Specify Amount of Fields in Student Struct
	ageSIZE = 2,	  // Specify Size of Age Char Array in Student Struct
	lastSIZE = 19,	  // Specify Size of Last Char Array in Student Struct
	firstSIZE = 20,	  // Specify Size of First Char Array in Student Struct
	StudentsSIZE = 3; // Specify Size of Students Arrays

/** 	Initialize Const Strings for File	-	-	-	-	-	-	-	-	 **/
const string studentFileName = "Students.dat"; // Specify Name of Students File

/*  	INITIALIZE GLOBAL STRUCTS FOR FILE	-	-	-	-	-	-	-	-	  */
/** 	Define Student Structs	-	-	-	-	-	-	-	-	-	-	-	 **/
// Struct that stores Data for Students
// Contains Char Arrays
// Defines Struct
struct Student
{
	/*  	INITIALIZE VARIABLES FOR Student -	-	-	-	-	-	-	-	  */
	/** 	Initialize Ints for Student	-	-	-	-	-	-	-	-	-	 **/
	int age = (-1); // Specify Age of Student

	/** 	Initialize Char Arrays for Student	-	-	-	-	-	-	-	 **/
	char
		last[lastSIZE] = "Student ~ LastName",	  // Specify Last Name
		first[firstSIZE] = "Student ~ FirstName"; // Specify First Name
};

/*  	INITIALIZE GLOBAL FUNCTIONS FOR FILE	-	-	-	-	-	-	-	  */
/** 	Initialize File Read/Write Functions	-	-	-	-	-	-	-	 **/
int rndInt(int, int = 1);
bool FileOpen(fstream &, string = "NewFile.txt", bool = false);
void Initialize(Student[]);
void WriteFile();

/******************************************************************************
 *                               GLOBAL DECLARATIONS                          *
 ******************************************************************************/

/******************************************************************************
 *                                 Main Function                              *
 ******************************************************************************/

int main()
{
	/*  	INITIALIZE ARRAYS FOR main	-	-	-	-	-	-	-	-	-	  */
	/** 	Initialize Student Arrays	-	-	-	-	-	-	-	-	-	 **/
	Student Students[StudentsSIZE]; // Array for Storing Students

	/*  	BEGIN PROGRAM	-	-	-	-	-	-	-	-	-	-	-	-	  */
	Initialize(Students);

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

// Function to Generate Random Number
// Requires 1 Int Parameter to Specify Max Value of Number by Default
// If Entered, also Accepts 1 Int Parameter to Specify Min Value of Number
// Returns Int, passes Data by Member Access
int rndInt(int rndMax, int rndMin)
{
	static bool initialized{false};
	static mt19937 generator; // Mersenne Twister

	// Initialize the random engine if not already done
	if (!initialized)
	{
		// Use a random device to seed the generator
		random_device rd;
		generator.seed(rd());
		initialized = true;
	}

	uniform_int_distribution<int> distribution(rndMin, rndMax);

	// Return Random Number as Int
	return distribution(generator);
}

// Function to Open Files in Binary Mode
// Accepts:	1 Fstream Parameter for File Stream,
// 			1 String Parameter for File Name,
// Optional	1 Bool Parameter for True == Outputting to File. (Default: false)
// Returns Bool, true == File is Open, false == File is Not Open
bool FileOpen(fstream &File, string FileName, bool isFileOut)
{
	/*  	CHECK IF FSTREAM IS INPUT OR OUTPUT	-	-	-	-	-	-	-	  */
	/** 	If Fstream is Output, Open File with ios::out	-	-	-	-	 **/
	if (isFileOut == true)
	{
		/***	Open File with ios::out	-	-	-	-	-	-	-	-	-	***/
		File.open(FileName, ios::out | ios::binary);
	}

	/** 	If Fstream is Input, Open File with ios::in	-	-	-	-	-	 **/
	else
	{
		/***	Open File with ios::in	-	-	-	-	-	-	-	-	-	***/
		File.open(FileName, ios::in | ios::binary);
	}

	/*  	CHECK IF FILE IS OPEN	-	-	-	-	-	-	-	-	-	-	  */
	/** 	If File Fails to Open Correctly, Return File is Not Open	-	 **/
	if (File.fail())
	{
		/***	Output Error Message	-	-	-	-	-	-	-	-	-	***/
		cout << "File, " << FileName << ", failed to open" << endl
			 << endl;

		/***	Return File is Not Open	-	-	-	-	-	-	-	-	-	***/
		return false; // false == File is Not Open
	}

	/** 	If File Opens Correctly, Return File is Open	-	-	-	-	 **/
	else
	{
		/***	Output Success Message	-	-	-	-	-	-	-	-	-	***/
		cout << "File, " << FileName << ", opened successfully" << endl
			 << endl;

		/***	Return File is Open	-	-	-	-	-	-	-	-	-	-	***/
		return true; // true == File is Open
	}
}

// Function to Initialize Student Data from Files
// Accepts 1 Student Array Parameter
// Returns Void
void Initialize(Student Students[StudentsSIZE])
{
	/*  	INITIALIZE VARIABLES FOR Initialize()	-	-	-	-	-	-	  */
	/** 	Initialize Fstreams for Initialize()	-	-	-	-	-	-	 **/
	fstream StudentsIn;

	/*  	OPEN THE FILE WITH FileOpen()	-	-	-	-	-	-	-	-	  */
	/** 	If File Opens Correctly, Retrieve Student Data	-	-	-	-	 **/
	if (FileOpen(StudentsIn, studentFileName, false) == true)
	{
		/***	Initialize Strings for Retrieving Student Data	-	-	-	***/
		string lineTrash; // Initialize Variable for Trash

		/***	Initialize New Students for Retrieving Student Data	-	-	***/
		Student newStudent; // Initialize New Student for Storing Student Data

		/*  	DISPLAY CLIENT DATA	-	-	-	-	-	-	-	-	-	-	  */
		cout << "List of Students:" << endl
			 << endl;
		/** 	Do While File is Not at End of File	-	-	-	-	-	-	 **/
		int i = 1;
		do
		{
			/*  	RETRIEVE CLIENT DATA	-	-	-	-	-	-	-	-	  */
			StudentsIn.read(reinterpret_cast<char *>(&newStudent),
							sizeof(newStudent));

			/** 	Display Each Field for Student	-	-	-	-	-	-	 **/
			cout << "STUDENT " << i << endl
				 << "Age: " << newStudent.age << endl
				 << "First: " << newStudent.first << endl
				 << "Last: " << newStudent.last << endl
				 << endl;

			/***	Advance to Next Line in File	-	-	-	-	-	-	***/
			getline(StudentsIn, lineTrash);

			++i;
		} while (i < 4 /*!StudentsIn.eof()*/); /*  	CHECK IF AT END OF FILE	-	-	  */

		/*  	CLOSE CLIENT FILE WHEN DONE RETRIEVING CLIENT DATA	-	-	  */
		StudentsIn.close();
	}

	/** 	If File Fails to Open Correctly, Call WriteFile Function	-	 **/
	else
	{
		/*  	CALL WriteFile() FUNCTION	-	-	-	-	-	-	-	-	  */
		WriteFile();
	}

	/*  	RETURN VOID	-	-	-	-	-	-	-	-	-	-	-	-	-	  */
	return;
}

// Function to Write Student Data to Files
// Accepts 1 Student Array Parameter
// Returns Void
void WriteFile()
{
	/*  	INITIALIZE VARIABLES FOR WriteFile()	-	-	-	-	-	-	  */
	/** 	Initialize Fstreams for WriteFile() AND OPEN FILE	-	-	-	 **/
	fstream StudentsOut;
	// StudentsOut.write(reinterpret_cast<char *>(ptr), sizeof(numbers));
	// StudentsOut.read(reinterpret_cast<char *>(ptr), sizeof(numbers));

	/** 	Initialize Arrays for WriteFile()	-	-	-	-	-	-	-	 **/
	Student notStudents[StudentsSIZE]; // Array for Storing Students

	/*  	OPEN THE FILE WITH FileOpen()	-	-	-	-	-	-	-	-	  */
	/** 	If File Opens Correctly, Write Student Data to File	-	-	-	 **/
	if (FileOpen(StudentsOut, studentFileName, true) == true)
	{
		/*  	FILL CLIENTS WITH DATA BEFORE WRITING	-	-	-	-	-	  */
		for (int client = 0; client < StudentsSIZE; ++client)
		{
			/** 	Initialize Bools for Filling Students with Data	-	-	 **/
			bool isDone = false; // Specify when Done Checking for Signals

			/*  	FILL CLIENT WITH Last DATA	-	-	-	-	-	-	-	  */
			/** 	Loop through Each Char in Student's First Field	-	-	 **/
			for (int stringChar = 0;
				 !(isDone) && stringChar < firstSIZE;
				 ++stringChar)
			{
				/*  	CHECK FOR SIGNAL TO SWAP CHAR	-	-	-	-	-	  */
				/** 	If Char == '~', Swap '~' for Student Number	-	-	 **/
				if (notStudents[client].last[stringChar] == '~')
				{
					/***	Swap '~' for Student Number	-	-	-	-	-	***/
					notStudents[client].last[stringChar] =
						to_string(client + 1)[0];

					/***	Stop Checking for Signal	-	-	-	-	-	***/
					isDone = true;
				}
			}
			/***	Reset Signal for Next Student	-	-	-	-	-	-	***/
			isDone = false;

			/** 	Loop through Each Char in Student's Last Field	-	-	 **/
			for (int stringChar = 0;
				 !(isDone) && stringChar < lastSIZE;
				 ++stringChar)
			{
				/*  	CHECK FOR SIGNAL TO SWAP CHAR	-	-	-	-	-	  */
				/** 	If Char == '~', Swap '~' for Student Number	-	-	 **/
				if (notStudents[client].first[stringChar] == '~')
				{
					/***	Swap '~' for Student Number	-	-	-	-	-	***/
					notStudents[client].first[stringChar] =
						to_string(client + 1)[0];

					/***	Stop Checking for Signal	-	-	-	-	-	***/
					isDone = true;
				}
			}
			/***	Reset Signal for Next Student	-	-	-	-	-	-	***/
			isDone = false;

			/** 	Add Student Age	-	-	-	-	-	-	-	-	-	-	 **/
			notStudents[client].age = rndInt(30, 18);
		}

		/*  	WRITE CLIENT DATA TO FILE	-	-	-	-	-	-	-	-	  */
		for (int client = 0; client < StudentsSIZE; ++client)
		{
			/** 	Write Students[client] to File	-	-	-	-	-	-	 **/
			StudentsOut.write(reinterpret_cast<char *>(&notStudents[client]),
							  sizeof(notStudents[client]));

			/***	Advance to Next Line in File	-	-	-	-	-	-	***/
			StudentsOut << '\n';
		}

		/*  	CLOSE CLIENT FILE WHEN DONE WRITING CLIENT DATA	-	-	-	  */
		StudentsOut.close();
	}

	/*  	RETURN VOID	-	-	-	-	-	-	-	-	-	-	-	-	-	  */
	return;
}

/******************************************************************************
 *                               GLOBAL DEFINITIONS                           *
 ******************************************************************************/
