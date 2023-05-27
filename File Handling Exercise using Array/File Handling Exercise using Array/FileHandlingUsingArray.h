#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>


#define MyFilePath "   D:\\Bilal\\Sem 3\\Data\\   "
#define MaxNumber 110000

typedef struct MyData
{
	long ID;
	int  group;
}MYDATA, mydata;

/// <summary>
/// Method to remov right trailing character from input string
/// </summary>
/// <param name="szSource"> Source String</param>
/// <param name="charToTrim">Character to remove from Right</param>
/// <returns></returns>
char* rtrim(char* szSource, char* charToTrim)
{
	char* pszEOS;

	// Set pointer to end of string to point to the character just
	//  before the 0 at the end of the string.
	pszEOS = szSource + strlen(szSource) - 1;

	while (pszEOS >= szSource && *pszEOS == *charToTrim)
		*pszEOS-- = '\0';

	return szSource;
}

/// <summary>
/// Method to remove / trim string from left
/// </summary>
/// <param name="szSource">Input String</param>
/// <param name="charToTrim">Character to remove</param>
/// <returns></returns>
char* ltrim(char* szSource, char* charToTrim)
{
	char* pszEOS;
	int		i;

	// Set pointer to start of string to point to the character

	pszEOS = szSource;

	while (*pszEOS == *charToTrim) // check spaces. 
	{
		for (i = 0; i < strlen(szSource); i++)
		{
			szSource[i] = szSource[i + 1];
		}
		pszEOS = szSource;
	}
	return szSource;
}




void partition(MyData x[], long lb, long ub, long *ptrj)
{
	long up, down;

	MyData y, temp;
	
	y = x[lb];
	up = ub;
	down = lb;
	while (down<up)
	{
		while (x[down].ID <= y.ID && down < ub)
			down++;
	
		while (x[up].ID > y.ID)
			up--;
	
		if (down<up)
		{
			temp = x[down];
			x[down] = x[up];
			x[up] = temp;
		}
	}
	x[lb] = x[up];
	x[up] = y;
	*ptrj = up;
}

void partition(long x[], long lb, long ub, long* ptrj)
{
	long up, down;

	long y, temp;

	y = x[lb];
	up = ub;
	down = lb;
	while (down < up)
	{
		while (x[down] <= y && down < ub)
			down++;

		while (x[up] > y)
			up--;

		if (down < up)
		{
			temp = x[down];
			x[down] = x[up];
			x[up] = temp;
		}
	}
	x[lb] = x[up];
	x[up] = y;
	*ptrj = up;
}

int sortOnID(long x[], long lb, long ub)
{
	long j;

	if (lb >= ub) return(0);

	partition(x, lb, ub, &j);

	sortOnID(x, lb, j - 1);
	sortOnID(x, j + 1, ub);

	return(1);
}

int sortOnID(MyData x[], long lb, long ub)
{
   long j;

   if (lb >= ub) return(0);

   partition(x, lb, ub, &j);

   sortOnID(x, lb, j - 1);
   sortOnID(x, j + 1, ub);

   return(1);
}


