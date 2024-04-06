/****************************************************************

   Solution : NovaTend

   Project : z-sms-01.dll

   Module : GoogleVoiceSMSManager.cpp

   Description :  this module implements methods of
				  class GoogleVoiceSMSManager

*****************************************************************/

#include "stdafx.h"

#include <stdlib.h>
#include <regex>
#include "GoogleVoiceSMSManager.h"

// Version of google voice
#define GV_VERSION "v1.0.1"

// Cookie file name
#define GV_COOKIE_FILE	"GVOICE_COOKIE.TXT"

// Cookie time file name
#define GV_TIME_FILE	"GVOICE_TIME.DAT"

// Buffer size
int curlBufferSize = 0;

extern HMODULE g_hinst;

#pragma region Construction

/****************************************************************

   Class : GoogleVoiceSMSManager

   Method : Constructor

   Parameters :
			Input : 
				logWriter - pointer to LogWriter instance

*****************************************************************/
GoogleVoiceSMSManager :: GoogleVoiceSMSManager(unsigned long dllUserID, LogWriter * logWriter) : SMSManager(dllUserID, logWriter)
{
	// Initialize fields
	hCURL = NULL;
	loggedIn = false;

	curlBuffer = NULL;
	curlBufferSize = 0;
	curlCode = CURLE_OK;

	strcpy(version, GV_VERSION);
	email[0] = 0;
	password[0] = 0;
	rnrSE[0] = 0;
			
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
		WriteToLog("GoogleVoiceSMSManager : constructor");
	#endif

	// Initialize CURL
	Init();
}

/****************************************************************

   Class : GoogleVoiceSMSManager

   Method : Destructor

*****************************************************************/
GoogleVoiceSMSManager :: ~GoogleVoiceSMSManager(void)
{
	// Logout
	Logout();

	if(hCURL) 
	{
		// Cleanup CURL
		curl_easy_cleanup(hCURL);
	}

	curl_global_cleanup();

	// Remove buffer
	ClearCurlBuffer();

	// Delete cookie time file
	/*char fileName[MAX_PATH] = "";
	GetCookieTimeFileName(fileName);
	remove(fileName);*/

//	remove(GV_COOKIE_FILE);
//	remove(GV_TIME_FILE);

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
		WriteToLog("GoogleVoiceSMSManager : destructor");
	#endif
}

#pragma endregion

#pragma region Cookies

/****************************************************************

   Class : GoogleVoiceSMSManager

   Method : GetCookieFileName

   Parameters:

		Output:
			fileName - name of cookie file

   Return : Name of cookie file

   Description : Create name of cookie file

*****************************************************************/
char * GoogleVoiceSMSManager :: GetCookieFileName(char * fileName)
{
	// Get file name of DLL module
	GetModuleFileNameA(g_hinst, fileName, MAX_PATH);

	// Get file path
	for(size_t i = strlen(fileName) - 1; i >= 0; i--)
	  if (fileName[i] == '\\')
	  {
		  fileName[i + 1] = '\0';
		  break;
	  }

	strcat(fileName, GV_COOKIE_FILE);

	return fileName;
}

/****************************************************************

   Class : GoogleVoiceSMSManager

   Method : GetCookieTimeFileName

   Parameters:

		Output:
			fileName - name of cookie time file

   Return : Name of cookie file

   Description : Create name of cookie time file

*****************************************************************/
char * GoogleVoiceSMSManager :: GetCookieTimeFileName(char * fileName)
{
	// Get file name of DLL module
	GetModuleFileNameA(g_hinst, fileName, MAX_PATH);

	// Get file path
	for(size_t i = strlen(fileName) - 1; i >= 0; i--)
	  if (fileName[i] == '\\')
	  {
		  fileName[i + 1] = '\0';
		  break;
	  }

	strcat(fileName, GV_TIME_FILE);

	return fileName;
}

/****************************************************************

   Class : GoogleVoiceSMSManager

   Method : ReadCookieTime

   Return : TRUE if success

   Description :  Get cookie time

*****************************************************************/
bool GoogleVoiceSMSManager :: ReadCookieTime(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
		WriteToLog("GoogleVoiceSMSManager : ReadCookieTime. Start");
	#endif

	try
	{
		FILE * fp;

		// Open cookie time file
		/*char fileName[MAX_PATH] = "";
		GetCookieTimeFileName(fileName);*/

		fp = fopen(/*fileName*/GV_TIME_FILE, "r");

		if(fp == NULL)
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
				WriteToLog("GoogleVoiceSMSManager : ReadCookieTime. Can't open cookie time file!");
				WriteToLog("GoogleVoiceSMSManager : ReadCookieTime. Done");
			#endif

			return false;
		}
			
        unsigned long long int origTime;
		char tmpRNR[64], tmpEmail[128];
	
		// read time and rnr_se token
		fscanf(fp, "%s\n%s\n%Lu", tmpRNR, tmpEmail, &origTime);
		fclose(fp);

		
		time_t now, orig;
		orig = (time_t)origTime;

		// Get current time
		time(&now);

		// Count time difference
		double seconds = difftime(now,orig);

		// Check session time
		if (seconds >= 86400)
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
				WriteToLog("GoogleVoiceSMSManager : ReadCookieTime. Session time is up!");
				WriteToLog("GoogleVoiceSMSManager : ReadCookieTime. Done");
			#endif

			return false;
		}
		else
		{
			if(strcmp(email, tmpEmail) != 0)
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
					WriteToLog("GoogleVoiceSMSManager : ReadCookieTime. Email differs from previous!");
					WriteToLog("GoogleVoiceSMSManager : ReadCookieTime. Done");
				#endif

				return false;
			}
			else
			{
				strcpy(rnrSE, tmpRNR);
				loggedIn = true;

				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
					WriteToLog("GoogleVoiceSMSManager : ReadCookieTime. Get current session token!");
					WriteToLog("GoogleVoiceSMSManager : ReadCookieTime. Done");
				#endif

				return true;
			}
		}
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
			WriteToLog("GoogleVoiceSMSManager : ReadCookieTime. Can't read cookie time file!");
			WriteToLog("GoogleVoiceSMSManager : ReadCookieTime. Done");
		#endif

		return false;
	}
}

/****************************************************************

   Class : GoogleVoiceSMSManager

   Method : WriteCookieTime

   Return : TRUE if success

   Description :  Set cookie time

*****************************************************************/
bool GoogleVoiceSMSManager :: WriteCookieTime(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
		WriteToLog("GoogleVoiceSMSManager : WriteCookieTime. Start");
	#endif

	try
	{
		FILE * fp;

		// Open cookie file
		/*char fileName[MAX_PATH] = "";
		GetCookieTimeFileName(fileName);*/

		fp = fopen(GV_TIME_FILE/*fileName*/, "w");

		if(fp == NULL)
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
				WriteToLog("GoogleVoiceSMSManager : WriteCookieTime. Can't open cookie time file!");
				WriteToLog("GoogleVoiceSMSManager : WriteCookieTime. Done");
			#endif

			return false;
		}

		time_t now;

		// Get current itme
		time(&now);

		// Save cookie time data
		fprintf(fp, "%s\n%s\n%lu", rnrSE, email, (unsigned long long int)now);
		//fprintf(fp, "%s\n%s\n%Lu", rnrSE, email, now);

		fclose(fp);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
			WriteToLog("GoogleVoiceSMSManager : WriteCookieTime. Done");
		#endif

		return true;
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
			WriteToLog("GoogleVoiceSMSManager : WriteCookieTime. Can't write to cookie time file!");
			WriteToLog("GoogleVoiceSMSManager : WriteCookieTime. Done");
		#endif

		return false;
	}
}

#pragma endregion

#pragma region Login

/****************************************************************

   Class : GoogleVoiceSMSManager

   Method : Login

   Parameters:
		Input:
			login - user email
			password - password

   Return : Error code

   Description :  Login to Google Voice

*****************************************************************/
int GoogleVoiceSMSManager :: Login(char * login, char * password)
{
	// Check input data
	if ((login == NULL) || (password == NULL)) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
			WriteToLog("GoogleVoiceSMSManager : Login. Input data error!");
		#endif

		return GVOICE_INPUT_DATA_ERROR;
	}

	// Set email and password
	strcpy(this -> email, login);
	strcpy(this -> password, password);
	
		
	/*char fileName[MAX_PATH] = "";
	GetCookieFileName(fileName);*/

	// Check session
	if (!ReadCookieTime())
		curl_easy_setopt(hCURL, CURLOPT_COOKIEJAR, GV_COOKIE_FILE/*fileName*/);
	else
		curl_easy_setopt(hCURL, CURLOPT_COOKIEFILE, GV_COOKIE_FILE/*fileName*/);
	
	return Login();
}

/****************************************************************

   Class : GoogleVoiceSMSManager

   Method : Login

   Return : Error code

   Description :  Login to Google Voice

*****************************************************************/
int GoogleVoiceSMSManager :: Login(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
		WriteToLog("GoogleVoiceSMSManager : Login. Start");
	#endif

	if(!hCURL) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
			WriteToLog("GoogleVoiceSMSManager : Login. CURL is not initialized!");
			WriteToLog("GoogleVoiceSMSManager : Login. Done");
		#endif

		return GVOICE_CURL_ERROR;
	}

	if (loggedIn) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
			WriteToLog("GoogleVoiceSMSManager : Login. Aready logged!");
			WriteToLog("GoogleVoiceSMSManager : Login. Done");
		#endif

		return GVOICE_OK;
	}

	try
	{
		// Get GLAX token.
		curl_easy_setopt(hCURL, CURLOPT_URL, "https://accounts.google.com/ServiceLoginAuth");
		ClearCurlBuffer();
	
		curlCode = curl_easy_perform(hCURL);

		if((curlCode != CURLE_OK) || (curlBuffer == NULL))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
				WriteToLog("GoogleVoiceSMSManager : Login. Error of CURL using!");
				WriteToLog("GoogleVoiceSMSManager : Login. Done");
			#endif

			return GVOICE_CURL_ERROR;
		}
		else
		{
			curlBuffer = (char*)realloc(curlBuffer, curlBufferSize + 1); 
			curlBufferSize += 1;
			curlBuffer[curlBufferSize - 1] = '\0';
		}

		// Parse GALX token
		char galx[64];

		cmatch m;
		//if(regex_search(curlBuffer, m, regex("name=\"GALX\"\\s*type=\"hidden\"([\\s\\n\\t]*)value=\"([^\"]+)\"")))
		if (regex_search(curlBuffer, m, regex("type=\"hidden\"([\\s\\n\\t]*)name=\"GALX\"\\s*value=\"([^\"]+)\"")))
		{
			strcpy(galx, m[2].str().c_str());
		}

		char post[256];

		// Login and get rnr_se token.
		curl_easy_setopt(hCURL, CURLOPT_URL, "https://accounts.google.com/ServiceLogin?service=grandcentral&continue=https://www.google.com/voice");
		curl_easy_setopt(hCURL, CURLOPT_POST, 1);

		strcpy(post,"GALX=");
		strcat(post, galx);
		strcat(post, "&Email=");
		strcat(post, email);
		strcat(post, "&Passwd=");
		strcat(post, password);
		
		curl_easy_setopt(hCURL, CURLOPT_POSTFIELDS, post);
		ClearCurlBuffer();
	
		curlCode = curl_easy_perform(hCURL);

		if ((curlCode != CURLE_OK)  || (curlBuffer == NULL)) 
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
				WriteToLog("GoogleVoiceSMSManager : Login. Error of CURL using!");
				WriteToLog("GoogleVoiceSMSManager : Login. Done");
			#endif

			return GVOICE_CURL_ERROR;
		}
		else
		{
			curlBuffer = (char*)realloc(curlBuffer, curlBufferSize + 1); 
			curlBufferSize += 1;
			curlBuffer[curlBufferSize - 1] = '\0';
		}

		// Parse rnr_se session token
		if(regex_search(curlBuffer, m, regex("name=\"_rnr_se\"\\s*type=\"hidden\"([\\s\\n\\t]*)value=\"([^\"]+)\"")))
		{
			strcpy(rnrSE, m[2].str().c_str());
			loggedIn = true;

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
				WriteToLog("GoogleVoiceSMSManager : Login. Got rnr_se session token.");
				WriteToLog("GoogleVoiceSMSManager : Login. Done");
			#endif

			WriteCookieTime();

			return GVOICE_OK;
		}
		else
		{
			loggedIn = false;
		
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
				WriteToLog("GoogleVoiceSMSManager : Login. Failed to find rnr_se token. (Most likely a bad/mistyped email/passwd)!");
				WriteToLog("GoogleVoiceSMSManager : Login. Done");
			#endif

			return GVOICE_LOGIN_ERROR;
		}
	}
	catch(...)
	{
		loggedIn = false;
		
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
			WriteToLog("GoogleVoiceSMSManager : Login. Login error!");
			WriteToLog("GoogleVoiceSMSManager : Login. Done");
		#endif

		return GVOICE_LOGIN_ERROR;
	}
}

/****************************************************************

   Class : GoogleVoiceSMSManager

   Method : Logout

   Return : Error code

   Description :  Google Voice logout

*****************************************************************/
void GoogleVoiceSMSManager :: Logout(void) 
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
		WriteToLog("GoogleVoiceSMSManager : Logout");
	#endif

	rnrSE[0] = '\0';
    loggedIn = false;
}

#pragma endregion

#pragma region Send SMS

/****************************************************************

   Class : GoogleVoiceSMSManager

   Method : SendSMS

   Parameters:
		Input:
			number - phone number
			msg - text of message

   Return : Error code

   Description :  Send short message

*****************************************************************/
int GoogleVoiceSMSManager :: SendSMS(char * number, char * msg)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
		WriteToLog("GoogleVoiceSMSManager : SendSMS. Start");
	#endif

	if(!hCURL) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
			WriteToLog("GoogleVoiceSMSManager : SendSMS. CURL is not initialized!");
			WriteToLog("GoogleVoiceSMSManager : SendSMS. Done");
		#endif

		return GVOICE_CURL_ERROR;
	}

	// Check input data
	if ((number == NULL) || (msg == NULL)) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
			WriteToLog("GoogleVoiceSMSManager : SendSMS. Input data error!");
		#endif

		return GVOICE_INPUT_DATA_ERROR;
	}

	// Try to login
	if(Login() != GVOICE_OK) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
			WriteToLog("GoogleVoiceSMSManager : SendSMS. Login error!");
			WriteToLog("GoogleVoiceSMSManager : SendSMS. Done");
		#endif

		return GVOICE_LOGIN_ERROR;
	}

	try
	{
		curl_easy_setopt(hCURL, CURLOPT_URL, "https://www.google.com/voice/sms/send/");
		curl_easy_setopt(hCURL, CURLOPT_POST, 1);

		char post[1024];
		strcpy(post, "_rnr_se=");
		strcat(post, rnrSE);
		strcat(post, "&phoneNumber=");
		strcat(post, number);
		strcat(post, "&text=");
		strcat(post, msg);
	
		curl_easy_setopt(hCURL, CURLOPT_POSTFIELDS, post);
		ClearCurlBuffer();
	
		curlCode = curl_easy_perform(hCURL);

		if ((curlCode != CURLE_OK) || (curlBuffer == NULL))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
				WriteToLog("GoogleVoiceSMSManager : SendSMS. Error of CURL using!");
				WriteToLog("GoogleVoiceSMSManager : SendSMS. Done");
			#endif

			return GVOICE_CURL_ERROR;
		}
		else
		{
			curlBuffer = (char*)realloc(curlBuffer, curlBufferSize + 1); 
			curlBufferSize += 1;
			curlBuffer[curlBufferSize - 1] = '\0';
		}

		// Parse sending result
		cmatch m;
		if(regex_search(curlBuffer, m, regex("\"data\":\\{\"code\":(\\d+)\\}")))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
				WriteToLog("GoogleVoiceSMSManager : SendSMS. Success!");
				WriteToLog("GoogleVoiceSMSManager : SendSMS. Done");
			#endif

			return atoi(m[1].str().c_str());
		}
		else
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
				WriteToLog("GoogleVoiceSMSManager : SendSMS. Fail!");
				WriteToLog("GoogleVoiceSMSManager : SendSMS. Done");
			#endif

			return GVOICE_SMS_SEND_ERROR;
		}
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
			WriteToLog("GoogleVoiceSMSManager : SendSMS. General error!");
			WriteToLog("GoogleVoiceSMSManager : SendSMS. Done");
		#endif

		return GVOICE_SMS_SEND_ERROR;
	}
}

#pragma endregion

#pragma region SMS in(out)box

/****************************************************************

   Class : GoogleVoiceSMSManager

   Method : GetSMSThreads

   Return : Pointer to the SMS threads structure

   Description :  Get SMS threads

*****************************************************************/
PSMS_THREADS GoogleVoiceSMSManager :: GetSMSThreads(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
		WriteToLog("GoogleVoiceSMSManager : GetSMSThreads. Start");
	#endif

	if(!hCURL) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
			WriteToLog("GoogleVoiceSMSManager : GetSMSThreads. CURL is not initialized!");
			WriteToLog("GoogleVoiceSMSManager : GetSMSThreads. Done");
		#endif

		return NULL;
	}

	// Try to login
	if(Login() != GVOICE_OK) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
			WriteToLog("GoogleVoiceSMSManager : GetSMSThreads. Login error!");
			WriteToLog("GoogleVoiceSMSManager : GetSMSThreads. Done");
		#endif

		return NULL;
	}

	try
	{
		// Get page count
		int pageCount = GetPageCount();

		if (pageCount == 0)
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
				WriteToLog("GoogleVoiceSMSManager : GetSMSThreads. No messages pages!");
				WriteToLog("GoogleVoiceSMSManager : GetSMSThreads. Done");
			#endif

			return NULL;
		}

		// Create SMS threads structure
		PSMS_THREADS smsThreads = (PSMS_THREADS)malloc(sizeof(SMS_THREADS));
		smsThreads -> count = 0;

		int page = 1;

		// Retrieve all pages
		while(page <= pageCount) 
		{
			
			json_object * jobj = json_tokener_parse(curlBuffer);
			
			if (GetSMSThreads(jobj, smsThreads) != GVOICE_OK)
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
					WriteToLog("GoogleVoiceSMSManager : GetSMSThreads. Error of JSON parsing!");
					WriteToLog("GoogleVoiceSMSManager : GetSMSThreads. Done");
				#endif

				return DeleteSMSThreads(smsThreads);
			}

			page += 1;

			if (page <= pageCount)
			{
				char url[64];
				char pageNumber[8];
				strcpy(url, "https://www.google.com/voice/request/messages?page=");
				itoa(page, pageNumber, 10);
				strcat(url, pageNumber);
					
				curl_easy_setopt(hCURL, CURLOPT_URL, url);
				curl_easy_setopt(hCURL, CURLOPT_HTTPGET, 1);
		
				ClearCurlBuffer();
	
				curlCode = curl_easy_perform(hCURL);

				if ((curlCode != CURLE_OK) || (curlBuffer == NULL))
				{
					#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
						WriteToLog("GoogleVoiceSMSManager : GetSMSThreads. Error of CURL using!");
						WriteToLog("GoogleVoiceSMSManager : GetSMSThreads. Done");
					#endif

					return NULL;
				}
				else
				{
					curlBuffer = (char*)realloc(curlBuffer, curlBufferSize + 1); 
					curlBufferSize += 1;
					curlBuffer[curlBufferSize - 1] = '\0';
				}
			}
		} 

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
			WriteToLog("GoogleVoiceSMSManager : GetSMSThreads. Done");
		#endif

		return smsThreads;

	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
			WriteToLog("GoogleVoiceSMSManager : GetSMSThreads. Error of sms threads creating!");
			WriteToLog("GoogleVoiceSMSManager : GetSMSThreads. Done");
		#endif

		return NULL;
	}
}

/****************************************************************

   Class : GoogleVoiceSMSManager

   Method : GetSMSThreads

   Parameters:
		Input:
			jobj - JSON object
		Output:
			smsThreads - SMS threads instance

   Return : Error code

   Description :  Get SMS threads

*****************************************************************/
int GoogleVoiceSMSManager :: GetSMSThreads(json_object * jobj, PSMS_THREADS smsThreads)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
		WriteToLog("GoogleVoiceSMSManager : GetSMSThreads. Start");
	#endif

	// Check input data
	if ((jobj == NULL) || (smsThreads == NULL))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
			WriteToLog("GoogleVoiceSMSManager : GetSMSThreads. Wrong input data!");
			WriteToLog("GoogleVoiceSMSManager : GetSMSThreads. Done");
		#endif

		return GVOICE_INPUT_DATA_ERROR;
	}

	try
	{
		// Get SMS threads
		json_object * messLstObj = json_object_object_get(jobj, "messageList");

		int threadsCount = json_object_array_length(messLstObj);

		// Check all threads
		for(int i = 0; i < threadsCount; i++)
		{
			json_object * messValue = json_object_array_get_idx(messLstObj, i);
			json_object * labesObj = json_object_object_get(messValue, "labels");

			// Search of SMS label
			bool smsFound = false;
			int labelsCount = json_object_array_length(labesObj);

			for(int j = 0; j < labelsCount; j++)
			{
				json_object * labelValue = json_object_array_get_idx(labesObj, j);
				if (strcmp(json_object_get_string(labelValue), "sms") == 0)
				{
					smsFound = true;
					break;
				}
			}

			// If SMS label found
			if (smsFound)
			{
				// Create new message list
				smsThreads -> count++;

				if (smsThreads -> count > MAX_THREADS_COUNT)
				{
					#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
						WriteToLog("GoogleVoiceSMSManager : GetSMSThreads. Threads list overflow!");
						WriteToLog("GoogleVoiceSMSManager : GetSMSThreads. Done");
					#endif

					return GVOICE_GET_SMS_ERROR;
				}

				smsThreads -> threads[smsThreads -> count - 1] = (PSMS_MESSAGES_LIST)malloc(sizeof(SMS_MESSAGES_LIST));
				smsThreads -> threads[smsThreads -> count - 1] -> size = 0;

				// Parse message list
				json_object * childrenObj = json_object_object_get(messValue, "children");
				int childrenCount = json_object_array_length(childrenObj);

				for(int j = 0; j < childrenCount; j++)
				{
					smsThreads -> threads[smsThreads -> count - 1] -> size++;
					if (smsThreads -> threads[smsThreads -> count - 1] -> size > MAX_SMS_COUNT)
					{
						#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
							WriteToLog("GoogleVoiceSMSManager : GetSMSThreads. Messagges list overflow!");
							WriteToLog("GoogleVoiceSMSManager : GetSMSThreads. Done");
						#endif

						return GVOICE_GET_SMS_ERROR;
					}

					json_object * childrenValue = json_object_array_get_idx(childrenObj, j);

					// Create new message
					smsThreads -> threads[smsThreads -> count - 1] -> messages[j] = (PSMS_MESSAGE)malloc(sizeof(SMS_MESSAGE));
					smsThreads -> threads[smsThreads -> count - 1] -> messages[j] -> fromPhoneNumber[0] = 0;
					smsThreads -> threads[smsThreads -> count - 1] -> messages[j] -> toPhoneNumber[0] = 0;
					smsThreads -> threads[smsThreads -> count - 1] -> messages[j] -> messageTime[0] = 0;
					smsThreads -> threads[smsThreads -> count - 1] -> messages[j] -> messageText[0] = 0;

					// Parse message
					json_object * typeObj = json_object_object_get(childrenValue, "type");
					json_object * phone1Obj = json_object_object_get(childrenValue, "phoneNumber");
					json_object * phone2Obj = json_object_object_get(childrenValue, "did");
					json_object * timeObj = json_object_object_get(childrenValue, "displayStartDateTime");
					json_object * textObj = json_object_object_get(childrenValue, "message");
										
					int type = json_object_get_int(typeObj);
					strcpy(smsThreads -> threads[smsThreads -> count - 1] -> messages[j] -> messageTime, json_object_get_string(timeObj));
					strcpy(smsThreads -> threads[smsThreads -> count - 1] -> messages[j] -> messageText, json_object_get_string(textObj));

					// Check message type
					if (type == 10)
					{
						strcpy(smsThreads -> threads[smsThreads -> count - 1] -> messages[j] -> fromPhoneNumber, json_object_get_string(phone1Obj));
						strcpy(smsThreads -> threads[smsThreads -> count - 1] -> messages[j] -> toPhoneNumber, json_object_get_string(phone2Obj));
					}
					else
						if (type == 11)
						{
							strcpy(smsThreads -> threads[smsThreads -> count - 1] -> messages[j] -> fromPhoneNumber, json_object_get_string(phone2Obj));
							strcpy(smsThreads -> threads[smsThreads -> count - 1] -> messages[j] -> toPhoneNumber, json_object_get_string(phone1Obj));
						}
				}
			}
		}

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
			WriteToLog("GoogleVoiceSMSManager : GetSMSThreads. Done");
		#endif
			
		return GVOICE_OK;
	}
	catch(...)
	{
		
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
			WriteToLog("GoogleVoiceSMSManager : GetSMSThreads. Error of sms threads creating!");
			WriteToLog("GoogleVoiceSMSManager : GetSMSThreads. Done");
		#endif

		return GVOICE_GET_SMS_ERROR;
	}

}

/****************************************************************

   Class : GoogleVoiceSMSManager

   Method : GetPageCount

   Return : Get count of messages pages

   Description :  Get SMS threads

*****************************************************************/
int GoogleVoiceSMSManager :: GetPageCount(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
		WriteToLog("GoogleVoiceSMSManager : GetPageCount. Start");
	#endif

	if(!hCURL) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
			WriteToLog("GoogleVoiceSMSManager : GetPageCount. CURL is not initialized!");
			WriteToLog("GoogleVoiceSMSManager : GetPageCount. Done");
		#endif

		return 0;
	}

	// Try to login
	if(Login() != GVOICE_OK) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
			WriteToLog("GoogleVoiceSMSManager : GetPageCount. Login error!");
			WriteToLog("GoogleVoiceSMSManager : GetPageCount. Done");
		#endif

		return 0;
	}

	try
	{
		curl_easy_setopt(hCURL, CURLOPT_URL, "https://www.google.com/voice/request/messages?page=1");
		curl_easy_setopt(hCURL, CURLOPT_HTTPGET, 1);
		
		ClearCurlBuffer();
	
		curlCode = curl_easy_perform(hCURL);

		if ((curlCode != CURLE_OK) || (curlBuffer == NULL))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
				WriteToLog("GoogleVoiceSMSManager : GetPageCount. Error of CURL using!");
				WriteToLog("GoogleVoiceSMSManager : GetPageCount. Done");
			#endif

			return 0;
		}
		else
		{
			curlBuffer = (char*)realloc(curlBuffer, curlBufferSize + 1); 
			curlBufferSize += 1;
			curlBuffer[curlBufferSize - 1] = '\0';
		}

		// Parse JSON object
		json_object * jobj = json_tokener_parse(curlBuffer);
		int pageCount = GetPageCount(jobj);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
			WriteToLog("GoogleVoiceSMSManager : GetPageCount. Done");
		#endif

		return pageCount;
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
			WriteToLog("GoogleVoiceSMSManager : GetPageCount. Error of page count computing!");
			WriteToLog("GoogleVoiceSMSManager : GetPageCount. Done");
		#endif

		return 0;
	}
}

/****************************************************************

   Class : GoogleVoiceSMSManager

   Method : GetPageCount

   Parameters:
		Input:
			jobj - JSON object
			
   Return : page count

   Description :  Get count of messages pages

*****************************************************************/
int GoogleVoiceSMSManager :: GetPageCount(json_object * jobj)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
		WriteToLog("GoogleVoiceSMSManager : GetPageCount. Start");
	#endif

	int totalMessages = -1;
	int messagesPerPage = -1;
	int pageCount = 0;
		
	if(!jobj) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
			WriteToLog("GoogleVoiceSMSManager : GetPageCount. Empty JSON object!");
			WriteToLog("GoogleVoiceSMSManager : GetPageCount. Done");
		#endif

		return 0;
	}

	try
	{
		// Parse values
		json_object * new_obj = json_object_object_get(jobj, "totalSize");
		totalMessages = json_object_get_int(new_obj);
		new_obj = json_object_object_get(jobj, "resultsPerPage");
		messagesPerPage = atoi(json_object_get_string(new_obj));
		
		// Count page count
		if ((totalMessages != -1) && (messagesPerPage != -1))
		{
			pageCount = (totalMessages / messagesPerPage) + 1;

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
				WriteToLog("GoogleVoiceSMSManager : GetPageCount. Done");
			#endif

			return pageCount;
		}
		

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
			WriteToLog("GoogleVoiceSMSManager : GetPageCount. No pages!");
			WriteToLog("GoogleVoiceSMSManager : GetPageCount. Done");
		#endif

		return pageCount;
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
			WriteToLog("GoogleVoiceSMSManager : GetPageCount. Error of page count computing!");
			WriteToLog("GoogleVoiceSMSManager : GetPageCount. Done");
		#endif

		return 0;
	}
}

/****************************************************************

   Class : GoogleVoiceSMSManager

   Method : GetSMSInbox

   Parameters:
		Input:
			number - phone number
			
   Return : pointer to SMS list structure

   Description :  Get SMS inbox

*****************************************************************/
PSMS_MESSAGES_LIST GoogleVoiceSMSManager :: GetSMSInbox(char * number)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
		WriteToLog("GoogleVoiceSMSManager : GetSMSInbox. Start");
	#endif

	if(!number) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
			WriteToLog("GoogleVoiceSMSManager : GetSMSInbox. Bad input number!");
			WriteToLog("GoogleVoiceSMSManager : GetSMSInbox. Done");
		#endif

		return NULL;
	}

	try
	{
		PSMS_THREADS smsThreads = GetSMSThreads();
		
		if (smsThreads)
		{
			PSMS_MESSAGES_LIST messageList = (PSMS_MESSAGES_LIST)malloc(sizeof(SMS_MESSAGES_LIST));
			messageList -> size = 0;
			
			for(int i = 0; i < smsThreads -> count; i++)
			{
				for(int j = 0; j < smsThreads -> threads[i] -> size; j++)
				{
					if (strcmp(number, smsThreads -> threads[i] -> messages[j] -> toPhoneNumber) == 0)
					{
						messageList -> size++;
						messageList -> messages[messageList -> size - 1] = (PSMS_MESSAGE)malloc(sizeof(SMS_MESSAGE));
						memcpy(messageList -> messages[messageList -> size - 1], smsThreads -> threads[i] -> messages[j], sizeof(SMS_MESSAGE));
					}
				}
			}

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
				WriteToLog("GoogleVoiceSMSManager : GetSMSInbox. Done");
			#endif
			
			smsThreads = DeleteSMSThreads(smsThreads);
			return messageList;
		}
		else
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
				WriteToLog("GoogleVoiceSMSManager : GetSMSInbox. No SMS threads!");
				WriteToLog("GoogleVoiceSMSManager : GetSMSInbox. Done");
			#endif

			return NULL;
		}
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
			WriteToLog("GoogleVoiceSMSManager : GetSMSInbox. Error of message list creating!");
			WriteToLog("GoogleVoiceSMSManager : GetSMSInbox. Done");
		#endif

		return NULL;
	}
}

/****************************************************************

   Class : GoogleVoiceSMSManager

   Method : GetSMSOutbox

   Parameters:
		Input:
			number - phone number
			
   Return : pointer to SMS list structure

   Description :  Get SMS outbox

*****************************************************************/
PSMS_MESSAGES_LIST GoogleVoiceSMSManager :: GetSMSOutbox(char * number)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
		WriteToLog("GoogleVoiceSMSManager : GetSMSOutbox. Start");
	#endif

	if(!number) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
			WriteToLog("GoogleVoiceSMSManager : GetSMSOutbox. Bad input number!");
			WriteToLog("GoogleVoiceSMSManager : GetSMSOutbox. Done");
		#endif

		return NULL;
	}

	try
	{
		PSMS_THREADS smsThreads = GetSMSThreads();
		
		if (smsThreads)
		{
			PSMS_MESSAGES_LIST messageList = (PSMS_MESSAGES_LIST)malloc(sizeof(SMS_MESSAGES_LIST));
			messageList -> size = 0;
			
			for(int i = 0; i < smsThreads -> count; i++)
			{
				for(int j = 0; j < smsThreads -> threads[i] -> size; j++)
				{
					if (strcmp(number, smsThreads -> threads[i] -> messages[j] -> fromPhoneNumber) == 0)
					{
						messageList -> size++;
						messageList -> messages[messageList -> size - 1] = (PSMS_MESSAGE)malloc(sizeof(SMS_MESSAGE));
						memcpy(messageList -> messages[messageList -> size - 1], smsThreads -> threads[i] -> messages[j], sizeof(SMS_MESSAGE));
					}
				}
			}

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
				WriteToLog("GoogleVoiceSMSManager : GetSMSOutbox. Done");
			#endif

			smsThreads = DeleteSMSThreads(smsThreads);
			return messageList;
		}
		else
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
				WriteToLog("GoogleVoiceSMSManager : GetSMSOutbox. No SMS threads!");
				WriteToLog("GoogleVoiceSMSManager : GetSMSOutbox. Done");
			#endif

			return NULL;
		}
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
			WriteToLog("GoogleVoiceSMSManager : GetSMSOutbox. Error of message list creating!");
			WriteToLog("GoogleVoiceSMSManager : GetSMSOutbox. Done");
		#endif

		return NULL;
	}
}

#pragma endregion

#pragma region SMS data structures

/****************************************************************

   Class : GoogleVoiceSMSManager

   Method : DeleteSMSThreads

   Parameters:
		Input:
			smsThreads - pointer to SMS threads structure
			
   Return : pointer to SMS threads structure

   Description :  Delete SMS threads structure

*****************************************************************/
PSMS_THREADS GoogleVoiceSMSManager :: DeleteSMSThreads(PSMS_THREADS smsThreads)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
		WriteToLog("GoogleVoiceSMSManager : DeleteSMSThreads. Start");
	#endif

	if (smsThreads)
	{
		for(int i = 0; i < smsThreads -> count; i++)
			smsThreads -> threads[i] = DeleteSMSList(smsThreads -> threads[i]);

		free(smsThreads);

		smsThreads = NULL;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
		WriteToLog("GoogleVoiceSMSManager : DeleteSMSThreads. Done");
	#endif

	return smsThreads;
}

/****************************************************************

   Class : GoogleVoiceSMSManager

   Method : DeleteSMSList

   Parameters:
		Input:
			smsList - pointer to SMS list structure
			
   Return : pointer to SMS list structure

   Description :  Delete SMS list structure

*****************************************************************/
PSMS_MESSAGES_LIST GoogleVoiceSMSManager :: DeleteSMSList(PSMS_MESSAGES_LIST smsList)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
		WriteToLog("GoogleVoiceSMSManager : DeleteSMSList. Start");
	#endif
	
	if (smsList)
	{
		for(int i = 0; i < smsList -> size; i++)
			free(smsList -> messages[i]);

		free(smsList);

		smsList = NULL;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
		WriteToLog("GoogleVoiceSMSManager : DeleteSMSList. Done");
	#endif

	return smsList;
}

#pragma endregion

#pragma region cURL

/****************************************************************

   Class : GoogleVoiceSMSManager

   Method : Init

   Return : Error code

   Description :  Initialize CURL library

*****************************************************************/
int GoogleVoiceSMSManager :: Init(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
		WriteToLog("GoogleVoiceSMSManager : Init. Start");
	#endif

		
	curlCode = curl_global_init(CURL_GLOBAL_ALL);
	
	if (curlCode != CURLE_OK)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
			WriteToLog("GoogleVoiceSMSManager : Init. Error of CURL global init!");
			WriteToLog("GoogleVoiceSMSManager : Init. Done");
		#endif

		return GVOICE_CURL_ERROR;
	}
	

	// Init CURL
	hCURL = curl_easy_init(); 

	//hCURL = (CURL *)((int)hCURL + dllUserCheckResult);

	if(!hCURL) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
			WriteToLog("GoogleVoiceSMSManager : Init. Can't init CURL!");
			WriteToLog("GoogleVoiceSMSManager : Init. Done");
		#endif

		return GVOICE_CURL_ERROR;
	}

	// Set options
	curl_easy_setopt(hCURL, CURLOPT_ERRORBUFFER, errorBuffer);
	curl_easy_setopt(hCURL, CURLOPT_WRITEFUNCTION, CurlWriter);
	curl_easy_setopt(hCURL, CURLOPT_WRITEDATA, &curlBuffer);
    curl_easy_setopt(hCURL, CURLOPT_SSL_VERIFYPEER, 0);
    curl_easy_setopt(hCURL, CURLOPT_SSL_VERIFYHOST, 0);
	
	curl_easy_setopt(hCURL, CURLOPT_USERAGENT, "Mozilla/5.0 (X11; U; Linux x86_64; en-US; rv:1.9.2.8) Gecko/20100804 Gentoo Firefox/3.6.8");

	curl_easy_setopt(hCURL, CURLOPT_HEADER, 0);
	curl_easy_setopt(hCURL, CURLOPT_FOLLOWLOCATION, 1);
	
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
		WriteToLog("GoogleVoiceSMSManager : Init. Done");
	#endif

	return GVOICE_OK;
}


/****************************************************************

   Class : GoogleVoiceSMSManager

   Method : CurlWriter

   Parameters:
		Input:
			data - input data
			size - size of data block
			nMemb - count of blocks
		
		Output:
			buffer - result buffer

   Return : buffer size

   Description :  Write data CURL callback function

*****************************************************************/
int GoogleVoiceSMSManager :: CurlWriter(char * data, size_t size, size_t nMemb, char ** buffer)
{
	if (*buffer == NULL)
	{
		// If buffer is empty then alloc memory fot it
		*buffer = (char *)malloc(size*nMemb);
		curlBufferSize = 0;
	}
	else
	{
		// Else realloc memory for buffer
		*buffer = (char *)realloc(*buffer, curlBufferSize + size*nMemb); 
	}

  // Copy data to buffer
  memcpy(*buffer + curlBufferSize, data, size*nMemb);

  curlBufferSize += size*nMemb;
  
  return size*nMemb;
}

/****************************************************************

   Class : GoogleVoiceSMSManager

   Method : ClearCurlBuffer

   Return : buffer size

   Description : Clear CURL buffer

*****************************************************************/
int GoogleVoiceSMSManager :: ClearCurlBuffer(void)
{
	if (curlBuffer)
	{
		free(curlBuffer);
		curlBuffer = NULL;
		curlBufferSize = 0;
	}

	return curlBufferSize;
}

#pragma endregion

