//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlSmartPtr.h
//    Author:      Streamlet
//    Create Time: 2011-05-21
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XLSMARTPTR_H_0020004E_79A8_4C64_B292_F102DBE1BF96_INCLUDED__
#define __XLSMARTPTR_H_0020004E_79A8_4C64_B292_F102DBE1BF96_INCLUDED__


#include <xl/xlDef.h>
#include <xl/Meta/xlTypeTraits.h>

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
            AddRef();
        }

        SmartPtr(const SmartPtr &that) :
            m_pData(nullptr), m_pRefCounter(nullptr)
        {
            this->m_pData = that.m_pData;
            this->m_pRefCounter = that.m_pRefCounter;
            this->AddRef();
        }

        SmartPtr &operator=(const SmartPtr &that)
        {
            if (this != &that && this->m_pData != that.m_pData)
            {
                this->Release();

                this->m_pData = that.m_pData;
                this->m_pRefCounter = that.m_pRefCounter;
                this->AddRef();    
            }

            return *this;
        }

        ~SmartPtr()
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

    public:
        T *RawPointer()
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

        SharedArray(const SharedPtr &that) :
            SmartPtrBase(that)
        {

        }
    };

} // namespace xl

#endif // #ifndef __XLSMARTPTR_H_0020004E_79A8_4C64_B292_F102DBE1BF96_INCLUDED__
