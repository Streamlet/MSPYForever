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


#include "../../Common/String/xlString.h"
#include "xlGraphics.h"
#include "xlBitmap.h"
#include <gdiplus.h>
#include <d2d1_1.h>
#pragma comment(lib, "gdiplus.lib")

namespace xl
{
    namespace Windows
    {
        struct RenderMethods
        {
            virtual void Clear(const RectX &rect, const ColorX &color) = 0;
            virtual void DrawPixel(const PointX &rect, const ColorX &color) = 0;
            virtual void DrawLine(const PointX &pt1, const PointX &pt2, const ColorX &color);
            virtual void DrawRect(const RectX &rect, const ColorX &color) = 0;
            virtual void DrawImage(const BitmapX *pBitmap, const RectX &rcDest, const RectX &rcSource, BYTE byAlpha) = 0;
            virtual void DrawText(const xl::String &strText, const RectX &rect, UINT uFormat, const ColorX &color) = 0;
        };

        struct RenderContext : public RenderMethods
        {
            virtual bool Initialize() = 0;
            virtual void Uninitialize() = 0;
            virtual void BeginDraw() = 0;
            virtual void EndDraw() = 0;
        };

        enum RendererType
        {
            RendererType_GDI,
            RendererType_GDIPLUS,
            RendererType_D2D1,
            RendererType_D2D1Point1,
        };

        struct Renderer
        {
            virtual RendererType GetType() const = 0;
            virtual bool Initialize() = 0;
            virtual void Uninitialize() = 0;
            virtual BitmapX *CreateBitmap() = 0;
            virtual void ReleaseBitmap() = 0;
            virtual RenderContext *CreateContext(HWND hWnd) = 0;
            virtual void ReleaseContext(RenderContext *pContext) = 0;
        };

    } // namespace Windows
} // namespace xl


#endif // #ifndef __XLRENDERER_H_5080051E_9044_4A42_A5AF_25DE919755E3_INCLUDED__
