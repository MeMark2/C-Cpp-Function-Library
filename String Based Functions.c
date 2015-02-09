/*
Name:			lexiStrCmp()
Description:
	This function compares the contents of two arrays of char in order to figure out their lexicographical order.
The comparison is case insensitive.

Parameters:
char* str1	- The first array of char to use for comparison.
char* str2	- The second array of char to use for comparison.

Return:
int lexiCmp	
	- This will return 0 if both str1 and str2 are equal lexicographically, it will return -1 if str1 comes before str2,
	or 1 if str1 comes after str2.
*/
int lexiStrCmp(char* str1, char* str2)
{
	char str1Buff[kMaxMP3Name] = "";
	char str2Buff[kMaxMP3Name] = "";
	int lexiCmp = 0;

	// Copy arrays of char into buffers
	strcpy(str1Buff, str1);
	strcpy(str2Buff, str2);

	// Set all characters in both buffers to lower case.
	for (int currChar = 0; str1Buff[currChar] != '\0' ; currChar++)
	{
		str1Buff[currChar] = tolower(str1Buff[currChar]);
	}
	for (int currChar = 0; str2Buff[currChar] != '\0'; currChar++)
	{
		str2Buff[currChar] = tolower(str2Buff[currChar]);
	}


	// This loop steps through every character of str1Buff and str2Buff in order to figure out which of str1 and str2
	// comes first lexicographically.
	for (int currChar = 0; 1 ; currChar++)
	{
		// If no differences have been found and both arrays of char have the same length, the arrays are equal.
		// If no differences have been found and str1 ends before str2, str1 comes before str2 lexicographically. 
		// If no differences have been found and str2 ends before str1, str1 comes after str2 lexicographically. 
		if (str1Buff[currChar] == '\0' && str2Buff[currChar] == '\0')
		{
			lexiCmp = 0;
			break;
		}
		else if (str1Buff[currChar] == '\0')
		{
			lexiCmp = -1;
			break;
		}
		else if (str2Buff[currChar] == '\0')
		{
			lexiCmp = 1;
			break;
		}


		// If the current character for str1 is smaller than for str2, then str1 comes before str2 lexicographically.
		// If the current character for str1 is larger than for str2, then str1 comes after str2 lexicographically.
		if (str1Buff[currChar] < str2Buff[currChar])
		{
			lexiCmp = -1;
			break;
		}
		else if (str1Buff[currChar] > str2Buff[currChar])
		{
			lexiCmp = 1;
			break;
		}

	}

	// Return the results of the lexical comparison.
	return lexiCmp;
}



/*
Name:			removeLnTSpaces()
Description:
This function will get rid of any trailing and/or leading spaces of a string that is passed in.

Parameters:
char* string	- The pointer to the array of char where the final (modified) input will be saved.

Return:
int errorCode	- This will return 0 if nothing goes wrong or 1 if any errors occur.
*/
int removeLnTSpaces(char* string)
{
	char tempBuffer[kMaxDirLength] = "";
	int assignCount = 0;
	int errorCode = 0;
	int spaceCounter = 0;
	char* strJumper = NULL;

	//If the string has a '\n' character at the end, remove it.
	assignCount = sscanf(string, "%[^\n]", string);

	//Check for any errors.
	if (assignCount != 1)
	{
		errorCode = 1;
	}
	else
	{
		//If the string has any leading spaces, remove them.
		sscanf(string, "%[ ]%[^\n\0]", tempBuffer, string);
	}


	if (errorCode == 1); //If an error has be encountered, do nothing.
	else //Else, run through a loop to get rid of any trailing spaces.
	{
		// Copy the current string to a temporary buffer.
		strcpy(tempBuffer, string);

		// This loop will step through every char of the tempBuffer string.
		// The loop will break once a null terminator ('\0') is found.
		// Anytime a space char is found, the spaceCounter will be incremented.
		// Anytime a non-space char is found, the spaceCounter will be reset to 0.
		for (int charCounter = 0; 1; charCounter++)
		{
			if (tempBuffer[charCounter] == '\0')
			{
				break;
			}
			else if (isspace(tempBuffer[charCounter]) != 0)
			{
				spaceCounter += 1;
			}
			else
			{
				spaceCounter = 0;
			}
		}

		// If any space characters were found between the last non-space character in the string and 
		// the null terminator ('\0'), use the strJumper to jump to the location after the last non-space character
		// and insert a null terminator there ('\0').
		if (spaceCounter > 0)
		{
			strJumper = string;
			strJumper += strlen(string) - spaceCounter;
			*strJumper = '\0';
		}
	}


	return errorCode;
}


/*
Name:			spaceSeperatedItems()
Description:
This function finds how many groups of space-seperated characters are within a string.

Parameters:
char* inputString	- The pointer to the string to process.

Return:
int returnCode	- This returns the number of groups (of characters) that are seperated by spaces within the inputString.
- If anything unexpected occurs, -1 is returned.
*/
int spaceSeperatedItems(char* inputString)
{
	int intBuff = 0;
	char strBuff[MAX_STRING_LENGTH] = "";
	char strCut[MAX_STRING_LENGTH] = "";
	int assignFound = 0;
	int returnCode = -1;

	//pass input string into the buffer
	strcpy(strBuff, inputString);

	if (sscanf(strBuff, "%[ ]%[^\0]", strCut, strCut) == 1)
	{	//If the string has nothing other than spaces (no groups of space-seperated characters were found), set returnCode to 0.
		returnCode = 0;
	}
	else
	{
		for (int assignCount = 0; true; assignCount++)
		{	//Otherwise, run through a for to find the number of space-seperated groups of characters.

			//Find the first set of space-seperated characters and split it from the rest of the string.
			intBuff = sscanf(strBuff, "%s %[^\0]", strCut, strBuff);


			if (intBuff == 2) //If a group was succesfully found and thee is leftover characters.
			{	// Add one to the number of groups found.
				assignFound += 1;
			}
			else if (intBuff == 1) // If a group was successfully found but there is no more leftover characters.
			{	// Add one to the number of groups found, set the numer found so far to return and break.
				assignFound += 1;
				returnCode = assignFound;
				break;
			}
			else // Any unexpected results will set the return code to -1 and break out of loop.
			{
				returnCode = -1;
				break;
			}
		}
	}

	// Exit function.
	return returnCode;
}


/*
Name:			cmpStringToChar()
Description:
This function is usd to compare a 1 character string to a char. The comparison is case-sensitive.

Parameters:
char* cmpString		- The pointer to the string to compare to a char.
char cmpCar			- The char to compare to a string.

Return:
bool match	- If the one-character string matches the char, true will be returned. Otherwise, false will be returned.
*/
bool cmpStringToChar(char* cmpString, char cmpChar)
{
	bool match = false;

	// Check that the cmpString is one char in length and that the first element is equal to the cmpChar.
	if (strlen(cmpString) == 1 && cmpString[0] == cmpChar)
	{
		match = true;
	}

	return match;
}
