//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   TraceLog.h
//    Author:      Streamlet
//    Create Time: 2010-05-01
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __TRACELOG_H_404E7488_857C_4041_8BD7_4388BFE30810_INCLUDED__
#define __TRACELOG_H_404E7488_857C_4041_8BD7_4388BFE30810_INCLUDED__

#define COMPLIE_TIME_LOG_LEVEL_FATAL
#define COMPLIE_TIME_LOG_LEVEL_ERROR
#define COMPLIE_TIME_LOG_LEVEL_WARNING
#define COMPLIE_TIME_LOG_LEVEL_INFO
#define COMPLIE_TIME_LOG_LEVEL_VERBOSE

#define COMPLIE_TIME_LOG_TARGET_CONSOLE
#define COMPLIE_TIME_LOG_TARGET_DEBUGGER
#define COMPLIE_TIME_LOG_TARGET_FILE

#define COMPLIE_TIME_LOG_CONTENT_PREFIX
#define COMPLIE_TIME_LOG_CONTENT_LEVEL
#define COMPLIE_TIME_LOG_CONTENT_MESSAGE
#define COMPLIE_TIME_LOG_CONTENT_FILE
#define COMPLIE_TIME_LOG_CONTENT_FUNCTION
#define COMPLIE_TIME_LOG_CONTENT_LINE

#define XL_LOG_POLICY LogPolicy
#include "xlLog.h"
#include <xl/String/xlString.h>
#include <Windows.h>

class LogPolicy
{
public:
    static LogPolicy &GetInstance();

private:
    static bool initialized_;

private:
    LogPolicy();
    ~LogPolicy();

public:
    void EnterFunction(::xl::LOG_LEVEL logLevel, const xl::String &file, const xl::String &funName, const xl::String &line);
    void LeaveFunction(::xl::LOG_LEVEL logLevel, const xl::String &file, const xl::String &funName, const xl::String &line);
    void Print(::xl::LOG_LEVEL logLevel, const xl::String &file, const xl::String &funName, const xl::String &line, const wchar_t *format, ...);

private:
    xl::String GetLogLevelString(::xl::LOG_LEVEL logLevel);
    void PrintMessage(::xl::LOG_LEVEL logLevel, const xl::String &file, const xl::String &funName, const xl::String &line, const xl::String &message);
    void PrintToConsole(const xl::String &message);
    void PrintToDebugger(const xl::String &message);
    void PrintToFile(const xl::String &message);

private:
    DWORD logLevel_;
    DWORD logTarget_;
    DWORD logContent_;
    xl::String logFile_;
    CRITICAL_SECTION cs_;
};

#ifndef COMPLIE_TIME_LOG_LEVEL_FATAL
#define XL_FATAL()
#define XL_FATAL_FUNCTION()
#endif

#ifndef COMPLIE_TIME_LOG_LEVEL_ERROR
#define XL_ERROR()
#define XL_ERROR_FUNCTION()
#endif

#ifndef COMPLIE_TIME_LOG_LEVEL_WARNING
#define XL_WARNING()
#define XL_WARNING_FUNCTION()
#endif

#ifndef COMPLIE_TIME_LOG_LEVEL_INFO
#define XL_INFO()
#define XL_INFO_FUNCTION()
#endif

#ifndef COMPLIE_TIME_LOG_LEVEL_VERBOSE
#define XL_VERBOSE()
#define XL_VERBOSE_FUNCTION()
#endif


#endif // #ifndef __TRACELOG_H_404E7488_857C_4041_8BD7_4388BFE30810_INCLUDED__
