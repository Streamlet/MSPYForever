//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlComPtr.h
//    Author:      Streamlet
//    Create Time: 2013-04-20
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLCOMPTR_H_E52D7EAE_DC76_4D71_8CB0_A22C1AAB5463_INCLUDED__
#define __XLCOMPTR_H_E52D7EAE_DC76_4D71_8CB0_A22C1AAB5463_INCLUDED__


#include "../xlWin32Ver.h"

namespace xl
{
    namespace Windows
    {
        template <typename T>
        class ComPtr
        {
        public:
            ComPtr() :
                m_pData(nullptr)
            {
            }

            ComPtr(T *pData) :
                m_pData(pData)
            {
                if (m_pData != nullptr)
                {
                    AddRef();
                }
            }

            ComPtr(const ComPtr &that) :
                m_pData(nullptr)
            {
                this->m_pData = that.m_pData;

                AddRef();
            }

            ComPtr &operator=(const ComPtr &that)
            {
                if (this != &that && this->m_pData != that.m_pData)
                {
                    Release();

                    this->m_pData = that.m_pData;

                    if (m_pData != nullptr)
                    {
                        AddRef();
                    }
                }

                return *this;
            }

            ~ComPtr()
            {
                Release();
            }

        public:
            bool operator == (const ComPtr &that) const
            {
                return this->m_pData == that.m_pData;
            }

            bool operator != (const ComPtr &that) const
            {
                return this->m_pData != that.m_pData;
            }

            bool operator == (const T *pThat) const
            {
                return this->m_pData == pThat;
            }

            bool operator != (const T *pThat) const
            {
                return this->m_pData != pThat;
            }

        public:
            T &operator * () const
            {
                return *this->m_pData;
            }

            T *operator -> () const
            {
                return this->m_pData;
            }

        public:
            operator T * () const
            {
                return this->m_pData;
            }

            T **operator & ()
            {
                return &this->m_pData;
            }

        private:
            void AddRef()
            {
                if (m_pData != nullptr)
                {
                    m_pData->AddRef();
                }
            }

            void Release()
            {
                if (m_pData != nullptr)
                {
                    m_pData->Release();
                }
            }

        private:
            T *m_pData;
        };

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLCOMPTR_H_E52D7EAE_DC76_4D71_8CB0_A22C1AAB5463_INCLUDED__
