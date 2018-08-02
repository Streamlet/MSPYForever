//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlGraphics.h
//    Author:      Streamlet
//    Create Time: 2015-06-24
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLGRAPHICS_H_E294CF1C_2CFD_4AA9_9531_5BEF7AB8677A_INCLUDED__
#define __XLGRAPHICS_H_E294CF1C_2CFD_4AA9_9531_5BEF7AB8677A_INCLUDED__


#include "../../Common/Math/xlMathBase.h"
#include <d2d1.h>
#include <GdiPlus.h>

namespace xl
{
    namespace Windows
    {
        struct SizeX : public xl::Size
        {
            SizeX() : xl::Size()
            {

            }

            template <typename T>
            SizeX(T cx, T cy) : xl::Size(cx, cy)
            {

            }

            SizeX(const SizeX &that) : xl::Size(that)
            {

            }

            SizeX(const SIZE &sz) : xl::Size(sz.cx, sz.cy)
            {

            }

            SizeX(const D2D_SIZE_U &sz) : xl::Size(sz.width, sz.height)
            {

            }

            SizeX(const D2D_SIZE_F &sz) : xl::Size(sz.width, sz.height)
            {

            }

            SizeX(const Gdiplus::Size &sz) : xl::Size(sz.Width, sz.Height)
            {

            }

            SizeX(const Gdiplus::SizeF &sz) : xl::Size(sz.Width, sz.Height)
            {

            }

            operator SIZE() const
            {
                SIZE sz = { (LONG)CX(), (LONG)CY() };
                return sz;
            }

            operator D2D_SIZE_U() const
            {
                D2D_SIZE_U sz = { (UINT32)CX(), (UINT32)CY() };
                return sz;
            }

            operator D2D_SIZE_F() const
            {
                D2D_SIZE_F sz = { (FLOAT)CX(), (FLOAT)CY() };
                return sz;
            }

            operator Gdiplus::Size() const
            {
                return Gdiplus::Size((INT)CX(), (INT)CY());
            }

            operator Gdiplus::SizeF() const
            {
                return Gdiplus::SizeF((Gdiplus::REAL)CX(), (Gdiplus::REAL)CY());
            }
        };

        struct PointX : public xl::Point
        {
            PointX() : xl::Point()
            {

            }

            template <typename T>
            PointX(T cx, T cy) : xl::Point(cx, cy)
            {

            }

            PointX(const PointX &that) : xl::Point(that)
            {

            }

            PointX(const POINT &pt) : xl::Point(pt.x, pt.y)
            {

            }

            PointX(const D2D_POINT_2U &pt) : xl::Point(pt.x, pt.y)
            {

            }

            PointX(const D2D_POINT_2F &pt) : xl::Point(pt.x, pt.y)
            {

            }

            PointX(const Gdiplus::Point &pt) : xl::Point(pt.X, pt.Y)
            {

            }

            PointX(const Gdiplus::PointF &pt) : xl::Point(pt.X, pt.Y)
            {

            }

            operator POINT() const
            {
                POINT pt = { (LONG)X(), (LONG)Y() };
                return pt;
            }

            operator D2D_POINT_2U() const
            {
                D2D_POINT_2U pt = { (UINT32)X(), (UINT32)Y() };
                return pt;
            }

            operator D2D_POINT_2F() const
            {
                D2D_POINT_2F pt = { (FLOAT)X(), (FLOAT)Y() };
                return pt;
            }

            operator Gdiplus::Point() const
            {
                return Gdiplus::Point((INT)X(), (INT)Y());
            }

            operator Gdiplus::PointF() const
            {
                return Gdiplus::PointF((Gdiplus::REAL)X(), (Gdiplus::REAL)Y());
            }
        };

        struct RectX : public xl::Rect
        {
            RectX() : xl::Rect()
            {

            }

            template <typename T>
            RectX(T left, T top, T right, T bottom) : xl::Rect(left, top, right, bottom)
            {

            }

            RectX(const RectX &that) : xl::Rect(that)
            {

            }

            RectX(const RECT &rc) : xl::Rect(rc.left, rc.top, rc.right, rc.bottom)
            {

            }

            RectX(const D2D_RECT_U &rc) : xl::Rect(rc.left, rc.top, rc.right, rc.bottom)
            {

            }

            RectX(const D2D_RECT_F &rc) : xl::Rect(rc.left, rc.top, rc.right, rc.bottom)
            {

            }

            RectX(const Gdiplus::Rect &rc) : xl::Rect(rc.GetLeft(), rc.GetTop(), rc.GetRight(), rc.GetBottom())
            {

            }

            RectX(const Gdiplus::RectF &rc) : xl::Rect(rc.GetLeft(), rc.GetTop(), rc.GetRight(), rc.GetBottom())
            {

            }

            operator RECT() const
            {
                RECT rc = { (LONG)Left(), (LONG)Right(), (LONG)Top(), (LONG)Bottom() };
                return rc;
            }

            operator D2D_RECT_U() const
            {
                D2D_RECT_U rc = { (UINT32)Left(), (UINT32)Right(), (UINT32)Top(), (UINT32)Bottom() };
                return rc;
            }

            operator D2D_RECT_F() const
            {
                D2D_RECT_F rc = { (FLOAT)Left(), (FLOAT)Right(), (FLOAT)Top(), (FLOAT)Bottom() };
                return rc;
            }

            operator Gdiplus::Rect() const
            {
                return Gdiplus::Rect((INT)X(), (INT)Y(), (INT)Width(), (INT)Height());
            }

            operator Gdiplus::RectF() const
            {
                return Gdiplus::RectF((Gdiplus::REAL)X(), (Gdiplus::REAL)Y(), (Gdiplus::REAL)Width(), (Gdiplus::REAL)Height());
            }
        };

        struct ColorX : Color
        {
            ColorX() : Color(0, 0, 0, 0)
            {

            }

            ColorX(DWORD dw0xAARRGGBB) : Color((BYTE)((dw0xAARRGGBB >> 24) & 0xff), (BYTE)((dw0xAARRGGBB >> 16) & 0xff), (BYTE)((dw0xAARRGGBB >> 8) & 0xff), (BYTE)(dw0xAARRGGBB & 0xff))
            {

            }

            ColorX(BYTE a, BYTE r, BYTE g, BYTE b) : Color(a, r, g, b)
            {

            }

            ColorX(int a, int r, int g, int b) : Color((BYTE)a, (BYTE)r, (BYTE)g, (BYTE)b)
            {

            }

            ColorX(float a, float r, float g, float b) : Color((BYTE)(a * 0xff), (BYTE)(r * 0xff), (BYTE)(g * 0xff), (BYTE)(b * 0xff))
            {

            }

            ColorX(const RGBQUAD &color) : Color(color.rgbReserved, color.rgbRed, color.rgbGreen, color.rgbBlue)
            {

            }

            ColorX(const D3DCOLORVALUE &color) : Color((BYTE)(color.a * 0xff), (BYTE)(color.r * 0xff), (BYTE)(color.g * 0xff), (BYTE)(color.b * 0xff))
            {

            }

            operator RGBQUAD() const
            {
                RGBQUAD color = { B(), G(), R(), A() };
                return color;
            }

            operator D3DCOLORVALUE() const
            {
                D3DCOLORVALUE color = { R() / 255.f, G() / 255.f, B() / 255.f, A() / 255.f };
                return color;
            }

            static ColorX FromColorRef(COLORREF color)
            {
                return ColorX((BYTE)0xff, (BYTE)GetRValue(color), (BYTE)GetGValue(color), (BYTE)GetBValue(color));
            }

            COLORREF ToColorRef() const
            {
                return RGB(R(), G(), B());
            }

            enum
            {
                Black = 0xff000000,
                Red = 0xffff0000,
                Green = 0xff00ff00,
                Blue = 0xff0000ff,
                Yellow = 0xffffff00,
                Cyan = 0xff00ffff,
                Purple = 0xffff00ff,
                White = 0xffffffff,
            };
        };

    } // namespace Windows
} // namespace xl

#endif // #ifndef __XLGRAPHICS_H_E294CF1C_2CFD_4AA9_9531_5BEF7AB8677A_INCLUDED__
