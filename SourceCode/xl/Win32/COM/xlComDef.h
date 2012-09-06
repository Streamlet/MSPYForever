//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlComDef.h
//    Author:      Streamlet
//    Create Time: 2012-09-01
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLCOMDEF_H_4B89206D_F947_4052_B92D_FD7B1E00CB8F_INCLUDED__
#define __XLCOMDEF_H_4B89206D_F947_4052_B92D_FD7B1E00CB8F_INCLUDED__


#include <Windows.h>

namespace xl
{
    struct InterfaceEntry
    {
    	const IID *piid;
        DWORD_PTR dwOffset;
    };

    template <typename T>
    class ComClass
    {
    public:
        ComClass() : m_nRefCount(0)
        {

        }

        ~ComClass()
        {
        
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
    };

} // namespace xl

#endif // #ifndef __XLCOMDEF_H_4B89206D_F947_4052_B92D_FD7B1E00CB8F_INCLUDED__
