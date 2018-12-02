//----------------------------------------------------------------------------- 
// File: DxStdAfx.h 
// 
// Desc: Standard includes and precompiled headers for DXUT 
// 
// Copyright (c) Microsoft Corporation. All rights reserved. 
//----------------------------------------------------------------------------- 

#pragma once 

#ifndef DXSDK_STDAFX_H 
#define DXSDK_STDAFX_H 

#ifndef STRICT 
#define STRICT 
#endif 

// If app hasn't choosen, set to work with Windows 98, Windows Me, 
// Windows 2000, Windows XP and beyond
#ifndef NTDDI_VERSION
#define NTDDI_VERSION 0x06030000
#endif

#ifndef WINVER 
#define WINVER         0x0410 
#endif 
#ifndef _WIN32_WINDOWS 
#define _WIN32_WINDOWS 0x0410  
#endif 
#ifndef _WIN32_WINNT 
#define _WIN32_WINNT   0x0500  
#endif 

#define DIRECTSOUND_VERSION 0x0800 

// disable unreference formal parameter warnings for /W4 builds 
#pragma warning( disable : 4100 )  

#include <windows.h>
#include <excpt.h>
#include <wrl\client.h>
#include <assert.h> 
#include <wchar.h> 
#include <mmsystem.h> 
#include <commctrl.h> // for InitCommonControls()  
#include <shellapi.h> // for ExtractIcon() 
#include <new.h>      // for placement new 
#include <math.h>       
#include <limits.h>       
#include <stdio.h> 
#include <XInput.h> // Header for XInput APIs 

// CRT's memory leak detection 
#if defined(DEBUG) || defined(_DEBUG) 
#include <crtdbg.h> 
#endif 

// Enable extra D3D debugging in debug builds if using the debug DirectX 
// runtime. This makes D3D objects work well in the debugger watch window, but  
// slows down performance slightly. 
#if defined(DEBUG) || defined(_DEBUG) 
#ifndef D3D_DEBUG_INFO 
#define D3D_DEBUG_INFO 
#endif 
#endif 

// Direct3D includes
#include <d3dcompiler.h>
#include <D3D11.h>
#include <D3D10.h>
#include <dxgi1_3.h>
#include <DirectXMath.h>

// DirectSound includes 
#include <mmsystem.h> 
#include <mmreg.h> 
#include <dsound.h> 

// strsafe.h deprecates old unsecure string functions.  If you really do not  
// want to it to (not recommended), then uncomment the next line. 
#define STRSAFE_NO_DEPRECATE 

#ifndef STRSAFE_NO_DEPRECATE 
#pragma deprecated("strncpy") 
#pragma deprecated("wcsncpy") 
#pragma deprecated("_tcsncpy") 
#pragma deprecated("wcsncat") 
#pragma deprecated("strncat") 
#pragma deprecated("_tcsncat") 
#endif 

#pragma warning( disable : 4996 ) // disable deprecated warning  
#include <strsafe.h> 
#pragma warning( default : 4996 )  


#if defined(DEBUG) || defined(_DEBUG) 
#ifndef V 
#define V(x)           { hr = x; if( FAILED(hr) ) { DXUTTrace( __FILE__, (DWORD)__LINE__, hr, L#x, true ); } } 
#endif 
#ifndef V_RETURN 
#define V_RETURN(x)    { hr = x; if( FAILED(hr) ) { return DXUTTrace( __FILE__, (DWORD)__LINE__, hr, L#x, true ); } } 
#endif 
#else 
#ifndef V 
#define V(x)           { hr = x; } 
#endif 
#ifndef V_RETURN 
#define V_RETURN(x)    { hr = x; if( FAILED(hr) ) { return hr; } } 
#endif 
#endif 

#ifndef SAFE_DELETE 
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } } 
#endif     
#ifndef SAFE_DELETE_ARRAY 
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } } 
#endif     
#ifndef SAFE_RELEASE 
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } } 
#endif 

#endif // !defined(DXSDK_STDAFX_H)