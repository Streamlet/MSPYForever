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


#include "../../xlDef.h"
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

            BlockType *pUBlock = (BlockType *)pMemory;

            while (cbSize >= sizeof(BlockType))
            {
                *pUBlock++ = nValue;
                cbSize -= sizeof(BlockType);
            }

            unsigned char *pUCharDest = (unsigned char *)pUBlock;
            unsigned char *pUCharSource = (unsigned char *)&nValue;

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
                BlockType *pUBlockDest = (BlockType *)pDest;
                BlockType *pUBlockSource = (BlockType *)pSource;

                while (cbSize >= sizeof(BlockType))
                {
                    *pUBlockDest++ = *pUBlockSource++;
                    cbSize -= sizeof(BlockType);
                }

                unsigned char *pUCharDest = (unsigned char *)pUBlockDest;
                unsigned char *pUCharSource = (unsigned char *)pUBlockSource;

                while (cbSize > 0)
                {
                    *pUCharDest++ = *pUCharSource++;
                    --cbSize;
                }
            }
            else
            {
                BlockType *pUBlockDest = (BlockType *)((unsigned char *)pDest + cbSize);
                BlockType *pUBlockSource = (BlockType *)((unsigned char *)pSource + cbSize);

                while (cbSize >= sizeof(BlockType))
                {
                    *--pUBlockDest = *--pUBlockSource;
                    cbSize -= sizeof(BlockType);
                }

                unsigned char *pUCharDest = (unsigned char *)pUBlockDest;
                unsigned char *pUCharSource = (unsigned char *)pUBlockSource;

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
