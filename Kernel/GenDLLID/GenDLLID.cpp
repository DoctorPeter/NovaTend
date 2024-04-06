// GenDLLID.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <DllIDList.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


unsigned long RangedRand(long range_min, long range_max)
{
	unsigned long u = (double)rand() / (RAND_MAX + 1) * (range_max - range_min) + range_min;
	return u;
}


int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));

	unsigned long int key_ID[33] = {Z_WIN_CRED_PROV_DLL_ID,
									Z_WRITE_LOG_DLL_ID, 
									Z_EXCEPTIONS_DLL_ID,
									Z_SCREEN_BUILD_DLL_ID,
									Z_AUTHENTICATE_DLL_ID,
									Z_AUTH_CLIENT_DLL_ID,
									Z_DESKTOP_SERVER_ID,
									Z_AUTH_WCP_DLL_ID,
									Z_ENCRYPTION_DLL_ID, 
									Z_DB_CONNECT_DLL_ID,
									Z_CONTENT_DLL_ID,
									Z_VALIDATE_RESPONSE_DLL_ID,
									Z_IPC_CLIENT_DLL_ID,
									Z_IPC_SERVER_DLL_ID,
									Z_WIN_SERVICE_DLL_ID,
									Z_HOST_SERVER_ID,
									Z_HUB_SERVER_ID,
									Z_SERIALIZE_DLL_ID,
									Z_SET_MAN_DLL_ID,
									Z_LICENSE_MAN_DLL_ID,
									Z_AD_MAN_DLL_ID,
									Z_SYNC_DLL_ID,
									Z_EMAIL_DLL_ID,
									Z_SMS_DLL_ID,
									Z_COMMAND_DLL_ID,
									Z_HUBCMD_DLL_ID,
									Z_DESKTOPCMD_DLL_ID,
									Z_HOSTCMD_DLL_ID,
									Z_SCHEDULER_DLL_ID,
									Z_CMDHIST_DLL_ID,
									Z_UPDATE_SRV_ID,
									Z_SERVER_SERVICE_DLL_ID};

	
	unsigned short keyCount = 32;
	
	bool found;
	unsigned long randKey;

	for(int i = 0; i < 1; i++)
	{
		do
		{
			found = true;
			randKey = RangedRand(256, 4000000000);

			for(int k = 0; k < keyCount; k++)
				if ((key_ID[k] & (~randKey)) == 0)
					found = false;

		} while(!found);

		key_ID[keyCount] = randKey;
		keyCount++;
	}

	for(int i = 0; i < keyCount; i++)
	{
		printf("%d -> %X\n", i + 1, key_ID[i]);
	}

	return 0;
}

