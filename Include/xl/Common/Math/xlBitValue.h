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


#include "../Meta/xlAssert.h"
#include "../Meta/xlTypeTraits.h"
#include "../Math/xlMathBase.h"

namespace xl
{
    namespace BitValue
    {
        template <typename R = unsigned int, typename T = unsigned int>
        inline R Eval(const T &tData, size_t nOffset, size_t nBits)
        {
            XL_ASSERT(nOffset < sizeof(T) * 8);
            XL_ASSERT(nOffset + nBits <= sizeof(T) * 8);
            XL_ASSERT(nBits > 0 && nBits <= sizeof(R) * 8);

            return (R)(((SizeToUnignedIntType<sizeof(T)>::Type)tData << nOffset) >> (sizeof(T) * 8 - nBits));
        }

        template <typename R = unsigned int, typename T = unsigned int>
        inline R Eval(const T *pData, size_t nOffset, size_t nBits)
        {
            XL_ASSERT(nOffset < sizeof(T) * 8);
            XL_ASSERT(nBits > 0 && nBits <= sizeof(R) * 8);

            if (nOffset + nBits <= sizeof(T) * 8)
            {
                return Eval<R, T>(pData[0], nOffset, nBits);
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


    }
} // namespace xl

#endif // #ifndef __XLBITVALUE_H_2C0491F2_B7F9_41A2_8E10_26C71C5CA0DB_INCLUDED__
