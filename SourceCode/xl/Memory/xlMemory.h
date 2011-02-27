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


#include <xl/xlDef.h>

namespace xl
{
    class Memory
    {
    private:
        Memory();

    public:
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
    };

} // namespace xl

#endif // #ifndef __XLMEMORY_H_269E94A2_E25E_40CC_A48C_3EA8F354B4BA_INCLUDED__
