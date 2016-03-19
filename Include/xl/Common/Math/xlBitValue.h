//------------------------------------------------------------------------------
//
//    Copyright (C) YourCompany. All rights reserved.
//
//    File Name:   xlBitValue.h
//    Author:      YourName
//    Create Time: 2016-02-26
//    Description: 
//
//------------------------------------------------------------------------------

#ifndef __XLBITVALUE_H_2C0491F2_B7F9_41A2_8E10_26C71C5CA0DB_INCLUDED__
#define __XLBITVALUE_H_2C0491F2_B7F9_41A2_8E10_26C71C5CA0DB_INCLUDED__


#include "../../xlDef.h"
#include "../Meta/xlAssert.h"
#include "../Meta/xlTypeTraits.h"
#include "../Math/xlMathBase.h"

namespace xl
{
    namespace BitValue
    {
        template <typename R, typename T>
        inline R EvalT(const T &tData, size_t nOffset, size_t nBits)
        {
            XL_ASSERT(nOffset < sizeof(T) * 8);
            XL_ASSERT(nOffset + nBits <= sizeof(T) * 8);
            XL_ASSERT(nBits > 0 && nBits <= sizeof(R) * 8);

            return (R)(((SizeToUnignedIntType<sizeof(T)>::Type)tData << nOffset) >> (sizeof(T) * 8 - nBits));
        }

#ifdef __XL_CPP11
        template <typename R = unsigned int, typename T = unsigned int>
        inline R Eval(const T &tData, size_t nOffset, size_t nBits)
        {
            return EvalT<R, T>(tData, nOffset, nBits);
        }
#else
        inline unsigned int Eval(unsigned char tData, size_t nOffset, size_t nBits)
        {
            return EvalT<unsigned int, unsigned char>(tData, nOffset, nBits);
        }
        inline unsigned int Eval(unsigned int tData, size_t nOffset, size_t nBits)
        {
            return EvalT<unsigned int, unsigned int>(tData, nOffset, nBits);
        }
        inline unsigned int Eval(int tData, size_t nOffset, size_t nBits)
        {
            return EvalT<unsigned int, int>(tData, nOffset, nBits);
        }
#endif

        template <typename R, typename T>
        inline R EvalT(const T *pData, size_t nOffset, size_t nBits)
        {
            XL_ASSERT(nBits > 0 && nBits <= sizeof(R) * 8);

            if (nOffset + nBits <= sizeof(T) * 8)
            {
                return EvalT<R, T>(pData[0], nOffset, nBits);
            }

            while (nOffset > sizeof(T) * 8)
            {
                ++pData;
                nOffset -= sizeof(T) * 8;
            }

            R r = 0;

            while (nBits > 0)
            {
                size_t n = Min(sizeof(T) * 8 - nOffset, nBits);
                r = (r << n) | (((SizeToUnignedIntType<sizeof(T)>::Type)*pData++ << nOffset) >> (sizeof(T) * 8 - n));
                nBits -= n;
                nOffset = 0;
            }

            return r;
        }

#ifdef __XL_CPP11
        template <typename R = unsigned int, typename T = unsigned int>
        inline R Eval(const T *pData, size_t nOffset, size_t nBits)
        {
            return EvalT<R, T>(pData, nOffset, nBits);
        }
#else
        inline unsigned int Eval(const unsigned char *pData, size_t nOffset, size_t nBits)
        {
            return EvalT<unsigned int, unsigned char>(pData, nOffset, nBits);
        }
        inline unsigned int Eval(const unsigned int *pData, size_t nOffset, size_t nBits)
        {
            return EvalT<unsigned int, unsigned int>(pData, nOffset, nBits);
        }
        inline unsigned int Eval(const int *pData, size_t nOffset, size_t nBits)
        {
            return EvalT<unsigned int, int>(pData, nOffset, nBits);
        }
#endif

    }
} // namespace xl

#endif // #ifndef __XLBITVALUE_H_2C0491F2_B7F9_41A2_8E10_26C71C5CA0DB_INCLUDED__
