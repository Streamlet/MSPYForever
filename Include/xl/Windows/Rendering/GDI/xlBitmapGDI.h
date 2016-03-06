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


#include "../../../Common/Meta/xlNonCopyable.h"
#include "../../../Common/Memory/xlSmartPtr.h"
#include "../xlBitmapDef.h"
#include "../GDIPlus/xlBitmapGDIPlus.h"

namespace xl
{
    namespace Windows
    {
        class BitmapGDI : public BitmapX, public NonCopyable
        {
        public:
            BitmapGDI() : m_hBitmap(nullptr)
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
                Release();

                m_hBitmap = CreateBitmap(iWidth, iHeight, nullptr);

                return m_hBitmap != nullptr;
            }

            bool LoadFromMemory(const void *pData, size_t cbSize)
            {
                Release();

                BitmapGDIPlus bmp;

                if (!bmp.LoadFromMemory(pData, cbSize))
                {
                    return false;
                }

                m_hBitmap = LoadFromGDIPlus(bmp);

                return m_hBitmap != nullptr;
            }

            bool LoadFromFile(const String &strFileName)
            {
                Release();

                BitmapGDIPlus bmp;

                if (!bmp.LoadFromFile(strFileName))
                {
                    return false;
                }

                m_hBitmap = LoadFromGDIPlus(bmp);

                return m_hBitmap != nullptr;
            }

            void *SaveToMemory(size_t &cbSize) const
            {
                SharedPtr<BitmapGDIPlus> spBmp = SaveToGDIPlus(m_hBitmap);

                if (spBmp == nullptr)
                {
                    return nullptr;
                }

                return spBmp->SaveToMemory(cbSize);
            }

            bool SaveToFile(const String &strFileName) const
            {
                SharedPtr<BitmapGDIPlus> spBmp = SaveToGDIPlus(m_hBitmap);

                if (spBmp == nullptr)
                {
                    return nullptr;
                }

                return spBmp->SaveToFile(strFileName);
            }

            SizeX GetSize() const
            {
                if (m_hBitmap == nullptr)
                {
                    return SizeX();
                }

                BITMAP bmp = {};

                if (GetObject(m_hBitmap, sizeof(bmp), &bmp) == 0)
                {
                    return SizeX();
                }

                return SizeX(bmp.bmWidth, bmp.bmHeight);
            }

            ColorX *Lock(BitmapLockFlag eFlag)
            {
                if (m_hBitmap == nullptr)
                {
                    return nullptr;
                }

                BITMAP bmp = {};

                if (GetObject(m_hBitmap, sizeof(bmp), &bmp) == 0)
                {
                    return nullptr;
                }

                return (ColorX *)bmp.bmBits;
            }

            void Unlock()
            {

            }

            void Release()
            {
                Unlock();

                if (m_hBitmap != nullptr)
                {
                    DeleteObject(m_hBitmap);
                    m_hBitmap = nullptr;
                }
            }

            static HBITMAP CreateBitmap(int iWidth, int iHeight, LPVOID *ppvBits)
            {
                BITMAPINFO bmp = {};
                bmp.bmiHeader.biSize = sizeof(BITMAPINFO);
                bmp.bmiHeader.biWidth = iWidth;
                bmp.bmiHeader.biHeight = -iHeight;
                bmp.bmiHeader.biPlanes = 1;
                bmp.bmiHeader.biBitCount = 32;
                bmp.bmiHeader.biCompression = BI_RGB;

                HWND hWnd = GetDesktopWindow();
                HDC hDC = GetDC(hWnd);
                HBITMAP hBitmap = CreateDIBSection(hDC, &bmp, DIB_RGB_COLORS, ppvBits, nullptr, 0);
                ReleaseDC(hWnd, hDC);

                return hBitmap;
            }

            static HBITMAP LoadFromGDIPlus(BitmapGDIPlus &bmp)
            {
                SizeX sz = bmp.GetSize();
                ColorX *pSrc = bmp.Lock(BitmapLockFlag_Read);

                if (sz.Width() == 0 || sz.Height() == 0 || pSrc == nullptr)
                {
                    return false;
                }

                ColorX *pDest = nullptr;
                HBITMAP hBitmap = CreateBitmap(sz.Width(), sz.Height(), (LPVOID *)&pDest);

                if (hBitmap == nullptr)
                {
                    return false;
                }

                for (int i = 0; i < sz.Width() * sz.Height(); ++i)
                {
                    pDest[i] = pSrc[i];
                }

                bmp.Unlock();

                return hBitmap;
            }

            static BitmapGDIPlus *SaveToGDIPlus(HBITMAP hBitmap)
            {
                BITMAP bmp = {};

                if (GetObject(hBitmap, sizeof(bmp), &bmp) == 0 ||
                    bmp.bmWidth == 0 || bmp.bmHeight == 0 || bmp.bmBitsPixel != 32 || bmp.bmBits == nullptr)
                {
                    return nullptr;
                }

                ColorX *pSrc = (ColorX *)bmp.bmBits;

                BitmapGDIPlus *pNew = new BitmapGDIPlus;

                if (!pNew->CreateBlank(bmp.bmWidth, bmp.bmHeight))
                {
                    delete pNew;
                    return nullptr;
                }

                ColorX *pDest = pNew->Lock(BitmapLockFlag_Write);

                if (pDest == nullptr)
                {
                    delete pNew;
                    return nullptr;
                }

                for (int i = 0; i < bmp.bmWidth * bmp.bmHeight; ++i)
                {
                    pDest[i] = pSrc[i];
                }

                return pNew;
            }

        protected:
            HBITMAP m_hBitmap;
        };

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLBITMAPGDI_H_98263866_1B6E_47BF_B731_CB8321F9359C_INCLUDED__
