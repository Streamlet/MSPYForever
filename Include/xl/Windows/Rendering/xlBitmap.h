//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlBitmap.h
//    Author:      Streamlet
//    Create Time: 2015-07-04
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLBITMAP_H_BC330422_03BA_4696_B813_3E886CD6A62B_INCLUDED__
#define __XLBITMAP_H_BC330422_03BA_4696_B813_3E886CD6A62B_INCLUDED__


#include "../../Common/Meta/xlNonCopyable.h"
#include "GDI/xlBitmapGDI.h"
#include "GDIPlus/xlBitmapGDIPlus.h"
#include "D2D/xlBitmapD2D1.h"
#include "D2D/xlBitmapD2D1Point1.h"

namespace xl
{
    namespace Windows
    {
        namespace Bitmap
        {
            BitmapX *CreateBitmap(BitmapType eType)
            {
                switch (eType)
                {
                case BitmapType_GDI:
                    return new BitmapGDI;
                case BitmapType_GDIPLUS:
                    return new BitmapGDIPlus;
                case BitmapType_D2D1:
                    return new BitmapD2D1;
                case BitmapType_D2D1Point1:
                    return new BitmapD2D1Point1;
                default:
                    break;
                }

                return nullptr;
            }

            void ReleaseBitmap(BitmapX *pBitmap)
            {
                delete pBitmap;
            }

        } // namespace Bitmap
    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLBITMAP_H_BC330422_03BA_4696_B813_3E886CD6A62B_INCLUDED__
