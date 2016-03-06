//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlSafeSmartPtr.h
//    Author:      Streamlet
//    Create Time: 2011-05-21
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLSAFESMARTPTR_H_E74125A8_C767_44A2_8659_D350F7638ED6_INCLUDED__
#define __XLSAFESMARTPTR_H_E74125A8_C767_44A2_8659_D350F7638ED6_INCLUDED__


#include "../../Common/Memory/xlSmartPtr.h"
#include "../xlWin32Ver.h"

namespace xl
{
    namespace Windows
    {
        class WinSafeRefCounter
        {
        public:
            WinSafeRefCounter() :
                m_nCount(0)
            {

            }

            ~WinSafeRefCounter()
            {

            }

        public:
            int Increase()
            {
                return (int)InterlockedIncrement(&m_nCount);
            }

            int Decrease()
            {
                return (int)InterlockedDecrement(&m_nCount);
            }

        private:
            LONG m_nCount;
        };

        template <typename T>
        class SafeSharedPtr : public SmartPtr<T, ElementDeleter, WinSafeRefCounter>
        {
        protected:
            typedef SmartPtr<T, ElementDeleter, WinSafeRefCounter> SmartPtrBase;

        public:
            SafeSharedPtr()
            {

            }

            SafeSharedPtr(T *pData) :
                SmartPtrBase(pData)
            {

            }

            SafeSharedPtr(const SafeSharedPtr &that) :
                SmartPtrBase(that)
            {

            }

        };

        template <typename T>
        class SafeSharedArray : public SmartPtr<T, ArrayDeleter, WinSafeRefCounter>
        {
        protected:
            typedef SmartPtr<T, ArrayDeleter, WinSafeRefCounter> SmartPtrBase;

        public:
            SafeSharedArray()
            {

            }

            SafeSharedArray(T *pData) :
                SmartPtrBase(pData)
            {

            }

            SafeSharedArray(const SafeSharedArray &that) :
                SmartPtrBase(that)
            {

            }
        };

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLSAFESMARTPTR_H_E74125A8_C767_44A2_8659_D350F7638ED6_INCLUDED__
