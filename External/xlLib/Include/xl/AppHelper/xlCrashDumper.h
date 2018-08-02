//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlCrashDumper.h
//    Author:      Streamlet
//    Create Time: 2016-03-26
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLCRASHDUMPER_H_77DCEC70_6894_4F30_9536_9660FE3A67E9_INCLUDED__
#define __XLCRASHDUMPER_H_77DCEC70_6894_4F30_9536_9660FE3A67E9_INCLUDED__


#include <xl/Common/Meta/xlScopeExit.h>
#include <Windows.h>
#pragma warning(push)
#pragma warning(disable: 4091)
#include <DbgHelp.h>
#pragma warning(pop)
#pragma comment(lib, "DbgHelp.lib")

// Define following macros before include this file
#ifndef XL_DUMP_FILE
#define XL_DUMP_FILE    L"%Temp%\\xlCrash.mdmp"  // Path of mini dump file, supporting environment variables
#endif

namespace xl
{
    namespace AppHelper
    {
        namespace CrashDumper
        {
            DWORD WINAPI ThreadProcWriteDumpFile(LPVOID lpParam)
            {
                PEXCEPTION_POINTERS pExceptionInfo = (PEXCEPTION_POINTERS)lpParam;

                WCHAR szPath[MAX_PATH] = {};

                if (ExpandEnvironmentStrings(XL_DUMP_FILE, szPath, _countof(szPath)) == 0)
                {
                    return 0;
                }

                HANDLE hFile = CreateFile(szPath, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, 0, nullptr);

                if (hFile == INVALID_HANDLE_VALUE)
                {
                    return 0;
                }

                XL_ON_BLOCK_EXIT(CloseHandle, hFile);

                MINIDUMP_EXCEPTION_INFORMATION mei = { GetCurrentThreadId(), pExceptionInfo, TRUE };
                MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpNormal, &mei, nullptr, nullptr);

                return 0;
            }

            LONG WINAPI TopLevelExceptionFilter(PEXCEPTION_POINTERS pExceptionInfo)
            {
                HANDLE hThread = CreateThread(NULL, 0, ThreadProcWriteDumpFile, pExceptionInfo, 0, nullptr);

                if (hThread != nullptr)
                {
                    WaitForSingleObject(hThread, INFINITE);
                    CloseHandle(hThread);
                }

                return EXCEPTION_EXECUTE_HANDLER;
            }

            void Initialize()
            {
                SetUnhandledExceptionFilter(TopLevelExceptionFilter);
            }
        }
    }
} // namesapce xl

#endif // #ifndef __XLCRASHDUMPER_H_77DCEC70_6894_4F30_9536_9660FE3A67E9_INCLUDED__
