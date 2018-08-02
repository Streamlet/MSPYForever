//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlGDIPlusImports.h
//    Author:      Streamlet
//    Create Time: 2015-07-05
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLGDIPLUSIMPORTS_H_ED4930F0_F0E6_4A6E_9B17_5D858632EF53_INCLUDED__
#define __XLGDIPLUSIMPORTS_H_ED4930F0_F0E6_4A6E_9B17_5D858632EF53_INCLUDED__


#include "../../xlDllHelper.h"
#include <Gdiplus.h>

namespace xl
{
    namespace Windows
    {
#define _GdiplusStartup(...)                DllHelper<Gdiplus::Status (WINAPI *)(ULONG_PTR *, const Gdiplus::GdiplusStartupInput *, Gdiplus::GdiplusStartupOutput *)>::CallFunction(L"Gdiplus.dll", "GdiplusStartup", __VA_ARGS__)
#define _GdiplusShutdown(...)               DllHelper<VOID (WINAPI *)(ULONG_PTR)>::CallFunction(L"Gdiplus.dll", "GdiplusShutdown", __VA_ARGS__)
#define _GdipCreateBitmapFromScan0(...)     DllHelper<Gdiplus::GpStatus (WINGDIPAPI *)(INT, INT, INT, Gdiplus::PixelFormat, BYTE *, Gdiplus::GpBitmap **)>::CallFunction(L"Gdiplus.dll", "GdipCreateBitmapFromScan0", __VA_ARGS__)
#define _GdipCreateBitmapFromStream(...)    DllHelper<Gdiplus::GpStatus (WINGDIPAPI *)(IStream *, Gdiplus::GpBitmap **)>::CallFunction(L"Gdiplus.dll", "GdipCreateBitmapFromStream", __VA_ARGS__)
#define _GdipCreateBitmapFromFile(...)      DllHelper<Gdiplus::GpStatus (WINGDIPAPI *)(GDIPCONST WCHAR *, Gdiplus::GpBitmap **)>::CallFunction(L"Gdiplus.dll", "GdipCreateBitmapFromFile", __VA_ARGS__)
#define _GdipSaveImageToStream(...)         DllHelper<Gdiplus::GpStatus (WINGDIPAPI *)(Gdiplus::GpImage *, IStream *, GDIPCONST CLSID *, GDIPCONST Gdiplus::EncoderParameters *)>::CallFunction(L"Gdiplus.dll", "GdipSaveImageToStream", __VA_ARGS__)
#define _GdipSaveImageToFile(...)           DllHelper<Gdiplus::GpStatus (WINGDIPAPI *)(Gdiplus::GpImage *, GDIPCONST WCHAR *, GDIPCONST CLSID *, GDIPCONST Gdiplus::EncoderParameters *)>::CallFunction(L"Gdiplus.dll", "GdipSaveImageToFile", __VA_ARGS__)
#define _GdipBitmapLockBits(...)            DllHelper<Gdiplus::GpStatus (WINGDIPAPI *)(Gdiplus::GpBitmap *, GDIPCONST Gdiplus::GpRect *, UINT, Gdiplus::PixelFormat, Gdiplus::BitmapData *)>::CallFunction(L"Gdiplus.dll", "GdipBitmapLockBits", __VA_ARGS__)
#define _GdipBitmapUnlockBits(...)          DllHelper<Gdiplus::GpStatus (WINGDIPAPI *)(Gdiplus::GpBitmap *, Gdiplus::BitmapData *)>::CallFunction(L"Gdiplus.dll", "GdipBitmapUnlockBits", __VA_ARGS__)
#define _GdipGetImageDecodersSize(...)      DllHelper<Gdiplus::GpStatus (WINGDIPAPI *)(UINT *, UINT *)>::CallFunction(L"Gdiplus.dll", "GdipGetImageDecodersSize", __VA_ARGS__)
#define _GdipGetImageDecoders(...)          DllHelper<Gdiplus::GpStatus (WINGDIPAPI *)(UINT, UINT, Gdiplus::ImageCodecInfo *)>::CallFunction(L"Gdiplus.dll", "GdipGetImageDecoders", __VA_ARGS__)
#define _GdipGetImageWidth(...)             DllHelper<Gdiplus::GpStatus (WINGDIPAPI *)(Gdiplus::GpImage *, UINT *)>::CallFunction(L"Gdiplus.dll", "GdipGetImageWidth", __VA_ARGS__)
#define _GdipGetImageHeight(...)            DllHelper<Gdiplus::GpStatus (WINGDIPAPI *)(Gdiplus::GpImage *, UINT *)>::CallFunction(L"Gdiplus.dll", "GdipGetImageHeight", __VA_ARGS__)
#define _GdipDisposeImage(...)              DllHelper<Gdiplus::GpStatus (WINGDIPAPI *)(Gdiplus::GpImage *)>::CallFunction(L"Gdiplus.dll", "GdipDisposeImage", __VA_ARGS__)

#define _EncoderQuality                     DllHelper<GUID>::GetVariable(L"Gdiplus.dll", "EncoderQuality")

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLGDIPLUSIMPORTS_H_ED4930F0_F0E6_4A6E_9B17_5D858632EF53_INCLUDED__
