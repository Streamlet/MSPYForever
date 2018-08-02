//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlPerfTest.h
//    Author:      Streamlet
//    Create Time: 2015-11-08
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLPERFTEST_H_17B83870_FC01_404C_BB61_8329747C04BC_INCLUDED__
#define __XLPERFTEST_H_17B83870_FC01_404C_BB61_8329747C04BC_INCLUDED__


#include "../Common/Meta/xlAssert.h"
#include "../Common/Meta/xlMacros.h"
#include <time.h>
#include <stdio.h>

namespace xl
{
    namespace AppHelper
    {

#define XL_PERF_CLASS_NAME(name)            XL_CONN(xlPerfTest_, name)

#define XL_BEGIN_PERF_TEST(name)                                                                    \
        {                                                                                           \
            class XL_PERF_CLASS_NAME(name)                                                          \
            {                                                                                       \
            public:                                                                                 \
                XL_PERF_CLASS_NAME(name)()                                                          \
                {                                                                                   \
                    wprintf(L"Testing %s ...\n", XL_TOWCS(name));                                   \
                    m_tStart = clock();                                                             \
                    Run();                                                                          \
                }                                                                                   \
                ~XL_PERF_CLASS_NAME(name)()                                                         \
                {                                                                                   \
                    clock_t tEnd = clock();                                                         \
                    wprintf(L"Time elasped: %lf\n\n", (double)(tEnd - m_tStart) / CLOCKS_PER_SEC);  \
                }                                                                                   \
            private:                                                                                \
                clock_t m_tStart;                                                                   \
                void Run()                                                                          \

#define XL_END_PERF_TEST()                                                                          \
            } XL_CONN(xlPertTestIntance_, __COUNTER__);                                             \
        }                                                                                           \

    } // namespace AppHelper
} // namespace xl


#endif // #ifndef __XLPERFTEST_H_17B83870_FC01_404C_BB61_8329747C04BC_INCLUDED__
