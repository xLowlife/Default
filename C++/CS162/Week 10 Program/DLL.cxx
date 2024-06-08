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
 *                                          DLL .cxx                          *
 ******************************************************************************/
/*  	INCLUDE LIBRARIES FOR FILE	-	-	-	-	-	-	-	-	-	-	  */
#include "DLL.h"
/*  	DEFINE NAMESPACE FOR FILE	-	-	-	-	-	-	-	-	-	-	  */
using namespace std;
/******************************************************************************
 *                             FUNCTION DEFINITIONS                           *
 ******************************************************************************/

/*  	DEFINE PUBLIC FUNCTIONS FOR CLASS	-	-	-	-	-	-	-	-	  */
/** 	Define Node Editing Functions	-	-	-	-	-	-	-	-	-	 **/

// Function to Append Nodes to DLLS
// Accepts 1 Node Pointer Parameter
// Returns Void, Passes Data by Member Access
void DLL::append(Node *target)
{
	/*  	CHECK IF NODE POINTERS POINT TO nullptr	-	-	-	-	-	-	  */
	/** 	If target Node Points to nullptr, Return Void	-	-	-	-	 **/
	if (target == nullptr)
	{
		/***	Client should have sent a pointer to a node to be appended	***/

		/*  	RETURN VOID	-	-	-	-	-	-	-	-	-	-	-	-	  */
		return;
	}

	/** 	Set target Node as End of DLL	-	-	-	-	-	-	-	-	 **/
	target->set_next(nullptr);

	/** 	If tail Node Points to nullptr, Set target to Head Node	-	-	 **/
	if (tail == nullptr)
	{
		/***	Set target Node to Head Node in DLL	-	-	-	-	-	-	***/
		head = target;
		target->set_prev(nullptr);
	}

	/** 	If tail Node does Not Point to nullptr, Append target Node	-	 **/
	else
	{
		/***	Append target Node into DLL	-	-	-	-	-	-	-	-	***/
		tail->set_next(target);
		target->set_prev(tail);
	}

	/** 	Set target Node to Tail Node in DLL	-	-	-	-	-	-	-	 **/
	tail = target;

	/*  	RETURN VOID	-	-	-	-	-	-	-	-	-	-	-	-	-	  */
	return;
}

// Function to Insert Nodes into DLLS
// Accepts 1 Node Pointer Parameter, and 1 Int Parameter
// Returns Bool, Passes Data by Member Access
bool DLL::insert_after(Node *node_ptr, int value)
{
	/*  	INITIALIZE VARIABLES FOR insert_after()	-	-	-	-	-	-	  */
	/** 	Initialize Node Pointers for insert_after()	-	-	-	-	-	 **/
	Node *curr = head; // Specify Pointer to Head Node in DLL

	/*  	CHECK FOR REQUESTED NODE TO INSERT NEW NODE AFTER	-	-	-	  */
	/** 	While curr is Not Requested Node, Loop through DLL	-	-	-	 **/
	while (curr != nullptr && curr->get_data() != value)
	{
		/***	Point to Next Node in DLL	-	-	-	-	-	-	-	-	***/
		curr = curr->get_next();
	}

	/*  	CHECK IF NODE POINTERS POINT TO nullptr	-	-	-	-	-	-	  */
	/** 	If curr Points to nullptr, Return False	-	-	-	-	-	-	 **/
	if (curr == nullptr)
	{
		/***	Return False	-	-	-	-	-	-	-	-	-	-	-	***/
		return false;
	}

	/** 	If Pointer After curr Points to nullptr, Append node_ptr	-	 **/
	if (curr->get_next() == nullptr)
	{
		/***	Append node_ptr into DLL	-	-	-	-	-	-	-	-	***/
		append(node_ptr);
	}

	/** 	If Pointer After curr does Not Point to nullptr, Move Nodes	-	 **/
	else
	{
		/***	Move Nodes in DLL	-	-	-	-	-	-	-	-	-	-	***/
		node_ptr->set_prev(curr);
		node_ptr->set_next(curr->get_next());
		curr->set_next(node_ptr);
	}

	/*  	RETURN BOOL	-	-	-	-	-	-	-	-	-	-	-	-	-	  */
	return true;
}

/** 	Define Display Node Functions	-	-	-	-	-	-	-	-	-	 **/

// Function to Output Nodes in DLLS
// Accepts 1 Int Parameter
// Returns Void, Passes Data by Member Access
void DLL::display(int direction)
{
	/*  	INITIALIZE VARIABLES FOR insert_after()	-	-	-	-	-	-	  */
	/** 	Initialize Node Pointers for insert_after()	-	-	-	-	-	 **/
	Node *curr{}; // Specify Pointer to Current Node

	/*  	CHECK IF DIRECTION IS REVERSE	-	-	-	-	-	-	-	-	  */
	/** 	If Direction is Reverse, Display Reverse Message	-	-	-	 **/
	if (direction == -1)
	{
		/***	Display Reverse Message	-	-	-	-	-	-	-	-	-	***/
		cout << "Reverse ";
	}

	/*  	DISPLAY INTRO FOR insert_after()	-	-	-	-	-	-	-	  */
	cout << "List: " << endl;

	/*  	CHECK IF DIRECTION IS REVERSE AGAIN	-	-	-	-	-	-	-	  */
	/** 	If Direction is Normal, Loop through DLL Normally	-	-	-	 **/
	if (direction == 1)
	{
		/*  	DISPLAY NODES IN DLL	-	-	-	-	-	-	-	-	-	  */
		/** 	Point to Head Node in DLL	-	-	-	-	-	-	-	-	 **/
		curr = head;

		/** 	While curr does Not Point to nullptr, Loop through DLL	-	 **/
		while (curr != nullptr)
		{
			/***	Display Current Node, then Point to Next Node	-	-	***/
			cout << curr->get_data() << endl;
			curr = curr->get_next();
		}
	}

	/** 	If Direction is Reverse, Loop through DLL in Reverse	-	-	 **/
	else
	{
		/*  	DISPLAY NODES IN DLL	-	-	-	-	-	-	-	-	-	  */
		/** 	Point to Tail Node in DLL	-	-	-	-	-	-	-	-	 **/
		curr = tail;

		/** 	While curr does Not Point to nullptr, Loop through DLL	-	 **/
		while (curr != nullptr)
		{
			/***	Display Current Node, then Point to Previous Node	-	***/
			cout << curr->get_data() << endl;
			curr = curr->get_prev();
		}
	}

	/*  	Output New Line	-	-	-	-	-	-	-	-	-	-	-	-	  */
	cout << endl;

	/*  	RETURN VOID	-	-	-	-	-	-	-	-	-	-	-	-	-	  */
	return;
}

/******************************************************************************
 *                             FUNCTION DEFINITIONS                           *
 ******************************************************************************/
