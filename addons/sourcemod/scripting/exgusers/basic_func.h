const int g_const_midnight_timestamp=1654185600;
const int SQL_Inject_Str_Num = 14;
char SQL_Inject_List[SQL_Inject_Str_Num][64]={"\'","=",",",";","%","insert","select","update","create","exec","delete","declare","master","truncate"};
bool IsInSameTeam(int client1,int client2)
{
	if(GetClientTeam(client1)==GetClientTeam(client2))	return true;
	return false;
}
int Max(int a,int b)
{
	return a>=b?a:b;
}
int Min(int a,int b)
{
	return a<=b?a:b;
}
float fMax(float a,float b)
{
	return a>=b?a:b;
}
float fMin(float a,float b)
{
	return a<=b?a:b;
}
Action SetClientTeam(int client,int team)
{
	if(!IsClientInGame(client))	return Plugin_Handled;
	if (team == 1) FakeClientCommand(client, "jointeam spectator");
	if (team == 2) FakeClientCommand(client, "jointeam red");
	if (team == 3) FakeClientCommand(client, "jointeam blue");
	return Plugin_Handled;
}
bool DiffTimeTransform1(char buffer[PLATFORM_MAX_PATH],int timestamp1,int timestamp2,int total)
{
	int day,hour,minute;
	int diff_time;
	diff_time = total - (timestamp1 - timestamp2);
	if(diff_time <= 0)
	{
		return false;
	}
	else
	{
		day = diff_time / 86400;
		hour = (diff_time - day*86400)/ 3600;
		minute = (diff_time - day*86400 - hour *3600)/60;
		Format(buffer,sizeof(buffer),"冷却时间剩余:%d天%d小时%d分钟",day,hour,minute);
		return true;
	}
}
int IsClientVIP(int client)
{
	if(client<=0||client>=65)	return -1;
	if(!IsClientInGame(client))	return -1;
	if(IsFakeClient(client))	return -1;
	if (GetUserFlagBits(client) && ADMFLAG_RESERVATION)
	{
		return 1;
	}
	return 0;
}
void KillTimerSafe(Handle& timer) {
	if (!timer||timer==INVALID_HANDLE) return;
	KillTimer(timer);
	timer = INVALID_HANDLE;
}

void CloseHandleSafe(Handle& hndl) {
	if (!hndl&&hndl==INVALID_HANDLE) return;
	hndl.Close();
	hndl = null;
}

bool IsInClockTimePeriod(int start_point,int end_point)
{
	int current_time_reduced = (GetTime()-g_const_midnight_timestamp)%86400;
	int sp = start_point%24;
	int ep = end_point%24;
	int sp_t = sp*3600;
	int ep_t = ep*3600;
	if(sp_t<ep_t)
	{
		if(current_time_reduced>=sp_t&&current_time_reduced<=ep_t)	return true;
		else return false;
	}
	else
	{
		if(current_time_reduced>=sp_t&&current_time_reduced<=ep_t)	return false;
		else return true;
	}
}

void CheckSQLInjectString(char[] text,int maxlen)
{
	for(int i=0;i<SQL_Inject_Str_Num;i++)
	{
		ReplaceString(text,maxlen,SQL_Inject_List[i]," ",false);
	}
}