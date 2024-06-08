/******************************************************************************
Week 7 Program

Donnie Gilbert
CS162-W1 SP24 Priestley

Specification Summary:
- Define a class to store a student record.
- Include a method to write the class to the console screen.
- Declare an array of this class in a file.
- Populate at least four entries in the array with sample data.
- Write the data to a random access binary file, then close the file.
- Open the file as random access,
  and read the student information into the array of students.
- Prompt the user to enter a student ID.
- Search the array for the student,
  and display the student information on the screen in a nice format.

Also:
- Calculate where in the file the student with this ID can be found.
- Go directly there with ID and index, and get the student info in a variable.
- Display this student's information to the user.

Provide a menu for the user containing at least three options:
- Display a list of all the objects, or display squares of the object(s).
- Ask the user to choose to edit the object to change one of its values.

Sources:
Watching Mr.Priestley's labs.

"If you don't specify, I may ask you if I can share it."
*******************************************************************************/

/******************************************************************************
 *                               Week 7 Program .cpp                          *
 ******************************************************************************/
/*  	INCLUDE LIBRARIES FOR FILE	-	-	-	-	-	-	-	-	-	-	  */
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
/*  	DEFINE NAMESPACE FOR FILE	-	-	-	-	-	-	-	-	-	-	  */
using namespace std;
/******************************************************************************
 *                               GLOBAL DECLARATIONS                          *
 ******************************************************************************/

/*  	INITIALIZE GLOBAL CONSTS FOR FILE	-	-	-	-	-	-	-	-	  */
/** 	Initialize Const Ints for File	-	-	-	-	-	-	-	-	-	 **/
const int
	arraySIZE = 4, // Specify Size of File Array
	idSIZE = 5;	   // Specify Length of Student ID

/** 	Initialize Const Strings for File	-	-	-	-	-	-	-	-	 **/
const string
	fileNew = "fileNew.dat",		 // Specify Name of New File
	fileStudent = "fileStudent.dat"; // Specify Name of Student File

/*  	INITIALIZE GLOBAL CLASSES FOR FILE	-	-	-	-	-	-	-	-	  */
/** 	Initialize Global Class for Students	-	-	-	-	-	-	-	 **/
class Student;

/*  	INITIALIZE GLOBAL FUNCTIONS FOR FILE	-	-	-	-	-	-	-	  */
/** 	Initialize File Read/Write Functions	-	-	-	-	-	-	-	 **/
bool fileOpen(fstream &,
			  const string &fileName = fileNew,
			  bool fileIsWriting = false);

void fileRead(Student[],
			  const string &fileName = fileNew,
			  int fileData = (-1));

void fileWrite(Student[],
			   const string &fileName = fileNew,
			   bool arrayIsEmpty = false);

void fileSearch(Student[],
				const string &fileName = fileNew);

void fileEdit(Student[],
			  const string &fileName = fileNew,
			  int fileData = (-1));

/******************************************************************************
 *                               GLOBAL DECLARATIONS                          *
 ******************************************************************************/

/******************************************************************************
 *                                CLASS DEFINITIONS                           *
 ******************************************************************************/

class Student /*  	INITIALIZE CLASS FOR STUDENTS	-	-	-	-	-	-	  */
{
private: /*  	PRIVATE MEMBER SECTION FOR CLASS	-	-	-	-	-	-	  */
	/*  	INITIALIZE PRIVATE VARIABLES FOR CLASS	-	-	-	-	-	-	  */
	/** 	Initialize Private Ints for Class	-	-	-	-	-	-	-	 **/
	static int counter; // Specify Counter of All Students

	int Id; // Specify Student's ID Number

	/** 	Initialize Private Doubles for Class	-	-	-	-	-	-	 **/
	double Gpa; // Specify Student's GPA

	/** 	Initialize Private Char Arrays for Class	-	-	-	-	-	 **/
	char
		Name[50],  // Specify Student's Name
		Major[50], // Specify Student's Major
		City[50];  // Specify Student's City

public: /*  	PUBLIC MEMBER SECTION FOR CLASS	-	-	-	-	-	-	-	  */
	/*  	INITIALIZE PUBLIC FUNCTIONS FOR CLASS	-	-	-	-	-	-	  */
	/** 	Initialize Class Constructor Functions	-	-	-	-	-	-	 **/
	Student()
		: Id{++counter}, Name{""}, Major{""}, City{""}, Gpa{0} {};
	Student(const Student &source);
	Student(const char arg_Name[], const char arg_Major[],
			const char arg_City[], double arg_Gpa);
	~Student();

	/** 	Initialize Private Member Get Functions	-	-	-	-	-	-	 **/
	int get_Id() { return Id; }
	char *get_Name() { return Name; }
	char *get_Major() { return Major; }
	char *get_City() { return City; }
	operator double() { return Gpa; }

	/** 	Initialize Private Member Set Functions	-	-	-	-	-	-	 **/
	void set_Id(int new_Id) { Id = new_Id; }
	void set_Name(char new_Name[]) { strcpy(Name, new_Name); }
	void set_Major(char new_Major[]) { strcpy(Major, new_Major); }
	void set_City(char new_City[]) { strcpy(City, new_City); }
	void set_Gpa(double new_Gpa) { Gpa = new_Gpa; }

	/** 	Initialize Display Output Functions	-	-	-	-	-	-	-	 **/
	void output(ostream &, char = 'V');
	friend ostream &operator<<(ostream &, Student);
};

/*  	DEFINE PRIVATE VARIABLES FOR CLASS	-	-	-	-	-	-	-	-	  */
/** 	Define Private Ints for Class	-	-	-	-	-	-	-	-	-	 **/
int Student::counter = 1000; // Specify Starting ID Number

/*  	DEFINE PUBLIC FUNCTIONS FOR CLASS	-	-	-	-	-	-	-	-	  */
/** 	Define Class Constructor Functions	-	-	-	-	-	-	-	-	 **/

// Constructor to Copy Private Members to Students
// Accepts 1 Student Parameter
// Returns Void, Passes Data by Member Access
Student::Student(const Student &source)
	: Id{++counter}, Gpa{source.Gpa}
{
	/*  	COPY PRIVATE MEMBERS	-	-	-	-	-	-	-	-	-	-	  */
	/** 	Copy Private Members to Students	-	-	-	-	-	-	-	 **/
	strcpy(Name, source.Name);
	strcpy(Major, source.Major);
	strcpy(City, source.City);
}

// Constructor to Copy Private Members to Char Arrays
// Accepts 2 Char Array Parameters, 1 Double Parameter, and 1 Int Parameter
// Returns Void, Passes Data by Member Access
Student::Student(const char arg_Name[], const char arg_Major[],
				 const char arg_City[], double arg_Gpa)
	: Id{++counter}, Gpa{arg_Gpa}
{

	/*  	COPY PRIVATE MEMBERS	-	-	-	-	-	-	-	-	-	-	  */
	/** 	Copy Private Members to Char Arrays	-	-	-	-	-	-	-	 **/
	strcpy(Name, arg_Name);
	strcpy(Major, arg_Major);
	strcpy(City, arg_City);
}

// Default Deconstructor for Student
// Accepts No Parameters
// Returns Void, Passes Data by Member Access
Student::~Student()
{
}

/** 	Define Display Output Functions	-	-	-	-	-	-	-	-	-	 **/

// Function to Output Students
// Accepts 1 Ostream Parameter, and 1 Char Parameter
// Returns Void, Passes Data by Member Access
void Student::output(ostream &os, char ori)
{
	/*  	INITIALIZE VARIABLES FOR output()	-	-	-	-	-	-	-	  */
	/** 	Initialize Ints for output()	-	-	-	-	-	-	-	-	 **/
	ori = toupper(ori); // Capitalize Char Parameter Before Check

	/*  	CHECK IF ori IS 'V'	-	-	-	-	-	-	-	-	-	-	-	  */
	/** 	If ori is 'V', Display Student Vertically	-	-	-	-	-	 **/
	if (ori == 'V')
	{
		/***	Display Student Vertically	-	-	-	-	-	-	-	-	***/
		os << setw(15) << "ID #: " << Id << endl
		   << setw(15) << "Name: " << Name << endl
		   << setw(15) << "Major: " << Major << endl
		   << setw(15) << "City: " << City << endl
		   << setw(15) << "Gpa: " << setprecision(2) << fixed << Gpa << endl
		   << endl;
	}

	/** 	Otherwise, Display Student Horizontally	-	-	-	-	-	-	 **/
	else
	{
		/***	Display Student Horizontally	-	-	-	-	-	-	-	***/
		os << setw(15) << Id << ' '
		   << setw(15) << Name << ' '
		   << setw(15) << Major << ' '
		   << setw(15) << City << ' '
		   << setw(15) << setprecision(2) << fixed << Gpa << endl;
	}
}

// Function to Output Students
// Accepts 1 Ostream Parameter, and 1 Student Parameter
// Returns Void, Passes Data by Member Access
ostream &operator<<(ostream &os, Student p)
{

	/*  	DISPLAY StudentS	-	-	-	-	-	-	-	-	-	-	-	  */
	/** 	Display Students Vertically	-	-	-	-	-	-	-	-	-	 **/
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
	/** 	Initialize Arrays for main()	-	-	-	-	-	-	-	-	 **/
	Student fileArray[arraySIZE];

	/*  	BEGIN PROGRAM	-	-	-	-	-	-	-	-	-	-	-	-	  */
	/** 	Read Data from Files	-	-	-	-	-	-	-	-	-	-	 **/
	fileRead(fileArray, fileStudent);

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
// Optional	1 Bool Parameter for true == Writing to File. (Default: false)
// Returns Bool, true == File is Open, false == File is Not Open
bool fileOpen(fstream &fileStream, const string &fileName, bool fileIsWriting)
{
	/*  	CHECK IF OPENING FSTREAM IN INPUT OR OUTPUT MODE	-	-	-	  */
	/** 	If Opening Fstream in Output Mode, Open File with ios::out	-	 **/
	if (fileIsWriting == true)
	{
		/***	Open File with ios::out to Write to File	-	-	-	-	***/
		fileStream.open(fileName, ios::out | ios::binary);
	}

	/** 	If Opening Fstream in Input Mode, Open File with ios::in	-	 **/
	else
	{
		/***	Open File with ios::in to Read from File	-	-	-	-	***/
		fileStream.open(fileName, ios::in | ios::binary);
	}

	/*  	CHECK IF FILE IS OPEN	-	-	-	-	-	-	-	-	-	-	  */
	/** 	If File Fails to Open Correctly, Return File is Not Open	-	 **/
	if (fileStream.fail())
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

// Function to Read Data from Open Files
// Accepts:	1 Array Parameter for File Array,
// 			1 String Parameter for File Name.
// Optional	1 Int Parameter for Position of Data in File.
// Returns Void
void fileRead(Student fileArray[], const string &fileName, int fileData)
{
	/*  	INITIALIZE VARIABLES FOR fileRead()	-	-	-	-	-	-	-	  */
	/** 	Initialize Fstreams for fileRead()	-	-	-	-	-	-	-	 **/
	fstream readStream;

	/*  	OPEN FILE IN READ MODE WITH fileOpen()	-	-	-	-	-	-	  */
	/** 	If File Opens Correctly, Read Data from File	-	-	-	-	 **/
	if (fileOpen(readStream, fileName, false))
	{
		/***	Initialize Strings for Reading Data from File	-	-	-	***/
		string lineTrash; // Initialize Variable for Trash from File

		/***	Initialize New Data for Storing Read Data from File	-	-	***/
		Student newStudent;

		/*  	OPEN FILE IN READ MODE WITH fileOpen()	-	-	-	-	-	  */
		/** 	If fileData == (-1), Read All Data from File	-	-	-	 **/
		if (fileData == (-1))
		{
			/*  	DISPLAY DATA INTRO MESSAGE	-	-	-	-	-	-	-	  */
			cout << "List of Data:" << endl;

			/*  	READ DATA FROM FILE	-	-	-	-	-	-	-	-	-	  */
			for (int Data = 0; Data < arraySIZE; ++Data)
			{
				/** 	Read fileArray[Data] from File	-	-	-	-	-	 **/
				readStream.read(
					reinterpret_cast<char *>(&fileArray[Data]),
					sizeof(fileArray[Data]));

				/***	Display Data After Reading	-	-	-	-	-	-	***/
				fileArray[Data].output(cout, 'H');

				/***	Advance to Next Line in File	-	-	-	-	-	***/
				getline(readStream, lineTrash);
			}

			/*  	Output Newline	-	-	-	-	-	-	-	-	-	-	  */
			cout << endl;

			/*  	CLOSE FILE WHEN DONE READING DATA	-	-	-	-	-	  */
			readStream.close();

			/** 	Search Data from Files	-	-	-	-	-	-	-	-	 **/
			fileSearch(fileArray, fileStudent);
		}

		/** 	If fileData != (-1), Read Requested Data from File	-	-	 **/
		else
		{
			/*  	DISPLAY REQUESTED DATA INTRO MESSAGE	-	-	-	-	  */
			cout << "Requested Data from File:" << endl;

			/*  	READ REQUESTED DATA FROM FILE	-	-	-	-	-	-	  */
			for (int Data = 0; Data < fileData; ++Data)
			{
				/***	Advance to Next Line in File	-	-	-	-	-	***/
				getline(readStream, lineTrash);
			}

			/** 	Read Requested fileArray[Data] from File	-	-	-	 **/
			readStream.read(
				reinterpret_cast<char *>(&newStudent),
				sizeof(newStudent));

			/***	Display Data After Reading	-	-	-	-	-	-	-	***/
			newStudent.output(cout, 'V');

			/*  	Output Newline	-	-	-	-	-	-	-	-	-	-	  */
			cout << endl;

			/*  	CLOSE FILE WHEN DONE READING DATA	-	-	-	-	-	  */
			readStream.close();

			/** 	Edit Data from Files	-	-	-	-	-	-	-	-	 **/
			fileEdit(fileArray, fileStudent, fileData);
		}
	}

	/** 	If File Fails to Open Correctly, Create File then Write	-	-	 **/
	else
	{
		/*  	OPEN FILE IN WRITE MODE WITH EMPTY ARRAY	-	-	-	-	  */
		fileWrite(fileArray, fileName, true);
	}

	/*  	RETURN VOID	-	-	-	-	-	-	-	-	-	-	-	-	-	  */
	return;
}

// Function to Write Data to Open Files
// Accepts:	1 Array Parameter for File Array,
// 			1 String Parameter for File Name,
// Optional	1 Bool Parameter for true == Array is Empty. (Default: false)
// Returns Void
void fileWrite(Student fileArray[], const string &fileName, bool arrayIsEmpty)
{
	/*  	INITIALIZE VARIABLES FOR fileWrite()	-	-	-	-	-	-	  */
	/** 	Initialize Fstreams for fileWrite()	-	-	-	-	-	-	-	 **/
	fstream writeStream;

	/*  	CHECK IF ARRAY IS EMPTY	-	-	-	-	-	-	-	-	-	-	  */
	/** 	If Array is Empty, Add New Data to Array	-	-	-	-	-	 **/
	if (arrayIsEmpty == true)
	{
		/***	Initialize New Data for Array	-	-	-	-	-	-	-	***/
		vector<Student> newData;

		Student newData1{"Student 1 Name", "Comp Sci 1", "Portland", 2.50};
		Student newData2{"Student 2 Name", "Comp Sci 2", "Gresham", 3.00};
		Student newData3{"Student 3 Name", "Comp Sci 3", "Troutdale", 3.50};
		Student newData4{"Student 4 Name", "Comp Sci 4", "Beaverton", 4.00};

		newData.push_back(newData1);
		newData.push_back(newData2);
		newData.push_back(newData3);
		newData.push_back(newData4);

		/***	Add New Data to Array	-	-	-	-	-	-	-	-	-	***/
		for (int Data = 0; Data < newData.size(); ++Data)
		{
			fileArray[Data] = newData.at(Data);
		}
	}

	/*  	OPEN FILE IN WRITE MODE WITH fileOpen()	-	-	-	-	-	-	  */
	/** 	If File Opens Correctly, Write Data to File	-	-	-	-	-	 **/
	if (fileOpen(writeStream, fileName, true))
	{
		/*  	WRITE DATA TO FILE	-	-	-	-	-	-	-	-	-	-	  */
		for (int Data = 0; Data < arraySIZE; ++Data)
		{
			/** 	Write fileArray[Data] to File	-	-	-	-	-	-	 **/
			writeStream.write(
				reinterpret_cast<char *>(&fileArray[Data]),
				sizeof(fileArray[Data]));

			/***	Advance to Next Line in File	-	-	-	-	-	-	***/
			writeStream << '\n';
		}

		/*  	CLOSE FILE WHEN DONE WRITING DATA	-	-	-	-	-	-	  */
		writeStream.close();
	}

	/***	Output New Data Success Message	-	-	-	-	-	-	-	-	***/
	cout << "File, " << fileName
		 << ", Created and Filled with Data." << endl
		 << "Please Re-run the program to access Data." << endl
		 << endl;

	/*  	RETURN VOID	-	-	-	-	-	-	-	-	-	-	-	-	-	  */
	return;
}

// Function to Search Data from Open Files
// Accepts:	1 Array Parameter for File Array,
// 			1 String Parameter for File Name.
// Returns Void
void fileSearch(Student fileArray[], const string &fileName)
{
	/*  	INITIALIZE VARIABLES FOR fileSearch()	-	-	-	-	-	-	  */
	/** 	Initialize Arrays for fileSearch()	-	-	-	-	-	-	-	 **/
	char userInput[idSIZE];

	/*  	DISPLAY INTRO FOR fileSearch()	-	-	-	-	-	-	-	-	  */
	cout << "Student Lookup Program" << endl
		 << "Please Enter A Student ID #: ";

	/*  	SEARCH DATA IN FILE	-	-	-	-	-	-	-	-	-	-	-	  */
	cin.get(userInput, idSIZE);
	/** 	Loop through Size of File Array	-	-	-	-	-	-	-	-	 **/
	for (int Data = 0; Data < arraySIZE; ++Data)
	{
		/*  	CHECK IF DATA IS REQUESTED DATA	-	-	-	-	-	-	-	  */
		/** 	If Data is Requested Data, Display Data	-	-	-	-	-	 **/
		if (fileArray[Data].get_Id() == stoi(userInput))
		{
			/***	Display Found Message	-	-	-	-	-	-	-	-	***/
			cout << "Student ID # Matched: "
				 << fileArray[Data].get_Name() << endl
				 << endl;

			/***	Display Data Vertically	-	-	-	-	-	-	-	-	***/
			fileArray[Data].output(cout, 'V');

			/***	Request Data from Files	-	-	-	-	-	-	-	-	***/
			fileRead(fileArray, fileStudent, Data);

			/***	End Search	-	-	-	-	-	-	-	-	-	-	-	***/
			break;
		}
	}

	/*  	RETURN VOID	-	-	-	-	-	-	-	-	-	-	-	-	-	  */
	return;
}

// Function to Edit Data from Open Files
// Accepts:	1 Array Parameter for File Array,
// 			1 String Parameter for File Name.
// Returns Void
void fileEdit(Student fileArray[], const string &fileName, int fileData)
{
	/*  	INITIALIZE VARIABLES FOR fileEdit()	-	-	-	-	-	-	-	  */
	/** 	Initialize Bools for fileEdit()	-	-	-	-	-	-	-	-	 **/
	bool isDone = false;

	/** 	Initialize Arrays for fileEdit()	-	-	-	-	-	-	-	 **/
	char userInput[2];
	char editInput[2];
	char setId[idSIZE];
	char setName[50];
	char setMajor[50];
	char setCity[50];
	char setGpa[idSIZE];

	/*  	DISPLAY INTRO FOR fileEdit()	-	-	-	-	-	-	-	-	  */
	cout << "Would you like to Edit this Student's Data?" << endl
		 << "(1 = Yes, 2 = No): ";

	/*  	CHECK IF USER WANTS TO EDIT DATA IN FILE	-	-	-	-	-	  */
	cin >> userInput;
	cout << endl;
	/** 	If User Enters Yes, Allow them to Edit Data	-	-	-	-	-	 **/
	if (userInput[0] == '1')
	{
		/*  	CHECK WHICH DATA USER WANTS TO EDIT IN FILE	-	-	-	-	  */
		/** 	Take User Input Until Correct Choice Given	-	-	-	-	 **/
		do
		{
			/***	Display Editing Message	-	-	-	-	-	-	-	-	***/
			cout << "What would you like to Edit in Student's Data?" << endl
				 << "(1 = ID, 2 = Name, 3 = Major, 4 = City, 5 = GPA): ";

			/***	Take User Input	-	-	-	-	-	-	-	-	-	-	***/
			cin >> editInput;
			cout << endl;

			/*  	CHECK WHICH DATA USER IS EDITING	-	-	-	-	-	  */
			/** 	If User is Selected Data, Edit Data	-	-	-	-	-	 **/
			switch (editInput[0])
			{
			case '1':
				cout << "Please Enter New ID (xxxx): ";
				cin >> setId;
				fileArray[fileData].set_Id(stoi(setId));
				isDone = true;
				break;
			case '2':
				cout << "Please Enter New Name: ";
				cin >> setName;
				fileArray[fileData].set_Name(setName);
				isDone = true;
				break;
			case '3':
				cout << "Please Enter New Major: ";
				cin >> setMajor;
				fileArray[fileData].set_Major(setMajor);
				isDone = true;
				break;
			case '4':
				cout << "Please Enter New City: ";
				cin >> setCity;
				fileArray[fileData].set_City(setCity);
				isDone = true;
				break;
			case '5':
				cout << "Please Enter New GPA (x.xx): ";
				cin >> setGpa;
				fileArray[fileData].set_Gpa(stod(setGpa));
				isDone = true;
				break;
			default:
				isDone = false;
				break;
			}

			cout << endl;

		} while (isDone != true); /*  	CHECK FOR SIGNAL TO BE DONE	-	-	  */

		/*  	OPEN FILE IN WRITE MODE WITH NEW DATA AND WRITE	-	-	-	  */
		fileWrite(fileArray, fileName);
	}

	/*  	RETURN VOID	-	-	-	-	-	-	-	-	-	-	-	-	-	  */
	return;
}

/******************************************************************************
 *                               GLOBAL DEFINITIONS                           *
 ******************************************************************************/
