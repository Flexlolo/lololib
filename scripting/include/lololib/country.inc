#include <geoip>

stock bool lolo_GetClientCountry(int client, char[] string, int maxlength, bool geoipcity=false)
{
	#if defined _geoipcity_included
	if (geoipcity && LibraryExists("GeoIPCity"))
	{	
		char ip[32];
		GetClientIP(client, ip, sizeof(ip));

		char city[45];
		char region[45];
		char country[45];
		char country_code[3];
		char country_code3[4];

		GeoipGetRecord(ip, city, region, country, country_code, country_code3);

		if (strlen(city) < 1 && strlen(country) < 1)
		{
			Format(string, maxlength, "???");
		}
		else
		{
			if (strlen(city) < 1)
			{
				Format(city, sizeof(city), "???");
			}

			if (strlen(country) < 1)
			{
				Format(country, sizeof(country), "???");
			}

			Format(string, maxlength, "%s, %s", country, city);
		}
	}
	else
	{
	#endif
		char ip[32];
		GetClientIP(client, ip, sizeof(ip));
		GeoipCountry(ip, string, maxlength);

		if (strlen(string) < 1)
		{
			Format(string, maxlength, "???");
		}
	#if defined _geoipcity_included
	}
	#endif
}