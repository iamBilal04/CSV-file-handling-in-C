#pragma once

void GetDataFromFile(FILE* InputFilePointer, char  tempString[285], long& DataRows, char  CharToRemove[1], time_t& ReadTime, FILE* SummaryPointer, clock_t& ProcessStartTime, char  tempString1[285], long  DataID[110000], FILE* ErrorLogPointer, bool& isCountinue);
