#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MyFilePath "D:\\Bilal\\Sem 3\\Data\\"

typedef struct MyData
{
    long Data;
    int group;
} MYDATA, mydata;

/// <summary>
/// Data Singly Link List
/// </summary>
typedef struct DataLink 
{
	//long Data;
    //int group;
    MyData DataRow;
	DataLink* Link;
}DATALINK, datalink;


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
		for (i = 0; i < (int) strlen(szSource); i++)
		{
			szSource[i] = szSource[i + 1];
		}
		pszEOS = szSource;
	}
	return szSource;
}

/*
DataLink* parition(DataLink* newHead, DataLink* last)
{
    DataLink* pivot = newHead;
    DataLink* front = newHead;
    DataLink* SortedList = NULL;
   
    long temp = 0;
    while (front != NULL && last != NULL) 
    {
        if (front->Data < last->Data)
        {
            pivot = newHead;

            temp = newHead->Data;
            newHead->Data = front->Data;
            front->Data = temp;

            newHead = newHead->Link;
        }
        front = front->Link;
    }
   
    temp = newHead->Data;
    newHead->Data = last->Data;
    last->Data = temp;
    return pivot;
}

void quick_sort(DataLink **newHead, DataLink **last)
{
    DataLink* pivot;
    if (*newHead == *last)
        return;

    pivot = parition(*newHead, *last);

    if (pivot != NULL && pivot->Link != NULL)
        quick_sort(&(pivot->Link), last);

    if (pivot != NULL && *newHead != pivot)
        quick_sort(newHead, &pivot);
}
*/

DataLink* findPivot(DataLink* newHead)
{
    DataLink* Slow, * Fast;
    Slow = newHead;
    Fast = newHead->Link;

    while (Fast != NULL && Fast->Link != NULL)
    {
        Slow = Slow->Link;
        Fast = Fast->Link->Link;
    }

    return Slow;
}

DataLink* Merge(DataLink* LeftList, DataLink* RightList)
{
    DataLink* TempList;
    DataLink* MergedList = NULL;

    if (LeftList == NULL)
        return RightList;
    else if (RightList == NULL)
        return LeftList;

    MergedList = (DataLink*)malloc(sizeof(datalink));
    TempList = MergedList;

    while (LeftList != NULL && RightList != NULL)
    {
        if ((LeftList->DataRow).Data < (RightList->DataRow).Data)
        {
            TempList->Link = LeftList;
            TempList = LeftList;
            LeftList = LeftList->Link;
        }
        else
        {
            TempList->Link = RightList;
            TempList = RightList;
            RightList = RightList->Link;
        }
    }

    while (LeftList != NULL)
    {
        TempList->Link = LeftList;
        TempList = LeftList;
        LeftList = LeftList->Link;
    }

    while (RightList != NULL)
    {
        TempList->Link = RightList;
        TempList = RightList;
        RightList = RightList->Link;
    }

    MergedList = MergedList->Link;
    return MergedList;
}

DataLink* MergeSortOnID(DataLink* newHead)
{
    if (newHead == NULL || newHead->Link == NULL)
        return newHead;
    else
    {
        DataLink *pivot = NULL, *LeftList = NULL, * RightList = NULL, * SortedList = NULL;
 
        pivot = findPivot(newHead);

        LeftList = newHead;
        RightList = pivot->Link;
        pivot->Link = NULL;

        LeftList = MergeSortOnID(LeftList);
        RightList = MergeSortOnID(RightList);

        SortedList = Merge(LeftList, RightList);

        return SortedList;
    }
    
}

DataLink* findGroupPivot(DataLink* newHead)
{
    DataLink* Slow, * Fast;
    Slow = newHead;
    Fast = newHead->Link;

    while (Fast != NULL && Fast->Link != NULL && Slow->DataRow.Data == Fast->Link->DataRow.Data)
    {
        Slow = Slow->Link;
        Fast = Fast->Link->Link;
    }

    return Slow;
}

DataLink* MergeGroup(DataLink* LeftList, DataLink* RightList)
{
    DataLink* TempList;
    DataLink* MergedList = NULL;

    if (LeftList == NULL)
        return RightList;
    else if (RightList == NULL)
        return LeftList;

    MergedList = (DataLink*)malloc(sizeof(DataLink));
    TempList = MergedList;

    while (LeftList != NULL && RightList != NULL)
    {
        if ((LeftList->DataRow).group > (RightList->DataRow).group && (LeftList->DataRow).Data == (RightList->DataRow).Data)
        {
            TempList->Link = LeftList;
            TempList = LeftList;
            LeftList = LeftList->Link;
        }
        else
        {
            TempList->Link = RightList;
            TempList = RightList;
            RightList = RightList->Link;
        }
    }

    while (LeftList != NULL)
    {
        TempList->Link = LeftList;
        TempList = LeftList;
        LeftList = LeftList->Link;
    }

    while (RightList != NULL)
    {
        TempList->Link = RightList;
        TempList = RightList;
        RightList = RightList->Link;
    }

    MergedList = MergedList->Link;
    return MergedList;
}

DataLink* MergeSortOnGroup(DataLink* newHead)
{
    if (newHead == NULL || newHead->Link == NULL)
        return newHead;
    else
    {
        DataLink* pivot = NULL, * LeftList = NULL, * RightList = NULL, * SortedList = NULL;

        pivot = findGroupPivot(newHead);

        LeftList = newHead;
        RightList = pivot->Link;
        pivot->Link = NULL;

        LeftList = MergeSortOnGroup(LeftList);
        RightList = MergeSortOnGroup(RightList);

        SortedList = MergeGroup(LeftList, RightList);

        return SortedList;
    }

}