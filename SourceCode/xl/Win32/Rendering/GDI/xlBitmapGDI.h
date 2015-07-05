//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlBitmapGDI.h
//    Author:      Streamlet
//    Create Time: 2015-07-05
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLBITMAPGDI_H_98263866_1B6E_47BF_B731_CB8321F9359C_INCLUDED__
#define __XLBITMAPGDI_H_98263866_1B6E_47BF_B731_CB8321F9359C_INCLUDED__


#include "../../Meta/xlUtility.h"
#include "xlBitmapDef.h"
#include <Windows.h>

namespace xl
{
    class BitmapGDI : public BitmapX, public NonCopyable
    {
    public:
        BitmapGDI()
        {

        }

        ~BitmapGDI()
        {

        }

        BitmapType GetType() const
        {
            return BitmapType_GDI;
        }

        bool CreateBlank(int iWidth, int iHeight)
        {
            return false;
        }

        bool LoadFromMemory(const void *pData, size_t cbSize)
        {
            return false;
        }

        bool LoadFromFile(const String &strFileName)
        {
            return false;
        }

        void *SaveToMemory(size_t &cbSize) const
        {
            return nullptr;
        }

        bool SaveToFile(const String &strFileName) const
        {
            return false;
        }

        SizeX GetSize() const
        {
            return SizeX();
        }

        ColorX *Lock(BitmapLockFlag eFlag)
        {
            return nullptr;
        }

        void Unlock()
        {

        }

    };

} // namespace xl

#endif // #ifndef __XLBITMAPGDI_H_98263866_1B6E_47BF_B731_CB8321F9359C_INCLUDED__
