//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlMemory.h
//    Author:      Streamlet
//    Create Time: 2011-02-27
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLMEMORY_H_269E94A2_E25E_40CC_A48C_3EA8F354B4BA_INCLUDED__
#define __XLMEMORY_H_269E94A2_E25E_40CC_A48C_3EA8F354B4BA_INCLUDED__


#include <memory.h>
#include "../Meta/xlTypeTraits.h"
#include "../Meta/xlEnableIf.h"

namespace xl
{
    namespace Memory
    {
        __forceinline int Compare(const void *pBuf1, const void *pBuf2, size_t cbSize)
        {
            return memcmp(pBuf1, pBuf2, cbSize);
        }

        __forceinline void *Set(void *pDst, int byVal, size_t cbSize)
        {
            return memset(pDst, byVal, cbSize);
        }

        __forceinline void *Copy(void *pDst, const void *pSrc, size_t cbSize)
        {
            return memmove(pDst, pSrc, cbSize);
        }

        template <typename T>
        inline void Zero(T &tVar)
        {
            Set(&tVar, 0, sizeof(T));
        }

        template <typename T>
        inline typename EnableIf<(StdTypeDetect<T>::IsStdType || PtrTraits<T>::IsPtr) && !ArrayTraits<T>::IsArray, T>::Type *
            CopyT(T *pDst, const T *pSrc, size_t nCount)
        {
            return (T *)Copy((void *)pDst, (const void *)pSrc, sizeof(T) * nCount);
        }

        template <typename T>
        inline typename EnableIf<(!StdTypeDetect<T>::IsStdType && !PtrTraits<T>::IsPtr) && !ArrayTraits<T>::IsArray, T>::Type *
            CopyT(T *pDst, const T *pSrc, size_t nCount)
        {
            for (size_t i = 0; i < nCount; ++i)
            {
                pDst[i] = Move(pSrc[i]);
            }

            return pDst;
        }

        template <typename T>
        inline typename RemoveRef<T>::Type &&Move(T &&t)
        {
            return (typename RemoveRef<T>::Type &&)t;
        }

        template <typename T>
        inline void Swap(T &t1, T &t2)
        {
            T t(Move(t1));
            t1 = Move(t2);
            t2 = Move(t);
        }
    };

} // namespace xl

#endif // #ifndef __XLMEMORY_H_269E94A2_E25E_40CC_A48C_3EA8F354B4BA_INCLUDED__
