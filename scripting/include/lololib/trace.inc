#if defined _lololib_trace_included
  #endinput
#endif
#define _lololib_trace_included

#include <sdktools>

stock bool lolo_IsPlayerOnRamp(int client)
{
	float min[3];
	float max[3];
	float p1[3];
	float p2[3];

	GetEntPropVector(client, Prop_Data, "m_vecOrigin", 	p1);
	GetEntPropVector(client, Prop_Data, "m_vecOrigin", 	p2);
	GetEntPropVector(client, Prop_Send, "m_vecMins", 	min);
	GetEntPropVector(client, Prop_Send, "m_vecMaxs", 	max);

	max[2] = min[2];
	p1[2] += 1.0;
	p2[2] -= 4.0;

	TR_TraceHullFilter(p1, p2, min, max, MASK_PLAYERSOLID_BRUSHONLY, lolo_IsPlayerOnRampFilter, client);

	if (TR_DidHit())
	{
		float plane[3];
		TR_GetPlaneNormal(null, plane);
		
		return 0.7 > plane[2];
	}

	return false;
}

public bool lolo_IsPlayerOnRampFilter(int entity, int mask, any data)
{
	return entity != data && !(0 < entity <= MaxClients);
}