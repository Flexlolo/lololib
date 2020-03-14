#if defined _lololib_args_included
  #endinput
#endif
#define _lololib_args_included



stock bool lolo_Args_Char_Escaped(const char[] string, int index, bool recursive = true)
{
	if (recursive)
	{
		bool escaped = false;

		for (int i = index; i > 0; i--)
		{
			if (lolo_Args_Char_Escaped(string, i, false)) escaped = !escaped;
			else break;
		}

		return escaped;
	}
	else
	{
		return (index > 0 && string[index - 1] == '\\');
	}
}

stock void lolo_Args_String_Clear(char[] string, int maxlength, bool space)
{
	int length = strlen(string);
	if (!length) return;
	
	int at = length - 1;
	bool done = false;

	while (!done)
	{
		for (int i = at; i > 0; i--)
		{
			at = i;

			if (string[i] == '\"' || string[i] == ' ' || (space && at + 1 == length && string[i] == '\\'))
			{
				if (!lolo_Args_Char_Escaped(string, i)) continue;

				char[] temp = new char[maxlength];
				if (i > 1) strcopy(temp, i, string);
				strcopy(temp[strlen(temp)], maxlength - strlen(temp), string[i]);
				strcopy(string, maxlength, temp);

				at -= 1;
				length -= 1;
				break;
			}
		}

		if (at < 2) done = true; 
	}

	return;
}

stock bool lolo_Args_String_Empty(const char[] string)
{
	for (int i; i < strlen(string); i++)
	{
		if (!IsCharSpace(string[i])) 
		{
			return false;
		}
	}

	return true;
}



stock ArrayList lolo_Args_Split(const char[] string)
{
	int maxlength = strlen(string);
	if (!maxlength) return null;

	char[] buffer = new char[maxlength + 1];
	strcopy(buffer, maxlength + 1, string);

	ArrayList args = new ArrayList(maxlength);

	bool done;
	
	do
	{
		// check if buffer is empty
		int buffer_len = strlen(buffer);
		if (!buffer_len) break;

		if (lolo_Args_String_Empty(buffer)) break;

		// find first char
		int start = 0;
		while (IsCharSpace(buffer[start])) start += 1;

		// cut buffer
		if (start)
		{
			strcopy(buffer, maxlength + 1, buffer[start]);
			buffer_len -= start;
		}

		// starts with quote
		if (buffer[0] == '\"')
		{
			bool added = false;
			int search = 0;

			// split at valid quote end
			while (!done)
			{
				// EOS
				if (search + 1 == buffer_len) break;

				// find end quote
				int quote_end = StrContains(buffer[search + 1], "\""); 	
				if (quote_end == -1) break;

				search += quote_end + 1;

				// not escaped
				if (lolo_Args_Char_Escaped(buffer, search)) continue;

				// EOS
				if (search + 1 != buffer_len && buffer[search + 1] != ' ') continue;

				// get arg
				int length = search;
				if (search > 1 && buffer[search - 1] == '\\' && !lolo_Args_Char_Escaped(buffer, search - 1)) length--;

				char[] arg = new char[length];
				strcopy(arg, length, buffer[1]);

				// de-escape
				lolo_Args_String_Clear(arg, length, false);

				// add
				args.PushString(arg);
				added = true;

				// if EOS then done
				if (search + 1 == buffer_len) done = true;
				else strcopy(buffer, maxlength + 1, buffer[search + 2]);

				break;
			}

			if (added) continue;	
		}

		// doesnt start with quote OR not closed quote
		bool added = false;
		int search = 0;
		
		// split at space
		while (!done)
		{
			// EOS
			if (search + 1 == buffer_len) break;

			// find space
			int space = StrContains(buffer[search + 1], " "); 	
			if (space == -1) break;

			search += space + 1;

			// not escaped
			if (lolo_Args_Char_Escaped(buffer, search)) continue;

			// get arg
			int length = search + 1;
			if (search > 1 && buffer[search - 1] == '\\' && !lolo_Args_Char_Escaped(buffer, search - 1)) length--;

			char[] arg = new char[length];
			strcopy(arg, length, buffer);

			// de-escape
			lolo_Args_String_Clear(arg, length, true);

			// add
			args.PushString(arg);
			added = true;

			// if EOS then done
			if (search + 1 == buffer_len) done = true;
			else strcopy(buffer, maxlength + 1, buffer[search + 1]);

			break;
		}		

		// add remainder		
		if (!added) 
		{
			// de-escape
			lolo_Args_String_Clear(buffer, maxlength + 1, false);

			args.PushString(buffer);
			done = true;
		}
	}
	while (!done);

	return args;
}