/******************************************************************************
Proficiency Demo

Donnie Gilbert
CS162-W1 SP24 Priestley

Purpose of the Program:
Make a Program that can find all of the Prime Numbers between 1 and 1000.

Specification Summary:
Uses Loops, Conditional Statements

Sources:
Watching Mr.Priestley's labs.

"If you don't specify, I may ask you if I can share it."
*******************************************************************************/

/******************************************************************************
 *                              Proficiency Demo .cpp                         *
 ******************************************************************************/
#include <iostream>
#include <vector>
using namespace std;
/******************************************************************************
 *                               GLOBAL DECLARATIONS                          *
 ******************************************************************************/

const int is_primeMax = 1000;

vector<int> Primes;

bool is_prime(int &Number);
void is_primeDisplay();

/******************************************************************************
 *                                                                            *
 ******************************************************************************/

/******************************************************************************
 *                                                                            *
 ******************************************************************************/
int main()
{
	cout << "Prime Numbers between 1 and " << is_primeMax << '.' << endl
		 << endl;

	for (int Number = 2; Number < (is_primeMax + 1); ++Number)
	{
		if (is_prime(Number) == true)
		{
			Primes.push_back(Number);
		}
	}

	is_primeDisplay();

	return 0;
}

/******************************************************************************
 *                                                                            *
 ******************************************************************************/

/******************************************************************************
 *                                                                            *
 ******************************************************************************/
bool is_prime(int &Number)
{
	bool isPrime = true;

	for (int Divisor = 2; isPrime && Divisor < Number; ++Divisor)
	{
		if (Number % Divisor == 0)
		{
			isPrime = false;
		}
	}

	return isPrime;
}

void is_primeDisplay()
{
	for (int Prime = 0; Prime < Primes.size(); ++Prime)
	{
		cout << Primes.at(Prime) << ", ";

		if ((Prime + 1) % 10 == 0)
		{
			cout << endl;
		}
	}

	return;
}

/******************************************************************************
 *                                                                             *
 *******************************************************************************/
