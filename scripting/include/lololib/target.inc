#if defined _lololib_target_included
  #endinput
#endif
#define _lololib_target_included

#include <lololib/players>
#include <lololib/strings>

enum
{
	lolo_Target_Group_Me,
	lolo_Target_Group_All,
	lolo_Target_Group_Humans,
	lolo_Target_Group_Bots,
	lolo_Target_Group_Admins,
	lolo_Target_Group_CT,
	lolo_Target_Group_T,
	lolo_Target_Group_SPEC,
	lolo_Target_Group_Alive,
	lolo_Target_Group_Dead,

	lolo_Target_Groups
}

#define CSS_TEAM_SPEC 	1
#define CSS_TEAM_T 		2
#define CSS_TEAM_CT 	3

/*
Process target string and return list of players matching search criteria

works with @all, @alive, etc. (can use multiple with '|' as AND operation (@all|@alive))

if doesnt find any group in string
it then tries to find player by SteamID if starts with '#' or by name otherwise

Requires handle to be closed afterwards.
*/
stock ArrayList lolo_Target_Process(int client, const char[] sTarget, bool case_sensitive = true)
{
	ArrayList hTargets = new ArrayList(1);
	
	if (strlen(sTarget))
	{
		int groups = lolo_Target_Groups_Parse(sTarget);

		if (groups)
		{
			if (client != 0 && groups & 1<<lolo_Target_Group_Me)
			{
				int target = client;

				if (lolo_IsClientValid(target, true))
				{
					if (lolo_Target_Groups_Check(target, groups))
					{
						hTargets.Resize(hTargets.Length + 1);
						hTargets.Set(hTargets.Length - 1, target);
					}
				}
			}
			else
			{
				for (int target = 1; target <= MaxClients; target++)
				{
					if (lolo_IsClientValid(target, true))
					{
						if (lolo_Target_Groups_Check(target, groups))
						{
							hTargets.Resize(hTargets.Length + 1);
							hTargets.Set(hTargets.Length - 1, target);
						}
					}
				}
			}
		}
		else
		{
			if (lolo_String_Startswith(sTarget, "#STEAM", true))
			{
				int target = lolo_Find_SteamID(sTarget[1], false);

				if (lolo_IsClientValid(target))
				{
					hTargets.Resize(hTargets.Length + 1);
					hTargets.Set(hTargets.Length - 1, target);
				}
			}
			else if (lolo_String_Startswith(sTarget, "#", true))
			{
				int target = StringToInt(sTarget[1]);

				if (lolo_IsClientValid(target, true))
				{
					hTargets.Resize(hTargets.Length + 1);
					hTargets.Set(hTargets.Length - 1, target);
				}
			}
			else
			{
				char name[32];

				for (int target = 1; target <= MaxClients; target++)
				{
					if (lolo_IsClientValid(target))
					{
						GetClientName(target, name, sizeof(name));

						if (lolo_String_Startswith(name, sTarget, case_sensitive))
						{
							hTargets.Resize(hTargets.Length + 1);
							hTargets.Set(hTargets.Length - 1, target);
						}
					}
				}
			}
		}
	}

	return hTargets;
}

stock int lolo_Target_Groups_Parse(const char[] sTarget)
{
	int groups;

	if (strlen(sTarget))
	{
		if (lolo_String_Startswith(sTarget, "@", true))
		{
			char sGroups[lolo_Target_Groups][32];

			ExplodeString(sTarget, "|", sGroups, sizeof(sGroups), sizeof(sGroups[]));

			int index;
			bool done;

			while (!done && index < lolo_Target_Groups)
			{
				if (strlen(sGroups[index]))
				{
					int group = lolo_Target_Groups_Get(sGroups[index]);

					if (group != -1)
					{
						groups ^= 1<<group;
					}

					index++;
				}
				else
				{
					done = true;
				}
			}
		}
	}

	return groups;
}

stock int lolo_Target_Groups_Get(const char[] sGroup)
{
	if (StrEqual(sGroup, "@me", true)) return lolo_Target_Group_Me;
	else if (StrEqual(sGroup, "@all", true)) return lolo_Target_Group_All;
	else if (StrEqual(sGroup, "@humans", true)) return lolo_Target_Group_Humans;
	else if (StrEqual(sGroup, "@bots", true)) return lolo_Target_Group_Bots;
	else if (StrEqual(sGroup, "@admins", true)) return lolo_Target_Group_Admins;
	else if (StrEqual(sGroup, "@ct", true)) return lolo_Target_Group_CT;
	else if (StrEqual(sGroup, "@t", true)) return lolo_Target_Group_T;
	else if (StrEqual(sGroup, "@spec", true)) return lolo_Target_Group_SPEC;
	else if (StrEqual(sGroup, "@alive", true)) return lolo_Target_Group_Alive;
	else if (StrEqual(sGroup, "@dead", true)) return lolo_Target_Group_Dead;

	return -1;
}

stock bool lolo_Target_Groups_Check(int client, int groups)
{
	int client_groups;

	if (groups & 1<<lolo_Target_Group_Me)
	{
		client_groups ^= 1<<lolo_Target_Group_Me;
	}

	if (groups & 1<<lolo_Target_Group_All)
	{
		client_groups ^= 1<<lolo_Target_Group_All;
	}

	if (groups & 1<<lolo_Target_Group_Humans)
	{
		if (!IsFakeClient(client))
		{
			client_groups ^= 1<<lolo_Target_Group_Humans;
		}
	}

	if (groups & 1<<lolo_Target_Group_Bots)
	{
		if (IsFakeClient(client))
		{
			client_groups ^= 1<<lolo_Target_Group_Bots;
		}
	}

	if (groups & 1<<lolo_Target_Group_Admins)
	{
		if (lolo_IsClientAdmin(client))
		{
			client_groups ^= 1<<lolo_Target_Group_Admins;
		}
	}

	if (groups & 1<<lolo_Target_Group_CT)
	{
		if (GetClientTeam(client) == CSS_TEAM_CT)
		{
			client_groups ^= 1<<lolo_Target_Group_CT;
		}
	}

	if (groups & 1<<lolo_Target_Group_T)
	{
		if (GetClientTeam(client) == CSS_TEAM_T)
		{
			client_groups ^= 1<<lolo_Target_Group_T;
		}
	}

	if (groups & 1<<lolo_Target_Group_SPEC)
	{
		if (GetClientTeam(client) <= CSS_TEAM_SPEC)
		{
			client_groups ^= 1<<lolo_Target_Group_SPEC;
		}
	}

	if (groups & 1<<lolo_Target_Group_Alive)
	{
		if (IsPlayerAlive(client))
		{
			client_groups ^= 1<<lolo_Target_Group_Alive;
		}
	}

	if (groups & 1<<lolo_Target_Group_Dead)
	{
		if (!IsPlayerAlive(client))
		{
			client_groups ^= 1<<lolo_Target_Group_Dead;
		}
	}

	return client_groups == groups;
}