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
 *                                          DLL .h                            *
 ******************************************************************************/
/*  	DEFINE FILE AS HEADER FILE	-	-	-	-	-	-	-	-	-	-	  */
#ifndef DLL_H
#define DLL_H
/*  	INCLUDE LIBRARIES FOR FILE	-	-	-	-	-	-	-	-	-	-	  */
#include <iostream>
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

/*  	DEFINE GLOBAL CLASSES FOR FILE	-	-	-	-	-	-	-	-	-	  */
/** 	Define Global Class for Nodes	-	-	-	-	-	-	-	-	-	 **/

class Node /*  	INITIALIZE CLASS FOR NODES	-	-	-	-	-	-	-	-	  */
{
protected: /*  	PROTECTED MEMBER SECTION FOR CLASS	-	-	-	-	-	-	  */
	/*  	INITIALIZE PROTECTED VARIABLES FOR CLASS	-	-	-	-	-	  */
	/** 	Initialize Protected Ints for Class	-	-	-	-	-	-	-	 **/
	int data{}; // Specify Data Stored in Node

	/** 	Initialize Protected Nodes for Class	-	-	-	-	-	-	 **/
	Node
		*next, // Specify Pointer to Next Node in DLL
		*prev; // Specify Pointer to Previous Node in DLL

public: /*  	PUBLIC MEMBER SECTION FOR CLASS	-	-	-	-	-	-	-	  */
	/*  	INITIALIZE PUBLIC FUNCTIONS FOR CLASS	-	-	-	-	-	-	  */
	/** 	Initialize Class Constructor Functions	-	-	-	-	-	-	 **/
	Node() : data{}, next{}, prev{} {}
	Node(int a_data) : data{a_data}, next{}, prev{} {}

	/** 	Initialize Protected Member Accesor Functions	-	-	-	-	 **/
	int get_data() const { return data; }
	Node *get_next() const { return next; }
	Node *get_prev() const { return prev; }

	/** 	Initialize Protected Member Mutator Functions	-	-	-	-	 **/
	void set_next(Node *a_next) { next = a_next; }
	void set_prev(Node *a_prev) { prev = a_prev; }
};

/** 	Define Global Class for DLLs	-	-	-	-	-	-	-	-	-	 **/

class DLL /*  	INITIALIZE CLASS FOR DLLS	-	-	-	-	-	-	-	-	  */
{
protected: /*  	PROTECTED MEMBER SECTION FOR CLASS	-	-	-	-	-	-	  */
	/*  	INITIALIZE PROTECTED VARIABLES FOR CLASS	-	-	-	-	-	  */
	/** 	Initialize Protected Nodes for Class	-	-	-	-	-	-	 **/
	Node
		*head, // Specify Pointer to Head of DLL
		*tail; // Specify Pointer to Tail of DLL

public: /*  	PUBLIC MEMBER SECTION FOR CLASS	-	-	-	-	-	-	-	  */
	/*  	INITIALIZE PUBLIC FUNCTIONS FOR CLASS	-	-	-	-	-	-	  */
	/** 	Initialize Class Constructor Functions	-	-	-	-	-	-	 **/
	DLL() : head{}, tail{} {}

	/** 	Initialize Node Editing Functions	-	-	-	-	-	-	-	 **/
	void append(Node *);
	bool insert_after(Node *, int);

	/** 	Initialize Display Node Functions	-	-	-	-	-	-	-	 **/
	void display(int direction = 1);
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

#endif /*  	DLL_H	-	-	-	-	-	-	-	-	-	-	-	-	-	-	  */
