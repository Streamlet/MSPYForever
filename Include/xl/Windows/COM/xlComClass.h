//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlComClass.h
//    Author:      Streamlet
//    Create Time: 2012-09-16
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLCOMCLASS_H_EE07A885_D300_4CA6_81BE_DDFD9296BABE_INCLUDED__
#define __XLCOMCLASS_H_EE07A885_D300_4CA6_81BE_DDFD9296BABE_INCLUDED__


#include "../xlWin32Ver.h"
#include "xlComDef.h"

namespace xl
{
    namespace Windows
    {
        template <typename T>
        class ComClass
        {
        public:
            ComClass(bool bAddObjRefCount = true) : m_nRefCount(0), m_bAddObjRefCount(bAddObjRefCount)
            {
                if (g_pComModule != nullptr && m_bAddObjRefCount)
                {
                    g_pComModule->ObjectAddRef();
                }
            }

            ~ComClass()
            {
                if (g_pComModule != nullptr && m_bAddObjRefCount)
                {
                    g_pComModule->ObjectRelease();
                }
            }

        public:
            STDMETHODIMP InternalQueryInterface(const InterfaceEntry *pEntries, REFIID riid, LPVOID *ppvObject)
            {
                *ppvObject = nullptr;
                T *pThis = (T *)this;

                IUnknown *pUnknown = (IUnknown *)((INT_PTR)pThis + pEntries->dwOffset);

                if (riid == __uuidof(IUnknown))
                {
                    *ppvObject = pUnknown;
                    pUnknown->AddRef();
                    return S_OK;
                }

                for (const InterfaceEntry *pEntry = pEntries; pEntry->piid != nullptr; ++pEntry)
                {
                    if (riid == *pEntry->piid)
                    {
                        *ppvObject = (IUnknown *)((INT_PTR)pThis + pEntry->dwOffset);
                        pUnknown->AddRef();
                        return S_OK;
                    }
                }

                return E_NOINTERFACE;
            }

            ULONG STDMETHODCALLTYPE InternalAddRef()
            {
                return (ULONG)InterlockedIncrement(&m_nRefCount);
            }

            ULONG STDMETHODCALLTYPE InternalRelease()
            {
                LONG nRefCount = InterlockedDecrement(&m_nRefCount);

                if (nRefCount <= 0)
                {
                    delete (T *)this;
                }

                return (ULONG)nRefCount;
            }

        protected:
            LONG m_nRefCount;
            bool m_bAddObjRefCount;
        };

    } // namespace Windows
} // namespace xl


#endif // #ifndef __XLCOMCLASS_H_EE07A885_D300_4CA6_81BE_DDFD9296BABE_INCLUDED__
