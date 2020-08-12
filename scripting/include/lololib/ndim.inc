#if defined _lololib_ndim_included
  #endinput
#endif
#define _lololib_ndim_included

stock void pack(ArrayList list, int[] i, const int n, any value)
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

stock ArrayList unpack(ArrayList list, int[] i, const int n)
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

stock ArrayList iterate(ArrayList l, int[] i, const int n, bool &found, int p=0)
{
	if (p != n - 1)
	{
		while (i[p] < l.Length)
		{
			ArrayList t = l.Get(i[p]);

			if (t != null)
			{
				bool found_t = false;
				t = iterator(t, i, n, found_t, p + 1);

				if (found_t)
				{
					found = true;
					return t;
				}
			}

			i[p] += 1;

			for (int j = p + 1; j < n; j++)
			{
				i[j] = 0;
			}
		}

		return null;
	}
	else
	{
		if (i[p] < l.Length)
		{
			found = true;
			i[p] += 1;
			return l.Get(i[p] - 1);
		}

		return null;
	}
}