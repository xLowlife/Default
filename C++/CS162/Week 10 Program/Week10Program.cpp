/******************************************************************************
Week 10 Program

Donnie Gilbert
CS162-W1 SP24 Priestley

Specification Summary:


Sources:
Watching Mr.Priestley's labs.

"If you don't specify, I may ask you if I can share it."
*******************************************************************************/

/******************************************************************************
 *                              Week 10 Program .cpp                          *
 ******************************************************************************/
/*  	INCLUDE LIBRARIES FOR FILE	-	-	-	-	-	-	-	-	-	-	  */
#include <fstream>
#include <iostream>
#include <string>
#include "DLL.h"
#include "DLL.cxx"
/*  	DEFINE NAMESPACE FOR FILE	-	-	-	-	-	-	-	-	-	-	  */
using namespace std;
/******************************************************************************
 *                               GLOBAL DECLARATIONS                          *
 ******************************************************************************/

/*  	INITIALIZE GLOBAL CONSTS FOR FILE	-	-	-	-	-	-	-	-	  */
/** 	Initialize Const Strings for File	-	-	-	-	-	-	-	-	 **/
const string
	fileNew = "fileNew.dat",   // Specify Name of New File
	fileDLLs = "fileDLLs.dat"; // Specify Name of Nodes File

/*  	INITIALIZE GLOBAL FUNCTIONS FOR FILE	-	-	-	-	-	-	-	  */
/** 	Initialize File Read/Write Functions	-	-	-	-	-	-	-	 **/
bool fileOpen(fstream &fileStream,
			  const string &fileName = fileNew,
			  bool fileIsWriting = false,
			  bool fileIsBinary = false);

/******************************************************************************
 *                               GLOBAL DECLARATIONS                          *
 ******************************************************************************/

/******************************************************************************
 *                                 Main Function                              *
 ******************************************************************************/

int main()
{
	/*  	INITIALIZE VARIABLES FOR main()	-	-	-	-	-	-	-	-	  */
	/** 	Initialize DLLs for main()	-	-	-	-	-	-	-	-	-	 **/
	DLL dll; // Specify DLL for Storing Nodes

	/** 	Initialize Node Pointers for main()	-	-	-	-	-	-	-	 **/
	Node *node_ptr; // Specify Pointer for Pointing to Nodes

	/*  	BEGIN PROGRAM	-	-	-	-	-	-	-	-	-	-	-	-	  */
	/** 	Program Introduction	-	-	-	-	-	-	-	-	-	-	 **/
	cout << "Welcome to our Doubly Linked List Program" << endl;

	/** 	Display Nodes in DLL	-	-	-	-	-	-	-	-	-	-	 **/
	dll.display();

	/** 	Point to Nodes in DLL	-	-	-	-	-	-	-	-	-	-	 **/
	node_ptr = new Node(15);

	/** 	Append Nodes into DLL	-	-	-	-	-	-	-	-	-	-	 **/
	dll.append(node_ptr);
	dll.append(new Node(7));
	dll.append(new Node(13));
	dll.append(new Node(3));
	dll.append(new Node(10));

	/** 	Display Nodes in DLL	-	-	-	-	-	-	-	-	-	-	 **/
	dll.display();

	/** 	Append Nodes into DLL	-	-	-	-	-	-	-	-	-	-	 **/
	dll.append(new Node(7));

	/** 	Display Nodes in DLL	-	-	-	-	-	-	-	-	-	-	 **/
	dll.display();

	/** 	Display Nodes in DLL	-	-	-	-	-	-	-	-	-	-	 **/
	dll.display(-1);

	/** 	Append Nodes into DLL	-	-	-	-	-	-	-	-	-	-	 **/
	dll.append(new Node(18));

	/** 	Display Nodes in DLL	-	-	-	-	-	-	-	-	-	-	 **/
	dll.display();

	/** 	Display Nodes in DLL	-	-	-	-	-	-	-	-	-	-	 **/
	dll.display(-1);

	/** 	Point to Nodes in DLL	-	-	-	-	-	-	-	-	-	-	 **/
	node_ptr = new Node(5);

	/** 	Insert Nodes into DLL	-	-	-	-	-	-	-	-	-	-	 **/
	if (!dll.insert_after(node_ptr, 15))
	{
		cout << "Insertion after 15 failed. \n";
	}

	/** 	Display Nodes in DLL	-	-	-	-	-	-	-	-	-	-	 **/
	dll.display();

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

/******************************************************************************
 *                               GLOBAL DEFINITIONS                           *
 ******************************************************************************/
