//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlTls.h
//    Author:      Streamlet
//    Create Time: 2010-12-20
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLTLS_H_227ED6E5_E819_4DAF_8ACB_51EBFA717AFC_INCLUDED__
#define __XLTLS_H_227ED6E5_E819_4DAF_8ACB_51EBFA717AFC_INCLUDED__


#include "../../Common/Meta/xlNonCopyable.h"
#include "../xlWin32Ver.h"

namespace xl
{
    namespace Windows
    {
        class Tls : public NonCopyable
        {
        public:
            Tls() :
                m_dwTlsIndex(TLS_OUT_OF_INDEXES)
            {
                m_dwTlsIndex = TlsAlloc();
            }

            ~Tls()
            {
                if (m_dwTlsIndex != TLS_OUT_OF_INDEXES)
                {
                    TlsFree(m_dwTlsIndex);
                    m_dwTlsIndex = TLS_OUT_OF_INDEXES;
                }
            }

        public:
            BOOL Set(LPVOID lpValue)
            {
                if (m_dwTlsIndex == TLS_OUT_OF_INDEXES)
                {
                    return FALSE;
                }

                return TlsSetValue(m_dwTlsIndex, lpValue);
            }

            LPVOID Get()
            {
                if (m_dwTlsIndex == TLS_OUT_OF_INDEXES)
                {
                    return NULL;
                }

                return TlsGetValue(m_dwTlsIndex);
            }

        private:
            DWORD m_dwTlsIndex;
        };

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLTLS_H_227ED6E5_E819_4DAF_8ACB_51EBFA717AFC_INCLUDED__
