//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlWin32Ver.h
//    Author:      Streamlet
//    Create Time: 2011-02-27
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLWIN32VER_H_0AF602A1_81D0_4829_88DB_7DD912BD2A35_INCLUDED__
#define __XLWIN32VER_H_0AF602A1_81D0_4829_88DB_7DD912BD2A35_INCLUDED__



#include "../xlDef.h"

#ifdef __XL_CPP11

// Including SDKDDKVer.h defines the highest available Windows platform.

// If you wish to build your application for a previous Windows platform, include WinSDKVer.h and
// set the _WIN32_WINNT macro to the platform you wish to support before including SDKDDKVer.h.

#include <SDKDDKVer.h>

#else

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER				// Allow use of features specific to Windows XP or later.
#define WINVER 0x0501		// Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif						

#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE			// Allow use of features specific to IE 6.0 or later.
#define _WIN32_IE 0x0600	// Change this to the appropriate value to target other versions of IE.
#endif

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#endif

#include <Windows.h>

#endif // #ifndef __XLWIN32VER_H_0AF602A1_81D0_4829_88DB_7DD912BD2A35_INCLUDED__
