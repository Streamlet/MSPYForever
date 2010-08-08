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


// Use the method by vczh(http://www.cppblog.com/vczh/archive/2010/06/27/118829.html)


#define TEST_CASE(name) \
class TestCase_##name   \
    {   \
    public: \
        TestCase_##name();  \
    } TestCase_##name##_Instance;    \
    TestCase_##name::TestCase_##name()


#define TEST_ASSERT(expression) \
    do  \
    {   \
        if (!(expression))  \
        {   \
            throw "Test assert fails."; \
        }   \
    }   \
    while (false)


#endif // #ifndef __UNITTESTFRAME_H_D6074214_D6DB_4590_9EF3_B25B76DB713D_INCLUDED__
