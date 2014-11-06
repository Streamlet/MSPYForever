//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   TraceLog.cpp
//    Author:      Streamlet
//    Create Time: 2010-05-01
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------


#include <xl/String/xlString.h>
#include <Windows.h>
#include <tchar.h>
#include <iostream>
#include "TraceLog.h"

#define LOG_PREFIX  _T("[MSPYForever] ")

#define CONFIG_NAME_LOG_LEVEL      _T("LogLevel")
#define CONFIG_NAME_LOG_TARGET     _T("LogTarget")
#define CONFIG_NAME_LOG_CONTENT    _T("LogContent")
#define CONFIG_NAME_LOG_FILE       _T("LogFile")

#define CONFIG_VALUE_LOG_LEVEL_FATAL    0x00000001
#define CONFIG_VALUE_LOG_LEVEL_ERROR    0x00000002
#define CONFIG_VALUE_LOG_LEVEL_WARNING  0x00000004
#define CONFIG_VALUE_LOG_LEVEL_INFO     0x00000008
#define CONFIG_VALUE_LOG_LEVEL_VERBOSE  0x00000010

#define CONFIG_VALUE_LOG_TARGET_CONSOLE    0x00000001
#define CONFIG_VALUE_LOG_TARGET_DEBUGGER   0x00000002
#define CONFIG_VALUE_LOG_TARGET_FILE       0x00000004

#define CONFIG_VALUE_LOG_CONTENT_PREGIX    0x00000001
#define CONFIG_VALUE_LOG_CONTENT_LEVEL     0x00000002
#define CONFIG_VALUE_LOG_CONTENT_MESSAGE   0x00000004
#define CONFIG_VALUE_LOG_CONTENT_FILE      0x00000008
#define CONFIG_VALUE_LOG_CONTENT_FUNCTION  0x00000010
#define CONFIG_VALUE_LOG_CONTENT_LINE      0x00000020


#ifdef _DEBUG
#define CONFIG_VALUE_DEFAULT_LOG_LEVEL     (CONFIG_VALUE_LOG_LEVEL_FATAL     | CONFIG_VALUE_LOG_LEVEL_ERROR   | CONFIG_VALUE_LOG_LEVEL_WARNING   | CONFIG_VALUE_LOG_LEVEL_INFO | CONFIG_VALUE_LOG_LEVEL_VERBOSE)
#define CONFIG_VALUE_DEFAULT_LOG_TARGET    (CONFIG_VALUE_LOG_TARGET_DEBUGGER | CONFIG_VALUE_LOG_TARGET_FILE)
#define CONFIG_VALUE_DEFAULT_LOG_CONTENT   (CONFIG_VALUE_LOG_CONTENT_PREGIX  | CONFIG_VALUE_LOG_CONTENT_LEVEL | CONFIG_VALUE_LOG_CONTENT_MESSAGE | CONFIG_VALUE_LOG_CONTENT_LINE)
#define CONFIG_VALUE_DEFAULT_LOG_FILE      _T("MSPYForever.log")
#else
#define CONFIG_VALUE_DEFAULT_LOG_LEVEL     (CONFIG_VALUE_LOG_LEVEL_FATAL     | CONFIG_VALUE_LOG_LEVEL_ERROR   | CONFIG_VALUE_LOG_LEVEL_WARNING   | CONFIG_VALUE_LOG_LEVEL_INFO)
#define CONFIG_VALUE_DEFAULT_LOG_TARGET    (CONFIG_VALUE_LOG_TARGET_DEBUGGER)
#define CONFIG_VALUE_DEFAULT_LOG_CONTENT   (CONFIG_VALUE_LOG_CONTENT_PREGIX  | CONFIG_VALUE_LOG_CONTENT_LEVEL | CONFIG_VALUE_LOG_CONTENT_MESSAGE | CONFIG_VALUE_LOG_CONTENT_LINE)
#define CONFIG_VALUE_DEFAULT_LOG_FILE      _T("MSPYForever.log")
#endif


bool LogPolicy::initialized_ = false;

LogPolicy &LogPolicy::GetInstance()
{
    static LogPolicy instance;

    if (!initialized_)
    {
        instance.logLevel_   = CONFIG_VALUE_DEFAULT_LOG_LEVEL;
        instance.logTarget_  = 0;
        instance.logContent_ = CONFIG_VALUE_DEFAULT_LOG_CONTENT;
        instance.logFile_    = CONFIG_VALUE_DEFAULT_LOG_FILE;
        instance.logTarget_  = CONFIG_VALUE_DEFAULT_LOG_TARGET;

        initialized_ = true;
    }

    return instance;
}

LogPolicy::LogPolicy()
{
    InitializeCriticalSection(&cs_);
}

LogPolicy::~LogPolicy()
{
    DeleteCriticalSection(&cs_);
}

void LogPolicy::EnterFunction(::xl::LOG_LEVEL logLevel, const xl::String &file, const xl::String &funName, const xl::String &line)
{
    xl::String message = xl::String(L">>>>>>>>>> Enter ") + funName;
    PrintMessage(logLevel, file, funName, line, message);
}

void LogPolicy::LeaveFunction(::xl::LOG_LEVEL logLevel, const xl::String &file, const xl::String &funName, const xl::String &line)
{
    xl::String message = xl::String(L"<<<<<<<<<< Leave ") + funName;
    PrintMessage(logLevel, file, funName, line, message);
}

void LogPolicy::Print(::xl::LOG_LEVEL logLevel, const xl::String &file, const xl::String &funName, const xl::String &line, const wchar_t *format, ...)
{
    const int MAX_MSG_LENGTH = 1024;
    wchar_t message[MAX_MSG_LENGTH];
    memset((void *)message, 0, sizeof(message));

    va_list args;
    va_start(args, format);
    int len = vswprintf(message, MAX_MSG_LENGTH, format, args);
    va_end(args);

    for (int i = len - 1; i >= 0; --i)
    {
        if (message[i] == L'\r' || message[i] == L'\n')
        {
            message[i] = L'\0';
        }
        else
        {
            break;
        }
    }

    PrintMessage(logLevel, file, funName, line, message);
}

xl::String LogPolicy::GetLogLevelString(::xl::LOG_LEVEL logLevel)
{
    switch (logLevel)
    {
    case ::xl::LL_FATAL:
        return L"FATAL";
    case ::xl::LL_ERROR:
        return L"ERROR";
    case ::xl::LL_WARNING:
        return L"WARNING";
    case ::xl::LL_INFO:
        return L"INFO";
    case ::xl::LL_VERBOSE:
        return L"VERBOSE";
    default:
        return L"NOLEVEL";
    }
}

void LogPolicy::PrintMessage(::xl::LOG_LEVEL logLevel, const xl::String &file, const xl::String &funName, const xl::String &line, const xl::String &message)
{
    if ((logLevel & logLevel_) == 0)
    {
        return;
    }

    const int MAX_LEVEL_LENGTH = 10;
    wchar_t level[MAX_LEVEL_LENGTH];
    swprintf(level, MAX_LEVEL_LENGTH, L"%-7s ", (LPCTSTR)(GetLogLevelString(logLevel) + L":"));

    xl::String msg;

#ifdef COMPLIE_TIME_LOG_CONTENT_PREFIX
    if ((logContent_ & CONFIG_VALUE_LOG_CONTENT_PREGIX) != 0)
    {
        msg += LOG_PREFIX;
    }
#endif

#ifdef COMPLIE_TIME_LOG_CONTENT_LEVEL
    if ((logContent_ & CONFIG_VALUE_LOG_CONTENT_LEVEL) != 0)
    {
        msg += level;
    }
#endif

#ifdef COMPLIE_TIME_LOG_CONTENT_MESSAGE
    if ((logContent_ & CONFIG_VALUE_LOG_CONTENT_MESSAGE) != 0)
    {
        msg += message;
    }
#endif

#if (defined(COMPLIE_TIME_LOG_CONTENT_FILE) || defined(COMPLIE_TIME_LOG_CONTENT_FUNCTION) || defined(COMPLIE_TIME_LOG_CONTENT_LINE))
    if ((logContent_ & (CONFIG_VALUE_LOG_CONTENT_FILE | CONFIG_VALUE_LOG_CONTENT_FUNCTION | CONFIG_VALUE_LOG_CONTENT_LINE)) != 0)
    {
        msg += L" (";
    }
#endif

#ifdef COMPLIE_TIME_LOG_CONTENT_FILE
    if ((logContent_ & CONFIG_VALUE_LOG_CONTENT_FILE) != 0)
    {
        msg += file;

#if (defined(COMPLIE_TIME_LOG_CONTENT_FUNCTION) || defined(COMPLIE_TIME_LOG_CONTENT_LINE))
        if ((logContent_ & (CONFIG_VALUE_LOG_CONTENT_FUNCTION | CONFIG_VALUE_LOG_CONTENT_LINE)) != 0)
        {
            msg += L", ";
        }
#endif
    }
#endif

#ifdef COMPLIE_TIME_LOG_CONTENT_FUNCTION
    if ((logContent_ & CONFIG_VALUE_LOG_CONTENT_FUNCTION) != 0)
    {
        msg += funName;

#if (defined(COMPLIE_TIME_LOG_CONTENT_LINE))
        if ((logContent_ & (CONFIG_VALUE_LOG_CONTENT_LINE)) != 0)
        {
            msg += L", ";
        }
#endif
    }
#endif

#ifdef COMPLIE_TIME_LOG_CONTENT_LINE
    if ((logContent_ & CONFIG_VALUE_LOG_CONTENT_LINE) != 0)
    {
        msg += xl::String(L"L") +line;
    }
#endif

#if (defined(COMPLIE_TIME_LOG_CONTENT_FILE) || defined(COMPLIE_TIME_LOG_CONTENT_FUNCTION) || defined(COMPLIE_TIME_LOG_CONTENT_LINE))
    if ((logContent_ & (CONFIG_VALUE_LOG_CONTENT_FILE | CONFIG_VALUE_LOG_CONTENT_FUNCTION | CONFIG_VALUE_LOG_CONTENT_LINE)) != 0)
    {
        msg += L")";
    }
#endif

    msg += L"\r\n";
    
#ifdef COMPLIE_TIME_LOG_TARGET_CONSOLE
    if ((logTarget_ & CONFIG_VALUE_LOG_TARGET_CONSOLE) != 0)
    {
        PrintToConsole(msg);
    }
#endif

#ifdef COMPLIE_TIME_LOG_TARGET_DEBUGGER
    if ((logTarget_ & CONFIG_VALUE_LOG_TARGET_DEBUGGER) != 0)
    {
        PrintToDebugger(msg);
    }
#endif

#ifdef COMPLIE_TIME_LOG_TARGET_FILE
    if ((logTarget_ & CONFIG_VALUE_LOG_TARGET_FILE) != 0)
    {
        PrintToFile(msg);
    }
#endif
}

void LogPolicy::PrintToConsole(const xl::String &message)
{
    HANDLE hConsole = GetStdHandle(STD_ERROR_HANDLE);
    DWORD dwWritten = 0;
    WriteConsole(hConsole, message, message.Length(), &dwWritten, NULL);
}

void LogPolicy::PrintToDebugger(const xl::String &message)
{
    OutputDebugString(message);
}

void LogPolicy::PrintToFile(const xl::String &message)
{
    EnterCriticalSection(&cs_);

    HANDLE hFile = CreateFile(logFile_, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        hFile = CreateFile(logFile_, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_NEW, 0, NULL);

        if (hFile == INVALID_HANDLE_VALUE)
        {
            return;
        }

        WORD wUnicodeBOM = 0xfeff;
        DWORD dwWritten = 0;
        WriteFile(hFile, &wUnicodeBOM, sizeof(wUnicodeBOM), &dwWritten, NULL);
    }

    LARGE_INTEGER li;
    li.QuadPart = 0;
    SetFilePointer(hFile, li.LowPart, &li.HighPart, FILE_END);

    DWORD dwWritten = 0;
    WriteFile(hFile, message, message.Length() * sizeof(wchar_t), &dwWritten, NULL);

    CloseHandle(hFile);

    LeaveCriticalSection(&cs_);
}
