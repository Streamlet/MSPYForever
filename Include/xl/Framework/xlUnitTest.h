//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   UnitTestFrame.h
//    Author:      Streamlet
//    Create Time: 2010-08-08
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __UNITTESTFRAME_H_D6074214_D6DB_4590_9EF3_B25B76DB713D_INCLUDED__
#define __UNITTESTFRAME_H_D6074214_D6DB_4590_9EF3_B25B76DB713D_INCLUDED__


#include "../Common/Meta/xlAssert.h"
#include "../Common/Meta/xlMacros.h"
#include <tchar.h>
#include <stdio.h>

namespace xl
{
#define XL_TEST_CLASS_NAME(name)            XL_CONN(xlTestCase, name)
#define XL_TEST_CLASS_INSTANCE_NAME(name)   XL_CONN(XL_TEST_CLASS_NAME(name), name)

#define XL_NAMED_TEST_CASE(name)                                                    \
                                                                                    \
    class XL_TEST_CLASS_NAME(name)                                                  \
    {                                                                               \
    public:                                                                         \
        XL_TEST_CLASS_NAME(name)() : m_nOK(0), m_nFailed(0)                         \
        {                                                                           \
            _tprintf(_T("Running test case '%s' ...\r\n"), _T(XL_TOSTR(name)));     \
            m_nOK = 0;                                                              \
            m_nFailed = 0;                                                          \
            Run();                                                                  \
            _tprintf(_T("%d succeeded, %d failed.\r\n"), m_nOK, m_nFailed);         \
            _tprintf(_T("\r\n"));                                                   \
        }                                                                           \
                                                                                    \
        void Run();                                                                 \
                                                                                    \
    private:                                                                        \
        int m_nOK;                                                                  \
        int m_nFailed;                                                              \
                                                                                    \
    } XL_TEST_CLASS_INSTANCE_NAME(name);                                            \
                                                                                    \
    void XL_TEST_CLASS_NAME(name)::Run()

#define XL_TEST_CASE()  XL_NAMED_TEST_CASE(XL_CONN(_unnamed_, __LINE__))

#define XL_TEST_ASSERT(expr)                                                        \
    do                                                                              \
    {                                                                               \
        _tprintf(_T("\tChecking test assert '%s' ..."), _T(XL_TOSTR(expr)));        \
        if (expr)                                                                   \
        {                                                                           \
            ++m_nOK;                                                                \
            _tprintf(_T(" OK.\r\n"));                                               \
        }                                                                           \
        else                                                                        \
        {                                                                           \
            ++m_nFailed;                                                            \
            _tprintf(_T(" Failed.\r\n"));                                           \
        }                                                                           \
                                                                                    \
    } while (false)

} // namespace xl

#endif // #ifndef __UNITTESTFRAME_H_D6074214_D6DB_4590_9EF3_B25B76DB713D_INCLUDED__
