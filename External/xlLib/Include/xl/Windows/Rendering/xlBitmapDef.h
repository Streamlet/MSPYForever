//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlBitmapDef.h
//    Author:      Streamlet
//    Create Time: 2015-07-05
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLBITMAPDEF_H_727259A4_E1C1_4ED9_9CF2_693486E201B2_INCLUDED__
#define __XLBITMAPDEF_H_727259A4_E1C1_4ED9_9CF2_693486E201B2_INCLUDED__


#include "../../Common/String/xlString.h"
#include "xlGraphics.h"

namespace xl
{
    namespace Windows
    {
        enum BitmapType
        {
            BitmapType_GDI,
            BitmapType_GDIPLUS,
            BitmapType_D2D1,
            BitmapType_D2D1Point1,
        };

        enum BitmapLockFlag
        {
            BitmapLockFlag_Read = 0x01,
            BitmapLockFlag_Write = 0x02,
            BitmapLockFlag_ReadWrite = 0x03,
        };

        struct BitmapX
        {
            virtual BitmapType GetType() const = 0;
            virtual bool CreateBlank(int iWidth, int iHeight) = 0;
            virtual bool LoadFromMemory(const void *pData, size_t cbSize) = 0;
            virtual bool LoadFromFile(const String &strFileName) = 0;
            virtual void *SaveToMemory(size_t &cbSize) const = 0;
            virtual bool SaveToFile(const String &strFileName) const = 0;
            virtual SizeX GetSize() const = 0;
            virtual ColorX *Lock(BitmapLockFlag eFlag) = 0;
            virtual void Unlock() = 0;
        };

    } // namespace Windows
}   // namespace xl

#endif // #ifndef __XLBITMAPDEF_H_727259A4_E1C1_4ED9_9CF2_693486E201B2_INCLUDED__
