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


#include "../Meta/xlTypeTraits.h"

namespace xl
{
    namespace Memory
    {
        template <typename BlockType = unsigned int>
        static void *Set(void *pMemory, size_t cbSize, BlockType nValue)
        {
            if (pMemory == nullptr || cbSize == 0)
            {
                return pMemory;
            }

            unsigned char *pUCharDest = (unsigned char *)pMemory;
            unsigned char *pUCharSource = (unsigned char *)&nValue;
            size_t cbBytes = (unsigned int)pUCharDest %  sizeof(BlockType) == 0 ? 0 : sizeof(BlockType) - (unsigned int)pUCharDest %  sizeof(BlockType);

            if (cbBytes > cbSize)
            {
                cbBytes = cbSize;
            }

            for (size_t i = 0; i < cbBytes; ++i)
            {
                *pUCharDest++ = *pUCharSource++;
                --cbSize;
            }

            if (cbBytes > 0)
            {
                size_t nShiftRightBits = cbBytes * 8;
                size_t nShiftLeftBits = (sizeof(BlockType) - cbBytes) * 8;
                BlockType nMask = ~(((BlockType)-1) << nShiftLeftBits);
                nValue = ((nValue >> nShiftRightBits) & nMask) | (nValue << nShiftLeftBits);
            }

            BlockType *pUBlock = (BlockType *)pUCharDest;

            while (cbSize >= sizeof(BlockType))
            {
                *pUBlock++ = nValue;
                cbSize -= sizeof(BlockType);
            }

            pUCharDest = (unsigned char *)pUBlock;
            pUCharSource = (unsigned char *)&nValue;

            while (cbSize > 0)
            {
                *pUCharDest++ = *pUCharSource++;
                --cbSize;
            }

            return pMemory;
        }

        template <typename BlockType = unsigned int>
        static void *Copy(void *pDest, const void *pSource, size_t cbSize)
        {
            if (pDest == nullptr || pSource == nullptr || pDest == pSource || cbSize == 0)
            {
                return pDest;
            }

            if (pDest < pSource)
            {
                unsigned char *pUCharDest = (unsigned char *)pDest;
                unsigned char *pUCharSource = (unsigned char *)pSource;
                size_t cbBytes = (unsigned int)pUCharDest % sizeof(BlockType) == 0 ? 0 : sizeof(BlockType) - (unsigned int)pUCharDest %  sizeof(BlockType);

                if (cbBytes > cbSize)
                {
                    cbBytes = cbSize;
                }

                for (size_t i = 0; i < cbBytes; ++i)
                {
                    *pUCharDest++ = *pUCharSource++;
                    --cbSize;
                }

                BlockType *pUBlockDest = (BlockType *)pUCharDest;
                BlockType *pUBlockSource = (BlockType *)pUCharSource;

                while (cbSize >= sizeof(BlockType))
                {
                    *pUBlockDest++ = *pUBlockSource++;
                    cbSize -= sizeof(BlockType);
                }

                pUCharDest = (unsigned char *)pUBlockDest;
                pUCharSource = (unsigned char *)pUBlockSource;

                while (cbSize > 0)
                {
                    *pUCharDest++ = *pUCharSource++;
                    --cbSize;
                }
            }
            else
            {
                unsigned char *pUCharDest = (unsigned char *)pDest + cbSize;
                unsigned char *pUCharSource = (unsigned char *)pSource + cbSize;
                size_t cbBytes = (unsigned int)pUCharDest %  sizeof(BlockType);

                if (cbBytes > cbSize)
                {
                    cbBytes = cbSize;
                }

                for (size_t i = 0; i < cbBytes; ++i)
                {
                    *--pUCharDest = *--pUCharSource;
                    --cbSize;
                }

                BlockType *pUBlockDest = (BlockType *)pUCharDest;
                BlockType *pUBlockSource = (BlockType *)pUCharSource;

                while (cbSize >= sizeof(BlockType))
                {
                    *--pUBlockDest = *--pUBlockSource;
                    cbSize -= sizeof(BlockType);
                }

                pUCharDest = (unsigned char *)pUBlockDest;
                pUCharSource = (unsigned char *)pUBlockSource;

                while (cbSize > 0)
                {
                    *--pUCharDest = *--pUCharSource;
                    --cbSize;
                }
            }

            return pDest;
        }

        template <typename T>
        static void Zero(T &tVar)
        {
            Set(&tVar, sizeof(T), 0);
        }

        template <typename T>
        static void Copy(T &tDest, T &tSource)
        {
            Copy(&tDest, &tSource, sizeof(T));
        }

        template <typename T>
        static void Copy(T &tDest, const T &tSource)
        {
            Copy(&tDest, &tSource, sizeof(T));
        }

        template <typename T>
        static void Copy(T &tDest, T &&tSource)
        {
            Copy(&tDest, &tSource, sizeof(T));
        }

        template <typename T>
        static void Copy(T &tDest, const T &&tSource)
        {
            Copy(&tDest, &tSource, sizeof(T));
        }

#if defined(_MSC_VER) && (_MSC_VER >= 1600)

        template <typename T>
        static typename RemoveRef<T>::Type &&Move(T &&t)
        {
            return (typename RemoveRef<T>::Type &&)t;
        }

#else

        template <typename T>
        static T &Move(T &t)
        {
            return t;
        }

#endif

        template <typename T>
        static void Swap(T &t1, T &t2)
        {
            T t(Move(t1));
            t1 = Move(t2);
            t2 = Move(t);
        }
    };

} // namespace xl

#endif // #ifndef __XLMEMORY_H_269E94A2_E25E_40CC_A48C_3EA8F354B4BA_INCLUDED__
