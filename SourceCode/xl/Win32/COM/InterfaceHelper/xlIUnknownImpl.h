//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlIUnknownImpl.h
//    Author:      Streamlet
//    Create Time: 2012-09-01
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLIUNKNOWNIMPL_H_02B7268E_6F8B_47E7_BF44_1EDB0C545C42_INCLUDED__
#define __XLIUNKNOWNIMPL_H_02B7268E_6F8B_47E7_BF44_1EDB0C545C42_INCLUDED__


#include <Unknwn.h>
#include <Windows.h>
#include <xl/Win32/COM/xlComDef.h>

namespace xl
{
    template <typename T = IUnknown>
    class IUnknownImpl : public T
    {
    public:
        IUnknownImpl() : m_nRefCount(0)
        {
            AddRef();
        }

        ~IUnknownImpl()
        {
        
        }

    public: // IUnknown Methods
        XL_COM_INTERFACE_BEGIN()
            XL_COM_INTERFACE(IUnknown)
        XL_COM_INTERFACE_END()

        ULONG STDMETHODCALLTYPE AddRef()
        {
            return (ULONG)InterlockedIncrement(&m_nRefCount);
        }

        ULONG STDMETHODCALLTYPE Release()
        {
            LONG nRefCount = InterlockedDecrement(&m_nRefCount);

            if (nRefCount <= 0)
            {
                delete this;
            }

            return (ULONG)nRefCount;
        }

    private:
        LONG m_nRefCount;
    };

} // namespace xl

#endif // #ifndef __XLIUNKNOWNIMPL_H_02B7268E_6F8B_47E7_BF44_1EDB0C545C42_INCLUDED__
