//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlSmartPtr.h
//    Author:      Streamlet
//    Create Time: 2011-05-21
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLSMARTPTR_H_0020004E_79A8_4C64_B292_F102DBE1BF96_INCLUDED__
#define __XLSMARTPTR_H_0020004E_79A8_4C64_B292_F102DBE1BF96_INCLUDED__


#include "../../xlDef.h"

namespace xl
{
    struct ElementDeleter
    {
        template <typename T>
        static void Delete(T *pEmelent)
        {
            delete pEmelent;
        }
    };

    struct ArrayDeleter
    {
        template <typename T>
        static void Delete(T *pArray)
        {
            delete[] pArray;
        }
    };

    class BasicRefCounter
    {
    public:
        BasicRefCounter() :
            m_nCount(0)
        {

        }

        ~BasicRefCounter()
        {

        }

    public:
        int Increase()
        {
            return ++m_nCount;
        }

        int Decrease()
        {
            return --m_nCount;
        }

    private:
        int m_nCount;
    };

    template <typename T, typename Deleter, typename RefCounter>
    class SmartPtr
    {
    public:
        SmartPtr() :
            m_pData(nullptr), m_pRefCounter(nullptr)
        {
        }

        SmartPtr(T *pData) :
            m_pData(pData), m_pRefCounter(nullptr)
        {
            if (m_pData != nullptr)
            {
                AddRef();
            }
        }

        SmartPtr(const SmartPtr &that) :
            m_pData(nullptr), m_pRefCounter(nullptr)
        {
            this->m_pData = that.m_pData;
            this->m_pRefCounter = that.m_pRefCounter;

            AddRef();
        }

        SmartPtr &operator=(const SmartPtr &that)
        {
            if (this != &that && this->m_pData != that.m_pData)
            {
                Release();

                this->m_pData = that.m_pData;
                this->m_pRefCounter = that.m_pRefCounter;

                if (m_pData != nullptr)
                {
                    AddRef();    
                }
            }

            return *this;
        }

        virtual ~SmartPtr()
        {
            Release();
        }

    public:
        bool operator==(const SmartPtr &that) const
        {
            return this->m_pData == that.m_pData;
        }

        bool operator!=(const SmartPtr &that) const
        {
            return this->m_pData != that.m_pData;
        }

        bool operator==(const T *pThat) const
        {
            return this->m_pData == pThat;
        }

        bool operator!=(const T *pThat) const
        {
            return this->m_pData != pThat;
        }

    public:
        T &operator*() const
        {
            return *this->m_pData;
        }

        T *operator->() const
        {
            return this->m_pData;
        }

        const T &operator[](int i) const
        {
            return this->m_pData[i];
        }

        T &operator[](int i)
        {
            return this->m_pData[i];
        }

    public:
        T *RawPointer() const
        {
            return this->m_pData;
        }

    private:
        void AddRef()
        {
            if (m_pRefCounter == nullptr)
            {
                m_pRefCounter = new RefCounter;
            }

            m_pRefCounter->Increase();
        }

        void Release()
        {
            if (m_pRefCounter != nullptr && m_pRefCounter->Decrease() == 0)
            {
                delete m_pRefCounter;
                Deleter::Delete(m_pData);
            }
        }

    private:
        T *m_pData;
        RefCounter *m_pRefCounter;
    };

    template <typename T>
    class SharedPtr : public SmartPtr<T, ElementDeleter, BasicRefCounter>
    {
    protected:
        typedef SmartPtr<T, ElementDeleter, BasicRefCounter> SmartPtrBase;

    public:
        SharedPtr()
        {

        }

        SharedPtr(T *pData) :
            SmartPtrBase(pData)
        {

        }

        SharedPtr(const SharedPtr &that) :
            SmartPtrBase(that)
        {

        }
    };

    template <typename T>
    class SharedArray : public SmartPtr<T, ArrayDeleter, BasicRefCounter>
    {
    protected:
        typedef SmartPtr<T, ArrayDeleter, BasicRefCounter> SmartPtrBase;

    public:
        SharedArray()
        {

        }

        SharedArray(T *pData) :
            SmartPtrBase(pData)
        {

        }

        SharedArray(const SharedArray &that) :
            SmartPtrBase(that)
        {

        }
    };

} // namespace xl

//
// For convenience of debugging, put the following code to the [AutoExpand] section of
//     X:\Program Files\Microsoft Visual Studio 10.0\Common7\Packages\Debugger\autoexp.dat
//
// ;------------------------------------------------------------------------------
// ;  xl::SharedPtr, xl::SharedPtr
// ;------------------------------------------------------------------------------
// xl::SharedPtr<*>|xl::SharedArray<*>{
//     preview (
//         #(
//             "[",
//             #if ($e.m_pRefCounter == 0) ( 0 ) #else ( $e.m_pRefCounter->m_nCount ),
//             "] ",
//             $e.m_pData
//         )
//     )
//     children (
//         #(
//             [ref] : #if ($e.m_pRefCounter == 0) ( 0 ) #else ( $e.m_pRefCounter->m_nCount ),
//             [val] : *$e.m_pData
//         )
//     )
// }
//

#endif // #ifndef __XLSMARTPTR_H_0020004E_79A8_4C64_B292_F102DBE1BF96_INCLUDED__
