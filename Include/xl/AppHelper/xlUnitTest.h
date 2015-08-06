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
#include <tchar.h>
#include <stdio.h>

namespace xl
{
    namespace AppHelper
    {
        typedef Function<void(bool, const String &)> TestAssert;
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
                Map<String, int> mapFailedCases;

                for (auto it = m_mapTestCases.Begin(); it != m_mapTestCases.End(); ++it)
                {
                    if (!r.Match(it->Key))
                    {
                        continue;
                    }

                    int nSucceededAsserts = 0;
                    int nFailedAsserts = 0;

                    _tprintf(_T("Running test case '%s' ...\r\n"), (const TCHAR *)it->Key);
                    (it->Value)(Bind(this, &TestSuite::Assert, _1, _2, (int &)nSucceededAsserts, (int &)nFailedAsserts));
                    _tprintf(_T("%d succeeded, %d failed.\r\n"), nSucceededAsserts, nFailedAsserts);
                    _tprintf(_T("\r\n"));

                    if (nFailedAsserts <= 0)
                    {
                        ++nSucceededCases;
                    }
                    else
                    {
                        mapFailedCases[it->Key] = nFailedAsserts;
                    }
                }

                if (mapFailedCases.Empty())
                {
                    _tprintf(_T("All %d cases succeeded.\r\n"), nSucceededCases);
                }
                else
                {
                    _tprintf(_T("%d cases succeeded. Following %d cases failed:\r\n"), nSucceededCases, (int)mapFailedCases.Size());

                    for (auto it = mapFailedCases.Begin(); it != mapFailedCases.End(); ++it)
                    {
                        _tprintf(_T("%s (%d asserts failed.)\r\n"), (const TCHAR *)it->Key, it->Value);
                    }
                }

                return (int)mapFailedCases.Size();
            }

            void Assert(bool bResult, const String &strAssertExpr, int &nSucceededAsserts, int &nFailedAsserts)
            {
                if (bResult)
                {
                    ++nSucceededAsserts;
                    _tprintf(_T("[  OK  ] %s\r\n"), (const TCHAR *)strAssertExpr);
                }
                else
                {
                    ++nFailedAsserts;
                    _tprintf(_T("[Failed] %s\r\n"), (const TCHAR *)strAssertExpr);
                }
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
        fnAssert((expr), _T(XL_TOSTR(expr)))

#define XL_TEST_RUN_ALL_CASES(filter)   \
        xl::AppHelper::g_TestSuite.Run(filter)

    } // namespace AppHelper
} // namespace xl

#endif // #ifndef __XLUNITTEST_H_D6074214_D6DB_4590_9EF3_B25B76DB713D_INCLUDED__
