#include "RandomPractice.h"



void ReadFile(char *MyInputFile, FILE* InputFilePointer, DataLink **FirstDataLink, DataLink **LastDataLink)
{
	DataLink* Temp = (DataLink*)malloc(sizeof(DataLink));
	MyData TempData;
	char tempString[FILENAME_MAX + 25], tempString1[FILENAME_MAX + 25], CharToRemove[1] = {' '}, Group[30], TempGroupString[30];

	memset(tempString, '\0', sizeof(tempString));

	CharToRemove[0] = ' ';

	*FirstDataLink = *LastDataLink = NULL;

	while (!feof(InputFilePointer))
	{
		memset(tempString, '\0', sizeof(tempString));
		fscanf_s(InputFilePointer, "%s %s", tempString, (unsigned int)sizeof(tempString), Group, (unsigned int)sizeof(Group));

		ltrim(tempString, CharToRemove);
		rtrim(tempString, CharToRemove);

		if (!strcmp(tempString, "")) continue;

		if (!strcmp(Group, ""))
			strcpy_s(Group, "1");

		if (atol(tempString) && !strcmp(_strlwr(tempString), _strupr(tempString)) && atoi(Group) && !strcmp(_strlwr(Group), _strupr(Group)))
		{
			_ltoa(atol(tempString), tempString1, 10);
			_itoa(atol(Group), TempGroupString, 10);

			if (strlen(tempString) == strlen(tempString1) && strlen(Group) == strlen(TempGroupString))
			{
				TempData.Data = atol(tempString);
				TempData.group = atoi(TempGroupString);
				//GroupDataFromFile = atol(Group);

				if (*FirstDataLink == NULL)
					*FirstDataLink = *LastDataLink = (DataLink*)malloc(sizeof(DataLink));
				else
				{
					(*LastDataLink)->Link = (DataLink*)malloc(sizeof(DataLink));
					*LastDataLink = (*LastDataLink)->Link;
				}
				(*LastDataLink)->DataRow = TempData;
				//(*LastDataLink)->DataRow->Data = TempData.Data;
				//(*LastDataLink)->DataRow->group = TempData.group;
				(*LastDataLink)->Link = NULL;
				
			}
		}

	}
	return;
}

void writeLinkedList(char *MyOutputFile, FILE* OutputFilePointer, DataLink* newHead)
{
	DataLink* Temp = newHead;
	//long DataToFile[1], GroupDataFromFile[1];
	//MyData TempData;

	while (Temp != NULL)
	{
		//TempData.Data = Temp->DataRow.Data
		/*DataToFile[0] = (Temp->Data);*/
		//GroupDataFromFile[0] = (Temp->group);
		//fwrite(DataToFile, sizeof(long), 1, OutputFilePointer);
		fprintf_s(OutputFilePointer, " %ld %ld\n", Temp->DataRow.Data, Temp->DataRow.group);
		Temp = Temp->Link;
	}
}

int main()
{
	//FILE POINTERS
	FILE* InputFilePointer = NULL, * OutputFilePointer = NULL, * ErrorLogPointer = NULL, * SummaryPointer = NULL;

	//Variables
	//int SwapVar;
	double timeSpent = 0.0;
	long DataRows = 0;

	clock_t BeginTime = clock(), ProcessStartTime = NULL, ProcessEndTime = NULL;

	
	//FILE NAMES
	char MyInputFile[FILENAME_MAX], MyOutputFile[FILENAME_MAX], MyErrorLogFile[FILENAME_MAX], MySummaryFile[FILENAME_MAX], tempString[FILENAME_MAX + 25], CharToRemove[1] = { ' ' };
	char tempString1[FILENAME_MAX + 25];

	bool isCountinue = true;

	time_t ReadTime = time(NULL);

	DataLink* newHead = NULL, *LastLink = NULL;

	memset(MyInputFile, '\0', sizeof(MyInputFile));
	memset(MyOutputFile, '\0', sizeof(MyOutputFile));
	memset(MyErrorLogFile, '\0', sizeof(MyErrorLogFile));
	memset(tempString, '\0', sizeof(tempString));
	memset(tempString1, '\0', sizeof(tempString));
	memset(MySummaryFile, '\0', sizeof(MySummaryFile));

	strcpy_s(tempString, MyFilePath);

	ltrim(tempString, CharToRemove);
	rtrim(tempString, CharToRemove);

	CharToRemove[0] = '\\';
	rtrim(tempString, CharToRemove);

	CharToRemove[0] = '/';
	rtrim(tempString, CharToRemove);

	sprintf_s(MyInputFile, "%s\\%s", tempString, "ToRead.txt");
	sprintf_s(MyOutputFile, "%s\\%s", tempString, "Destination.txt");
	sprintf_s(MyErrorLogFile, "%s\\%s", tempString, "ErrorLog.txt");
	sprintf_s(MySummaryFile, "%s\\%s", tempString, "Summary.txt");

	/// <summary>
	/// Read Data from the file and copy into array 
	/// </summary>
	fopen_s(&InputFilePointer, MyInputFile, "r");
	fopen_s(&OutputFilePointer, MyOutputFile, "w");
	fopen_s(&ErrorLogPointer, MyErrorLogFile, "w");
	fopen_s(&SummaryPointer, MySummaryFile, "w");

	if (InputFilePointer)
	{
		DataLink* groupSortLink = NULL;
		MyData	SwapData;

		ReadFile((char*)"MyInputFile.txt", InputFilePointer, &newHead, &LastLink);
		ProcessStartTime = clock();
		ProcessEndTime = clock();
		timeSpent = (double)(ProcessEndTime - ProcessStartTime) / CLOCKS_PER_SEC;
		fprintf_s(SummaryPointer, "Elapsed Time for Reading --> %f\n", timeSpent);
		fclose(InputFilePointer);

		ProcessStartTime = clock();
		newHead = MergeSortOnID(newHead);

		LastLink = newHead;
		while (LastLink->Link)
		{
			LastLink = LastLink->Link;
		}

		 //Group Sort
		
		groupSortLink = newHead;

		while (groupSortLink->Link)
		{
			DataLink *NextLink = groupSortLink->Link;
			while (NextLink->Link && NextLink->DataRow.Data == groupSortLink->DataRow.Data)
			{
				if (NextLink->DataRow.group < groupSortLink->DataRow.group)
				{
					SwapData = NextLink->DataRow;
					NextLink->DataRow = groupSortLink->DataRow;
					groupSortLink->DataRow = SwapData;
				}
				
				if (NextLink->DataRow.Data == LastLink->DataRow.Data && LastLink->DataRow.group < NextLink->DataRow.group)
				{
					SwapData = LastLink->DataRow;
					LastLink->DataRow = NextLink->DataRow;
					NextLink->DataRow = SwapData;
				}
				NextLink = NextLink->Link;
			}
			groupSortLink = groupSortLink->Link;
		}

	    //newHead = MergeSortOnGroup(newHead);
		ProcessEndTime = clock();
		timeSpent += (double)(ProcessEndTime - ProcessEndTime) / CLOCKS_PER_SEC;
		fprintf_s(SummaryPointer, "Elapsed time for Sorting --> %f\n", timeSpent);

		ProcessStartTime = clock();
		writeLinkedList(MyOutputFile, OutputFilePointer, newHead);
		ProcessEndTime = clock();
		timeSpent += (double)(ProcessEndTime - ProcessStartTime) / CLOCKS_PER_SEC;


		printf("The Contents of the File has Been Succesfully copied and Sorted");
	}
	else

	{
		// Failed to Open File
		printf("Failed to Open the File");
		fprintf_s(ErrorLogPointer, "FAILED TO OPEN THE FILE");
	}

	ProcessEndTime = clock();
	timeSpent = (double)(ProcessEndTime - BeginTime) / CLOCKS_PER_SEC;
	fprintf_s(SummaryPointer, "Elapsed time for Execution --> %f\n", timeSpent);

	fclose(InputFilePointer);
	fclose(OutputFilePointer);
	fclose(SummaryPointer);
	fclose(ErrorLogPointer);
}