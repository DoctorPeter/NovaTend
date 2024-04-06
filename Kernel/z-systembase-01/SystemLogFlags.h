/****************************************************************

   Solution : NovaTend

   Project : z-systembase-01.dll

   Module : SystemLogFlags.h

   Description :  this module defines list
				  of flags that responsible for
				  managament of records to LOG-file during
				  debugging.

*****************************************************************/

#ifndef SYSTEM_LOG_FLAGS_H
#define SYSTEM_LOG_FLAGS_H

// General debug LOG trigger
#define _DEBUG_LOG


#ifdef _DEBUG_LOG

// All components
//#define _DEBUG_LOG_ALL

// AD manager
//#define _DEBUG_LOG_ADMAN

// Auth client
//#define _DEBUG_LOG_AUTH_CLIENT

// Authenticate
//#define _DEBUG_LOG_AUTH

// Auth WCP
//#define _DEBUG_LOG_AUTH_WCP

// Command history
//#define _DEBUG_LOG_CMD_HIST

// Command
//#define _DEBUG_LOG_CMD

// Content
//#define _DEBUG_LOG_CONTENT

// DB connect
//#define _DEBUG_LOG_DBCONNECT

// Desktop command manager
//#define _DEBUG_LOG_DESKTOP_CMD

// Desktop server
//#define _DEBUG_LOG_DESKTOP_SRV

// Email
//#define _DEBUG_LOG_EMAIL

// Encryption
//#define _DEBUG_LOG_ENCRYPTION

// Exceptions
//#define _DEBUG_LOG_EXCEPTION

// Host command manager
//#define _DEBUG_LOG_HOST_CMD

// Host server
//#define _DEBUG_LOG_HOST_SRV

// Hub command manager
//#define _DEBUG_LOG_HUB_CMD

// Hub server
//#define _DEBUG_LOG_HUB_SRV

// IPC-client
//#define _DEBUG_LOG_IPC_CLIENT

// IPC-server
//#define _DEBUG_LOG_IPC_SERVER

// License manager
//#define _DEBUG_LOG_LICMAN

// Scheduler
//#define _DEBUG_LOG_SCHEDULER

// Screen builder
//#define _DEBUG_LOG_SCREEN_BUILDER

// Serialization manager
//#define _DEBUG_LOG_SERIALIZE

// Settings manager
//#define _DEBUG_LOG_SETMAN

// SMS manager
//#define _DEBUG_LOG_SMS

// Synchronize manager
//#define _DEBUG_LOG_SYNCHRO

// Response validator
//#define _DEBUG_LOG_VAL_RESP

// Credential provider
//#define _DEBUG_LOG_WCP

// Windows service
//#define _DEBUG_LOG_WINSRV

// Write log
//#define _DEBUG_LOG_WRITELOG

// Update service
//#define _DEBUG_LOG_UPDATER

// Server service
//#define _DEBUG_SRV_SRV

#endif


#endif