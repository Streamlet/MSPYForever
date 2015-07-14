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


#include "../Meta/xlMacros.h"
#include "../Meta/xlScopeExit.h"
#include "../String/xlString.h"
#include "../Win32/Threads/xlCriticalSection.h"
#include "../Win32/xlHandle.h"
#include <tchar.h>

// Define following macros before include this file
// #define XL_LOG_PREFIX _T("[LogPrefix] ")             // Log prefix
// #define XL_LOG_TARGET_DEBUGGER                       // Output to debugger
// #define XL_LOG_TARGET_CONSOLE                        // Output to console
// #define XL_LOG_TARGET_FILE _T("%Temp%\xlLog.log")    // Output to file, supporting environment variables
// #define XL_LOG_CONTENT_SOURCEFILE                    // Output source file name
// #define XL_LOG_CONTENT_FUNCTION                      // Output function name
// #define XL_LOG_CONTENT_LINE                          // Output line number
#ifndef XL_LOG_LEVEL                                    // Output level
#define XL_LOG_LEVEL    0xffffffff                      // Output all for default
#endif

namespace xl
{
    namespace Log
    {
        enum LogLevel
        {
            LogLevel_Fatal      = 0x00000001,
            LogLevel_Error      = 0x00000002,
            LogLevel_Warning    = 0x00000004,
            LogLevel_Info       = 0x00000008,
            LogLevel_Verbose    = 0x00000010,
        };

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
            WriteConsole(hConsole, strMessage, strMessage.Length(), &dwWritten, NULL);

            return true;
        }

        inline bool PrintToDebugger(const xl::String &strMessage)
        {
            OutputDebugString(strMessage);
            return true;
        }

#ifdef XL_LOG_TARGET_FILE
        inline bool PrintToFile(const xl::String &strMessage)
        {
            static CriticalSection csLogFile;
            csLogFile.Lock();

            TCHAR szPath[MAX_PATH] = {};
            if (ExpandEnvironmentStrings(XL_LOG_TARGET_FILE, szPath, _countof(szPath)) == 0)
            {
                return false;
            }

            Handle hFile = CreateFile(szPath, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

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

            LARGE_INTEGER li;
            li.QuadPart = 0;
            SetFilePointer(hFile, li.LowPart, &li.HighPart, FILE_END);

            DWORD dwWritten = 0;
            WriteFile(hFile, strMessage, strMessage.Length() * sizeof(xl::Char), &dwWritten, NULL);

            csLogFile.UnLock();

            return true;
        }
#endif

        inline void PrintMessage(LogLevel eLevel, const xl::String &strMessage, const xl::String &strSourceFile, const xl::String &strFunctionName, const xl::String &strLine)
        {
            xl::String strOutput;

#ifdef XL_LOG_PREFIX
            strOutput += XL_LOG_PREFIX;
#endif

            LPCTSTR lpszLevel = nullptr;
            switch (eLevel)
            {
            case LogLevel_Fatal:
                lpszLevel = _T("Fatal:  ");
                break;
            case LogLevel_Error:
                lpszLevel = _T("Error:  ");
                break;
            case LogLevel_Warning:
                lpszLevel = _T("Warning:");
                break;
            case LogLevel_Info:
                lpszLevel = _T("Info:   ");
                break;
            case LogLevel_Verbose:
                lpszLevel = _T("Verbose:");
                break;
            default:
                lpszLevel = _T("");
                break;
            }
            strOutput += lpszLevel;

            strOutput += strMessage;

#if defined(XL_LOG_CONTENT_SOURCEFILE) || defined(XL_LOG_CONTENT_FUNCTION) || defined(XL_LOG_CONTENT_LINE)
            strOutput += _T(" (");

#if defined(XL_LOG_CONTENT_SOURCEFILE)
            strOutput += strSourceFile;
#if defined(XL_LOG_CONTENT_FUNCTION) || defined(XL_LOG_CONTENT_LINE)
            strOutput += _T(", ");
#endif
#endif

#if defined(XL_LOG_CONTENT_FUNCTION)
            strOutput += strFunctionName;
#if defined(XL_LOG_CONTENT_LINE)
            strOutput += _T(", ");
#endif
#endif

#if defined(XL_LOG_CONTENT_LINE)
            strOutput += _T("L");
            strOutput += strLine;
#endif

            strOutput += _T(")");
#endif

            strOutput += _T("\r\n");

#ifdef XL_LOG_TARGET_DEBUGGER
            PrintToConsole(strOutput);
#endif

#ifdef XL_LOG_TARGET_CONSOLE
            PrintToDebugger(strOutput);
#endif

#ifdef XL_LOG_TARGET_FILE
            PrintToFile(strOutput);
#endif
        } // PrintMessage

        inline void LogEnterFunction(LogLevel eLevel, const xl::String &strSourceFile, const xl::String &strFunctionName, const xl::String &strLine)
        {
            xl::String strMessage;
            strMessage += _T(">>>>>>>>>> Enter ");
            strMessage += strFunctionName;
            PrintMessage(eLevel, strMessage, strSourceFile, strFunctionName, strLine);
        }

        inline void LogLeaveFunction(LogLevel eLevel, const xl::String &strSourceFile, const xl::String &strFunctionName, const xl::String &strLine)
        {
            xl::String strMessage;
            strMessage += _T("<<<<<<<<<< Leave ");
            strMessage += strFunctionName;
            PrintMessage(eLevel, strMessage, strSourceFile, strFunctionName, strLine);
        }

        inline void LogFormat(LogLevel eLevel, const xl::String &strSourceFile, const xl::String &strFunctionName, const xl::String &strLine, const wchar_t *strFormat, ...)
        {
            const int MAX_MSG_LENGTH = 1024;
            xl::Char szMessage[MAX_MSG_LENGTH] = {};

            va_list args;
            va_start(args, strFormat);
            int iLength = _vstprintf_s(szMessage, MAX_MSG_LENGTH, strFormat, args);
            va_end(args);

            for (int i = iLength - 1; i >= 0; --i)
            {
                if (szMessage[i] == _T('\r') || szMessage[i] == _T('\n'))
                {
                    szMessage[i] = _T('\0');
                }
                else
                {
                    break;
                }
            }

            PrintMessage(eLevel, szMessage, strSourceFile, strFunctionName, strLine);
        }

#define XL_LOG_FILE        _T(__FILE__)
#define XL_LOG_FUNC        _T(__FUNCTION__)
#define XL_LOG_LINE        _T(XL_TOSTR(__LINE__))

#define XL_LOG_FUNCTION(level)      ::xl::Log::LogEnterFunction(level, XL_LOG_FILE, XL_LOG_FUNC, XL_LOG_LINE); \
                                    XL_ON_BLOCK_EXIT(::xl::Log::LogLeaveFunction, level, XL_LOG_FILE, XL_LOG_FUNC, XL_LOG_LINE)
#define XL_LOG(level, format, ...)  ::xl::Log::LogFormat(level, XL_LOG_FILE, XL_LOG_FUNC, XL_LOG_LINE, format, __VA_ARGS__)

#define XL_LOG_FATAL_FUNCTION()     XL_LOG_FUNCTION(::xl::Log::LogLevel_Fatal)
#define XL_LOG_ERROR_FUNCTION()     XL_LOG_FUNCTION(::xl::Log::LogLevel_Error)
#define XL_LOG_WARNING_FUNCTION()   XL_LOG_FUNCTION(::xl::Log::LogLevel_Warning)
#define XL_LOG_INFO_FUNCTION()      XL_LOG_FUNCTION(::xl::Log::LogLevel_Info)
#define XL_LOG_VERBOSE_FUNCTION()   XL_LOG_FUNCTION(::xl::Log::LogLevel_Verbose)

#define XL_LOG_FATAL(format, ...)   XL_LOG(::xl::Log::LogLevel_Fatal,   format, __VA_ARGS__)
#define XL_LOG_ERROR(format, ...)   XL_LOG(::xl::Log::LogLevel_Error,   format, __VA_ARGS__)
#define XL_LOG_WARNING(format, ...) XL_LOG(::xl::Log::LogLevel_Warning, format, __VA_ARGS__)
#define XL_LOG_INFO(format, ...)    XL_LOG(::xl::Log::LogLevel_Info,    format, __VA_ARGS__)
#define XL_LOG_VERBOSE(format, ...) XL_LOG(::xl::Log::LogLevel_Verbose, format, __VA_ARGS__)

    } // namespace Log

} // namespace xl

#endif // #ifndef __XLLOG_H_D66E7ECF_5480_47E4_B502_6ACDA54CEE61_INCLUDED__
