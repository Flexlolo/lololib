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