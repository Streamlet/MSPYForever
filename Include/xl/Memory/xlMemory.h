//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlMemory.h
//    Author:      Streamlet
//    Create Time: 2011-02-27
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------

#ifndef __XLMEMORY_H_269E94A2_E25E_40CC_A48C_3EA8F354B4BA_INCLUDED__
#define __XLMEMORY_H_269E94A2_E25E_40CC_A48C_3EA8F354B4BA_INCLUDED__


#include "../xlDef.h"

namespace xl
{
    class Memory
    {
    private:
        Memory();

    public:
        static bool IsEqual(const void *pMemory1, const void *pMemory2, size_t cbSize)
        {
            if (pMemory1 == nullptr || pMemory2 == nullptr || cbSize == 0)
            {
                return pMemory1 == pMemory2;
            }

            const unsigned int *pUInt1 = (const unsigned int *)pMemory1;
            const unsigned int *pUInt2 = (const unsigned int *)pMemory2;

            while (cbSize >= 4)
            {
                if (*pUInt1 != *pUInt2)
                {
                    return false;
                }

                cbSize -= 4;
            }

            const unsigned char *pUChar1 = (const unsigned char *)pUInt1;
            const unsigned char *pUChar2 = (const unsigned char *)pUInt2;

            while (cbSize > 0)
            {
                if (*pUChar1 != *pUChar2)
                {
                    return false;
                }

                --cbSize;
            }

            return true;
        }

        static void *Set(void *pMemory, size_t cbSize, unsigned int nValue = 0)
        {
            if (pMemory == nullptr || cbSize == 0)
            {
                return pMemory;
            }

            unsigned int *pUInt = (unsigned int *)pMemory;

            while (cbSize >= 4)
            {
                *pUInt++ = nValue;
                cbSize -= 4;
            }

            unsigned char *pUChar = (unsigned char *)pUInt;

            while (cbSize > 0)
            {
                *pUChar++ = (unsigned char)nValue;
                --cbSize;
            }

            return pMemory;
        }

        static void *Copy(void *pDest, const void *pSource, size_t cbSize)
        {
            if (pDest == nullptr || pSource == nullptr || pDest == pSource || cbSize == 0)
            {
                return pDest;
            }

            unsigned int *pUIntDest = (unsigned int *)pDest;
            unsigned int *pUIntSource = (unsigned int *)pSource;

            while (cbSize >= 4)
            {
                *pUIntDest++ = *pUIntSource++;
                cbSize -= 4;
            }

            unsigned char *pUCharDest = (unsigned char *)pUIntDest;
            unsigned char *pUCharSource = (unsigned char *)pUIntSource;

            while (cbSize > 0)
            {
                *pUCharDest++ = *pUCharSource++;
                --cbSize;                
            }

            return pDest;
        }

        static void *Move(void *pDest, const void *pSource, size_t cbSize)
        {
            if (pDest == nullptr || pSource == nullptr || pDest == pSource || cbSize == 0)
            {
                return pDest;
            }

            if (pDest < pSource)
            {
                unsigned int *pUIntDest = (unsigned int *)pDest;
                unsigned int *pUIntSource = (unsigned int *)pSource;

                while (cbSize >= 4)
                {
                    *pUIntDest++ = *pUIntSource++;
                    cbSize -= 4;
                }

                unsigned char *pUCharDest = (unsigned char *)pUIntDest;
                unsigned char *pUCharSource = (unsigned char *)pUIntSource;

                while (cbSize > 0)
                {
                    *pUCharDest++ = *pUCharSource++;
                    --cbSize;                
                }
            }
            else
            {
                unsigned int *pUIntDest = (unsigned int *)((unsigned char *)pDest + cbSize );
                unsigned int *pUIntSource = (unsigned int *)((unsigned char *)pSource + cbSize);

                while (cbSize >= 4)
                {
                    *--pUIntDest = *--pUIntSource;
                    cbSize -= 4;
                }

                unsigned char *pUCharDest = (unsigned char *)pUIntDest;
                unsigned char *pUCharSource = (unsigned char *)pUIntSource;

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
            Set(&tVar, sizeof(T));
        }

#if defined(_MSC_VER) && (_MSC_VER >= 1600)

        template <typename T>
        static T &&ElementMove(T &&t)
        {
            return t;
        }

#else

        template <typename T>
        static T &ElementMove(T &t)
        {
            return t;
        }

#endif

        template <typename T>
        static void ElementSwap(T &t1, T &t2)
        {
            T t(ElementMove(t1));
            t1 = ElementMove(t2);
            t2 = ElementMove(t);
        }
    };

} // namespace xl

#endif // #ifndef __XLMEMORY_H_269E94A2_E25E_40CC_A48C_3EA8F354B4BA_INCLUDED__
