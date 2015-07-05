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
#include <Windows.h>

namespace xl
{

#define _GdiplusStartup(...)                DllHelper<Gdiplus::Status (WINAPI *)(ULONG_PTR *, const Gdiplus::GdiplusStartupInput *, Gdiplus::GdiplusStartupOutput *)>::CallFunction(_T("Gdiplus.dll"), "GdiplusStartup", __VA_ARGS__)
#define _GdiplusShutdown(...)               DllHelper<VOID (WINAPI *)(ULONG_PTR)>::CallFunction(_T("Gdiplus.dll"), "GdiplusShutdown", __VA_ARGS__)
#define _GdipCreateBitmapFromScan0(...)     DllHelper<Gdiplus::GpStatus (WINGDIPAPI *)(INT, INT, INT, Gdiplus::PixelFormat, BYTE *, Gdiplus::GpBitmap **)>::CallFunction(_T("Gdiplus.dll"), "GdipCreateBitmapFromScan0", __VA_ARGS__)
#define _GdipCreateBitmapFromStream(...)    DllHelper<Gdiplus::GpStatus (WINGDIPAPI *)(IStream *, Gdiplus::GpBitmap **)>::CallFunction(_T("Gdiplus.dll"), "GdipCreateBitmapFromStream", __VA_ARGS__)
#define _GdipCreateBitmapFromFile(...)      DllHelper<Gdiplus::GpStatus (WINGDIPAPI *)(GDIPCONST WCHAR *, Gdiplus::GpBitmap **)>::CallFunction(_T("Gdiplus.dll"), "GdipCreateBitmapFromFile", __VA_ARGS__)
#define _GdipSaveImageToStream(...)         DllHelper<Gdiplus::GpStatus (WINGDIPAPI *)(Gdiplus::GpImage *, IStream *, GDIPCONST CLSID *, GDIPCONST Gdiplus::EncoderParameters *)>::CallFunction(_T("Gdiplus.dll"), "GdipSaveImageToStream", __VA_ARGS__)
#define _GdipSaveImageToFile(...)           DllHelper<Gdiplus::GpStatus (WINGDIPAPI *)(Gdiplus::GpImage *, GDIPCONST WCHAR *, GDIPCONST CLSID *, GDIPCONST Gdiplus::EncoderParameters *)>::CallFunction(_T("Gdiplus.dll"), "GdipSaveImageToFile", __VA_ARGS__)
#define _GdipBitmapLockBits(...)            DllHelper<Gdiplus::GpStatus (WINGDIPAPI *)(Gdiplus::GpBitmap *, GDIPCONST Gdiplus::GpRect *, UINT, Gdiplus::PixelFormat, Gdiplus::BitmapData *)>::CallFunction(_T("Gdiplus.dll"), "GdipBitmapLockBits", __VA_ARGS__)
#define _GdipBitmapUnlockBits(...)          DllHelper<Gdiplus::GpStatus (WINGDIPAPI *)(Gdiplus::GpBitmap *, Gdiplus::BitmapData *)>::CallFunction(_T("Gdiplus.dll"), "GdipBitmapUnlockBits", __VA_ARGS__)
#define _GdipGetImageDecodersSize(...)      DllHelper<Gdiplus::GpStatus (WINGDIPAPI *)(UINT *, UINT *)>::CallFunction(_T("Gdiplus.dll"), "GdipGetImageDecodersSize", __VA_ARGS__)
#define _GdipGetImageDecoders(...)          DllHelper<Gdiplus::GpStatus (WINGDIPAPI *)(UINT, UINT, Gdiplus::ImageCodecInfo *)>::CallFunction(_T("Gdiplus.dll"), "GdipGetImageDecoders", __VA_ARGS__)
#define _GdipGetImageWidth(...)             DllHelper<Gdiplus::GpStatus (WINGDIPAPI *)(Gdiplus::GpImage *, UINT *)>::CallFunction(_T("Gdiplus.dll"), "GdipGetImageWidth", __VA_ARGS__)
#define _GdipGetImageHeight(...)            DllHelper<Gdiplus::GpStatus (WINGDIPAPI *)(Gdiplus::GpImage *, UINT *)>::CallFunction(_T("Gdiplus.dll"), "GdipGetImageHeight", __VA_ARGS__)
#define _GdipDisposeImage(...)              DllHelper<Gdiplus::GpStatus (WINGDIPAPI *)(Gdiplus::GpImage *)>::CallFunction(_T("Gdiplus.dll"), "GdipDisposeImage", __VA_ARGS__)

#define _EncoderQuality                     DllHelper<GUID>::GetVariable(_T("Gdiplus.dll"), "EncoderQuality")

} // namespace xl

#endif // #ifndef __XLGDIPLUSIMPORTS_H_ED4930F0_F0E6_4A6E_9B17_5D858632EF53_INCLUDED__
