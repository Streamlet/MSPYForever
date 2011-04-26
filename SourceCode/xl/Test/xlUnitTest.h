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


#include <xl/Meta/xlAssert.h>
#include <xl/Meta/xlMacros.h>

namespace xl
{
#define XL_TEST_CLASS_NAME(name)            XL_CONN(xlTestCase, name)
#define XL_TEST_CLASS_INSTANCE_NAME(name)   XL_CONN(XL_TEST_CLASS_NAME(name), name)

#define XL_NAMED_TEST_CASE(name)                        \
                                                        \
    class XL_TEST_CLASS_NAME(name)                      \
    {                                                   \
    public:                                             \
        XL_TEST_CLASS_NAME(name)();                     \
                                                        \
    } XL_TEST_CLASS_INSTANCE_NAME(name);                \
                                                        \
    XL_TEST_CLASS_NAME(name)::XL_TEST_CLASS_NAME(name)()

#define XL_TEST_CASE()  XL_NAMED_TEST_CASE(__LINE__)

#define XL_TEST_ASSERT(expr)    XL_ASSERT(expr)

} // namespace xl

#endif // #ifndef __UNITTESTFRAME_H_D6074214_D6DB_4590_9EF3_B25B76DB713D_INCLUDED__
