//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlBitmapGDIPlus.h
//    Author:      Streamlet
//    Create Time: 2015-07-05
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLBITMAPGDIPLUS_H_944EFD32_0936_4161_80FE_FE147D62FA2E_INCLUDED__
#define __XLBITMAPGDIPLUS_H_944EFD32_0936_4161_80FE_FE147D62FA2E_INCLUDED__


#include "../../../Common/Meta/xlNonCopyable.h"
#include "../../../Common/Meta/xlScopeExit.h"
#include "../../COM/xlComPtr.h"
#include "../../File/xlPath.h"
#include "../xlBitmapDef.h"
#include "xlGDIPlusUtility.h"

namespace xl
{
    namespace Windows
    {
        class BitmapGDIPlus : public BitmapX, public NonCopyable
        {
        public:
            BitmapGDIPlus() : m_pBitmap(nullptr), m_pLastLock(nullptr)
            {

            }

            ~BitmapGDIPlus()
            {
                Release();
            }

            BitmapType GetType() const
            {
                return BitmapType_GDIPLUS;
            }

            bool CreateBlank(int iWidth, int iHeight)
            {
                Release();

                if (_GdipCreateBitmapFromScan0(iWidth, iHeight, 0, PixelFormat32bppPARGB, NULL, &m_pBitmap) != Gdiplus::Ok)
                {
                    return false;
                }

                return m_pBitmap != nullptr;
            }

            bool LoadFromMemory(const void *lpData, size_t cbSize)
            {
                Release();

                m_pBitmap = CreateFromMemory(lpData, cbSize);

                return m_pBitmap != nullptr;
            }

            bool LoadFromFile(const String &strFileName)
            {
                Release();

                if (_GdipCreateBitmapFromFile(strFileName, &m_pBitmap) != Gdiplus::Ok)
                {
                    return false;
                }

                return m_pBitmap != nullptr;
            }

            void *SaveToMemory(size_t &cbSize) const
            {
                return SaveToMemory(m_pBitmap, cbSize);
            }

            bool SaveToFile(const String &strFileName) const
            {
                return SaveToFile(m_pBitmap, strFileName);
            }

            SizeX GetSize() const
            {
                if (m_pBitmap == nullptr)
                {
                    return SizeX();
                }

                UINT uWidth = 0;
                UINT uHeight = 0;

                if (_GdipGetImageWidth(m_pBitmap, &uWidth) != Gdiplus::Ok ||
                    _GdipGetImageHeight(m_pBitmap, &uHeight) != Gdiplus::Ok)
                {
                    return SizeX();
                }

                return SizeX(uWidth, uHeight);
            }

            ColorX *Lock(BitmapLockFlag eFlag)
            {
                if (m_pBitmap == nullptr)
                {
                    return nullptr;
                }

                if (m_pLastLock != nullptr)
                {
                    return nullptr;
                }

                UINT uflags = 0;

                if ((eFlag & BitmapLockFlag_Read) != 0)
                {
                    uflags |= Gdiplus::ImageLockModeRead;
                }

                if ((eFlag & BitmapLockFlag_Read) != 0)
                {
                    uflags |= Gdiplus::ImageLockModeWrite;
                }

                m_pLastLock = new Gdiplus::BitmapData;

                if (_GdipBitmapLockBits(m_pBitmap, nullptr, uflags, PixelFormat32bppPARGB, m_pLastLock) != Gdiplus::Ok)
                {
                    return nullptr;
                }

                return (ColorX *)m_pLastLock->Scan0;
            }

            void Unlock()
            {
                if (m_pBitmap == nullptr)
                {
                    return;
                }

                if (m_pLastLock == nullptr)
                {
                    return;
                }

                _GdipBitmapUnlockBits(m_pBitmap, m_pLastLock);
            }

            void Release()
            {
                Unlock();

                if (m_pBitmap != nullptr)
                {
                    _GdipDisposeImage(m_pBitmap);
                    m_pBitmap = nullptr;
                }
            }

            static Gdiplus::GpBitmap *CreateFromMemory(const void *pData, size_t cbSize)
            {
                HGLOBAL hGlobal = ::GlobalAlloc(GMEM_MOVEABLE | GMEM_NODISCARD, cbSize);

                if (hGlobal == nullptr)
                {
                    return nullptr;
                }

                {
                    LPVOID lpBuffer = GlobalLock(hGlobal);

                    if (lpBuffer == nullptr)
                    {
                        return nullptr;
                    }

                    XL_ON_BLOCK_EXIT(GlobalUnlock, hGlobal);
                    CopyMemory(lpBuffer, pData, cbSize);
                }

                ComPtr<IStream> spStream = nullptr;
                HRESULT hr = CreateStreamOnHGlobal(hGlobal, TRUE, &spStream);

                if (FAILED(hr))
                {
                    return nullptr;
                }

                Gdiplus::GpBitmap *pBitmap = nullptr;

                if (_GdipCreateBitmapFromStream(spStream, &pBitmap) != Gdiplus::Ok)
                {
                    return nullptr;
                }

                return pBitmap;
            }

            static bool GetEncoderByFileName(const String &strFileName, CLSID *pClsid)
            {
                GDIPlusStartupShutDown gdiplus;
                UINT nEncoders = 0;
                UINT nBytes = 0;

                String strExtName = Path::GetFileExtName(strFileName);
                strExtName.MakeLower();
                strExtName.AppendFront(L'.');
                strExtName.AppendBack(L';');

                if (_GdipGetImageDecodersSize(&nEncoders, &nBytes) != Gdiplus::Ok)
                {
                    return false;
                }

                SharedArray<BYTE> spBuffer = new BYTE[nBytes];
                Gdiplus::ImageCodecInfo *pEncoders = (Gdiplus::ImageCodecInfo*)spBuffer.RawPointer();

                if (_GdipGetImageDecoders(nEncoders, nBytes, pEncoders) != Gdiplus::Ok)
                {
                    return false;
                }

                for (UINT i = 0; i < nEncoders; i++)
                {
                    xl::String strExtSet = pEncoders[i].FilenameExtension;
                    strExtSet.MakeLower();
                    strExtSet.AppendBack(L';');

                    if (strExtSet.IndexOf(strExtName) >= 0)
                    {
                        *pClsid = pEncoders[i].Clsid;
                        return true;
                    }
                }

                return false;
            }

            static bool SaveToFile(Gdiplus::GpBitmap *pBitmap, const String &strFileName)
            {
                GDIPlusStartupShutDown gdiplus;

                CLSID clsid = {};

                if (!GetEncoderByFileName(strFileName, &clsid))
                {
                    return false;
                }

                long lQuality = 100;
                Gdiplus::EncoderParameters ep = { 1, { _EncoderQuality, 1, Gdiplus::EncoderParameterValueTypeLong, (void*)&lQuality } };

                if (_GdipSaveImageToFile(pBitmap, strFileName, &clsid, &ep) != Gdiplus::Ok)
                {
                    return false;
                }

                return true;
            }

            static void *SaveToMemory(Gdiplus::GpBitmap *pBitmap, size_t &cbSize)
            {
                GDIPlusStartupShutDown gdiplus;

                CLSID clsid = {};

                if (!GetEncoderByFileName(L".bmp", &clsid))
                {
                    return false;
                }

                ComPtr<IStream> spStream = nullptr;
                HRESULT hr = CreateStreamOnHGlobal(nullptr, FALSE, &spStream);

                if (FAILED(hr))
                {
                    return false;
                }

                long lQuality = 100;
                Gdiplus::EncoderParameters ep = { 1, { _EncoderQuality, 1, Gdiplus::EncoderParameterValueTypeLong, (void*)&lQuality } };

                if (_GdipSaveImageToStream(pBitmap, spStream, &clsid, &ep) != Gdiplus::Ok)
                {
                    return false;
                }

                STATSTG stat = {};
                hr = spStream->Stat(&stat, STATFLAG_NONAME);

                if (FAILED(hr))
                {
                    return false;
                }

                if (stat.cbSize.HighPart > 0)
                {
                    return false;
                }

                cbSize = (size_t)stat.cbSize.LowPart;
                LARGE_INTEGER liStart = {};

                hr = spStream->Seek(liStart, STREAM_SEEK_SET, nullptr);

                if (FAILED(hr))
                {
                    return false;
                }

                LPBYTE lpBuffer = new BYTE[cbSize];
                hr = spStream->Read(lpBuffer, (ULONG)cbSize, nullptr);

                if (FAILED(hr))
                {
                    delete[] lpBuffer;
                    return false;
                }

                return lpBuffer;
            }

        protected:
            GDIPlusStartupShutDown m_Gdiplus;
            Gdiplus::GpBitmap *m_pBitmap;
            Gdiplus::BitmapData *m_pLastLock;
        };

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLBITMAPGDIPLUS_H_944EFD32_0936_4161_80FE_FE147D62FA2E_INCLUDED__
