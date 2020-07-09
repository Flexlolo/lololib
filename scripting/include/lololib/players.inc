#if defined _lololib_players_included
  #endinput
#endif
#define _lololib_players_included

stock bool lolo_IsClientValid(int client, bool bot_valid = false)
{
	if (client > 0 && client <= MaxClients)
	{
		if (IsClientConnected(client) && IsClientInGame(client))
		{
			if (bot_valid || !IsFakeClient(client))
			{
				return true;
			}
		}
	}
	return false;
}

stock bool lolo_IsClientAdmin(int client)
{
	return GetUserAdmin(client) != INVALID_ADMIN_ID;
}

stock bool lolo_CheckClientAdminFlag(int client, AdminFlag flag, AdmAccessMode mode = Access_Real)
{
	AdminId Admin = GetUserAdmin(client);

	if (Admin.HasFlag(flag, mode))
	{
		return true;
	}

	return false;
}

/*
WRAPPERS
*/

stock void lolo_GetClientPosition(int client, float vector[3])
{
	GetEntPropVector(client, Prop_Send, "m_vecOrigin", vector);
}

stock void lolo_GetClientEyePosition(int client, float vector[3])
{
	GetClientEyePosition(client, vector);
}

stock void lolo_GetClientVelocity(int client, float vector[3])
{
	GetEntPropVector(client, Prop_Data, "m_vecVelocity", vector);
}

stock void lolo_GetClientBaseVelocity(int client, float vector[3])
{
	GetEntPropVector(client, Prop_Data, "m_vecBaseVelocity", vector);
}

stock void lolo_GetClientAbsVelocity(int client, float vector[3])
{
	GetEntPropVector(client, Prop_Data, "m_vecAbsVelocity", vector);
}

stock float lolo_GetClientVelocityLengtn(int client, bool x, bool y, bool z)
{
	float vector[3];
	
	if (x) vector[0] = GetEntPropFloat(client, Prop_Data, "m_vecVelocity[0]");
	if (y) vector[1] = GetEntPropFloat(client, Prop_Data, "m_vecVelocity[1]");
	if (z) vector[2] = GetEntPropFloat(client, Prop_Data, "m_vecVelocity[2]");

	return GetVectorLength(vector);
}

stock float lolo_GetClientBaseVelocityLengtn(int client, bool x, bool y, bool z)
{
	float vector[3];
	
	if (x) vector[0] = GetEntPropFloat(client, Prop_Data, "m_vecBaseVelocity[0]");
	if (y) vector[1] = GetEntPropFloat(client, Prop_Data, "m_vecBaseVelocity[1]");
	if (z) vector[2] = GetEntPropFloat(client, Prop_Data, "m_vecBaseVelocity[2]");

	return GetVectorLength(vector);
}

stock float lolo_GetClientAbsVelocityLengtn(int client, bool x, bool y, bool z)
{
	float vector[3];

	if (x) vector[0] = GetEntPropFloat(client, Prop_Data, "m_vecAbsVelocity[0]");
	if (y) vector[1] = GetEntPropFloat(client, Prop_Data, "m_vecAbsVelocity[1]");
	if (z) vector[2] = GetEntPropFloat(client, Prop_Data, "m_vecAbsVelocity[2]");

	return GetVectorLength(vector);
}

stock int lolo_GetClientWaterLevel(int client)
{
	return GetEntProp(client, Prop_Data, "m_nWaterLevel");
}

stock void lolo_SetClientHealth(int client, int health)
{
	SetEntProp(client, Prop_Send, "m_iHealth", health);
}

stock void lolo_SetClientGod(int client, bool god)
{
	if (god)
	{
		SetEntProp(client, Prop_Data, "m_takedamage", 0, 1);
	}
	else
	{
		SetEntProp(client, Prop_Data, "m_takedamage", 2, 1);	
	}
}

stock bool lolo_GetClientGod(int client)
{
	return GetEntProp(client, Prop_Data, "m_takedamage") == 0;
}

stock int lolo_GetClientSpecTarget(int client)
{
	if (lolo_IsClientValid(client))
	{
		int specmode = GetEntProp(client, Prop_Send, "m_iObserverMode");

		// The client isn't spectating anyone
		if (specmode != 4 && specmode != 5) return -1;
		
		// Find out who the client is spectating.
		int target = GetEntPropEnt(client, Prop_Send, "m_hObserverTarget");
		return target;
	}
	return -1;	
}

stock int lolo_SetClientSpecTarget(int client, int target)
{
	SetEntPropEnt(client, Prop_Send, "m_hObserverTarget", target);
	SetEntProp(client, Prop_Send, "m_iObserverMode", 4);
}



#include <lololib/strings>

/*
Searches through valid players and finds one with spricified name

return client if found;
return 0 if more than one client is matching
return -1 if none are found
*/
stock int lolo_Find_Name(const char[] name, bool case_sensitive)
{
	int count;
	int lastfound = -1;

	char client_name[32];

	for (int client = 1; client <= MaxClients; client++)
	{
		if (CheckClient(client))
		{
			GetClientName(client, client_name, sizeof(client_name));

			if (lolo_CompareStringBeginning(client_name, name, case_sensitive))
			{
				lastfound = client;
				count++;
			}
		}
	}

	if (count > 1)
	{
		return 0;
	}

	return lastfound;
}

/*
Searches through valid players and finds one with spricified SteamID

return client if found;
return -1 if none are found
*/
stock int lolo_Find_SteamID(const char[] steamid, bool case_sensitive)
{
	char client_steamid[32];

	for (int client = 1; client <= MaxClients; client++)
	{
		if (lolo_IsClientValid(client))
		{
			GetClientAuthId(client, AuthId_Steam2, client_steamid, sizeof(client_steamid));

			if (StrEqual(client_steamid, steamid, case_sensitive))
			{
				return client;
			}
		}
	}

	return -1;
}


/*
Converts new SteamID3 to old SteamID2 format
*/
stock void lolo_SteamID2(char[] string, int maxlength, const char[] steamid3)
{
	/*
	Old: STEAM_0:A:B
	New: [U:1:B*2+A]
	Example: STEAM_0:1:1234 ---> [U:1:2469]
	*/

	int A,B,Z;

	strcopy(string, maxlength, steamid3);
	lolo_String_Remove(string, maxlength, "[U:1:");
	lolo_String_Remove(string, maxlength, "]");

	Z = StringToInt(string);
	A = Z % 2;
	B = (Z - A) / 2;
	Format(string, maxlength, "STEAM_0:%d:%d", A, B);
}

/*
Converts old SteamID2 format to unique SteamID3 integer
*/
stock int lolo_SteamID3I(const char[] steamid2)
{
	/*
	Old: STEAM_0:A:B
	New: [U:1:B*2+A]
	Example: STEAM_0:1:1234 ---> [U:1:2469]
	*/

	int A,B;

	char sParts[3][32];
	ExplodeString(steamid2, ":", sParts, sizeof(sParts), sizeof(sParts[]), true);

	A = StringToInt(sParts[1]);
	B = StringToInt(sParts[2]);

	return B*2 + A;
}