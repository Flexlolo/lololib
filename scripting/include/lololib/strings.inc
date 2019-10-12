#if defined _lololib_strings_included
  #endinput
#endif
#define _lololib_strings_included



/*
Characters
*/

stock void lolo_Chars_GetByIndex(const char[] string, int index, char[] result, int maxlength)
{
	int a = index + 1;
	if (IsCharMB(string[index]))
	{
		a = index + IsCharMB(string[index]);
	}
	int j;
	for (int i = index; i < a; i++)
	{
		result[j] = string[i];
		j++;
	}
}

stock int lolo_Chars_GetIndexes(const char[] string, bool spaces, int[] indexes, int maxlength)
{
	int char_count;

	for (int i = 0; i < strlen(string); i++)
	{
		if (char_count >= maxlength) break;
		if (!spaces && IsCharSpace(string[i])) continue;

		indexes[char_count++] = i;

		int a = IsCharMB(string[i]);
		if (!a) a = 1;
		i = i + a - 1;
	}

	return char_count;
}

stock int lolo_Chars_Count(const char[] string, bool spaces)
{
	int char_count;

	for (int i = 0; i < strlen(string); i++)
	{
		if (!spaces && IsCharSpace(string[i])) continue;

		int a = IsCharMB(string[i]);
		if (!a) a = 1;
		i = i + a - 1;
	}
	
	return char_count;
}



/*
Colors
*/

stock void lolo_GetTeamColorString(int team, char[] string, int maxlength)
{
	if (team == 2) Format(string, maxlength, "\x07FF4040");
	else if (team == 3) Format(string, maxlength, "\x0799CCFF");
	else Format(string, maxlength, "\x07CCCCCC");
}



/*
Strings
*/

stock void lolo_String_Lower(char[] string)
{
	for (int i; i < strlen(string); i++)
	{
		string[i] = CharToLower(string[i]);
	}
}

stock void lolo_String_Upper(char[] string)
{
	for (int i; i < strlen(string); i++)
	{
		string[i] = CharToUpper(string[i]);
	}
}

stock void lolo_String_Remove(char[] string, int maxlength, const char[] remove)
{
	ReplaceString(string, maxlength, remove, "", true);
}

stock bool lolo_String_Startswith(const char[] string, const char[] start, bool case_sensitive = true)
{
	return StrContains(string, start, case_sensitive) == 0;
}

/*stock void lolo_RemoveCharsFromString(char[] string, int maxlength, const char[] sChars)
{
	char[] sResult = new char[maxlength];

	int iStringLength = strlen(string);
	int iCharsLength = strlen(sChars);
	if (iStringLength > 0 && iCharsLength > 0)
	{
		for (int i = 0; i < iStringLength; i++)
		{
			if (lolo_CompareStringBeginning(string[i], sChars, true))
			{
				if (i + iCharsLength < iStringLength)
				{
					if (i)
					{
						Format(sResult, maxlength, "%s%s", sResult, string[i+iCharsLength]);
					}
					else
					{
						Format(sResult, maxlength, "%s", string[i+iCharsLength]);
					}
				}
				else
				{
					if (i)
					{
						int iTempLength = strlen(sResult) + 1;
						char[] sTemp = new char[iTempLength];
						Format(sTemp, iTempLength, "%s", sResult);
						strcopy(sResult, maxlength, sTemp);
					}
					else
					{
						Format(sResult, maxlength, "");
					}
					i += iCharsLength;
					continue;
				}
				// Restart checking
				strcopy(string, maxlength, sResult);
				iStringLength = strlen(string);
				i = -1;
			}
			else
			{
				char sChar[2];
				Format(sChar, sizeof(sChar), "%s", string[i]);
				if (i)
				{
					Format(sResult, maxlength, "%s%s", sResult, sChar);
				}
				else
				{
					Format(sResult, maxlength, "%s", sChar);
				}
			}
		}
		strcopy(string, maxlength, sResult);
	}
}
*/

/*
stock bool lolo_CompareStringBeginning(const char[] string, const char[] sWith, bool CaseSensetive)
{
	return StrContains(string, sWith, CaseSensetive) == 0;
}
*/