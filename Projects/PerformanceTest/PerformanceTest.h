//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   PerformanceTest.h
//    Author:      Streamlet
//    Create Time: 2012-06-11
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __PERFORMANCETEST_H_75CF91CF_F93D_480A_B697_E69FF92D0D4A_INCLUDED__
#define __PERFORMANCETEST_H_75CF91CF_F93D_480A_B697_E69FF92D0D4A_INCLUDED__


#include <iostream>
#include <ctime>

#define SECTION_BEGIN(name)                                                                                                   \
    std::cout << "Testing \"" << #name << "\"..." << std::endl;
#define SECTION_END()                                                                                                         \
    std::cout << std::endl;
#define PERFORMANCE_TEST_BEGIN(name)                                                                                          \
    {                                                                                                                         \
        std::cout << "Test begins." << std::endl;                                                                             \
        clock_t begin_##name = clock()
#define PERFORMANCE_TEST_END(name)                                                                                            \
        clock_t end_##name = clock();                                                                                         \
        std::cout << "Test ends. Time elasped: " << (double)(end_##name - begin_##name) / CLOCKS_PER_SEC << "." << std::endl; \
    }

#endif // #ifndef __PERFORMANCETEST_H_75CF91CF_F93D_480A_B697_E69FF92D0D4A_INCLUDED__
