#if defined _lololib_args_included
  #endinput
#endif
#define _lololib_args_included


stock bool lolo_Args_Char_Escaped(const char[] string, int index)
{
	// escaped
	if (index > 0 && string[index - 1] == '\\')
	{
		// not escaped
		if (index > 1 && string[index - 2] == '\\')
		{
			return false;
		}

		return true;
	}

	return false;
}

stock ArrayList lolo_Args_Split(const char[] sArgs, int parts = 0)
{
	int maxlength = strlen(sArgs);
	if (!maxlength) return null;

	char[] buffer = new char[maxlength + 1];
	strcopy(buffer, maxlength + 1, sArgs);

	bool done;

	ArrayList args = new ArrayList(maxlength);
	
	do
	{
		int buffer_len = strlen(buffer);

		// starts with quote
		if (StrContains(buffer, "\"") == 0)
		{
			// quote closed
			int search;
			bool added;

			while (!done)
			{
				if (search + 1 == buffer_len) break;
				int contains = StrContains(buffer[search + 1], "\"");
				if (contains == -1) break;
				search += contains + 1;

				// possible closing quote
				if (!lolo_Args_Char_Escaped(buffer, search))
				{
					// end of string or end of arg
					if (search == buffer_len - 1 || buffer[search + 1] == ' ')
					{
						// escape symbol
						int length = search;

						if (length > 2)
						{
							if (buffer[search-1] == '\\')
							{
								if (buffer[search-2] == '\\')
								{
									length--;
								}	
							}
						}

						// add
						char[] arg = new char[length];
						strcopy(arg, length, buffer[1]);
						args.PushString(arg);

						if (search == buffer_len - 1)
							done = true;
						else
							strcopy(buffer, strlen(buffer[search + 2]), buffer[search + 2]);

						added = true;
						break;
					}
				}
			}

			if (added) continue;
		}

		// find any non-space
		int char_start = -1;

		for (int i; i < buffer_len; i++)
		{
			if (!IsCharSpace(buffer[i])) 
			{
				char_start = i;
				break;
			}
		}

		if (char_start == -1) done = true;
		else
		{
			// find any valid space
			int search = char_start;
			bool added;

			while (!done)
			{
				if (search + 1 == buffer_len) break;
				int contains = StrContains(buffer[search + 1], " ");
				if (contains == -1) break;
				search += contains + 1;

				if (!lolo_Args_Char_Escaped(buffer, search))
				{
					// escape symbol
					int length = search - char_start + 1;

					if (length > 2)
					{
						if (buffer[search-1] == '\\')
						{
							if (buffer[search-2] == '\\')
							{
								length--;
							}	
						}
					}

					// add
					char[] arg = new char[length];
					strcopy(arg, length, buffer[char_start]);
					args.PushString(arg);

					//PrintToServer("buffer: %s\nbuffer after cut: %s\nlen: %d\n", buffer, buffer[search + 1], strlen(buffer[search + 1]));

					if (search == buffer_len - 1)
						done = true;
					else
						strcopy(buffer, maxlength, buffer[search + 1]);

					added = true;
					break;
				}
			}

			if (!added) 
			{
				// add remainder
				args.PushString(buffer[char_start]);
				done = true;
			}
		}
	}
	while (!done);

	return args;
}