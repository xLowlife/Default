/******************************************************************************
Week 5 Lab 2

Donnie Gilbert
CS162-W1 SP24 Priestley

Specification Summary:
Define a Client struct that has a fixed size.
Have a main that calls a function called Initialize.
The Initialize function attempts to open a file called customersOut.dat.
If the file is not found to open, then it calls a function called WriteFile.
The WriteFile function populates a struct array of size 3,
and writes the array to a binary file, then closes the file and returns.
Now the Initialize function can be certain that it can open the file,
because either it existed or it was just created.
Initialize now opens the file and reads in the customer array and returns.

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
	fieldsSIZE = 5,	 // Specify Amount of Fields in Client Struct
	idSIZE = 5,		 // Specify Size of ID Char Array in Client Struct
	nameSIZE = 14,	 // Specify Size of Name Char Array in Client Struct
	citySIZE = 14,	 // Specify Size of City Char Array in Client Struct
	stateSIZE = 15,	 // Specify Size of State Char Array in Client Struct
	typeSIZE = 14,	 // Specify Size of Type Char Array in Client Struct
	ClientsSIZE = 3; // Specify Size of Clients Arrays

/** 	Initialize Const Strings for File	-	-	-	-	-	-	-	-	 **/
const string clientFileName = "customers.dat"; // Specify Name of Clients File

/*  	INITIALIZE GLOBAL STRUCTS FOR FILE	-	-	-	-	-	-	-	-	  */
/** 	Define Client Structs	-	-	-	-	-	-	-	-	-	-	-	 **/
// Struct that stores Data for Clients
// Contains Char Arrays
// Defines Struct
struct Client
{
	/*  	INITIALIZE VARIABLES FOR Client -	-	-	-	-	-	-	-	  */
	/** 	Initialize Char Arrays for Client	-	-	-	-	-	-	-	 **/
	char
		id[idSIZE] = "000~",				 // Specify ID of Client
		name[nameSIZE] = "Client ~ Name",	 // Specify Name of Client
		city[citySIZE] = "Client ~ City",	 // Specify City of Client
		state[stateSIZE] = "Client ~ State", // Specify State of Client
		type[typeSIZE] = "Client ~ Type";	 // Specify Type of Client
};

/*  	INITIALIZE GLOBAL FUNCTIONS FOR FILE	-	-	-	-	-	-	-	  */
/** 	Initialize File Read/Write Functions	-	-	-	-	-	-	-	 **/
void Initialize(Client[]);
void WriteFile(Client[]);

/******************************************************************************
 *                               GLOBAL DECLARATIONS                          *
 ******************************************************************************/

/******************************************************************************
 *                                 Main Function                              *
 ******************************************************************************/

int main()
{
	/*  	INITIALIZE ARRAYS FOR main	-	-	-	-	-	-	-	-	-	  */
	/** 	Initialize Client Arrays	-	-	-	-	-	-	-	-	-	 **/
	Client Clients[ClientsSIZE]; // Array for Storing Clients

	/*  	BEGIN PROGRAM	-	-	-	-	-	-	-	-	-	-	-	-	  */
	Initialize(Clients);

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
// Function to Initialize Client Data from Files
// Accepts 1 Client Array Parameter
// Returns Void
void Initialize(Client Clients[ClientsSIZE])
{
	/*  	INITIALIZE VARIABLES FOR Initialize()	-	-	-	-	-	-	  */
	/** 	Initialize Fstreams for Initialize()	-	-	-	-	-	-	 **/
	fstream customersIn; // Specify Input Stream of Clients File

	/*  	OPEN THE FILE WITH clientFileName	-	-	-	-	-	-	-	  */
	customersIn.open(clientFileName, ios::in | ios::binary);
	/** 	If File Opens Correctly, Retrieve Client Data	-	-	-	-	 **/
	if (customersIn.is_open())
	{
		/***	Output Success Message	-	-	-	-	-	-	-	-	-	***/
		cout << "File, " << clientFileName << ", opened successfully" << endl
			 << endl;

		/***	Initialize Strings for Retrieving Client Data	-	-	-	***/
		string lineTrash; // Initialize Variable for Trash

		/***	Initialize New Clients for Retrieving Client Data	-	-	***/
		Client newClient; // Initialize New Client for Storing Client Data

		/*  	DISPLAY CLIENT DATA	-	-	-	-	-	-	-	-	-	-	  */
		cout << "List of Clients:" << endl
			 << endl;
		/** 	Do While File is Not at End of File	-	-	-	-	-	-	 **/
		do
		{
			/*  	RETRIEVE CLIENT DATA	-	-	-	-	-	-	-	-	  */
			customersIn.read(reinterpret_cast<char *>(&newClient),
							 sizeof(newClient));

			/** 	Display Each Field for Client	-	-	-	-	-	-	 **/
			cout << "CLIENT " << stoi(newClient.id) << endl
				 << "ID: " << newClient.id << endl
				 << "NAME: " << newClient.name << endl
				 << "CITY: " << newClient.city << endl
				 << "STATE: " << newClient.state << endl
				 << "TYPE: " << newClient.type << endl
				 << endl;

			/***	Advance to Next Line in File	-	-	-	-	-	-	***/
			getline(customersIn, lineTrash);

		} while (!customersIn.eof()); /*  	CHECK IF AT END OF FILE	-	-	  */

		/*  	CLOSE CLIENT FILE WHEN DONE RETRIEVING CLIENT DATA	-	-	  */
		customersIn.close();
	}

	/** 	If File Fails to Open Correctly, Call WriteFile Function	-	 **/
	else
	{
		/***	Output Error Message	-	-	-	-	-	-	-	-	-	***/
		cout << "File, " << clientFileName << ", failed to open" << endl
			 << endl
			 << "WriteFile() Function Called"
			 << endl;

		/*  	CALL WriteFile() FUNCTION	-	-	-	-	-	-	-	-	  */
		WriteFile(Clients);
	}

	/*  	RETURN VOID	-	-	-	-	-	-	-	-	-	-	-	-	-	  */
	return;
}

// Function to Write Client Data to Files
// Accepts 1 Client Array Parameter
// Returns Void
void WriteFile(Client Clients[ClientsSIZE])
{
	/*  	INITIALIZE VARIABLES FOR WriteFile()	-	-	-	-	-	-	  */
	/** 	Initialize Fstreams for WriteFile() AND OPEN FILE	-	-	-	 **/
	fstream customersOut(clientFileName, ios::out | ios::binary);

	/*  	CHECK IF FILE IS OPEN	-	-	-	-	-	-	-	-	-	-	  */
	/** 	If File Opens Correctly, Write Client Data to File	-	-	-	 **/
	if (customersOut.is_open())
	{
		/***	Output Success Message	-	-	-	-	-	-	-	-	-	***/
		cout << "File, " << clientFileName << ", opened successfully" << endl
			 << endl;

		/*  	FILL CLIENTS WITH DATA BEFORE WRITING	-	-	-	-	-	  */
		for (int client = 0; client < ClientsSIZE; ++client)
		{
			/** 	Initialize Bools for Filling Clients with Data	-	-	 **/
			bool isDone = false; // Specify when Done Checking for Signals

			/*  	FILL CLIENT WITH ID DATA	-	-	-	-	-	-	-	  */
			/** 	Loop through Each Char in Client's ID Field	-	-	-	 **/
			for (int stringChar = 0;
				 !(isDone) && stringChar < idSIZE;
				 ++stringChar)
			{
				/*  	CHECK FOR SIGNAL TO SWAP CHAR	-	-	-	-	-	  */
				/** 	If Char == '~', Swap '~' for Client Number	-	-	 **/
				if (Clients[client].id[stringChar] == '~')
				{
					/***	Swap '~' for Client Number	-	-	-	-	-	***/
					Clients[client].id[stringChar] =
						to_string(client + 1)[0];

					/***	Stop Checking for Signal	-	-	-	-	-	***/
					isDone = true;
				}
			}
			/***	Reset Signal for Next Client	-	-	-	-	-	-	***/
			isDone = false;

			/** 	Loop through Each Char in Client's Name Field	-	-	 **/
			for (int stringChar = 0;
				 !(isDone) && stringChar < nameSIZE;
				 ++stringChar)
			{
				/*  	CHECK FOR SIGNAL TO SWAP CHAR	-	-	-	-	-	  */
				/** 	If Char == '~', Swap '~' for Client Number	-	-	 **/
				if (Clients[client].name[stringChar] == '~')
				{
					/***	Swap '~' for Client Number	-	-	-	-	-	***/
					Clients[client].name[stringChar] =
						to_string(client + 1)[0];

					/***	Stop Checking for Signal	-	-	-	-	-	***/
					isDone = true;
				}
			}
			/***	Reset Signal for Next Client	-	-	-	-	-	-	***/
			isDone = false;

			/** 	Loop through Each Char in Client's City Field	-	-	 **/
			for (int stringChar = 0;
				 !(isDone) && stringChar < citySIZE;
				 ++stringChar)
			{
				/*  	CHECK FOR SIGNAL TO SWAP CHAR	-	-	-	-	-	  */
				/** 	If Char == '~', Swap '~' for Client Number	-	-	 **/
				if (Clients[client].city[stringChar] == '~')
				{
					/***	Swap '~' for Client Number	-	-	-	-	-	***/
					Clients[client].city[stringChar] =
						to_string(client + 1)[0];

					/***	Stop Checking for Signal	-	-	-	-	-	***/
					isDone = true;
				}
			}
			/***	Reset Signal for Next Client	-	-	-	-	-	-	***/
			isDone = false;

			/** 	Loop through Each Char in Client's State Field	-	-	 **/
			for (int stringChar = 0;
				 !(isDone) && stringChar < stateSIZE;
				 ++stringChar)
			{
				/*  	CHECK FOR SIGNAL TO SWAP CHAR	-	-	-	-	-	  */
				/** 	If Char == '~', Swap '~' for Client Number	-	-	 **/
				if (Clients[client].state[stringChar] == '~')
				{
					/***	Swap '~' for Client Number	-	-	-	-	-	***/
					Clients[client].state[stringChar] =
						to_string(client + 1)[0];

					/***	Stop Checking for Signal	-	-	-	-	-	***/
					isDone = true;
				}
			}
			/***	Reset Signal for Next Client	-	-	-	-	-	-	***/
			isDone = false;

			/** 	Loop through Each Char in Client's Type Field	-	-	 **/
			for (int stringChar = 0;
				 !(isDone) && stringChar < typeSIZE;
				 ++stringChar)
			{
				/*  	CHECK FOR SIGNAL TO SWAP CHAR	-	-	-	-	-	  */
				/** 	If Char == '~', Swap '~' for Client Number	-	-	 **/
				if (Clients[client].type[stringChar] == '~')
				{
					/***	Swap '~' for Client Number	-	-	-	-	-	***/
					Clients[client].type[stringChar] =
						to_string(client + 1)[0];

					/***	Stop Checking for Signal	-	-	-	-	-	***/
					isDone = true;
				}
			}
			/***	Reset Signal for Next Client	-	-	-	-	-	-	***/
			isDone = false;
		}

		/*  	WRITE CLIENT DATA TO FILE	-	-	-	-	-	-	-	-	  */
		for (int client = 0; client < ClientsSIZE; ++client)
		{
			/** 	Write Clients[client] to File	-	-	-	-	-	-	 **/
			customersOut.write(reinterpret_cast<char *>(&Clients[client]),
							   sizeof(Clients[client]));

			/***	Advance to Next Line in File	-	-	-	-	-	-	***/
			customersOut << '\n';
		}

		/*  	CLOSE CLIENT FILE WHEN DONE WRITING CLIENT DATA	-	-	-	  */
		customersOut.close();
	}

	/** 	If File Fails to Open Correctly, Output Error Message	-	-	 **/
	else
	{
		/***	Output Error Message	-	-	-	-	-	-	-	-	-	***/
		cout << "File, " << clientFileName << ", failed to open" << endl
			 << endl;
	}

	/*  	RETURN VOID	-	-	-	-	-	-	-	-	-	-	-	-	-	  */
	return;
}

/******************************************************************************
 *                               GLOBAL DEFINITIONS                           *
 ******************************************************************************/
