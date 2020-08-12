#if defined _lololib_macros_included
  #endinput
#endif
#define _lololib_macros_included

#define int(%1) view_as<int>(%1)

stock void pack(ArrayList list, const int[] i, const int n, any value)
{
	int j = 0;
	bool done = false;

	ArrayList l = list;

	while (!done)
	{
		if (i[j] >= l.Length)
		{
			int length = l.Length;

			l.Resize(i[j] + 1);

			for (int k = length; k <= i[j]; k++)
				l.Set(k, 0);
		}

		if (j == n - 1)
		{
			l.Set(i[n-1], value);
			break;
		}
		else
		{
			ArrayList t = l.Get(i[j]);

			if (t == null)
			{
				t = new ArrayList(1);
				l.Set(i[j], t);
			}

			l = t;
		}

		j++;
	}
}

stock ArrayList unpack(ArrayList list, const int[] i, const int n)
{
	if (!n)
		return list;

	int j = 0;
	bool done = false;

	ArrayList l = list;

	while (!done)
	{
		if (l != null && i[j] < l.Length)
		{
			l = l.Get(i[j]);
		}
		else
		{
			return null;
		}

		if (j == n - 1)
			return l;

		j++;
	}

	return null;
}