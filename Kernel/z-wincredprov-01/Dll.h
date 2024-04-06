/****************************************************************

   Solution : NovaTend

   Project : z-wincredprov-01.dll

   Module : dll.h

   Description :  Defines the entry point for the DLL application.

*****************************************************************/


#pragma once

// Global dll hinstance
extern HINSTANCE g_hinst;

#define HINST_THISDLL g_hinst

// add global dll reference
void DllAddRef();

// remove global dll reference
void DllRelease();
