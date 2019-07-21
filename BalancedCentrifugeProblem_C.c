//Implementation of The Balanced Centrifuge Problem using the the C language.

//newer versions of visual studio may give you some warnings.
//they can be easily solved. but for the purpose of this code, it's unnecessary.
//with the next 3 lines of code you can avoid those warnings.
//#pragma warning(disable:4996)
//#pragma warning(disable:6011)
//#pragma warning(disable:6385)
//#pragma warning(disable:6031)
//#pragma warning(disable:6386)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int asksUserNumberHoles(void);
int getNumDiffPrimeFactors(int num);
int* getPrimeFactors(int num, int *vec);
int checkForMaxCoeficient(int smallestFactor, int num);
int checkIfSolutionExists(int* _coeficients, int* _primeFactors, int _numPrimeFactors, int index, int _maxCoeficient, int _numCompare);

void main(void)
{
	int _numHoles=0;
	int flagTube = 0;
	int flagFreeSpace = 0;
	int size = 0;
	int* _primeFactors;
	int i = 0;
	int l = 0;
	int m = 0;
	int n = 0;
	int _numTubes = 0;
	int _numFreeSpaces = 0;
	int* _numBalancedTubes;
	int _maxCoeficient = 0;
	int* _coeficients;

	_numHoles = asksUserNumberHoles(); //asks the user for the number of holes in the centrifuge.

	_numBalancedTubes = (int*)malloc(_numHoles * sizeof(int));
	for (i = 0; i < _numHoles; i++)
		_numBalancedTubes[i] = 0;

	size = getNumDiffPrimeFactors(_numHoles); //get how many different prime factors there is in the number of holes.
	
	_primeFactors = (int*)malloc(size * (sizeof(int)));

	getPrimeFactors(_numHoles, _primeFactors); //populates the vector with the different prime factors.

	checkForMaxCoeficient(_primeFactors, _numHoles);


	if (size == 1) //number of holes is a prime number.
	{
		_numBalancedTubes[0] = _numHoles;
	}
	else
	{
		for (i = 0; i < _numHoles; i++)
		{
			flagTube = 0;
			flagFreeSpace = 0;

			_numTubes = i + 1;
			_numFreeSpaces = _numHoles - _numTubes;


			if (flagTube != 1)
			{
				_coeficients = (int*)malloc(size * (sizeof(int)));

				_maxCoeficient = checkForMaxCoeficient(_primeFactors[0], _numTubes);
				if (checkIfSolutionExists(_coeficients, _primeFactors, size, 0, _maxCoeficient, _numTubes))
					flagTube = 1;
			}

			if (flagFreeSpace != 1)
			{
				_coeficients = (int*)malloc(size * (sizeof(int)));

				_maxCoeficient = checkForMaxCoeficient(_primeFactors[0], _numFreeSpaces);
				if (checkIfSolutionExists(_coeficients, _primeFactors, size, 0, _maxCoeficient, _numFreeSpaces))
					flagFreeSpace = 1;
			}

			if (flagFreeSpace && flagTube)
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

		printf("\n\nInsert the number of holes in the centrifuge: ");
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

int* getPrimeFactors(int num, int* vec)
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
			{
				sum = sum + (_coeficients[l] * _primeFactors[l]);
			}
				
			if (sum == _numCompare)
				return 1;
		}
	}

	return 0;
}