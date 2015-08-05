//------------------------------------------------------------------------------
// 
//
// File Name:   xlLog.h
// Author:      Streamlet
// Create Time: 2010-04-03
// Description: Streamlet Log
//
// Version history:
//      20100403: First version.
//      20100404: Add log level.
//      20100405: Add file name and line.
//
//------------------------------------------------------------------------------


#ifndef __XLLOG_H_504F06E0_64F2_484D_8626_C201BBD6F1EB_INCLUDED__
#define __XLLOG_H_504F06E0_64F2_484D_8626_C201BBD6F1EB_INCLUDED__


#include <xl/Common/String/xlString.h>

namespace xl
{

#define XL_CONCATENATE_DIRECTLY(s1, s2) s1##s2
#define XL_CONCATENATE(s1, s2)          XL_CONCATENATE_DIRECTLY(s1, s2)
#define XL_UNIQUE_VARIABLE(v)           XL_CONCATENATE(v, __LINE__)

#define XL_TO_STRING_DIRECTLY(s)        #s
#define XL_TO_STRING(s)                 XL_TO_STRING_DIRECTLY(s)
#define XL_CURRENT_LINE_A               XL_TO_STRING(__LINE__)

#define XL_UNICODE_STRING_DIRECTLY(s)   L##s
#define XL_UNICODE_STRING(s)            XL_UNICODE_STRING_DIRECTLY(s)
#define XL_CURRENT_FILE_W               XL_UNICODE_STRING(__FILE__)
#define XL_CURRENT_FUNCTION_W           XL_UNICODE_STRING(__FUNCTION__)
#define XL_CURRENT_LINE_W               XL_UNICODE_STRING(XL_CURRENT_LINE_A)


enum LOG_LEVEL
{
    LL_FATAL,
    LL_ERROR,
    LL_WARNING,
    LL_INFO,
    LL_VERBOSE
};

template <typename LogPolicy>
class FunctionScope
{
public:
    FunctionScope(const xl::String &funName, LOG_LEVEL logLevel, const xl::String &file, const xl::String &line)
    {
        logLevel_ = logLevel;
        file_ = file;
        funName_ = funName;
        line_ = line;
        LogPolicy::GetInstance().EnterFunction(logLevel_, file_, funName_, line_);
    }

    ~FunctionScope()
    {
        LogPolicy::GetInstance().LeaveFunction(logLevel_, file_, funName_, line_);
    }

private:
    LOG_LEVEL logLevel_;
    xl::String file_;
    xl::String funName_;
    xl::String line_;
};

#ifndef XL_LOG_POLICY
#define XL_LOG_POLICY ::xl::DefaultLogPolicy
#endif

#define XL_LOG_FUNCTION(logLevel)       ::xl::FunctionScope<XL_LOG_POLICY> XL_UNIQUE_VARIABLE(functionScope)(XL_CURRENT_FUNCTION_W, \
                                                                                                             logLevel,              \
                                                                                                             XL_CURRENT_FILE_W,     \
                                                                                                             XL_CURRENT_LINE_W)
#define XL_LOG(logLevel, format, ...)   XL_LOG_POLICY::GetInstance().Print(logLevel,                \
                                                                           XL_CURRENT_FILE_W,       \
                                                                           XL_CURRENT_FUNCTION_W,   \
                                                                           XL_CURRENT_LINE_W,       \
                                                                           format,                  \
                                                                           __VA_ARGS__)

#define XL_FATAL_FUNCTION()     XL_LOG_FUNCTION(::xl::LL_FATAL)
#define XL_ERROR_FUNCTION()     XL_LOG_FUNCTION(::xl::LL_ERROR)
#define XL_WARNING_FUNCTION()   XL_LOG_FUNCTION(::xl::LL_WARNING)
#define XL_INFO_FUNCTION()      XL_LOG_FUNCTION(::xl::LL_INFO)
#define XL_VERBOSE_FUNCTION()   XL_LOG_FUNCTION(::xl::LL_VERBOSE)

#define XL_FATAL(format, ...)   XL_LOG(::xl::LL_FATAL, format, __VA_ARGS__)
#define XL_ERROR(format, ...)   XL_LOG(::xl::LL_ERROR, format, __VA_ARGS__)
#define XL_WARNING(format, ...) XL_LOG(::xl::LL_WARNING, format, __VA_ARGS__)
#define XL_INFO(format, ...)    XL_LOG(::xl::LL_INFO, format, __VA_ARGS__)
#define XL_VERBOSE(format, ...) XL_LOG(::xl::LL_VERBOSE, format, __VA_ARGS__)

} // namespace xl

//------------------------------------------------------------------------------
// Default Log Policy
//
// The log policy class must implement GetInstance, EnterFunction, LeaveFunction,
// and Print, as the following class DefaultLogPolicy does.
//

#include <stdarg.h>
#include <stdio.h>
#include <xl/Common/String/xlString.h>

namespace xl
{

class DefaultLogPolicy
{
public:
    static DefaultLogPolicy &GetInstance()
    {
        static DefaultLogPolicy instance;
        return instance;
    }

public:
    void EnterFunction(LOG_LEVEL logLevel, const xl::String &file, const xl::String &funName, const xl::String &line)
    {
        fwprintf(stderr, L"%-7s: >>>>>>>>>> Enter %s (L%s)\n", (LPCTSTR)GetLogLevelString(logLevel), (LPCTSTR)funName, (LPCTSTR)line);
    }

    void LeaveFunction(LOG_LEVEL logLevel, const xl::String &file, const xl::String &funName, const xl::String &line)
    {
        fwprintf(stderr, L"%-7s: <<<<<<<<<< Leave %s (L%s)\n", (LPCTSTR)GetLogLevelString(logLevel), (LPCTSTR)funName, (LPCTSTR)line);
    }

    void Print(LOG_LEVEL logLevel, const xl::String &file, const xl::String &funName, const xl::String &line, const xl::String format, ...)
    {
        wchar_t prefix[10], postfix[10];
        swprintf(prefix, 10, L"%-7s: ", (LPCTSTR)GetLogLevelString(logLevel));
        swprintf(postfix, 10, L" (L%s)\n", (LPCTSTR)line);
        xl::String newFormat = prefix;
        newFormat += format;
        newFormat += postfix;

        va_list args;
        va_start(args, format);
        vfwprintf(stderr, (LPCTSTR)newFormat, args);
        va_end(args);
    }

private:
    xl::String GetLogLevelString(LOG_LEVEL logLevel)
    {
        switch (logLevel)
        {
        case LL_FATAL:
            return L"FATAL";
        case LL_ERROR:
            return L"ERROR";
        case LL_WARNING:
            return L"WARNING";
        case LL_INFO:
            return L"INFO";
        case LL_VERBOSE:
            return L"VERBOSE";
        default:
            return L"NOLEVEL";
        }
    }
};

} // namespace xl

//------------------------------------------------------------------------------
// Usage:
//
// If you accept the DefaultLogPolicy, just include xlLog.h where needed. Or, please
//
// 1. Create your own header file, e.g. TraceLog.h
// 2. Define macro XL_LOG_POLICY, e.g.
//     #define XL_LOG_POLICY MyLogPolicy
// 3. Include xlLog.h, e.g.
//     #include "xlLog.h"
// 4. Implement your class MyLogPolicy
// (Step 2, 3 and 4 are order-insensitive)
// 5. Include your own header file where needed.
//
// To log function entering and exiting, please put one of the following macro at the
// beginning of the function:
//     XL_FATAL_FUNCTION()
//     XL_ERROR_FUNCTION()
//     XL_WARNING_FUNCTION()
//     XL_INFO_FUNCTION()
//     XL_VERBOSE_FUNCTION()
//
// To log custom message, please use these macros:
//     XL_FATAL(format, ...)
//     XL_ERROR(format, ...)
//     XL_WARNING(format, ...)
//     XL_INFO(format, ...)
//     XL_VERBOSE(format, ...)
//

#endif // #ifndef __XLLOG_H_504F06E0_64F2_484D_8626_C201BBD6F1EB_INCLUDED__
