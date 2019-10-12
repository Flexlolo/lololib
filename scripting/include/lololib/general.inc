#if defined _lololib_general_included
  #endinput
#endif
#define _lololib_general_included


// probably not relevant
stock void lolo_CloseHandle(Handle &hndl)
{
	if (hndl != null)
	{
		CloseHandle(hndl);
		hndl = null;
	}
}