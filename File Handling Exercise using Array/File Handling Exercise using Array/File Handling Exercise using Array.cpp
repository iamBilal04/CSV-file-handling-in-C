#include "FileHandlingUsingArray.h"
#include "File Handling Exercise using Array.h"


void GetDataFromFile(FILE* InputFilePointer, long& DataRows, time_t& ReadTime, FILE* SummaryPointer, clock_t& ProcessStartTime, long  DataID[110000], FILE* ErrorLogPointer, bool& isCountinue)
{
	char tempString[FILENAME_MAX + 25], CharToRemove[1] = { ' ' };
	char tempString1[FILENAME_MAX + 25];

	if (InputFilePointer)
	{
		memset(tempString, '\0', sizeof(tempString));
		DataRows = 0;
		CharToRemove[0] = ' ';

		ReadTime = time(NULL);

		fprintf_s(SummaryPointer, "The Data reading started at %s\n", ctime(&ReadTime));
		ProcessStartTime = clock();

		while (!feof(InputFilePointer) && DataRows < MaxNumber)
		{
			memset(tempString, '\0', sizeof(tempString));

			fscanf_s(InputFilePointer, "%s", tempString, (unsigned int)sizeof(tempString));
			//fscanf_s(InputFilePointer, "%s %s", tempString, (unsigned int)sizeof(tempString), tempString1, (unsigned int)sizeof(tempString1));

			ltrim(tempString, CharToRemove);
			rtrim(tempString, CharToRemove);

			if (!strcmp(tempString, "")) continue;

			if (atol(tempString) && !strcmp(_strlwr(tempString), _strupr(tempString)))
			{
				_ltoa(atol(tempString), tempString1, 10);

				if (strlen(tempString) == strlen(tempString1))
				{

					DataID[DataRows] = atol(tempString);
					//printf("Array %d = %d\n", DataRows, Array[DataRows]);

					//Data[DataRows].ID = atol(tempString);
					//Data[DataRows].group = atol(groupString);
					DataRows++;
				}
				else
				{
					// Invalid Number "????" in the input file

					fprintf_s(ErrorLogPointer, "1.Invalid Number Detected '%s'..... '%s'\n", tempString, tempString1);

				}
			}
			else
			{
				// Invalid Number "????" in the input file

				fprintf_s(ErrorLogPointer, "2.Invalid Number Detected %s\n", tempString);
			}
		}
	}
	else
	{
		printf("\nERROR FAIL TO OPEN THE FILE FOR READING");

		fprintf_s(ErrorLogPointer, "Failed to open the File");
		isCountinue = false;
	}
}

void GetDataFromFile(FILE* InputFilePointer, long& DataRows, time_t& ReadTime, FILE* SummaryPointer, clock_t& ProcessStartTime, MyData  DataID[110000], FILE* ErrorLogPointer, bool& isCountinue)
{
	char tempString[FILENAME_MAX + 25], CharToRemove[1] = { ' ' };
	char tempString1[FILENAME_MAX + 25], group[25], tempString2[25];

	if (InputFilePointer)
	{
		memset(tempString, '\0', sizeof(tempString));
		DataRows = 0;
		CharToRemove[0] = ' ';

		ReadTime = time(NULL);

		fprintf_s(SummaryPointer, "The Data reading started at %s\n", ctime(&ReadTime));
		ProcessStartTime = clock();

		while (!feof(InputFilePointer) && DataRows < MaxNumber)
		{
			memset(tempString, '\0', sizeof(tempString));

			fscanf_s(InputFilePointer, "%s %s", tempString, (unsigned int)sizeof(tempString), group, (unsigned int)sizeof(group));

			ltrim(tempString, CharToRemove);
			rtrim(tempString, CharToRemove);

			ltrim(group, CharToRemove);
			rtrim(group, CharToRemove);

			if (!strcmp(tempString, "")) continue;

			if (!strcmp(group, ""))
				strcpy_s(group, "1");

			if (atol(tempString) && !strcmp(_strlwr(tempString), _strupr(tempString)) && atoi(group) && !strcmp(_strlwr(group), _strupr(group)))
			{
				_ltoa(atol(tempString), tempString1, 10);
				_itoa(atol(group), tempString2, 10);

				if (strlen(tempString) == strlen(tempString1) && strlen(group) == strlen(tempString2))
				{

					DataID[DataRows].ID = atol(tempString);
					DataID[DataRows].group = atol(group);
					DataRows++;
				}
				else
				{
					// Invalid Number "????" in the input file

					fprintf_s(ErrorLogPointer, "1.Invalid Number Detected '%s'..... '%s'\n", tempString, tempString1);

				}
			}
			else
			{
				// Invalid Number "????" in the input file

				fprintf_s(ErrorLogPointer, "2.Invalid Number Detected %s\n", tempString);
			}
		}
	}
	else
	{
		printf("\nERROR FAIL TO OPEN THE FILE FOR READING");

		fprintf_s(ErrorLogPointer, "Failed to open the File");
		isCountinue = false;
	}
}

int main()
{
	//FILE POINTERS
	FILE *InputFilePointer = NULL, *OutputFilePointer = NULL, *ErrorLogPointer = NULL, *SummaryPointer = NULL;

	//Variables
	//long DataID[MaxNumber] = { NULL };
	long DataRows = 0;
	double timeSpent = 0.0;

	MyData DataID[MaxNumber] = {NULL};


	clock_t BeginTime = clock(), ProcessStartTime = NULL, ProcessEndTime = NULL;

	//FILE NAMES
	char MyInputFile[FILENAME_MAX], MyOutputFile[FILENAME_MAX], MyErrorLogFile[FILENAME_MAX], MySummaryFile[FILENAME_MAX], tempString[FILENAME_MAX + 25], CharToRemove[1] = {' '};
	char tempString1[FILENAME_MAX + 25];

	bool isCountinue = true;

	time_t ReadTime = time(NULL);

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
	fopen_s(&ErrorLogPointer, MyErrorLogFile, "w");
	fopen_s(&SummaryPointer, MySummaryFile, "w");


	//Reading file and inserting the data into an array....

	GetDataFromFile(InputFilePointer, DataRows, ReadTime, SummaryPointer, ProcessStartTime, DataID, ErrorLogPointer, isCountinue);

	/*
	ReadTime = time(NULL);
	fprintf_s(SummaryPointer, "The Data of the file was read at %s\n", ctime(&ReadTime));
	*/

	fprintf_s(SummaryPointer, "Total Data Read %ld\n", DataRows);

	ProcessEndTime = clock();
	timeSpent = (double)(ProcessEndTime - ProcessStartTime) / CLOCKS_PER_SEC;
	fprintf_s(SummaryPointer, "Elapsed time for reading --> %f\n", timeSpent);
	
	timeSpent = 0.0;
	ProcessStartTime = clock();

	if (isCountinue)
	{
		//Selection/Bubble sorting for sorting the data
		/*
		for (int j = 0; j < DataRows; j++)
		{
			for (int i = 0; i < DataRows - j - 1; i++)
			{
				if (DataID[i] > DataID[i + 1])
				{
					SwapVar = DataID[i];
					DataID[i] = DataID[i + 1];
					DataID[i + 1] = SwapVar;
				}
			}
		}
		*/
		sortOnID(DataID, 0, DataRows - 1);

		// Group Sort

		for (int i = 0; i < DataRows; i++)
		{
			int j = i;
			while (j > 0 && DataID[j].ID == DataID[j - 1].ID)
			{
				if (DataID[j].group < DataID[j - 1].group)
				{
					MyData TempData = DataID[j];
					DataID[j] = DataID[j - 1];
					DataID[j - 1] = TempData;
				}
				j--;
			}
		}


		ReadTime = time(NULL);
		fprintf_s(SummaryPointer, "The Data was Sorted at %s\n", ctime(&ReadTime));
		
		ProcessEndTime = clock();
		timeSpent = (double)(ProcessEndTime - ProcessStartTime) / CLOCKS_PER_SEC;
		fprintf_s(SummaryPointer, "Elapsed time for Sorting --> %f\n", timeSpent);
		timeSpent = 0.0;

		/// <summary>
		/// Display the sorted Data into the Destination file 
		/// </summary>
		fopen_s(&OutputFilePointer, MyOutputFile, "w");

		ProcessStartTime = clock();

		if (OutputFilePointer)
		{
			int CurrentRow = 0;
			//Printing the sorted data into a file
			while (CurrentRow < DataRows)
			{
				fprintf_s(OutputFilePointer, "%ld %d\n", DataID[CurrentRow].ID, DataID[CurrentRow].group);
				CurrentRow++;
			}
			fprintf_s(SummaryPointer, "Total Data Written %ld\n", CurrentRow);

			printf("The Contents of the File has Been Succesfully copied and Sorted");
		}
		else

		{
			printf("Failed to open file for writting");
		}
		if(OutputFilePointer)
			fclose(OutputFilePointer);

		ReadTime = time(NULL);
		ProcessEndTime = clock();
		timeSpent += (double)(ProcessEndTime - ProcessStartTime) / CLOCKS_PER_SEC;
		fprintf_s(SummaryPointer, "The Data was written in the Destination File at At %s \n", ctime(&ReadTime));
		fprintf_s(SummaryPointer, "Elapsed time for Writing --> %f\n", timeSpent);
	}
	if(InputFilePointer)
		fclose(InputFilePointer);
	
	ProcessEndTime = clock();

	timeSpent = (double)(ProcessEndTime - BeginTime) / CLOCKS_PER_SEC;
	fprintf_s(SummaryPointer, "Elapsed time --> %f", timeSpent);

	if (SummaryPointer)
		fclose(SummaryPointer);

	if (ErrorLogPointer)
		fclose(ErrorLogPointer);

	return 0;
}