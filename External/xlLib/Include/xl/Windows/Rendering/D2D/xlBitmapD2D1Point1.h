//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlBitmapD2D1Point1.h
//    Author:      Streamlet
//    Create Time: 2015-07-05
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLBITMAPD2D1POINT1_H_F360F84D_C11B_4807_85C5_8C6F760746E7_INCLUDED__
#define __XLBITMAPD2D1POINT1_H_F360F84D_C11B_4807_85C5_8C6F760746E7_INCLUDED__


#include "../../Common/Meta/xlNonCopyable.h"
#include "xlBitmapDef.h"
#include <d2d1_1.h>

namespace xl
{
    namespace Windows
    {
        class BitmapD2D1Point1 : public BitmapX, public NonCopyable
        {
        public:
            BitmapD2D1Point1()
            {

            }

            ~BitmapD2D1Point1()
            {

            }

            BitmapType GetType() const
            {
                return BitmapType_D2D1Point1;
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

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLBITMAPD2D1POINT1_H_F360F84D_C11B_4807_85C5_8C6F760746E7_INCLUDED__
