//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlRenderer.h
//    Author:      Streamlet
//    Create Time: 2015-06-23
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLRENDERER_H_5080051E_9044_4A42_A5AF_25DE919755E3_INCLUDED__
#define __XLRENDERER_H_5080051E_9044_4A42_A5AF_25DE919755E3_INCLUDED__


#include "../../Meta/xlMetaBase.h"
#include "../../String/xlString.h"
#include "xlGraphics.h"
#include <Windows.h>
#include <gdiplus.h>
#include <d2d1_1.h>
#pragma comment(lib, "gdiplus.lib")

namespace xl
{
    typedef TypeConverter<void *, HBITMAP, Gdiplus::Bitmap *, ID2D1Bitmap *, ID2D1Bitmap1 *> BitmapX;

    struct RenderMethods
    {
        virtual void FillSolidRect(const RectX &rect, const ColorX &color) = 0;
        virtual void DrawText(const xl::String &strText, const RectX &rect, UINT uFormat, const ColorX &color) = 0;
        virtual void DrawImage(BitmapX hBitmap, const RectX &rcDest, const RectX &rcSource, BYTE byAlpha) = 0;
    };

    struct RenderContext : public RenderMethods
    {
        virtual bool Initialize() = 0;
        virtual void Uninitialize() = 0;
        virtual void BeginDraw() = 0;
        virtual void EndDraw() = 0;
    };

    struct Renderer
    {
        virtual xl::String GetName() = 0;
        virtual bool Initialize() = 0;
        virtual void Uninitialize() = 0;
        virtual RenderContext *CreateContext(HWND hWnd) = 0;
        virtual void ReleaseContext(RenderContext *pContext) = 0;
    };

} // namespace xl


#endif // #ifndef __XLRENDERER_H_5080051E_9044_4A42_A5AF_25DE919755E3_INCLUDED__
