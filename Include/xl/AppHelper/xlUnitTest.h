//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlUnitTest.h
//    Author:      Streamlet
//    Create Time: 2010-08-08
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XLUNITTEST_H_D6074214_D6DB_4590_9EF3_B25B76DB713D_INCLUDED__
#define __XLUNITTEST_H_D6074214_D6DB_4590_9EF3_B25B76DB713D_INCLUDED__


#include "../Common/Meta/xlAssert.h"
#include "../Common/Meta/xlMacros.h"
#include "../Common/Meta/xlFunction.h"
#include "../Common/Meta/xlBind.h"
#include "../Common/Containers/xlMap.h"
#include "../Common/String/xlString.h"
#include "../Common/Parser/xlRegExp.h"
#include "../Windows/Console/xlConsole.h"
#include <tchar.h>
#include <stdio.h>

namespace xl
{
    namespace AppHelper
    {
        typedef Function<void(bool, const String &, const String &, int)> TestAssert;
        typedef Function<void(TestAssert)> TestCase;

        class TestSuite
        {
        public:
            TestSuite()
            {

            }

            ~TestSuite()
            {

            }

        protected:
            struct FailureInfo
            {
                String strExpr;
                String strFile;
                int nLine;

                FailureInfo() : nLine(0)
                {

                }

                FailureInfo(const String &strExpr, const String &strFile, int nLine) :
                    strExpr(strExpr), strFile(strFile), nLine(nLine)
                {

                }
            };

            typedef Array<FailureInfo> FailedAsserts;
            typedef Map<String, FailedAsserts> FailedCases;

        public:
            void AddTestCase(const String &strName, TestCase fnTestCase)
            {
                m_mapTestCases.Insert(strName, fnTestCase);
            }

            int Run(const String &strFilter)
            {
                RegExp r;

                if (!r.Parse(strFilter))
                {
                    r.Parse(_T(".*"));
                }

                int nSucceededCases = 0;
                FailedCases mapFailedCases;

                for (auto it = m_mapTestCases.Begin(); it != m_mapTestCases.End(); ++it)
                {
                    if (!r.Match(it->Key))
                    {
                        continue;
                    }

                    int nSucceededAsserts = 0;
                    FailedAsserts arrFailedAsserts;

                    Windows::StdOutput().SetTextAttribute(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    _tprintf(_T("Running test case '%s' ...\r\n"), (const TCHAR *)it->Key);
                    Windows::StdOutput().SetTextAttribute(0);

                    (it->Value)(Bind(this, &TestSuite::Assert, _1, _2, (int &)nSucceededAsserts, (FailedAsserts &)arrFailedAsserts, _3, _4));

                    Windows::StdOutput().SetTextAttribute(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    _tprintf(_T("%d succeeded, "), nSucceededAsserts);

                    if (!arrFailedAsserts.Empty())
                    {
                        Windows::StdOutput().SetTextAttribute(FOREGROUND_RED | FOREGROUND_INTENSITY);
                    }

                    _tprintf(_T("%d failed.\r\n"), (int)arrFailedAsserts.Size());

                    Windows::StdOutput().SetTextAttribute(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                    _tprintf(_T("\r\n"));
                    _tprintf(_T("\r\n"));

                    if (arrFailedAsserts.Empty())
                    {
                        ++nSucceededCases;
                    }
                    else
                    {
                        mapFailedCases[it->Key] = arrFailedAsserts;
                    }
                }

                Windows::StdOutput().SetTextAttribute(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

                if (mapFailedCases.Empty())
                {
                    _tprintf(_T("All %d cases succeeded.\r\n"), nSucceededCases);
                }
                else
                {
                    _tprintf(_T("%d cases succeeded."), nSucceededCases);

                    Windows::StdOutput().SetTextAttribute(FOREGROUND_RED | FOREGROUND_INTENSITY);
                    _tprintf(_T(" Following %d cases failed:\r\n"), (int)mapFailedCases.Size());

                    for (auto it = mapFailedCases.Begin(); it != mapFailedCases.End(); ++it)
                    {
                        Windows::StdOutput().SetTextAttribute(FOREGROUND_RED | FOREGROUND_INTENSITY);
                        _tprintf(_T("%s (%d asserts failed):\r\n"), (const TCHAR *)it->Key, (int)it->Value.Size());

                        for (auto itAssers = it->Value.Begin(); itAssers != it->Value.End(); ++itAssers)
                        {
                            Windows::StdOutput().SetTextAttribute(FOREGROUND_RED | FOREGROUND_INTENSITY);
                            _tprintf(_T("    %s"), (const TCHAR *)itAssers->strExpr);

                            Windows::StdOutput().SetTextAttribute(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                            _tprintf(_T(" (%s, L%d)\r\n"), (const TCHAR *)itAssers->strFile, itAssers->nLine);
                        }
                    }
                }

                Windows::StdOutput().SetTextAttribute(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

                return (int)mapFailedCases.Size();
            }

            void Assert(bool bResult, const String &strAssertExpr, int &nSucceededAsserts, FailedAsserts &arrFailedAsserts, const String &strFile, int nLine)
            {
                if (bResult)
                {
                    ++nSucceededAsserts;
                    Windows::StdOutput().SetTextAttribute(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    _tprintf(_T("[  OK  ]"));
                }
                else
                {
                    arrFailedAsserts.PushBack(FailureInfo(strAssertExpr, strFile, nLine));
                    Windows::StdOutput().SetTextAttribute(FOREGROUND_RED | FOREGROUND_INTENSITY);
                    _tprintf(_T("[Failed]"));
                }

                Windows::StdOutput().SetTextAttribute(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                _tprintf(_T(" %s\r\n"), (const TCHAR *)strAssertExpr);
            }

        protected:
            Map<String, TestCase> m_mapTestCases;
        };

        __declspec(selectany) xl::AppHelper::TestSuite g_TestSuite;

#define XL_TEST_CLASS_NAME(name)            name
#define XL_TEST_CLASS_INSTANCE_NAME(name)   XL_CONN(_, XL_TEST_CLASS_NAME(name))

#define XL_TEST_NAMED_CASE(name)                                                            \
                                                                                            \
    class XL_TEST_CLASS_NAME(name)                                                          \
    {                                                                                       \
    public:                                                                                 \
        XL_TEST_CLASS_NAME(name)()                                                          \
        {                                                                                   \
            xl::AppHelper::g_TestSuite.AddTestCase(_T(XL_TOSTR(XL_TEST_CLASS_NAME(name))),  \
                xl::AppHelper::TestCase(this, &XL_TEST_CLASS_NAME(name)::Run));             \
        }                                                                                   \
                                                                                            \
        void Run(xl::AppHelper::TestAssert);                                                \
                                                                                            \
    } XL_TEST_CLASS_INSTANCE_NAME(name);                                                    \
                                                                                            \
    void XL_TEST_CLASS_NAME(name)::Run(xl::AppHelper::TestAssert fnAssert)

#define XL_TEST_CASE()  XL_TEST_NAMED_CASE(XL_CONN(UnnamedTestCase, __LINE__))

#define XL_TEST_ASSERT(expr)    \
        fnAssert((expr), _T(XL_TOSTR(expr)), _T(__FILE__), __LINE__)

#define XL_TEST_RUN_ALL_CASES(filter)   \
        xl::AppHelper::g_TestSuite.Run(filter)

    } // namespace AppHelper
} // namespace xl

#endif // #ifndef __XLUNITTEST_H_D6074214_D6DB_4590_9EF3_B25B76DB713D_INCLUDED__
