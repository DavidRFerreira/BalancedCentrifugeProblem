//Implementation of The Balanced Centrifuge Problem using the the C language.

//newer versions of visual studio may give you some warnings.
//they can be easily solved. but for the purpose of this code, it's unnecessary.
//with the next 3 lines of code you can avoid those warnings.
#pragma warning(disable:4996)
#pragma warning(disable:6011)
#pragma warning(disable:6385)
#pragma warning(disable:6031)
#pragma warning(disable:6386)

#include <stdio.h>
#include <stdlib.h>

int asksUserNumberHoles(void); //asks user to input the number of holes in the centrifuge.
int getNumDiffPrimeFactors(int num); //returns the number of different prime factors of the number of holes.
int getPrimeFactors(int num, int *vec); //returns an array with the prime factors of the number of holes.
int checkForMaxCoeficient(int smallestFactor, int num); //returns the biggest coeficient that can be a solution to the problem (worst case scenario).
//brute force to find if _numCompare can be written as sums of the prime factors of the number of holes (it's not the most elegant solution).
int checkIfSolutionExists(int* _coeficients, int* _primeFactors, int _numPrimeFactors, int index, int _maxCoeficient, int _numCompare); 

void main(void)
{
	int _numHoles=0;
	int flagTube = 0;
	int flagFreeSpace = 0;
	int size = 0; //will represent the number of different prime factors of _numHoles.
	int* _primeFactors; //array that will contain the prime factors of _numHoles.
	int i = 0, l = 0, m = 0, n = 0;
	int _numTubes = 0;
	int _numFreeSpaces = 0;
	int* _numBalancedTubes; //array that will contain the number of tubes for which is possible to obtain a balanced-configuration.
	int _maxCoeficient = 0;
	int* _coeficients;

	_numHoles = asksUserNumberHoles(); //asks the user to input the number of holes in the centrifuge.

	 //at most, there will be as many number of tubes (for which are possible the balanced-configuration) as the number of holes in the centrifuge.
	_numBalancedTubes = (int*)malloc(_numHoles * sizeof(int));
	for (i = 0; i < _numHoles; i++)
		_numBalancedTubes[i] = 0;

	size = getNumDiffPrimeFactors(_numHoles); //get how many different prime factors there is for the number of holes.
	
	_primeFactors = (int*)malloc(size * (sizeof(int)));

	getPrimeFactors(_numHoles, _primeFactors); //populates the array with the different prime factors.

	if (size == 1) //if the number of holes is a prime number, the only solution is the number of holes itself. 
	{
		_numBalancedTubes[0] = _numHoles;
	}
	else
	{
		for (i = 0; i < _numHoles; i++) //we will verify the possibility for every number of tubes from 1 to the number of holes.
		{
			flagTube = 0;
			flagFreeSpace = 0;

			_numTubes = i + 1;
			_numFreeSpaces = _numHoles - _numTubes;

			//let's verify if the number of test tubes satisfies the necessary condition for this problem.
			_coeficients = (int*)malloc(size * (sizeof(int)));

			_maxCoeficient = checkForMaxCoeficient(_primeFactors[0], _numTubes);
			if (checkIfSolutionExists(_coeficients, _primeFactors, size, 0, _maxCoeficient, _numTubes))
				flagTube = 1;

			//now, let's verify if the number of empty spots satisfies the necessary condition for this problem.
			_coeficients = (int*)malloc(size * (sizeof(int)));

			_maxCoeficient = checkForMaxCoeficient(_primeFactors[0], _numFreeSpaces);
			if (checkIfSolutionExists(_coeficients, _primeFactors, size, 0, _maxCoeficient, _numFreeSpaces))
				flagFreeSpace = 1;

			if (flagFreeSpace && flagTube) //if both conditions are satisfied.
			{
				_numBalancedTubes[m] = _numTubes; 
				m++;
			}
		}
	}
	
	printf("\n\n You can have a balance configuration in a %d-hole centrifuge with: ", _numHoles);

	for (l = 0; l < _numHoles; l++)
	{
		if (_numBalancedTubes[l] != 0)
			printf(" %d, ", _numBalancedTubes[l]);
	}
		
	printf(" test tubes.");

	printf("\n\n");
}

int asksUserNumberHoles(void)
{
	int flag1 = 0;
	int n;

	do
	{
		flag1 = 1;

		printf("Insert the number of holes in the centrifuge: ");
		scanf("%d", &n);

		if (n<= 0)
		{
			printf("The number inserted is not acceptable!");
			flag1 = 0;
		}

	} while (!flag1);

	return n;
}

int getNumDiffPrimeFactors(int num)
{
	int i=0, j=0;
	int _isPrime = 1;
	int _numDifferentPrimeFactors = 0;

	for (i = 2; i <= num; i++)
	{
		if (num % i == 0)
		{
			_isPrime = 1;

			for (j = 2; j <= i / 2; j++)
			{
				if (i % j == 0)
				{
					_isPrime = 0;
					break;
				}	
			}

			if (_isPrime)
				_numDifferentPrimeFactors++;
		}
	}

	return _numDifferentPrimeFactors;
}

int getPrimeFactors(int num, int* vec)
{
	int i = 0, j = 0, l=0;
	int _isPrime = 1;

	for (i = 2; i <= num; i++)
	{
		if (num % i == 0)
		{
			_isPrime = 1;

			for (j = 2; j <= i / 2; j++)
			{
				if (i % j == 0)
				{
					_isPrime = 0;
					break;
				}
			}

			if (_isPrime)
			{
				vec[l] = i;
				l++;
			}
		}
	}
}

/* Important Explanation:
	Disclaimer: this sure is not an elegant solution or method.

	Let's assume that we are testing if we can get a balanced-configuration with 7 test tubes in a 12-hole centrifuge.
	(the prime factors of 12 are 2 and 3)
	We can have that balanced-configuration if and only we find the (positive or null) solutions for the next equation to be possible:
	7 = (a * 2) + (b * 3).
	So, we need to find an 'a' and 'b' (that can be positive or zero) so that equation is possible. 

	We know that the biggest number that both coeficients (a and b) can assume is the number we get from diving 7 by the smallest prime factor + 1.
	(7 / 2) + 1 = 4 (since we are working with integers).
	(this is what the function checkForMaxCoeficient() will do)

	This will be our worst case scenario. So, in the function checkIfSolutionExists(), we will brute force to see if we can find a solution of 'a' and 'b'
	that satisfies the equation above. By knowing the worst case scenario, we can limit our options for both values, so if we don't find any solution we
	know when to stop (in this case, when we test for a = b = 4 (that of course, it's not possible, but at least we know when to stop to find a solution).

	So, basically, in this example, we are going to test if the equation is possible when:
	a = 0, b = 0;
	a = 1, b = 0;
	a = 2, b = 0;
	a = 3, b = 0;
	a = 4, b = 0;
	...
	a = 0, b = 1;
	a = 1, b = 1;
	a = 3, b = 1;
	...
	a = 0, b = 2;
	a = 1, b = 2;
	...
	...
	...
	a = 4, b = 4;

	If the equation is satisfied, we will stop immediately our brute force and the function will return 1.
	Otherwise, when we reach our worst case scenario without finding a suitable solution the function will return 0.
*/


int checkForMaxCoeficient(int smallestFactor, int num)
{
	int maxcoeficient;
	
	maxcoeficient = (num / smallestFactor) + 1; 

	return maxcoeficient;
}


int checkIfSolutionExists(int* _coeficients, int* _primeFactors, int _numPrimeFactors, int index, int _maxCoeficient, int _numCompare)
{
	int i = 0;
	int l = 0;
	int sum = 0;

	for (i = 0; i <= _maxCoeficient; i++)
	{
		_coeficients[index] = i;

		if (index != _numPrimeFactors - 1)
		{
			if (checkIfSolutionExists(_coeficients, _primeFactors, _numPrimeFactors, index + 1, _maxCoeficient, _numCompare))
				return 1;
		}
		else
		{
			sum = 0;

			for (l = 0; l < _numPrimeFactors; l++)
				sum = sum + (_coeficients[l] * _primeFactors[l]);
				
			if (sum == _numCompare) //if the condition is verified.
				return 1;
		}
	}

	return 0;
}