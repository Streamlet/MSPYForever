//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlLog.h
//    Author:      Streamlet
//    Create Time: 2015-02-25
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLLOG_H_D66E7ECF_5480_47E4_B502_6ACDA54CEE61_INCLUDED__
#define __XLLOG_H_D66E7ECF_5480_47E4_B502_6ACDA54CEE61_INCLUDED__


#include "../Common/Meta/xlMacros.h"
#include "../Common/Meta/xlScopeExit.h"
#include "../Common/String/xlString.h"
#include "../Windows/Threads/xlCriticalSection.h"
#include "../Windows/xlHandle.h"
#include <stdio.h>

// Define following macros before include this file
// #define XL_LOG_PREFIX L"[LogPrefix] "           // Log prefix
// #define XL_LOG_TARGET_DEBUGGER                  // Output to debugger
// #define XL_LOG_TARGET_CONSOLE                   // Output to console
// #define XL_LOG_TARGET_FILE L"%Temp%\xlLog.log"  // Output to file, supporting environment variables
// #define XL_LOG_CONTENT_SOURCEFILE               // Output source file name
// #define XL_LOG_CONTENT_FUNCTION                 // Output function name
// #define XL_LOG_CONTENT_LINE                     // Output line number
// #define XL_LOG_LEVEL_FATAL                      // Output log level fatal
// #define XL_LOG_LEVEL_ERROR                      // Output log level error
// #define XL_LOG_LEVEL_WARNING                    // Output log level warning
// #define XL_LOG_LEVEL_INFO                       // Output log level info
// #define XL_LOG_LEVEL_VERBOSE                    // Output log level verbose

namespace xl
{
    namespace AppHelper
    {
        namespace Log
        {
#ifdef XL_LOG_TARGET_DEBUGGER
            inline bool PrintToDebugger(const xl::String &strMessage)
            {
                OutputDebugString(strMessage);
                return true;
            }
#endif

#ifdef XL_LOG_TARGET_CONSOLE
            inline bool PrintToConsole(const xl::String &strMessage)
            {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

                if (hConsole == nullptr && AllocConsole())
                {
                    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                }

                if (hConsole == nullptr || hConsole == INVALID_HANDLE_VALUE)
                {
                    return false;
                }

                DWORD dwWritten = 0;
                WriteConsole(hConsole, strMessage, (DWORD)(strMessage.Length()), &dwWritten, NULL);

                return true;
            }
#endif

#ifdef XL_LOG_TARGET_FILE
            inline bool PrintToFile(const xl::String &strMessage)
            {
                static Windows::CriticalSection csLogFile;
                csLogFile.Lock();

                wchar_t szPath[MAX_PATH] = {};

                if (ExpandEnvironmentStrings(XL_LOG_TARGET_FILE, szPath, _countof(szPath)) == 0)
                {
                    return false;
                }

                HANDLE hFile = CreateFile(szPath, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

                if (hFile == INVALID_HANDLE_VALUE)
                {
                    hFile = CreateFile(szPath, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_NEW, 0, NULL);

                    if (hFile == INVALID_HANDLE_VALUE)
                    {
                        return false;
                    }

                    WORD wUnicodeBOM = 0xfeff;
                    DWORD dwWritten = 0;
                    WriteFile(hFile, &wUnicodeBOM, sizeof(wUnicodeBOM), &dwWritten, NULL);
                }

                XL_ON_BLOCK_EXIT(CloseHandle, hFile);

                LARGE_INTEGER li;
                li.QuadPart = 0;
                SetFilePointer(hFile, li.LowPart, &li.HighPart, FILE_END);

                DWORD dwWritten = 0;
                WriteFile(hFile, strMessage, (DWORD)(strMessage.Length() * sizeof(xl::Char)), &dwWritten, NULL);

                csLogFile.UnLock();

                return true;
            }
#endif

            inline void PrintMessage(const xl::String &strLevel, const xl::String &strMessage, const xl::String &strSourceFile, const xl::String &strFunctionName, const xl::String &strLine)
            {
                xl::String strOutput;

                SYSTEMTIME st = {};
                GetLocalTime(&st);
                WCHAR szTime[] = L"0000-00-00 00:00:00.000 BUFFER";
                swprintf_s(szTime, L"%04u-%02u-%02u %02u:%02u:%02u.%03u ", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
                strOutput += szTime;

#ifdef XL_LOG_PREFIX
                strOutput += XL_LOG_PREFIX;
#endif
                strOutput += strLevel;
                strOutput += strMessage;

#if defined(XL_LOG_CONTENT_SOURCEFILE) || defined(XL_LOG_CONTENT_FUNCTION) || defined(XL_LOG_CONTENT_LINE)
                strOutput += L" (";

#if defined(XL_LOG_CONTENT_SOURCEFILE)
                strOutput += strSourceFile;
#if defined(XL_LOG_CONTENT_FUNCTION) || defined(XL_LOG_CONTENT_LINE)
                strOutput += L", ";
#endif
#endif

#if defined(XL_LOG_CONTENT_FUNCTION)
                strOutput += strFunctionName;
#if defined(XL_LOG_CONTENT_LINE)
                strOutput += L", ";
#endif
#endif

#if defined(XL_LOG_CONTENT_LINE)
                strOutput += L"L";
                strOutput += strLine;
#endif

                strOutput += L")";
#endif

                strOutput += L"\r\n";

#ifdef XL_LOG_TARGET_DEBUGGER
                PrintToDebugger(strOutput);
#endif

#ifdef XL_LOG_TARGET_CONSOLE
                PrintToConsole(strOutput);
#endif

#ifdef XL_LOG_TARGET_FILE
                PrintToFile(strOutput);
#endif
            } // PrintMessage

            inline void LogEnterFunction(const xl::String &strLevel, const xl::String &strSourceFile, const xl::String &strFunctionName, const xl::String &strLine)
            {
                xl::String strMessage;
                strMessage += L">>>>>>>>>> Enter ";
                strMessage += strFunctionName;
                PrintMessage(strLevel, strMessage, strSourceFile, strFunctionName, strLine);
            }

            inline void LogLeaveFunction(const xl::String &strLevel, const xl::String &strSourceFile, const xl::String &strFunctionName, const xl::String &strLine)
            {
                xl::String strMessage;
                strMessage += L"<<<<<<<<<< Leave ";
                strMessage += strFunctionName;
                PrintMessage(strLevel, strMessage, strSourceFile, strFunctionName, strLine);
            }

            inline void LogFormat(const xl::String &strLevel, const xl::String &strSourceFile, const xl::String &strFunctionName, const xl::String &strLine, const wchar_t *strFormat, ...)
            {
                const int MAX_MSG_LENGTH = 1024;
                xl::Char szMessage[MAX_MSG_LENGTH] = {};

                va_list args;
                va_start(args, strFormat);
                int iLength = vswprintf_s(szMessage, MAX_MSG_LENGTH, strFormat, args);
                va_end(args);

                for (int i = iLength - 1; i >= 0; --i)
                {
                    if (szMessage[i] == L'\r' || szMessage[i] == L'\n')
                    {
                        szMessage[i] = L'\0';
                    }
                    else
                    {
                        break;
                    }
                }

                PrintMessage(strLevel, szMessage, strSourceFile, strFunctionName, strLine);
            }

#define XL_LOG_FILE        XL_CONN(L, __FILE__)
#define XL_LOG_FUNC        XL_CONN(L, __FUNCTION__)
#define XL_LOG_LINE        XL_CONN(L, XL_TOSTR(__LINE__))

#define XL_LOG_LEVEL_S_FATAL    L"Fatal:  "
#define XL_LOG_LEVEL_S_ERROR    L"Error:  "
#define XL_LOG_LEVEL_S_WARNING  L"Warning:"
#define XL_LOG_LEVEL_S_INFO     L"Info:   "
#define XL_LOG_LEVEL_S_VERBOSE  L"Verbose:"

#define XL_LOG_FUNCTION(level)      ::xl::AppHelper::Log::LogEnterFunction(level, XL_LOG_FILE, XL_LOG_FUNC, XL_LOG_LINE); \
                                    XL_ON_BLOCK_EXIT(::xl::AppHelper::Log::LogLeaveFunction, level, XL_LOG_FILE, XL_LOG_FUNC, XL_LOG_LINE)
#define XL_LOG(level, format, ...)  ::xl::AppHelper::Log::LogFormat(level, XL_LOG_FILE, XL_LOG_FUNC, XL_LOG_LINE, format, __VA_ARGS__)


#ifdef XL_LOG_LEVEL_FATAL
#define XL_LOG_FATAL_FUNCTION()     XL_LOG_FUNCTION(XL_LOG_LEVEL_S_FATAL)
#else
#define XL_LOG_FATAL_FUNCTION()
#endif

#ifdef XL_LOG_LEVEL_ERROR
#define XL_LOG_ERROR_FUNCTION()     XL_LOG_FUNCTION(XL_LOG_LEVEL_S_ERROR)
#else
#define XL_LOG_ERROR_FUNCTION()
#endif

#ifdef XL_LOG_LEVEL_WARNING
#define XL_LOG_WARNING_FUNCTION()   XL_LOG_FUNCTION(XL_LOG_LEVEL_S_WARNING)
#else
#define XL_LOG_WARNING_FUNCTION()
#endif

#ifdef XL_LOG_LEVEL_INFO
#define XL_LOG_INFO_FUNCTION()      XL_LOG_FUNCTION(XL_LOG_LEVEL_S_INFO)
#else
#define XL_LOG_INFO_FUNCTION()
#endif

#ifdef XL_LOG_LEVEL_VERBOSE
#define XL_LOG_VERBOSE_FUNCTION()   XL_LOG_FUNCTION(XL_LOG_LEVEL_S_VERBOSE)
#else
#define XL_LOG_VERBOSE_FUNCTION()
#endif


#ifdef XL_LOG_LEVEL_FATAL
#define XL_LOG_FATAL(format, ...)   XL_LOG(XL_LOG_LEVEL_S_FATAL,   format, __VA_ARGS__)
#else
#define XL_LOG_FATAL(format, ...)
#endif

#ifdef XL_LOG_LEVEL_ERROR
#define XL_LOG_ERROR(format, ...)   XL_LOG(XL_LOG_LEVEL_S_ERROR,   format, __VA_ARGS__)
#else
#define XL_LOG_ERROR(format, ...)
#endif

#ifdef XL_LOG_LEVEL_WARNING
#define XL_LOG_WARNING(format, ...) XL_LOG(XL_LOG_LEVEL_S_WARNING, format, __VA_ARGS__)
#else
#define XL_LOG_WARNING(format, ...)
#endif

#ifdef XL_LOG_LEVEL_INFO
#define XL_LOG_INFO(format, ...)    XL_LOG(XL_LOG_LEVEL_S_INFO,    format, __VA_ARGS__)
#else
#define XL_LOG_INFO(format, ...)
#endif

#ifdef XL_LOG_LEVEL_VERBOSE
#define XL_LOG_VERBOSE(format, ...) XL_LOG(XL_LOG_LEVEL_S_VERBOSE, format, __VA_ARGS__)
#else
#define XL_LOG_VERBOSE(format, ...)
#endif


        } // namespace Log
    } // namespace AppHelper
} // namespace xl

#endif // #ifndef __XLLOG_H_D66E7ECF_5480_47E4_B502_6ACDA54CEE61_INCLUDED__
