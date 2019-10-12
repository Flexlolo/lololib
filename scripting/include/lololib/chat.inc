#if defined _lololib_chat_included
  #endinput
#endif
#define _lololib_chat_included




stock void lolo_PrintToChat(int client, const char[] format, any:...)
{
	char buffer[252];
	VFormat(buffer, sizeof(buffer), format, 3);
	
	Handle hMessage = StartMessageOne("SayText2", client); 

	if (hMessage != INVALID_HANDLE) 
	{ 
		if (GetFeatureStatus(FeatureType_Native, "GetUserMessageType") == FeatureStatus_Available && GetUserMessageType() == UM_Protobuf) 
		{
			PbSetInt(hMessage, "ent_idx", client);
			PbSetBool(hMessage, "chat", true);
			PbSetString(hMessage, "msg_name", buffer);
			PbAddString(hMessage, "params", "");
			PbAddString(hMessage, "params", "");
			PbAddString(hMessage, "params", "");
			PbAddString(hMessage, "params", "");
		}
		else
		{
			BfWriteByte(hMessage, client);
			BfWriteByte(hMessage, true);
			BfWriteString(hMessage, buffer);
		}
		
		EndMessage();
	}
}





stock void lolo_SayText(int client, const char[] message, int author, bool mutable)
{
	Handle hMessage = StartMessageOne("SayText2", client); 

	if (hMessage != INVALID_HANDLE) 
	{ 
		if (GetFeatureStatus(FeatureType_Native, "GetUserMessageType") == FeatureStatus_Available && GetUserMessageType() == UM_Protobuf) 
		{
			if (mutable)
			{
				PbSetInt(hMessage, "ent_idx", author);
			}
			else
			{
				PbSetInt(hMessage, "ent_idx", client);
			}

			PbSetBool(hMessage, "chat", true);
			PbSetString(hMessage, "msg_name", message);
			PbAddString(hMessage, "params", "");
			PbAddString(hMessage, "params", "");
			PbAddString(hMessage, "params", "");
			PbAddString(hMessage, "params", "");
		}
		else
		{
			if (mutable)
			{
				BfWriteByte(hMessage, author);
			}
			else
			{
				BfWriteByte(hMessage, client);
			}
			
			BfWriteByte(hMessage, true);
			BfWriteString(hMessage, message);
		}
		
		EndMessage();
	}
}

stock void lolo_SayText_All(const char[] message, int author, bool mutable)
{
	for (int client = 1; client <= MaxClients; client++)
	{
		if (lolo_IsClientValid(client))
		{
			lolo_SayText(client, message, author, mutable);
		}
	}
}





stock void lolo_GetChatTeamColor(int team, char[] string, int maxlength)
{
	if (team == 2)
	{
		Format(string, maxlength, "\x07FF4040");
	}
	else if (team == 3)
	{
		Format(string, maxlength, "\x0799CCFF");
	}
	else
	{
		Format(string, maxlength, "\x07CCCCCC");
	}
}