//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   Main.cpp
//    Author:      Streamlet
//    Create Time: 2011-04-30
//    Description: 
//
//    Version history:
//
//
//
//------------------------------------------------------------------------------


#include <stdio.h>
#include "../../Include/xl/Win32/Rendering/xlRenderer.h"
#include <tuple>

int main()
{
//     xl::Bitmap bmp;
//     HBITMAP h = bmp;
//     Gdiplus::Bitmap *p = bmp;
//     ID2D1Bitmap *p1 = bmp;
//     ID2D1Bitmap1 *p2 = bmp;
// 

    xl::SizeX s(10, 20);

    xl::PointX p(100.0f, 200.0f);

    xl::RectX r(1, 1, 200, 200);
    r.Inflate(1);
    r.Deflate(2, 2, 2, 2);

    xl::ColorX c = xl::ColorX::Red;
    c.G() = 15;
    c.B() = 16;

    xl::Tuple<> x;
    xl::Tuple<int> xx(1);
    xl::Tuple<int, int> xxx(1, 2);
    xl::Tuple<int, int, int> xxxx(1, 2, 3);
    xl::Tuple<int, int, int, int> xxxxx(1, 2, 3, 4);

    xx += xxx;

    xxxxx.Set<0>(3);

    std::tuple<int, float, bool> a(100, 2.0f, true);


    return 0;
}
