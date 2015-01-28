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